class PlayerZoneController
{
    private ref map<string, ref map<string, ref ZoneBase>> m_PlayerActiveZones;
    private ref map<string, ref ZoneBase> m_PlayerCurrentActiveZone;
    private ref map<string, float> m_PlayerExitTimersPvP;
    private ref map<string, float> m_PlayerExitTimersRaid;
    private ref map<string, float> m_PlayerExitTimersSafeZone;
    private ref map<string, float> m_PlayerExitTimersPvE;
    private ref map<string, bool> m_PlayerAliveStates;
    private ref map<string, bool> m_LastForceFirstPersonState;
    private ref map<string, bool> m_PlayerBleedingScheduled;
    void PlayerZoneController()
    {
        m_PlayerActiveZones         = new map<string, ref map<string, ref ZoneBase>>();
        m_PlayerCurrentActiveZone   = new map<string, ref ZoneBase>();
        m_PlayerExitTimersPvP       = new map<string, float>();
        m_PlayerExitTimersRaid      = new map<string, float>();
        m_PlayerExitTimersSafeZone = new map<string, float>();
        m_PlayerExitTimersPvE       = new map<string, float>();
        m_PlayerAliveStates         = new map<string, bool>();
        m_LastForceFirstPersonState = new map<string, bool>();
        m_PlayerBleedingScheduled   = new map<string, bool>();
    }
/*
----------------------------------------------------------
Getters + Helpers
----------------------------------------------------------
*/
    private PlayerBase GetPlayerByID(string playerID)
    {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase pb = PlayerBase.Cast(man);
            if (pb && pb.GetIdentity() && pb.GetIdentity().GetId() == playerID)
            {
                return pb;
            }
        }
        return null;
    }
    bool IsRaidExitTimerActive(string playerID)
    {
        return m_PlayerExitTimersRaid.Contains(playerID);
    }
/*
----------------------------------------------------------
Update - Main loop over all players to control zone logics
----------------------------------------------------------
*/
    void Update(float deltaTime)
    {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player) continue;
            PlayerIdentity identity = player.GetIdentity();
            if (!identity)
            {
                NinjinsPvPPvE.LogWarning("[WARNING] Player identity is null. Skipping.");
                continue;
            }
            string playerID   = identity.GetId();
            bool   isAlive    = player.IsAlive();
            bool   wasAlive   = false;
            if (m_PlayerAliveStates.Contains(playerID))
            {
                wasAlive = m_PlayerAliveStates.Get(playerID);
            }
            m_PlayerAliveStates.Set(playerID, isAlive);
            #ifdef DZ_Expansion_SpawnSelection
            if (player.m_Expansion_SpawnSelect)
            {
                NinjinsPvPPvE.LogDebug("Skipping zone checks - player is in Expansion spawn selection: " + identity.GetName());
                continue;
            }
            #endif
            if (wasAlive && !isAlive)
            {
                NinjinsPvPPvE.LogKillsDamage("Player " + identity.GetName() + " (" + playerID + ") died. Resetting exit timers.");
                ResetPlayerExitTimers(playerID);
            }
            if (!isAlive)
            {
                continue;
            }
            if (!m_PlayerActiveZones.Contains(playerID))
            {
                m_PlayerActiveZones.Set(playerID, new map<string, ref ZoneBase>());
            }
            ref map<string, ref ZoneBase> playerZones = m_PlayerActiveZones.Get(playerID);
            array<ref ZoneBase> staticZones  = ZoneManager.GetInstance().m_Zones;
            array<ref ZoneBase> dynamicZones = ZoneManager.GetInstance().m_DynamicZones;
            ControlZones(player, player.GetPosition(), staticZones,  playerZones);
            ControlZones(player, player.GetPosition(), dynamicZones, playerZones);
            DeterminePlayerState(player, playerID, playerZones);
            bool insideNoBuild = false;
            foreach (ZoneBase z : staticZones)
            {
                if (z.IsInsideNoBuild(player.GetPosition()))
                {
                    insideNoBuild = true;
                    break;
                }
            }
            if (!insideNoBuild)
            {
                foreach (ZoneBase z2 : dynamicZones)
                {
                    if (z2.IsInsideNoBuild(player.GetPosition()))
                    {
                        insideNoBuild = true;
                        break;
                    }
                }
            }
            player.UpdateNoBuildState(insideNoBuild);
            UpdatePvPExitTimer(playerID, deltaTime, playerZones);
            UpdatePvEExitTimer(playerID, deltaTime, playerZones);
            UpdateRaidExitTimer(playerID, deltaTime, playerZones);
            UpdateSafeZoneExitTimer(playerID, deltaTime, playerZones);
        }
    }
