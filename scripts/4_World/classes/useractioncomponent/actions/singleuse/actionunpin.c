modded class ActionUnpin
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player && player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
        {
            NinjinsPvPPvE.LogDebug(" [SafeZone] Preventing grenade unpin for: " + player.GetIdentity().GetName());
            return false;
        }
        return super.ActionCondition(player, target, item);
    }
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        PlayerBase player = action_data.m_Player;
        Grenade_Base grenade = Grenade_Base.Cast(action_data.m_MainItem);
        if (grenade && player)
        {
            grenade.SetThrower(player);
            NinjinsPvPPvE.LogDebug(" [ActionUnpin] Grenade thrower set to: " + player.GetIdentity().GetName());
        }
        else
        {
            if (!grenade)
            {
                NinjinsPvPPvE.LogWarning(" [ActionUnpin] Grenade is null.");
            }
            if (!player)
            {
                NinjinsPvPPvE.LogWarning(" [ActionUnpin] Player is null.");
            }
        }
    }
}
