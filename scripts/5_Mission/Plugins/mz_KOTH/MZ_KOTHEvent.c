#ifdef mz_koth
modded class MZ_KOTHEvent
{
	string m_MZKZoneID;
	bool m_ZoneCreated = false;
	bool m_ZoneRemoved = false;
	void OnInitZone()
	{
		if (m_ZoneCreated || !GetGame().IsServer())
			return;
		if (!g_MainConfig || !g_MainConfig.EnableKOTHZoneCreation)
			return;
		NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
		if (!settings || !settings.MZKOTHZoneDefaults)
		{
			NinjinsPvPPvE.LogWarning("[MZK KOTH] Settings or defaults missing — skipping zone creation.");
			return;
		}
		DynamicZones def = settings.MZKOTHZoneDefaults;
		float radius     = def.radius;
		float minOffset  = radius * def.offsetMinMultiplier;
		float maxOffset  = radius * def.offsetMaxMultiplier;
		float angle      = Math.RandomFloatInclusive(0, Math.PI2);
		float distance   = Math.RandomFloatInclusive(minOffset, maxOffset);
		float offsetX    = Math.Cos(angle) * distance;
		float offsetZ    = Math.Sin(angle) * distance;
		vector center    = Vector(MZK_Position[0] + offsetX, MZK_Position[1], MZK_Position[2] + offsetZ);
		m_MZKZoneID = "MZK_KOTHZone_" + MZK_Name + "_ID" + MZK_ID;
		ZoneBase zone = new ZoneBase();
		zone.name                 = m_MZKZoneID;
		zone.HideWhenNested 	  = def.HideWhenNested;
        zone.DrawNoBuildShape 	  = def.DrawNoBuildShape;
		zone.displayName          = MZK_Name;
		zone.center               = center;
		zone.radius               = radius;
		zone.shape                = ZoneShape.CIRCLE;
		zone.zoneMinHeight        = def.zoneMinHeight;
        zone.zoneMaxHeight        = def.zoneMaxHeight;
		zone.noBuildRadius        = -1;
        zone.ignoreHeightCheck    = def.ignoreHeightCheck;
		zone.type                 = def.type;
		zone.priority             = def.priority;
		zone.zoneAlpha            = def.zoneAlpha;
		zone.zoneRed              = def.zoneRed;
		zone.zoneGreen            = def.zoneGreen;
		zone.zoneBlue             = def.zoneBlue;
		zone.dayConfigs = new array<ref DayConfig>();
		foreach (DayConfig config : def.dayConfigs)
		{
			zone.dayConfigs.Insert(new DayConfig(config.dayName, config.startHour, config.endHour));
		}
		zone.forceFirstPerson     = def.forceFirstPerson;
		zone.drawShape            = def.drawShape;
		zone.enableCustomMessages = def.enableCustomMessages;
		zone.customTitle          = def.customTitle;
		zone.customMessageEnter   = def.customMessageEnter;
		zone.customMessageExit    = def.customMessageExit;
		zone.customIcon           = def.customIcon;
		zone.notificationColor    = def.notificationColor;
		zone.UsesDisallowedVehicles = def.UsesDisallowedVehicles;
		zone.EnableExpansion3DMarker = def.EnableExpansion3DMarker;
		zone.OnlyAllowExpansion2DMarker = def.OnlyAllowExpansion2DMarker;
		zone.Expansion3DIcon         = def.Expansion3DIcon;
		zone.ExpansionMarkerName     = def.ExpansionMarkerName;
		zone.drawStrikeZone          = def.drawStrikeZone;
		zone.ZonelabelOffsetX_Meters = def.ZonelabelOffsetX_Meters;
        zone.ZonelabelOffsetZ_Meters = def.ZonelabelOffsetZ_Meters;
        zone.ZoneLabelColor          = def.ZoneLabelColor;
        zone.Hide          = def.Hide;
		zone.NoLogOut                     = def.NoLogOut;
        zone.NoLogOutTeleportPos          = def.NoLogOutTeleportPos;
		ZoneManager.GetInstance().RegisterDynamicZone(zone);
		m_ZoneCreated = true;
		NinjinsPvPPvE.LogDebug("[MZK KOTH] Zone created: " + m_MZKZoneID + " at " + center.ToString());
	}
	override void UpdateKOTH()
	{
		super.UpdateKOTH();
			if (!m_ZoneCreated && !MZK_Finished && MZK_StartDelay == 1)
		{
			OnInitZone();
		}
		if (m_ZoneCreated && !m_ZoneRemoved && MZK_Finished)
		{
			m_ZoneRemoved = true;
			RemoveMZKZone();
		}
	}
	void RemoveMZKZone()
	{
		if (!m_MZKZoneID || m_MZKZoneID == "")
			return;
		bool removed;
		if (g_MainConfig && g_MainConfig.RemoveDynamicZoneOnlyifNoPlayerInside)
		{
			removed = ZoneManager.GetInstance().RemoveDynamicZone(m_MZKZoneID);
			if (!removed)
			{
				NinjinsPvPPvE.LogDebug("[MZK KOTH] Zone not empty, retry scheduled for: " + m_MZKZoneID);
				return;
			}
		}
		else
		{
			removed = ZoneManager.GetInstance().RemoveDynamicZone(m_MZKZoneID);
		}
		if (removed)
		{
			NinjinsPvPPvE.LogDebug("[MZK KOTH] Zone removed: " + m_MZKZoneID);
		}
		else
		{
			NinjinsPvPPvE.LogWarning("[MZK KOTH] Zone removal failed: " + m_MZKZoneID);
		}
	}
}
#ifdef mz_koth