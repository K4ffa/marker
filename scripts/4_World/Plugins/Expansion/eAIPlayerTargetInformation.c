#ifdef EXPANSIONMODAI
modded class eAIPlayerTargetInformation
{
	override float CalculateThreat(eAIBase ai = null)
	{
		if (g_MainConfig && g_MainConfig.DisableAiZoneScanning)
		{
			if (ai && ai.m_eAI_IsInSafeZone)
			{
				return 0.0;
			}
			PlayerBase player = PlayerBase.Cast(m_Player);
			if (player && player.netSync_IsInSafeZone)
			{
				return 0.0;
			}
		}
		else
		{
			string type = m_Player.GetType();
			if (type.Contains("ExpansionQuestNPC") || type.Contains("ExpansionP2PTraderAI"))
			{
				return super.CalculateThreat(ai);
			}
			ZoneManager zm = ZoneManager.GetInstance();
			if (zm && zm.IsPositionInZone(m_Player.GetPosition(), ZONE_TYPE_SAFEZONE))
			{
				return 0.0;
			}
		}
		return super.CalculateThreat(ai);
	}
}
#endif