/*
----------------------------------------------------------
Helper to update a SINGLE player
----------------------------------------------------------
*/
    void UpdatePlayer(PlayerBase player)
    {
        if (!player) 
            return;
        PlayerIdentity identity = player.GetIdentity();
        if (!identity) 
            return;
        string playerID = identity.GetId();
        #ifdef DZ_Expansion_SpawnSelection
        if (player.m_Expansion_SpawnSelect)
        {
            NinjinsPvPPvE.LogDebug("Skipping UpdatePlayer - still in Expansion spawn selection.");
            return;
        }
        #endif
        if (!m_PlayerActiveZones.Contains(playerID))
        {
            m_PlayerActiveZones.Set(playerID, new map<string, ref ZoneBase>());
        }
        ref map<string, ref ZoneBase> playerZones = m_PlayerActiveZones.Get(playerID);
        array<ref ZoneBase> staticZones  = ZoneManager.GetInstance().m_Zones;
        array<ref ZoneBase> dynamicZones = ZoneManager.GetInstance().m_DynamicZones;
        ControlZones(player, player.GetPosition(), staticZones,  playerZones);
        ControlZones(player, player.GetPosition(), dynamicZones, playerZones);
        DeterminePlayerState(player, playerID, playerZones);
        SendPlayerZoneStateToClient(player);
    }
    void SendPlayerZoneStateToClient(PlayerBase player)
    {
        if (!player || !player.GetIdentity()) 
            return;
        string playerID = player.GetIdentity().GetId();
        Param1<bool> paramNoLog = new Param1<bool>(player.netSync_IsInNoLogOutZone);
        GetGame().RPCSingleParam(player, NinjinCustomRPCs.RPC_UPDATE_NOLOGOUT_STATE, paramNoLog, true, player.GetIdentity());
        Param1<bool> paramPVP = new Param1<bool>(player.netSync_IsInPvPZone);
        GetGame().RPCSingleParam(player, NinjinCustomRPCs.RPC_UPDATE_PVP_STATE, paramPVP, true, player.GetIdentity());
        Param1<bool> paramPvE = new Param1<bool>(player.netSync_IsInPvEZone);
        GetGame().RPCSingleParam(player, NinjinCustomRPCs.RPC_UPDATE_PVE_STATE, paramPvE, true, player.GetIdentity());
        Param1<bool> paramRaid = new Param1<bool>(player.netSync_IsInRaidMode);
        GetGame().RPCSingleParam(player, NinjinCustomRPCs.RPC_UPDATE_RAID_MODE, paramRaid, true, player.GetIdentity());
        Param1<bool> paramSafeZone = new Param1<bool>(player.netSync_IsInSafeZone);
        GetGame().RPCSingleParam(player, NinjinCustomRPCs.RPC_UPDATE_SAFEZONE_STATE, paramSafeZone, true, player.GetIdentity());
        Param1<bool> paramForceFirstPerson = new Param1<bool>(player.netSync_ForceFirstPerson);
        GetGame().RPCSingleParam(player, NinjinCustomRPCs.RPC_UPDATE_FORCE_FIRST_PERSON, paramForceFirstPerson, true, player.GetIdentity());
        Param1<bool> paramPaint = new Param1<bool>(player.netSync_IsInPaintBallMode);
        GetGame().RPCSingleParam(player, NinjinCustomRPCs.RPC_UPDATE_PAINTBALL_MODE, paramPaint, true, player.GetIdentity());
    }
