/* 
---------------------------------------
Pathing COnstants
---------------------------------------
*/
const string NinjinsPvPPvE_ROOT_FOLDER         = "$profile:NinjinsPvPPvE\\";
const string NinjinsPvPPvE_LOG_FOLDER          = NinjinsPvPPvE_ROOT_FOLDER + "Logging\\";
const string NinjinsPvPPvE_LOGGER_CONFIG_DIR   = NinjinsPvPPvE_LOG_FOLDER + "Config\\";
const string NinjinsPvPPvE_LOGGER_CONFIG_FILE  = NinjinsPvPPvE_LOGGER_CONFIG_DIR + "LoggingSettings.json";
const string NinjinsPvPPvE_LOGGER_LOG_DIR      = NinjinsPvPPvE_LOG_FOLDER + "Logs\\";
const string NinjinsPvPPvE_LOGGER_LOG_FILE     = NinjinsPvPPvE_LOGGER_LOG_DIR + "NinjinsPvPPvE_%1.log";
const string NinjinsPvPPvE_GENERAL_CONFIG_DIR  = NinjinsPvPPvE_ROOT_FOLDER + "Config\\";
const string NinjinsPvPPvE_ZONES_CONFIG_FILE   = NinjinsPvPPvE_GENERAL_CONFIG_DIR + "Zones.json";
const string NinjinsPvPPvE_MAIN_CONFIG_FILE    = NinjinsPvPPvE_GENERAL_CONFIG_DIR + "MainConfig.json";
const string NinjinsPvPPvE_ADMIN_CONFIG_FILE   = NinjinsPvPPvE_GENERAL_CONFIG_DIR + "Admins.json";
const string NinjinsPvPPvE_ITEM_RULES_FILE     = NinjinsPvPPvE_GENERAL_CONFIG_DIR + "ItemRules.json";
const string NinjinsPvPPvE_LEGACY_BACKUP_DIR   = NinjinsPvPPvE_ROOT_FOLDER + "legacy backup\\";
/* 
---------------------------------------
ZONE TYPE CONSTANTS
---------------------------------------
*/
const int ZONE_TYPE_PVP    = 1;  
const int ZONE_TYPE_PVE    = 2;  
const int ZONE_TYPE_VISUAL = 3;  
const int ZONE_TYPE_RAID   = 4; 
const int ZONE_TYPE_SAFEZONE = 5; 
const int ZONE_TYPE_PAINTBALL = 6;
/* 
---------------------------------------
PRIORITY CONSTANTS
---------------------------------------
*/
const int PRIORITY_ONE   = 1;
const int PRIORITY_TWO   = 2;
const int PRIORITY_THREE = 3;
const int PRIORITY_FOUR  = 4;
const int PRIORITY_FIVE  = 5;
const int PRIORITY_SIX   = 6;
const int PRIORITY_SEVEN = 7;
const int PRIORITY_EIGHT = 8;
const int PRIORITY_NINE  = 9;
const int PRIORITY_TEN   = 10;
const int PRIORITY_ELEVEN   = 11;
const int PRIORITY_TWELVE   = 12;
const int PRIORITY_THIRTEEN = 13;
const int PRIORITY_FOURTEEN = 14;
const int PRIORITY_FIFTEEN  = 15;
/* 
----------------------------------------
DAMAGE SOURCE TYPE CONSTANTS
----------------------------------------  
*/
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_UNKNOWN     = -1;
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_EXPLOSIVE   = 0; 
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_WEAPON      = 1;    
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_VEHICLE     = 2;   
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_FISTS       = 3;     
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_SELF        = 4;      
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_CLAWS       = 5;     
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_CHEMGAS     = 6; 
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_WEAPON_MELEE= 7;
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_AI          = 8;
const int NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_EXPANSION_EXPLOSIVE = 9;
/* 
---------------------------------------
Disallowed Vehicles Constants
---------------------------------------
*/
static const int NFZA_KILL = 0;
static const int NFZA_DESTROY_VEHICLE = 1;
static const int NFZA_DELETE_VEHICLE = 2;
/* 
---------------------------------------
Admin-Menu
---------------------------------------
*/
static const int COLOR_CHECKED = ARGB(255,   0, 255,   0);  
static const int COLOR_UNCHECK = ARGB(255, 255,   0,   0);  
