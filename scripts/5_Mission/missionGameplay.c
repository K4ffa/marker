modded class MissionGameplay extends MissionBase
{
    ref NinjinClientSettingsMenu m_ClientSettingsMenu;
    private ref array<ref ZoneBase> m_CachedZones;
    ref array<string> client_AllowedRaidingPlayers;
    private Widget m_RootWidgetIcons;
    private ImageWidget m_IconWidget;
    private Widget m_RootWidgetNotifications;
    private RichTextWidget m_CountdownTimer;
    private Widget m_RootFrameNoVehicle;
    private RichTextWidget m_WarningText;
    ref NinjinsAdminMenu m_AdminMenu;
    ref ItemSearchMenu m_ItemSearchMenu;
    ref AdminConfig g_AdminConfig;
    private ref map<int, float> m_ActiveTimers;
    private string m_LastReloadedConfig;
    ref map<string, vector> m_PendingScanResults;
    private bool m_RequestedZones = false;
/*
--------------------------------------------------
GETTERS
--------------------------------------------------
*/
    array<ref ZoneBase> GetCachedZones()
    {
        return m_CachedZones;
    }
/*
--------------------------------------------------
OnInit - Override
--------------------------------------------------
*/
    override void OnInit()
    {
        super.OnInit();
        m_ActiveTimers = new map<int, float>();
        m_CachedZones  = new array<ref ZoneBase>();
        RegisterRPCs();
        LoadIconLayout();
        LoadNotificationLayout();
        NinjinClientZoneSettings settings = NinjinClientZoneSettings.Init();
        client_AllowedRaidingPlayers = new array<string>;
        if (m_RootWidgetNotifications)
        {
            m_RootWidgetNotifications.Show(false);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] NotificationWidget explicitly hidden in OnInit.");
        }
        if (m_RootFrameNoVehicle)
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay] m_RootFrameNoVehicle loaded successfully.");
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[MissionGameplay][ERROR] m_RootFrameNoVehicle is null.");
        }
    }
/*
--------------------------------------------------
RPCs
--------------------------------------------------
*/
    private void RegisterRPCs()
    {
        GetRPCManager().AddRPC("NinjinsPvPPvE", "SyncMainConfig",this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ReceiveZones",this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ReloadConfigResult",this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ZoneNotification",this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "UpdateAllowedRaidingPlayers", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ApplyVehicleWarningEffect", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "RemoveVehicleWarningEffect", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ShowNoVehicleWarning", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "HideNoVehicleWarning", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "SyncAdminConfig", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "SyncItemRules", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "UpdateNotificationUI", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "HandleScanResults", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "ReceiveOnlinePlayers", this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC("NinjinsPvPPvE", "RequestZones", this, SingleplayerExecutionType.Server);
    }
/*
--------------------------------------------------
No Vehicle Zones - Related
--------------------------------------------------
*/
    void ApplyVehicleWarningEffect(CallType type, ParamsReadContext ctx)
    {
        if (type != CallType.Client) 
            return;
        string effect = g_MainConfig.NoVehicleWarningEffect;
        float intensity = g_MainConfig.NoVehicleWarningEffectIntensity;
        if (effect == "none" || effect == "")
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay] No effect applied (effect set to 'none' or empty).");
            return;
        }
        switch (effect)
        {
            case "shock":
                PPEffects.SetShockVignette(intensity);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Applying shock effect with intensity: " + intensity);
                break;
            case "blur":
                PPEffects.SetBlur(intensity);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Applying blur effect with intensity: " + intensity);
                break;
            case "blood":
                PPEffects.SetBloodSaturation(0.5 - intensity);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Applying blood effect with intensity: " + intensity);
                break;
            case "redscreen":
                PPEffects.SetColorizationNV(1.0 * intensity, 0.0, 0.0);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Applying redscreen effect with intensity: " + intensity);
                break;
            case "blackscreen":
                PPEffects.SetDeathDarkening(intensity);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Applying darkening effect with intensity: " + intensity);
                break;
            default:
                NinjinsPvPPvE.LogWarning("[MissionGameplay] Unknown effect: " + effect);
                break;
        }
    }
    void RemoveVehicleWarningEffect(CallType type, ParamsReadContext ctx)
    {
        if (type != CallType.Client) 
            return;
        string effect = g_MainConfig.NoVehicleWarningEffect;
        if (effect == "none" || effect == "")
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay] No effect to remove (effect set to 'none' or empty).");
            return;
        }
        switch (effect)
        {
            case "shock":
                PPEffects.SetShockVignette(0);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Removing shock effect.");
                break;
            case "blur":
                PPEffects.SetBlur(0);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Removing blur effect.");
                break;
            case "blood":
                PPEffects.SetBloodSaturation(1.0);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Removing blood effect.");
                break;
            case "redscreen":
                PPEffects.ResetColorize();
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Removing redscreen effect.");
                break;
            case "blackscreen":
                PPEffects.SetDeathDarkening(0);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Removing darkening effect.");
                break;
            default:
                NinjinsPvPPvE.LogWarning("[MissionGameplay] Unknown effect: " + effect);
                break;
        }
    }
