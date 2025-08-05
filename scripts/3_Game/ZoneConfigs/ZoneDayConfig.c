class ZoneDayConfigHelper
{
    static array<ref DayConfig> CreateDefaultDayConfigs()
    {
        array<ref DayConfig> configs = new array<ref DayConfig>();
        configs.Insert(new DayConfig("Monday"));
        configs.Insert(new DayConfig("Tuesday"));
        configs.Insert(new DayConfig("Wednesday"));
        configs.Insert(new DayConfig("Thursday"));
        configs.Insert(new DayConfig("Friday"));
        configs.Insert(new DayConfig("Saturday"));
        configs.Insert(new DayConfig("Sunday"));
        return configs;
    }   
    static array<ref DayConfig> CreateDayConfigs(int startHour = 0, int endHour = 24)
    {
        array<ref DayConfig> configs = new array<ref DayConfig>();
        configs.Insert(new DayConfig("Monday", startHour, endHour));
        configs.Insert(new DayConfig("Tuesday", startHour, endHour));
        configs.Insert(new DayConfig("Wednesday", startHour, endHour));
        configs.Insert(new DayConfig("Thursday", startHour, endHour));
        configs.Insert(new DayConfig("Friday", startHour, endHour));
        configs.Insert(new DayConfig("Saturday", startHour, endHour));
        configs.Insert(new DayConfig("Sunday", startHour, endHour));
        return configs;
    }  
    static void SetupZoneDayConfigs(ZoneBase zone, int startHour = 0, int endHour = 24)
    {
        zone.dayConfigs = CreateDayConfigs(startHour, endHour);
    }
    static void UpgradeLegacy(DynamicZones zone)
    {
        if (!zone) 
            return;
        if (zone.dayConfigs && zone.dayConfigs.Count() > 0) 
            return;

        array<ref DayConfig> cfgs = new array<ref DayConfig>();
        array<string> list       = new array<string>();
        if (zone.days != "") zone.days.Split(" ", list);

        if (list.Count() == 0)
        {
            cfgs = CreateDefaultDayConfigs();
        }
        else
        {
            foreach (string dName : list)
            {
                cfgs.Insert(new DayConfig(dName, zone.startHour, zone.endHour));
            }
        }
        zone.dayConfigs = cfgs;
    }
    static void UpgradeLegacy(ZoneBase zone)
    {
        if (!zone) 
            return;
        if (zone.dayConfigs && zone.dayConfigs.Count() > 0) 
            return;

        array<ref DayConfig> cfgs = new array<ref DayConfig>();
        array<string> list       = new array<string>();
        if (zone.days != "") zone.days.Split(" ", list);

        if (list.Count() == 0)
        {
            cfgs = CreateDefaultDayConfigs();
        }
        else
        {
            foreach (string dName : list)
            {
                cfgs.Insert(new DayConfig(dName, zone.startHour, zone.endHour));
            }
        }
        zone.dayConfigs = cfgs;
    }
}
