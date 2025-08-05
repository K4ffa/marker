/*
    ==================================================================================
    =                                CLASS: ZoneManager                                =
    =  for managing all zone information (static, dynamic, circle,                  =
    =  polygon). Also handles RPC communication, loading/saving, and sync to clients. =
    ==================================================================================
*/
class ZoneManager
{
 
    static ref ZoneManager instance = null;
    ref array<ref ZoneBase> m_Zones;
    ref array<ref ZoneBase> m_DynamicZones;
    private ref map<string, ref ZoneBase> m_PlayerCurrentActiveZone;
    #ifdef EXPANSIONMODNAVIGATION
    ExpansionMarkerModule m_MarkerModule;
    ref map<string, ExpansionMarkerData> m_ZoneMarkers;
    #endif
    static ZoneManager GetInstance()
    {
        if (!GetGame())
        {
            NinjinsPvPPvE.LogWarning("[ZoneManager] GetGame() returned null.");
            return null;
        }
        if (!instance)
        {
            instance = new ZoneManager();
        }
        return instance;
    }
    void ~ZoneManager()
    {
        m_Zones.Clear();
        m_DynamicZones.Clear();
        m_PlayerCurrentActiveZone.Clear();
        #ifdef EXPANSIONMODNAVIGATION
        ClearAllExpansionMarkers();
        #endif
    }
    private void ZoneManager()
    {
        m_Zones        = new array<ref ZoneBase>();
        m_DynamicZones = new array<ref ZoneBase>();
        m_PlayerCurrentActiveZone = new map<string, ref ZoneBase>();
        InitializeZones();
        #ifdef EXPANSIONMODNAVIGATION
        m_ZoneMarkers = new map<string, ExpansionMarkerData>();
        #endif
    }
/*
--------------------------------------------------------------------------------
Init Zones
--------------------------------------------------------------------------------
*/
    void InitializeZones()
    {
        NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
        if (settings)
        {
            m_Zones = settings.Zones;
        }
        else
        {
            NinjinsPvPPvE.LogDebug("ZoneManager::InitializeZones - No zones found. Initialized with 0 zones.");
        }
    }
    bool IsPvPZone(vector position)
    {
        return IsPositionInZone(position, ZONE_TYPE_PVP);
    }
    bool IsPvEZone(vector position)
    {
        return IsPositionInZone(position, ZONE_TYPE_PVE);
    }
/*
--------------------------------------------------------------------------------
ExpansionMarker
--------------------------------------------------------------------------------
*/
    void CreateExpansionMarkers()
    {
    #ifdef EXPANSIONMODNAVIGATION
        if (!m_MarkerModule)
            CF_Modules<ExpansionMarkerModule>.Get(m_MarkerModule);
        if (!m_MarkerModule)
            return;
        ClearAllExpansionMarkers();
        bool showInWorld;
        vector pos;
        int col;
        foreach (ZoneBase z : m_Zones)
        {
            if (!z.OnlyAllowExpansion2DMarker && !z.EnableExpansion3DMarker)
                continue;
            if (m_ZoneMarkers.Contains(z.GetName()))
                continue;
            string name = z.ExpansionMarkerName;
            if (name == "")
                name = z.GetName();
            string icon = z.Expansion3DIcon;
            if (icon == "")
                icon = "Exclamation";
            pos = z.center;
            if (z.shape == ZoneShape.POLYGON && pos[0] == 0 && pos[1] == 0 && pos[2] == 0)
                pos = z.GetPolygonCentroid();
            pos[0] = pos[0] + z.ZonelabelOffsetX_Meters;
            pos[2] = pos[2] + z.ZonelabelOffsetZ_Meters;
            showInWorld = z.EnableExpansion3DMarker && !z.OnlyAllowExpansion2DMarker;
            if (z.ZoneLabelColor == 0)
                col = ARGB(z.zoneAlpha, z.zoneRed, z.zoneGreen, z.zoneBlue);
            else
                col = z.ZoneLabelColor;
            ExpansionMarkerData mk = m_MarkerModule.CreateServerMarker(name, icon, pos, col, showInWorld);
            if (!mk)
                continue;
            if (z.EnableExpansion3DMarker && !z.OnlyAllowExpansion2DMarker)
                mk.RemoveVisibility(EXPANSION_MARKER_VIS_MAP);
            m_ZoneMarkers.Insert(z.GetName(), mk);
        }
        foreach (ZoneBase dz : m_DynamicZones)
        {
            if (!dz.OnlyAllowExpansion2DMarker && !dz.EnableExpansion3DMarker)
                continue;
            if (m_ZoneMarkers.Contains(dz.GetName()))
                continue;
            string nameD = dz.ExpansionMarkerName;
            if (nameD == "")
                nameD = dz.GetName();
            string iconD = dz.Expansion3DIcon;
            if (iconD == "")
                iconD = "Exclamation";
            pos = dz.center;
            if (dz.shape == ZoneShape.POLYGON && pos[0] == 0 && pos[1] == 0 && pos[2] == 0)
                pos = dz.GetPolygonCentroid();
            pos[0] = pos[0] + dz.ZonelabelOffsetX_Meters;
            pos[2] = pos[2] + dz.ZonelabelOffsetZ_Meters;
            showInWorld = dz.EnableExpansion3DMarker && !dz.OnlyAllowExpansion2DMarker;
            if (dz.ZoneLabelColor == 0)
                col = ARGB(dz.zoneAlpha, dz.zoneRed, dz.zoneGreen, dz.zoneBlue);
            else
                col = dz.ZoneLabelColor;
            ExpansionMarkerData mkD = m_MarkerModule.CreateServerMarker(nameD, iconD, pos, col, showInWorld);
            if (!mkD)
                continue;
            if (dz.EnableExpansion3DMarker && !dz.OnlyAllowExpansion2DMarker)
                mkD.RemoveVisibility(EXPANSION_MARKER_VIS_MAP);
            m_ZoneMarkers.Insert(dz.GetName(), mkD);
        }
    #endif
    }
    void ClearAllExpansionMarkers()
    {
        #ifdef EXPANSIONMODNAVIGATION
        if (m_ZoneMarkers && m_MarkerModule)
        {
            foreach (string zoneName, ExpansionMarkerData marker : m_ZoneMarkers)
            {
                m_MarkerModule.RemoveServerMarker(marker.GetUID());
            }
            m_ZoneMarkers.Clear();
            //NinjinsPvPPvE.LogDebug("Cleared alll Expansion 3D markers.");
        }
        #endif
    }
/*
--------------------------------------------------------------------------------
Zone Helpers
--------------------------------------------------------------------------------
*/
    ZoneBase GetPlayerZone(PlayerBase player)
    {
        if (!player || !player.GetIdentity()) 
            return null;
        string playerId = player.GetIdentity().GetId();
        if (m_PlayerCurrentActiveZone.Contains(playerId))
        {
            return m_PlayerCurrentActiveZone.Get(playerId);
        }
        return null;
    }
    bool IsZoneNameExists(string zoneName)
    {
        foreach (ZoneBase z : m_Zones)
        {
            if (z.GetName() == zoneName) 
                return true;
        }
        foreach (ZoneBase dz : m_DynamicZones)
        {
            if (dz.GetName() == zoneName) 
                return true;
        }
        return false;
    }
    bool ZoneHasPlayers(ZoneBase zone)
    {
        if (!zone) 
            return false;
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase pb = PlayerBase.Cast(man);
            if (!pb || !pb.IsAlive()) continue;
            if (zone.IsInside(pb.GetPosition()))
                return true;
        }
        return false;
    }
    bool IsPositionInZone(vector position, int zoneType)
    {
        if (CheckZones(m_Zones, position, zoneType))
        {
            return true;
        }
        if (CheckZones(m_DynamicZones, position, zoneType))
        {
            return true;
        }
        return false;
    }
    string GetLockpickingPlayerIDAtPosition(vector position)
    {
        foreach (ZoneBase z : m_DynamicZones)
        {
            if (z.GetName().Contains("Lockpick_") && z.IsInside(position))
            {
                return LockPickManager.GetLockpicker(z.GetName());
            }
        }
        return "";
    }
