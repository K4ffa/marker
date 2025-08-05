modded class Wreck_Mi8
{
/*
--------------------------------------------------
Creates a dynamic OLD-Mi8 zones
--------------------------------------------------
*/
    private string uniqueID;
    void Wreck_Mi8()
    {
        if (!GetGame().IsServer() || !g_MainConfig || !g_MainConfig.EnableMi8ZoneCreation)
            return;
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CreateOldMi8Zone, 500, false);
    }
    void CreateOldMi8Zone()
    {
        if (!GetGame().IsServer()) 
            return;
        vector position = GetPosition();
        uniqueID = "OldMi8Zone_" + position[0].ToString() + "_" + position[2].ToString();
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (!zoneManager) 
            return;
        NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
        if (!settings)
        {
            NinjinsPvPPvE.LogDebug("[Wreck_Mi8][Custom Zone][ERROR] Could not load NinjinsZoneSettings.");
            return;
        }
        DynamicZones def = settings.OldVanillaMi8;
        if (!def)
        {
            NinjinsPvPPvE.LogDebug("[Wreck_Mi8][Custom Zone][ERROR] OldVanillaMi8 is null.");
            return;
        }
        ZoneBase zone = new ZoneBase();
        zone.HideWhenNested = def.HideWhenNested;
        zone.DrawNoBuildShape = def.DrawNoBuildShape;
        zone.zoneMinHeight = def.zoneMinHeight;
        zone.zoneMaxHeight = def.zoneMaxHeight;
        zone.ignoreHeightCheck = def.ignoreHeightCheck;
        zone.type = def.type;
        zone.priority = def.priority;
        zone.shape = ZoneShape.CIRCLE;
        zone.drawShape = def.drawShape;
        zone.radius = def.radius;
        zone.noBuildRadius = -1;
        zone.zoneAlpha = def.zoneAlpha;
        zone.zoneRed = def.zoneRed;
        zone.zoneGreen = def.zoneGreen;
        zone.zoneBlue = def.zoneBlue;
        zone.dayConfigs = new array<ref DayConfig>();
        foreach (DayConfig config : def.dayConfigs)
        {
            zone.dayConfigs.Insert(new DayConfig(config.dayName, config.startHour, config.endHour));
        }
        zone.enableCustomMessages = def.enableCustomMessages;
        zone.customTitle = def.customTitle;
        zone.customMessageEnter = def.customMessageEnter;
        zone.customMessageExit = def.customMessageExit;
        zone.customIcon = def.customIcon;
        zone.notificationColor = def.notificationColor;
        zone.forceFirstPerson = def.forceFirstPerson;
        zone.name = uniqueID;
        zone.center = position;
        zone.UsesDisallowedVehicles = def.UsesDisallowedVehicles;
        zone.EnableExpansion3DMarker = def.EnableExpansion3DMarker;
        zone.OnlyAllowExpansion2DMarker = def.OnlyAllowExpansion2DMarker;
        zone.Expansion3DIcon         = def.Expansion3DIcon;
        zone.ExpansionMarkerName     = def.ExpansionMarkerName;
        zone.drawStrikeZone     = def.drawStrikeZone;
        zone.ZonelabelOffsetX_Meters = def.ZonelabelOffsetX_Meters;
        zone.ZonelabelOffsetZ_Meters = def.ZonelabelOffsetZ_Meters;
        zone.ZoneLabelColor          = def.ZoneLabelColor;
        zone.Hide          = def.Hide;
        zone.NoLogOut                     = def.NoLogOut;
        zone.NoLogOutTeleportPos          = def.NoLogOutTeleportPos;
        zoneManager.RegisterDynamicZone(zone);
        NinjinsPvPPvE.LogDebug("[Wreck_Mi8][Custom Zone] Zone created: " + uniqueID + " at " + position.ToString());
    }
/*
---------------------------------------------------------------------
EEDelete - Called when the wreck is deleted. Removes the dynamic zone
---------------------------------------------------------------------
*/
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
                NinjinsPvPPvE.LogDebug("[Wreck_Mi8][Custom Zone] Zone removed: " + uniqueID);
            }
            else
            {
                NinjinsPvPPvE.LogDebug("[Wreck_Mi8][Custom Zone] No zone found with name: " + uniqueID);
            }
        }
    }
}
