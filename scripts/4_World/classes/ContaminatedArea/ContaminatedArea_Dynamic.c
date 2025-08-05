modded class ContaminatedArea_Dynamic
{
    private string m_UniqueZoneID;
    override void EEInit()
    {
        super.EEInit();
        if (!GetGame().IsServer())
            return;
        if (!g_MainConfig || !g_MainConfig.EnableContaminatedZoneCreation)
        {
            NinjinsPvPPvE.LogDebug("[ContaminatedArea_Dynamic] Zone creation skipped: 'EnableContaminatedZoneCreation' is false or missing.");
            return;
        }
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CreateContamPvPZone, 500, false);
    }
    void CreateContamPvPZone()
    {
        if (!GetGame().IsServer()) 
            return;
        vector pos = GetPosition();
        NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
        if (!settings || !settings.ContaminatedZoneDefaults)
        {
            NinjinsPvPPvE.LogWarning("[ContaminatedArea_Dynamic] ContaminatedZoneDefaults missing. Zone not created.");
            return;
        }
        DynamicZones def = settings.ContaminatedZoneDefaults;
        float radius     = def.radius;
        float minOffset  = radius * def.offsetMinMultiplier;
        float maxOffset  = radius * def.offsetMaxMultiplier;
        float angle      = Math.RandomFloatInclusive(0, Math.PI2);
        float distance   = Math.RandomFloatInclusive(minOffset, maxOffset);
        float offsetX    = Math.Cos(angle) * distance;
        float offsetZ    = Math.Sin(angle) * distance;
        vector center = Vector(pos[0] + offsetX, pos[1], pos[2] + offsetZ);
        m_UniqueZoneID = "ContaminatedArea_Dynamic_" + center[0].ToString() + "_" + center[2].ToString();
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (!zoneManager)
        {
            NinjinsPvPPvE.LogWarning("[ContaminatedArea_Dynamic] ZoneManager not found.");
            return;
        }
        ZoneBase zone = new ZoneBase();
        zone.HideWhenNested              = def.HideWhenNested;
        zone.DrawNoBuildShape            = def.DrawNoBuildShape;
        zone.name                        = m_UniqueZoneID;
        zone.displayName                 = "Contaminated Area";
        zone.zoneMinHeight               = def.zoneMinHeight;
        zone.zoneMaxHeight               = def.zoneMaxHeight;
        zone.ignoreHeightCheck           = def.ignoreHeightCheck;
        zone.center                      = center;
        zone.noBuildRadius               = -1;
        zone.type                        = def.type;
        zone.priority                    = def.priority;
        zone.shape                       = ZoneShape.CIRCLE;
        zone.drawShape                   = def.drawShape;
        zone.radius                      = radius;
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
        zone.customMessageEnter         = def.customMessageEnter;
        zone.customMessageExit          = def.customMessageExit;
        zone.customIcon                  = def.customIcon;
        zone.notificationColor           = def.notificationColor;
        zone.forceFirstPerson            = def.forceFirstPerson;
        zone.UsesDisallowedVehicles      = def.UsesDisallowedVehicles;
        zone.EnableExpansion3DMarker     = def.EnableExpansion3DMarker;
        zone.OnlyAllowExpansion2DMarker  = def.OnlyAllowExpansion2DMarker;
        zone.Expansion3DIcon             = def.Expansion3DIcon;
        zone.ExpansionMarkerName         = def.ExpansionMarkerName;
        zone.drawStrikeZone              = def.drawStrikeZone;
        zone.ZonelabelOffsetX_Meters = def.ZonelabelOffsetX_Meters;
        zone.ZonelabelOffsetZ_Meters = def.ZonelabelOffsetZ_Meters;
        zone.ZoneLabelColor          = def.ZoneLabelColor;
        zone.Hide          = def.Hide;
        zone.NoLogOut                     = def.NoLogOut;
        zone.NoLogOutTeleportPos          = def.NoLogOutTeleportPos;
        zoneManager.RegisterDynamicZone(zone);
        NinjinsPvPPvE.LogDebug("[ContaminatedArea_Dynamic] Created contaminated zone: " + m_UniqueZoneID + " at " + center.ToString());
    }
    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);
        if (!GetGame().IsServer()) 
            return;
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (zoneManager && zoneManager.RemoveDynamicZone(m_UniqueZoneID))
        {
            NinjinsPvPPvE.LogDebug("[ContaminatedArea_Dynamic] Zone removed: " + m_UniqueZoneID);
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[ContaminatedArea_Dynamic] Failed to remove zone or it didn't exist: " + m_UniqueZoneID);
        }
    }
}
