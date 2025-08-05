/*
---------------------------------------------------------------------
Class for zone related settings
---------------------------------------------------------------------
*/
class NinjinsZoneSettings
{
    ref array<ref ZoneBase> Zones;
    ref DynamicZones OldVanillaMi8;
    ref DynamicZones AirdropDefaults;
    ref DynamicZones VanillaMi8Wreck;
    ref DynamicZones VanillaUH1YWreck;
    ref DynamicZones ContaminatedZoneDefaults;
    ref DynamicZones FlagZoneDefaults;
    #ifdef LBmaster_Groups_ATM
    ref DynamicZones LBATMRobberyDefaults;
    #endif
    #ifdef mz_koth
    ref DynamicZones MZKOTHZoneDefaults;
    #endif
    #ifdef RizenKOTH
    ref DynamicZones KOTHZoneDefaults;
    #endif
    #ifdef AI_Missions
    ref DynamicZones AIDynamicMission;
    #endif
    #ifdef RadioTower
    ref DynamicZones RTZoneDefaults;
    #endif
    void NinjinsZoneSettings()
    {
        Zones = new array<ref ZoneBase>();
    }
    DynamicZones CreateDefaultZone(int red, int green, int blue, string title, string enterMsg, string exitMsg, string icon, string markerName, string markerIcon, float radius = 100.0, bool forceFirstPerson = true)
    {
        DynamicZones zone = new DynamicZones();
        zone.HideWhenNested       = false;
        zone.DrawNoBuildShape     = false;
        zone.zoneMinHeight        = 0.0;
        zone.zoneMaxHeight        = 0.0;
        zone.ignoreHeightCheck    = 0.0;
        zone.type                 = ZONE_TYPE_PVP;
        zone.priority             = 10;
        zone.NoLogOut = true;
        zone.NoLogOutTeleportPos = "4500 0 3000";
        zone.zoneAlpha            = 255;
        zone.zoneRed              = red;
        zone.zoneGreen            = green;
        zone.zoneBlue             = blue;      
        zone.dayConfigs = new array<ref DayConfig>();
        zone.dayConfigs.Insert(new DayConfig("Monday"));
        zone.dayConfigs.Insert(new DayConfig("Tuesday"));
        zone.dayConfigs.Insert(new DayConfig("Wednesday"));
        zone.dayConfigs.Insert(new DayConfig("Thursday"));
        zone.dayConfigs.Insert(new DayConfig("Friday"));
        zone.dayConfigs.Insert(new DayConfig("Saturday"));
        zone.dayConfigs.Insert(new DayConfig("Sunday"));
        zone.enableCustomMessages = true;
        zone.customTitle          = title;
        zone.customMessageEnter   = enterMsg;
        zone.customMessageExit    = exitMsg;
        zone.customIcon           = icon;
        zone.notificationColor    = ARGB(255, red, green, blue);
        zone.forceFirstPerson     = forceFirstPerson;
        zone.drawShape            = true;
        zone.radius               = radius;
        zone.UsesDisallowedVehicles = false;
        zone.EnableExpansion3DMarker = false;
        zone.OnlyAllowExpansion2DMarker = false;
        zone.ExpansionMarkerName = markerName;
        zone.Expansion3DIcon     = markerIcon;
        zone.offsetMinMultiplier = 0.0;
        zone.offsetMaxMultiplier = 0.0;
        zone.ZonelabelOffsetX_Meters = 0.0;
        zone.ZonelabelOffsetZ_Meters = 0.0;
        zone.ZoneLabelColor      = -65536;
        return zone;
    }
/*
--------------------------------------------------
Default Settings
--------------------------------------------------
*/
    void DefaultSettings()
    {
        OldVanillaMi8 = CreateDefaultZone(150, 0, 255, "Old Mi8 Crash Zone", "You entered the Old Mi8 crash zone!", "You exited the Old Mi8 crash zone!", "NinjinsPvPPvE/gui/helicopter.edds", "Custom Zone", "Compass");
        AirdropDefaults = CreateDefaultZone(255, 0, 255, "Airdrop Zone", "Entered Airdrop Zone", "Exited Airdrop Zone", "NinjinsPvPPvE/gui/airdrop.edds", "Airdrop Zone", "Airdrop");
        VanillaMi8Wreck = CreateDefaultZone(255, 0, 0, "Mi8 Crash Zone", "You entered the Mi8 crash zone!", "You exited the Mi8 crash zone!", "NinjinsPvPPvE/gui/helicopter.edds", "Mi8 Zone", "Helicopter");
        VanillaUH1YWreck = CreateDefaultZone(0, 255, 0, "UH1Y Crash Zone", "You entered the UH1Y crash zone!", "You exited the UH1Y crash zone!", "NinjinsPvPPvE/gui/helicopter.edds", "UH1Y Zone", "Helicopter");
        ContaminatedZoneDefaults = CreateDefaultZone(64, 255, 64, "Contaminated Zone", "You have entered a contaminated PvP zone!", "You have exited the contaminated PvP zone!", "NinjinsPvPPvE/gui/gas.edds", "Contaminated Area", "Gas Mask", 120.0);
        FlagZoneDefaults = CreateDefaultZone(255, 165, 0, "Territory Flag Zone", "You have entered a territory flag PvP zone!", "You have left the territory flag PvP zone!", "NinjinsPvPPvE/gui/flag.edds", "Territory Flag Zone", "Flag", 100.0);
        FlagZoneDefaults.Hide = 1;
        #ifdef RadioTower
        RTZoneDefaults = CreateDefaultZone(0, 255, 200, "Radio Tower Zone", "You entered an RT zone!", "You exited the RT zone!", "NinjinsPvPPvE/gui/radiotower.edds", "Radio Tower", "Tower", 100.0, false);
        #endif
        #ifdef LBmaster_Groups_ATM
        LBATMRobberyDefaults = CreateDefaultZone(255, 100, 0, "ATM Robbery Zone", "You have entered an ATM Robbery Zone", "You have exited an ATM Robbery Zone", "NinjinsPvPPvE/gui/police2.edds", "ATM Robbery Zone", "Police", 100.0, true);
        #endif
        #ifdef mz_koth
        MZKOTHZoneDefaults = CreateDefaultZone(0, 128, 255, "MZ KOTH", "You entered the MZ KOTH Zone!", "You exited the MZ KOTH Zone!", "NinjinsPvPPvE/gui/pvpman.edds", "MZ Koth Zone", "Star", 100.0, false);
        #endif
        #ifdef RizenKOTH
        KOTHZoneDefaults = CreateDefaultZone(255, 50, 50, "KOTH Event", "You ve entered a King of the Hill!", "You ve left the King of the Hill!", "NinjinsPvPPvE/gui/pvpman.edds", "Three Kings Koth", "Star", 100.0, false);
        #endif
        #ifdef AI_Missions
        AIDynamicMission = CreateDefaultZone(255, 128, 0, "AI Dynamic Mission Zone", "You entered an AI PvP mission zone!", "You exited the AI PvP mission zone!", "NinjinsPvPPvE/gui/guns.edds", "Ai Mission", "Gun", 150.0, true);
        #endif
        ZoneBase polyZone = new ZoneBase();
        polyZone.HideWhenNested       = false;
        polyZone.DrawNoBuildShape     = false;
        polyZone.name = "VisualPolygon1";
        polyZone.displayName = "VisualPolygon1";
        polyZone.type = ZONE_TYPE_VISUAL;
        polyZone.shape = ZoneShape.POLYGON;
        polyZone.drawShape = true;
        polyZone.zoneAlpha = 255;
        polyZone.zoneRed = 255;
        polyZone.zoneGreen = 0;
        polyZone.zoneBlue = 0;
        polyZone.dayConfigs = new array<ref DayConfig>();
        polyZone.dayConfigs.Insert(new DayConfig("Monday"));
        polyZone.dayConfigs.Insert(new DayConfig("Tuesday"));
        polyZone.dayConfigs.Insert(new DayConfig("Wednesday"));
        polyZone.dayConfigs.Insert(new DayConfig("Thursday"));
        polyZone.dayConfigs.Insert(new DayConfig("Friday"));
        polyZone.dayConfigs.Insert(new DayConfig("Saturday"));
        polyZone.dayConfigs.Insert(new DayConfig("Sunday"));
        polyZone.enableCustomMessages = true;
        polyZone.customTitle = "Default VISUAL Polygon Zone";
        polyZone.customMessageEnter = "Welcome to the Default polygon!";
        polyZone.customMessageExit = "Leaving the Default polygon!";
        polyZone.customIcon = "NinjinsPvPPvE/gui/alarm.edds";
        polyZone.notificationColor = -65536;
        polyZone.forceFirstPerson = false;
        polyZone.UsesDisallowedVehicles = false;
        polyZone.EnableExpansion3DMarker = false;
        polyZone.OnlyAllowExpansion2DMarker = false;
        polyZone.ExpansionMarkerName = "Polygon Zone";
        polyZone.Expansion3DIcon = "Exclamation";
        polyZone.ZonelabelOffsetX_Meters = 0.0;
        polyZone.ZonelabelOffsetZ_Meters = 0.0;
        polyZone.ZoneLabelColor = -65536;
        polyZone.center = Vector(4100.03, 5.76707, 4099.72);
        polyZone.zoneMinHeight = 0.0;
        polyZone.zoneMaxHeight = 0.0;
        polyZone.ignoreHeightCheck = 0.0;
        polyZone.vertices.Insert(Vector(4000, 0, 4000));
        polyZone.vertices.Insert(Vector(4200, 0, 4000));
        polyZone.vertices.Insert(Vector(4200, 0, 4200));
        polyZone.vertices.Insert(Vector(4000, 0, 4200));
        Zones.Insert(polyZone);
        ZoneBase circleZone = new ZoneBase();
        circleZone.HideWhenNested       = false;
        circleZone.DrawNoBuildShape     = false;
        circleZone.name = "Circle Example PvP";
        circleZone.displayName = "Circle Example PvP";
        circleZone.type = ZONE_TYPE_PVP;
        circleZone.shape = ZoneShape.CIRCLE;
        circleZone.drawShape = true;    
        circleZone.center = Vector(3000, 0, 3000);
        circleZone.zoneMinHeight = 0.0;
        circleZone.zoneMaxHeight = 0.0;
        circleZone.ignoreHeightCheck = 0.0;
        circleZone.radius = 300.0;
        circleZone.priority = 10;
        circleZone.enableCustomMessages = true;
        circleZone.customTitle = "Circle Zone Example PVP";
        circleZone.customMessageEnter = "You entered the Circle Zone Example!";
        circleZone.customMessageExit = "You exited the Circle Zone Example!";
        circleZone.customIcon = "NinjinsPvPPvE/gui/guns.edds";
        circleZone.notificationColor = ARGB(255, 0, 255, 0);
        circleZone.dayConfigs = new array<ref DayConfig>();
        circleZone.dayConfigs.Insert(new DayConfig("Monday"));
        circleZone.dayConfigs.Insert(new DayConfig("Tuesday"));
        circleZone.dayConfigs.Insert(new DayConfig("Wednesday"));
        circleZone.dayConfigs.Insert(new DayConfig("Thursday"));
        circleZone.dayConfigs.Insert(new DayConfig("Friday"));
        circleZone.dayConfigs.Insert(new DayConfig("Saturday"));
        circleZone.dayConfigs.Insert(new DayConfig("Sunday"));
        circleZone.zoneAlpha = 255;
        circleZone.zoneRed = 255;
        circleZone.zoneGreen = 0;
        circleZone.zoneBlue = 0;
        circleZone.forceFirstPerson = false;
        circleZone.UsesDisallowedVehicles = false;
        circleZone.EnableExpansion3DMarker = false;
        circleZone.OnlyAllowExpansion2DMarker = false;
        circleZone.ExpansionMarkerName = "Circle Zone";
        circleZone.Expansion3DIcon = "Info";
        circleZone.ZonelabelOffsetX_Meters = 0.0;
        circleZone.ZonelabelOffsetZ_Meters = 0.0;
        circleZone.ZoneLabelColor = -65536;
        Zones.Insert(circleZone);
    }
    void SaveSettings()
    {
        CheckDirectories();
        JsonFileLoader<NinjinsZoneSettings>.JsonSaveFile(NinjinsPvPPvE_ZONES_CONFIG_FILE, this);
    }
    static ref NinjinsZoneSettings Load()
    {
        NinjinsZoneSettings settings = new NinjinsZoneSettings();
        CheckDirectories();

        if (FileExist(NinjinsPvPPvE_ZONES_CONFIG_FILE))
        {
            JsonFileLoader<NinjinsZoneSettings>.JsonLoadFile(NinjinsPvPPvE_ZONES_CONFIG_FILE, settings);
        }
        else
        {
            settings.DefaultSettings();
            settings.SaveSettings();
        }
        array<ref DynamicZones> dynZones = 
        {
            settings.OldVanillaMi8,
            settings.AirdropDefaults,
            settings.VanillaMi8Wreck,
            settings.VanillaUH1YWreck,
            settings.ContaminatedZoneDefaults
            #ifdef LBmaster_Groups_ATM
            settings.LBATMRobberyDefaults
            #endif
            #ifdef mz_koth
            settings.MZKOTHZoneDefaults
            #endif
            #ifdef RizenKOTH
            settings.KOTHZoneDefaults
            #endif
            #ifdef AI_Missions
            settings.AIDynamicMission
            #endif
            #ifdef RadioTower
            settings.RTZoneDefaults
            #endif
        };

        foreach (DynamicZones dz : dynZones)
        {
            ZoneDayConfigHelper.UpgradeLegacy(dz);
        }
        foreach (ZoneBase zb : settings.Zones)
        {
            ZoneDayConfigHelper.UpgradeLegacy(zb);
        }

        settings.SaveSettings();
        return settings;
    }
/*
--------------------------------------------------
logging
--------------------------------------------------
*/
    static void NinjinLogConfig (NinjinsZoneSettings config)
    {
    }
/*
--------------------------------------------------
check if config directories exist.
--------------------------------------------------
*/
    static void CheckDirectories()
    {
        if (!FileExist(NinjinsPvPPvE_ROOT_FOLDER))
        {
            bool dirCreated = MakeDirectory(NinjinsPvPPvE_ROOT_FOLDER);
            if (dirCreated)
                NinjinsPvPPvE.LogDebug("Created root directory: " + NinjinsPvPPvE_ROOT_FOLDER);
            else
                NinjinsPvPPvE.LogCritical("Failed to create root directory: " + NinjinsPvPPvE_ROOT_FOLDER);
        }
        if (!FileExist(NinjinsPvPPvE_GENERAL_CONFIG_DIR))
        {
            bool configDirCreated = MakeDirectory(NinjinsPvPPvE_GENERAL_CONFIG_DIR);
            if (configDirCreated)
                NinjinsPvPPvE.LogDebug("Created config directory: " + NinjinsPvPPvE_GENERAL_CONFIG_DIR);
            else
                NinjinsPvPPvE.LogCritical("Failed to create config directory: " + NinjinsPvPPvE_GENERAL_CONFIG_DIR);
        }
    }
}
