modded class DayZPlayerImplementFallDamage
{
    override void HandleFallDamage(FallDamageData pData)
    {
        PlayerBase player = PlayerBase.Cast(m_Player);
        if (DamageUtils.ShouldBlockFallDamage(player))
            return;    
        super.HandleFallDamage(pData);
    }

    override void HandleFallDamage(float pHeight)
    {
        PlayerBase player = PlayerBase.Cast(m_Player);
        if (DamageUtils.ShouldBlockFallDamage(player))
            return;
        super.HandleFallDamage(pHeight);
    }
}
