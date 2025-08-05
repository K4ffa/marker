modded class Wreck_UH1Y
{
/*
---------------------------------------------------------------------------------------------
Creates a dynamic UH1Y zone
---------------------------------------------------------------------------------------------
*/
    private string uniqueID;
    void Wreck_UH1Y()
    {
        if (!GetGame().IsServer() || !g_MainConfig || !g_MainConfig.EnableUH1YZoneCreation)
            return;
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CreateUH1YZone, 500, false);
    }
    void CreateUH1YZone()
    {
        if (!GetGame().IsServer()) 
            return;
        vector position = GetPosition();
        uniqueID = "UH1YZone_" + position[0].ToString() + "_" + position[2].ToString();
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (!zoneManager) 
            return;
        NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
        if (!settings)
        {
            NinjinsPvPPvE.LogDebug("[Wreck_UH1Y][ERROR] Could not load NinjinsZoneSettings. Using fallback.");
            return;
        }
        DynamicZones def = settings.VanillaUH1YWreck;
        if (!def)
        {
            NinjinsPvPPvE.LogDebug("[Wreck_UH1Y][ERROR] def is null. Using fallback values.");
            return;
        }
        ZoneBase zone = new ZoneBase();
        zone.HideWhenNested = def.HideWhenNested;
        zone.DrawNoBuildShape = def.DrawNoBuildShape;
        zone.zoneMinHeight               = def.zoneMinHeight;
        zone.zoneMaxHeight               = def.zoneMaxHeight;
        zone.ignoreHeightCheck           = def.ignoreHeightCheck;
        zone.type                = def.type;
        zone.priority            = def.priority;
        zone.shape               = ZoneShape.CIRCLE;
        zone.drawShape           = def.drawShape;
        zone.radius              = def.radius;
        zone.noBuildRadius       = -1;
        zone.zoneAlpha           = def.zoneAlpha;
        zone.zoneRed             = def.zoneRed;
        zone.zoneGreen           = def.zoneGreen;
        zone.zoneBlue            = def.zoneBlue;
        zone.dayConfigs = new array<ref DayConfig>();
        foreach (DayConfig config : def.dayConfigs)
        {
            zone.dayConfigs.Insert(new DayConfig(config.dayName, config.startHour, config.endHour));
        }
        zone.enableCustomMessages= def.enableCustomMessages;
        zone.customTitle         = def.customTitle;
        zone.customMessageEnter  = def.customMessageEnter;
        zone.customMessageExit   = def.customMessageExit;
        zone.customIcon          = def.customIcon;
        zone.notificationColor   = def.notificationColor;
        zone.forceFirstPerson    = def.forceFirstPerson;
        zone.UsesDisallowedVehicles    = def.UsesDisallowedVehicles;
        zone.EnableExpansion3DMarker = def.EnableExpansion3DMarker;
        zone.OnlyAllowExpansion2DMarker = def.OnlyAllowExpansion2DMarker;
        zone.Expansion3DIcon         = def.Expansion3DIcon;
        zone.ExpansionMarkerName     = def.ExpansionMarkerName;
        zone.drawStrikeZone     = def.drawStrikeZone;
        zone.ZonelabelOffsetX_Meters      = def.ZonelabelOffsetX_Meters;
        zone.ZonelabelOffsetZ_Meters      = def.ZonelabelOffsetZ_Meters;
        zone.ZoneLabelColor               = def.ZoneLabelColor;
        zone.Hide               = def.Hide;
        zone.NoLogOut                     = def.NoLogOut;
        zone.NoLogOutTeleportPos          = def.NoLogOutTeleportPos;
        zone.name   = uniqueID;
        zone.center = position;
        zoneManager.RegisterDynamicZone(zone);
        NinjinsPvPPvE.LogDebug("[Wreck_UH1Y] UH1Y zone created at position: " + position.ToString());
    }
    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);
        if (!GetGame().IsServer()) 
            return;
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (zoneManager)
        {
            bool removed = zoneManager.RemoveDynamicZone(uniqueID);
            if (removed)
            {
                NinjinsPvPPvE.LogDebug("[Wreck_UH1Y] UH1Y zone removed: " + uniqueID);
            }
            else
            {
                NinjinsPvPPvE.LogDebug("[Wreck_UH1Y] No UH1Y zone found with name: " + uniqueID);
            }
        }
    }
}