modded class Wreck_Mi8_Crashed
{
/*
--------------------------------------------------
Creates a dynamic Mi8 zone
--------------------------------------------------
*/
    private string uniqueID;
    void Wreck_Mi8_Crashed()
    {
        if (!GetGame().IsServer() || !g_MainConfig || !g_MainConfig.EnableMi8ZoneCreation)
            return;
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CreateMi8Zone, 500, false);
    }
    void CreateMi8Zone()
    {
        if (!GetGame().IsServer()) 
            return;
        vector wreckPosition = GetPosition();
        NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
        if (!settings || !settings.VanillaMi8Wreck) 
            return;
        DynamicZones def = settings.VanillaMi8Wreck;
        float radius     = def.radius;
        float minOffset  = radius * def.offsetMinMultiplier;
        float maxOffset  = radius * def.offsetMaxMultiplier;
        float angle      = Math.RandomFloatInclusive(0, Math.PI2);
        float distance   = Math.RandomFloatInclusive(minOffset, maxOffset);
        float offsetX    = Math.Cos(angle) * distance;
        float offsetZ    = Math.Sin(angle) * distance;
        float x = wreckPosition[0] + offsetX;
        float y = wreckPosition[1];
        float z = wreckPosition[2] + offsetZ;
        vector zoneCenter = Vector(x, y, z);
        uniqueID = "Mi8Zone_" + x.ToString() + "_" + z.ToString();
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (!zoneManager) 
            return;
        ZoneBase zone = new ZoneBase();
        zone.HideWhenNested = def.HideWhenNested;
        zone.DrawNoBuildShape = def.DrawNoBuildShape;
        zone.zoneMinHeight               = def.zoneMinHeight;
        zone.zoneMaxHeight               = def.zoneMaxHeight;
        zone.ignoreHeightCheck           = def.ignoreHeightCheck;
        zone.type                        = def.type;
        zone.priority                    = def.priority;
        zone.shape                       = ZoneShape.CIRCLE;
        zone.drawShape                   = def.drawShape;
        zone.radius                      = radius;
        zone.noBuildRadius               = -1;
        zone.zoneAlpha                   = def.zoneAlpha;
        zone.zoneRed                     = def.zoneRed;
        zone.zoneGreen                   = def.zoneGreen;
        zone.zoneBlue                    = def.zoneBlue;
        zone.dayConfigs = new array<ref DayConfig>();
        foreach (DayConfig config : def.dayConfigs)
        {
            zone.dayConfigs.Insert(new DayConfig(config.dayName, config.startHour, config.endHour));
        }
        zone.enableCustomMessages        = def.enableCustomMessages;
        zone.customTitle                 = def.customTitle;
        zone.customMessageEnter          = def.customMessageEnter;
        zone.customMessageExit           = def.customMessageExit;
        zone.customIcon                  = def.customIcon;
        zone.notificationColor           = def.notificationColor;
        zone.forceFirstPerson            = def.forceFirstPerson;
        zone.EnableExpansion3DMarker     = def.EnableExpansion3DMarker;
        zone.OnlyAllowExpansion2DMarker  = def.OnlyAllowExpansion2DMarker;
        zone.Expansion3DIcon             = def.Expansion3DIcon;
        zone.ExpansionMarkerName         = def.ExpansionMarkerName;
        zone.drawStrikeZone              = def.drawStrikeZone;
        zone.UsesDisallowedVehicles      = def.UsesDisallowedVehicles;
        zone.ZonelabelOffsetX_Meters      = def.ZonelabelOffsetX_Meters;
        zone.ZonelabelOffsetZ_Meters      = def.ZonelabelOffsetZ_Meters;
        zone.ZoneLabelColor               = def.ZoneLabelColor;
        zone.Hide               = def.Hide;
        zone.NoLogOut                     = def.NoLogOut;
        zone.NoLogOutTeleportPos          = def.NoLogOutTeleportPos;
        zone.name                        = uniqueID;
        zone.center                      = zoneCenter;
        zoneManager.RegisterDynamicZone(zone);
        NinjinsPvPPvE.LogDebug("[Wreck_Mi8_Crashed] Mi8 zone created with name: " + uniqueID + " at " + zoneCenter.ToString());
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
                NinjinsPvPPvE.LogDebug("[Wreck_Mi8_Crashed] Mi8 zone removed: " + uniqueID);
            else
                NinjinsPvPPvE.LogDebug("[Wreck_Mi8_Crashed] No zone found with name: " + uniqueID);
        }
    }
}
