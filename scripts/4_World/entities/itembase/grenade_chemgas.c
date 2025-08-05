modded class Grenade_ChemGas : Grenade_Base
{
    protected PlayerBase m_Thrower;
    override void SetThrower(PlayerBase thrower)
    {
        if (thrower)
        {
            m_Thrower = thrower;
            super.SetThrower(thrower);
        }
    }
    override PlayerBase GetThrower()
    {
        return m_Thrower;
    }
    override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        DamageUtils dmgUtils = DamageUtils.GetInstance();
        AttackerContext ctx = dmgUtils.ResolveAttacker(source);
        if (ctx.Player)
        {
            SetThrower(ctx.Player);
            if (ctx.Player.GetIdentity())
            {
                NinjinsPvPPvE.LogDebug("[Grenade_ChemGas] Set thrower (shot) as: " + ctx.Player.GetIdentity().GetName());
            }
            else
            {
                NinjinsPvPPvE.LogDebug("[Grenade_ChemGas] Set thrower (shot) as: Unknown Identity");
            }
        }
        return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
    }
    override protected void OnExplode()
    {
        if (g_MainConfig && g_MainConfig.BlockChemGasGrenadeOutsidePvP == 1)
        {
            int zoneType = ZoneRules.GetZoneTypeAtPosition(GetPosition());
            if (zoneType == ZONE_TYPE_PVE)
            {
                NinjinsPvPPvE.LogDebug("[Grenade_ChemGas] ChemGas explosion blocked by main config and zone (PvE). Grenade deleted.");
                Delete();
                return;
            }
        }
        vector explodePos = GetPosition();
        if (ZoneRules.ShouldExplodeInZone(explodePos, m_Thrower))
        {
            NinjinsPvPPvE.LogDebug("[Grenade_ChemGas] Allowed by ZoneRules.");
            super.OnExplode();
        }
        else
        {
            NinjinsPvPPvE.LogDebug("[Grenade_ChemGas] Blocked by ZoneRules. Grenade deleted.");
            Delete();
        }
    }
}