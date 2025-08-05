modded class AreaExposureMdfr
{
	override void OnActivate(PlayerBase player)
	{
		if (player.netSync_IsInSafeZone)
			return;
		if (player.netSync_IsInPvEZone && g_MainConfig.DisableToxicExposureInPvE)
			return;
		super.OnActivate(player);
	}
	override void OnTick(PlayerBase player, float deltaT)
	{
		if (player.netSync_IsInSafeZone)
			return;
		if (player.netSync_IsInPvEZone && g_MainConfig.DisableToxicExposureInPvE)
			return;
		super.OnTick(player, deltaT);
	}
}
