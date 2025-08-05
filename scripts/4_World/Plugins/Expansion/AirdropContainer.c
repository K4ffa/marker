#ifdef EXPANSIONMODMISSIONS
modded class ExpansionAirdropContainerBase
{
	protected string emm_UniqueAirdropID;
	override void EEInit()
	{
		super.EEInit();
		if (GetGame().IsServer())
		{
			emm_UniqueAirdropID = GetGame().GetTime().ToString() + "_" + Math.RandomInt(0, 100000).ToString();
		}
	}
	override void Expansion_DiscardParachute()
    {
        super.Expansion_DiscardParachute();
        if (!GetGame().IsServer() || !g_MainConfig || !g_MainConfig.EnableAirdropZoneCreation)
            return;
        NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
        if (!settings || !settings.AirdropDefaults)
        {
            NinjinsPvPPvE.LogWarning("[AirdropZone] Settings or defaults missing, skipping zone creation.");
            return;
        }
        DynamicZones def = settings.AirdropDefaults;
        vector origin     = GetPosition();
        float radius      = def.radius;
        float minOffset   = radius * def.offsetMinMultiplier;
        float maxOffset   = radius * def.offsetMaxMultiplier;
        float angle       = Math.RandomFloatInclusive(0, Math.PI2);
        float distance    = Math.RandomFloatInclusive(minOffset, maxOffset);
        float offsetX     = Math.Cos(angle) * distance;
        float offsetZ     = Math.Sin(angle) * distance;
        vector center     = Vector(origin[0] + offsetX, origin[1], origin[2] + offsetZ);
        ZoneBase zone = new ZoneBase();
        zone.name                        = "AirdropZone_" + emm_UniqueAirdropID;
        zone.HideWhenNested              = def.HideWhenNested;
        zone.DrawNoBuildShape            = def.DrawNoBuildShape;
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
            NinjinsPvPPvE.LogDebug("[AirdropZone] Registered dynamic zone: " + zone.name);
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[AirdropZone] ZoneManager instance not found.");
        }
    }
    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);
        if (!GetGame().IsServer())
            return;
        string zoneName = "AirdropZone_" + emm_UniqueAirdropID;
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (zoneManager && zoneManager.RemoveDynamicZone(zoneName))
        {
            NinjinsPvPPvE.LogDebug("[AirdropZone] Removed zone on deletion: " + zoneName);
        }
        else
        {
            NinjinsPvPPvE.LogDebug("[AirdropZone] No zone found to remove on deletion: " + zoneName);
        }
    }
}
#endif