modded class ActionGetInTransport
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        NinjinsPvPPvE.LogDebug("[ActionGetInTransport] Player " + action_data.m_Player.GetIdentity().GetName() + " is attempting to enter a vehicle.");
        NoFlightZoneModule noFlightModule = CF_Modules<NoFlightZoneModule>.Get();
        if (noFlightModule && noFlightModule.GetEnforcer())
        {
            NinjinsPvPPvE.LogDebug("[ActionGetInTransport] NoVehicleZoneEnforcer found. Processing entry.");
            noFlightModule.GetEnforcer().OnPlayerGetInTransport(action_data.m_Player);
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[ActionGetInTransport] NoVehicleZoneEnforcer not found!");
        }
    }
}