/*
--------------------------------------------------------------------------------
SendZonesToClient
Sends all zone data (both static + dynamic) to a client via RPC
--------------------------------------------------------------------------------
*/
    void SyncZonesWithClients()
    {
        if (!GetGame() || !GetGame().IsServer())
            return;
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man player : players)
        {
            PlayerBase pb = PlayerBase.Cast(player);
            if (!pb)
            {
                NinjinsPvPPvE.LogWarning("SyncZonesWithClients - PlayerBase cast failed.");
                continue;
            }
            PlayerIdentity identity = pb.GetIdentity();
            if (!identity)
            {
                NinjinsPvPPvE.LogWarning("SyncZonesWithClients - Player identity is null.");
                continue;
            }
            SendZonesToClient(identity);
        }
    }
    void SendZonesToClient(PlayerIdentity identity)
    {
        if (!identity) 
            return;
        PlayerBase player;
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase pb = PlayerBase.Cast(man);
            if (pb && pb.GetIdentity() && pb.GetIdentity().GetId() == identity.GetId())
            {
                player = pb;
                break;
            }
        }
        bool isAdmin = false;
        if (player)
        {
            isAdmin = player.IsAdmin();
        }
        bool showAll = isAdmin && g_MainConfig && g_MainConfig.AdminCanSeeAllInactiveZones;
        ref array<ref ZoneBase> allZones = new array<ref ZoneBase>();
        #ifdef SERVER
        foreach (ZoneBase z : m_Zones)
        {
            if (showAll || z.IsActive())
                allZones.Insert(z);
        }
        foreach (ZoneBase dz : m_DynamicZones)
        {
            if (showAll || dz.IsActive())
                allZones.Insert(dz);
        }
        #endif
        Param1<ref array<ref ZoneBase>> data = new Param1<ref array<ref ZoneBase>>(allZones);
        GetRPCManager().SendRPC("NinjinsPvPPvE", "ReceiveZones", data, true, identity);
    }