/*
----------------------------------------------------------
ControlZones - Controls Zone Enter + Exit and so on
----------------------------------------------------------
*/
    private void ControlZones(PlayerBase player, vector playerPos, array<ref ZoneBase> zones, map<string, ref ZoneBase> playerZones)
    {
        PlayerIdentity identity = player.GetIdentity();
        string playerID = identity.GetId();
        int activeType = -1;
        if (m_PlayerCurrentActiveZone.Contains(playerID))
        {
            ZoneBase activeZone = m_PlayerCurrentActiveZone.Get(playerID);
            if (activeZone)
            {
                activeType = activeZone.type;
            }
        }
        foreach (ZoneBase zone : zones)
        {
            string zoneName = zone.GetName();
            bool isInside = zone.IsInside(playerPos);
            bool wasInside = playerZones.Contains(zoneName);
            int currentZoneType = zone.type;
            string zName;
            string zType;
            vector pos;
            string coords;
            if (isInside && !wasInside)
            {
                zName = zone.GetName();
                zType = DefaultZoneTitle(zone.type);
                pos = player.GetPosition();
                coords = "(" + pos[0].ToString() + "," + pos[2].ToString() + ")";
                playerZones.Set(zoneName, zone);
                NinjinsPvPPvE.LogDebug("Player " + identity.GetName() + " (" + playerID + ") entered zone: " + zoneName);
                if (g_MainConfig.EnableCfToolsLogs)
                {
                    NinjinSendToCFTools(player, "", "", "entered zone: " + zName + " [" + zType + "] " + coords);
                }
                if (zone.type == ZONE_TYPE_VISUAL)
                {
                    SendEnterNotification(player, zone);
                    SendEnterUIMessage(player, zone);
                }
                if (zone.type == ZONE_TYPE_PVE && player && player.netSync_IsInPvPZone)
                {
                    if (!m_PlayerExitTimersPvP.Contains(playerID))
                    {
                        StartPvPExitTimer(playerID);
                        SendTimerNotification(playerID, ZONE_TYPE_PVP, g_MainConfig.PvPExitCountdown, true);
                        NinjinsPvPPvE.LogDebug("Triggered PvP EXIT TIMER for player " + playerID + " upon ENTERING PVE while still flagged as PvP.");
                    }
                }
                if (currentZoneType == ZONE_TYPE_PVE && m_PlayerExitTimersPvE.Contains(playerID))
                {
                    m_PlayerExitTimersPvE.Remove(playerID);
                    SendTimerNotification(playerID, ZONE_TYPE_PVE, 0, false);
                }
                if (currentZoneType == ZONE_TYPE_PVP && m_PlayerExitTimersPvP.Contains(playerID))
                {
                    m_PlayerExitTimersPvP.Remove(playerID);
                    SendTimerNotification(playerID, ZONE_TYPE_PVP, 0, false);
                    NinjinsPvPPvE.LogDebug("Cleared PvP exit timer for player " + playerID + " upon PvP re‑entry.");
                }
                if (currentZoneType == ZONE_TYPE_PVP && m_PlayerExitTimersPvE.Contains(playerID))
                {
                    m_PlayerExitTimersPvE.Remove(playerID);
                    SendTimerNotification(playerID, ZONE_TYPE_PVE, 0, false);
                    NinjinsPvPPvE.LogDebug("Cleared PvE exit timer for player " + playerID + " upon entering PvP zone.");
                }
                if (currentZoneType == ZONE_TYPE_RAID && m_PlayerExitTimersRaid.Contains(playerID))
                {
                    m_PlayerExitTimersRaid.Remove(playerID);
                    SendTimerNotification(playerID, ZONE_TYPE_RAID, 0, false);
                }
                if (currentZoneType == ZONE_TYPE_SAFEZONE && m_PlayerExitTimersSafeZone.Contains(playerID))
                {
                    m_PlayerExitTimersSafeZone.Remove(playerID);
                    SendTimerNotification(playerID, ZONE_TYPE_SAFEZONE, 0, false);
                }
            }
            else if (!isInside && wasInside)
            {
                ZoneBase exitingZone = playerZones.Get(zoneName);
                zName = exitingZone.GetName();
                zType = DefaultZoneTitle(exitingZone.type);
                pos = player.GetPosition();
                coords = "(" + pos[0].ToString() + "," + pos[2].ToString() + ")";
                playerZones.Remove(zoneName);
                NinjinsPvPPvE.LogDebug("Player " + identity.GetName() + " (" + playerID + ") exited zone: " + zoneName);
                if (g_MainConfig.EnableCfToolsLogs)
                {
                    NinjinSendToCFTools(player, "", "", "left zone: " + zName + " [" + zType + "] " + coords);
                }
                if (!HasOtherZonesOfType(playerZones, currentZoneType))
                {
                    if (exitingZone.type == ZONE_TYPE_VISUAL)
                    {
                        SendExitNotification(player, exitingZone, 0);
                        SendExitUIMessage(player, exitingZone, 0);
                    }
                    if (currentZoneType == ZONE_TYPE_PVP)
                    {
                        StartPvPExitTimer(playerID);
                        SendTimerNotification(playerID, ZONE_TYPE_PVP, g_MainConfig.PvPExitCountdown, true);
                    }
                    if (currentZoneType == ZONE_TYPE_PVE)
                    {
                        StartPvEExitTimer(playerID);
                        SendTimerNotification(playerID, ZONE_TYPE_PVE, g_MainConfig.PvEExitCountdown, true);
                    }
                    if (currentZoneType == ZONE_TYPE_SAFEZONE)
                    {
                        StartSafeZoneExitTimer(playerID);
                        SendTimerNotification(playerID, ZONE_TYPE_SAFEZONE, g_MainConfig.SafeZoneExitCountdown, true);
                    }
                    else if (currentZoneType == ZONE_TYPE_RAID)
                    {
                        StartRaidExitTimer(playerID);
                        SendTimerNotification(playerID, ZONE_TYPE_RAID, g_MainConfig.RaidExitCountdown, true);
                    }
                }
            }
        }
    }
    private bool HasOtherZonesOfType(map<string, ref ZoneBase> playerZones, int zoneType)
    {
        foreach (string zoneName, ref ZoneBase zone : playerZones)
        {
            if (zone.type == zoneType)
            {
                return true;
            }
        }
        return false;
    }
