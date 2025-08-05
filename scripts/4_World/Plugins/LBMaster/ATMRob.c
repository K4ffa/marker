#ifdef LBmaster_Groups_ATM
modded class LB_ATM_Position_Entry {
	protected string activeZoneID;
	static ref map<string, ref array<string>> s_PlayerZoneMap = new map<string, ref array<string>>();
	override void StartRobATM(PlayerBase player, int time) 
	{
		if (!player || !player.GetIdentity()) 
		{
			NinjinsPvPPvE.LogWarning("[ATM] Invalid player or identity in StartRobATM.");
			return;
		}
		string playerID = player.GetIdentity().GetId();
		vector atmPosition = position;
		if (g_MainConfig && g_MainConfig.LB_ATMRobberyOnlyInPvP && !player.netSync_IsInPvPZone && !player.ShouldBypassActionBlock()) 
		{
			NinjinsPvPPvE.LogDebug("[ATM] Robbery denied: not in PvP zone.");
			ZoneManager.GetInstance().NotifyRobberyDenied(player);
			player.GetActionManager().Interrupt();
			return;
		}
		super.StartRobATM(player, time);
		if (!g_MainConfig || !g_MainConfig.LB_ATMRobberyEnableZoneCreation) 
		{
			NinjinsPvPPvE.LogDebug("[ATM] ATM robbery zone creation is disabled.");
			return;
		}
		NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
		if (!settings || !settings.LBATMRobberyDefaults) 
		{
			NinjinsPvPPvE.LogWarning("[ATM] Robbery zone config not found.");
			return;
		}
		DynamicZones def = settings.LBATMRobberyDefaults;
		string uniqueID = "DynamicPvPZone_ATMRobbery_" + atmPosition[0].ToString() + "_" + atmPosition[2].ToString();
		ZoneBase zone = new ZoneBase();
		zone.name = uniqueID;
		zone.HideWhenNested = def.HideWhenNested;
        zone.DrawNoBuildShape = def.DrawNoBuildShape;
		zone.zoneMinHeight = def.zoneMinHeight;
        zone.zoneMaxHeight = def.zoneMaxHeight;
        zone.ignoreHeightCheck = def.ignoreHeightCheck;
		zone.type = def.type;
		zone.noBuildRadius = -1;
		zone.shape = ZoneShape.CIRCLE;
		zone.center = atmPosition;
		zone.radius = def.radius;
		zone.priority = def.priority;
		zone.enableCustomMessages = def.enableCustomMessages;
		zone.customTitle = def.customTitle;
		zone.customMessageEnter = def.customMessageEnter;
		zone.customMessageExit = def.customMessageExit;
		zone.customIcon = def.customIcon;
		zone.notificationColor = def.notificationColor;
		zone.days = def.days;
		zone.startHour = def.startHour;
		zone.endHour = def.endHour;
		zone.zoneAlpha = def.zoneAlpha;
		zone.zoneRed = def.zoneRed;
		zone.zoneGreen = def.zoneGreen;
		zone.zoneBlue = def.zoneBlue;
		zone.forceFirstPerson = def.forceFirstPerson;
		zone.drawShape = def.drawShape;
		zone.UsesDisallowedVehicles = def.UsesDisallowedVehicles;
		zone.drawStrikeZone = def.drawStrikeZone;
		zone.Expansion3DIcon = def.Expansion3DIcon;
		zone.ExpansionMarkerName = def.ExpansionMarkerName;
		zone.EnableExpansion3DMarker = def.EnableExpansion3DMarker;
		zone.OnlyAllowExpansion2DMarker = def.OnlyAllowExpansion2DMarker;
		zone.ZonelabelOffsetX_Meters = def.ZonelabelOffsetX_Meters;
		zone.ZonelabelOffsetZ_Meters = def.ZonelabelOffsetZ_Meters;
		zone.ZoneLabelColor = def.ZoneLabelColor;
		zone.Hide = def.Hide;
		zone.NoLogOut                     = def.NoLogOut;
        zone.NoLogOutTeleportPos          = def.NoLogOutTeleportPos;
		ZoneManager.GetInstance().RegisterDynamicZone(zone);
		NinjinsPvPPvE.LogDebug("[ATM] Created robbery zone: " + uniqueID);
		if (!s_PlayerZoneMap.Contains(playerID))
			s_PlayerZoneMap[playerID] = new array<string>();
		s_PlayerZoneMap[playerID].Insert(uniqueID);
		SetActiveZoneID(uniqueID);
		int durationMs = time * 60 * 1000;
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.RemoveATMZoneDelayed, durationMs, false, uniqueID);
	}
	void SetActiveZoneID(string id) 
	{
		activeZoneID = id;
	}
	void RemoveATMZoneDelayed(string uniqueID) 
	{
		bool removed = ZoneManager.GetInstance().RemoveDynamicZone(uniqueID);
		if (removed)
			NinjinsPvPPvE.LogDebug("[ATM] Robbery zone removed after timer: " + uniqueID);
		else
			NinjinsPvPPvE.LogDebug("[ATM] Zone not found for removal: " + uniqueID);
	}
	override void StopRobATM()
	{
		if (g_MainConfig && !g_MainConfig.RemoveDynamicZoneOnlyifNoPlayerInside)
		{
			super.StopRobATM();
			return;
		}
		if (robbingPlayer && robbingPlayer.GetIdentity())
		{
			string playerID = robbingPlayer.GetIdentity().GetId();
			if (s_PlayerZoneMap.Contains(playerID))
			{
				array<string> zones = s_PlayerZoneMap[playerID];
				foreach (string z : zones)
				{
					bool removedZone = ZoneManager.GetInstance().RemoveDynamicZone(z);
					if (removedZone)
						NinjinsPvPPvE.LogDebug("[ATM] Removed robbery zone for player " + playerID + ": " + z);
				}
				s_PlayerZoneMap.Remove(playerID);
			}
		}
		if (activeZoneID != "")
		{
			bool removedSelf = ZoneManager.GetInstance().RemoveDynamicZone(activeZoneID);
			if (removedSelf)
				NinjinsPvPPvE.LogDebug("[ATM] Removed active robbery zone: " + activeZoneID);
			activeZoneID = "";
		}
		super.StopRobATM();
	}
}
#endif
