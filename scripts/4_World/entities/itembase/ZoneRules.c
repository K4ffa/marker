class ZoneRules
{
    static int GetZoneTypeAtPosition(vector pos)
    {
        int zoneType = -1;
        bool zoneDetected = false;
        if (IsInsideZones(pos, ZoneManager.GetInstance().m_Zones, zoneType))
        {
            zoneDetected = true;
        }
        else if (IsInsideZones(pos, ZoneManager.GetInstance().m_DynamicZones, zoneType))
        {
            zoneDetected = true;
        }
        if (!zoneDetected && g_MainConfig)
        {
            if (g_MainConfig.IsPvEEverywhereActive())
            {
                zoneType = ZONE_TYPE_PVE;
            }
            else if (g_MainConfig.IsPvPEverywhereActive())
            {
                zoneType = ZONE_TYPE_PVP;
            }
        }
        return zoneType;
    }
    private static bool IsInsideZones(vector pos, array<ref ZoneBase> zones, out int zoneType)
    {
        foreach (ZoneBase zone : zones)
        {
            if (zone.IsInside(pos))
            {
                zoneType = zone.type;
                return true;
            }
        }
        return false;
    }
    static bool IsInsideFireplace(vector pos)
    {
        array<Object> nearbyObjects = new array<Object>;
        GetGame().GetObjectsAtPosition(pos, 2.0, nearbyObjects, NULL);
        foreach (Object obj : nearbyObjects)
        {
            if (FireplaceBase.Cast(obj))
            {
                return true;
            }
        }
        return false;
    }
    static bool ShouldBlockAmmo(vector pos)
    {
        int zoneType = GetZoneTypeAtPosition(pos);
        return zoneType == ZONE_TYPE_PVE && IsInsideFireplace(pos);
    }
    static bool ShouldExplodeInZone(vector pos, PlayerBase thrower)
    {
        int zoneType = GetZoneTypeAtPosition(pos);
        bool insideFireplace = IsInsideFireplace(pos);
        string throwerName = "null";
        bool isInPvE = false;
        bool isInPvP = false;
        bool isInRaid = false;
        if (thrower)
        {
            isInPvE = thrower.netSync_IsInPvEZone;
            isInPvP = thrower.netSync_IsInPvPZone;
            isInRaid = thrower.netSync_IsInRaidMode;
            if (thrower.GetIdentity())
                throwerName = thrower.GetIdentity().GetName();
        }
        NinjinsPvPPvE.LogDebug("[ZoneRules] Explosion Check: pos=" + pos.ToString() + ", zoneType=" + zoneType + ", insideFireplace=" + insideFireplace + ", thrower=" + throwerName);
        if (insideFireplace && (zoneType == ZONE_TYPE_PVP || zoneType == ZONE_TYPE_RAID))
            return true;
        if (zoneType == ZONE_TYPE_PVE)
        {
            if (!thrower)
            {
                NinjinsPvPPvE.LogDebug("[ZoneRules] No thrower detected, blocking explosion in PvE.");
                return false;
            }
            NinjinsPvPPvE.LogDebug("[ZoneRules] PvE zone: thrower isInPvE=" + isInPvE);
            return isInPvE;
        }
        if (zoneType == ZONE_TYPE_PVP)
        {
            if (!thrower)
            {
                NinjinsPvPPvE.LogDebug("[ZoneRules] No thrower detected, allowing explosion in PvP.");
                return true;
            }
            NinjinsPvPPvE.LogDebug("[ZoneRules] PvP zone: thrower isInPvP=" + isInPvP);
            return isInPvP;
        }
        if (zoneType == ZONE_TYPE_RAID)
        {
            if (!thrower)
            {
                NinjinsPvPPvE.LogDebug("[ZoneRules] No thrower detected, allowing explosion in Raid.");
                return true;
            }
            NinjinsPvPPvE.LogDebug("[ZoneRules] Raid zone: thrower isInRaidMode=" + isInRaid);
            return isInRaid;
        }
        if (zoneType == ZONE_TYPE_VISUAL)
        {
            if (!thrower)
            {
                NinjinsPvPPvE.LogDebug("[ZoneRules] No thrower detected in Visual/NoBuild zone, blocking explosion.");
                return false;
            }
            bool globalPvPActive = g_MainConfig && g_MainConfig.IsPvPEverywhereActive();
            bool globalPvEActive = g_MainConfig && g_MainConfig.IsPvEEverywhereActive();
            NinjinsPvPPvE.LogDebug("[ZoneRules] Visual/NoBuild zone: thrower PvE=" + isInPvE + ", PvP=" + isInPvP + ", globalPvE=" + globalPvEActive + ", globalPvP=" + globalPvPActive);
            if (isInPvE && globalPvEActive)
                return true;
            if (isInPvP && globalPvPActive)
                return true;
            NinjinsPvPPvE.LogDebug("[ZoneRules] Visual/NoBuild zone explosion blocked due to unmatched global state.");
            return false;
        }
        NinjinsPvPPvE.LogDebug("[ZoneRules] Unknown zoneType, blocking by default.");
        return false;
    }
}