/*
--------------------------------------------------
Admin Menu - Related
--------------------------------------------------
*/
    void UpdateAllowedRaidingPlayers(CallType type, ParamsReadContext ctx)
    {
        if (type != CallType.Client)
            return;
        Param1<array<string>> receivedPlayers;
        if (!ctx.Read(receivedPlayers))
            return;
        if (!receivedPlayers.param1 || !g_MainConfig)
            return;
        g_MainConfig.AllowedRaidingPlayers.Clear();
        foreach (string entry : receivedPlayers.param1)
        {
            g_MainConfig.AllowedRaidingPlayers.Insert(entry);
        }
        UIScriptedMenu menu = GetGame().GetUIManager().GetMenu();
        if (menu && menu.IsInherited(NinjinsAdminMenu))
        {
            NinjinsAdminMenu adminMenu = NinjinsAdminMenu.Cast(menu);
            adminMenu.PopulateAllowedRaidingPlayers();
        }
    }
    void ReceiveOnlinePlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client) 
            return;
        Param1<array<string>> data;
        if (!ctx.Read(data)) 
            return;
        UIScriptedMenu menu = GetGame().GetUIManager().GetMenu();
        if (menu && menu.IsInherited(NinjinsAdminMenu))
        {
            NinjinsAdminMenu adminMenu = NinjinsAdminMenu.Cast(menu);
            adminMenu.UpdateOnlinePlayersList(data.param1);
        }
    }
    void HandleScanResults(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client) 
            return;
        Param1<ref map<string, vector>> result;
        if (!ctx.Read(result) || !result || !result.param1) 
            return;
        UIScriptedMenu menu = GetGame().GetUIManager().GetMenu();
        if (menu && menu.IsInherited(ItemSearchMenu))
        {
            ItemSearchMenu searchMenu = ItemSearchMenu.Cast(menu);
            searchMenu.SetFoundItems(result.param1);
        }
    }
/*
--------------------------------------------------
OnUpdate - Player States
--------------------------------------------------
*/
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player) 
            return;
        bool isInPvEZone  = player.netSync_IsInPvEZone;
        bool isInPvPZone  = player.netSync_IsInPvPZone;
        bool isInRaidMode = player.netSync_IsInRaidMode;
        bool isInSafeZone = player.netSync_IsInSafeZone;
        UpdateIconBasedOnState(isInRaidMode, isInPvPZone, isInPvEZone, isInSafeZone);
        ControlInputs();
        if (!m_RequestedZones && player.GetIdentity())
        {
            GetRPCManager().SendRPC("NinjinsPvPPvE", "RequestZones", null, true, player.GetIdentity());
            m_RequestedZones = true;
            NinjinsPvPPvE.LogDebug("[MissionGameplay] RequestZones RPC sent from client.");
        }
    }
