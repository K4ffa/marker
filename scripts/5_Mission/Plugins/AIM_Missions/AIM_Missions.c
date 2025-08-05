#ifdef AI_Missions
modded class ExpansionAI_Mission
{
    private ref map<int, string> AIM_PVPZoneMap = new map<int, string>();    
    private void CreateMissionZone(int missionID, vector position)
    {
        if (!GetGame().IsServer() || !g_MainConfig || !g_MainConfig.EnableAIMissionZoneCreation)
            return;
        if (AIM_PVPZoneMap.Contains(missionID))
        {
            NinjinsPvPPvE.LogDebug("[AI Missions] Zone already exists for mission ID: " + missionID);
            return;
        }
        NinjinsZoneSettings configSettings = NinjinsZoneSettings.Load();
        if (!configSettings || !configSettings.AIDynamicMission)
        {
            NinjinsPvPPvE.LogWarning("[AI Missions] AIDynamicMission settings missing. Zone not created.");
            return;
        }
        DynamicZones def = configSettings.AIDynamicMission;
        float radius = def.radius;
        float minOffset = radius * def.offsetMinMultiplier;
        float maxOffset = radius * def.offsetMaxMultiplier;
        float angle = Math.RandomFloatInclusive(0, Math.PI2);
        float distance = Math.RandomFloatInclusive(minOffset, maxOffset);
        float offsetX = Math.Cos(angle) * distance;
        float offsetZ = Math.Sin(angle) * distance;
        vector center = Vector(position[0] + offsetX, position[1], position[2] + offsetZ);
        ZoneBase zone = new ZoneBase();
        zone.HideWhenNested = def.HideWhenNested;
        zone.DrawNoBuildShape = def.DrawNoBuildShape;
        zone.name = "AIMission_" + missionID.ToString();
        zone.displayName = "AI Mission Zone";
        zone.center = center;
        zone.zoneMinHeight = def.zoneMinHeight;
        zone.zoneMaxHeight = def.zoneMaxHeight;
        zone.ignoreHeightCheck = def.ignoreHeightCheck;
        zone.type = def.type;
        zone.priority = def.priority;
        zone.noBuildRadius = -1;
        zone.shape = ZoneShape.CIRCLE;
        zone.drawShape = def.drawShape;
        zone.radius = radius;
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
        zone.UsesDisallowedVehicles = def.UsesDisallowedVehicles;
        zone.EnableExpansion3DMarker = def.EnableExpansion3DMarker;
        zone.OnlyAllowExpansion2DMarker = def.OnlyAllowExpansion2DMarker;
        zone.ExpansionMarkerName = def.ExpansionMarkerName;
        zone.Expansion3DIcon = def.Expansion3DIcon;
        zone.drawStrikeZone = def.drawStrikeZone;
        zone.ZonelabelOffsetX_Meters = def.ZonelabelOffsetX_Meters;
        zone.ZonelabelOffsetZ_Meters = def.ZonelabelOffsetZ_Meters;
        zone.ZoneLabelColor = def.ZoneLabelColor;
        zone.Hide = def.Hide;
        zone.NoLogOut = def.NoLogOut;
        zone.NoLogOutTeleportPos = def.NoLogOutTeleportPos;
        zone.vertices = new array<vector>();
        ZoneManager zoneMgr = ZoneManager.GetInstance();
        if (zoneMgr && zoneMgr.RegisterDynamicZone(zone))
        {
            AIM_PVPZoneMap.Insert(missionID, zone.name);
            NinjinsPvPPvE.LogDebug("[AI Missions] Created dynamic PvP zone for mission " + missionID + " at " + center.ToString());
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[AI Missions] Failed to register zone for mission: " + missionID);
        }
    }
    override void StartAIMission()
    {
        super.StartAIMission();
        int newMissionIndex = AIM_MissionsArray.Count() - 1;
        if (newMissionIndex < 0)
            return;
        AIM_Missions missionData = AIM_MissionsArray.Get(newMissionIndex);
        if (!missionData)
            return;
        int actualMissionID = missionData.GetMissionID();
        vector missionPos = GetAIMConfig().Missions.Get(actualMissionID).GetPosition();
        CreateMissionZone(actualMissionID, missionPos);
    }
	override void MissionCleanup(int m_MissionID = -1)
	{
		if (!GetGame().IsServer())
			return;
		if (m_MissionID >= 0 && m_MissionID < AIM_MissionsArray.Count())
		{
			int actualMissionID = AIM_MissionsArray.Get(m_MissionID).GetMissionID();
			RemoveMissionZone(actualMissionID);
		}
		super.MissionCleanup(m_MissionID);
	}
	private void RemoveMissionZone(int missionID)
	{
		if (AIM_PVPZoneMap.Contains(missionID))
		{
			string zoneID = AIM_PVPZoneMap.Get(missionID);
			ZoneManager zoneMgr = ZoneManager.GetInstance();
			if (zoneMgr && zoneID != "" && zoneMgr.RemoveDynamicZone(zoneID))
			{
				NinjinsPvPPvE.LogDebug("[AI Missions] Removed dynamic zone for mission " + missionID);
			}
			else
			{
				NinjinsPvPPvE.LogWarning("[AI Missions] Failed to remove zone for mission: " + missionID);
			}
			AIM_PVPZoneMap.Remove(missionID);
		}
	}
}
#endif
