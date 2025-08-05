#ifdef Utopia_Airdrop_Public_Scripts
modded class UtopiaFallingContainer 
{
    protected string uniqueZoneID;
    void UtopiaFallingContainer() 
    {
        if (GetGame().IsServer())
            uniqueZoneID = "AirdropZone_" + GetGame().GetTime().ToString() + "_" + Math.RandomInt(0, 100000).ToString();
    }
    override void EOnLand() 
    {
        super.EOnLand();
        if (!GetGame().IsServer() || !g_MainConfig || !g_MainConfig.EnableAirdropZoneCreation)
            return;
        NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
        if (!settings || !settings.AirdropDefaults) 
        {
            NinjinsPvPPvE.LogWarning("[UtopiaFallingContainer] AirdropDefaults missing. Zone not created.");
            return;
        }
        DynamicZones def = settings.AirdropDefaults;
        vector origin    = GetPosition();
        float radius     = def.radius;
        float minOffset  = radius * def.offsetMinMultiplier;
        float maxOffset  = radius * def.offsetMaxMultiplier;
        float angle      = Math.RandomFloatInclusive(0, Math.PI2);
        float distance   = Math.RandomFloatInclusive(minOffset, maxOffset);
        float offsetX    = Math.Cos(angle) * distance;
        float offsetZ    = Math.Sin(angle) * distance;
        vector center    = Vector(origin[0] + offsetX, origin[1], origin[2] + offsetZ);
        ZoneBase zone = new ZoneBase();
        zone.name                        = uniqueZoneID;
        zone.center                      = center;
        zone.HideWhenNested              = def.HideWhenNested;
        zone.DrawNoBuildShape            = def.DrawNoBuildShape;
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
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (zoneManager) 
        {
            zoneManager.RegisterDynamicZone(zone);
            NinjinsPvPPvE.LogDebug("[UtopiaFallingContainer] Created dynamic zone: " + uniqueZoneID + " at " + center.ToString());
        } 
        else 
        {
            NinjinsPvPPvE.LogWarning("[UtopiaFallingContainer] ZoneManager missing.");
        }
    }
    void ~UtopiaFallingContainer() 
    {
        if (!GetGame().IsServer())
            return;
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (zoneManager && zoneManager.RemoveDynamicZone(uniqueZoneID)) 
        {
            NinjinsPvPPvE.LogDebug("[UtopiaFallingContainer] Removed dynamic zone: " + uniqueZoneID);
        }
    }
}
#endif