/*
--------------------------------------------------
Icons - Related
--------------------------------------------------
*/
    private bool IsHudHidden()
    {
        IngameHud hud = IngameHud.Cast( GetGame().GetMission().GetHud() );
        if ( !hud )
            return false;
        IngameHudVisibility vis = hud.GetHudVisibility();
        if ( !vis )
            return false;
            if ( vis.IsContextFlagActive( EHudContextFlags.HUD_HIDE ) || vis.IsContextFlagActive( EHudContextFlags.MENU_OPEN ) || vis.IsContextFlagActive( EHudContextFlags.HUD_DISABLE ))
             return true;
        return false;
    }
    private void InitializeIconWidgets()
    {
        m_IconWidget = ImageWidget.Cast(m_RootWidgetIcons.FindAnyWidget("Image"));
        if (m_IconWidget)
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay] ImageWidget found successfully.");
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[MissionGameplay][ERROR] Failed to find ImageWidget.");
        }
    }
    private void LoadIconLayout()
    {
        m_RootWidgetIcons = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/ZoneStateIcons.layout");
        if (m_RootWidgetIcons)
        {
            InitializeIconWidgets();
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[MissionGameplay][ERROR] Failed to create Icon layout widget.");
        }
    }
    private void UpdateIconBasedOnState(bool isInRaidMode, bool isInPvPZone, bool isInPvEZone, bool isInSafeZone)
    {
        if ( IsHudHidden() )
        {
            if ( m_RootWidgetIcons && m_RootWidgetIcons.IsVisible() )
                m_RootWidgetIcons.Show( false );
            return;
        }
        if (m_RootWidgetIcons && m_IconWidget)
        {
            string iconPath = "";
            int iconColor = -1;
            if (isInRaidMode)
            {
                iconPath  = g_MainConfig.RaidImagePath;
                iconColor = g_MainConfig.RaidIconColor;
            }
            else if (isInSafeZone)
            {
                iconPath  = g_MainConfig.SafeZoneImagePath;
                iconColor = g_MainConfig.SafeZoneIconColor;
            }
            else if (isInPvPZone)
            {
                iconPath  = g_MainConfig.PvPImagePath;
                iconColor = g_MainConfig.PvPIconColor;
            }
            else if (isInPvEZone)
            {
                iconPath  = g_MainConfig.PvEImagePath;
                iconColor = g_MainConfig.PvEIconColor;
            }
            if (iconPath != "")
            {
                iconPath = g_MainConfig.ResolveIcon(iconPath);
                m_IconWidget.LoadImageFile(0, iconPath);
                m_IconWidget.SetColor(iconColor);
                m_RootWidgetIcons.Show(true);
            }
            else
            {
                m_RootWidgetIcons.Show(false);
                NinjinsPvPPvE.LogDebug("[UpdateIconBasedState] No zone detected, hiding icon (fallback).");
            }
        }
    }
    void ApplyIconSize()
    {
        NinjinClientZoneSettings clientSettings = new NinjinClientZoneSettings();
        clientSettings.Load();
        if (!m_IconWidget)
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] m_IconWidget is null. Cannot set size.");
            return;
        }
        float width = 0;
        float height = 0;
        if (g_MainConfig)
        {
            width = g_MainConfig.IconWidth;
            height = g_MainConfig.IconHeight;
        }
        else
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] g_MainConfig is null. Using default size 0x0.");
        }
        if (clientSettings.iconWidth > 0)
        {
            width = clientSettings.iconWidth;
        }
        if (clientSettings.iconHeight > 0)
        {
            height = clientSettings.iconHeight;
        }
        m_IconWidget.SetSize(width, height);
        NinjinsPvPPvE.LogDebug("[MissionGameplay] Icon size updated to: " + width + "x" + height);
    }
    void ApplyIconPosition()
    {
        NinjinClientZoneSettings clientSettings = new NinjinClientZoneSettings();
        clientSettings.Load();
        if (!m_RootWidgetIcons)
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] m_RootWidgetIcons is null. Cannot set position.");
            return;
        }
        float posX = 0.0;
        float posY = 0.0;
        if (g_MainConfig)
        {
            posX = g_MainConfig.IconPositionX;
            posY = g_MainConfig.IconPositionY;
        }
        if (clientSettings.iconPosX > 0)
        {
            posX = clientSettings.iconPosX;
        }
        if (clientSettings.iconPosY > 0)
        {
            posY = clientSettings.iconPosY;
        }
        m_RootWidgetIcons.SetPos(posX, posY, true);
        NinjinsPvPPvE.LogDebug("[MissionGameplay] Icon rootFrame position set to X: " + posX + ", Y: " + posY);
    }
    void UpdateIcon(string iconPath)
    {
        if (m_IconWidget)
        {
            if (iconPath != "")
            {
                m_IconWidget.LoadImageFile(0, iconPath);
                m_IconWidget.Show(true);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Icon updated to: " + iconPath);
            }
            else
            {
                m_IconWidget.LoadImageFile(0, "");
                m_IconWidget.Show(false);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Icon cleared (empty path).");
            }
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[MissionGameplay][ERROR] m_IconWidget is null.");
        }
    }
