class ItemZoneController
{
	void ItemZoneController() 
	{
		
	}
	void Update(float deltaTime)
	{
		if (!g_MainConfig || !g_MainConfig.DeleteItemsInSafeZone)
			return;
		float verticalScan = 100.0;
		foreach (ZoneBase zone : ZoneManager.GetInstance().m_Zones)
		{
			if (zone.type != ZONE_TYPE_SAFEZONE || !zone.IsActive())
				continue;
			vector center = zone.center;
			float radius = zone.radius;
			vector min = Vector(center[0] - radius, center[1] - verticalScan, center[2] - radius);
			vector max = Vector(center[0] + radius, center[1] + verticalScan, center[2] + radius);
			array<EntityAI> found = new array<EntityAI>();
			DayZPlayerUtils.SceneGetEntitiesInBox(min, max, found);
			foreach (EntityAI e : found)
			{
				ItemBase ib = ItemBase.Cast(e);
				if (!ib)
					continue;
				EntityAI parent = ib.GetHierarchyParent();
				if (parent && parent.IsInherited(PlayerBase))
					continue;
				if (ib.IsWhitelistedFromSZCleanup())
					continue;
				vector pos = ib.GetPosition();
				if (vector.Distance(pos, center) <= radius)
				{
					NinjinsPvPPvE.LogDebug("[SZ] ITEM IN SAFEZONE (deleted): " + ib + " @ " + pos);
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, 1000, false, ib);
				}
			}
		}
	}
}
