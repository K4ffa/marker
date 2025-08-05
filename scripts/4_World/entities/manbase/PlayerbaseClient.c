#ifndef SERVER
modded class PlayerBaseClient
{
    protected float m_ClientAFKTimer = GetGame().GetTickTime();
    protected int m_AFK_Timeout;
    protected bool m_EnableAFKKick;
    protected bool m_HalfwayNotificationSent = false;
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);
        if (rpc_type == NinjinCustomRPCs.RPC_SYNC_AFK_SETTINGS)
        {
            Param2<int, bool> param;
            if (ctx.Read(param))
            {
                m_AFK_Timeout = param.param1;
                m_EnableAFKKick = param.param2;
            }
            return;
        }
        if (rpc_type == NinjinCustomRPCs.RPC_FORCE_RELOG)
        {
            Param1<string> p;
            if (ctx.Read(p))
            {
                Mission m = GetGame().GetMission();
                if (m)
                {
                    m.AbortMission();
                    ErrorModuleHandler.ThrowError(ErrorCategory.ClientKicked,EClientKicked.KICK,p.param1 );
                }
            }
            return;
        }
    }
    protected void ResetAFKTimer()
    {
        if (!m_EnableAFKKick)
            return;
        m_ClientAFKTimer = GetGame().GetTickTime();
    }
    override void OnStanceChange(int previousStance, int newStance)
    {
        super.OnStanceChange(previousStance, newStance);
        ResetAFKTimer();
    }
    override void OnMovementChanged()
    {
        super.OnMovementChanged();
        ResetAFKTimer();
    }
    override void OnInventoryMenuOpen()
    {
        super.OnInventoryMenuOpen();
        ResetAFKTimer();
    }
    override void OnInventoryMenuClose()
    {
        super.OnInventoryMenuClose();
        ResetAFKTimer();
    }
    override bool ModCommandHandlerBefore(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
    {
        if (!m_EnableAFKKick)
            return super.ModCommandHandlerBefore(pDt, pCurrentCommandID, pCurrentCommandFinished);
        vector aim_change = GetInputController().GetAimChange();
        if (aim_change != vector.Zero)
        {
            ResetAFKTimer();
        }
        if (pCurrentCommandFinished)
        {
            ResetAFKTimer();
        }
        return super.ModCommandHandlerBefore(pDt, pCurrentCommandID, pCurrentCommandFinished);
    }
    override bool ModCommandHandlerAfter(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
    {
        if (!m_EnableAFKKick)
            return super.ModCommandHandlerAfter(pDt, pCurrentCommandID, pCurrentCommandFinished);
        float currentTime = GetGame().GetTickTime();
        float diff = currentTime - m_ClientAFKTimer;
        float halfTimeout = m_AFK_Timeout / 2.0;
        if (!m_IsAdmin)
        {
            if (diff >= halfTimeout && diff < m_AFK_Timeout)
            {
                if (!m_HalfwayNotificationSent)
                {
                    NotificationSystem.Create(new StringLocaliser("AFK Warning"),new StringLocaliser("You have been AFK for " + halfTimeout + " seconds. Stay active to avoid being kicked soon."),"NinjinsPvPPvE/gui/alarm.edds",ARGB(255, 255, 255, 0),5.0,GetIdentity());
                    m_HalfwayNotificationSent = true;
                }
            }
            if (diff < halfTimeout)
            {
                m_HalfwayNotificationSent = false;
            }
        }
        if (diff > m_AFK_Timeout && KickWhenAFK())
        {
            Mission mission = GetGame().GetMission();
            if (mission)
            {
                mission.AbortMission();
                ErrorModuleHandler.ThrowError(ErrorCategory.ClientKicked, EClientKicked.KICK, string.Format("You have been AFK for more than %1s!", m_AFK_Timeout));
            }
        }
        return super.ModCommandHandlerAfter(pDt, pCurrentCommandID, pCurrentCommandFinished);
    }
    protected bool KickWhenAFK()
    {
        if (!GetGame())
            return false;
        if (!m_EnableAFKKick)
            return false;
        if (m_IsAdmin)
            return false;
        if (!this || !m_PlayerSelected)
            return false;
        if (!m_MovementState || m_MovementState.m_LocalMovement == -1)
            return false;
        if (m_MovementState.m_LocalMovement != DayZPlayerConstants.MOVEMENTIDX_IDLE)
            return false;
        if (!GetGame().IsMultiplayer())
            return false;
        return true;
    }
}
#endif