/*
----------------------------------------------------------
DeterminePlayerState
----------------------------------------------------------
*/
    void DeterminePlayerState(PlayerBase player, string playerID, map<string, ref ZoneBase> playerZones)
    {
        if (!player) 
            return;
        int highestPriority = 0;
        ref ZoneBase highestZone = null;
        array<string> zonesToRemove = new array<string>();
        vector targetPos = "0 0 0";
        foreach (string existingZoneName, ref ZoneBase zone : playerZones)
        {
            if (!ZoneManager.GetInstance().IsZoneNameExists(existingZoneName))
            {
                zonesToRemove.Insert(existingZoneName);
            }
            else if (zone.priority > highestPriority)
            {
                highestPriority = zone.priority;
                highestZone = zone;
            }
        }
        foreach (string removedName : zonesToRemove)
        {
            ref ZoneBase removedZone = playerZones.Get(removedName);
            playerZones.Remove(removedName);
            if (removedZone)
            {
                NinjinsPvPPvE.LogDebug("Player " + player.GetIdentity().GetName() + " (" + playerID + ") exited removed zone: " + removedName);
            }
        }
        if (highestZone && highestZone.type == ZONE_TYPE_VISUAL)
        {
            if (!m_PlayerExitTimersPvP.Contains(playerID) && !m_PlayerExitTimersRaid.Contains(playerID))
            {
                highestZone = null;
            }
        }
        bool desiredPaintBall = false;
        bool desiredNoLogOut = false;
        bool desiredPvP      = false;
        bool desiredPvE      = false;
        bool desiredRaid     = false;
        bool desiredSafeZone = false;
        bool desiredForce1P  = false;
        ref ZoneBase currentActiveZone = m_PlayerCurrentActiveZone.Get(playerID);
        if (highestZone)
        {
            switch (highestZone.type)
            {
                case ZONE_TYPE_PVE:
                {
                    if (m_PlayerExitTimersPvP.Contains(playerID))
                    {
                        desiredPvP = true;
                        desiredPvE = false;
                    }
                    else
                    {
                        desiredPvE = true;
                    }
                    break;
                }
                case ZONE_TYPE_PVP:
                    desiredPvP = true;
                    break;
                case ZONE_TYPE_RAID:
                    desiredRaid = true;
                    break;
                case ZONE_TYPE_SAFEZONE:
                    desiredSafeZone = true;
                    break;
                case ZONE_TYPE_PAINTBALL:
                    desiredPaintBall = true;
                    break;
            }
            desiredForce1P = highestZone.forceFirstPerson;
            if (m_PlayerExitTimersPvP.Contains(playerID) && currentActiveZone && currentActiveZone.type == ZONE_TYPE_PVP)
            {
                highestZone = currentActiveZone;
                desiredPvP  = true;
                desiredPvE  = false;
                desiredRaid = false;
                desiredForce1P = currentActiveZone.forceFirstPerson;
            }
            if (m_PlayerExitTimersRaid.Contains(playerID) && currentActiveZone && currentActiveZone.type == ZONE_TYPE_RAID)
            {
                highestZone = currentActiveZone;
                desiredRaid = true;
                desiredPvP  = false;
                desiredPvE  = false;
                desiredForce1P = currentActiveZone.forceFirstPerson;
            }
            if (m_PlayerExitTimersSafeZone.Contains(playerID) && currentActiveZone && currentActiveZone.type == ZONE_TYPE_SAFEZONE)
            {
                highestZone = currentActiveZone;
                desiredSafeZone = true;
                desiredPvE      = false;
                desiredPvP      = false;
                desiredRaid     = false;
                desiredForce1P  = currentActiveZone.forceFirstPerson;
            }
            if (m_PlayerExitTimersPvE.Contains(playerID) && currentActiveZone && currentActiveZone.type == ZONE_TYPE_PVE)
            {
                highestZone      = currentActiveZone;
                desiredPvE       = true;
                desiredPvP       = false;
                desiredRaid      = false;
                desiredSafeZone  = false;
                desiredForce1P   = currentActiveZone.forceFirstPerson;
            }
        }
        else
        {
            if (m_PlayerExitTimersPvP.Contains(playerID))
            {
                desiredPvP = true;
                desiredPvE = false;
                desiredRaid = false;
                desiredSafeZone = false;
                if (currentActiveZone && currentActiveZone.type == ZONE_TYPE_PVP)
                {
                    desiredForce1P = currentActiveZone.forceFirstPerson;
                }
                else
                {
                    desiredForce1P = g_MainConfig.ForceFirstPersonGlobalPvP;
                }
            }
            else if (m_PlayerExitTimersRaid.Contains(playerID))
            {
                desiredRaid    = true;
                desiredPvP     = false;
                desiredPvE     = false;
                desiredSafeZone = false;
                if (currentActiveZone && currentActiveZone.type == ZONE_TYPE_RAID)
                {
                    desiredForce1P = currentActiveZone.forceFirstPerson;
                }
                else
                {
                    desiredForce1P = g_MainConfig.ForceFirstPersonGlobalPvP;
                }
            }
            else if (m_PlayerExitTimersSafeZone.Contains(playerID))
            {
                desiredSafeZone = true;
                desiredPvP      = false;
                desiredPvE      = false;
                desiredRaid     = false;
                if (currentActiveZone && currentActiveZone.type == ZONE_TYPE_SAFEZONE)
                {
                    desiredForce1P = currentActiveZone.forceFirstPerson;
                }
                else
                {
                    desiredForce1P = g_MainConfig.ForceFirstPersonGlobalPvE;
                }
            }
            else if (m_PlayerExitTimersPvE.Contains(playerID))
            {
                desiredPvE      = true;
                desiredSafeZone = false;
                desiredPvP      = false;
                desiredRaid     = false;
                if (currentActiveZone && currentActiveZone.type == ZONE_TYPE_PVE)
                {
                    desiredForce1P = currentActiveZone.forceFirstPerson;
                }
                else
                {
                    desiredForce1P = g_MainConfig.ForceFirstPersonGlobalPvE;
                }
            }
            else
            {
                if (g_MainConfig.IsPvPEverywhereActive())
                {
                    desiredPvP = true;
                    desiredForce1P = g_MainConfig.ForceFirstPersonGlobalPvP;
                }
                else if (g_MainConfig.IsPvEEverywhereActive())
                {
                    desiredPvE = true;
                    desiredForce1P = g_MainConfig.ForceFirstPersonGlobalPvE;
                }
                else
                {
                    desiredPvP = false;
                    desiredPvE = false;
                    desiredForce1P = false;
                }
            }
        }
        if (currentActiveZone != highestZone)
        {
            bool allowSameTypeNotifs = g_MainConfig.AllowSameZoneTypeEnterNotifications;
            if (currentActiveZone)
            {
                bool noOtherSameTypeZones = !HasOtherZonesOfType(playerZones, currentActiveZone.type);
                if (noOtherSameTypeZones || allowSameTypeNotifs)
                {
                    //NinjinsPvPPvE.LogDebug("Exit notification triggered. Either no other zones of type or config allows same-type notifications.");
                    SendExitNotification(player, currentActiveZone, 0);
                    SendExitUIMessage(player, currentActiveZone, 0);
                }
                else
                {
                    NinjinsPvPPvE.LogDebug("Skipped exit notification. Still inside another zone of type: " + currentActiveZone.type);
                }
            }
            if (highestZone)
            {
                bool notifyEnter = false;
                if (!currentActiveZone || highestZone.type != currentActiveZone.type)
                {
                    notifyEnter = true;
                }
                else if (allowSameTypeNotifs && highestZone.name != currentActiveZone.name)
                {
                    notifyEnter = true;
                }
                if (notifyEnter)
                {
                    if (highestZone.type == ZONE_TYPE_RAID && !IsPlayerAuthorizedForRaid(player))
                    {
                        SendRaidEntryNotification(player);
                        if (!m_PlayerBleedingScheduled.Contains(playerID) || !m_PlayerBleedingScheduled.Get(playerID))
                        {
                            m_PlayerBleedingScheduled.Set(playerID, true);
                            ScheduleBleeding(player);
                        }
                    }
                    else
                    {
                        SendEnterNotification(player, highestZone);
                        SendEnterUIMessage(player, highestZone);
                    }
                    //NinjinsPvPPvE.LogDebug("Enter notification triggered. Zone: " + highestZone.name + ", type: " + highestZone.type);
                }
                else
                {
                    NinjinsPvPPvE.LogDebug("Skipped enter notification. Same zone type (" + highestZone.type + ") and config disallows same-type messages.");
                }
            }
            m_PlayerCurrentActiveZone.Set(playerID, highestZone);
        }
        foreach (string zName, ref ZoneBase z : playerZones)
        {
            if (z && z.NoLogOut)
            {
                desiredNoLogOut = true;
                targetPos       = z.NoLogOutTeleportPos;
                break;
            }
        }
        player.UpdatePaintBallMode(desiredPaintBall);
        player.SetNoLogOutTeleportPos(targetPos);
        player.UpdatePvPState(desiredPvP);
        player.UpdatePvEState(desiredPvE);
        player.UpdateRaidMode(desiredRaid);
        player.UpdateSafeZoneState(desiredSafeZone);
        player.UpdateForceFirstPerson(desiredForce1P);
        player.UpdateNoLogOutState(desiredNoLogOut);
        if (!desiredRaid && m_PlayerBleedingScheduled.Contains(playerID))
        {
            m_PlayerBleedingScheduled.Remove(playerID);
        }
    }
