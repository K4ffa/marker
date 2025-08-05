modded class ActionGetOutTransport
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        HumanCommandVehicle vehCommand = player.GetCommand_Vehicle();
        if (vehCommand)
        {
            Transport trans = vehCommand.GetTransport();
            if (trans)
            {
                int crewIndex = trans.CrewMemberIndex(player);
                bool isCrew = crewIndex >= 0;
                if (!isCrew)
                    return false;
                NoFlightZoneModule noFlightModule = CF_Modules<NoFlightZoneModule>.Get();
                if (noFlightModule)
                {
                    NoVehicleZoneEnforcer enforcer = noFlightModule.GetEnforcer();
                    if (enforcer && g_MainConfig)
                    {
                        int blockDelay = g_MainConfig.NoVehicleZoneExitBlockDelayMS;
                        float currentTime = GetGame().GetTime();
                        if (enforcer.m_PlayerEntryTimes.Contains(player))
                        {
                            float entryTime = enforcer.m_PlayerEntryTimes.Get(player);
                            float elapsed = currentTime - entryTime;
                            if (elapsed >= blockDelay)
                            {
                                string playerName = "Unknown";
                                if (player && player.GetIdentity())
                                {
                                    playerName = player.GetIdentity().GetName();
                                }
                                NinjinsPvPPvE.LogDebug("[ActionGetOutTransport] Blocking exit for player " + playerName + ". Time since entry: " + elapsed + "ms (threshold: " + blockDelay + "ms).");
                                return false;
                            }
                        }
                    }
                }
                return trans.CrewCanGetThrough(crewIndex) && trans.IsAreaAtDoorFree(crewIndex);
            }
        }
        return false;
    }
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        PlayerBase player = action_data.m_Player;
        string playerName = "Unknown";
        if (player && player.GetIdentity())
        {
            playerName = player.GetIdentity().GetName();
        }
        NinjinsPvPPvE.LogDebug("[ActionGetOutTransport] Player " + playerName + " is attempting to exit a vehicle.");
        NoFlightZoneModule noFlightModule = CF_Modules<NoFlightZoneModule>.Get();
        if (noFlightModule)
        {
            NoVehicleZoneEnforcer enforcer = noFlightModule.GetEnforcer();
            if (enforcer)
            {
                NinjinsPvPPvE.LogDebug("[ActionGetOutTransport] NoVehicleZoneEnforcer found. Processing exit cleanup.");
                enforcer.OnPlayerExitTransport(player);
            }
            else
            {
                NinjinsPvPPvE.LogWarning("[ActionGetOutTransport] NoVehicleZoneEnforcer not found!");
            }
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[ActionGetOutTransport] NoFlightZoneModule not found!");
        }
    }
}
