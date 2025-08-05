#ifdef EXPANSIONMODAI
modded class eAIBase
{
    bool m_eAI_IsInPVPZone  = false;
    bool m_eAI_IsInPVEZone  = false;
    bool m_eAI_IsInRaidZone = false;
    bool m_eAI_IsInSafeZone = false;
    void SetZoneState(bool inPvP, bool inPvE, bool inRaid, bool inSafe)
    {
        if (m_eAI_IsInPVPZone != inPvP || m_eAI_IsInPVEZone != inPvE || m_eAI_IsInRaidZone != inRaid || m_eAI_IsInSafeZone != inSafe)
        {
          NinjinsPvPPvE.LogDebug("[AI] " + ToString()+ " zone changed => PvP="  + inPvP+ "  PvE="  + inPvE+ "  Raid=" + inRaid+ "  Safe=" + inSafe);
        }
        m_eAI_IsInPVPZone  = inPvP;
        m_eAI_IsInPVEZone  = inPvE;
        m_eAI_IsInRaidZone = inRaid;
        m_eAI_IsInSafeZone = inSafe;
    }
    void SetZoneState(bool inPvP, bool inPvE)
    {
        SetZoneState(inPvP, inPvE, false, false);
    }
}
#endif