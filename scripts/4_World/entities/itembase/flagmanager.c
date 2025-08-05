modded class TerritoryFlag
{
    protected string m_FlagPvPZoneID;
    protected bool m_RefresherActivePrevState;
    void TerritoryFlag()
    {
        m_FlagPvPZoneID            = "";
        m_RefresherActivePrevState = m_RefresherActive;
        if (!GetGame().IsServer()) 
            return;
        if (!g_MainConfig || !g_MainConfig.EnableTerritoryFlagZones) 
            return;
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckAndControlPvPZone, g_MainConfig.TerritoryFlagPvPZoneCheckInterval, true);
    }
    void ~TerritoryFlag()
    {
        UnregisterPvPZone();
    }
    override void SetActions()
    {
        super.SetActions();
        NinjinsPvPPvE.LogDebug("TerritoryFlag::SetActions called.");
        if (g_MainConfig && !g_MainConfig.DisableRaidingDialogActionOnFlagPole)
        {
            NinjinsPvPPvE.LogDebug("Adding ActionAddRaidingPlayer to TerritoryFlag.");
            AddAction(ActionAddRaidingPlayer);
        }
        else
        {
            NinjinsPvPPvE.LogDebug("Dialog action is disabled by config.");
        }
    }
/*
----------------------------------------------------------------------------------------------------
IsFlagAssembled: Returns true if the flags construction parts (support, pole) are built
----------------------------------------------------------------------------------------------------
*/
    bool IsFlagAssembled()
    {
        if (!GetConstruction())
            return false;
        if (!GetConstruction().IsPartConstructed("support"))
            return false;
        if (!GetConstruction().IsPartConstructed("pole"))
            return false;
        if (!FindAttachmentBySlotName("Material_FPole_Flag"))
            return false;
        return true;
    }
/*
----------------------------------------------------------------------------------------------------
SetRefresher - Active
----------------------------------------------------------------------------------------------------
*/
    override void SetRefresherActive(bool state)
    {
        bool previousState = m_RefresherActive;
        super.SetRefresherActive(state);
        if (!GetGame().IsServer()) 
            return;
        if (!g_MainConfig || !g_MainConfig.EnableTerritoryFlagZones) 
            return;
        //NinjinsPvPPvE.LogDebug("[DEBUG] SetRefresherActive Triggered: Previous=" + previousState + ", Current=" + m_RefresherActive);
        //NinjinsPvPPvE.LogDebug("[DEBUG] TerritoryFlagZoneCreateMode: " + g_MainConfig.TerritoryFlagZoneCreateMode);
        if (!IsFlagAssembled())
        {
            UnregisterPvPZone();
            return;
        }
        if (g_MainConfig.TerritoryFlagZoneCreateMode == 0 && !m_RefresherActive)
        {
            CreatePvPZone();
        }
        else if (g_MainConfig.TerritoryFlagZoneCreateMode == 1 && m_RefresherActive)
        {
            CreatePvPZone();
        }
        else if (g_MainConfig.TerritoryFlagZoneCreateMode == 2)
        {
            CreatePvPZone();
        }
        else
        {
            UnregisterPvPZone();
        }
    }
/*
----------------------------------------------------------------------------------------------------
CheckAndControlPvPZone: Periodically makes sure the zone is correctly created or removed
----------------------------------------------------------------------------------------------------
*/
    void CheckAndControlPvPZone()
    {
        if (!GetGame().IsServer()) 
            return;
        if (!g_MainConfig || !g_MainConfig.EnableTerritoryFlagZones) 
            return;
        if (!IsFlagAssembled())
        {
            UnregisterPvPZone();
            return;
        }
        bool shouldCreate = false;
        if (g_MainConfig.TerritoryFlagZoneCreateMode == 0 && !m_RefresherActive) 
        {
            shouldCreate = true;
        }
        else if (g_MainConfig.TerritoryFlagZoneCreateMode == 1 && m_RefresherActive) 
        {
            shouldCreate = true;
        }
        else if (g_MainConfig.TerritoryFlagZoneCreateMode == 2) 
        {
            shouldCreate = true;
        }
        if (shouldCreate) 
        {
            CreatePvPZone();
        } 
        else 
        {
            UnregisterPvPZone();
        }
    }
