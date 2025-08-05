/*
---------------------------------------------------------------------
Register the custom raider action
---------------------------------------------------------------------
*/
modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
        actions.Insert(ActionAddRaidingPlayer);
    }
}
/*
---------------------------------------------------------------------
Add Self to Allowed Raiding Players
---------------------------------------------------------------------
*/
class ActionAddRaidingPlayer : ActionInteractBase
{
    static const int RAIDER_DIALOG_ID = 7654321;
    private ref UIScriptedMenu m_Dialog;
    void ActionAddRaidingPlayer()
    {
        m_Text = "Add Me as Raiding Player";
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
    }
    override void CreateConditionComponents()
    {
        m_ConditionTarget = new CCTObject(2.0);
        m_ConditionItem = new CCINone();
    }
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!player || !g_MainConfig)
        {
            NinjinsPvPPvE.LogDebug("[RaiderAction] Invalid player or config.");
            return false;
        }
        if (g_MainConfig.DisableRaidingDialogActionOnFlagPole)
        {
            NinjinsPvPPvE.LogDebug("[RaiderAction] Action disabled by config.");
            return false;
        }
        Object targetObj = target.GetObject();
        if (!targetObj)
        {
            NinjinsPvPPvE.LogDebug("[RaiderAction] No target object.");
            return false;
        }
        TerritoryFlag flag = TerritoryFlag.Cast(targetObj);
        if (!flag)
        {
            NinjinsPvPPvE.LogDebug("[RaiderAction] Target is not a TerritoryFlag: " + targetObj.GetType());
            return false;
        }
        PlayerIdentity identity = player.GetIdentity();
        if (!identity)
        {
            NinjinsPvPPvE.LogDebug("[RaiderAction] Player identity null.");
            return false;
        }
        string guid = identity.GetId();
        foreach (string id : g_MainConfig.AllowedRaidingPlayers)
        {
            if (id == guid)
            {
                NinjinsPvPPvE.LogDebug("[RaiderAction] Player " + guid + " already in AllowedRaidingPlayers.");
                return false;
            }
        }
        NinjinsPvPPvE.LogDebug("[RaiderAction] Action is valid and will be shown.");
        return true;
    }
    override void OnStartClient(ActionData action_data)
    {
        super.OnStartClient(action_data);
        m_Dialog = new ActionAddRaidingPlayerDialog();
        GetGame().GetUIManager().ShowDialog("Add Me as Raiding Player?","Are you sure you want to register yourself as a raider?",RAIDER_DIALOG_ID,DBT_YESNO,DBB_NO,DMT_QUESTION,m_Dialog);
    }
}
/*
---------------------------------------------------------------------
Raider Confirmation Dialog
---------------------------------------------------------------------
*/
class ActionAddRaidingPlayerDialog : UIScriptedMenu
{
    override bool OnModalResult(Widget w, int x, int y, int code, int result)
    {
        NinjinsPvPPvE.LogDebug("ActionAddRaidingPlayerDialog.OnModalResult: code=" + code.ToString() + ", result=" + result.ToString());
        if (code == ActionAddRaidingPlayer.RAIDER_DIALOG_ID)
        {
            if (result == DBB_YES)
            {
                NinjinsPvPPvE.LogDebug("[RaiderDialog] User confirmed raider addition. Preparing RPC.");
                PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
                if (player && player.GetIdentity())
                {
                    string playerName = player.GetIdentity().GetName();
                    string playerGuid = player.GetIdentity().GetId();
                    string playerEntry = playerName + ":" + playerGuid;
                    NinjinsPvPPvE.LogDebug("[RaiderDialog] Sending RPC with player entry: " + playerEntry);
                    Param1<string> data = new Param1<string>(playerEntry);
                    GetRPCManager().SendRPC("NinjinsPvPPvE", "AddRaidingPlayerServer", data, true);
                }
                else
                {
                    NinjinsPvPPvE.LogWarning("[RaiderDialog] Could not find player or identity.");
                }
            }
            else
            {
                NinjinsPvPPvE.LogDebug("[RaiderDialog] User cancelled raider addition.");
            }
            return true;
        }
        return false;
    }
}