/*
--------------------------------------------------------------------------------
SaveZones + Remove + Register + Reload
--------------------------------------------------------------------------------
*/
    ZoneBase RegisterDynamicZone(ZoneBase newZone)
    {
        if (!newZone)
            return null;
        if (IsZoneNameExists(newZone.GetName()))
            return null;
        m_DynamicZones.Insert(newZone);
    #ifdef EXPANSIONMODNAVIGATION
        if ((newZone.OnlyAllowExpansion2DMarker || newZone.EnableExpansion3DMarker) && m_MarkerModule)
        {
            string name = newZone.ExpansionMarkerName;
            if (name == "")
                name = newZone.GetName();
            string icon = newZone.Expansion3DIcon;
            if (icon == "")
                icon = "Exclamation";
            int col;
            if (newZone.ZoneLabelColor == 0)
                col = ARGB(newZone.zoneAlpha, newZone.zoneRed, newZone.zoneGreen, newZone.zoneBlue);
            else
                col = newZone.ZoneLabelColor;
            bool showInWorld = newZone.EnableExpansion3DMarker && !newZone.OnlyAllowExpansion2DMarker;
            ExpansionMarkerData mk = m_MarkerModule.CreateServerMarker(name, icon, newZone.center, col, showInWorld);
            if (mk)
            {
                if (newZone.EnableExpansion3DMarker && !newZone.OnlyAllowExpansion2DMarker)
                    mk.RemoveVisibility(EXPANSION_MARKER_VIS_MAP);
                m_ZoneMarkers.Insert(newZone.GetName(), mk);
            }
        }
    #endif
        if (GetGame() && GetGame().IsServer())
            SyncZonesWithClients();
        return newZone;
    }
    void SaveZones()
    {
        ref NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
        if (!settings)
        {
            settings = new NinjinsZoneSettings();
            settings.DefaultSettings();
        }
        settings.Zones = m_Zones;
        settings.SaveSettings();
        NinjinsPvPPvE.LogDebug("ZoneManager::SaveZones - Saved static zones with dynamic defaults preserved.");
    }
    void ReloadZones()
    {
        m_Zones.Clear();
        #ifdef EXPANSIONMODNAVIGATION
        ClearAllExpansionMarkers();
        #endif
        InitializeZones();
        #ifdef EXPANSIONMODNAVIGATION
        CreateExpansionMarkers();
        #endif
        NinjinsPvPPvE.LogDebug("ZoneManager::ReloadZones - reloaded zones from config.");
        if (GetGame() && GetGame().IsServer())
            SyncZonesWithClients();
    }
    bool RemoveDynamicZone(string zoneName)
    {
        if (zoneName == "") 
            return false;
        foreach (ZoneBase z : m_DynamicZones)
        {
            if (z.GetName() != zoneName) 
                continue;
            // Skip player check for AI mission zones
            if (zoneName.IndexOf("AIMission_") == 0)
            {
                NinjinsPvPPvE.LogDebug("[ZoneManager] Force removing AI mission zone: " + zoneName);
            }
            else if (g_MainConfig && g_MainConfig.RemoveDynamicZoneOnlyifNoPlayerInside && ZoneHasPlayers(z))
            {
                int retrySec = 5;
                if (g_MainConfig.DynamicZoneRemovalRetrySeconds > 0)
                    retrySec = g_MainConfig.DynamicZoneRemovalRetrySeconds;
                int retryMs = retrySec * 1000;
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.TryRemoveDynamicZoneWhenEmpty, retryMs, false, zoneName);
                NinjinsPvPPvE.LogDebug("[ZoneManager] Delay removal of " + zoneName + " - players still inside.");
                return false;
            }
            #ifdef EXPANSIONMODNAVIGATION
            if (m_ZoneMarkers.Contains(zoneName))
            {
                ExpansionMarkerData marker = m_ZoneMarkers.Get(zoneName);
                if (marker && m_MarkerModule)
                    m_MarkerModule.RemoveServerMarker(marker.GetUID());
                m_ZoneMarkers.Remove(zoneName);
            }
            #endif
            m_DynamicZones.RemoveItem(z);
            if (GetGame() && GetGame().IsServer())
                SyncZonesWithClients();
            NinjinsPvPPvE.LogDebug("[ZoneManager] Removed dynamic zone: " + zoneName);
            return true;
        }
        return false;
    }
    void TryRemoveDynamicZoneWhenEmpty(string zoneName)
    {
        RemoveDynamicZone(zoneName);
    }