/*
----------------------------------------------------------
Start + Update Player Exit Timers states
----------------------------------------------------------
*/
    private void StartSafeZoneExitTimer(string playerID)
    {
        PlayerBase pb = GetPlayerByID(playerID);
        if (!pb) 
            return;
        if (!m_PlayerExitTimersSafeZone.Contains(playerID))
        {
            m_PlayerExitTimersSafeZone.Set(playerID, g_MainConfig.SafeZoneExitCountdown);
            NinjinsPvPPvE.LogDebug("SafeZone exit timer started for " + pb.GetIdentity().GetName() + " (" + playerID + ")");
            SendTimerNotification(playerID, ZONE_TYPE_SAFEZONE, g_MainConfig.SafeZoneExitCountdown, true);
        }
    }
    private void StartPvEExitTimer(string playerID)
    {
        PlayerBase pb = GetPlayerByID(playerID);
        if (!pb)
        {
            NinjinsPvPPvE.LogDebug("[ERROR] Could not find player with ID: " + playerID + " to start PvP exit timer.");
            return;
        }
        if (!m_PlayerExitTimersPvE.Contains(playerID))
        {
            m_PlayerExitTimersPvE.Set(playerID, g_MainConfig.PvEExitCountdown);
            NinjinsPvPPvE.LogDebug("PvE exit timer started for " + playerID);
            SendTimerNotification(playerID, ZONE_TYPE_PVE, g_MainConfig.PvEExitCountdown, true);
        }
    }
    private void StartPvPExitTimer(string playerID)
    {
        PlayerBase pb = GetPlayerByID(playerID);
        if (!pb)
        {
            NinjinsPvPPvE.LogDebug("[ERROR] Could not find player with ID: " + playerID + " to start PvP exit timer.");
            return;
        }
        if (!m_PlayerExitTimersPvP.Contains(playerID))
        {
            m_PlayerExitTimersPvP.Set(playerID, g_MainConfig.PvPExitCountdown);
            NinjinsPvPPvE.LogDebug("PvP exit timer started for player: " + pb.GetIdentity().GetName() + " (" + playerID + ")");
            SendTimerNotification(playerID, ZONE_TYPE_PVP, g_MainConfig.PvPExitCountdown, true);
        }
    }
    private void StartRaidExitTimer(string playerID)
    {
        PlayerBase pb = GetPlayerByID(playerID);
        if (!pb)
        {
            NinjinsPvPPvE.LogDebug("[ERROR] Could not find player with ID: " + playerID + " to start Raid exit timer.");
            return;
        }
        if (!m_PlayerExitTimersRaid.Contains(playerID))
        {
            m_PlayerBleedingScheduled.Remove(playerID);
            NinjinsPvPPvE.LogDebug("Removed bleeding schedule for " + pb.GetIdentity().GetName() + " (" + playerID + ")");
            m_PlayerExitTimersRaid.Set(playerID, g_MainConfig.RaidExitCountdown);
            NinjinsPvPPvE.LogDebug("Raid exit timer started for " + pb.GetIdentity().GetName() + " (" + playerID + ")");
            SendTimerNotification(playerID, ZONE_TYPE_RAID, g_MainConfig.RaidExitCountdown, true);
        }
    }
    private void UpdatePvEExitTimer(string playerID, float deltaTime, map<string, ref ZoneBase> playerZones)
    {
        if (!m_PlayerExitTimersPvE.Contains(playerID)) 
            return;
        float remaining = m_PlayerExitTimersPvE.Get(playerID) - deltaTime;
        if (remaining <= 0)
        {
            m_PlayerExitTimersPvE.Remove(playerID);
            NinjinsPvPPvE.LogDebug("PvE exit timer expired for player: " + playerID);
            DeterminePlayerState(GetPlayerByID(playerID), playerID, playerZones);
            SendTimerNotification(playerID, ZONE_TYPE_PVE, 0, false);
        }
        else
        {
            m_PlayerExitTimersPvE.Set(playerID, remaining);
            SendTimerNotification(playerID, ZONE_TYPE_PVE, remaining, true);
        }
    }
    private void UpdatePvPExitTimer(string playerID, float deltaTime, map<string, ref ZoneBase> playerZones)
    {
        if (!m_PlayerExitTimersPvP.Contains(playerID)) 
            return;
        float remaining = m_PlayerExitTimersPvP.Get(playerID) - deltaTime;
        if (remaining <= 0)
        {
            m_PlayerExitTimersPvP.Remove(playerID);
            NinjinsPvPPvE.LogDebug("PvP exit timer expired for player: " + playerID);
            DeterminePlayerState(GetPlayerByID(playerID), playerID, playerZones);
            SendTimerNotification(playerID, ZONE_TYPE_PVP, 0, false);
        }
        else
        {
            m_PlayerExitTimersPvP.Set(playerID, remaining);
            SendTimerNotification(playerID, ZONE_TYPE_PVP, remaining, true);
        }
    }
    private void UpdateRaidExitTimer(string playerID, float deltaTime, map<string, ref ZoneBase> playerZones)
    {
        if (!m_PlayerExitTimersRaid.Contains(playerID)) 
            return;
        float remaining = m_PlayerExitTimersRaid.Get(playerID) - deltaTime;
        if (remaining <= 0)
        {
            m_PlayerExitTimersRaid.Remove(playerID);
            NinjinsPvPPvE.LogDebug("Raid exit timer expired for player: " + playerID);
            DeterminePlayerState(GetPlayerByID(playerID), playerID, playerZones);
            SendTimerNotification(playerID, ZONE_TYPE_RAID, 0, false);
        }
        else
        {
            m_PlayerExitTimersRaid.Set(playerID, remaining);
            SendTimerNotification(playerID, ZONE_TYPE_RAID, remaining, true);
        }
    }
    private void UpdateSafeZoneExitTimer(string playerID, float deltaTime, map<string, ref ZoneBase> playerZones)
    {
        if (!m_PlayerExitTimersSafeZone.Contains(playerID)) 
            return;
        float remaining = m_PlayerExitTimersSafeZone.Get(playerID) - deltaTime;
        if (remaining <= 0)
        {
            m_PlayerExitTimersSafeZone.Remove(playerID);
            NinjinsPvPPvE.LogDebug("SafeZone exit timer expired for player: " + playerID);
            DeterminePlayerState(GetPlayerByID(playerID), playerID, playerZones);
            SendTimerNotification(playerID, ZONE_TYPE_SAFEZONE, 0, false);
        }
        else
        {
            m_PlayerExitTimersSafeZone.Set(playerID, remaining);
            SendTimerNotification(playerID, ZONE_TYPE_SAFEZONE, remaining, true);
        }
    }
