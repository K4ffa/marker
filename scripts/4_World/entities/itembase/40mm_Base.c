modded class Ammo_40mm_Base
{
    private PlayerBase m_Thrower;
    void SetThrower(PlayerBase thrower)
    {
        m_Thrower = thrower;
    }
    PlayerBase GetThrower()
    {
        return m_Thrower;
    }
    override bool EEOnDamageCalculated(TotalDamageResult damageResult,int damageType,EntityAI source,int component,string dmgZone,string ammo,vector modelPos,float speedCoef)
    {
        if (!m_Thrower)
        {
            PlayerBase attacker = PlayerBase.Cast(source.GetHierarchyRootPlayer());
            if (attacker)
            {
                SetThrower(attacker);
                if (attacker.GetIdentity())
                    NinjinsPvPPvE.LogDebug("[" + this.GetType() + "] Thrower resolved via hierarchy: " + attacker.GetIdentity().GetName());
                else
                    NinjinsPvPPvE.LogDebug("[" + this.GetType() + "] Thrower resolved via hierarchy: Unknown identity");
            }
            else
            {
                NinjinsPvPPvE.LogWarning("[" + this.GetType() + "] Could not resolve thrower via hierarchy in EEOnDamageCalculated.");
            }
        }
        return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
    }
}
modded class Ammo_40mm_ChemGas: Ammo_40mm_Base
{
    override void OnActivatedByItem(notnull ItemBase item)
    {
        vector pos = GetPosition();
        if (ZoneRules.ShouldBlockAmmo(pos))
        {
            NinjinsPvPPvE.LogDebug("ChemGas ammo deactivated: blocked by zone/fireplace rules.");
            Delete();
            return;
        }
        super.OnActivatedByItem(item);
    }
    override void EEKilled(Object killer)
    {
        vector pos = GetPosition();
        PlayerBase thrower = GetThrower();
        int zoneType = ZoneRules.GetZoneTypeAtPosition(pos);
        string throwerName = "null";
        if (thrower && thrower.GetIdentity())
            throwerName = thrower.GetIdentity().GetName();
        NinjinsPvPPvE.LogDebug("[Ammo_40mm_ChemGas] EEKilled triggered. ZoneType=" + zoneType + ", Thrower=" + throwerName);
        if (!ZoneRules.ShouldExplodeInZone(pos, thrower))
        {
            NinjinsPvPPvE.LogDebug("[Ammo_40mm_ChemGas] Explosion canceled by ZoneRules. Deleting.");
            Delete();
            return;
        }
        if (zoneType == ZONE_TYPE_PVE)
        {
            NinjinsPvPPvE.LogDebug("[Ammo_40mm_ChemGas] Explosion blocked in PvE. Deleting.");
            Delete();
            return;
        }
        super.EEKilled(killer);
    }
}
modded class Ammo_40mm_Explosive: Ammo_40mm_Base
{
    override void OnActivatedByItem(notnull ItemBase item)
    {
        vector pos = GetPosition();
        if (ZoneRules.ShouldBlockAmmo(pos))
        {
            NinjinsPvPPvE.LogDebug("Explosive ammo deactivated: blocked by zone/fireplace rules.");
            Delete();
            return;
        }
        super.OnActivatedByItem(item);
    }
    override void EEKilled(Object killer)
    {
        vector pos = GetPosition();
        PlayerBase thrower = GetThrower();
        if (!ZoneRules.ShouldExplodeInZone(pos, thrower))
        {
            NinjinsPvPPvE.LogDebug("[Ammo_40mm_Explosive] Explosion canceled by ZoneRules. Deleting.");
            Delete();
            return;
        }
        super.EEKilled(killer);
    }
}