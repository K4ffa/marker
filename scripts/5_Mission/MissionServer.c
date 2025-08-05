/*
================================================================================================
    =                               MODDED CLASS: MissionServer                                    =
    =  Provides server-side initialization and RPC for zone management, config reloading,           =
    =  territory flag zones, item rules, and admin control                                          =
    ================================================================================================
*/
modded class MissionServer
{
    ref PlayerZoneController m_PlayerZoneController;
    ref ZombieZoneController m_ZombieZoneController;
    ref AnimalZoneController m_AnimalZoneController;
    ref ItemZoneController m_ItemZoneController;
    ref Timer m_ZombieZoneTimer;
    #ifdef EXPANSIONMODAI
    ref AIZoneController m_AIZoneController;
    #endif
    ref NoVehicleZoneEnforcer m_NoVehicleZoneEnforcer;
    override void OnInit()
    {
        super.OnInit();
        if (MainConfig.NeedsLegacyFix())
        {
            Print("[NinjinsPvPPvE] Legacy configuration detected. Backing up existing config files.");
            BackupLegacyConfigs();
            if (MainConfig.ApplyLegacyFix())
            {
                Print("[NinjinsPvPPvE] Legacy MainConfig was fixed for new days system. Now loading updated config. A backup of your old config files has been created in the 'legacy backup' folder.");
            }
            else
            {
                Print("[NinjinsPvPPvE] WARNING: Detected legacy config, but failed to apply fixes. Loading may fail.");
            }
        }
        int preLogLevel = PreloadLoggingLevel();
        Print("[NinjinsPvPPvE] MainConfig is clean. Now loading.");
        InitMainConfig();
        NinjinsPvPPvE.SetLogLevel(g_MainConfig.LoggingLevel);
        if (NinjinsPvPPvE.GetLogLevel() > 0)
            NinjinsPvPPvE.InitLogFile();
        InitAdminConfig();
        InitItemRules();    
        // RPC registrationss
        GetRPCManager().AddRPC("NinjinsPvPPvE", "SyncMainConfig", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ReloadConfigResult", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ReloadConfig", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "SyncAdminConfig", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "SyncAllowedRaidingPlayers", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "UpdateServerConfigAll", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "AddZone", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "RemoveZone", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "SaveZone", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "TeleportPlayer", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ItemRuleActionRPC", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ScanItemsOnMap", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "RemoveRaidingPlayerServer", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "AddRaidingPlayerServer", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "RequestOnlinePlayers", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "RequestZones", this, SingleplayerExecutionType.Server);
        ZoneManager.GetInstance();
        m_PlayerZoneController = new PlayerZoneController();
        m_ZombieZoneController = new ZombieZoneController();
        m_AnimalZoneController = new AnimalZoneController();
        m_ItemZoneController = new ItemZoneController();
        StartItemZoneTimer();
        StartZombieZoneTimer();
        StartAnimalZoneTimer();
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateZones, 1000, true);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ZoneManager.GetInstance().CreateExpansionMarkers, 3000, false);
        #ifdef EXPANSIONMODAI
        if (!g_MainConfig || !g_MainConfig.DisableAiZoneScanning)
        {
            m_AIZoneController = new AIZoneController();
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateAIZones, 1000, true);
        }
        else
        {
            NinjinsPvPPvE.LogDebug("AI zone scanning is disabled by config. Skipping AIZoneController init.");
        }
        #endif
    }
    void BackupLegacyConfigs()
    {
        if (!FileExist(NinjinsPvPPvE_LEGACY_BACKUP_DIR))
        {
            Print("[NinjinsPvPPvE] Creating legacy backup directory: " + NinjinsPvPPvE_LEGACY_BACKUP_DIR);
            MakeDirectory(NinjinsPvPPvE_LEGACY_BACKUP_DIR);
        }
        string searchPattern = NinjinsPvPPvE_GENERAL_CONFIG_DIR + "*.json";
        string fileName;
        FileAttr fileAttr;
        FindFileHandle searchHandle = FindFile(searchPattern, fileName, fileAttr, 0);
        if (!searchHandle)
        {
            Print("[NinjinsPvPPvE] BackupLegacyConfigs: No config files found to back up or error accessing directory.");
            return;
        }
        int filesBackedUp = 0;
        if (searchHandle)
        {
            while (true)
            {
                if (!(fileAttr & FileAttr.DIRECTORY))
                {
                    string sourceFile = NinjinsPvPPvE_GENERAL_CONFIG_DIR + fileName;
                    string destFile = NinjinsPvPPvE_LEGACY_BACKUP_DIR + fileName;
                    if (CopyFile(sourceFile, destFile))
                    {
                        filesBackedUp++;
                    }
                    else
                    {
                        Print("[NinjinsPvPPvE] ERROR: Failed to copy " + sourceFile + " to " + destFile);
                    }
                }
                if (!FindNextFile(searchHandle, fileName, fileAttr))
                    break;
            }
            CloseFindFile(searchHandle);
        }
        if (filesBackedUp > 0)
        {
            Print("[NinjinsPvPPvE] Successfully backed up " + filesBackedUp + " config file(s) to " + NinjinsPvPPvE_LEGACY_BACKUP_DIR);
        }
        else
        {
            Print("[NinjinsPvPPvE] No files were backed up from the config directory.");
        }
    }
/*
--------------------------------------------------
OnMissionFinish - override
--------------------------------------------------
*/
    override void OnMissionFinish()
    {
        super.OnMissionFinish(); 
        if (ZoneManager.instance)
        {
            delete ZoneManager.instance;
            ZoneManager.instance = null;
        }
        if (m_ZombieZoneTimer)
            m_ZombieZoneTimer.Stop();
        NinjinsPvPPvE.CloseLogFile();
    }
