class AnimalZoneController
{
	void AnimalZoneController() 
	{
		
	}

	void Update(float deltaTime)
	{
		if (!g_MainConfig || !g_MainConfig.KillAnimalsInSafeZone)
			return;

		float verticalScan = 100.0;
		array<ref ZoneBase> zones = ZoneManager.GetInstance().m_Zones;
		foreach (ZoneBase zone : zones)
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
				AnimalBase animal = AnimalBase.Cast(ent);
				if (!animal)
					continue;

				if (!animal.IsAlive())
					continue;

				string animalType = animal.GetType();
				if (animalType.Contains("Cat") || animalType.Contains("Dog") || animalType.Contains("Horse"))
					continue;

				vector pos = animal.GetPosition();
				if (vector.Distance(pos, center) <= radius)
				{
					NinjinsPvPPvE.LogDebug("[SZ] ANIMAL ENTERED SAFEZONE (killed): " + animal + " @ " + pos);
					animal.SetHealth(0);
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, 1000, false, animal);
				}
			}
		}
	}
}
