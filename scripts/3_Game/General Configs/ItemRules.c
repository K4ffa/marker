ref ItemRules g_ItemRules;
class ItemRules
{
    ref array<string> CantBeDamagedOnGround;
    ref array<string> CantBeDamagedInPvE;
    ref array<string> CantBeDamagedInPvP;
    ref array<string> SZItemWhiteList;
    ref array<string> NBItemWhiteList;
    ref array<string> DisallowedVehicles;
    ref array<string> BypassZoneChecksGrenades;
    ref array<string> PvEBlockedExplosivesDamage;
    ref array<string> BlockDeployIfPlayerInPvEState;
    ref array<string> BlockDeployIfPlayerInPvPState;
    ref array<string> BlockDeployIfPlayerInRaidState;
    ref array<string> AllowedAmmoInPvEState;
    ref array<string> AllowedAmmoInPaintBallState;
    ref map<string, ref DynamicZones> CreateZoneWhenItemSpawned;
    static ref ItemRules cachedConfig;
    void ItemRules()
    {
        CantBeDamagedOnGround            = new array<string>();
        CantBeDamagedInPvE               = new array<string>();
        CantBeDamagedInPvP               = new array<string>();
        SZItemWhiteList                  = new array<string>();
        NBItemWhiteList                  = new array<string>();
        DisallowedVehicles               = new array<string>();
        BypassZoneChecksGrenades         = new array<string>();
        PvEBlockedExplosivesDamage       = new array<string>();
        BlockDeployIfPlayerInPvEState    = new array<string>();
        BlockDeployIfPlayerInPvPState    = new array<string>();
        BlockDeployIfPlayerInRaidState   = new array<string>();
        AllowedAmmoInPvEState            = new array<string>();
        AllowedAmmoInPaintBallState      = new array<string>();
        CreateZoneWhenItemSpawned        = new map<string, ref DynamicZones>();
    }
    void SaveConfig()
    {
        if ( GetGame().IsClient() )
		{
			return;
		}
        CheckDirectories();
        JsonFileLoader<ItemRules>.JsonSaveFile(NinjinsPvPPvE_ITEM_RULES_FILE, this);
    }
    static ref ItemRules LoadConfig(bool forceReload = false)
    {
        if (cachedConfig && !forceReload)
            return cachedConfig;
        ItemRules config = new ItemRules();
        CheckDirectories();
        string configPath = NinjinsPvPPvE_ITEM_RULES_FILE;
        bool isFirstCreation = false;
        if (FileExist(configPath))
        {
            JsonFileLoader<ItemRules>.JsonLoadFile(configPath, config);
        }
        else
        {
            NinjinsPvPPvE.LogDebug("ItemRules.json not found. Creating default item rule settings.");
            isFirstCreation = true;
        }
        if (!config.CantBeDamagedOnGround)
            config.CantBeDamagedOnGround = new array<string>();
        if (!config.CantBeDamagedInPvE)
            config.CantBeDamagedInPvE = new array<string>();
        if (!config.CantBeDamagedInPvP)
            config.CantBeDamagedInPvP = new array<string>();
        if (!config.DisallowedVehicles)
            config.DisallowedVehicles = new array<string>();
        if (!config.BypassZoneChecksGrenades)
            config.BypassZoneChecksGrenades = new array<string>();
        if (!config.PvEBlockedExplosivesDamage)
            config.PvEBlockedExplosivesDamage = new array<string>();
        if (!config.BlockDeployIfPlayerInPvEState)
            config.BlockDeployIfPlayerInPvEState = new array<string>();
        if (!config.BlockDeployIfPlayerInPvPState)
            config.BlockDeployIfPlayerInPvPState = new array<string>();
        if (!config.BlockDeployIfPlayerInRaidState)
            config.BlockDeployIfPlayerInRaidState = new array<string>();
        if (!config.CreateZoneWhenItemSpawned) 
        {
            config.CreateZoneWhenItemSpawned = new map<string, ref DynamicZones>();
        } 
        else 
        {
   
            foreach (string zoneName, DynamicZones zone: config.CreateZoneWhenItemSpawned) 
            {
                if (zone) 
                {
   
                    ZoneDayConfigHelper.UpgradeLegacy(zone);
                }
            }
        }
        if (!config.AllowedAmmoInPvEState)
            config.AllowedAmmoInPvEState = new array<string>();
        if (!config.AllowedAmmoInPaintBallState)
            config.AllowedAmmoInPaintBallState = new array<string>();
        if (!config.SZItemWhiteList)
            config.SZItemWhiteList = new array<string>();
        if (!config.NBItemWhiteList)
            config.NBItemWhiteList = new array<string>();
        if (isFirstCreation)
        {
            NinjinsPvPPvE.LogDebug(">> CantBeDamagedInPvE <<: " + config.CantBeDamagedInPvE.Count());
            NinjinsPvPPvE.LogDebug(">> CantBeDamagedInPvP <<: " + config.CantBeDamagedInPvP.Count());
            config.PvEBlockedExplosivesDamage.Insert("ExplosivesBase");
            config.PvEBlockedExplosivesDamage.Insert("Ammo_40mm_Base");
            config.PvEBlockedExplosivesDamage.Insert("Expansion_C4_Explosion");
            config.PvEBlockedExplosivesDamage.Insert("Expansion_RPG_Explosion");
            config.PvEBlockedExplosivesDamage.Insert("Expansion_LAW_Explosion");
            config.PvEBlockedExplosivesDamage.Insert("Land_FuelStation_Feed");
            config.PvEBlockedExplosivesDamage.Insert("Land_FuelStation_Feed_Enoch");
            config.PvEBlockedExplosivesDamage.Insert("Expansion_M203");
            config.PvEBlockedExplosivesDamage.Insert("LargeGasCanister");
            config.PvEBlockedExplosivesDamage.Insert("M67Grenade");
            config.BypassZoneChecksGrenades.Insert("DLT_Paintball_Grenade_Ammo");
            config.BypassZoneChecksGrenades.Insert("DLT_Paintball_Grenade_Ammo_Small");
            config.BypassZoneChecksGrenades.Insert("DLT_Paintball_Grenade_Pink");
            config.BypassZoneChecksGrenades.Insert("DLT_Paintball_Grenade_Green");
            config.BypassZoneChecksGrenades.Insert("DLT_Paintball_Grenade_Orange");
            config.BypassZoneChecksGrenades.Insert("DLT_Paintball_Grenade_Blue");
            config.BypassZoneChecksGrenades.Insert("DLT_Paintball_GrenadeSmall_Pink");
            config.BypassZoneChecksGrenades.Insert("DLT_Paintball_GrenadeSmall_Blue");
            config.BypassZoneChecksGrenades.Insert("DLT_Paintball_GrenadeSmall_Orange");
            config.BypassZoneChecksGrenades.Insert("DLT_Paintball_GrenadeSmall_Green");
            config.AllowedAmmoInPaintBallState.Insert("DLT_Bullet_Paintball_Orange");
            config.AllowedAmmoInPaintBallState.Insert("DLT_Bullet_Paintball_Blue");
            config.AllowedAmmoInPaintBallState.Insert("DLT_Bullet_Paintball_Green");
            config.AllowedAmmoInPaintBallState.Insert("DLT_Bullet_Paintball_Pink");
            config.DisallowedVehicles.Insert("Transport");
            config.DisallowedVehicles.Insert("ExpansionHelicopterScript");
            config.DisallowedVehicles.Insert("RFFSHeli_base");
            config.DisallowedVehicles.Insert("CarScript");
        }
        NinjinLogConfig(config);
        config.SaveConfig();
        cachedConfig = config;
        return config;
    }
	static void NinjinLogConfig(ItemRules config)
	{
		NinjinsPvPPvE.LogDebug("-------------------------------------");
		NinjinsPvPPvE.LogDebug("-------- ItemRules Settings ---------");
		NinjinsPvPPvE.LogDebug("-------------------------------------");
        NinjinsPvPPvE.LogDebug(">> SZItemWhiteList <<: " + config.SZItemWhiteList.Count());
        if (config.SZItemWhiteList.Count() == 0)
            NinjinsPvPPvE.LogDebug(">> SZItemWhiteList << No items in the list.");
        for (int idxWhite = 0; idxWhite < config.SZItemWhiteList.Count(); idxWhite++)
            NinjinsPvPPvE.LogDebug("[" + idxWhite + "] " + config.SZItemWhiteList[idxWhite]);
		NinjinsPvPPvE.LogDebug(">> CantBeDamagedOnGround <<: " + config.CantBeDamagedOnGround.Count());
		if (config.CantBeDamagedOnGround.Count() == 0)
			NinjinsPvPPvE.LogDebug(">< CantBeDamagedOnGround << No items in the list.");
		for (int idxCant = 0; idxCant < config.CantBeDamagedOnGround.Count(); idxCant++)
			NinjinsPvPPvE.LogDebug("[" + idxCant + "] " + config.CantBeDamagedOnGround[idxCant]);
		NinjinsPvPPvE.LogDebug(">> DisallowedVehicles <<: " + config.DisallowedVehicles.Count());
		if (config.DisallowedVehicles.Count() == 0)
			NinjinsPvPPvE.LogDebug(">> DisallowedVehicles << No items in the list.");
		for (int idxDisallowed = 0; idxDisallowed < config.DisallowedVehicles.Count(); idxDisallowed++)
			NinjinsPvPPvE.LogDebug("[" + idxDisallowed + "] " + config.DisallowedVehicles[idxDisallowed]);
		NinjinsPvPPvE.LogDebug(">> BypassZoneChecksGrenades <<: " + config.BypassZoneChecksGrenades.Count());
		if (config.BypassZoneChecksGrenades.Count() == 0)
			NinjinsPvPPvE.LogDebug(">> BypassZoneChecksGrenades << No items in the list.");
		for (int idxBypass = 0; idxBypass < config.BypassZoneChecksGrenades.Count(); idxBypass++)
			NinjinsPvPPvE.LogDebug("[" + idxBypass + "] " + config.BypassZoneChecksGrenades[idxBypass]);
		NinjinsPvPPvE.LogDebug(">> PvEBlockedExplosivesDamage <<: " + config.PvEBlockedExplosivesDamage.Count());
		if (config.PvEBlockedExplosivesDamage.Count() == 0)
			NinjinsPvPPvE.LogDebug(">> PvEBlockedExplosivesDamage << No items in the list.");
		for (int idxPvEExpl = 0; idxPvEExpl < config.PvEBlockedExplosivesDamage.Count(); idxPvEExpl++)
			NinjinsPvPPvE.LogDebug("[" + idxPvEExpl + "] " + config.PvEBlockedExplosivesDamage[idxPvEExpl]);
		NinjinsPvPPvE.LogDebug(">> BlockDeployIfPlayerInPvEState <<: " + config.BlockDeployIfPlayerInPvEState.Count());
		if (config.BlockDeployIfPlayerInPvEState.Count() == 0)
			NinjinsPvPPvE.LogDebug(">> BlockDeployIfPlayerInPvEState << No items in the list.");
		for (int idxBlockPvE = 0; idxBlockPvE < config.BlockDeployIfPlayerInPvEState.Count(); idxBlockPvE++)
			NinjinsPvPPvE.LogDebug("[" + idxBlockPvE + "] " + config.BlockDeployIfPlayerInPvEState[idxBlockPvE]);
		NinjinsPvPPvE.LogDebug(">> BlockDeployIfPlayerInPvPState <<: " + config.BlockDeployIfPlayerInPvPState.Count());
		if (config.BlockDeployIfPlayerInPvPState.Count() == 0)
			NinjinsPvPPvE.LogDebug(">> BlockDeployIfPlayerInPvPState << No items in the list.");
		for (int idxBlockPvP = 0; idxBlockPvP < config.BlockDeployIfPlayerInPvPState.Count(); idxBlockPvP++)
			NinjinsPvPPvE.LogDebug("[" + idxBlockPvP + "] " + config.BlockDeployIfPlayerInPvPState[idxBlockPvP]);
		NinjinsPvPPvE.LogDebug(">> BlockDeployIfPlayerInRaidState <<: " + config.BlockDeployIfPlayerInRaidState.Count());
		if (config.BlockDeployIfPlayerInRaidState.Count() == 0)
			NinjinsPvPPvE.LogDebug(">>BlockDeployIfPlayerInRaidState << No items in the list.");
		for (int idxBlockRaid = 0; idxBlockRaid < config.BlockDeployIfPlayerInRaidState.Count(); idxBlockRaid++)
			NinjinsPvPPvE.LogDebug("[" + idxBlockRaid + "] " + config.BlockDeployIfPlayerInRaidState[idxBlockRaid]);
		NinjinsPvPPvE.LogDebug(">> AllowedAmmoInPvEState <<: " + config.AllowedAmmoInPvEState.Count());
		if (config.AllowedAmmoInPvEState.Count() == 0)
			NinjinsPvPPvE.LogDebug(">> AllowedAmmoInPvEState << No items in the list.");
		for (int idxAmmo = 0; idxAmmo < config.AllowedAmmoInPvEState.Count(); idxAmmo++)
			NinjinsPvPPvE.LogDebug("[" + idxAmmo + "] " + config.AllowedAmmoInPvEState[idxAmmo]);
		NinjinsPvPPvE.LogDebug(">> CreateZoneWhenItemSpawned <<: " + config.CreateZoneWhenItemSpawned.Count());
		if (config.CreateZoneWhenItemSpawned.Count() == 0)
		{
			NinjinsPvPPvE.LogDebug(">> CreateZoneWhenItemSpawned << No dynamic zones defined.");
		}
	}
    static void CheckDirectories()
    {
        if (!FileExist(NinjinsPvPPvE_ROOT_FOLDER))
        {
            if (MakeDirectory(NinjinsPvPPvE_ROOT_FOLDER))
                NinjinsPvPPvE.LogDebug("Created root directory: " + NinjinsPvPPvE_ROOT_FOLDER);
            else
                NinjinsPvPPvE.LogCritical("Failed to create root directory: " + NinjinsPvPPvE_ROOT_FOLDER);
        }
        if (!FileExist(NinjinsPvPPvE_GENERAL_CONFIG_DIR))
        {
            if (MakeDirectory(NinjinsPvPPvE_GENERAL_CONFIG_DIR))
                NinjinsPvPPvE.LogDebug("Created config directory: " + NinjinsPvPPvE_GENERAL_CONFIG_DIR);
            else
                NinjinsPvPPvE.LogCritical("Failed to create config directory: " + NinjinsPvPPvE_GENERAL_CONFIG_DIR);
        }
    }
}
