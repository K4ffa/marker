class LockPickManager {
    private static ref map<string, string> m_ZoneLockpickerMap = new map<string, string>();
    static void SetLockpicker(string zoneName, string lockpickerID) 
    {
        if (m_ZoneLockpickerMap.Contains(zoneName)) 
        {
            m_ZoneLockpickerMap.Set(zoneName, lockpickerID);
        } 
        else 
        {
            m_ZoneLockpickerMap.Insert(zoneName, lockpickerID);
        }
    }
    static string GetLockpicker(string zoneName) 
    {
        string lockpickerID;
        if (m_ZoneLockpickerMap.Find(zoneName, lockpickerID)) 
        {
            return lockpickerID;
        }
        return "";
    }
    static void RemoveLockpicker(string zoneName) 
    {
        if (m_ZoneLockpickerMap.Contains(zoneName)) 
        {
            m_ZoneLockpickerMap.Remove(zoneName);
        }
    }
    static void ClearAllLockpickers() 
    {
        m_ZoneLockpickerMap.Clear();
    }
}