/*
--------------------------------------------------
InvokeOnConnect - override
--------------------------------------------------
*/
    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);
        if (GetGame().IsServer() && identity)
        {
            string playerGuid = identity.GetId();
            string playerName = identity.GetName();
            for (int i = 0; i < g_MainConfig.AllowedRaidingPlayers.Count(); ++i)
            {
                string entry = g_MainConfig.AllowedRaidingPlayers[i];
                TStringArray parts = new TStringArray;
                entry.Split(":", parts);
                string entryGuid;
                string entryName;
                if (parts.Count() > 1)
                {
                    entryName = parts[0].Trim();
                    entryGuid = parts[1].Trim();
                }
                else
                {
                    entryGuid = parts[0].Trim();
                    entryName = parts[0].Trim();
                }
                if (entryGuid == playerGuid && entryName != playerName)
                {
                    g_MainConfig.AllowedRaidingPlayers[i] = playerName + ":" + playerGuid;
                    g_MainConfig.SaveConfig();
                    NinjinsPvPPvE.LogDebug("[InvokeOnConnect] Updated raider entry: " + playerName + ":" + playerGuid);
                    break;
                }
            }
            Param1<ref MainConfig> configParam = new Param1<ref MainConfig>(g_MainConfig);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "SyncMainConfig", configParam, true, identity);
            ZoneManager.GetInstance().SendZonesToClient(identity);
            Param2<int, bool> afkParams = new Param2<int, bool>(g_MainConfig.AFKKickTimeout, g_MainConfig.EnableAFKKick);
            GetGame().RPCSingleParam(player, NinjinCustomRPCs.RPC_SYNC_AFK_SETTINGS, afkParams, true, identity);
            if (m_AdminConfig && m_AdminConfig.IsAdmin(identity.GetId()))
            {
                player.SetAdminStatus(true);
                Param1<ref AdminConfig> adminParam = new Param1<ref AdminConfig>(m_AdminConfig);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "SyncAdminConfig", adminParam, true, identity);
            }
            if (g_ItemRules)
            {
                Param1<ref ItemRules> itemRulesParam = new Param1<ref ItemRules>(g_ItemRules);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "SyncItemRules", itemRulesParam, true, identity);
            }
            else
            {
                NinjinsPvPPvE.LogWarning("[MissionServer] g_ItemRules is null. Cannot sync ItemRules.");
            }
            if (m_PlayerZoneController)
            {
                m_PlayerZoneController.UpdatePlayer(player);
                m_PlayerZoneController.SendPlayerZoneStateToClient(player);
                if (g_MainConfig && g_MainConfig.AllowNoRelogOnServerCrash && player.netSync_IsInNoLogOutZone)
                {
                    player.TeleportToNoLogOutPos(identity);
                }
                NinjinsPvPPvE.LogInfo("Updated Single zone state for player: " + identity.GetName());
            }
            else
            {
                NinjinsPvPPvE.LogWarning("[ERROR] PlayerZoneController is not initialized.");
            }
        }
    }
/*
--------------------------------------------------
Initialization - Configs
--------------------------------------------------
*/
    void InitMainConfig()
    {
        g_MainConfig = MainConfig.LoadConfig();
        if (!g_MainConfig)
        {
            NinjinsPvPPvE.LogCritical("Failed to load MainConfig.");
        }
    }
    void InitAdminConfig()
    {
        m_AdminConfig = AdminConfig.LoadConfig();
        if (!m_AdminConfig)
        {
            NinjinsPvPPvE.LogDebug("[ERROR] Failed to load AdminConfig.");
        }
    }
    void InitItemRules()
    {
        g_ItemRules = ItemRules.LoadConfig(true);
        if (!g_ItemRules)
        {
            NinjinsPvPPvE.LogDebug("[ERROR] Failed to load ItemRules.");
        }
    }
    int PreloadLoggingLevel()
    {
        MainConfig tempConfig = new MainConfig();
        if (FileExist(NinjinsPvPPvE_MAIN_CONFIG_FILE)) 
        {
            JsonFileLoader<MainConfig>.JsonLoadFile(NinjinsPvPPvE_MAIN_CONFIG_FILE, tempConfig);
            return tempConfig.LoggingLevel;
        }
        return 1;
    }