/*
---------------------------------------------------------------------------------------------
CreatePvPZone: Creates the PvP zone if none exists and if the flag is fully attached
---------------------------------------------------------------------------------------------
*/
    void CreatePvPZone()
    {
        if (!GetGame().IsServer()) 
            return;
        if (!g_MainConfig || !g_MainConfig.EnableTerritoryFlagZones) 
            return;
        if (!IsFlagAssembled()) 
            return;
        if (m_FlagPvPZoneID != "")
            return;
        NinjinsZoneSettings settings = NinjinsZoneSettings.Load();
        if (!settings || !settings.FlagZoneDefaults) 
        {
            NinjinsPvPPvE.LogWarning("[NinjinsPvPPvE][TerritoryFlag] Failed to load FlagZoneDefaults from settings");
            return;
        }
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (!zoneManager)
            return;
        vector position = GetPosition();
        m_FlagPvPZoneID = "FlagPvPZone_" + position[0].ToString() + "_" + position[2].ToString();
        DynamicZones def = settings.FlagZoneDefaults;
        ZoneBase flagZone = new ZoneBase();
        flagZone.name = m_FlagPvPZoneID;
        flagZone.shape = ZoneShape.CIRCLE;
        flagZone.center = position;
        flagZone.HideWhenNested = def.HideWhenNested;
        flagZone.DrawNoBuildShape = def.DrawNoBuildShape;
        flagZone.zoneMinHeight = def.zoneMinHeight;
        flagZone.zoneMaxHeight = def.zoneMaxHeight;
        flagZone.ignoreHeightCheck = def.ignoreHeightCheck;
        flagZone.type = def.type;
        flagZone.priority = def.priority;
        flagZone.radius = def.radius;
        flagZone.noBuildRadius = -1;
        flagZone.zoneAlpha = def.zoneAlpha;
        flagZone.zoneRed = def.zoneRed;
        flagZone.zoneGreen = def.zoneGreen;
        flagZone.zoneBlue = def.zoneBlue;
        flagZone.drawShape = def.drawShape;
        flagZone.forceFirstPerson = def.forceFirstPerson;
        flagZone.enableCustomMessages = def.enableCustomMessages;
        flagZone.customTitle = def.customTitle;
        flagZone.customMessageEnter = def.customMessageEnter;
        flagZone.customMessageExit = def.customMessageExit;
        flagZone.customIcon = def.customIcon;
        flagZone.notificationColor = def.notificationColor;
        flagZone.EnableExpansion3DMarker = def.EnableExpansion3DMarker;
        flagZone.OnlyAllowExpansion2DMarker = def.OnlyAllowExpansion2DMarker;
        flagZone.Expansion3DIcon = def.Expansion3DIcon;
        flagZone.ExpansionMarkerName = def.ExpansionMarkerName;
        flagZone.drawStrikeZone = def.drawStrikeZone;
        flagZone.UsesDisallowedVehicles = def.UsesDisallowedVehicles;
        flagZone.ZonelabelOffsetX_Meters = def.ZonelabelOffsetX_Meters;
        flagZone.ZonelabelOffsetZ_Meters = def.ZonelabelOffsetZ_Meters;
        flagZone.ZoneLabelColor = def.ZoneLabelColor;
        flagZone.Hide = def.Hide;
        flagZone.NoLogOut = def.NoLogOut;
        flagZone.NoLogOutTeleportPos = def.NoLogOutTeleportPos;
        flagZone.dayConfigs = new array<ref DayConfig>();
        foreach (DayConfig config : def.dayConfigs)
        {
            flagZone.dayConfigs.Insert(new DayConfig(config.dayName, config.startHour, config.endHour));
        }
        zoneManager.RegisterDynamicZone(flagZone);
        NinjinsPvPPvE.LogDebug("[NinjinsPvPPvE][TerritoryFlag] PvP zone created: " + m_FlagPvPZoneID);
    }
/*
---------------------------------------------------------------------------------------------
UnregisterPvPZone: Removes the dynamic PvP zone if it exist
---------------------------------------------------------------------------------------------
*/
    void UnregisterPvPZone()
    {
        if (!GetGame() || !GetGame().IsServer())
            return;
        if (m_FlagPvPZoneID != "")
        {
            ZoneManager zoneManager = ZoneManager.GetInstance();
            if (zoneManager)
            {
                bool removed = zoneManager.RemoveDynamicZone(m_FlagPvPZoneID);
                if (removed)
                {
                    NinjinsPvPPvE.LogDebug("[NinjinsPvPPvE][TerritoryFlag] PvP zone removed: " + m_FlagPvPZoneID);
                }
                else
                {
                    NinjinsPvPPvE.LogDebug("[NinjinsPvPPvE][TerritoryFlag] No dynamic PvP zone found with name: " + m_FlagPvPZoneID);
                }
            }
            m_FlagPvPZoneID = "";
        }
    }
/*
---------------------------------------------------------------------------------------------
Callbacks to reflect construction or attachment changes
---------------------------------------------------------------------------------------------
*/
    override void OnPartBuiltServer(notnull Man player, string part_name, int action_id)
    {
        super.OnPartBuiltServer(player, part_name, action_id);
        CheckAndControlPvPZone();
    }
    override void OnPartDismantledServer(notnull Man player, string part_name, int action_id)
    {
        super.OnPartDismantledServer(player, part_name, action_id);
        CheckAndControlPvPZone();
    }
    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);
        if (GetGame().IsServer() && g_MainConfig && g_MainConfig.EnableTerritoryFlagZones)
            CheckAndControlPvPZone();
    }
    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);
        if (GetGame().IsServer() && g_MainConfig && g_MainConfig.EnableTerritoryFlagZones)
            CheckAndControlPvPZone();
    }
}
