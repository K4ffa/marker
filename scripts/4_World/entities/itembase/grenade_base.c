modded class Grenade_Base
{
    private PlayerBase Thrower;
    private bool m_IsFireplaceExplosion = false;
    void SetThrower(PlayerBase thrower)
    {
        Thrower = thrower;
    }
    PlayerBase GetThrower()
    {
        return Thrower;
    }
    void MarkAsFireplaceExplosion()
    {
        m_IsFireplaceExplosion = true;
    }
    bool IsFireplaceExplosion()
    {
        return m_IsFireplaceExplosion;
    }
    override protected void InitiateExplosion()
    {
        vector grenadePos = GetPosition();
        if (ZoneRules.IsInsideFireplace(grenadePos))
        {
            MarkAsFireplaceExplosion();
            NinjinsPvPPvE.LogDebug("[Grenade_Base] Marked as fireplace explosion.");
        }
        string grenadeType = this.GetType();
        if (g_ItemRules && g_ItemRules.BypassZoneChecksGrenades.Find(grenadeType) != -1)
        {
            NinjinsPvPPvE.LogDebug("[Grenade_Base] Bypassing zone checks for grenade type: " + grenadeType);
            super.InitiateExplosion();
            return;
        }
        if (ZoneRules.ShouldExplodeInZone(grenadePos, Thrower))
        {
            super.InitiateExplosion();
        }
        else
        {
            NinjinsPvPPvE.LogDebug("[Grenade_Base] Grenade deleted: zone check failed.");
            Delete();
        }
    }
    override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        if (!Thrower)
        {
            PlayerBase attacker = PlayerBase.Cast(source.GetHierarchyRootPlayer());
            if (attacker)
            {
                SetThrower(attacker);
                if (attacker.GetIdentity())
                    NinjinsPvPPvE.LogDebug("[Grenade_Base] Thrower/Attacker resolved via hierarchy lookup and set: " + attacker.GetIdentity().GetName());
                else
                    NinjinsPvPPvE.LogDebug("[Grenade_Base] Thrower/Attacker resolved via hierarchy lookup but has no Identity.");
            }
        }
        return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
    }
};