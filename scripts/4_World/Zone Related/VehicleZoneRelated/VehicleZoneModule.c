[CF_RegisterModule(NoFlightZoneModule)]
class NoFlightZoneModule : CF_ModuleWorld
{
    static ref NoFlightZoneModule g_NoFlightZoneModule;
    private ref NoVehicleZoneEnforcer m_NoVehicleZoneEnforcer;
    override void OnInit()
    {
        super.OnInit();
        g_NoFlightZoneModule = this;
        EnableMissionStart();
        EnableInvokeConnect();
    }
    override void OnMissionStart(Class sender, CF_EventArgs args)
    {
        super.OnMissionStart(sender, args);
        if (GetGame().IsServer())
        {
            m_NoVehicleZoneEnforcer = new NoVehicleZoneEnforcer();
            NinjinsPvPPvE.LogDebug("-------------------------------------");
            NinjinsPvPPvE.LogDebug("---- VehicleZoneEnforcer Init -------");
            NinjinsPvPPvE.LogDebug("-------------------------------------");
            NinjinsPvPPvE.LogDebug("NoVehicleZoneEnforcer initialized.");
        }
    }
    NoVehicleZoneEnforcer GetEnforcer()
    {
        return m_NoVehicleZoneEnforcer;
    }
}
