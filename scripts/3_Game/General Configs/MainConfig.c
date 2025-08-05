/*
---------------------------------------------------------------------
Mainconfig
---------------------------------------------------------------------
*/
ref MainConfig g_MainConfig;
class MainConfig
{
    int  StartingDayOfTheWeek;
    bool AdminCanSeeAllInactiveZones;
    bool EnablePvPEverywhere;
    bool EnablePvEEverywhere;  
    ref array<ref DayConfig> GlobalPvPZoneDays;  
    ref array<ref DayConfig> GlobalPvEZoneDays;
    float StrikeLineSpacingMeters;
    float StrikeLineTransparency;
    bool DisableAiZoneScanning;
    bool EVRStormSZNoShock;
    bool AllowNoRelogOnServerCrash;
    bool ThirdPersonOnlyDriver;
    int NoVehicleZoneExitBlockDelayMS;
    bool EnableReflectDamage;
    bool DisableRaidingDialogActionOnFlagPole;
    bool AllowAnyPlayerInRaidZone;
    bool DisableArmExplosivePvE;
    bool DisableFallDamage;
    bool DisableFallDamageSZ;
    bool DisableFallDamagePvE;
    float PvPExitCountdown;
    float RaidExitCountdown;
    float PvEExitCountdown;
    bool DisableActionBlockForAdmins;
    float SafeZoneExitCountdown;
    bool KillZombiesInSafeZone;
    bool KillAnimalsInSafeZone;
    bool DeleteItemsInSafeZone;
    float SZItemCleanUpInterval;
    bool EnableItemSpawnZoneCreation;
    bool AllowSameZoneTypeEnterNotifications;
    int BlockItemDamageStateorZones;
    #ifdef NinjinsPvPPvE_Vehicles
    float VehicleZoneCheckInterval;
    #endif
    bool EnableKOTHZoneCreation;
    bool EnableTKKOTHZoneCreation;
    float ZombieandAnimalSZKillScanInterval;
    bool PvPtoPvEBlockedNotification;
    bool DrawNamesOnZones;
    bool LB_AdminMapZones;
    int  LB_DrawMiniMapZones;
    int LB_MiniMapDrawNames;
    bool DrawZonesOnCOT;
    bool DrawCOTAdminZoneLabels;
    bool DrawZonesOnVPPAdmin;
    bool DrawVPPAdminZoneLabels;
    bool EnableAFKKick;
    int AFKKickTimeout;
    bool EnableCfToolsLogs;
    int CircleDrawingWidth;
    bool drawStrikeLinesForNB;
    bool DrawNoBuildRadius;
    int noBuildZoneColor;
    bool DisableToxicExposureInPvE;
    bool EnableContaminatedZoneCreation;
    bool EnableMi8ZoneCreation;
    bool EnableUH1YZoneCreation;
    bool EnableAirdropZoneCreation;
    bool EnableAIMissionZoneCreation;
    bool AllowRestrainTargetinPvE;
    bool AllowRestrainTargetinPvP;
    bool AllowRestrainTargetinRaid;
    bool DisableGiveBloodTargetPvE;
    bool DisableForceFeedPvE;
    bool DisableForceDrinkPvE;
    bool ForceFirstPersonGlobalPvP;
    bool ForceFirstPersonGlobalPvE;
    bool BlockChemGasGrenadeOutsidePvP;
    float NoVehicleZoneKillOrDestroyDelay;
    int NoVehicleKillPlayerOrDestroyVehicle;
    ref array<string> DestroyVehicleParts;
    ref array<string> RemoveVehicleAttachments;
    ref array<string> DestroyVehicleCargo;
    string NoVehicleWarningText;
    string NoVehicleWarningEffect;
    float NoVehicleWarningEffectIntensity;
    string PvEImagePath;
    string PvPImagePath;
    string RaidImagePath;
    string SafeZoneImagePath;
    float IconPositionX;
    float IconPositionY;
    float IconWidth;
    float IconHeight;
    int PvPIconColor;
    int PvEIconColor;
    int RaidIconColor;
    int SafeZoneIconColor;
    bool RemoveDynamicZoneOnlyifNoPlayerInside;
    int DynamicZoneRemovalRetrySeconds;
    bool ExitZoneNotification;
    string ExitNotificationText;
    float ExitNotificationPanelPositionX;
    float ExitNotificationPanelPositionY;
    float NotificationPanelWidth;
    float NotificationPanelHeight;
    int LoggingLevel;
    int ExpansionReputationPenealtyPveEsPvE;
    bool EnableExpansionReputationPenaltyPvEvsPvE;
    ref array<string> AllowedRaidingPlayers;
    bool OnlyAllowLockPickInPvP;
    bool EnableLockpickingZoneCreation;
    float LockPickZoneDeletionTime;
    float LockpickingZoneRadius;
    bool EnableLockpickingNotification;
    float LockpickNotificationBroadcastRadius;
    string LockpickNotificationIconPath;
    string LockpickNotificationTitle;
    string LockpickNotificationMessage;
    int LockpickNotificationColor;
    bool LB_ATMRobberyOnlyInPvP;
    bool LB_ATMRobberyEnableZoneCreation;
    int ExpansionGroupsFriendlyFireDisabled;
    bool AiToPlayerDamageEverywhere;
    bool PlayerToAiDamageEverywhere;
    bool OnlyAllowAIToDoDamageIfPlayerIsPvP;
    bool OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatus;
    bool OnlyAllowAIToDoDamageIfPlayerIsPvE;
    bool OnlyAllowDamageToAIIfPlayerHasPvEStatus;
    bool OnlyAllowAIToDamageInRaidMode;
    bool OnlyAllowPlayersToDamageAIInRaidMode;
    bool EnableTerritoryFlagZones;
    int  TerritoryFlagZoneCreateMode;
    float TerritoryFlagPvPZoneCheckInterval;
    string MessageCannotDeployInSafeZone;
    string NoBuildMessage;
    string MessageBlockedItemDeployInPvE;
    string MessageBlockedItemDeployInPvP;
    string MessageBlockedItemDeployInRaid;
    string MessageItemRulesNotInitialized;
    ref array<ref MapLegendEntry> mapLegend;
    string mapLegendTitle;
/*
---------------------------------------------------------------------
MainConfig - Initializes default configuration values
---------------------------------------------------------------------
*/
    void MainConfig()
    {
        mapLegendTitle = "Zone Legend";
        DestroyVehicleParts = new array<string>;
        RemoveVehicleAttachments = new array<string>;
        DestroyVehicleCargo = new array<string>;
        DestroyVehicleParts.Insert("Engine");
        RemoveVehicleAttachments.Insert("CarBattery");    
        RemoveVehicleAttachments.Insert("SparkPlug");
        mapLegend = new array<ref MapLegendEntry>;
        MapLegendEntry safezone = new MapLegendEntry();
        safezone.name = "Safezone";
        safezone.ColorAlpha = 255;
        safezone.ColorRed = 255;
        safezone.ColorGreen = 255;
        safezone.ColorBlue = 255;
        MapLegendEntry blackmarket = new MapLegendEntry();
        blackmarket.name = "Blackmarket";
        blackmarket.ColorAlpha = 255;
        blackmarket.ColorRed = 255;
        blackmarket.ColorGreen = 255;
        blackmarket.ColorBlue = 255;
        mapLegend.Insert(safezone);
        mapLegend.Insert(blackmarket);
        #ifdef NinjinsPvPPvE_Vehicles
        VehicleZoneCheckInterval                         = 5.0;
        #endif
        StartingDayOfTheWeek                             = false;
        DrawNamesOnZones                                 = true;
        DisableActionBlockForAdmins                      = false;
        LB_AdminMapZones                                 = true;
        LB_DrawMiniMapZones                              = false; 
        LB_MiniMapDrawNames                              = false;
        DrawVPPAdminZoneLabels                           = true;
        DrawZonesOnVPPAdmin                              = true;
        StrikeLineSpacingMeters                          = 20.0;
        NoVehicleZoneExitBlockDelayMS                    = 1000;
        DrawCOTAdminZoneLabels                           = true;
        DrawZonesOnCOT                                   = true;
        DisableAiZoneScanning                            = true;
        EVRStormSZNoShock                                = true;
        KillZombiesInSafeZone                            = false;
        KillAnimalsInSafeZone                            = false;
        DeleteItemsInSafeZone                            = false;
        SZItemCleanUpInterval                            = 900.0;
        ZombieandAnimalSZKillScanInterval                = 5.0;
        DisableFallDamage                                = false;
        DisableFallDamageSZ                              = false;
        DisableFallDamagePvE                             = false;
        DisableArmExplosivePvE                           = false;
        DisableRaidingDialogActionOnFlagPole             = true;
        AllowAnyPlayerInRaidZone                         = false;
        PvPtoPvEBlockedNotification                      = true;
        CircleDrawingWidth                               = 2;
        drawStrikeLinesForNB                             = false;
        DrawNoBuildRadius                                = true;
        noBuildZoneColor                                 = -16711936;
        EnableCfToolsLogs                                = false;
        EnableItemSpawnZoneCreation                      = false;
        ExpansionReputationPenealtyPveEsPvE              = 0;
        EnableExpansionReputationPenaltyPvEvsPvE         = false;
        #ifdef mz_koth
        EnableKOTHZoneCreation                           = false;
        #endif
        #ifdef RizenKOTH
        EnableTKKOTHZoneCreation                         = false;
        #endif
        EnableAIMissionZoneCreation                      = true;
        AllowSameZoneTypeEnterNotifications              = false;
        BlockItemDamageStateorZones                      = 0;
        AllowRestrainTargetinPvE                         = true;
        AllowRestrainTargetinPvP                         = true;
        AllowRestrainTargetinRaid                        = true;
        DisableGiveBloodTargetPvE                        = false;
        DisableForceFeedPvE                              = false;
        DisableForceDrinkPvE                             = false;
        DisableToxicExposureInPvE                        = true;
        EnableContaminatedZoneCreation                   = true;
        EnableMi8ZoneCreation                            = true;
        EnableUH1YZoneCreation                           = true;
        EnableAirdropZoneCreation                        = true;
        EnableReflectDamage                              = true;
        PvPExitCountdown                                 = 10.0;
        RaidExitCountdown = 10.0;
        SafeZoneExitCountdown = 10.0;
        PvEExitCountdown = 10.0;
        AdminCanSeeAllInactiveZones = false;
        EnablePvPEverywhere = false;       
        GlobalPvPZoneDays = new array<ref DayConfig>();
        GlobalPvPZoneDays.Insert(new DayConfig("Monday", 0, 24));
        GlobalPvPZoneDays.Insert(new DayConfig("Tuesday", 0, 24));
        GlobalPvPZoneDays.Insert(new DayConfig("Wednesday", 0, 24));
        GlobalPvPZoneDays.Insert(new DayConfig("Thursday", 0, 24));
        GlobalPvPZoneDays.Insert(new DayConfig("Friday", 0, 24));
        GlobalPvPZoneDays.Insert(new DayConfig("Saturday", 0, 24));
        GlobalPvPZoneDays.Insert(new DayConfig("Sunday", 0, 24));
        GlobalPvEZoneDays = new array<ref DayConfig>();
        GlobalPvEZoneDays.Insert(new DayConfig("Monday", 0, 24));
        GlobalPvEZoneDays.Insert(new DayConfig("Tuesday", 0, 24));
        GlobalPvEZoneDays.Insert(new DayConfig("Wednesday", 0, 24));
        GlobalPvEZoneDays.Insert(new DayConfig("Thursday", 0, 24));
        GlobalPvEZoneDays.Insert(new DayConfig("Friday", 0, 24));
        GlobalPvEZoneDays.Insert(new DayConfig("Saturday", 0, 24));
        GlobalPvEZoneDays.Insert(new DayConfig("Sunday", 0, 24));       
        EnablePvEEverywhere = true;
        ThirdPersonOnlyDriver                            = true;
        AllowNoRelogOnServerCrash                        = false;
        ForceFirstPersonGlobalPvP                        = true;
        ForceFirstPersonGlobalPvE                        = false;
        BlockChemGasGrenadeOutsidePvP                    = true;
        EnableAFKKick                                    = true;
        AFKKickTimeout                                   = 600;
        NoVehicleKillPlayerOrDestroyVehicle              = NFZA_KILL;
        NoVehicleZoneKillOrDestroyDelay                  = 15.0;
        NoVehicleWarningEffect                           = "blur";
        NoVehicleWarningEffectIntensity                  = 0.5;
        NoVehicleWarningText                             = "Warning: Half time over, exit the Zone with Vehicle in {countdown} seconds!";
        PvEImagePath                                     = "NinjinsPvPPvE/gui/shield.edds";
        PvPImagePath                                     = "NinjinsPvPPvE/gui/pvpman.edds";
        RaidImagePath                                    = "NinjinsPvPPvE/gui/alarm.edds";
        SafeZoneImagePath                                = "NinjinsPvPPvE/gui/siren.edds";
        IconPositionX                                    = 0.494;
        IconPositionY                                    = 0.849;
        IconWidth                                        = 48.0;
        IconHeight                                       = 48.0;
        PvPIconColor                                     = -65536;
        PvEIconColor                                     = -16711936;
        RaidIconColor                                    = -65281;
        SafeZoneIconColor                                = -16744448;
        ExitZoneNotification                             = true;
        RemoveDynamicZoneOnlyifNoPlayerInside            = false;
        DynamicZoneRemovalRetrySeconds                   = 30;
        ExitNotificationText                             = "Exiting {zonetype} in {seconds}!";
        ExitNotificationPanelPositionX                   = 0.0;
        ExitNotificationPanelPositionY                   = 0.1;
        NotificationPanelWidth                           = 1.0;
        NotificationPanelHeight                          = 1.0;
        LoggingLevel                                     = 5;
        AllowedRaidingPlayers                            = new array<string>;
        OnlyAllowLockPickInPvP                           = false;
        EnableLockpickingZoneCreation                    = true;
        LockPickZoneDeletionTime                         = 20.0;
        LockpickingZoneRadius                            = 100.0;
        StrikeLineTransparency                           = 0.3;
        EnableLockpickingNotification                    = true;
        LockpickNotificationBroadcastRadius              = 500.0;
        LockpickNotificationIconPath                     = "NinjinsPvPPvE/gui/police.edds";
        LockpickNotificationTitle                        = "Lockpicking";
        LockpickNotificationMessage                      = " is currently lockpicking a vehicle!";
        LockpickNotificationColor                        = -65536;
        LB_ATMRobberyOnlyInPvP                           = false;
        LB_ATMRobberyEnableZoneCreation                  = false;
        ExpansionGroupsFriendlyFireDisabled              = true;
        AiToPlayerDamageEverywhere                       = true;
        PlayerToAiDamageEverywhere                       = true;
        OnlyAllowAIToDoDamageIfPlayerIsPvP               = false;
        OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatus      = false;
        OnlyAllowAIToDoDamageIfPlayerIsPvE               = false;
        OnlyAllowDamageToAIIfPlayerHasPvEStatus          = false;
        OnlyAllowAIToDamageInRaidMode                    = false;
        OnlyAllowPlayersToDamageAIInRaidMode             = false;
        EnableTerritoryFlagZones                         = true;
        TerritoryFlagZoneCreateMode                      = 1;
        TerritoryFlagPvPZoneCheckInterval                = 1000.0;
        MessageCannotDeployInSafeZone                    = "You cannot deploy items in SafeZone.";
        NoBuildMessage                                   = "Building is not allowed here.";
        MessageBlockedItemDeployInPvE                    = "Deploying {item} is blocked in PvE zone.";
        MessageBlockedItemDeployInPvP                    = "Deploying {item} is blocked in PvP zone.";
        MessageBlockedItemDeployInRaid                   = "Deploying {item} is blocked in Raid mode.";
        MessageItemRulesNotInitialized                   = "Item rules are not initialized.";
    }
/*
---------------------------------------------------------------------
SaveConfig
---------------------------------------------------------------------
*/
    void SaveConfig()
    {
        if ( GetGame().IsClient() )
		{
			return;
		}
        CheckDirectories();
        JsonFileLoader<MainConfig>.JsonSaveFile(NinjinsPvPPvE_MAIN_CONFIG_FILE, this);
    }
/*
---------------------------------------------------------------------
LoadConfig
---------------------------------------------------------------------
*/
static ref MainConfig LoadConfig()
{
    if (GetGame().IsClient())
    {
        NinjinsPvPPvE.LogDebug("[Client] LoadConfig() call blocked.");
        return null;
    }
    CheckDirectories();
    MainConfig config;
    if (FileExist(NinjinsPvPPvE_MAIN_CONFIG_FILE))
    {
        config = new MainConfig();
        JsonFileLoader<MainConfig>.JsonLoadFile(NinjinsPvPPvE_MAIN_CONFIG_FILE, config);
        NinjinLogConfig(config);
    }
    else
    {
        config = new MainConfig();
        NinjinsPvPPvE.LogDebug("MainConfig.json not found. Creating default config.");
    }
    config.SaveConfig();
    return config;
}
/*
---------------------------------------------------------------------
NinjinLogConfig - Logs settings
---------------------------------------------------------------------
*/
    static void NinjinLogConfig(MainConfig config)
    {
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("--------- General Settings ----------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("EnablePvEEverywhere: " + config.EnablePvEEverywhere);
        NinjinsPvPPvE.LogDebug("EnablePvPEverywhere: " + config.EnablePvPEverywhere);
        NinjinsPvPPvE.LogDebug("EnableReflectDamage: " + config.EnableReflectDamage);
        NinjinsPvPPvE.LogDebug("BlockChemGasGrenadeOutsidePvP: " + config.BlockChemGasGrenadeOutsidePvP);
        NinjinsPvPPvE.LogDebug("DisableAiZoneScanning: " + config.DisableAiZoneScanning);
        NinjinsPvPPvE.LogDebug("KillZombiesInSafeZone: " + config.KillZombiesInSafeZone);
        NinjinsPvPPvE.LogDebug("EVRStormSZNoShock: " + config.EVRStormSZNoShock);
        NinjinsPvPPvE.LogDebug("RemoveDynamicZoneOnlyifNoPlayerInside: " + config.RemoveDynamicZoneOnlyifNoPlayerInside);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("--------- Camera Settings -----------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("ThirdPersonOnlyDriver: " + config.ThirdPersonOnlyDriver);
        NinjinsPvPPvE.LogDebug("ForceFirstPersonGlobalPvE: " + config.ForceFirstPersonGlobalPvE);
        NinjinsPvPPvE.LogDebug("ForceFirstPersonGlobalPvP: " + config.ForceFirstPersonGlobalPvP);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("---------    Actions    -------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("DisableActionBlockForAdmins: " + config.DisableActionBlockForAdmins);
        NinjinsPvPPvE.LogDebug("AllowAnyPlayerInRaidZone: " + config.AllowAnyPlayerInRaidZone);
        NinjinsPvPPvE.LogDebug("AllowRestrainTargetinPvE: " + config.AllowRestrainTargetinPvE);
        NinjinsPvPPvE.LogDebug("AllowRestrainTargetinPvP: " + config.AllowRestrainTargetinPvP);
        NinjinsPvPPvE.LogDebug("AllowRestrainTargetinRaid: " + config.AllowRestrainTargetinRaid);
        NinjinsPvPPvE.LogDebug("DisableArmExplosivePvE: " + config.DisableArmExplosivePvE);
        NinjinsPvPPvE.LogDebug("DisableFallDamage: " + config.DisableFallDamage);
        NinjinsPvPPvE.LogDebug("DisableForceDrinkPvE: " + config.DisableForceDrinkPvE);
        NinjinsPvPPvE.LogDebug("DisableForceFeedPvE: " + config.DisableForceFeedPvE);
        NinjinsPvPPvE.LogDebug("DisableGiveBloodTargetPvE: " + config.DisableGiveBloodTargetPvE);
        NinjinsPvPPvE.LogDebug("DisableToxicExposureInPvE: " + config.DisableToxicExposureInPvE);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("----------- Map Settings ------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("DrawCOTAdminZoneLabels: " + config.DrawCOTAdminZoneLabels);
        NinjinsPvPPvE.LogDebug("DrawNamesOnZones: " + config.DrawNamesOnZones);
        NinjinsPvPPvE.LogDebug("DrawZonesOnCOT: " + config.DrawZonesOnCOT);
        NinjinsPvPPvE.LogDebug("LB_AdminMapZones: " + config.LB_AdminMapZones);
        NinjinsPvPPvE.LogDebug("StrikeLineSpacingMeters: " + config.StrikeLineSpacingMeters);
        NinjinsPvPPvE.LogDebug("StrikeLineTransparency: " + config.StrikeLineTransparency);
        NinjinsPvPPvE.LogDebug("CircleDrawingWidth: " + config.CircleDrawingWidth);
        NinjinsPvPPvE.LogDebug("mapLegendTitle: " + config.mapLegendTitle);
        for (int l = 0; l < config.mapLegend.Count(); l++)
        {
            MapLegendEntry entry = config.mapLegend.Get(l);
            NinjinsPvPPvE.LogDebug("MapLegendEntry " + l + ": " + entry.name + " [A:" + entry.ColorAlpha + " R:" + entry.ColorRed + " G:" + entry.ColorGreen + " B:" + entry.ColorBlue + "]");
        }
        NinjinsPvPPvE.LogDebug("drawStrikeLinesForNB: " + config.drawStrikeLinesForNB);
        NinjinsPvPPvE.LogDebug("DrawNoBuildRadius: " + config.DrawNoBuildRadius);
        NinjinsPvPPvE.LogDebug("noBuildZoneColor: " + config.noBuildZoneColor);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("--------- Countdown & Timers --------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("PvEExitCountdown: " + config.PvEExitCountdown);
        NinjinsPvPPvE.LogDebug("PvPExitCountdown: " + config.PvPExitCountdown);
        NinjinsPvPPvE.LogDebug("RaidExitCountdown: " + config.RaidExitCountdown);
        NinjinsPvPPvE.LogDebug("SafeZoneExitCountdown: " + config.SafeZoneExitCountdown);
        NinjinsPvPPvE.LogDebug("ZombieandAnimalSZKillScanInterval: " + config.ZombieandAnimalSZKillScanInterval + " seconds");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("---------  AFK Settings  ------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("AFKKickTimeout: " + config.AFKKickTimeout);
        NinjinsPvPPvE.LogDebug("EnableAFKKick: " + config.EnableAFKKick);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("--------   Zone Creation  -----------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("EnableAirdropZoneCreation: " + config.EnableAirdropZoneCreation);
        NinjinsPvPPvE.LogDebug("EnableItemSpawnZoneCreation: " + config.EnableItemSpawnZoneCreation);
        NinjinsPvPPvE.LogDebug("EnableLockpickingZoneCreation: " + config.EnableLockpickingZoneCreation);
        NinjinsPvPPvE.LogDebug("EnableMi8ZoneCreation: " + config.EnableMi8ZoneCreation);
        NinjinsPvPPvE.LogDebug("EnableTerritoryFlagZones: " + config.EnableTerritoryFlagZones);
        NinjinsPvPPvE.LogDebug("EnableUH1YZoneCreation: " + config.EnableUH1YZoneCreation);
        NinjinsPvPPvE.LogDebug("EnableKOTHZoneCreation: " + config.EnableKOTHZoneCreation);
        NinjinsPvPPvE.LogDebug("EnableTKKOTHZoneCreation: " + config.EnableTKKOTHZoneCreation);
        NinjinsPvPPvE.LogDebug("EnableContaminatedZoneCreation: " + config.EnableContaminatedZoneCreation);
        NinjinsPvPPvE.LogDebug("EnableAIMissionZoneCreation: " + config.EnableAIMissionZoneCreation);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("--------  Vehicle Settings ----------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        #ifdef NinjinsPvPPvE_Vehicles
        NinjinsPvPPvE.LogDebug("VehicleZoneCheckInterval: " + config.VehicleZoneCheckInterval);
        #endif
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("--------   Zone Enforcer ------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("NoVehicleKillPlayerOrDestroyVehicle: " + config.NoVehicleKillPlayerOrDestroyVehicle);
        NinjinsPvPPvE.LogDebug("NoVehicleWarningEffect: " + config.NoVehicleWarningEffect);
        NinjinsPvPPvE.LogDebug("NoVehicleWarningEffectIntensity: " + config.NoVehicleWarningEffectIntensity);
        NinjinsPvPPvE.LogDebug("NoVehicleWarningText: " + config.NoVehicleWarningText);
        NinjinsPvPPvE.LogDebug("NoVehicleZoneExitBlockDelayMS: " + config.NoVehicleZoneExitBlockDelayMS);
        NinjinsPvPPvE.LogDebug("NoVehicleZoneKillOrDestroyDelay: " + config.NoVehicleZoneKillOrDestroyDelay + " seconds");
        NinjinsPvPPvE.LogDebug("DestroyVehicleParts:");
        if (config.DestroyVehicleParts.Count() == 0)
        {
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] No DestroyVehicleParts found.");
        }
        else
        {
            for (int i = 0; i < config.DestroyVehicleParts.Count(); i++)
                NinjinsPvPPvE.LogDebug("[" + i + "]: " + config.DestroyVehicleParts.Get(i));
        }
        NinjinsPvPPvE.LogDebug("RemoveVehicleAttachments:");
        if (config.RemoveVehicleAttachments.Count() == 0)
        {
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] No RemoveVehicleAttachments found.");
        }
        else
        {
            for (int j = 0; j < config.RemoveVehicleAttachments.Count(); j++)
                NinjinsPvPPvE.LogDebug("[" + j + "]: " + config.RemoveVehicleAttachments.Get(j));
        }
        NinjinsPvPPvE.LogDebug("DestroyVehicleCargo:");
        if (config.DestroyVehicleCargo.Count() == 0)
        {
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] No DestroyVehicleCargo found.");
        }
        else
        {
            for (int k = 0; k < config.DestroyVehicleCargo.Count(); k++)
                NinjinsPvPPvE.LogDebug("[" + k + "]: " + config.DestroyVehicleCargo.Get(k));
        }
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("----------- Time Setting ------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("StartingDayOfTheWeek: " + config.StartingDayOfTheWeek);
        NinjinsPvPPvE.LogDebug("GlobalPvEZoneDays: " + config.GlobalPvEZoneDays);
        NinjinsPvPPvE.LogDebug("GlobalPvPZoneDays: " + config.GlobalPvPZoneDays);
        NinjinsPvPPvE.LogDebug("DynamicZoneRemovalRetrySeconds: " + config.DynamicZoneRemovalRetrySeconds);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("----------- Icon Setting ------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("IconHeight: " + config.IconHeight);
        NinjinsPvPPvE.LogDebug("IconPositionX: " + config.IconPositionX);
        NinjinsPvPPvE.LogDebug("IconPositionY: " + config.IconPositionY);
        NinjinsPvPPvE.LogDebug("IconWidth: " + config.IconWidth);
        NinjinsPvPPvE.LogDebug("PvEImagePath: " + config.PvEImagePath);
        NinjinsPvPPvE.LogDebug("PvPImagePath: " + config.PvPImagePath);
        NinjinsPvPPvE.LogDebug("RaidImagePath: " + config.RaidImagePath);
        NinjinsPvPPvE.LogDebug("SafeZoneImagePath: " + config.SafeZoneImagePath);
        NinjinsPvPPvE.LogDebug("PvPIconColor: " + config.PvPIconColor);
        NinjinsPvPPvE.LogDebug("PvEIconColor: " + config.PvEIconColor);
        NinjinsPvPPvE.LogDebug("RaidIconColor: " + config.RaidIconColor);
        NinjinsPvPPvE.LogDebug("SafeZoneIconColor: " + config.SafeZoneIconColor);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("----------- Notification ------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("ExitNotificationPanelPositionX: " + config.ExitNotificationPanelPositionX);
        NinjinsPvPPvE.LogDebug("ExitNotificationPanelPositionY: " + config.ExitNotificationPanelPositionY);
        NinjinsPvPPvE.LogDebug("ExitNotificationText: " + config.ExitNotificationText);
        NinjinsPvPPvE.LogDebug("ExitZoneNotification: " + config.ExitZoneNotification);
        NinjinsPvPPvE.LogDebug("NotificationPanelHeight: " + config.NotificationPanelHeight);
        NinjinsPvPPvE.LogDebug("NotificationPanelWidth: " + config.NotificationPanelWidth);
        NinjinsPvPPvE.LogDebug("PvPtoPvEBlockedNotification: " + config.PvPtoPvEBlockedNotification);
        NinjinsPvPPvE.LogDebug("AllowSameZoneTypeEnterNotifications: " + config.AllowSameZoneTypeEnterNotifications);
        NinjinsPvPPvE.LogDebug("MessageCannotDeployInSafeZone: " + config.MessageCannotDeployInSafeZone);
        NinjinsPvPPvE.LogDebug("NoBuildMessage: " + config.NoBuildMessage);
        NinjinsPvPPvE.LogDebug("MessageBlockedItemDeployInPvE: " + config.MessageBlockedItemDeployInPvE);
        NinjinsPvPPvE.LogDebug("MessageBlockedItemDeployInPvP: " + config.MessageBlockedItemDeployInPvP);
        NinjinsPvPPvE.LogDebug("MessageBlockedItemDeployInRaid: " + config.MessageBlockedItemDeployInRaid);
        NinjinsPvPPvE.LogDebug("MessageItemRulesNotInitialized: " + config.MessageItemRulesNotInitialized);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("----------- Logging LvL  ------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("EnableCfToolsLogs: " + config.EnableCfToolsLogs);
        NinjinsPvPPvE.LogDebug("LoggingLevel: " + config.LoggingLevel);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("----------- Raid Setting ------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("AllowedRaidingPlayers Count: " + config.AllowedRaidingPlayers.Count());
        int index = 1;
        foreach (string guid : config.AllowedRaidingPlayers)
        {
            NinjinsPvPPvE.LogDebug("AllowedRaidingPlayer " + index + ": " + guid);
            index++;
        }
        NinjinsPvPPvE.LogDebug("DisableRaidingDialogActionOnFlagPole: " + config.DisableRaidingDialogActionOnFlagPole);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("----------- Lockpicking  ------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("OnlyAllowLockPickInPvP: " + config.OnlyAllowLockPickInPvP);
        NinjinsPvPPvE.LogDebug("EnableLockpickingNotification: " + config.EnableLockpickingNotification);
        NinjinsPvPPvE.LogDebug("LockpickNotificationBroadcastRadius: " + config.LockpickNotificationBroadcastRadius + " meters");
        NinjinsPvPPvE.LogDebug("LockpickNotificationColor: " + config.LockpickNotificationColor);
        NinjinsPvPPvE.LogDebug("LockpickNotificationIconPath: " + config.LockpickNotificationIconPath);
        NinjinsPvPPvE.LogDebug("LockpickNotificationMessage: " + config.LockpickNotificationMessage);
        NinjinsPvPPvE.LogDebug("LockpickNotificationTitle: " + config.LockpickNotificationTitle);
        NinjinsPvPPvE.LogDebug("LockPickZoneDeletionTime: " + config.LockPickZoneDeletionTime);
        NinjinsPvPPvE.LogDebug("LockpickingZoneRadius: " + config.LockpickingZoneRadius);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("----------- AI/Expansion ------------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("AiToPlayerDamageEverywhere: " + config.AiToPlayerDamageEverywhere);
        NinjinsPvPPvE.LogDebug("ExpansionGroupsFriendlyFireDisabled: " + config.ExpansionGroupsFriendlyFireDisabled);
        NinjinsPvPPvE.LogDebug("OnlyAllowAIToDamageInRaidMode: " + config.OnlyAllowAIToDamageInRaidMode);
        NinjinsPvPPvE.LogDebug("OnlyAllowAIToDoDamageIfPlayerIsPvE: " + config.OnlyAllowAIToDoDamageIfPlayerIsPvE);
        NinjinsPvPPvE.LogDebug("OnlyAllowAIToDoDamageIfPlayerIsPvP: " + config.OnlyAllowAIToDoDamageIfPlayerIsPvP);
        NinjinsPvPPvE.LogDebug("OnlyAllowDamageToAIIfPlayerHasPvEStatus: " + config.OnlyAllowDamageToAIIfPlayerHasPvEStatus);
        NinjinsPvPPvE.LogDebug("OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatus: " + config.OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatus);
        NinjinsPvPPvE.LogDebug("OnlyAllowPlayersToDamageAIInRaidMode: " + config.OnlyAllowPlayersToDamageAIInRaidMode);
        NinjinsPvPPvE.LogDebug("PlayerToAiDamageEverywhere: " + config.PlayerToAiDamageEverywhere);
        NinjinsPvPPvE.LogDebug("OnlyAllowDamageToAIIfPlayerHasPvEStatus: " + config.OnlyAllowDamageToAIIfPlayerHasPvEStatus);
        NinjinsPvPPvE.LogDebug("OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatus: " + config.OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatus);
        NinjinsPvPPvE.LogDebug("ExpansionReputationPenealtyPveEsPvE: " + config.ExpansionReputationPenealtyPveEsPvE);
        NinjinsPvPPvE.LogDebug("EnableExpansionReputationPenaltyPvEvsPvE: " + config.EnableExpansionReputationPenaltyPvEvsPvE);
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("--------- Territory & Flag ----------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("EnableTerritoryFlagZones: " + config.EnableTerritoryFlagZones);
        NinjinsPvPPvE.LogDebug("TerritoryFlagPvPZoneCheckInterval: " + config.TerritoryFlagPvPZoneCheckInterval);
        NinjinsPvPPvE.LogDebug("TerritoryFlagZoneCreateMode: " + config.TerritoryFlagZoneCreateMode);
    }
/*
---------------------------------------------------------------------
CheckDirectories
---------------------------------------------------------------------
*/
    static void CheckDirectories()
    {
        if (!FileExist(NinjinsPvPPvE_ROOT_FOLDER))
        {
            bool dirCreated = MakeDirectory(NinjinsPvPPvE_ROOT_FOLDER);
            if (dirCreated)
            {
                NinjinsPvPPvE.LogDebug("Created root directory: " + NinjinsPvPPvE_ROOT_FOLDER);
            }
            else
            {
                NinjinsPvPPvE.LogCritical("Failed to create root directory: " + NinjinsPvPPvE_ROOT_FOLDER);
            }
        }
        if (!FileExist(NinjinsPvPPvE_GENERAL_CONFIG_DIR))
        {
            bool configDirCreated = MakeDirectory(NinjinsPvPPvE_GENERAL_CONFIG_DIR);
            if (configDirCreated)
            {
                NinjinsPvPPvE.LogDebug("Created config directory: " + NinjinsPvPPvE_GENERAL_CONFIG_DIR);
            }
            else
            {
                NinjinsPvPPvE.LogCritical("Failed to create config directory: " + NinjinsPvPPvE_GENERAL_CONFIG_DIR);
            }
        }
    }
/*
---------------------------------------------------------------------
Icon Reslover
---------------------------------------------------------------------
*/
    string ResolveIcon(string input)
    {
        string fallbackPath = "NinjinsPvPPvE/gui/";
        if (!input || input == "")
        {
            return "";
        }
        if (input.Length() >= 5 && input.Substring(input.Length() - 5, 5) == ".edds")
        {
            if (!input.Contains("/"))
                return fallbackPath + input;
            return input;
        }
        #ifdef EXPANSIONMODCORE
            string expansionIcon = ExpansionIcons.GetPath(input);
            if (expansionIcon != "")
                return expansionIcon;
        #endif
        if (input == "airdrop")        return fallbackPath + "airdrop.edds";
        else if (input == "alarm")     return fallbackPath + "alarm.edds";
        else if (input == "arrows")    return fallbackPath + "arrows.edds";
        else if (input == "axe")       return fallbackPath + "axe.edds";
        else if (input == "bow")       return fallbackPath + "bow.edds";
        else if (input == "checkmark") return fallbackPath + "checkmark.edds";
        else if (input == "close")     return fallbackPath + "close.edds";
        else if (input == "error")     return fallbackPath + "error.edds";
        else if (input == "exclamation") return fallbackPath + "exclamation.edds";
        else if (input == "gearwheel") return fallbackPath + "gearwheel.edds";
        else if (input == "guns")      return fallbackPath + "guns.edds";
        else if (input == "gunstwo")   return fallbackPath + "gunstwo.edds";
        else if (input == "knife")     return fallbackPath + "knife.edds";
        else if (input == "knife2")    return fallbackPath + "knife2.edds";
        else if (input == "swords")    return fallbackPath + "swords.edds";
        else if (input == "swords3")   return fallbackPath + "swords3.edds";
        else if (input == "swords4")   return fallbackPath + "swords4.edds";
        else if (input == "swordstwo") return fallbackPath + "swordstwo.edds";
        else if (input == "shield")    return fallbackPath + "shield.edds";
        else if (input == "shield2")   return fallbackPath + "shield2.edds";
        else if (input == "scope")     return fallbackPath + "scope.edds";
        else if (input == "scope2")    return fallbackPath + "scope2.edds";
        else if (input == "handcuffs") return fallbackPath + "handcuffs.edds";
        else if (input == "police")    return fallbackPath + "police.edds";
        else if (input == "police2")   return fallbackPath + "police2.edds";
        else if (input == "siren")     return fallbackPath + "siren.edds";
        else if (input == "present")   return fallbackPath + "present.edds";
        else if (input == "info")          return fallbackPath + "info.edds";
        else if (input == "information")   return fallbackPath + "information.edds";
        else if (input == "open")          return fallbackPath + "open.edds";
        else if (input == "paw")           return fallbackPath + "paw.edds";
        else if (input == "skull2")        return fallbackPath + "skull2.edds";
        else if (input == "skullbones")    return fallbackPath + "skullbones.edds";
        else if (input == "pvp_logosmall") return fallbackPath + "pvp_logosmall.edds";
        else if (input == "pvp")           return fallbackPath + "pvp.edds";
        else if (input == "pvpman")        return fallbackPath + "pvpman.edds";
        else if (input == "toxic")         return fallbackPath + "toxic.edds";
        else if (input == "toxic2")        return fallbackPath + "toxic2.edds";
        else if (input == "toxic4")        return fallbackPath + "toxic4.edds";
        else if (input == "toxic6")        return fallbackPath + "toxic6.edds";
        else if (input == "toxic7")        return fallbackPath + "toxic7.edds";
        else if (input == "toxic8")        return fallbackPath + "toxic8.edds";
        else if (input == "toxicbarrel")   return fallbackPath + "toxicbarrel.edds";
        else if (input == "toxicstop")     return fallbackPath + "toxicstop.edds";
        else if (input == "helicopter")    return fallbackPath + "helicopter.edds";
        else if (input == "helicopter2")   return fallbackPath + "helicopter2.edds";
        else if (input == "crouchmanblack")return fallbackPath + "crouchmanblack.edds";
        else if (input == "crouchmanwhite")return fallbackPath + "crouchmanwhite.edds";
        #ifdef EXPANSIONMODCORE
            return ExpansionIcons.GetPath("Questionmark");
        #endif
        return fallbackPath + "present.edds";
    }
/*
---------------------------------------------------------------------
Helper + Getter
---------------------------------------------------------------------
*/
    bool IsPvPEverywhereActive()
    {
        return EnablePvPEverywhere && IsTimeActive(GlobalPvPZoneDays);
    }
    bool IsPvEEverywhereActive()
    {
        return EnablePvEEverywhere && IsTimeActive(GlobalPvEZoneDays);
    }
    bool IsTimeActive(array<ref DayConfig> dayConfigs)
    {
        if (!dayConfigs || dayConfigs.Count() == 0)
            return false;
        NinjinsZoneTimeSettings currentTime = NinjinsZoneTimeSettings.Now();
        int currentDay = NinjinsZoneTimeSettings.GetDayOfWeek();
        string currentDayName = NinjinsZoneTimeSettings.GetDayName(currentDay);
        foreach (DayConfig config : dayConfigs)
        {
            if (config.dayName == currentDayName)
            {
                int currentHour = currentTime.Hour;
                int normalizedStart = config.startHour % 24;
                int normalizedEnd = config.endHour % 24;
                if (normalizedStart < normalizedEnd)
                {
                    return currentHour >= normalizedStart && currentHour < normalizedEnd;
                }
                else
                {
                    return currentHour >= normalizedStart || currentHour < normalizedEnd;
                }
            }
        }
        return false;
    }
    static bool NeedsLegacyFix()
    {
        if (!FileExist(NinjinsPvPPvE_MAIN_CONFIG_FILE))
            return false;

        FileHandle file = OpenFile(NinjinsPvPPvE_MAIN_CONFIG_FILE, FileMode.READ);
        if (file == 0)
            return false;

        string line;
        bool needsFixing = false;
        while (FGets(file, line) > 0)
        {
            if (line.Contains("\"GlobalPvPZoneDays\"") && line.Contains(":") && line.Contains("\""))
            {
                TStringArray pvpParts = new TStringArray;
                line.Split(":", pvpParts);
                if (pvpParts.Count() > 1 && pvpParts[1].Contains("\""))
                {
                    needsFixing = true;
                    break;
                }
            }
            if (line.Contains("\"GlobalPvEZoneDays\"") && line.Contains(":") && line.Contains("\""))
            {
                TStringArray pveParts = new TStringArray;
                line.Split(":", pveParts);
                if (pveParts.Count() > 1 && pveParts[1].Contains("\""))
                {
                    needsFixing = true;
                    break;
                }
            }
        }
        CloseFile(file);
        return needsFixing;
    }
	
    static bool ApplyLegacyFix()
    {
        CheckDirectories();
        string fixedContent;
        bool needsFixing = false;
        if (FileExist(NinjinsPvPPvE_MAIN_CONFIG_FILE))
        {
            FileHandle file = OpenFile(NinjinsPvPPvE_MAIN_CONFIG_FILE, FileMode.READ);
            if (file != 0)
            {
                string line;
                while (FGets(file, line) > 0)
                {
                    if (line.Contains("\"GlobalPvPZoneDays\"") && line.Contains(":") && line.Contains("\""))
                    {
                        string legacyPvP;
                        int colonIdxPvP = FindColonIndex(line);
                        int quote1PvP = FindNextQuote(line, colonIdxPvP);
                        int quote2PvP = FindNextQuote(line, quote1PvP + 1);
                        if (quote1PvP != -1 && quote2PvP != -1)
                        {
                            legacyPvP = line.Substring(quote1PvP + 1, quote2PvP - quote1PvP - 1);
                            array<string> daysPvP = new array<string>();
                            legacyPvP.Split(" ", daysPvP);
                            fixedContent += "        \"GlobalPvPZoneDays\": [\n";
                            for (int iPvP = 0; iPvP < daysPvP.Count(); iPvP++)
                            {
                                string dayPvP = daysPvP[iPvP].Trim();
                                fixedContent += "            { \"dayName\": \"" + dayPvP + "\", \"startHour\": 0, \"endHour\": 24 }";
                                if (iPvP < daysPvP.Count() - 1)
                                    fixedContent += ",\n";
                                else
                                    fixedContent += "\n";
                            }
                            fixedContent += "        ],\n";
                            needsFixing = true;
                            continue;
                        }
                    }
                    if (line.Contains("\"GlobalPvEZoneDays\"") && line.Contains(":") && line.Contains("\""))
                    {
                        string legacyPvE;
                        int colonIdxPvE = FindColonIndex(line);
                        int quote1PvE = FindNextQuote(line, colonIdxPvE);
                        int quote2PvE = FindNextQuote(line, quote1PvE + 1);
                        if (quote1PvE != -1 && quote2PvE != -1)
                        {
                            legacyPvE = line.Substring(quote1PvE + 1, quote2PvE - quote1PvE - 1);
                            array<string> daysPvE = new array<string>();
                            legacyPvE.Split(" ", daysPvE);
                            fixedContent += "        \"GlobalPvEZoneDays\": [\n";
                            for (int iPvE = 0; iPvE < daysPvE.Count(); iPvE++)
                            {
                                string dayPvE = daysPvE[iPvE].Trim();
                                fixedContent += "            { \"dayName\": \"" + dayPvE + "\", \"startHour\": 0, \"endHour\": 24 }";
                                if (iPvE < daysPvE.Count() - 1)
                                    fixedContent += ",\n";
                                else
                                    fixedContent += "\n";
                            }
                            fixedContent += "        ],\n";
                            needsFixing = true;
                            continue;
                        }
                    }
                    fixedContent += line + "\n";
                }
                CloseFile(file);
            }
            if (needsFixing)
            {
                FileHandle outFile = OpenFile(NinjinsPvPPvE_MAIN_CONFIG_FILE, FileMode.WRITE);
                if (outFile != 0)
                {
                    FPrint(outFile, fixedContent);
                    CloseFile(outFile);
                    NinjinsPvPPvE.LogDebug("Legacy day format fixed and written back to MainConfig.json");
                    return true;
                }
            }
        }
        return false;
    }
	
    static int FindColonIndex(string line)
    {
        for (int i = 0; i < line.Length(); i++)
        {
            if (line.Get(i) == ":")
                return i;
        }
        return -1;
    }
    static int FindNextQuote(string line, int start)
    {
        for (int i = start; i < line.Length(); i++)
        {
            if (line.Get(i) == "\"")
                return i;
        }
        return -1;
    }
}