/*
--------------------------------------------------------------------------------
CheckZones
--------------------------------------------------------------------------------
*/
    private bool CheckZones(array<ref ZoneBase> zones, vector position, int zoneType)
    {
        foreach (ZoneBase z : zones)
        {
            if (z.type == zoneType && z.IsInside(position))
            {
                return true;
            }
        }
        return false;
    }
/*
--------------------------------------------------
Notification - Related Stuff
--------------------------------------------------
*/
    void BroadcastNotification(string title, string message, string iconPath, int color, float duration, vector position)
    {
        if (!g_MainConfig.EnableLockpickingNotification)
        {
            NinjinsPvPPvE.LogDebug("Lockpicking notifications are disabled in the config.");
            return;
        }
        float broadcastRadius = g_MainConfig.LockpickNotificationBroadcastRadius;
        array<Man> players    = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man player : players)
        {
            PlayerBase pb = PlayerBase.Cast(player);
            if (!pb || !pb.GetIdentity()) continue;
            float distance = vector.Distance(pb.GetPosition(), position);
            if (distance <= broadcastRadius)
            {
                NotificationSystem.Create(new StringLocaliser(title),new StringLocaliser(message),iconPath,color,duration,pb.GetIdentity());
                NinjinsPvPPvE.LogDebug("Sent notification to " + pb.GetIdentity().GetName() + " at distance " + distance + " m.");
            }
        }
    }
    void NotifyLockpickingDenied(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
            return;
        string title = "Lockpicking Denied";
        string message = "Lockpicking is only allowed in PvP Zones!";
        string iconPath = "NinjinsPvPPvE/gui/error.edds";
        int color = ARGB(255, 255, 0, 0);
        float duration = 5.0;
        NotificationSystem.Create(new StringLocaliser(title),new StringLocaliser(message),iconPath,color,duration,player.GetIdentity());
        NinjinsPvPPvE.LogDebug("[ZoneManager] Sent lockpicking denied notification to player: " + player.GetIdentity().GetName());
    }
    void NotifyRobberyDenied(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
            return;
        string title = "ATM Robbery Denied";
        string message = "ATM robberies are only allowed in PvP Zones!";
        string iconPath = "NinjinsPvPPvE/gui/error.edds";
        int color = ARGB(255, 255, 0, 0);
        float duration = 5.0;
        NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, player.GetIdentity());
        NinjinsPvPPvE.LogDebug("[ZoneManager] Sent ATM robbery denied notification to player: " + player.GetIdentity().GetName());
    }
}