/*
--------------------------------------------------
Notifications - Related
--------------------------------------------------
*/
    private void InitializeNotificationWidgets()
    {
        m_CountdownTimer = RichTextWidget.Cast(m_RootWidgetNotifications.FindAnyWidget("CountdownTimer"));
        if (m_CountdownTimer)
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay] CountdownTimer found successfully.");
            m_RootWidgetNotifications.Show(false);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] NotificationWidget hidden on initialization.");
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[MissionGameplay][ERROR] Failed to find CountdownTimer.");
        }
    }
    private void LoadNotificationLayout()
    {
        m_RootWidgetNotifications = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/PvPZoneNotification.layout");
        if (m_RootWidgetNotifications)
        {
            InitializeNotificationWidgets();
            m_RootWidgetNotifications.Show(false);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] PvPZoneNotification UI loaded successfully.");
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[MissionGameplay][ERROR] Failed to create PvPZoneNotification layout widget.");
        }
        m_RootFrameNoVehicle = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/NoVehicleWarning.layout");
        if (m_RootFrameNoVehicle)
        {
            m_WarningText = RichTextWidget.Cast(m_RootFrameNoVehicle.FindAnyWidget("WarningText"));
            m_RootFrameNoVehicle.Show(false);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] NoVehicleWarning UI loaded successfully.");
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[MissionGameplay][ERROR] Failed to load NoVehicleWarning layout!");
        }
    }
    void ShowNoVehicleWarning(CallType type, ParamsReadContext ctx)
    {
        if (type != CallType.Client) 
            return;
        Param1<string> msg;
        if (!ctx.Read(msg)) 
            return;
        if (m_WarningText)
        {
            m_WarningText.SetText(msg.param1);
            m_RootFrameNoVehicle.Show(true);
        }
    }
    void HideNoVehicleWarning(CallType type, ParamsReadContext ctx)
    {
        if (type != CallType.Client) 
            return;
        HideNoVehicleWarning();
    }
    void ShowNoVehicleWarning()
    {
        if (m_RootFrameNoVehicle && m_WarningText)
        {
            m_WarningText.SetText(g_MainConfig.NoVehicleWarningText);
            m_RootFrameNoVehicle.Show(true);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] Showing NoVehicleWarning UI with text: " + g_MainConfig.NoVehicleWarningText);
        }
    }
    void HideNoVehicleWarning()
    {
        if (m_RootFrameNoVehicle)
        {
            m_RootFrameNoVehicle.Show(false);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] Hiding NoVehicleWarning UI.");
        }
    }
    void ShowNotification(string message, int duration = 0)
    {
        if (m_RootWidgetNotifications && m_CountdownTimer)
        {
            m_CountdownTimer.SetText(message);
            if (duration > 0)
            {
                GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(HideNotificationTitle, duration, false);
            }
            m_RootWidgetNotifications.Show(true);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] Notification displayed: " + message);
        }
    }
    void HideNotificationTitle()
    {
        if (m_RootWidgetNotifications && m_CountdownTimer)
        {
            m_CountdownTimer.SetText("");
            m_RootWidgetNotifications.Show(false);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] Notification hidden.");
        }
    }
    void ZoneNotification(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client) 
            return;
        Param4<string, int, float, bool> timerParam;
        if (!ctx.Read(timerParam))
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] Failed to read ZoneNotification from RPC.");
            return;
        }
        string playerID = timerParam.param1;
        int zoneType = timerParam.param2;
        float remainingTime = timerParam.param3;
        bool isActive = timerParam.param4;
        PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());
        if (!localPlayer || localPlayer.GetIdentity().GetId() != playerID)
            return;
        if (isActive && remainingTime > 0)
        {
            m_ActiveTimers.Set(zoneType, remainingTime);
            string countdownText = g_MainConfig.ExitNotificationText;
            countdownText.Replace("{seconds}", Math.Ceil(remainingTime).ToString());
            countdownText.Replace("{zonetype}", DefaultZoneTitle(zoneType));
            ShowNotification(countdownText);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] Countdown updated: " + countdownText);
        }
        else
        {
            if (m_ActiveTimers.Contains(zoneType))
            {
                m_ActiveTimers.Remove(zoneType);
            }
            HideNotificationTitle();
            NinjinsPvPPvE.LogDebug("[MissionGameplay] Notification cleared for zoneType " + zoneType);
        }
    }
    void ApplyNotificationSize()
    {
        if (m_RootWidgetNotifications && g_MainConfig)
        {
            m_RootWidgetNotifications.SetSize(g_MainConfig.NotificationPanelWidth, g_MainConfig.NotificationPanelHeight);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] NotificationWidget size set to Width: " + g_MainConfig.NotificationPanelWidth + ", Height: " + g_MainConfig.NotificationPanelHeight);
        }
        else
        {
            if (!m_RootWidgetNotifications)
            {
                NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] m_RootWidgetNotifications is null. Cannot set size.");
            }
            if (!g_MainConfig)
            {
                NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] g_MainConfig is null. Cannot apply notification size.");
            }
        }
    }
    void ApplyNotificationPosition()
    {
        if (m_RootWidgetNotifications && g_MainConfig)
        {
            m_RootWidgetNotifications.SetPos(g_MainConfig.ExitNotificationPanelPositionX, g_MainConfig.ExitNotificationPanelPositionY, true);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] NotificationWidget position set to X: " + g_MainConfig.ExitNotificationPanelPositionX + ", Y: " + g_MainConfig.ExitNotificationPanelPositionY);
        }
        else
        {
            if (!m_RootWidgetNotifications)
            {
                NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] m_RootWidgetNotifications is null. Cannot set position.");
            }
            if (!g_MainConfig)
            {
                NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] g_MainConfig is null. Cannot apply notification position.");
            }
        }
    }
