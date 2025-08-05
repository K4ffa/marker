 modded class DayZPlayerImplement
 {
    private bool m_LastForceFirstPerson = false;
    private bool m_LastBlockedRaise = false;
    override void HandleView()
    {
        super.HandleView();
        PlayerBase player = PlayerBase.Cast(this);
        if (player)
        {
            bool currentForceFirstPerson = player.IsForceFirstPerson();
            if (currentForceFirstPerson != m_LastForceFirstPerson)
            {
                if (currentForceFirstPerson)
                {
                NinjinsPvPPvE.LogDebug("Enforcing first-person view due to active zone or global setting.");
                }
                m_LastForceFirstPerson = currentForceFirstPerson;
            }
            if (currentForceFirstPerson)
            {
                m_Camera3rdPerson = false;
            }
        }
    }
    override void HandleWeapons(float pDt, Entity pInHands, HumanInputController pInputs, out bool pExitIronSights)
    {
        super.HandleWeapons(pDt, pInHands, pInputs, pExitIronSights);
        PlayerBase player = PlayerBase.Cast(this);
        if (!player) 
        return;
        bool isTryingToRaise = pInputs.IsWeaponRaised();
        bool hasWeapon = pInHands && (pInHands.IsWeapon() || pInHands.IsMeleeWeapon());
        if (player.netSync_IsInSafeZone && hasWeapon)
        {
            if (isTryingToRaise && player.GetCommand_Action())
            {
                player.GetCommand_Action().Cancel();
            }
            if (player.GetCommand_Melee())
            {
                player.GetCommand_Melee().Cancel();
            }
            if (!m_LastBlockedRaise)
            {
                m_LastBlockedRaise = true;
            }
        }
        else if (m_LastBlockedRaise && (!isTryingToRaise || !hasWeapon))
        {
        m_LastBlockedRaise = false;
        }
    }
 }
