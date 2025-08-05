#ifdef NAMALSK_SURVIVAL
modded class EVRStorm : NamWeatherEvent
{
    override void OnEVRFinished(notnull SurvivorBase player)
    {
        if (g_MainConfig && g_MainConfig.EVRStormSZNoShock && player.netSync_IsInSafeZone)
        {
            return;
        }
        super.OnEVRFinished(player);
    }
}
#endif
