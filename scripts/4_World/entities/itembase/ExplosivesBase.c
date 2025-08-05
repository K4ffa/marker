modded class ExplosivesBase
{
    protected PlayerBase m_Placer;
    void SetPlacer(PlayerBase placer)
    {
        m_Placer = placer;
    }
    PlayerBase GetPlacer()
    {
        return m_Placer;
    }
    override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
    {
        super.OnPlacementComplete(player, position, orientation);
        PlayerBase placer = PlayerBase.Cast(player);
        if (placer)
        {
            SetPlacer(placer);
            NinjinsPvPPvE.LogDebug("[ExplosivesBase] Set placer as: " + placer.GetIdentity().GetName());
        }
    }
    override protected void InitiateExplosion()
    {
        if (GetGame().IsServer())
        {
            if (ZoneRules.GetZoneTypeAtPosition(GetPosition()) == ZONE_TYPE_PVE)
            {
                NinjinsPvPPvE.LogDebug("[ExplosivesBase] Blocking explosion in PvE (position check). Deleting explosive instead.");
                Delete();
                return;
            }
        }
        super.InitiateExplosion();
    }
    override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (!m_Placer)
		{
			PlayerBase attacker = PlayerBase.Cast(source.GetHierarchyRootPlayer());
			if (attacker)
			{
				SetPlacer(attacker);
				if (attacker.GetIdentity())
					NinjinsPvPPvE.LogDebug("[ExplosivesBase] Placer/Attacker resolved via hierarchy lookup and set: " + attacker.GetIdentity().GetName());
				else
					NinjinsPvPPvE.LogDebug("[ExplosivesBase] Placer/Attacker resolved via hierarchy lookup but has no Identity.");
			}

		}
		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
}