modded class ActionRestrainTarget
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() &&  !g_MainConfig.AllowRestrainTargetinPvE)
            return false;
       if (player.netSync_IsInPvPZone && !player.ShouldBypassActionBlock() && !g_MainConfig.AllowRestrainTargetinPvP)
            return false;
        if (player.netSync_IsInRaidMode && !player.ShouldBypassActionBlock() && !g_MainConfig.AllowRestrainTargetinRaid)
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionGiveBloodTarget
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() && g_MainConfig.DisableGiveBloodTargetPvE)
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionForceFeed
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() && g_MainConfig.DisableForceFeedPvE)
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionForceDrink
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() && g_MainConfig.DisableForceDrinkPvE)
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionAttachExplosivesTrigger
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionArmExplosive
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() && g_MainConfig.DisableArmExplosivePvE == 1)
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionActivateTrap
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionCoverHeadTarget
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionDigInStash
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionDismantlePart
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionFoldBaseBuildingObject
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionGagTarget
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionMineTree
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionPackTent
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionRestrainSelf
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionShaveTarget
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionUnlockDoors
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionLockDoors
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionUnmountBarbedWire
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionFoldObject
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionHandcuffTarget
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionTogglePlaceObject
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionTriggerRemotely
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() && g_MainConfig.DisableArmExplosivePvE == 1)
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionDisarmExplosive
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() && g_MainConfig.DisableArmExplosivePvE == 1)
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionDisarmExplosiveWithRemoteDetonator
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() && g_MainConfig.DisableArmExplosivePvE == 1)
            return false;
        return super.ActionCondition(player, target, item);
    }
}
#ifdef RA_BaseBuilding_Scripts
modded class ActionPlaceCurrentBlueprint: ActionPlaceHologram
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        if (player.netSync_IsInNoBuildZone && !player.ShouldBypassActionBlock())
        {
            if (!g_ItemRules || !g_ItemRules.NBItemWhiteList || g_ItemRules.NBItemWhiteList.Find(item.GetType()) == -1)
                return false;
        }
        if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() && g_ItemRules && g_ItemRules.BlockDeployIfPlayerInPvEState && g_ItemRules.BlockDeployIfPlayerInPvEState.Find(item.GetType()) != -1)
            return false;
        if (player.netSync_IsInPvPZone && !player.ShouldBypassActionBlock() && g_ItemRules && g_ItemRules.BlockDeployIfPlayerInPvPState && g_ItemRules.BlockDeployIfPlayerInPvPState.Find(item.GetType()) != -1)
            return false;
        if (player.netSync_IsInRaidMode && !player.ShouldBypassActionBlock() && g_ItemRules && g_ItemRules.BlockDeployIfPlayerInRaidState && g_ItemRules.BlockDeployIfPlayerInRaidState.Find(item.GetType()) != -1)
            return false;
        return super.ActionCondition(player, target, item);
    }
}
#endif
modded class ActionDeployObject
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        #ifdef EXPANSIONMODBASEBUILDING
        ExpansionKitBase kit = ExpansionKitBase.Cast(item);
        if (kit && player.netSync_IsInNoBuildZone && !player.ShouldBypassActionBlock())
        {
            return false;
        }
        #endif
        return super.ActionCondition(player, target, item);
    }
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        PlayerBase player = action_data.m_Player;
        ItemBase item = action_data.m_MainItem;
        if (!player || !item)
        {
            return;
        }
        string notificationMessage = "";
        bool blockAction = false;
        if (player.netSync_IsInNoBuildZone && !player.ShouldBypassActionBlock())
        {
            if (!g_ItemRules || !g_ItemRules.NBItemWhiteList || g_ItemRules.NBItemWhiteList.Find(item.GetType()) == -1)
            {
                notificationMessage = g_MainConfig.NoBuildMessage;
                blockAction = true;
            }
        }
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
        {
            notificationMessage = g_MainConfig.MessageCannotDeployInSafeZone;
            blockAction = true;
        }
        else if (!g_ItemRules)
        {
            notificationMessage = g_MainConfig.MessageItemRulesNotInitialized;
            blockAction = false;
        }
        else if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() &&  g_ItemRules.BlockDeployIfPlayerInPvEState && g_ItemRules.BlockDeployIfPlayerInPvEState.Find(item.GetType()) != -1)
        {
            notificationMessage = FormatMessage(g_MainConfig.MessageBlockedItemDeployInPvE, item.GetType());
            blockAction = true;
        }
        else if (player.netSync_IsInPvPZone && !player.ShouldBypassActionBlock() && g_ItemRules.BlockDeployIfPlayerInPvPState && g_ItemRules.BlockDeployIfPlayerInPvPState.Find(item.GetType()) != -1)
        {
            notificationMessage = FormatMessage(g_MainConfig.MessageBlockedItemDeployInPvP, item.GetType());
            blockAction = true;
        }
        else if (player.netSync_IsInRaidMode && !player.ShouldBypassActionBlock() && g_ItemRules.BlockDeployIfPlayerInRaidState && g_ItemRules.BlockDeployIfPlayerInRaidState.Find(item.GetType()) != -1)
        {
            notificationMessage = FormatMessage(g_MainConfig.MessageBlockedItemDeployInRaid, item.GetType());
            blockAction = true;
        }
        if (blockAction)
        {
            NotifyPlayer(player, notificationMessage);
            if (player.GetActionManager())
            {
                player.GetActionManager().Interrupt();
            }
            action_data.m_Player.PlacingCancelServer();
            action_data.m_MainItem.SetIsBeingPlaced(false);
            GetGame().ClearJunctureEx(player, item);
            return;
        }
    }
    private void NotifyPlayer(PlayerBase player, string message)
    {
        if (player && player.GetIdentity())
        {
            NotificationSystem.Create(new StringLocaliser(message), new StringLocaliser(""), "NinjinsPvPPvE/gui/error.edds", COLOR_RED, 5.0, player.GetIdentity());
        }
    }
}
modded class ActionPushCar
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
modded class ActionPushBoat
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
            return false;
        return super.ActionCondition(player, target, item);
    }
}
#ifdef HDSN_BreachingCharge
modded class HDSN_ActionDeployBreachingCharge
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        PlayerBase player = action_data.m_Player;
        ItemBase item = action_data.m_MainItem;
        if (!player || !item)
        {
            return;
        }
        string notificationMessage = "";
        bool blockAction = false;
        if (player.netSync_IsInSafeZone && !player.ShouldBypassActionBlock())
        {
            notificationMessage = g_MainConfig.MessageCannotDeployInSafeZone;
            blockAction = true;
        }
        else if (!g_ItemRules)
        {
            notificationMessage = g_MainConfig.MessageItemRulesNotInitialized;
            blockAction = false;
        }
        else if (player.netSync_IsInPvEZone && !player.ShouldBypassActionBlock() &&  g_ItemRules.BlockDeployIfPlayerInPvEState && g_ItemRules.BlockDeployIfPlayerInPvEState.Find(item.GetType()) != -1)
        {
            notificationMessage = FormatMessage(g_MainConfig.MessageBlockedItemDeployInPvE, item.GetType());
            blockAction = true;
        }
        else if (player.netSync_IsInPvPZone && !player.ShouldBypassActionBlock() && g_ItemRules.BlockDeployIfPlayerInPvPState && g_ItemRules.BlockDeployIfPlayerInPvPState.Find(item.GetType()) != -1)
        {
            notificationMessage = FormatMessage(g_MainConfig.MessageBlockedItemDeployInPvP, item.GetType());
            blockAction = true;
        }
        else if (player.netSync_IsInRaidMode && !player.ShouldBypassActionBlock() && g_ItemRules.BlockDeployIfPlayerInRaidState && g_ItemRules.BlockDeployIfPlayerInRaidState.Find(item.GetType()) != -1)
        {
            notificationMessage = FormatMessage(g_MainConfig.MessageBlockedItemDeployInRaid, item.GetType());
            blockAction = true;
        }
        if (blockAction)
        {
            NotifyPlayer(player, notificationMessage);
            if (player.GetActionManager())
            {
                player.GetActionManager().Interrupt();
            }
            action_data.m_Player.PlacingCancelServer();
            action_data.m_MainItem.SetIsBeingPlaced(false);
            GetGame().ClearJunctureEx(player, item);
            return;
        }
    }
    private void NotifyPlayer(PlayerBase player, string message)
    {
        if (player && player.GetIdentity())
        {
            NotificationSystem.Create(new StringLocaliser(message), new StringLocaliser(""), "NinjinsPvPPvE/gui/error.edds", COLOR_RED, 5.0, player.GetIdentity());
        }
    }
}
#endif
string FormatMessage(string message, string itemName)
{
    message.Replace("{item}", itemName);
    return message;
}