/*
--------------------------------------------------
ControlInputs - Hotkeys
--------------------------------------------------
*/
    private void ControlInputs()
    {
        UIScriptedMenu currentMenu = GetGame().GetUIManager().GetMenu();
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || !player.GetIdentity())
            return;
        if (GetUApi().GetInputByName("UAUIBack").LocalPress())
        {
            if (currentMenu)
            {
                if (currentMenu.IsInherited(NinjinsAdminMenu))
                {
                    currentMenu.OnHide();
                    m_AdminMenu = null;
                    return;
                }
                if (currentMenu.IsInherited(ItemSearchMenu))
                {         
                    GetGame().GetUIManager().HideScriptedMenu(currentMenu);       
                    return;
                }
                if (currentMenu.IsInherited(NinjinClientSettingsMenu))
                {
                    currentMenu.OnHide();
                    m_ClientSettingsMenu = null;
                    return;
                }
            }
        }
        if (GetUApi().GetInputByName("UAAdminMenu").LocalPress())
        {
            if (!g_AdminConfig || !g_AdminConfig.IsAdmin(player.GetIdentity().GetId()))
            {
                NotificationSystem.Create(new StringLocaliser("Access Denied"), new StringLocaliser("You do not have permission to access the admin menu."), "NinjinsPvPPvE/gui/error.edds", COLOR_RED, 5.0, player.GetIdentity());
                return;
            }
            if (currentMenu && !currentMenu.IsInherited(NinjinsAdminMenu))
                return;
            if (currentMenu && currentMenu.IsInherited(NinjinsAdminMenu))
            {
                GetGame().GetUIManager().HideScriptedMenu(currentMenu);
                m_AdminMenu = null;
            }
            else
            {
                m_AdminMenu = new NinjinsAdminMenu();
                GetGame().GetUIManager().ShowScriptedMenu(m_AdminMenu, NULL);
            }
        }
        if (GetUApi().GetInputByName("UAItemSearchMenu").LocalPress())
        {
            if (!g_AdminConfig || !g_AdminConfig.IsAdmin(player.GetIdentity().GetId()))
            {
                NotificationSystem.Create(new StringLocaliser("Access Denied"), new StringLocaliser("You do not have permission to access the item search."), "NinjinsPvPPvE/gui/error.edds", COLOR_RED, 5.0, player.GetIdentity());
                return;
            }
            if (currentMenu && !currentMenu.IsInherited(ItemSearchMenu))
                return;
            if (currentMenu && currentMenu.IsInherited(ItemSearchMenu))
            {
                currentMenu.OnHide();
                GetGame().GetUIManager().HideScriptedMenu(currentMenu);
                return;
            }
            if (!m_ItemSearchMenu)
            {
                m_ItemSearchMenu = new ItemSearchMenu();
            }
            GetGame().GetUIManager().ShowScriptedMenu(m_ItemSearchMenu, NULL);
        }
        if (GetUApi().GetInputByName("UAClientZoneSettingsMenu").LocalPress())
        {
            if (currentMenu && currentMenu.IsInherited(NinjinClientSettingsMenu))
            {
                GetGame().GetUIManager().HideScriptedMenu(currentMenu);
                m_ClientSettingsMenu = null;
            }
            else if (!currentMenu)
            {
                m_ClientSettingsMenu = new NinjinClientSettingsMenu();
                GetGame().GetUIManager().ShowScriptedMenu(m_ClientSettingsMenu, NULL);
            }
        }
    }
    void ToggleClientSetting(string key)
    {
        NinjinClientZoneSettings settings = new NinjinClientZoneSettings();
        settings.Load();
        if (key == "PvP")
        {
            settings.showPvP = !settings.showPvP;
        }
        else if (key == "PvE")
        {
            settings.showPvE = !settings.showPvE;
        }
        else if (key == "Raid")
        {
            settings.showRaid = !settings.showRaid;
        }
        else if (key == "SafeZone")
        {
            settings.showSafeZone = !settings.showSafeZone;
        }
        else if (key == "Paintball")
        {
            settings.showPaintball = !settings.showPaintball;
        }
        else if (key == "Visual")
        {
            settings.showVisual = !settings.showVisual;
        }
        else if (key == "ZoneLabels")
        {
            settings.showZoneLabels = !settings.showZoneLabels;
        }
        else if (key == "NoBuild")
        {
            settings.showNoBuildRadius = !settings.showNoBuildRadius;
        }
        else
        {
            NinjinsPvPPvE.LogWarning("[ToggleClientSetting] Unknown setting key: " + key);
            return;
        }
        settings.Save();
        NinjinsPvPPvE.LogDebug("[ToggleClientSetting] " + key + " toggled and saved.");
    }
