class NinjinsPvPPvE
{
    private static FileHandle m_LogFile;
    private static string m_LogFilePath;
    static int m_LogLevel = 1;
    static int GetLogLevel()
    {
        return m_LogLevel;
    }
    static void InitLogFile()
    {
        if (m_LogLevel == 0)
            return;
        CheckDirectories();
        m_LogFilePath = NinjinsPvPPvE_LOGGER_LOG_FILE;
        m_LogFilePath.Replace("%1", GetDateTime());
        m_LogFile = OpenFile(m_LogFilePath, FileMode.APPEND);
        if (m_LogFile) 
        {
            Print("[NinjinsPvPPvE] Log file initialized: " + m_LogFilePath);
            FPrintln(m_LogFile, "[" + GetTime() + "] [Init] Log file created for this session.");
            CloseFile(m_LogFile);
            m_LogFile = null;
        }
        else
        {
            Print("[NinjinsPvPPvE ERROR] Failed to initialize log file: " + m_LogFilePath);
        }
    }
    static void CheckDirectories()
    {
        if (!FileExist(NinjinsPvPPvE_ROOT_FOLDER))
        {
            bool rootCreated = MakeDirectory(NinjinsPvPPvE_ROOT_FOLDER);
            if (rootCreated)
            {
                LogDebug("Created root directory: " + NinjinsPvPPvE_ROOT_FOLDER);
            }
            else
            {
                LogCritical("Failed to create root directory: " + NinjinsPvPPvE_ROOT_FOLDER);
            }
        }
        if (!FileExist(NinjinsPvPPvE_LOG_FOLDER))
        {
            bool logFolderCreated = MakeDirectory(NinjinsPvPPvE_LOG_FOLDER);
            if (logFolderCreated)
            {
                LogDebug("Created logging folder: " + NinjinsPvPPvE_LOG_FOLDER);
            }
            else
            {
                LogCritical("Failed to create logging folder: " + NinjinsPvPPvE_LOG_FOLDER);
            }
        }
        if (!FileExist(NinjinsPvPPvE_LOGGER_LOG_DIR))
        {
            bool logsCreated = MakeDirectory(NinjinsPvPPvE_LOGGER_LOG_DIR);
            if (logsCreated)
            {
                LogDebug("Created logs directory: " + NinjinsPvPPvE_LOGGER_LOG_DIR);
            }
            else
            {
                LogCritical("Failed to create logs directory: " + NinjinsPvPPvE_LOGGER_LOG_DIR);
            }
        }
    }
    static void SetLogLevel(int logLevel)
    {
        if (m_LogLevel == logLevel)
            return;
        m_LogLevel = logLevel;
        Print("[DEBUG] NinjinsPvPPvE called. m_LogLevel set to: " + m_LogLevel);
    }
    static void Log(int level, string message)
    {
        if (m_LogLevel == 0)
            return;
        bool shouldLog = false;
        if (m_LogLevel == 6) 
        {
            shouldLog = true;
        } else if (m_LogLevel == 5 && level == 5) 
        {
            shouldLog = true;
        } else if (level <= m_LogLevel) 
        {
            shouldLog = true;
        }
        if (!shouldLog)
            return;
        string logMessage = "[" + GetTime() + "] [Level " + level.ToString() + "] " + message;
        if (m_LogLevel == 0)
            return;
        CheckDirectories();
        if (m_LogFilePath == "") 
        {
            m_LogFilePath = NinjinsPvPPvE_LOGGER_LOG_FILE;
            m_LogFilePath.Replace("%1", GetDateTime());
        }
        FileHandle tempLogFile = OpenFile(m_LogFilePath, FileMode.APPEND);
        if (tempLogFile) 
        {
            FPrintln(tempLogFile, logMessage);
            CloseFile(tempLogFile);
        } 
        else 
        {
            Print("[ERROR] Could not open log file: " + m_LogFilePath);
        }
    }
    static void LogCritical(string message) 
    {   Log(1, "[Critical] " + message); }
    static void LogWarning(string message)  {   Log(2, "[Warning] " + message);  }
    static void LogInfo(string message)     {   Log(3, "[Info ] " + message);     }
    static void LogDebug(string message)    {   Log(4, "[Debug] " + message);    }
    static void LogKillsDamage(string message) 
    { Log(5, "[Kills/Damage] " + message); }
    static void LogEverything(string message)  { Log(6, "[Everything] " + message); }
    static void CloseLogFile()
    {
        if (m_LogFile)
        {
            CloseFile(m_LogFile);
            m_LogFile = null;
            Print("[DEBUG] Log file closed.");
        }
    }
    private static string GetDateTime()
    {
        int year, month, day, hour, minute, second;
        GetYearMonthDay(year, month, day);
        GetHourMinuteSecond(hour, minute, second);
        string dateTime = year.ToString() + "-";
        if (month < 10) dateTime += "0";
        dateTime += month.ToString() + "-";
        if (day < 10) dateTime += "0";
        dateTime += day.ToString() + "_";
        if (hour < 10) dateTime += "0";
        dateTime += hour.ToString() + "-";
        if (minute < 10) dateTime += "0";
        dateTime += minute.ToString() + "-";
        if (second < 10) dateTime += "0";
        dateTime += second.ToString();
        return dateTime;
    }
    private static string GetTime()
    {
        int hour, minute, second;
        GetHourMinuteSecond(hour, minute, second);
        string time = "";
        if (hour < 10) time += "0";
        time += hour.ToString() + ":";
        if (minute < 10) time += "0";
        time += minute.ToString() + ":";
        if (second < 10) time += "0";
        time += second.ToString();
        return time;
    }
}
