/*
---------------------------------------------------------------------
Class for timing related settings
---------------------------------------------------------------------
*/
class NinjinsZoneTimeSettings : Managed
{
    int Year, Month, Day, Hour, Minute;
    void NinjinsZoneTimeSettings(int year = 2000, int month = 1, int day = 1, int hour = 0, int minute = 0)
    {
        Year   = year;
        Month  = month;
        Day    = day;
        Hour   = hour;
        Minute = minute;
    }
    static NinjinsZoneTimeSettings Now()
    {
        int year, month, day, hour, minute;
        GetYearMonthDay(year, month, day);
        GetHourMinuteSecond(hour, minute, NULL);
        return new NinjinsZoneTimeSettings(year, month, day, hour, minute);
    }
    static string GetDayName(int dayIndex)
    {
        if (!g_MainConfig) 
            return "Unknown";
        int startingDay = g_MainConfig.StartingDayOfTheWeek;
        string dayName  = "";
        if (startingDay == 1)
        {
            if (dayIndex == 0) dayName = "Sunday";
            else if (dayIndex == 1) dayName = "Monday";
            else if (dayIndex == 2) dayName = "Tuesday";
            else if (dayIndex == 3) dayName = "Wednesday";
            else if (dayIndex == 4) dayName = "Thursday";
            else if (dayIndex == 5) dayName = "Friday";
            else if (dayIndex == 6) dayName = "Saturday";
        }
        else
        {
            if (dayIndex == 0) dayName = "Monday";
            else if (dayIndex == 1) dayName = "Tuesday";
            else if (dayIndex == 2) dayName = "Wednesday";
            else if (dayIndex == 3) dayName = "Thursday";
            else if (dayIndex == 4) dayName = "Friday";
            else if (dayIndex == 5) dayName = "Saturday";
            else if (dayIndex == 6) dayName = "Sunday";
        }
        return dayName;
    }
    static int GetDayOfWeek()
    {
        int y, m, d;
        GetYearMonthDay(y, m, d);
        int t[] = 
        {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        if (m < 3) y -= 1;
        int dow = (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
        if (!g_MainConfig) 
        {
            return dow;
        }
        int startingDay = g_MainConfig.StartingDayOfTheWeek;
        if (startingDay == 0) 
        {
            dow -= 1;
            if (dow == -1) 
            {
                dow = 6;
            }
        }
        return dow;
    }
}