/*
--------------------------------------------------
Reload & Synchronisation
--------------------------------------------------
*/
    void SyncMainConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client) 
            return;
        Param1<ref MainConfig> configParam;
        if (!ctx.Read(configParam))
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] Failed to read MainConfig from RPC.");
            return;
        }
        g_MainConfig = configParam.param1;
        if (g_MainConfig)
        {
            ApplyIconPosition();
            ApplyIconSize();
            ApplyNotificationPosition();
            ApplyNotificationSize();
            UpdateIcon(g_MainConfig.PvPImagePath);
            NinjinsPvPPvE.LogDebug("[MissionGameplay] MainConfig updated and applied.");
        }
        else
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] MainConfig is null on the client.");
        }
    }
    void ReloadConfigResult(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client)
            return;
        Param2<bool, string> result;
        if (!ctx.Read(result))
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] Failed to read ReloadConfigResult from RPC.");
            return;
        }
        bool   success     = result.param1;
        string sectionKey  = result.param2;
        string friendly;
        if (sectionKey == "MainConfig")
            friendly = "Main Configuration";
        else if (sectionKey == "Zones")
            friendly = "Zones Configuration";
        else if (sectionKey == "AdminConfig")
            friendly = "Admin Configuration";
        else if (sectionKey == "ItemRules")
            friendly = "Item Rules Configuration";
        else
            friendly = "Configuration";
        string title;
        string detail;
        string icon;
        int    color;
        if (success)
        {
            title  = friendly + " Reload Successful";
            detail = "";
            icon   = "NinjinsPvPPvE/gui/checkmark.edds";
            color  = COLOR_GREEN;
        }
        else
        {
            title  = friendly + " Reload Denied";
            detail = "You do not have permission to reload " + friendly + ".";
            icon   = "NinjinsPvPPvE/gui/error.edds";
            color  = COLOR_RED;
        }
        NotificationSystem.Create(new StringLocaliser(title),new StringLocaliser(detail),icon,color,5.0,GetGame().GetPlayer().GetIdentity());
    }
    void ReceiveZones(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client) 
            return;
        Param1<ref array<ref ZoneBase>> data;
        if (!ctx.Read(data))
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] Failed to read zones data from RPC.");
            return;
        }
        m_CachedZones = data.param1;
        NinjinsPvPPvE.LogDebug("[MissionGameplay] Zones data updated and cached. Count: " + m_CachedZones.Count());
        UIScriptedMenu currentMenu = GetGame().GetUIManager().GetMenu();
        if (currentMenu && currentMenu.IsInherited(NinjinsAdminMenu))
        {
            NinjinsAdminMenu adminMenu = NinjinsAdminMenu.Cast(currentMenu);
            NinjinsAdminMenuMap adminMap = adminMenu.GetAdminMap();
            if (adminMap)
            {
                adminMap.UpdateZones();
                adminMap.TriggerUpdate();
            }
            if (!adminMenu.IsZoneEditContainerVisible())
            adminMenu.PopulateZoneList();
        }
    }
    void SyncItemRules(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client) 
            return;
        Param1<ref ItemRules> param;
        if (!ctx.Read(param))
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] Failed to read ItemRules from RPC.");
            return;
        }
        g_ItemRules = param.param1;
        NinjinsPvPPvE.LogDebug("[MissionGameplay] ItemRules synchronized on client.");
    }
    /* ---------- Admin COnfig Sync ------------- */
    void SyncAdminConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client)
            return;
        Param1<ref AdminConfig> adminParam;
        if (!ctx.Read(adminParam))
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] Failed to read AdminConfig from RPC.");
            return;
        }
        g_AdminConfig = adminParam.param1;
        if (g_AdminConfig)
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay] AdminConfig successfully synced. Admin GUIDs: " + g_AdminConfig.AdminGUIDs.ToString());
            PlayerBase clientPlayer = PlayerBase.Cast(GetGame().GetPlayer());
            if (clientPlayer && clientPlayer.GetIdentity())
            {
                string guid = clientPlayer.GetIdentity().GetId();
                bool isAdmin = g_AdminConfig.IsAdmin(guid);
                clientPlayer.SetAdminStatus(isAdmin);
                NinjinsPvPPvE.LogDebug("[MissionGameplay] Player admin status: " + isAdmin);
            }
        }
        else
        {
            NinjinsPvPPvE.LogDebug("[MissionGameplay][ERROR] Received null AdminConfig.");
        }
    }
/*
--------------------------------------------------
DefaultZoneTitles - Default readable Zone Types
--------------------------------------------------
*/
    private string DefaultZoneTitle(int type)
    {
        if (type == ZONE_TYPE_PVP)
        {
            return "PvP Zone";
        }
        else if (type == ZONE_TYPE_PVE)
        {
            return "PvE Zone";
        }
        else if (type == ZONE_TYPE_VISUAL)
        {
            return "Visual Zone";
        }
        else if (type == ZONE_TYPE_RAID)
        {
            return "Raid Zone";
        }
        else if (type == ZONE_TYPE_SAFEZONE)
        {
            return "Safe Zone";
        }
        else if (type == ZONE_TYPE_PAINTBALL)
        {
            return "Paintball Zone";
        }
        else
        {
            return "Unknown Zone";
        }
    }
}