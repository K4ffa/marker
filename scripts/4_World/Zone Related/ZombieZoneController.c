class ZombieZoneController
{
	void ZombieZoneController() 
	{
		
	}
	void Update(float deltaTime)
	{
		if (!g_MainConfig || !g_MainConfig.KillZombiesInSafeZone)
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
			array<EntityAI> entities = new array<EntityAI>();
			DayZPlayerUtils.SceneGetEntitiesInBox(min, max, entities);
			foreach (EntityAI ent : entities)
			{
				ZombieBase zombie = ZombieBase.Cast(ent);
				if (!zombie)
					continue;
				if (!zombie.IsAlive())
					continue;
				vector pos = zombie.GetPosition();
				if (vector.Distance(pos, center) <= radius)
				{
					NinjinsPvPPvE.LogDebug("[SZ] ZOMBIE ENTERED SAFEZONE (killed): " + zombie + " @ " + pos);
					zombie.SetHealth(0);
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, 1000, false, zombie);
				}
			}
		}
	}
}