/*
--------------------------------------------------
Admin Menu Stuff
--------------------------------------------------
*/
    void TeleportPlayer(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param3<float, float, float> posParam;
        if (!ctx.Read(posParam))
        {
            NinjinsPvPPvE.LogWarning("[MissionServer] TeleportPlayer: Failed to read x/y/z from RPC.");
            return;
        }
        if (!m_AdminConfig || !m_AdminConfig.IsAdmin(sender.GetId()))
        {
            NinjinsPvPPvE.LogWarning("[DENIED] Unauthorized teleport attempt by: " + sender.GetName() + " (" + sender.GetId() + ")");
            return;
        }
        vector pos = Vector(posParam.param1, posParam.param2, posParam.param3);
        PlayerBase player = PlayerBase.Cast(sender.GetPlayer());
        if (player)
        {
            vector oldPos = player.GetPosition();
            player.SaveLastPosition();
            player.TeleportTo(pos);
            //NinjinsPvPPvE.LogDebug("[MissionServer] Teleported " + sender.GetName() + " from " + oldPos.ToString() + " to " + pos.ToString());
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[MissionServer] TeleportPlayer: Player not found for identity: " + sender.GetName());
        }
    }
    void AddZone(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender) 
            return;
        if (!m_AdminConfig || !m_AdminConfig.IsAdmin(sender.GetId()))
        {
            NinjinsPvPPvE.LogDebug("[DENIED] Unauthorized attempt to add a zone by: " + sender.GetName());
            return;
        }
        vector zoneCenter = Vector(3000, 0, 3000); // fallback default
        Param3<float, float, float> posParam;
        if (ctx.Read(posParam))
        {
            zoneCenter = Vector(posParam.param1, posParam.param2, posParam.param3);
        }
        ZoneBase circleZone = new ZoneBase();
        circleZone.name = "Zone " + ZoneManager.GetInstance().m_Zones.Count().ToString();
        circleZone.type = ZONE_TYPE_PVP;
        circleZone.shape = ZoneShape.CIRCLE;
        circleZone.displayName = "Default Display Zone Text";
        circleZone.drawShape = true;
        circleZone.center = zoneCenter;
        circleZone.radius = 300.0;
        circleZone.priority = 10;
        circleZone.enableCustomMessages = true;
        circleZone.customTitle = "New Zone";
        circleZone.customMessageEnter = "You entered the New Zone!";
        circleZone.customMessageExit = "You exited the New Zone!";
        circleZone.customIcon = "NinjinsPvPPvE/gui/guns.edds";
        circleZone.notificationColor = ARGB(255, 0, 255, 0);
        circleZone.dayConfigs = new array<ref DayConfig>();
        circleZone.dayConfigs.Insert(new DayConfig("Monday", 0, 24));
        circleZone.dayConfigs.Insert(new DayConfig("Tuesday", 0, 24));
        circleZone.dayConfigs.Insert(new DayConfig("Wednesday", 0, 24));
        circleZone.dayConfigs.Insert(new DayConfig("Thursday", 0, 24));
        circleZone.dayConfigs.Insert(new DayConfig("Friday", 0, 24));
        circleZone.dayConfigs.Insert(new DayConfig("Saturday", 0, 24));
        circleZone.dayConfigs.Insert(new DayConfig("Sunday", 0, 24));
        circleZone.zoneAlpha = 255;
        circleZone.zoneRed = 255;
        circleZone.zoneGreen = 0;
        circleZone.zoneBlue = 0;
        circleZone.forceFirstPerson = false;
        circleZone.UsesDisallowedVehicles = false;
        circleZone.drawStrikeZone = false;
        circleZone.EnableExpansion3DMarker = false;
        circleZone.OnlyAllowExpansion2DMarker = false;
        circleZone.Hide = false;
        circleZone.ExpansionMarkerName = "DefaultZone";
        circleZone.Expansion3DIcon = "Ambush";
        circleZone.ZonelabelOffsetX_Meters = 0.0;
        circleZone.ZonelabelOffsetZ_Meters = 0.0;
        circleZone.ZoneLabelColor = -65536;
        circleZone.NoLogOutTeleportPos = Vector(0, 0, 0);
        circleZone.NoLogOut = false;
        circleZone.noBuildRadius = -1;
        circleZone.ignoreHeightCheck = false;
        circleZone.zoneMinHeight = 0.0;
        circleZone.zoneMaxHeight = 0.0;
        circleZone.HideWhenNested = false;
        circleZone.DrawNoBuildShape = true;
        ZoneManager.GetInstance().m_Zones.Insert(circleZone);
        ZoneManager.GetInstance().SaveZones();
        ReloadZonesOnServer();
        NinjinsPvPPvE.LogDebug("[MissionServer] New zone added at " + zoneCenter.ToString() + " by admin: " + sender.GetName());
    }
    void RemoveZone(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender) 
            return;
        if (!m_AdminConfig || !m_AdminConfig.IsAdmin(sender.GetId()))
        {
            NinjinsPvPPvE.LogDebug("[DENIED] Unauthorized attempt to remove a zone by: " + sender.GetName());
            return;
        }
        Param1<string> zoneNameParam;
        if (!ctx.Read(zoneNameParam)) 
            return;
        string zoneName = zoneNameParam.param1;
        ref array<ref ZoneBase> zones = ZoneManager.GetInstance().m_Zones;
        for (int i = 0; i < zones.Count(); i++)
        {
            if (zones[i].GetName() == zoneName)
            {
                zones.Remove(i);
                NinjinsPvPPvE.LogDebug("[MissionServer] Zone removed: " + zoneName);
                break;
            }
        }
        ZoneManager.GetInstance().SaveZones();
        ReloadZonesOnServer();
    }
    void SaveZone(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender) 
            return;
        if (!m_AdminConfig || !m_AdminConfig.IsAdmin(sender.GetId()))
        {
            NinjinsPvPPvE.LogDebug("[DENIED] Unauthorized attempt to update zone by: " + sender.GetName());
            return;
        }
        Param1<ref ZoneUpdateData> zoneParam;
        if (!ctx.Read(zoneParam))
        {
            NinjinsPvPPvE.LogDebug("[MissionServer] Failed to read zone parameter for SaveZone.");
            return;
        }
        ZoneUpdateData updateData = zoneParam.param1;
        if (!updateData)
        {
            NinjinsPvPPvE.LogDebug("[MissionServer] Received null zone update data.");
            return;
        }
        ZoneBase updatedZone = updateData.updatedZone;
        if (!updatedZone)
        {
            NinjinsPvPPvE.LogDebug("[MissionServer] Received null updatedZone.");
            return;
        }
        MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
        ref array<ref ZoneBase> zones;
        if (mission)
        {
            zones = mission.GetCachedZones();
        }
        if (!zones || zones.Count() == 0)
        {
            zones = ZoneManager.GetInstance().m_Zones;
        }
        bool found = false;
        for (int i = 0; i < zones.Count(); i++)
        {
            if (zones[i].GetName() == updateData.originalName)
            {
                zones[i].name                 = updatedZone.name;
                zones[i].displayName          = updatedZone.displayName;
                zones[i].type                 = updatedZone.type;
                zones[i].priority             = updatedZone.priority;
                zones[i].enableCustomMessages = updatedZone.enableCustomMessages;
                zones[i].customTitle          = updatedZone.customTitle;
                zones[i].customMessageEnter   = updatedZone.customMessageEnter;
                zones[i].customMessageExit    = updatedZone.customMessageExit;
                zones[i].customIcon           = updatedZone.customIcon;
                zones[i].notificationColor    = updatedZone.notificationColor;
                if (updatedZone.dayConfigs && updatedZone.dayConfigs.Count() > 0)
                {
                    zones[i].dayConfigs = new array<ref DayConfig>();
                    foreach (DayConfig config : updatedZone.dayConfigs)
                    {
                        zones[i].dayConfigs.Insert(new DayConfig(config.dayName, config.startHour, config.endHour));
                    }
                }
                zones[i].forceFirstPerson     = updatedZone.forceFirstPerson;
                zones[i].UsesDisallowedVehicles     = updatedZone.UsesDisallowedVehicles;
                zones[i].drawShape            = updatedZone.drawShape;
                zones[i].radius               = updatedZone.radius;
                zones[i].zoneAlpha            = updatedZone.zoneAlpha;
                zones[i].zoneRed              = updatedZone.zoneRed;
                zones[i].zoneGreen            = updatedZone.zoneGreen;
                zones[i].zoneBlue             = updatedZone.zoneBlue;
                zones[i].UsesDisallowedVehicles = updatedZone.UsesDisallowedVehicles;
                zones[i].shape                = updatedZone.shape;
                zones[i].center               = updatedZone.center;
                zones[i].drawStrikeZone       = updatedZone.drawStrikeZone;
                zones[i].EnableExpansion3DMarker = updatedZone.EnableExpansion3DMarker;
                zones[i].ExpansionMarkerName     = updatedZone.ExpansionMarkerName;
                zones[i].Expansion3DIcon         = updatedZone.Expansion3DIcon;
                zones[i].OnlyAllowExpansion2DMarker = updatedZone.OnlyAllowExpansion2DMarker;
                zones[i].ZonelabelOffsetX_Meters = updatedZone.ZonelabelOffsetX_Meters;
                zones[i].ZonelabelOffsetZ_Meters = updatedZone.ZonelabelOffsetZ_Meters;
                zones[i].Hide = updatedZone.Hide;
                zones[i].ZoneLabelColor = updatedZone.ZoneLabelColor;
                zones[i].NoLogOutTeleportPos = updatedZone.NoLogOutTeleportPos;
                zones[i].NoLogOut = updatedZone.NoLogOut;
                zones[i].noBuildRadius = updatedZone.noBuildRadius;
                zones[i].ignoreHeightCheck = updatedZone.ignoreHeightCheck;
                zones[i].zoneMinHeight = updatedZone.zoneMinHeight;
                zones[i].zoneMaxHeight = updatedZone.zoneMaxHeight;
                zones[i].HideWhenNested = updatedZone.HideWhenNested;
                zones[i].DrawNoBuildShape = updatedZone.DrawNoBuildShape;
                found = true;
                break;
            }
        }
        if (!found)
        {
            NinjinsPvPPvE.LogDebug("[MissionServer] SaveZone: No matching zone found for: " + updateData.originalName);
            return;
        }
        ZoneManager.GetInstance().SaveZones();
        ReloadZonesOnServer();
        NinjinsPvPPvE.LogDebug("[MissionServer] Zone updated: " + updatedZone.name);
    }
    void UpdateServerConfigAll(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender) 
            return;
        Param1<ref MainConfig> data;
        if (!ctx.Read(data)) 
            return;
        MainConfig newConfig = data.param1;
        if (!newConfig)
        {
            NinjinsPvPPvE.LogDebug("[MissionServer] Received null MainConfig from client. Aborting.");
            return;
        }
        if (!m_AdminConfig || !m_AdminConfig.IsAdmin(sender.GetId()))
        {
            NinjinsPvPPvE.LogDebug("[DENIED] Unauthorized attempt to update MainConfig by " + sender.GetName());
            return;
        }
        g_MainConfig = newConfig;
        NinjinsPvPPvE.LogDebug("[MissionServer] Received entire MainConfig from " + sender.GetName() + ". Saving...");
        SaveAndSyncMainConfig();
        InitItemRules();  
        NoVehicleZoneEnforcer enforcer = null;
        if (NoFlightZoneModule.g_NoFlightZoneModule && NoFlightZoneModule.g_NoFlightZoneModule.GetEnforcer())
        {
            enforcer = NoFlightZoneModule.g_NoFlightZoneModule.GetEnforcer();
            enforcer.UpdateMainConfigSettings();
            enforcer.UpdateItemRulesSettings();
            NinjinsPvPPvE.LogDebug("[MissionServer] NoVehicleZoneEnforcer settings updated with new config.");
        }
        Param2<bool, string> result = new Param2<bool, string>(true, "MainConfig");
        GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadConfigResult", result, true, sender);
    }
    void SaveAndSyncMainConfig()
    {
        if (!g_MainConfig)
        {
            NinjinsPvPPvE.LogDebug("[ERROR] Cannot save MainConfig, it is null.");
            return;
        }
        g_MainConfig.SaveConfig();
        if (FileExist(NinjinsPvPPvE_MAIN_CONFIG_FILE))
        {
            NinjinsPvPPvE.LogDebug("[MissionServer] MainConfig saved successfully to json.");
            SyncMainConfigWithClients();
        }
        else
        {
            NinjinsPvPPvE.LogDebug("[ERROR] Failed to save MainConfig to json.");
        }
    }
    void RequestOnlinePlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender) 
            return;
        array<string> playerList = new array<string>();
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.IsAlive()) continue;
            PlayerIdentity identity = player.GetIdentity();
            if (!identity) continue;
            string name = identity.GetName();
            string guid = identity.GetId();
            playerList.Insert(name + ":" + guid);
        }
        Param1<array<string>> result = new Param1<array<string>>(playerList);
        GetRPCManager().SendRPC("NinjinsPvPPvE", "ReceiveOnlinePlayers", result, true, sender);
    }
    void ScanItemsOnMap(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param1<string> param;
        if (!ctx.Read(param))
            return;
        string itemType = param.param1.Trim();
        map<string, vector> resultPositions = new map<string, vector>;
        array<EntityAI> entities = new array<EntityAI>;
        DayZPlayerUtils.SceneGetEntitiesInBox("0.0 -1200.0 0.0", "20000.0 1200.0 20000.0", entities);
        int foundCount = 0;
        for (int i = 0; i < entities.Count(); i++)
        {
            EntityAI ent = entities[i];
            if (!ent) continue;
            if (ent.GetType() == itemType)
            {
                vector pos = ent.GetPosition();
                resultPositions.Insert(itemType + "_" + i.ToString(), pos);
                foundCount++;
            }
        }
        //NinjinsPvPPvE.LogInfo("[MissionServer] Total exact-matching items found: " + foundCount);
        GetRPCManager().SendRPC("NinjinsPvPPvE", "HandleScanResults", new Param1<ref map<string, vector>>(resultPositions), true, sender);
    }
    void AddRaidingPlayerServer(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !g_MainConfig)
            return;
        Param1<string> data;
        if (!ctx.Read(data))
            return;
        string entry = data.param1;
        if (entry == "") 
            return;
        string newGuid;
        TStringArray parts = new TStringArray;
        entry.Split(":", parts);
        if (parts.Count() > 1)
            newGuid = parts[1].Trim();
        else
            newGuid = parts[0].Trim();
        foreach (string existing : g_MainConfig.AllowedRaidingPlayers)
        {
            TStringArray exParts = new TStringArray;
            existing.Split(":", exParts);
            string guidToCheck;
            if (exParts.Count() > 1)
                guidToCheck = exParts[1].Trim();
            else
                guidToCheck = exParts[0].Trim();
            if (guidToCheck == newGuid)
                return;
        }
        g_MainConfig.AllowedRaidingPlayers.Insert(entry);
        g_MainConfig.SaveConfig();
        Param1<array<string>> sync = new Param1<array<string>>(g_MainConfig.AllowedRaidingPlayers);
        GetRPCManager().SendRPC("NinjinsPvPPvE", "UpdateAllowedRaidingPlayers", sync, true);
    }
    void RemoveRaidingPlayerServer(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param1<string> data;
        if (!ctx.Read(data))
            return;
        string entryToRemove = data.param1;
        if (!g_MainConfig || g_MainConfig.AllowedRaidingPlayers.Count() == 0)
            return;
        for (int i = g_MainConfig.AllowedRaidingPlayers.Count() - 1; i >= 0; --i)
        {
            if (g_MainConfig.AllowedRaidingPlayers[i] == entryToRemove)
            {
                g_MainConfig.AllowedRaidingPlayers.RemoveOrdered(i);
                break;
            }
        }
        g_MainConfig.SaveConfig();
        Param1<array<string>> sync = new Param1<array<string>>(g_MainConfig.AllowedRaidingPlayers);
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man player : players)
        {
            PlayerIdentity id = PlayerBase.Cast(player).GetIdentity();
            if (id)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "UpdateAllowedRaidingPlayers", sync, true, id);
            }
        }
    }
    void ItemRuleActionRPC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender) 
            return;
        Param2<string, string> param;
        if (!ctx.Read(param)) 
            return;
        string action = param.param1;
        string value = param.param2;
        ItemRules rules = ItemRules.LoadConfig();
        bool modified = false;
        switch (action)
        {
            case "AddNBItemWhiteList":
                if (rules.NBItemWhiteList.Find(value) == -1)
                {
                    rules.NBItemWhiteList.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveNBItemWhiteList":
                int idxNB = rules.NBItemWhiteList.Find(value);
                if (idxNB >= 0)
                {
                    rules.NBItemWhiteList.Remove(idxNB);
                    modified = true;
                }
                break;
            case "AddAllowedAmmoPaintballState":
                if (rules.AllowedAmmoInPaintBallState.Find(value) == -1)
                {
                    rules.AllowedAmmoInPaintBallState.Insert(value);
                    modified = true;
                }
            break;
            case "RemoveAllowedAmmoPaintballState":
                int idxPaintballAmmo = rules.AllowedAmmoInPaintBallState.Find(value);
                if (idxPaintballAmmo >= 0)
                {
                    rules.AllowedAmmoInPaintBallState.Remove(idxPaintballAmmo);
                    modified = true;
                }
                break;
            case "AddSZItemWhiteList":
                if (rules.SZItemWhiteList.Find(value) == -1)
                {
                    rules.SZItemWhiteList.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveSZItemWhiteList":
                int idxSZ = rules.SZItemWhiteList.Find(value);
                if (idxSZ >= 0)
                {
                    rules.SZItemWhiteList.Remove(idxSZ);
                    modified = true;
                }
                break;
            case "AddCantBeDamagedInPvE":
                if (rules.CantBeDamagedInPvE.Find(value) == -1)
                {
                    rules.CantBeDamagedInPvE.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveCantBeDamagedInPvE":
                int idxPvEItem = rules.CantBeDamagedInPvE.Find(value);
                if (idxPvEItem >= 0)
                {
                    rules.CantBeDamagedInPvE.Remove(idxPvEItem);
                    modified = true;
                }
                break;
            case "AddCantBeDamagedInPvP":
                if (rules.CantBeDamagedInPvP.Find(value) == -1)
                {
                    rules.CantBeDamagedInPvP.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveCantBeDamagedInPvP":
                int idxPvPItem = rules.CantBeDamagedInPvP.Find(value);
                if (idxPvPItem >= 0)
                {
                    rules.CantBeDamagedInPvP.Remove(idxPvPItem);
                    modified = true;
                }
                break;
            case "AddAllowedAmmoPvEState":
            if (rules.AllowedAmmoInPvEState.Find(value) == -1)
            {
                rules.AllowedAmmoInPvEState.Insert(value);
                modified = true;
            }
                break;
            case "RemoveAllowedAmmoPvEState":
            int idxAmmo = rules.AllowedAmmoInPvEState.Find(value);
            if (idxAmmo >= 0)
            {
                rules.AllowedAmmoInPvEState.Remove(idxAmmo);
                modified = true;
            }
                break;
            case "AddExplosive":
                if (rules.PvEBlockedExplosivesDamage.Find(value) == -1)
                {
                    rules.PvEBlockedExplosivesDamage.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveExplosive":
                int idxExplosive = rules.PvEBlockedExplosivesDamage.Find(value);
                if (idxExplosive >= 0)
                {
                    rules.PvEBlockedExplosivesDamage.Remove(idxExplosive);
                    modified = true;
                }
                break;
            case "AddVehicle":
                if (rules.DisallowedVehicles.Find(value) == -1)
                {
                    rules.DisallowedVehicles.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveVehicle":
                int idxVehicle = rules.DisallowedVehicles.Find(value);
                if (idxVehicle >= 0)
                {
                    rules.DisallowedVehicles.Remove(idxVehicle);
                    modified = true;
                }
                break;
            case "AddGrenade":
                if (rules.BypassZoneChecksGrenades.Find(value) == -1)
                {
                    rules.BypassZoneChecksGrenades.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveGrenade":
                int idxGrenade = rules.BypassZoneChecksGrenades.Find(value);
                if (idxGrenade >= 0)
                {
                    rules.BypassZoneChecksGrenades.Remove(idxGrenade);
                    modified = true;
                }
                break;
            case "AddCantBeDamagedOnGround":
                if (rules.CantBeDamagedOnGround.Find(value) == -1)
                {
                    rules.CantBeDamagedOnGround.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveCantBeDamagedOnGround":
                int idxCBDOG = rules.CantBeDamagedOnGround.Find(value);
                if (idxCBDOG >= 0)
                {
                    rules.CantBeDamagedOnGround.Remove(idxCBDOG);
                    modified = true;
                }
                break;
            case "AddAnimalPvE":
                #ifdef NinjinsPvPPvE_Animal
                if (rules.CantBeDamagedAnimalsinPvE.Find(value) == -1)
                {
                    rules.CantBeDamagedAnimalsinPvE.Insert(value);
                    modified = true;
                }
                #endif
                break;
            case "RemoveAnimalPvE":
                #ifdef NinjinsPvPPvE_Animal
                int idxAnimal = rules.CantBeDamagedAnimalsinPvE.Find(value);
                if (idxAnimal >= 0)
                {
                    rules.CantBeDamagedAnimalsinPvE.Remove(idxAnimal);
                    modified = true;
                }
                #endif
                break;
            case "AddItemPvEDeploy":
                if (rules.BlockDeployIfPlayerInPvEState.Find(value) == -1)
                {
                    rules.BlockDeployIfPlayerInPvEState.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveItemPvEDeploy":
                int idxPvEDeploy = rules.BlockDeployIfPlayerInPvEState.Find(value);
                if (idxPvEDeploy >= 0)
                {
                    rules.BlockDeployIfPlayerInPvEState.Remove(idxPvEDeploy);
                    modified = true;
                }
                break;
            case "AddItemPvPDeploy":
                if (rules.BlockDeployIfPlayerInPvPState.Find(value) == -1)
                {
                    rules.BlockDeployIfPlayerInPvPState.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveItemPvPDeploy":
                int idxPvPDeploy = rules.BlockDeployIfPlayerInPvPState.Find(value);
                if (idxPvPDeploy >= 0)
                {
                    rules.BlockDeployIfPlayerInPvPState.Remove(idxPvPDeploy);
                    modified = true;
                }
                break;
            case "AddItemRaidDeploy":
                if (rules.BlockDeployIfPlayerInRaidState.Find(value) == -1)
                {
                    rules.BlockDeployIfPlayerInRaidState.Insert(value);
                    modified = true;
                }
                break;
            case "RemoveItemRaidDeploy":
                int idxRaidDeploy = rules.BlockDeployIfPlayerInRaidState.Find(value);
                if (idxRaidDeploy >= 0)
                {
                    rules.BlockDeployIfPlayerInRaidState.Remove(idxRaidDeploy);
                    modified = true;
                }
                break;
            default:
                NinjinsPvPPvE.LogWarning("Unknown item rule action: " + action);
                return;
        }
        if (modified)
        {
            rules.SaveConfig();
            Param1<ref ItemRules> itemRulesParam = new Param1<ref ItemRules>(rules);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", itemRulesParam, true);
        }
    }
    void SyncItemRulesToClient(PlayerIdentity sender)
    {
        if (g_ItemRules)
        {
            Param1<ref ItemRules> param = new Param1<ref ItemRules>(g_ItemRules);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "SyncItemRules", param, true, sender);
            NinjinsPvPPvE.LogDebug("ItemRules synchronized with client: " + sender.GetName());
        }
        else
        {
            NinjinsPvPPvE.LogWarning("g_ItemRules is null on the server. Cannot synchronize.");
        }
    }
/*
--------------------------------------------------
Reloading & Request Stuff
--------------------------------------------------
*/
    void ReloadConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param1<string> p;
        if (!ctx.Read(p))
            return;
        string section = p.param1;
        Param2<bool, string> rpcResult;
        if (!m_AdminConfig || !m_AdminConfig.IsAdmin(sender.GetId()))
        {
            rpcResult = new Param2<bool, string>(false, section);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadConfigResult", rpcResult, true, sender);
            NinjinsPvPPvE.LogWarning("[DENIED] ReloadConfig(" + section + ") by " + sender.GetName());
            return;
        }
        bool ok = true;
        array<Man> players = new array<Man>();
        int i;
        PlayerBase pb;
        PlayerIdentity id;
        Param1<ref MainConfig> cfg;
        Param1<ref ItemRules> rulesP;
        ItemRules newRules;
        NoVehicleZoneEnforcer enforcer = null;
        if (section == "MainConfig")
        {
            g_MainConfig = MainConfig.LoadConfig();
            if (g_MainConfig)
            {
                StartZombieZoneTimer();
                StartAnimalZoneTimer();
                StartItemZoneTimer();
                if (g_MainConfig.KillZombiesInSafeZone)
                NinjinsPvPPvE.LogDebug("Zombie SZ cleanup enabled.");
                else
                    NinjinsPvPPvE.LogDebug("Zombie SZ cleanup disabled.");
                if (g_MainConfig.KillAnimalsInSafeZone)
                    NinjinsPvPPvE.LogDebug("Animal SZ cleanup enabled.");
                else
                    NinjinsPvPPvE.LogDebug("Animal SZ cleanup disabled.");
                if (NoFlightZoneModule.g_NoFlightZoneModule && NoFlightZoneModule.g_NoFlightZoneModule.GetEnforcer())
                {
                    enforcer = NoFlightZoneModule.g_NoFlightZoneModule.GetEnforcer();
                    enforcer.UpdateMainConfigSettings();
                    NinjinsPvPPvE.LogDebug("[ReloadConfig] NoVehicleZoneEnforcer settings updated with new config.");
                }
                cfg = new Param1<ref MainConfig>(g_MainConfig);
                GetGame().GetPlayers(players);
                for (i = 0; i < players.Count(); ++i)
                {
                    pb = PlayerBase.Cast(players[i]);
                    if (!pb) continue;
                    id = pb.GetIdentity();
                    if (!id) continue;
                    GetRPCManager().SendRPC("NinjinsPvPPvE", "SyncMainConfig", cfg, true, id);
                }
            }
            else
            {
                ok = false;
            }
        }
        else if (section == "AdminConfig")
        {
            m_AdminConfig = AdminConfig.LoadConfig();
            if (!m_AdminConfig)
                ok = false;
        }
        else if (section == "Zones")
        {
            ZoneManager.GetInstance().ReloadZones();
            if (m_PlayerZoneController)
                m_PlayerZoneController.ReloadZones();
            GetGame().GetPlayers(players);
            for (i = 0; i < players.Count(); ++i)
            {
                pb = PlayerBase.Cast(players[i]);
                if (!pb) continue;
                id = pb.GetIdentity();
                if (!id) continue;
                ZoneManager.GetInstance().SendZonesToClient(id);
            }
        }
        else if (section == "ItemRules")
        {
            newRules = ItemRules.LoadConfig(true);
            if (newRules)
            {
                g_ItemRules = newRules;
                if (NoFlightZoneModule.g_NoFlightZoneModule && NoFlightZoneModule.g_NoFlightZoneModule.GetEnforcer())
                {
                    enforcer = NoFlightZoneModule.g_NoFlightZoneModule.GetEnforcer();
                    enforcer.UpdateItemRulesSettings();
                    NinjinsPvPPvE.LogDebug("[ReloadConfig] NoVehicleZoneEnforcer item rules updated.");
                }
                rulesP = new Param1<ref ItemRules>(g_ItemRules);
                GetGame().GetPlayers(players);
                for (i = 0; i < players.Count(); ++i)
                {
                    pb = PlayerBase.Cast(players[i]);
                    if (!pb) continue;
                    id = pb.GetIdentity();
                    if (!id) continue;
                    GetRPCManager().SendRPC("NinjinsPvPPvE", "SyncItemRules", rulesP, true, id);
                }
            }
            else
            {
                ok = false;
            }
        }
        else
        {
            ok = false;
            NinjinsPvPPvE.LogWarning("ReloadConfig: unknown section `" + section + "`");
        }
        rpcResult = new Param2<bool, string>(ok, section);
        GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadConfigResult", rpcResult, true, sender);
        if (ok)
            NinjinsPvPPvE.LogDebug("ReloadConfig(" + section + ") by " + sender.GetName());
    }
    void ReloadItemRulesMenu(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        string senderGUID = sender.GetId();
        if (!m_AdminConfig || !m_AdminConfig.IsAdmin(senderGUID))
            return;
        ref ItemRules newRules = ItemRules.LoadConfig(true);
        if (!newRules)
            return;
        g_ItemRules = newRules;
        NoVehicleZoneEnforcer enforcer = null;
        if (NoFlightZoneModule.g_NoFlightZoneModule && NoFlightZoneModule.g_NoFlightZoneModule.GetEnforcer())
        {
            enforcer = NoFlightZoneModule.g_NoFlightZoneModule.GetEnforcer();
            enforcer.UpdateItemRulesSettings();
            NinjinsPvPPvE.LogDebug("[ReloadItemRulesMenu] NoVehicleZoneEnforcer item rules updated.");
        }
        Param1<ref ItemRules> itemRulesParam = new Param1<ref ItemRules>(g_ItemRules);
        array<Man> players();
        GetGame().GetPlayers(players);
        foreach (Man player : players)
        {
            PlayerIdentity id = PlayerBase.Cast(player).GetIdentity();
            if (id)
                GetRPCManager().SendRPC("NinjinsPvPPvE", "SyncItemRules", itemRulesParam, true, id);
        }
    }
    void ReloadZonesOnServer()
    {
        ZoneManager.GetInstance().ReloadZones();
        if (m_PlayerZoneController)
        {
            m_PlayerZoneController.ReloadZones();
        }
        SyncZonesWithClients();
        NinjinsPvPPvE.LogDebug("Zones reloaded and updated successfully.");
    }
    void RequestZones(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server || !sender) 
            return;
        ZoneManager.GetInstance().SendZonesToClient(sender);
    }
/*
--------------------------------------------------
Synconisation
--------------------------------------------------
*/
    void SyncZonesWithClients()
    {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man player : players)
        {
            PlayerIdentity identity = PlayerBase.Cast(player).GetIdentity();
            if (identity)
            {
                ZoneManager.GetInstance().SendZonesToClient(identity);
                NinjinsPvPPvE.LogDebug("Zones synced with client: " + identity.GetName());
            }
        }
    }
    void SyncMainConfigWithClients()
    {
        if (!g_MainConfig)
        {
            NinjinsPvPPvE.LogDebug("[ERROR] Cannot sync MainConfig, it is null.");
            return;
        }
        Param1<ref MainConfig> configParam = new Param1<ref MainConfig>(g_MainConfig);
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man player : players)
        {
            PlayerIdentity identity = PlayerBase.Cast(player).GetIdentity();
            if (identity)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "SyncMainConfig", configParam, true, identity);
                Param2<int, bool> afkParams = new Param2<int, bool>(g_MainConfig.AFKKickTimeout, g_MainConfig.EnableAFKKick);
                GetGame().RPCSingleParam(player, NinjinCustomRPCs.RPC_SYNC_AFK_SETTINGS, afkParams, true, identity);
                NinjinsPvPPvE.LogDebug("MainConfig settings synced with client: " + identity.GetName());
            }
        }
    }
/*
-------------------------------------------------------------------------------------------
UpdateZones
Called periodically to update PlayerZoneController & AI COntroller
-------------------------------------------------------------------------------------------
*/
    void UpdateZones()
    {
        if (m_PlayerZoneController)
        {
            m_PlayerZoneController.Update(1.0);
        }
    }
    void UpdateZombieZones()
    {
        if (!g_MainConfig || !g_MainConfig.KillZombiesInSafeZone)
            return;
        if (m_ZombieZoneController)
        {
            m_ZombieZoneController.Update(1.0);
        }
    }
    void UpdateAnimalZones()
    {
        if (!g_MainConfig || !g_MainConfig.KillAnimalsInSafeZone)
            return;
        if (m_AnimalZoneController)
            m_AnimalZoneController.Update(1.0);
    }
    void UpdateItemZones()
    {
        if (!g_MainConfig || !g_MainConfig.DeleteItemsInSafeZone)
            return;
        if (m_ItemZoneController)
            m_ItemZoneController.Update(1.0);
    }
    void StartZombieZoneTimer()
    {
        float interval = 5.0;
        if (g_MainConfig && g_MainConfig.ZombieandAnimalSZKillScanInterval > 0)
            interval = g_MainConfig.ZombieandAnimalSZKillScanInterval;
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(UpdateZombieZones);
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateZombieZones, interval * 1000, true);
        NinjinsPvPPvE.LogDebug("Started ZombieZoneTimer with interval: " + interval + "s using CallLater.");
    }
    void StartAnimalZoneTimer()
    {
        float interval = 5.0;
        if (g_MainConfig && g_MainConfig.ZombieandAnimalSZKillScanInterval > 0)
            interval = g_MainConfig.ZombieandAnimalSZKillScanInterval;
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(UpdateAnimalZones);
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateAnimalZones, interval * 1000, true);
        NinjinsPvPPvE.LogDebug("Started AnimalZoneTimer with interval: " + interval + "s using CallLater.");
    }
    void StartItemZoneTimer()
    {
        float interval = 5.0;
        if (g_MainConfig && g_MainConfig.SZItemCleanUpInterval  > 0)
            interval = g_MainConfig.SZItemCleanUpInterval;
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(UpdateItemZones);
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateItemZones, interval * 1000, true);
        NinjinsPvPPvE.LogDebug("Started ItemZoneTimer with interval: " + interval + "s using CallLater.");
    }
    #ifdef EXPANSIONMODAI
    void UpdateAIZones()
    {
        if (g_MainConfig && g_MainConfig.DisableAiZoneScanning)
            return;
        if (m_AIZoneController)
            m_AIZoneController.Update(1.0);
    }
    #endif
}