#ifdef EXPANSIONMODAI
class AIZoneController
{
    private ref map<eAIBase, ref map<string, ref ZoneBase>> m_AIActiveZones;
    void AIZoneController()
    {
        m_AIActiveZones = new map<eAIBase, ref map<string, ref ZoneBase>>();
    }
    void Update(float deltaTime)
    {
        if (g_MainConfig && g_MainConfig.DisableAiZoneScanning)
            return;
        array<eAIBase> allAI = eAIBase.eAI_GetAll();
        foreach (eAIBase ai : allAI)
        {
            if (!ai || !ai.IsAlive())
                continue;
            if (!m_AIActiveZones.Contains(ai))
            {
                m_AIActiveZones.Set(ai, new map<string, ref ZoneBase>());
            }
            ref map<string, ref ZoneBase> aiZones = m_AIActiveZones.Get(ai);
            vector pos = ai.GetPosition();
            array<ref ZoneBase> staticZones  = ZoneManager.GetInstance().m_Zones;
            array<ref ZoneBase> dynamicZones = ZoneManager.GetInstance().m_DynamicZones;
            ControlZones(ai, pos, staticZones, aiZones);
            ControlZones(ai, pos, dynamicZones, aiZones);
            DetermineAIState(ai, aiZones);
        }
    }
    void ControlZones(eAIBase ai, vector pos, array<ref ZoneBase> zones, map<string, ref ZoneBase> aiZones)
    {
        foreach (ZoneBase zone : zones)
        {
            string zName = zone.GetName();
            bool isInsideNow = zone.IsInside(pos);
            bool wasInside   = aiZones.Contains(zName);
            if (isInsideNow && !wasInside)
            {
                aiZones[zName] = zone;
            }
            else if (!isInsideNow && wasInside)
            {
                aiZones.Remove(zName);
            }
        }
    }
    void DetermineAIState(eAIBase ai, map<string, ref ZoneBase> aiZones)
    {
        string aiType = ai.GetType();
        if (aiType.Contains("ExpansionQuestNPC") || aiType.Contains("ExpansionP2PTraderAI"))
        {
            ai.SetZoneState(false, false, false, true);
            return;
        }
        ZoneBase basezone;
        int bestPriority = -1;
        foreach (string zName, ZoneBase zone : aiZones)
        {
            if (zone.priority > bestPriority)
            {
                basezone = zone;
                bestPriority = zone.priority;
            }
        }
        if (!basezone)
        {
            bool fallbackPvP = false;
            bool fallbackPvE = false;
            if (g_MainConfig)
            {
                if (g_MainConfig.IsPvPEverywhereActive())
                    fallbackPvP = true;
                else if (g_MainConfig.IsPvEEverywhereActive())
                    fallbackPvE = true;
            }
            ai.SetZoneState(fallbackPvP, fallbackPvE);
            return;
        }
        bool inPvP  = (basezone.type == ZONE_TYPE_PVP);
        bool inPvE  = (basezone.type == ZONE_TYPE_PVE);
        bool inRaid = (basezone.type == ZONE_TYPE_RAID);
        bool inSafe = (basezone.type == ZONE_TYPE_SAFEZONE);
        ai.SetZoneState(inPvP, inPvE, inRaid, inSafe);
    }
}
#endif