modded class DayZPlayerImplementThrowing
{
    override void HandleThrowing(HumanInputController pHic, HumanCommandWeapons pHcw, EntityAI pEntityInHands, float pDt)
    {
        PlayerBase player = PlayerBase.Cast(m_Player);
        if (!player)
        {
            super.HandleThrowing(pHic, pHcw, pEntityInHands, pDt);
            return;
        }
        if (player.netSync_IsInSafeZone)
        {
            bool canThrow = false;
            if (pEntityInHands)
            {
                if (pEntityInHands.IsInherited(Grenade_Base))
                {
                    string grenadeType = pEntityInHands.GetType();
                    if (g_ItemRules && g_ItemRules.BypassZoneChecksGrenades.Find(grenadeType) != -1)
                    {
                        canThrow = true;
                    }
                }
                #ifdef TraderPlus
                if (pEntityInHands.IsInherited(ReceiptBase) || pEntityInHands.IsInherited(NewReceiptBase))
                {
                    canThrow = true;
                }
                #endif
            }
            if (!canThrow)
            {
                if (m_bThrowingModeEnabled)
                {
                    m_bThrowingModeEnabled = false;
                    ResetState();
                    pHcw.SetActionProgressParams(0, 0);
                    pHcw.SetThrowingMode(false);
                }
                return;
            }
        }
        if (pEntityInHands && pEntityInHands.IsInherited(Grenade_Base))
        {
            Grenade_Base grenade = Grenade_Base.Cast(pEntityInHands);
            if (grenade)
            {
                grenade.SetThrower(player);
            }
        }
        super.HandleThrowing(pHic, pHcw, pEntityInHands, pDt);
    }
}
