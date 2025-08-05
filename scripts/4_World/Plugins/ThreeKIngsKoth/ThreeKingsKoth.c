#ifdef RizenKOTH
modded class ThreeKingsKothRPCObject
{
    string m_KOTHZoneID;
    override void StartTimer(PluginThreeKingsKothSpawnPoint capturePoint)
    {
        super.StartTimer(capturePoint);
        CreateKOTHZone(capturePoint);
    }
    override void OnCaptured()
    {
        super.OnCaptured();
        RemoveKOTHZone();
    }
    override void OnExpired()
    {
        super.OnExpired();
        RemoveKOTHZone();
    }
    void CreateKOTHZone(PluginThreeKingsKothSpawnPoint capturePoint)
    {
        if (!GetGame().IsServer() || !g_MainConfig || !g_MainConfig.EnableTKKOTHZoneCreation)
            return;
        NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
        if (!settings || !settings.KOTHZoneDefaults)
        {
            NinjinsPvPPvE.LogWarning("[RizenKOTH] Failed to load KOTHZoneDefaults. Skipping zone creation.");
            return;
        }
        DynamicZones def = settings.KOTHZoneDefaults;
        vector origin    = capturePoint.spawnPoint;
        float radius     = def.radius;
        float minOffset  = radius * def.offsetMinMultiplier;
        float maxOffset  = radius * def.offsetMaxMultiplier;
        float angle      = Math.RandomFloatInclusive(0, Math.PI2);
        float distance   = Math.RandomFloatInclusive(minOffset, maxOffset);
        float offsetX    = Math.Cos(angle) * distance;
        float offsetZ    = Math.Sin(angle) * distance;
        vector center    = Vector(origin[0] + offsetX, origin[1], origin[2] + offsetZ);
        m_KOTHZoneID = "KOTHZone_" + capturePoint.zoneName;
        ZoneBase zone = new ZoneBase();
        zone.HideWhenNested              = def.HideWhenNested;
        zone.DrawNoBuildShape            = def.DrawNoBuildShape;
        zone.name                        = m_KOTHZoneID;
        zone.displayName                 = capturePoint.zoneName;
        zone.center                      = center;
        zone.radius                      = radius;
        zone.noBuildRadius               = -1;
        zone.shape                       = ZoneShape.CIRCLE;
        zone.zoneMinHeight               = def.zoneMinHeight;
        zone.zoneMaxHeight               = def.zoneMaxHeight;
        zone.ignoreHeightCheck           = def.ignoreHeightCheck;
        zone.type                        = def.type;
        zone.priority                    = def.priority;
        zone.zoneAlpha                   = def.zoneAlpha;
        zone.zoneRed                     = def.zoneRed;
        zone.zoneGreen                   = def.zoneGreen;
        zone.zoneBlue                    = def.zoneBlue;
        zone.dayConfigs = new array<ref DayConfig>();
        foreach (DayConfig config : def.dayConfigs)
        {
            zone.dayConfigs.Insert(new DayConfig(config.dayName, config.startHour, config.endHour));
        }
        zone.forceFirstPerson            = def.forceFirstPerson;
        zone.drawShape                   = def.drawShape;
        zone.enableCustomMessages        = def.enableCustomMessages;
        zone.customTitle                 = def.customTitle;
        zone.customMessageEnter          = def.customMessageEnter;
        zone.customMessageExit           = def.customMessageExit;
        zone.customIcon                  = def.customIcon;
        zone.notificationColor           = def.notificationColor;
        zone.UsesDisallowedVehicles      = def.UsesDisallowedVehicles;
        zone.EnableExpansion3DMarker     = def.EnableExpansion3DMarker;
        zone.OnlyAllowExpansion2DMarker  = def.OnlyAllowExpansion2DMarker;
        zone.ExpansionMarkerName         = def.ExpansionMarkerName;
        zone.Expansion3DIcon             = def.Expansion3DIcon;
        zone.drawStrikeZone              = def.drawStrikeZone;
        zone.ZonelabelOffsetX_Meters = def.ZonelabelOffsetX_Meters;
        zone.ZonelabelOffsetZ_Meters = def.ZonelabelOffsetZ_Meters;
        zone.ZoneLabelColor          = def.ZoneLabelColor;
        zone.Hide          = def.Hide;
        zone.NoLogOut                     = def.NoLogOut;
        zone.NoLogOutTeleportPos          = def.NoLogOutTeleportPos;
        ZoneManager.GetInstance().RegisterDynamicZone(zone);
        NinjinsPvPPvE.LogDebug("[RizenKOTH] Zone created: " + m_KOTHZoneID);
    }
    void RemoveKOTHZone()
    {
        if (!m_KOTHZoneID || m_KOTHZoneID == "")
            return;
        bool removed;
        if (g_MainConfig && g_MainConfig.RemoveDynamicZoneOnlyifNoPlayerInside)
        {
            removed = ZoneManager.GetInstance().RemoveDynamicZone(m_KOTHZoneID);
            if (!removed)
            {
                NinjinsPvPPvE.LogDebug("[RizenKOTH] Zone not empty — removal will be retried: " + m_KOTHZoneID);
                return;
            }
        }
        else
        {
            removed = ZoneManager.GetInstance().RemoveDynamicZone(m_KOTHZoneID);
        }
        if (removed)
        {
            NinjinsPvPPvE.LogDebug("[RizenKOTH] Zone removed: " + m_KOTHZoneID);
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[RizenKOTH] Failed to remove zone: " + m_KOTHZoneID);
        }
    }
}
#endif