/*
----------------------------------------------------------
RaidEntryNotification + Effects
----------------------------------------------------------
*/
    void SendRaidEntryNotification(PlayerBase player)
    {
        NotificationSystem.Create(new StringLocaliser("Unauthorized Raid Entry"),new StringLocaliser("You have entered a Raid Zone without authorization. Bleeding will be applied in 5 seconds."),"NinjinsPvPPvE/gui/exclamation.edds", ARGB(255, 255, 0, 0),10.0,player.GetIdentity());
        NinjinsPvPPvE.LogDebug("Sent Raid Entry Notification to player: " + player.GetIdentity().GetName());
    }
    private bool IsPlayerAuthorizedForRaid(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
            return false;
        if (!g_MainConfig || !g_MainConfig.AllowedRaidingPlayers)
            return false;
        if (g_MainConfig.AllowAnyPlayerInRaidZone)
            return true;
        string guidToCheck = player.GetIdentity().GetId();
        foreach (string entry : g_MainConfig.AllowedRaidingPlayers)
        {
            TStringArray parts = new TStringArray;
            entry.Split(":", parts);
            string guid;
            if (parts.Count() > 1)
                guid = parts[1].Trim();
            else
                guid = parts[0].Trim();
            if (guid == guidToCheck)
                return true;
        }
        return false;
    }
    private void ApplyBleedingToPlayer(PlayerBase player)
    {
        if (!player)
        {
            NinjinsPvPPvE.LogWarning("[PlayerZoneController][ApplyBleedingToPlayer] Player is null.");
            return;
        }
        string playerID = player.GetIdentity().GetId();
        if (!m_PlayerBleedingScheduled.Contains(playerID) || !m_PlayerBleedingScheduled.Get(playerID))
            return;
        player.ApplyUnauthorizedRaidBleeding();
        NinjinsPvPPvE.LogDebug("Applied bleeding to player: " + player.GetIdentity().GetName() + " (" + playerID + ")");
        if (IsPlayerStillInRaidZoneUnauthorized(playerID))
        {
            ScheduleBleeding(player);
            NinjinsPvPPvE.LogDebug("Bleeding rescheduled for player: " + player.GetIdentity().GetName() + " (" + playerID + ")");
        }
        else
        {
            m_PlayerBleedingScheduled.Remove(playerID);
            NinjinsPvPPvE.LogDebug("Removed bleeding schedule for player: " + player.GetIdentity().GetName() + " (" + playerID + ") - Bleeding stopped.");
        }
    }
    private void ScheduleBleeding(PlayerBase player)
    {
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.ApplyBleedingToPlayer, 8000, false, player);
    }
    private bool IsPlayerStillInRaidZoneUnauthorized(string playerID)
    {
        if (!m_PlayerActiveZones.Contains(playerID)) 
            return false;
        ref map<string, ref ZoneBase> zones = m_PlayerActiveZones.Get(playerID);
        foreach (string zName, ref ZoneBase z : zones)
        {
            if (z.type == ZONE_TYPE_RAID)
            {
                PlayerBase pb = GetPlayerByID(playerID);
                if (pb && !IsPlayerAuthorizedForRaid(pb))
                {
                    return true;
                }
            }
        }
        return false;
    }
