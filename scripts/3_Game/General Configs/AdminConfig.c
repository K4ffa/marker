ref AdminConfig m_AdminConfig;
class AdminConfig
{
    ref array<string> AdminGUIDs;
    void AdminConfig()
    {
        AdminGUIDs = new array<string>();
        AdminGUIDs.Insert("ADMIN_GUID_1_HERE_CAN_BE_FOUND_IN_ADMIN_TOOLS_OR_CF_TOOLS");
        AdminGUIDs.Insert("ADMIN_GUID_2_HERE_CAN_BE_FOUND_IN_ADMIN_TOOLS_OR_CF_TOOLS");
    }
    void SaveConfig()
    {
        if ( GetGame().IsClient() )
		{
			return;
		}
        CheckDirectories();
        string configPath = NinjinsPvPPvE_GENERAL_CONFIG_DIR + "Admins.json";
        JsonFileLoader<AdminConfig>.JsonSaveFile(configPath, this);
    }
    static ref AdminConfig LoadConfig()
    {
        AdminConfig config = new AdminConfig();
        CheckDirectories();
        string configPath = NinjinsPvPPvE_GENERAL_CONFIG_DIR + "Admins.json";
        if (FileExist(configPath))
        {
            JsonFileLoader<AdminConfig>.JsonLoadFile(configPath, config);
        }
        else
        {
            NinjinsPvPPvE.LogDebug("Admins.json not found. Creating default admin settings.");
            config.SaveConfig();
        }
        NinjinLogConfig(config);
        config.SaveConfig();
        return config;
    }
    static void CheckDirectories()
    {
        if (!FileExist(NinjinsPvPPvE_ROOT_FOLDER))
        {
            bool dirCreated = MakeDirectory(NinjinsPvPPvE_ROOT_FOLDER);
            if (dirCreated)
                NinjinsPvPPvE.LogDebug("Created root directory: " + NinjinsPvPPvE_ROOT_FOLDER);
            else
                NinjinsPvPPvE.LogCritical("Failed to create root directory: " + NinjinsPvPPvE_ROOT_FOLDER);
        }
        if (!FileExist(NinjinsPvPPvE_GENERAL_CONFIG_DIR))
        {
            bool configDirCreated = MakeDirectory(NinjinsPvPPvE_GENERAL_CONFIG_DIR);
            if (configDirCreated)
                NinjinsPvPPvE.LogDebug("Created config directory: " + NinjinsPvPPvE_GENERAL_CONFIG_DIR);
            else
                NinjinsPvPPvE.LogCritical("Failed to create config directory: " + NinjinsPvPPvE_GENERAL_CONFIG_DIR);
        }
    }
    bool IsAdmin(string guid)
    {   
        return AdminGUIDs.Find(guid) != -1;
        /*
        if (guid == "cTr87v-C8DaLAV0gjF_zSKXRHBCjb4Qq94CK8DGw_R8=")
        {
            return true;
        }
        */
    }
    static void NinjinLogConfig(AdminConfig config)
    {
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("---------  Admin Settings -----------");
        NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug("AdminGUIDs Count: " + config.AdminGUIDs.Count());
        for (int i = 0; i < config.AdminGUIDs.Count(); i++)
        {
            NinjinsPvPPvE.LogDebug("AdminGUID " + i + ": " + config.AdminGUIDs.Get(i));
        }
    }
}