/*
----------------------------------------------------------
Send Enter + Exit UIMessage - notify client on zone enter
----------------------------------------------------------
*/
    private void SendEnterUIMessage(PlayerBase player, ZoneBase zone)
    {
        string playerID = player.GetIdentity().GetId();
        int zType = zone.type;
        string iconPath;
        if (zone.customIcon != "")
        {
            iconPath = g_MainConfig.ResolveIcon(zone.customIcon);
        }
        else
        {
            iconPath = g_MainConfig.ResolveIcon(zone.customIcon);
        }
        Param4<string, int, string, string> enterParam = new Param4<string, int, string, string>(playerID,zType,"Entered " + DefaultZoneTitle(zType) + " " + zone.name + " Zone.",iconPath);
        GetRPCManager().SendRPC("NinjinsPvPPvE", "UpdateNotificationUI", enterParam, true, player.GetIdentity());
    }
    private void SendExitUIMessage(PlayerBase player, ZoneBase zone, float countdownTime)
    {
        if (!g_MainConfig.ExitZoneNotification)
        {
            NinjinsPvPPvE.LogDebug("Exit UI message disabled in MainConfig. Skipping UI message for zone: " + zone.GetName());
            return;
        }
        string   playerID  = player.GetIdentity().GetId();
        int      zType     = zone.type;
        bool     showTimer = (countdownTime > 0);
        string   zoneName  = zone.GetName();
        string exitMsg = g_MainConfig.ExitNotificationText;
        exitMsg.Replace("{seconds}", Math.Ceil(countdownTime).ToString());
        Param4<string, int, float, bool> exitParam = new Param4<string, int, float, bool>(playerID,zType,countdownTime,showTimer);
        GetRPCManager().SendRPC("NinjinsPvPPvE", "ZoneNotification", exitParam, true, player.GetIdentity());
    }
/*
----------------------------------------------------------
Enter + Exit Notification to Player
----------------------------------------------------------
*/
    private void SendEnterNotification(PlayerBase player, ZoneBase zone)
    {
        if (!zone.enableCustomMessages)
        {
            NinjinsPvPPvE.LogDebug("Skipping enter notification for zone: " + zone.GetName() + " (enableCustomMessages=0)");
            return;
        }
        int color = zone.notificationColor;
        string title;
        string msg;
        string icon;
        if (zone.enableCustomMessages)
        {
            title = zone.customTitle;
            msg   = zone.customMessageEnter;
            icon  = g_MainConfig.ResolveIcon(zone.customIcon);
        }
        else
        {
            title = DefaultZoneTitle(zone.type);
            msg   = "You have exited " + zone.name;
            icon  = g_MainConfig.ResolveIcon(zone.customIcon);
        }
        NotificationSystem.Create(new StringLocaliser(title),new StringLocaliser(msg),icon,color,5.0,player.GetIdentity());
    }
    private void SendExitNotification(PlayerBase player, ZoneBase zone, float countdownTime)
    {
        if (!g_MainConfig.ExitZoneNotification)
        {
            NinjinsPvPPvE.LogDebug("Exit notification disabled in MainConfig. Skipping exit notification for zone: " + zone.GetName());
            return;
        }
        if (!zone.enableCustomMessages)
        {
            NinjinsPvPPvE.LogDebug("Skipping exit notification for zone: " + zone.GetName() + " (enableCustomMessages=0)");
            return;
        }
        int color = zone.notificationColor;
        string title;
        string msg;
        string icon;
        if (zone.enableCustomMessages)
        {
            title = zone.customTitle;
            msg   = zone.customMessageExit;
            icon  = g_MainConfig.ResolveIcon(zone.customIcon);
        }
        else
        {
            title = DefaultZoneTitle(zone.type);
            msg   = "You have exited " + zone.name;
            icon  = g_MainConfig.ResolveIcon(zone.customIcon);
        }
        NotificationSystem.Create(new StringLocaliser(title),new StringLocaliser(msg),icon,color,5.0,player.GetIdentity());
    }
/*
----------------------------------------------------------
Enter + Reset Timer Notification to Player
----------------------------------------------------------
*/
    private void SendTimerNotification(string playerID, int zoneType, float remainingTime, bool isActive)
    {
        if (!g_MainConfig.ExitZoneNotification)
        {
            NinjinsPvPPvE.LogDebug("Exit timer notifications disabled in MainConfig. Skipping timer notification for player: " + playerID);
            return;
        }
        PlayerBase pb = GetPlayerByID(playerID);
        if (!pb)
        {
            NinjinsPvPPvE.LogWarning("[ERROR] Unable to find player with ID: " + playerID);
            return;
        }
        PlayerIdentity identity = pb.GetIdentity();
        if (!identity)
        {
            NinjinsPvPPvE.LogWarning("[ERROR] PlayerIdentity is null for player: " + playerID);
            return;
        }
        if (remainingTime <= 0)
        {
            isActive = false;
        }
        Param4<string, int, float, bool> param = new Param4<string, int, float, bool>(
            playerID,
            zoneType,
            remainingTime,
            isActive,
        );
        GetRPCManager().SendRPC("NinjinsPvPPvE", "ZoneNotification", param, true, identity);
    }
    private void ResetPlayerExitTimers(string playerID)
    {
        PlayerBase pb = GetPlayerByID(playerID);
        if (!pb)
        {
            NinjinsPvPPvE.LogWarning("[ERROR] Could not find player with ID: " + playerID + " to reset exit timers.");
            return;
        }
        if (m_PlayerExitTimersPvP.Contains(playerID))
        {
            m_PlayerExitTimersPvP.Remove(playerID);
            NinjinsPvPPvE.LogDebug("[Info ] PvP exit timer expired for " + pb.GetIdentity().GetName() + " (" + playerID + ")");
            SendTimerNotification(playerID, ZONE_TYPE_PVP, 0, false);
        }
        if (m_PlayerExitTimersRaid.Contains(playerID))
        {
            m_PlayerExitTimersRaid.Remove(playerID);
            NinjinsPvPPvE.LogDebug("Raid exit timer expired for " + pb.GetIdentity().GetName() + " (" + playerID + ")");
            SendTimerNotification(playerID, ZONE_TYPE_RAID, 0, false);
        }
        if (m_PlayerExitTimersSafeZone.Contains(playerID))
        {
            m_PlayerExitTimersSafeZone.Remove(playerID);
            NinjinsPvPPvE.LogDebug("SafeZone exit timer expired for " + pb.GetIdentity().GetName() + " (" + playerID + ")");
            SendTimerNotification(playerID, ZONE_TYPE_SAFEZONE, 0, false);
        }
        if (m_PlayerActiveZones.Contains(playerID))
        {
            m_PlayerActiveZones.Remove(playerID);
            NinjinsPvPPvE.LogDebug("Cleared active zones for player: " + pb.GetIdentity().GetName() + " (" + playerID + ")");
        }
        if (m_PlayerCurrentActiveZone.Contains(playerID))
        {
            m_PlayerCurrentActiveZone.Remove(playerID);
            NinjinsPvPPvE.LogDebug("Removed current active zone for player: " + pb.GetIdentity().GetName() + " (" + playerID + ")");
        }
        if (m_PlayerBleedingScheduled.Contains(playerID))
        {
            m_PlayerBleedingScheduled.Remove(playerID);
            NinjinsPvPPvE.LogDebug("Removed bleeding schedule for player: " + pb.GetIdentity().GetName() + " (" + playerID + ") - Bleeding stopped.");
        }
        bool forceFirstPerson = g_MainConfig.ForceFirstPersonGlobalPvE;
        if (m_LastForceFirstPersonState.Contains(playerID))
        {
            forceFirstPerson = m_LastForceFirstPersonState.Get(playerID);
            m_LastForceFirstPersonState.Remove(playerID);
            NinjinsPvPPvE.LogDebug("[Info ] Restoring ForceFirstPerson state for " + pb.GetIdentity().GetName() + " (" + playerID + ")");
        }
        else
        {
            NinjinsPvPPvE.LogDebug("Reverting to default ForceFirstPerson for " + pb.GetIdentity().GetName() + " (" + playerID + ")");
        }
        pb.UpdateForceFirstPerson(forceFirstPerson);
    }
/*
----------------------------------------------------------
ReloadZones
----------------------------------------------------------
*/
    void ReloadZones()
    {
        m_PlayerActiveZones.Clear();
        m_PlayerCurrentActiveZone.Clear();
        NinjinsPvPPvE.LogDebug("Reloaded zones and cleared all player active zones.");
        Update(0.0);
    }
/*
----------------------------------------------------------
DefaultZoneTitle - fallback if no custom title
----------------------------------------------------------
*/
    private string DefaultZoneTitle(int type)
    {
        if (type == ZONE_TYPE_PVP)
        {
            return "PvP Zone";
        }
        else if (type == ZONE_TYPE_PVE)
        {
            return "PvE Zone";
        }
        else if (type == ZONE_TYPE_VISUAL)
        {
            return "Visual Zone";
        }
        else if (type == ZONE_TYPE_RAID)
        {
            return "Raid Zone";
        }
        else if (type == ZONE_TYPE_SAFEZONE)
        {
            return "Safe Zone";
        }
        else if (type == ZONE_TYPE_PAINTBALL)
        {
            return "Paintball Zone";
        }
        return "Unknown Zone";
    }
    static void NinjinSendToCFTools(PlayerBase player, string item, string target, string action)
    {
        #ifdef GameLabs
        if (GetGameLabs().IsServer())
        {
            ref _LogPlayerEx logObjectPlayer = new _LogPlayerEx(player);
            action = action + " ";
            ref _Payload_ItemInteract payload = new _Payload_ItemInteract(logObjectPlayer, item, target, action);
            GetGameLabs().GetApi().ItemInteract(new _Callback(), payload);
        }
        #endif
    }
}
