class NinjinsAdminMenu extends UIScriptedMenu
{     
    private TextListboxWidget m_DayList;
    private TextWidget m_SelectedDayText;
    private EditBoxWidget m_StartHourEdit;
    private EditBoxWidget m_EndHourEdit;
    private EditBoxWidget m_DayNameToAdd;
    private ButtonWidget m_AddDayButton;
    private ButtonWidget m_RemoveDayButton;
    private TextListboxWidget m_DayListGlobalPvP;
    private TextWidget m_SelectedDayTextGlobalPvP;
    private EditBoxWidget m_StartHourEditGlobalPvP;
    private EditBoxWidget m_EndHourEditGlobalPvP;
    private EditBoxWidget m_DayNameToAddGlobalPvP;
    private ButtonWidget m_AddDayToDayListGlobalPvP;
    private ButtonWidget m_RemoveDayFromDayListGlobalPvP;
    private TextListboxWidget m_DayListGlobalPvE;
    private TextWidget m_SelectedDayTextGlobalPvE;
    private EditBoxWidget m_StartHourEditGlobalPvE;
    private EditBoxWidget m_EndHourEditGlobalPvE;
    private EditBoxWidget m_DayNameToAddGlobalPvE;
    private ButtonWidget m_AddDayToDayListGlobalPvE;
    private ButtonWidget m_RemoveDayFromDayListGlobalPvE;
    private ref map<string, ref DayConfig> m_DayConfigs = new map<string, ref DayConfig>();
    private string m_CurrentSelectedDay = "";
    private CheckBoxWidget AdminCanSeeAllInactiveZonesCheck;
    private CheckBoxWidget HideWhenNestedTitleValue0;
    private CheckBoxWidget ZoneDrawNoBuildShapeValue;
    private Widget NBItemWhiteListContainer;
    private ButtonWidget BtnAddNBItemWhiteList;
    private ButtonWidget RemoveNBItemWhiteList;
    private CheckBoxWidget ZoneIgnoreHeightCheckValue;
    private EditBoxWidget ZoneMinHeightValue;
    private EditBoxWidget ZoneMaxHeightValue;
    private EditBoxWidget ZoneNoBuildRadiusValue;
    private CheckBoxWidget DrawStrikeLinesForNBValue;
    private EditBoxWidget NoBuildZoneColorValue;
    private ButtonWidget IconBtn;
    private Widget IconPanel;
    private SliderWidget IconsliderX, IconsliderY;
    private Widget previewIconChange;
    private ButtonWidget m_ResetSearchBoxBtn;
    private ButtonWidget m_FilterVehiclesBtn;
    private ButtonWidget m_FilterWeaponsBtn;
    private ButtonWidget m_FilterMagazinesBtn;
    private ButtonWidget m_FilterItemsBtn;
    private ButtonWidget m_FilterAllBtn;
    private ButtonWidget m_FilterFoodBtn;
    private ButtonWidget m_FilterClothingBtn;
    private ButtonWidget m_FilterAIButton;
    private ButtonWidget m_FilterExpansionAIBtn;
    private ref map<Widget, string> m_FilterButtonMap;
    private bool m_FilterByPrefixOnly = false;
    private string m_PrefixFilter = "";
    private string m_CurrentFilterBaseClass = "";
    private Widget AllowedAmmoInPvEStatePanel;
    private TextListboxWidget AllowedAmmoInPvEStatelList;
    private ButtonWidget AllowedAmmoInPvEStateRemove;
    private ButtonWidget AddAllowedAmmoInPvEState;
    private Widget SideBarWidget;
    private MapWidget g_MapWidget;
    private ref NinjinsAdminMenuMap m_AdminMap;
    private Widget m_ActualMapContainer;
    TextListboxWidget m_AllowedAmmoInPaintBallStateList;
    TextListboxWidget m_CantBeDamagedInPvPList;
    TextListboxWidget m_CantBeDamagedInPvEList;
    TextListboxWidget m_SZItemWhiteListList;
    ButtonWidget m_BtnAddPaintballAmmo;
    ButtonWidget m_BtnRemovePaintballAmmo;
    ButtonWidget m_BtnAddSZItemWhiteList;
    ButtonWidget m_BtnRemoveSZItemWhiteList;
    ButtonWidget m_BtnAddPvPItem;
    ButtonWidget m_BtnRemovePvPItem;
    ButtonWidget m_BtnAddPvEItem;
    ButtonWidget m_BtnRemovePvEItem;
    private ButtonWidget wReloadMainConfig;
    private ButtonWidget wReloadZones;
    private ButtonWidget wReloadItemRules;
    private ButtonWidget wReloadAdmins;
    private ButtonWidget MainEdit;
    private ButtonWidget RemoveItemExplosive;
    private ButtonWidget VehicleRemove;
    private ButtonWidget RemoveCantBeDamagedOnGround;
    private ButtonWidget RemoveChecksGrenades;
    private ButtonWidget BTNRemoveAnimal;
    private ButtonWidget DeployPvERemove;
    private ButtonWidget DeployPvPRemove;
    private ButtonWidget DeployRaidRemove;
    private ButtonWidget BtnAddExplosives;
    private ButtonWidget BtnAddVehicle;
    private ButtonWidget BtnAddGrenades;
    private ButtonWidget BtnAddCantBeDamagedOnGround;
    private ButtonWidget BtnAddtoAnimals;
    private ButtonWidget DeployPvEAdd;
    private ButtonWidget DeployPvPAdd;
    private ButtonWidget DeployRaidAdd;
    private TextListboxWidget m_ItemList;
    private EditBoxWidget m_SearchBox;
    private ItemPreviewWidget m_ItemPreviewWidget;
    private EntityAI m_PreviewItem;
    private vector m_Orientation = vector.Zero;
    private int m_MouseX;
    private int m_MouseY;
    private float m_Distance;
    private EditBoxWidget ClassNameToAdd;
    private ButtonWidget btnGeneral;
    private ButtonWidget btnMap;
    private ButtonWidget btnVehicle;
    private ButtonWidget btnLockpick;
    private ButtonWidget btnTerritory;
    private ButtonWidget btnAI;
    private ButtonWidget btnOther;
    private ButtonWidget btnRaid;
    private ButtonWidget btnGeneralApply;
    private ButtonWidget btnGeneralApplyIcon;
    private Widget GeneralRootPanel;
    private Widget MapRootPanel;
    private Widget VehicleRootPanel;
    private Widget LockpickRootPanel;
    private Widget TerritoryRootPanel;
    private Widget AIRootPanel;
    private Widget OtherRootPanel;
    private Widget RaidPanelRoot;
    private Widget zonePropertiesPanel;
    private ButtonWidget ItemRulesEdit;
    private Widget ItemRulesPanel;
    private Widget ItemSearch;
    private Widget PvEBlockedExplosivesDamagePanel;
    private Widget DisallowedVehiclesPanelRules;
    private Widget CantBeDamagedOnGround;
    private Widget BypassZoneChecksGrenades;
    private Widget CantBeDamagedAnimalsinPvE;
    private Widget BlockDeployIfPlayerInPvEStatePanel;
    private Widget BlockDeployIfPlayerInPvPStatePanel;
    private Widget BlockDeployIfPlayerInRaidStatePanel;
    private XComboBoxWidget BlockItemDamageStateorZonesValue0;
    private EditBoxWidget DynamicZoneRemovalRetrySecondsValue;
    private CheckBoxWidget AllowNoRelogOnServerCrashValue;
    private CheckBoxWidget RemoveDynamicZoneOnlyifNoPlayerInsideValue;
    private EditBoxWidget ExpansionReputationPenealtyPveEsPvEValue;
    private CheckBoxWidget EnableExpansionReputationPenaltyPvEvsPvEValue;
    private EditBoxWidget StrikeLineTransparencyValue;
    private XComboBoxWidget StartingDayOfTheWeekValue0;
    private CheckBoxWidget EnableReflectDamageValue0;
    private EditBoxWidget  PvPExitCountdownValue;
    private EditBoxWidget  RaidExitCountdownValue;
    private EditBoxWidget SafeZoneExitCountdownValue;
    private EditBoxWidget PvEZoneExitCountDownValue;
    private CheckBoxWidget SafeZoneZombieKillPanelValue0;
    private CheckBoxWidget SafeZoneAnimalKillPanelValue0;
    private EditBoxWidget SafeZoneZombieKillIntervalValue0;
    private EditBoxWidget SZItemCleanUpIntervalValue;
    private CheckBoxWidget DeleteItemsInSafeZoneValue;
    private CheckBoxWidget AllowRestrainTargetinPvEValue0;
    private CheckBoxWidget AllowRestrainTargetinPvPValue0;
    private CheckBoxWidget AllowRestrainTargetinRaidValue0;
    private CheckBoxWidget ThirdPersonOnlyDriverValue0;
    private CheckBoxWidget EnablePvPEverywhereValue0;
    private CheckBoxWidget EnablePvEEverywhereValue0;
    private CheckBoxWidget ForceFirstPersonGlobalPvPValue0;
    private CheckBoxWidget ForceFirstPersonGlobalPvEValue0;
    private CheckBoxWidget BlockChemGasGrenadeOutsidePvPValue0;
    private EditBoxWidget  LoggingLevelValue0;
    private CheckBoxWidget DisableGiveBloodTargetPvEValue;
    private CheckBoxWidget DisableForceFeedPvEValue;
    private CheckBoxWidget DisableForceDrinkPvEValue;
    private CheckBoxWidget DisableToxicExposureInPvEValue;
    private CheckBoxWidget EnableAFKKickValue;
    private EditBoxWidget  AFKKickTimeoutValue;
    private CheckBoxWidget Mi8CreationValue;
    private CheckBoxWidget UH1YCreationValue;
    private CheckBoxWidget EnableAIMissionZoneCreationValue;
    private CheckBoxWidget AirdropCreationValue;
    private CheckBoxWidget DisableArmExplosivePvEValue;
    private CheckBoxWidget DisableFallDamageValue;
    private CheckBoxWidget DisableFallDamageSZValue;
    private CheckBoxWidget DisableFallDamagePVEValue;
    private CheckBoxWidget EnableKOTHZoneCreationValue;
    private CheckBoxWidget EnableTKKOTHZoneCreationValue;
    private EditBoxWidget CircleDrawingWidthValue;
    private CheckBoxWidget AllowSameZoneTypeEnterNotificationsValue;
    private CheckBoxWidget DisableAiZoneScanningValue;
    private CheckBoxWidget EnableItemSpawnZoneCreationValue;
    private CheckBoxWidget EnableContaminatedZoneCreationValue;
    private EditBoxWidget GlobalPvPZoneDaysValue;
    private EditBoxWidget GlobalPvEZoneDaysValue;
    private CheckBoxWidget EVRStormSZNoShockValue;
    private CheckBoxWidget DisableActionBlockForAdminsValue;
    private EditBoxWidget MessageCannotDeployInSafeZoneValue;
    private EditBoxWidget MessageBlockedItemDeployInPvEValue;
    private EditBoxWidget MessageBlockedItemDeployInPvPValue;
    private EditBoxWidget MessageBlockedItemDeployInRaidValue;
    private EditBoxWidget MessageItemRulesNotInitializedValue;
    private EditBoxWidget NoBuildMessageValue;
    private CheckBoxWidget DrawNamesOnZonesValue0;
    private CheckBoxWidget LB_DrawMiniMapZonesValue0;
    private CheckBoxWidget LB_MiniMapDrawNamesValue0;
    private CheckBoxWidget LB_AdminMapValue;
    private CheckBoxWidget DrawZonesOnVPPAdminValue0;
    private CheckBoxWidget DrawVPPAdminZoneLabelsValue0;
    private CheckBoxWidget DrawZonesOnCOTValue0;
    private CheckBoxWidget DrawCOTAdminZoneLabelsValue0;
    private EditBoxWidget StrikeLineSpacingMetersValue;
    private CheckBoxWidget DisableRaidingDialogActionOnFlagPoleValue;
    private CheckBoxWidget AllowAnyPlayerInRaidZoneValue;
    private TextListboxWidget  m_AllowedPlayersRaidingList;
    private TextListboxWidget m_OnlinePlayersList;
    private ButtonWidget      m_AddToRaidingPlayersBtn;
    private ButtonWidget      m_RemoveRaidingPlayerBtn;
    private ButtonWidget      RefreshPlayerListBTN;
    private CheckBoxWidget AlwaysAllowEnviroDmgValue;
    private EditBoxWidget   NoVehicleZoneKillOrDestroyDelayValue;
    private XComboBoxWidget NoVehicleKillPlayerOrDestroyVehicleValue0;
    private EditBoxWidget   NoVehicleWarningTextValue;
    private XComboBoxWidget NoVehicleWarningEffectValue;
    private EditBoxWidget  NoVehicleWarningEffectIntensityValue;
    private EditBoxWidget NoVehicleZoneExitBlockDelayMSValue;
    private CheckBoxWidget AllowVehicleDamagePvEValue;
    private CheckBoxWidget AllowVehicleDamagePvPValue;
    private CheckBoxWidget AllowVehicleDamageRaidValue;
    private CheckBoxWidget VehicleDamageLoggingValue;
    private EditBoxWidget VehicleZoneCheckIntervalValue;
    private EditBoxWidget  DestroyVehiclePartsValue;
    private EditBoxWidget  RemoveVehicleAttachmentsValue;
    private EditBoxWidget  DestroyVehicleCargoValue;
    private CheckBoxWidget OnlyAllowLockPickInPvPValue0;
    private CheckBoxWidget EnableLockpickingZoneCreationValue0;
    private EditBoxWidget  LockPickZoneDeletionTimeValue;
    private EditBoxWidget  LockpickingZoneRadiusValue;
    private CheckBoxWidget EnableLockpickingNotificationValue0;
    private EditBoxWidget  LockpickNotificationBroadcastRadiusValue;
    private EditBoxWidget  LockpickNotificationIconPathValue;
    private EditBoxWidget  LockpickNotificationTitleValue;
    private EditBoxWidget  LockpickNotificationMessageValue;
    private EditBoxWidget  LockpickNotificationColorValue;
    private CheckBoxWidget ATMRobberyOnlyinPvPLBValue;
    private CheckBoxWidget ATMRobberyEnableZoneCreationValue;
    private CheckBoxWidget ExpansionGroupsFriendlyFireDisabledValue0;
    private CheckBoxWidget AiToPlayerDamageEverywhereValue0;
    private CheckBoxWidget PlayerToAiDamageEverywhereValue0;
    private CheckBoxWidget OnlyAllowAIToDoDamageIfPlayerIsPvPValue0;
    private CheckBoxWidget OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatusValue0;
    private CheckBoxWidget OnlyAllowAIToDoDamageIfPlayerIsPvEValue0;
    private CheckBoxWidget OnlyAllowDamageToAIIfPlayerHasPvEStatusValue0;
    private CheckBoxWidget OnlyAllowAIToDamageInRaidModeValue0;
    private CheckBoxWidget OnlyAllowPlayersToDamageAIInRaidModeValue0;
    private CheckBoxWidget EnableTerritoryFlagZonesValue0;
    private XComboBoxWidget TerritoryFlagZoneCreateModeValue0;
    private EditBoxWidget  TerritoryFlagPvPZoneCheckIntervalValue;
    private EditBoxWidget PvEImagePathValue;
    private EditBoxWidget PvPImagePathValue;
    private EditBoxWidget RaidImagePathValue;
    private EditBoxWidget SafeZoneImagePathValue;
    private EditBoxWidget IconXValue;
    private EditBoxWidget IconYValue;
    private EditBoxWidget IconWidthValue;
    private EditBoxWidget IconHeightValue;
    private EditBoxWidget PvPIconColorValue;
    private EditBoxWidget PvEIconColorValue;
    private EditBoxWidget RaidIconColorValue;
    private EditBoxWidget SafeZoneIconColorValue;
    private EditBoxWidget ExitNotifMessage;
    private CheckBoxWidget BlockedNotificationValue0;
    private EditBoxWidget ExitNotifPanelXValue;
    private EditBoxWidget ExitNotifPanelYValue;
    private EditBoxWidget ExitNotifPanelWidthValue;
    private EditBoxWidget ExitNotifPanelHeightValue;
    private CheckBoxWidget ExitNotificationValue;
    private EditBoxWidget NoLogOutTeleportPosXValue;
    private EditBoxWidget NoLogOutTeleportPosYValue;
    private EditBoxWidget NoLogOutTeleportPosZValue;
    private CheckBoxWidget NoLogOutValue;
    private ButtonWidget NoLogOutPosBTN;
    private CheckBoxWidget HideWhenNestedTitleValue;
    private EditBoxWidget ZoneLabelOffsetXValue;
    private EditBoxWidget ZoneLabelOffsetZValue;
    private EditBoxWidget ZoneLabelColorValue;
    private TextListboxWidget zoneList;
    private Widget TitlePanel;
    private Widget ZoneEditContainer;
    private ButtonWidget ZoneEditBtn;
    private ButtonWidget CloseZoneEditBtn;
    private EditBoxWidget  ZoneNameValue;
    private EditBoxWidget displayNameValue;
    private XComboBoxWidget ZoneTypeValue;
    private XComboBoxWidget ShapeTypeValue;
    private EditBoxWidget  ZonePriorityValue;
    private CheckBoxWidget ZoneEnableCustomMessagesValue;
    private EditBoxWidget  ZoneCustomTitleValue;
    private EditBoxWidget  ZoneCustomMessageEnterValue;
    private EditBoxWidget  ZoneCustomMessageExitValue;
    private EditBoxWidget  ZoneCustomIconValue;
    private EditBoxWidget  ZoneNotificationColorValue;
    private EditBoxWidget  ZoneDaysValue;
    private EditBoxWidget  ZoneStartHourValue;
    private EditBoxWidget  ZoneEndHourValue;
    private CheckBoxWidget ZoneForceFirstPersonValue;
    private CheckBoxWidget ZoneDrawShapeValue;
    private EditBoxWidget  ZoneRadiusValue;
    private EditBoxWidget  ZoneAlphaValue;
    private EditBoxWidget  ZoneRedValue;
    private EditBoxWidget  ZoneGreenValue;
    private EditBoxWidget  ZoneBlueValue;
    private EditBoxWidget ZoneCenterXValue;
    private EditBoxWidget ZoneCenterYValue;
    private EditBoxWidget ZoneCenterZValue;
    private CheckBoxWidget ZoneNoVehicleValue;
    private CheckBoxWidget drawStrikeZoneValue;
    private ButtonWidget PlayerPosButton;
    private CheckBoxWidget EnableExpansion3DMarkerValue;
    private EditBoxWidget ExpansionMarkerNameValue;
    private EditBoxWidget Expansion3DIconValue;
    private CheckBoxWidget EnableExpansion2DMarkerValue;
    private Widget Info1;
    private Widget Info2;
    private ButtonWidget SaveZoneBtn;
    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/NinjinsAdminMenu.layout");
        if (!layoutRoot) 
            return NULL;
        g_MapWidget = MapWidget.Cast(layoutRoot.FindAnyWidget("AdminMapWidget"));
        if (g_MapWidget)
        {
            m_AdminMap = new NinjinsAdminMenuMap(g_MapWidget);
        }
        m_ActualMapContainer = layoutRoot.FindAnyWidget("ActualMapContainer");
        if (m_ActualMapContainer)
            m_ActualMapContainer.Show(false);
        SideBarWidget = layoutRoot.FindAnyWidget("SideBar");
        IconBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("IconBtn"));
        IconPanel = layoutRoot.FindAnyWidget("PanelWidgetIcon");
        IconsliderX = SliderWidget.Cast(layoutRoot.FindAnyWidget("IconsliderX"));
        IconsliderY = SliderWidget.Cast(layoutRoot.FindAnyWidget("IconsliderY"));
        previewIconChange = layoutRoot.FindAnyWidget("previewIconChange");
        if (IconsliderX)
            IconsliderX.SetCurrent(g_MainConfig.IconPositionX);
        if (IconsliderY)
            IconsliderY.SetCurrent(g_MainConfig.IconPositionY);
        UpdatePreviewIconPosition();
/*
--------------------------------------------------
Buttons
--------------------------------------------------
*/ 
        Widget w = layoutRoot.GetChildren();
        while (w) 
        {
            //Print("- " + w.GetName());
            w = w.GetSibling();
        }
        m_DayListGlobalPvP = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("DayListGlobalPvP"));
        m_SelectedDayTextGlobalPvP = TextWidget.Cast(layoutRoot.FindAnyWidget("SelectedDayTextGlobalPvP"));
        m_StartHourEditGlobalPvP = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("StartHourEditGlobalPvP"));
        m_EndHourEditGlobalPvP = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("EndHourEditGlobalPvP"));
        m_DayNameToAddGlobalPvP = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("DayNameToAddGlobalPvP"));
        m_AddDayToDayListGlobalPvP = ButtonWidget.Cast(layoutRoot.FindAnyWidget("AddDayToDayListGlobalPvP"));
        m_RemoveDayFromDayListGlobalPvP = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveDayFromDayListGlobalPvP"));        
        m_DayListGlobalPvE = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("DayListGlobalPvE"));
        m_SelectedDayTextGlobalPvE = TextWidget.Cast(layoutRoot.FindAnyWidget("SelectedDayTextGlobalPvE"));
        m_StartHourEditGlobalPvE = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("StartHourEditGlobalPvE"));
        m_EndHourEditGlobalPvE = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("EndHourEditGlobalPvE"));
        m_DayNameToAddGlobalPvE = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("DayNameToAddGlobalPvE"));
        m_AddDayToDayListGlobalPvE = ButtonWidget.Cast(layoutRoot.FindAnyWidget("AddDayToDayListGlobalPvE"));
        m_RemoveDayFromDayListGlobalPvE = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveDayFromDayListGlobalPvE"));
        m_AllowedAmmoInPaintBallStateList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("AllowedAmmoInPaintBallStateList"));
        m_BtnAddPaintballAmmo = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddPaintballAmmo"));
        m_BtnRemovePaintballAmmo = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemovePaintballAmmo"));
        m_SZItemWhiteListList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ListSZItemWhiteList"));
        m_BtnAddSZItemWhiteList = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddSZItemWhiteList"));
        m_BtnRemoveSZItemWhiteList = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveSZItemWhiteList"));
        m_CantBeDamagedInPvPList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ListCantBeDamagedInPvP"));
        m_CantBeDamagedInPvEList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ListCantBeDamagedInPvE"));
        m_BtnAddPvPItem = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddPvPItem"));
        m_BtnRemovePvPItem = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnRemovePvPItem"));
        m_BtnAddPvEItem = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddPvEItem"));
        m_BtnRemovePvEItem = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnRemovePvEItem"));
        AllowedAmmoInPvEStatePanel = layoutRoot.FindAnyWidget("AllowedAmmoInPvEStatePanel");
        AllowedAmmoInPvEStatelList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("AllowedAmmoInPvEStatelList"));
        AllowedAmmoInPvEStateRemove = ButtonWidget.Cast(layoutRoot.FindAnyWidget("AllowedAmmoInPvEStateRemove"));
        AddAllowedAmmoInPvEState = ButtonWidget.Cast(layoutRoot.FindAnyWidget("AddAllowedAmmoInPvEState"));
        m_FilterVehiclesBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterVehiclesBtn"));
        m_FilterWeaponsBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterWeaponsBtn"));
        m_FilterMagazinesBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterMagazinesBtn"));
        m_FilterItemsBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterItemsBtn"));
        m_FilterAllBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterAllBtn"));
        m_FilterFoodBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterFoodBtn"));
        m_FilterClothingBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterClothingBtn"));
        m_FilterAIButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterAIButton"));
        m_FilterExpansionAIBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterExpansionAIBtn"));
        m_FilterButtonMap = new map<Widget, string>();
        m_FilterButtonMap.Insert(m_FilterExpansionAIBtn, "#EXPANSIONAI");
        m_FilterButtonMap.Insert(m_FilterAllBtn, "");
        m_FilterButtonMap.Insert(m_FilterFoodBtn, "edible_base");
        m_FilterButtonMap.Insert(m_FilterVehiclesBtn, "transport");
        m_FilterButtonMap.Insert(m_FilterWeaponsBtn, "weapon_base");
        m_FilterButtonMap.Insert(m_FilterMagazinesBtn, "Magazine_Base");
        m_FilterButtonMap.Insert(m_FilterClothingBtn, "clothing_base");
        m_FilterButtonMap.Insert(m_FilterItemsBtn, "inventory_base");
        m_FilterButtonMap.Insert(m_FilterAIButton, "dz_lightai");
        m_ItemPreviewWidget = ItemPreviewWidget.Cast(layoutRoot.FindAnyWidget("ItemPreviewWidget"));
        BtnAddExplosives = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddExplosives"));
        BtnAddVehicle = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddVehicle"));
        BtnAddGrenades = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddGrenades"));
        BtnAddCantBeDamagedOnGround = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddCantBeDamagedOnGround"));
        BtnAddtoAnimals = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddtoAnimals"));
        DeployPvEAdd = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DeployPvEAdd"));
        DeployPvPAdd = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DeployPvPAdd"));
        DeployRaidAdd = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DeployRaidAdd"));
        BTNRemoveAnimal = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BTNRemoveAnimal"));
        RemoveChecksGrenades = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveChecksGrenades"));
        RemoveCantBeDamagedOnGround = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveCantBeDamagedOnGround"));
        VehicleRemove = ButtonWidget.Cast(layoutRoot.FindAnyWidget("VehicleRemove"));
        RemoveItemExplosive = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveItemExplosive"));
        DeployPvERemove = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DeployPvERemove"));
        DeployPvPRemove = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DeployPvPRemove"));
        DeployRaidRemove = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DeployRaidRemove"));
        ClassNameToAdd = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ClassNameToAdd"));
        m_ResetSearchBoxBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ResetSearchBoxXML"));
        m_ItemList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ItemListBoxXML0"));
        m_SearchBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SearchBoxXML"));
        ref array<string> availableItems = GetAvailableItemsFromConfig();
        if (m_ItemList)
        {
            m_ItemList.ClearItems();
            foreach (string itemName : availableItems)
            {
                m_ItemList.AddItem(itemName, NULL, 0);
            }
        }
        wReloadMainConfig = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ReloadMainConfig"));
        wReloadZones      = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ReloadZones"));
        wReloadItemRules  = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ReloadItemRules"));
        wReloadAdmins     = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ReloadAdmins"));
        MainEdit = ButtonWidget.Cast(layoutRoot.FindAnyWidget("MainEdit"));
        ItemRulesEdit = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ItemRulesEdit"));
        btnGeneral   = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnGeneral"));
        btnMap       = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnMap"));
        btnVehicle   = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnVehicle"));
        btnLockpick  = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnLockpick"));
        btnTerritory = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnTerritory"));
        btnAI        = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnAI"));
        btnOther     = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnOther"));
        btnRaid = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnRaid"));
        GeneralRootPanel   = layoutRoot.FindAnyWidget("GeneralRootPanel");
        MapRootPanel       = layoutRoot.FindAnyWidget("MapRootPanel");
        VehicleRootPanel   = layoutRoot.FindAnyWidget("VehicleRootPanel");
        LockpickRootPanel  = layoutRoot.FindAnyWidget("LockpickRootPanel");
        TerritoryRootPanel = layoutRoot.FindAnyWidget("TerritoryRootPanel");
        AIRootPanel        = layoutRoot.FindAnyWidget("AIRootPanel");
        OtherRootPanel     = layoutRoot.FindAnyWidget("OtherRootPanel");
        RaidPanelRoot      = layoutRoot.FindAnyWidget("RaidPanel");
        zonePropertiesPanel = layoutRoot.FindAnyWidget("zonePropertiesPanel");
        ItemRulesPanel = layoutRoot.FindAnyWidget("ItemRulesPanel");
        ItemSearch     = layoutRoot.FindAnyWidget("ItemSearch");
        PvEBlockedExplosivesDamagePanel = layoutRoot.FindAnyWidget("PvEBlockedExplosivesDamagePanel");
        DisallowedVehiclesPanelRules = layoutRoot.FindAnyWidget("DisallowedVehiclesPanelRules");
        CantBeDamagedOnGround = layoutRoot.FindAnyWidget("CantBeDamagedOnGround");
        BypassZoneChecksGrenades = layoutRoot.FindAnyWidget("BypassZoneChecksGrenades");
        CantBeDamagedAnimalsinPvE = layoutRoot.FindAnyWidget("CantBeDamagedAnimalsinPvE");
        BlockDeployIfPlayerInPvEStatePanel = layoutRoot.FindAnyWidget("BlockDeployIfPlayerInPvEStatePanel");
        BlockDeployIfPlayerInPvPStatePanel = layoutRoot.FindAnyWidget("BlockDeployIfPlayerInPvPStatePanel");
        BlockDeployIfPlayerInRaidStatePanel = layoutRoot.FindAnyWidget("BlockDeployIfPlayerInRaidStatePanel");
        btnGeneralApply  = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnGeneralApply"));
        btnGeneralApplyIcon = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnGeneralApplyIcon"));
        SaveZoneBtn      = ButtonWidget.Cast(layoutRoot.FindAnyWidget("SaveZone"));
        BlockItemDamageStateorZonesValue0 = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget("BlockItemDamageStateorZonesValue0"));
        DynamicZoneRemovalRetrySecondsValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("DynamicZoneRemovalRetrySecondsValue"));
        ExpansionReputationPenealtyPveEsPvEValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ExpansionReputationPenealtyPveEsPvEValue"));
        EnableExpansionReputationPenaltyPvEvsPvEValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableExpansionReputationPenaltyPvEvsPvEValue"));
        StrikeLineTransparencyValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("StrikeLineTransparencyValue"));
        StartingDayOfTheWeekValue0 = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget("StartingDayOfTheWeekValue0"));
        EnableReflectDamageValue0       = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableReflectDamageValue0"));
        PvPExitCountdownValue           = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PvPExitCountdownValue"));
        RaidExitCountdownValue          = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RaidExitCountdownValue"));
        SafeZoneExitCountdownValue      = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SafeZoneExitCountdownValue0"));
        PvEZoneExitCountDownValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PvEZoneExitCountDownValue"));
        SafeZoneZombieKillPanelValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("SafeZoneZombieKillPanelValue0"));
        SafeZoneAnimalKillPanelValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("SafeZoneAnimalKillPanelValue0"));
        SafeZoneZombieKillIntervalValue0 = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SafeZoneZombieKillIntervalValue0"));
        SZItemCleanUpIntervalValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SZItemCleanUpIntervalValue"));
        DeleteItemsInSafeZoneValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DeleteItemsInSafeZoneValue"));
        AllowRestrainTargetinPvEValue0  = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowRestrainTargetinPvEValue0"));
        AllowRestrainTargetinPvPValue0  = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowRestrainTargetinPvPValue0"));
        AllowRestrainTargetinRaidValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowRestrainTargetinRaidValue0"));
        ThirdPersonOnlyDriverValue0     = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ThirdPersonOnlyDriverValue0"));
        EnablePvPEverywhereValue0       = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnablePvPEverywhereValue0"));
        EnablePvEEverywhereValue0       = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnablePvEEverywhereValue0"));
        ForceFirstPersonGlobalPvPValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ForceFirstPersonGlobalPvPValue0"));
        ForceFirstPersonGlobalPvEValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ForceFirstPersonGlobalPvEValue0"));
        BlockChemGasGrenadeOutsidePvPValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BlockChemGasGrenadeOutsidePvPValue0"));
        LoggingLevelValue0              = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("LoggingLevelValue"));
        DisableGiveBloodTargetPvEValue  = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableGiveBloodTargetPvEValue"));
        DisableForceFeedPvEValue  = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableForceFeedPvEValue"));
        DisableForceDrinkPvEValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableForceDrinkPvEValue"));
        DisableToxicExposureInPvEValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableToxicExposureInPvEValue"));
        EnableAFKKickValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableAFKKickValue"));
        AFKKickTimeoutValue  = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("AFKKickTimeoutValue"));
        Mi8CreationValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("Mi8CreationValue"));
        UH1YCreationValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("UH1YCreationValue"));
        AirdropCreationValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AirdropCreationValue"));
        EnableAIMissionZoneCreationValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableAIMissionZoneCreationValue"));
        DisableArmExplosivePvEValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableArmExplosivePvEValue"));
        DisableFallDamageValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableFallDamageValue"));
        DisableFallDamageSZValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableFallDamageSZValue"));
        DisableFallDamagePVEValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableFallDamagePVEValue"));
        EnableKOTHZoneCreationValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableKOTHZoneCreationValue"));
        EnableTKKOTHZoneCreationValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableTKKOTHZoneCreationValue"));
        CircleDrawingWidthValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CircleDrawingWidthValue"));
        AllowSameZoneTypeEnterNotificationsValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowSameZoneTypeEnterNotificationsValue"));
        DisableAiZoneScanningValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableAiZoneScanningValue"));
        AllowNoRelogOnServerCrashValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowNoRelogOnServerCrashValue"));
        RemoveDynamicZoneOnlyifNoPlayerInsideValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RemoveDynamicZoneOnlyifNoPlayerInsideValue"));
        EnableItemSpawnZoneCreationValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableItemSpawnZoneCreationValue"));
        EnableContaminatedZoneCreationValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableContaminatedZoneCreationValue"));
        GlobalPvPZoneDaysValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("GlobalPvPZoneDaysValue"));
        GlobalPvEZoneDaysValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("GlobalPvEZoneDaysValue"));
        EVRStormSZNoShockValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EVRStormSZNoShockValue"));
        DisableActionBlockForAdminsValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableActionBlockForAdminsValue"));
        NoBuildMessageValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("NoBuildMessageValue"));
        MessageCannotDeployInSafeZoneValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MessageCannotDeployInSafeZoneValue"));
        MessageBlockedItemDeployInPvEValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MessageBlockedItemDeployInPvEValue"));
        MessageBlockedItemDeployInPvPValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MessageBlockedItemDeployInPvPValue"));
        MessageBlockedItemDeployInRaidValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MessageBlockedItemDeployInRaidValue"));
        MessageItemRulesNotInitializedValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MessageItemRulesNotInitializedValue"));
        DisableRaidingDialogActionOnFlagPoleValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableRaidingDialogActionOnFlagPoleValue"));
        AllowAnyPlayerInRaidZoneValue             = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowAnyPlayerInRaidZoneValue"));
        m_AllowedPlayersRaidingList               = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "TextListboxWidgetAllowedPlayersRaiding" ) );
        m_OnlinePlayersList        = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("TextListboxWidgetOnlinePlayers"));
        m_AddToRaidingPlayersBtn   = ButtonWidget.Cast(layoutRoot.FindAnyWidget("AddtoRaidingPlayers"));
        m_RemoveRaidingPlayerBtn   = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveRaidingPlayerBTN"));
        RefreshPlayerListBTN = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RefreshPlayerListBTN"));
        DrawNamesOnZonesValue0    = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DrawNamesOnZonesValue0"));
        LB_DrawMiniMapZonesValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("LB_DrawMiniMapZonesValue0"));
        LB_MiniMapDrawNamesValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("LB_MiniMapDrawNamesValue0"));
        DrawZonesOnVPPAdminValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DrawZonesOnVPPAdminValue0"));
        DrawVPPAdminZoneLabelsValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DrawVPPAdminZoneLabelsValue0"));
        DrawZonesOnCOTValue0         = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DrawZonesOnCOTValue0"));
        DrawCOTAdminZoneLabelsValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DrawCOTAdminZoneLabelsValue0"));
        StrikeLineSpacingMetersValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("StrikeLineSpacingMetersValue"));
        LB_AdminMapValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("LB_AdminMapValue"));
        NoVehicleZoneKillOrDestroyDelayValue  = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("NoVehicleZoneKillOrDestroyDelayValue"));
        NoVehicleKillPlayerOrDestroyVehicleValue0 = XComboBoxWidget .Cast(layoutRoot.FindAnyWidget("NoVehicleKillPlayerOrDestroyVehicleValue0"));
        NoVehicleWarningTextValue             = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("NoVehicleWarningTextValue"));
        NoVehicleWarningEffectValue           = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget("NoVehicleWarningEffectValue"));
        NoVehicleWarningEffectIntensityValue  = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("NoVehicleWarningEffectIntensityValue"));
        DestroyVehiclePartsValue              = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("DestroyVehiclePartsValue"));
        RemoveVehicleAttachmentsValue         = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RemoveVehicleAttachmentsValue"));
        DestroyVehicleCargoValue              = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("DestroyVehicleCargoValue"));
        NoVehicleZoneExitBlockDelayMSValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("NoVehicleZoneExitBlockDelayMSValue"));
        AllowVehicleDamagePvEValue            = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowVehicleDamagePvEValue"));
        AllowVehicleDamagePvPValue            = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowVehicleDamagePvPValue"));
        AllowVehicleDamageRaidValue           = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowVehicleDamageRaidValue"));
        VehicleDamageLoggingValue             = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("VehicleDamageLoggingValue"));
        AlwaysAllowEnviroDmgValue              = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AlwaysAllowEnviroDmgValue"));
        VehicleZoneCheckIntervalValue         = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("VehicleZoneCheckIntervalValue"));
        ATMRobberyOnlyinPvPLBValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ATMRobberyOnlyinPvPLBValue"));
        ATMRobberyEnableZoneCreationValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ATMRobberyEnableZoneCreationValue"));
        OnlyAllowLockPickInPvPValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OnlyAllowLockPickInPvPValue0_Check"));
        EnableLockpickingZoneCreationValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableLockpickingZoneCreationValue0"));
        LockPickZoneDeletionTimeValue       = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("LockPickZoneDeletionTimeValue"));
        LockpickingZoneRadiusValue          = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("LockpickingZoneRadiusValue"));
        EnableLockpickingNotificationValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableLockpickingNotificationValue0"));
        LockpickNotificationBroadcastRadiusValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("LockpickNotificationBroadcastRadiusValue"));
        LockpickNotificationIconPathValue   = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("LockpickNotificationIconPathValue"));
        LockpickNotificationTitleValue      = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("LockpickNotificationTitleValue"));
        LockpickNotificationMessageValue    = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("LockpickNotificationMessageValue"));
        LockpickNotificationColorValue      = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("LockpickNotificationColorValue"));
        ExpansionGroupsFriendlyFireDisabledValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ExpansionGroupsFriendlyFireDisabledValue0"));
        AiToPlayerDamageEverywhereValue0  = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AiToPlayerDamageEverywhereValue0"));
        PlayerToAiDamageEverywhereValue0  = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PlayerToAiDamageEverywhereValue0"));
        OnlyAllowAIToDoDamageIfPlayerIsPvPValue0   = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OnlyAllowAIToDoDamageIfPlayerIsPvPValue0"));
        OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatusValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatusValue0"));
        OnlyAllowAIToDoDamageIfPlayerIsPvEValue0   = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OnlyAllowAIToDoDamageIfPlayerIsPvEValue0"));
        OnlyAllowDamageToAIIfPlayerHasPvEStatusValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OnlyAllowDamageToAIIfPlayerHasPvEStatusValue0"));
        OnlyAllowAIToDamageInRaidModeValue0        = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OnlyAllowAIToDamageInRaidModeValue0"));
        OnlyAllowPlayersToDamageAIInRaidModeValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OnlyAllowPlayersToDamageAIInRaidModeValue0"));
        EnableTerritoryFlagZonesValue0    = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableTerritoryFlagZonesValue0"));
        TerritoryFlagZoneCreateModeValue0 = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget("TerritoryFlagZoneCreateModeValue0"));
        TerritoryFlagPvPZoneCheckIntervalValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("TerritoryFlagPvPZoneCheckIntervalValue"));
        PvPIconColorValue      = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PvPIconColorValue"));
        PvEIconColorValue      = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PvEIconColorValue"));
        RaidIconColorValue     = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RaidIconColorValue"));
        SafeZoneIconColorValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SafeZoneIconColorValue"));
        PvEImagePathValue  = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PvEImagePathValue"));
        PvPImagePathValue  = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PvPImagePathValue"));
        RaidImagePathValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RaidImagePathValue"));
        SafeZoneImagePathValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SafeZoneImagePathValue"));
        IconXValue         = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("IconXValue"));
        IconYValue         = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("IconYValue"));
        IconWidthValue     = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("IconWidthValue"));
        IconHeightValue    = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("IconHeightValue"));
        ExitNotificationValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ExitNotificationValue"));
        BlockedNotificationValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BlockedNotificationValue"));
        ExitNotifMessage = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ExitNotifMessage"));
        ExitNotifPanelXValue     = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ExitNotifPanelXValue"));
        ExitNotifPanelYValue     = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ExitNotifPanelYValue"));
        ExitNotifPanelWidthValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ExitNotifPanelWidthValue"));
        ExitNotifPanelHeightValue= EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ExitNotifPanelHeightValue"));
        NoLogOutTeleportPosXValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("NoLogOutTeleportPosXValue"));
        NoLogOutTeleportPosYValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("NoLogOutTeleportPosYValue"));
        NoLogOutTeleportPosZValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("NoLogOutTeleportPosZValue"));
        NoLogOutValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("NoLogOutValue"));
        HideWhenNestedTitleValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("HideWhenNestedTitleValue"));
        TitlePanel = layoutRoot.FindAnyWidget("TitlePanel");
        ZoneEditContainer = layoutRoot.FindAnyWidget("ZoneEditContainer");
        ZoneEditBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ZoneEditBtn"));
        CloseZoneEditBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("CloseZoneEditBtn"));
        ZoneNameValue               = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneNameValue"));
        displayNameValue            = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("displayNameValue"));
        ZoneTypeValue               = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneTypeValue"));
        ShapeTypeValue              = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget("ShapeTypeValue"));
        ZonePriorityValue           = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZonePriorityValue"));
        ZoneEnableCustomMessagesValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneEnableCustomMessagesValue"));
        ZoneCustomTitleValue        = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneCustomTitleValue"));
        ZoneCustomMessageEnterValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneCustomMessageEnterValue"));
        ZoneCustomMessageExitValue  = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneCustomMessageExitValue"));
        ZoneCustomIconValue         = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneCustomIconValue"));
        ZoneNotificationColorValue  = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneNotificationColorValue"));
        ZoneDaysValue               = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneDaysValue"));
        ZoneStartHourValue          = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneStartHourValue"));
        ZoneEndHourValue            = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneEndHourValue"));
        ZoneForceFirstPersonValue   = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneForceFirstPersonValue"));
        ZoneDrawShapeValue          = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneDrawShapeValue"));
        ZoneRadiusValue             = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneRadiusValue"));
        ZoneAlphaValue              = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneAlphaValue"));
        ZoneRedValue                = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneRedValue"));
        ZoneGreenValue              = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneGreenValue"));
        ZoneBlueValue               = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneBlueValue"));
        zoneList                    = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ZoneList"));
        ZoneCenterXValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneCenterXValue"));
        ZoneCenterYValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneCenterYValue"));
        ZoneCenterZValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneCenterZValue"));
        ZoneNoVehicleValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneNoVehicleValue"));
        PlayerPosButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("PlayerPosButton"));
        drawStrikeZoneValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("drawStrikeZoneValue"));
        EnableExpansion3DMarkerValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableExpansion3DMarkerValue"));
        ExpansionMarkerNameValue     = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ExpansionMarkerNameValue"));
        Expansion3DIconValue         = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Expansion3DIconValue"));
        EnableExpansion2DMarkerValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableExpansion2DMarkerValue"));
        ZoneLabelOffsetXValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneLabelOffsetXValue"));
        ZoneLabelOffsetZValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneLabelOffsetZValue"));
        ZoneLabelColorValue   = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneLabelColorValue"));
        NoLogOutPosBTN = ButtonWidget.Cast(layoutRoot.FindAnyWidget("NoLogOutPosBTN"));
        DrawStrikeLinesForNBValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DrawStrikeLinesForNBValue"));
        NoBuildZoneColorValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("NoBuildZoneColorValue"));
        ZoneNoBuildRadiusValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneNoBuildRadiusValue"));
        ZoneIgnoreHeightCheckValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneIgnoreHeightCheckValue"));
        ZoneMinHeightValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneMinHeightValue"));
        ZoneMaxHeightValue = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneMaxHeightValue"));
        BtnAddNBItemWhiteList = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddNBItemWhiteList"));
        RemoveNBItemWhiteList = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveNBItemWhiteList"));     
        NBItemWhiteListContainer = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("NBItemWhiteListList"));
        HideWhenNestedTitleValue0 = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("HideWhenNestedTitleValue0"));
        ZoneDrawNoBuildShapeValue = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ZoneDrawNoBuildShapeValue"));
        AdminCanSeeAllInactiveZonesCheck = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AdminCanSeeAllInactiveZonesCheck"));
        m_DayList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("DayList"));
        m_SelectedDayText = TextWidget.Cast(layoutRoot.FindAnyWidget("SelectedDayText"));
        m_StartHourEdit = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("StartHourEdit"));
        m_EndHourEdit = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("EndHourEdit"));
        m_DayNameToAdd = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("DayNameToAdd"));
        m_AddDayButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("AddDayToDayList"));
        m_RemoveDayButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveDayFromDayList"));
        Info1 = layoutRoot.FindAnyWidget("Info1");
        Info2 = layoutRoot.FindAnyWidget("Info2");
        layoutRoot.Show(true);
        return layoutRoot;
    }
    override void OnShow()
    {
        super.OnShow();
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        PPEffects.SetBlurMenu(0.5);
        GetGame().GetInput().ChangeGameFocus(1);
        GetGame().GetUIManager().ShowUICursor(true);
        GetGame().GetMission().GetHud().Show(false);
        TIntArray skip = { UAUIBack, UAAdminMenu  };
        ForceDisableInputs(true, skip);
        SetFocus(layoutRoot);
        HideAllPanels();
        if (SideBarWidget)
            SideBarWidget.Show(true);
        if (TitlePanel)
            TitlePanel.Show(true);
        if (GeneralRootPanel)
            GeneralRootPanel.Show(true);
        if (btnGeneralApply)
            btnGeneralApply.Show(true);
        if (SaveZoneBtn)
            SaveZoneBtn.Show(false);
        if (!g_MainConfig) 
            return;
        if (AdminCanSeeAllInactiveZonesCheck)
            AdminCanSeeAllInactiveZonesCheck.SetChecked(g_MainConfig.AdminCanSeeAllInactiveZones == 1);
        if (DrawStrikeLinesForNBValue)
            DrawStrikeLinesForNBValue.SetChecked(g_MainConfig.drawStrikeLinesForNB == 1);
        if (NoBuildZoneColorValue)
            NoBuildZoneColorValue.SetText(g_MainConfig.noBuildZoneColor.ToString());
        if (BlockItemDamageStateorZonesValue0)
            BlockItemDamageStateorZonesValue0.SetCurrentItem(g_MainConfig.BlockItemDamageStateorZones);
        if (PvPIconColorValue)
        {
            PvPIconColorValue.SetText(g_MainConfig.PvPIconColor.ToString());
            PvPIconColorValue.SetColor(g_MainConfig.PvPIconColor);
        }
        if (PvEIconColorValue)
        {
            PvEIconColorValue.SetText(g_MainConfig.PvEIconColor.ToString());
            PvEIconColorValue.SetColor(g_MainConfig.PvEIconColor);
        }
        if (RaidIconColorValue)
        {
            RaidIconColorValue.SetText(g_MainConfig.RaidIconColor.ToString());
            RaidIconColorValue.SetColor(g_MainConfig.RaidIconColor);
        }
        if (SafeZoneIconColorValue)
        {
            SafeZoneIconColorValue.SetText(g_MainConfig.SafeZoneIconColor.ToString());
            SafeZoneIconColorValue.SetColor(g_MainConfig.SafeZoneIconColor);
        }
        if (MessageCannotDeployInSafeZoneValue)
            MessageCannotDeployInSafeZoneValue.SetText(g_MainConfig.MessageCannotDeployInSafeZone);
        if (NoBuildMessageValue)
            NoBuildMessageValue.SetText(g_MainConfig.NoBuildMessage);
        if (MessageBlockedItemDeployInPvEValue)
            MessageBlockedItemDeployInPvEValue.SetText(g_MainConfig.MessageBlockedItemDeployInPvE);
        if (MessageBlockedItemDeployInPvPValue)
            MessageBlockedItemDeployInPvPValue.SetText(g_MainConfig.MessageBlockedItemDeployInPvP);
        if (MessageBlockedItemDeployInRaidValue)
            MessageBlockedItemDeployInRaidValue.SetText(g_MainConfig.MessageBlockedItemDeployInRaid);
        if (MessageItemRulesNotInitializedValue)
            MessageItemRulesNotInitializedValue.SetText(g_MainConfig.MessageItemRulesNotInitialized);
        if (DynamicZoneRemovalRetrySecondsValue)
            DynamicZoneRemovalRetrySecondsValue.SetText(g_MainConfig.DynamicZoneRemovalRetrySeconds.ToString());
        if (AllowNoRelogOnServerCrashValue)
            AllowNoRelogOnServerCrashValue.SetChecked(g_MainConfig.AllowNoRelogOnServerCrash);
        if (RemoveDynamicZoneOnlyifNoPlayerInsideValue)
            RemoveDynamicZoneOnlyifNoPlayerInsideValue.SetChecked(g_MainConfig.RemoveDynamicZoneOnlyifNoPlayerInside);
        if (ExpansionReputationPenealtyPveEsPvEValue)
            ExpansionReputationPenealtyPveEsPvEValue.SetText(g_MainConfig.ExpansionReputationPenealtyPveEsPvE.ToString());
        if (EnableExpansionReputationPenaltyPvEvsPvEValue)
            EnableExpansionReputationPenaltyPvEvsPvEValue.SetChecked(g_MainConfig.EnableExpansionReputationPenaltyPvEvsPvE);
        if (StrikeLineTransparencyValue)
        StrikeLineTransparencyValue.SetText(g_MainConfig.StrikeLineTransparency.ToString());
        if (DisableActionBlockForAdminsValue)
            DisableActionBlockForAdminsValue.SetChecked(g_MainConfig.DisableActionBlockForAdmins == 1);
        if (EVRStormSZNoShockValue)
            EVRStormSZNoShockValue.SetChecked(g_MainConfig.EVRStormSZNoShock);
        if (LB_AdminMapValue)
            LB_AdminMapValue.SetChecked(g_MainConfig.LB_AdminMapZones);
        if (m_DayListGlobalPvP && g_MainConfig.GlobalPvPZoneDays)
        {
            m_DayListGlobalPvP.ClearItems();
            //Print("[NinjinsPvPPvE] Loading GlobalPvP days. Total days: " + g_MainConfig.GlobalPvPZoneDays.Count().ToString());
            array<int> dayIndices = new array<int>;
            for (int dayIdx = 0; dayIdx < g_MainConfig.GlobalPvPZoneDays.Count(); dayIdx++)
            {
                DayConfig dayCfg = g_MainConfig.GlobalPvPZoneDays.Get(dayIdx);
                if (dayCfg)
                {
                    //Print(string.Format("[NinjinsPvPPvE] Adding day: %1 (Start: %2, End: %3)", 
                    //    dayCfg.dayName, dayCfg.startHour.ToString(), dayCfg.endHour.ToString()));
                    m_DayListGlobalPvP.AddItem(dayCfg.dayName, NULL, 0);
                }
                else
                {
                    //Print("[NinjinsPvPPvE] Warning: Null day config at index " + dayIdx.ToString());
                }
            }           
            if (m_DayListGlobalPvP.GetNumItems() > 0)
            {              
                OnGlobalPvPDaySelected();
            }
        }
        if (m_DayListGlobalPvE && g_MainConfig.GlobalPvEZoneDays)
        {
            m_DayListGlobalPvE.ClearItems();
            //Print("[NinjinsPvPPvE] Loading GlobalPvE days. Total days: " + g_MainConfig.GlobalPvEZoneDays.Count().ToString());
            array<int> pveDayIndices = new array<int>;
            for (int pveDayIdx = 0; pveDayIdx < g_MainConfig.GlobalPvEZoneDays.Count(); pveDayIdx++)
            {
                DayConfig pveDayCfg = g_MainConfig.GlobalPvEZoneDays.Get(pveDayIdx);
                if (pveDayCfg)
                {
                    //Print(string.Format("[NinjinsPvPPvE] Adding GlobalPvE day: %1 (Start: %2, End: %3)", 
                    //    pveDayCfg.dayName, pveDayCfg.startHour.ToString(), pveDayCfg.endHour.ToString()));
                    m_DayListGlobalPvE.AddItem(pveDayCfg.dayName, NULL, 0);
                }
                else
                {
                    //Print("[NinjinsPvPPvE] Warning: Null GlobalPvE day config at index " + pveDayIdx.ToString());
                }
            }
            if (m_DayListGlobalPvE.GetNumItems() > 0)
            {              
                OnGlobalPvEDaySelected();
            }
        }
        if (StrikeLineSpacingMetersValue)
            StrikeLineSpacingMetersValue.SetText(g_MainConfig.StrikeLineSpacingMeters.ToString());
        if (NoVehicleZoneExitBlockDelayMSValue)
            NoVehicleZoneExitBlockDelayMSValue.SetText(g_MainConfig.NoVehicleZoneExitBlockDelayMS.ToString());
        if (DisableAiZoneScanningValue)
            DisableAiZoneScanningValue.SetChecked(g_MainConfig.DisableAiZoneScanning == 1);
        if (EnableItemSpawnZoneCreationValue)
            EnableItemSpawnZoneCreationValue.SetChecked(g_MainConfig.EnableItemSpawnZoneCreation == 1);
        if (EnableContaminatedZoneCreationValue)
            EnableContaminatedZoneCreationValue.SetChecked(g_MainConfig.EnableContaminatedZoneCreation == 1);
        if (AllowSameZoneTypeEnterNotificationsValue)
            AllowSameZoneTypeEnterNotificationsValue.SetChecked(g_MainConfig.AllowSameZoneTypeEnterNotifications == 1);
        if (CircleDrawingWidthValue)
            CircleDrawingWidthValue.SetText(g_MainConfig.CircleDrawingWidth.ToString());
        #ifdef RizenKOTH
        if (EnableTKKOTHZoneCreationValue)
            EnableTKKOTHZoneCreationValue.SetChecked(g_MainConfig.EnableTKKOTHZoneCreation == 1);
        #endif
        #ifdef mz_koth
        if (EnableKOTHZoneCreationValue)
            EnableKOTHZoneCreationValue.SetChecked(g_MainConfig.EnableKOTHZoneCreation == 1);
        #endif
        if (ATMRobberyOnlyinPvPLBValue)
            ATMRobberyOnlyinPvPLBValue.SetChecked(g_MainConfig.LB_ATMRobberyOnlyInPvP == 1);
        if (ATMRobberyEnableZoneCreationValue)
            ATMRobberyEnableZoneCreationValue.SetChecked(g_MainConfig.LB_ATMRobberyEnableZoneCreation == 1);
        if (StartingDayOfTheWeekValue0)
            StartingDayOfTheWeekValue0.SetCurrentItem(g_MainConfig.StartingDayOfTheWeek);
        if (EnableReflectDamageValue0)
            EnableReflectDamageValue0.SetChecked(g_MainConfig.EnableReflectDamage);
        if (DisableFallDamageValue)
            DisableFallDamageValue.SetChecked(g_MainConfig.DisableFallDamage);
        if (DisableFallDamageSZValue)
            DisableFallDamageSZValue.SetChecked(g_MainConfig.DisableFallDamageSZ);
        if (DisableFallDamagePVEValue)
            DisableFallDamagePVEValue.SetChecked(g_MainConfig.DisableFallDamagePvE);
        if (PvPExitCountdownValue)
            PvPExitCountdownValue.SetText(g_MainConfig.PvPExitCountdown.ToString());
        if (RaidExitCountdownValue)
            RaidExitCountdownValue.SetText(g_MainConfig.RaidExitCountdown.ToString());
        if (SafeZoneExitCountdownValue)
            SafeZoneExitCountdownValue.SetText(g_MainConfig.SafeZoneExitCountdown.ToString());
        if (PvEZoneExitCountDownValue)
            PvEZoneExitCountDownValue.SetText(g_MainConfig.PvEExitCountdown.ToString());
        if (SafeZoneZombieKillPanelValue0)
            SafeZoneZombieKillPanelValue0.SetChecked(g_MainConfig.KillZombiesInSafeZone == 1);
        if (SafeZoneAnimalKillPanelValue0)
            SafeZoneAnimalKillPanelValue0.SetChecked(g_MainConfig.KillAnimalsInSafeZone == 1);
        if (SafeZoneZombieKillIntervalValue0)
            SafeZoneZombieKillIntervalValue0.SetText(g_MainConfig.ZombieandAnimalSZKillScanInterval.ToString());
        if (SZItemCleanUpIntervalValue)
            SZItemCleanUpIntervalValue.SetText(g_MainConfig.SZItemCleanUpInterval.ToString());
        if (DeleteItemsInSafeZoneValue)
            DeleteItemsInSafeZoneValue.SetChecked(g_MainConfig.DeleteItemsInSafeZone == 1);
        if (Mi8CreationValue)
            Mi8CreationValue.SetChecked(g_MainConfig.EnableMi8ZoneCreation == 1);
        if (UH1YCreationValue)
            UH1YCreationValue.SetChecked(g_MainConfig.EnableUH1YZoneCreation == 1);
        if (AirdropCreationValue)
            AirdropCreationValue.SetChecked(g_MainConfig.EnableAirdropZoneCreation == 1);
        if (EnableAIMissionZoneCreationValue)
            EnableAIMissionZoneCreationValue.SetChecked(g_MainConfig.EnableAIMissionZoneCreation == 1);
        if (DisableArmExplosivePvEValue)
            DisableArmExplosivePvEValue.SetChecked(g_MainConfig.DisableArmExplosivePvE == 1);
        if (DisableRaidingDialogActionOnFlagPoleValue)
            DisableRaidingDialogActionOnFlagPoleValue.SetChecked(g_MainConfig.DisableRaidingDialogActionOnFlagPole == 1);
        if (AllowAnyPlayerInRaidZoneValue)
            AllowAnyPlayerInRaidZoneValue.SetChecked(g_MainConfig.AllowAnyPlayerInRaidZone == 1);
        if (EnableAFKKickValue)
            EnableAFKKickValue.SetChecked(g_MainConfig.EnableAFKKick == 1);
        if (AFKKickTimeoutValue)
            AFKKickTimeoutValue.SetText(g_MainConfig.AFKKickTimeout.ToString());
        if (AllowRestrainTargetinPvEValue0)
            AllowRestrainTargetinPvEValue0.SetChecked(g_MainConfig.AllowRestrainTargetinPvE == 1);
        if (AllowRestrainTargetinPvPValue0)
            AllowRestrainTargetinPvPValue0.SetChecked(g_MainConfig.AllowRestrainTargetinPvP == 1);
        if (AllowRestrainTargetinRaidValue0)
            AllowRestrainTargetinRaidValue0.SetChecked(g_MainConfig.AllowRestrainTargetinRaid == 1);
        if (DisableGiveBloodTargetPvEValue)
            DisableGiveBloodTargetPvEValue.SetChecked(g_MainConfig.DisableGiveBloodTargetPvE == 1);
        if (DisableForceFeedPvEValue)
            DisableForceFeedPvEValue.SetChecked(g_MainConfig.DisableForceFeedPvE == 1);
        if (DisableForceDrinkPvEValue)
            DisableForceDrinkPvEValue.SetChecked(g_MainConfig.DisableForceDrinkPvE == 1);
        if (DisableToxicExposureInPvEValue)
            DisableToxicExposureInPvEValue.SetChecked(g_MainConfig.DisableToxicExposureInPvE == 1);
        if (ThirdPersonOnlyDriverValue0)
            ThirdPersonOnlyDriverValue0.SetChecked(g_MainConfig.ThirdPersonOnlyDriver == 1);
        if (EnablePvPEverywhereValue0)
            EnablePvPEverywhereValue0.SetChecked(g_MainConfig.EnablePvPEverywhere == 1);
        if (EnablePvEEverywhereValue0)
            EnablePvEEverywhereValue0.SetChecked(g_MainConfig.EnablePvEEverywhere == 1);
        if (ForceFirstPersonGlobalPvPValue0)
            ForceFirstPersonGlobalPvPValue0.SetChecked(g_MainConfig.ForceFirstPersonGlobalPvP == 1);
        if (ForceFirstPersonGlobalPvEValue0)
            ForceFirstPersonGlobalPvEValue0.SetChecked(g_MainConfig.ForceFirstPersonGlobalPvE == 1);
        if (BlockChemGasGrenadeOutsidePvPValue0)
            BlockChemGasGrenadeOutsidePvPValue0.SetChecked(g_MainConfig.BlockChemGasGrenadeOutsidePvP == 1);
        if (LoggingLevelValue0)
            LoggingLevelValue0.SetText(g_MainConfig.LoggingLevel.ToString());
        if (DrawNamesOnZonesValue0)
            DrawNamesOnZonesValue0.SetChecked(g_MainConfig.DrawNamesOnZones == 1);
        if (LB_DrawMiniMapZonesValue0)
            LB_DrawMiniMapZonesValue0.SetChecked(g_MainConfig.LB_DrawMiniMapZones == 1);
        if (LB_MiniMapDrawNamesValue0)
            LB_MiniMapDrawNamesValue0.SetChecked(g_MainConfig.LB_MiniMapDrawNames == 1);
        if (DrawZonesOnVPPAdminValue0)
            DrawZonesOnVPPAdminValue0.SetChecked(g_MainConfig.DrawZonesOnVPPAdmin == 1);
        if (DrawVPPAdminZoneLabelsValue0)
            DrawVPPAdminZoneLabelsValue0.SetChecked(g_MainConfig.DrawVPPAdminZoneLabels == 1);
        if (DrawZonesOnCOTValue0)
            DrawZonesOnCOTValue0.SetChecked(g_MainConfig.DrawZonesOnCOT == 1);
        if (DrawCOTAdminZoneLabelsValue0)
            DrawCOTAdminZoneLabelsValue0.SetChecked(g_MainConfig.DrawCOTAdminZoneLabels == 1);
        if (NoVehicleZoneKillOrDestroyDelayValue)
            NoVehicleZoneKillOrDestroyDelayValue.SetText(g_MainConfig.NoVehicleZoneKillOrDestroyDelay.ToString());
        if (NoVehicleKillPlayerOrDestroyVehicleValue0)
            NoVehicleKillPlayerOrDestroyVehicleValue0.SetCurrentItem(g_MainConfig.NoVehicleKillPlayerOrDestroyVehicle);
        if (NoVehicleWarningTextValue)
            NoVehicleWarningTextValue.SetText(g_MainConfig.NoVehicleWarningText);
        if (NoVehicleWarningEffectValue)
        {
            string currentEffect = g_MainConfig.NoVehicleWarningEffect;
            int effectIndex = 0;
            if (currentEffect == "shock")
                effectIndex = 0;
            else if (currentEffect == "blur")
                effectIndex = 1;
            else if (currentEffect == "blood")
                effectIndex = 2;
            else if (currentEffect == "redscreen")
                effectIndex = 3;
            else if (currentEffect == "blackscreen")
                effectIndex = 4;
            else
                effectIndex = 0;
            NoVehicleWarningEffectValue.SetCurrentItem(effectIndex);
        }
        if (NoVehicleWarningEffectIntensityValue)
            NoVehicleWarningEffectIntensityValue.SetText(g_MainConfig.NoVehicleWarningEffectIntensity.ToString());
        #ifdef NinjinsPvPPvE_Vehicles
        if (AllowVehicleDamagePvEValue)
            AllowVehicleDamagePvEValue.SetChecked(g_MainConfig.AllowVehicleDamagePvE  == 1);
        if (AllowVehicleDamagePvPValue)
            AllowVehicleDamagePvPValue.SetChecked(g_MainConfig.AllowVehicleDamagePvP  == 1);
        if (AllowVehicleDamageRaidValue)
            AllowVehicleDamageRaidValue.SetChecked(g_MainConfig.AllowVehicleDamageRaid  == 1);
        if (VehicleDamageLoggingValue)
            VehicleDamageLoggingValue.SetChecked(g_MainConfig.VehicleDamageLogging  == 1);
        if (VehicleZoneCheckIntervalValue)
            VehicleZoneCheckIntervalValue.SetText(g_MainConfig.VehicleZoneCheckInterval.ToString());
        if (AlwaysAllowEnviroDmgValue)
            AlwaysAllowEnviroDmgValue.SetChecked(g_MainConfig.AlwaysAllowEnviroDmg);
        #endif
        if (DestroyVehiclePartsValue && g_MainConfig.DestroyVehicleParts)
        {
            string partsString = "";
            for (int f = 0; f < g_MainConfig.DestroyVehicleParts.Count(); f++)
            {
                partsString += g_MainConfig.DestroyVehicleParts[f];
                if (f < g_MainConfig.DestroyVehicleParts.Count() - 1)
                    partsString += ", ";
            }
            DestroyVehiclePartsValue.SetText(partsString);
        }
        if (RemoveVehicleAttachmentsValue && g_MainConfig.RemoveVehicleAttachments)
        {
            string attachmentsString = "";
            for (int j = 0; j < g_MainConfig.RemoveVehicleAttachments.Count(); j++)
            {
                attachmentsString += g_MainConfig.RemoveVehicleAttachments[j];
                if (j < g_MainConfig.RemoveVehicleAttachments.Count() - 1)
                    attachmentsString += ", ";
            }
            RemoveVehicleAttachmentsValue.SetText(attachmentsString);
        }
        if (DestroyVehicleCargoValue && g_MainConfig.DestroyVehicleCargo)
        {
            string cargoString = "";
            for (int k = 0; k < g_MainConfig.DestroyVehicleCargo.Count(); k++)
            {
                cargoString += g_MainConfig.DestroyVehicleCargo[k];
                if (k < g_MainConfig.DestroyVehicleCargo.Count() - 1)
                    cargoString += ", ";
            }
            DestroyVehicleCargoValue.SetText(cargoString);
        }
        if (OnlyAllowLockPickInPvPValue0)
            OnlyAllowLockPickInPvPValue0.SetChecked(g_MainConfig.OnlyAllowLockPickInPvP == 1);
        if (EnableLockpickingZoneCreationValue0)
            EnableLockpickingZoneCreationValue0.SetChecked(g_MainConfig.EnableLockpickingZoneCreation == 1);
        if (LockPickZoneDeletionTimeValue)
            LockPickZoneDeletionTimeValue.SetText(g_MainConfig.LockPickZoneDeletionTime.ToString());
        if (LockpickingZoneRadiusValue)
            LockpickingZoneRadiusValue.SetText(g_MainConfig.LockpickingZoneRadius.ToString());
        if (EnableLockpickingNotificationValue0)
            EnableLockpickingNotificationValue0.SetChecked(g_MainConfig.EnableLockpickingNotification == 1);
        if (LockpickNotificationBroadcastRadiusValue)
            LockpickNotificationBroadcastRadiusValue.SetText(g_MainConfig.LockpickNotificationBroadcastRadius.ToString());
        if (LockpickNotificationIconPathValue)
            LockpickNotificationIconPathValue.SetText(g_MainConfig.LockpickNotificationIconPath);
        if (LockpickNotificationTitleValue)
            LockpickNotificationTitleValue.SetText(g_MainConfig.LockpickNotificationTitle);
        if (LockpickNotificationMessageValue)
            LockpickNotificationMessageValue.SetText(g_MainConfig.LockpickNotificationMessage);
        if (LockpickNotificationColorValue)
            LockpickNotificationColorValue.SetText(g_MainConfig.LockpickNotificationColor.ToString());
        if (ExpansionGroupsFriendlyFireDisabledValue0)
            ExpansionGroupsFriendlyFireDisabledValue0.SetChecked(g_MainConfig.ExpansionGroupsFriendlyFireDisabled == 1);
        if (AiToPlayerDamageEverywhereValue0)
            AiToPlayerDamageEverywhereValue0.SetChecked(g_MainConfig.AiToPlayerDamageEverywhere == 1);
        if (PlayerToAiDamageEverywhereValue0)
            PlayerToAiDamageEverywhereValue0.SetChecked(g_MainConfig.PlayerToAiDamageEverywhere == 1);
        if (OnlyAllowAIToDoDamageIfPlayerIsPvPValue0)
            OnlyAllowAIToDoDamageIfPlayerIsPvPValue0.SetChecked(g_MainConfig.OnlyAllowAIToDoDamageIfPlayerIsPvP == 1);
        if (OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatusValue0)
            OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatusValue0.SetChecked(g_MainConfig.OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatus == 1);
        if (OnlyAllowAIToDoDamageIfPlayerIsPvEValue0)
            OnlyAllowAIToDoDamageIfPlayerIsPvEValue0.SetChecked(g_MainConfig.OnlyAllowAIToDoDamageIfPlayerIsPvE == 1);
        if (OnlyAllowDamageToAIIfPlayerHasPvEStatusValue0)
            OnlyAllowDamageToAIIfPlayerHasPvEStatusValue0.SetChecked(g_MainConfig.OnlyAllowDamageToAIIfPlayerHasPvEStatus == 1);
        if (OnlyAllowAIToDamageInRaidModeValue0)
            OnlyAllowAIToDamageInRaidModeValue0.SetChecked(g_MainConfig.OnlyAllowAIToDamageInRaidMode == 1);
        if (OnlyAllowPlayersToDamageAIInRaidModeValue0)
            OnlyAllowPlayersToDamageAIInRaidModeValue0.SetChecked(g_MainConfig.OnlyAllowPlayersToDamageAIInRaidMode == 1);
        if (EnableTerritoryFlagZonesValue0)
            EnableTerritoryFlagZonesValue0.SetChecked(g_MainConfig.EnableTerritoryFlagZones == 1);
        if (TerritoryFlagZoneCreateModeValue0)
            TerritoryFlagZoneCreateModeValue0.SetCurrentItem(g_MainConfig.TerritoryFlagZoneCreateMode);
        if (TerritoryFlagPvPZoneCheckIntervalValue)
            TerritoryFlagPvPZoneCheckIntervalValue.SetText(g_MainConfig.TerritoryFlagPvPZoneCheckInterval.ToString());
        if (PvEImagePathValue)
            PvEImagePathValue.SetText(g_MainConfig.PvEImagePath);
        if (PvPImagePathValue)
            PvPImagePathValue.SetText(g_MainConfig.PvPImagePath);
        if (RaidImagePathValue)
            RaidImagePathValue.SetText(g_MainConfig.RaidImagePath);
        if (SafeZoneImagePathValue)
            SafeZoneImagePathValue.SetText(g_MainConfig.SafeZoneImagePath);
        if (IconXValue)
            IconXValue.SetText(g_MainConfig.IconPositionX.ToString());
        if (IconYValue)
            IconYValue.SetText(g_MainConfig.IconPositionY.ToString());
        if (IconsliderX)
            IconsliderX.SetCurrent(g_MainConfig.IconPositionX);
        if (IconsliderY)
            IconsliderY.SetCurrent(g_MainConfig.IconPositionY);
        if (IconWidthValue)
            IconWidthValue.SetText(g_MainConfig.IconWidth.ToString());
        if (IconHeightValue)
            IconHeightValue.SetText(g_MainConfig.IconHeight.ToString());
        if (ExitNotificationValue)
            ExitNotificationValue.SetChecked(g_MainConfig.ExitZoneNotification == 1);
        if (BlockedNotificationValue0)
            BlockedNotificationValue0.SetChecked(g_MainConfig.PvPtoPvEBlockedNotification == 1);
        if (ExitNotifMessage)
            ExitNotifMessage.SetText(g_MainConfig.ExitNotificationText);
        if (ExitNotifPanelXValue)
            ExitNotifPanelXValue.SetText(g_MainConfig.ExitNotificationPanelPositionX.ToString());
        if (ExitNotifPanelYValue)
            ExitNotifPanelYValue.SetText(g_MainConfig.ExitNotificationPanelPositionY.ToString());
        if (ExitNotifPanelWidthValue)
            ExitNotifPanelWidthValue.SetText(g_MainConfig.NotificationPanelWidth.ToString());
        if (ExitNotifPanelHeightValue)
            ExitNotifPanelHeightValue.SetText(g_MainConfig.NotificationPanelHeight.ToString());
        RefreshAllCheckBoxes(layoutRoot);
    }
    override void OnHide()
    {
        super.OnHide();
        if (m_PreviewItem)
        {
            GetGame().ObjectDelete(m_PreviewItem);
            m_PreviewItem = null;
        }
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        ForceDisableInputs(false);
        PPEffects.SetBlurMenu(0);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor(false);
        GetGame().GetMission().GetHud().Show(true);
        Close();
    }
    private void HideAllPanels()
    {
        array<Widget> noneToShow = { SideBarWidget };
        ShowOnlyPanels(noneToShow);
    }
    private void ShowOnlyPanel(Widget panelToShow, bool showTitlePanel = true)
    {
        GeneralRootPanel.Show(false);
        MapRootPanel.Show(false);
        VehicleRootPanel.Show(false);
        LockpickRootPanel.Show(false);
        TerritoryRootPanel.Show(false);
        AIRootPanel.Show(false);
        OtherRootPanel.Show(false);
        RaidPanelRoot.Show(false);
        ZoneEditContainer.Show(false);
        g_MapWidget.Show(false);
        m_ActualMapContainer.Show(false);
        TitlePanel.Show(false);
        if (showTitlePanel && TitlePanel)
            TitlePanel.Show(true);
        if (panelToShow)
            panelToShow.Show(true);
    }
    void OnDaySelected()
    {
        if (!m_DayList || !m_StartHourEdit || !m_EndHourEdit || !m_SelectedDayText) 
            return;
        int dayRow = m_DayList.GetSelectedRow();
        if (dayRow < 0) 
            return;
        string dayName;
        m_DayList.GetItemText(dayRow, 0, dayName);
        if (m_CurrentSelectedDay != "" && m_DayConfigs.Contains(m_CurrentSelectedDay)) 
        {
            DayConfig currentConfig = m_DayConfigs.Get(m_CurrentSelectedDay);
            currentConfig.startHour = m_StartHourEdit.GetText().ToInt();
            currentConfig.endHour = m_EndHourEdit.GetText().ToInt();
        }
        if (m_DayConfigs.Contains(dayName)) 
        {
            DayConfig config = m_DayConfigs.Get(dayName);
            m_StartHourEdit.SetText(config.startHour.ToString());
            m_EndHourEdit.SetText(config.endHour.ToString());
            m_SelectedDayText.SetText(dayName);
            m_CurrentSelectedDay = dayName;
        }
    }
    void OnGlobalPvPDaySelected()
    {
        if (!m_DayListGlobalPvP || !m_EndHourEditGlobalPvP || !m_SelectedDayTextGlobalPvP) 
        {
            //Print("[NinjinsPvPPvE] Error: Missing required UI elements in OnGlobalPvPDaySelected");
            return;
        }
        int dayRow = m_DayListGlobalPvP.GetSelectedRow();
        if (dayRow < 0)
        {
            //Print("[NinjinsPvPPvE] No day selected in GlobalPvP day list");
            return;
        }
        string dayName;
        m_DayListGlobalPvP.GetItemText(dayRow, 0, dayName);
        //Print("[NinjinsPvPPvE] Selected day: " + dayName);
        bool found = false;
        for (int i = 0; i < g_MainConfig.GlobalPvPZoneDays.Count(); i++)
        {
            DayConfig dayCfg = g_MainConfig.GlobalPvPZoneDays.Get(i);
            if (dayCfg && dayCfg.dayName == dayName)
            {
                //Print(string.Format("[NinjinsPvPPvE] Found day config: %1, Start: %2, End: %3", 
                //    dayCfg.dayName, dayCfg.startHour.ToString(), dayCfg.endHour.ToString()));
                if (m_StartHourEditGlobalPvP) 
                {
                    m_StartHourEditGlobalPvP.SetText(dayCfg.startHour.ToString());
                }
                m_EndHourEditGlobalPvP.SetText(dayCfg.endHour.ToString());
                m_SelectedDayTextGlobalPvP.SetText(dayCfg.dayName);
                found = true;
                break;
            }
        }
        if (!found)
        {
            //Print("[NinjinsPvPPvE] Could not find config for day: " + dayName);
            if (m_StartHourEditGlobalPvP) 
            {
                m_StartHourEditGlobalPvP.SetText("");
            }
            m_EndHourEditGlobalPvP.SetText("");
            m_SelectedDayTextGlobalPvP.SetText(dayName);
        }
    }
    void OnGlobalPvEDaySelected()
    {
        if (!m_DayListGlobalPvE || !m_EndHourEditGlobalPvE || !m_SelectedDayTextGlobalPvE) 
        {
            //Print("[NinjinsPvPPvE] Error: Missing required UI elements in OnGlobalPvEDaySelected");
            return;
        }
        int dayRow = m_DayListGlobalPvE.GetSelectedRow();
        if (dayRow < 0)
        {
            //Print("[NinjinsPvPPvE] No day selected in GlobalPvE day list");
            return;
        }
        string dayName;
        m_DayListGlobalPvE.GetItemText(dayRow, 0, dayName);
        //Print("[NinjinsPvPPvE] Selected day: " + dayName);
        bool found = false;
        for (int i = 0; i < g_MainConfig.GlobalPvEZoneDays.Count(); i++)
        {
            DayConfig dayCfg = g_MainConfig.GlobalPvEZoneDays.Get(i);
            if (dayCfg && dayCfg.dayName == dayName)
            {
                //Print(string.Format("[NinjinsPvPPvE] Found day config: %1, Start: %2, End: %3", 
                //    dayCfg.dayName, dayCfg.startHour.ToString(), dayCfg.endHour.ToString()));
                if (m_StartHourEditGlobalPvE) 
                {
                    m_StartHourEditGlobalPvE.SetText(dayCfg.startHour.ToString());
                }
                m_EndHourEditGlobalPvE.SetText(dayCfg.endHour.ToString());
                m_SelectedDayTextGlobalPvE.SetText(dayCfg.dayName);
                found = true;
                break;
            }
        }
        if (!found)
        {
            //Print("[NinjinsPvPPvE] Could not find config for day: " + dayName);
            if (m_StartHourEditGlobalPvE) 
            {
                m_StartHourEditGlobalPvE.SetText("");
            }
            m_EndHourEditGlobalPvE.SetText("");
            m_SelectedDayTextGlobalPvE.SetText(dayName);
        }
    }
    void AddDayToDayList()
    {
        if (!m_DayNameToAdd || !m_DayList) 
            return;
        string dayName = m_DayNameToAdd.GetText();
        dayName.Trim();
        if (dayName == "") 
            return;
        for (int i = 0; i < m_DayList.GetNumItems(); i++) 
        {
            string existingDay;
            m_DayList.GetItemText(i, 0, existingDay);
            if (existingDay == dayName) 
            {
                return;
            }
        }
        int row = m_DayList.AddItem(dayName, NULL, 0);
        DayConfig newConfig = new DayConfig(dayName, 0, 24);
        m_DayConfigs.Set(dayName, newConfig);
        m_DayList.SelectRow(row);
        m_CurrentSelectedDay = dayName;
        m_SelectedDayText.SetText(dayName);
        m_StartHourEdit.SetText("0");
        m_EndHourEdit.SetText("24");
        m_DayNameToAdd.SetText("");
    }
    void AddDayToDayListGlobalPvP()
    {
        if (!m_DayNameToAddGlobalPvP || !m_DayListGlobalPvP) 
            return;
        string dayName = m_DayNameToAddGlobalPvP.GetText();
        dayName.Trim();
        if (dayName == "") 
            return;
        for (int i = 0; i < m_DayListGlobalPvP.GetNumItems(); i++) 
        {
            string existingDay;
            m_DayListGlobalPvP.GetItemText(i, 0, existingDay);
            if (existingDay == dayName) 
            {
                return;
            }
        }
        int row = m_DayListGlobalPvP.AddItem(dayName, NULL, 0);
        DayConfig newConfig = new DayConfig(dayName, 0, 24);
        g_MainConfig.GlobalPvPZoneDays.Insert(newConfig);
        m_DayListGlobalPvP.SelectRow(row);
        m_SelectedDayTextGlobalPvP.SetText(dayName);
        m_StartHourEditGlobalPvP.SetText("0");
        m_EndHourEditGlobalPvP.SetText("24");
        m_DayNameToAddGlobalPvP.SetText("");
    }
    void AddDayToDayListGlobalPvE()
    {
        if (!m_DayNameToAddGlobalPvE || !m_DayListGlobalPvE) 
            return;
        string dayName = m_DayNameToAddGlobalPvE.GetText();
        dayName.Trim();
        if (dayName == "") 
            return;
        for (int i = 0; i < m_DayListGlobalPvE.GetNumItems(); i++) 
        {
            string existingDay;
            m_DayListGlobalPvE.GetItemText(i, 0, existingDay);
            if (existingDay == dayName) 
            {
                return;
            }
        }
        int row = m_DayListGlobalPvE.AddItem(dayName, NULL, 0);
        DayConfig newConfig = new DayConfig(dayName, 0, 24);
        g_MainConfig.GlobalPvEZoneDays.Insert(newConfig);
        m_DayListGlobalPvE.SelectRow(row);
        m_SelectedDayTextGlobalPvE.SetText(dayName);
        m_StartHourEditGlobalPvE.SetText("0");
        m_EndHourEditGlobalPvE.SetText("24");
        m_DayNameToAddGlobalPvE.SetText("");
    }
    void RemoveDayFromDayList()
    {
        if (!m_DayList) 
            return;
        int selectedRow = m_DayList.GetSelectedRow();
        if (selectedRow < 0) 
            return;
        string dayName;
        m_DayList.GetItemText(selectedRow, 0, dayName);
        if (m_DayConfigs.Contains(dayName)) 
        {
            m_DayConfigs.Remove(dayName);
        }
        m_DayList.RemoveRow(selectedRow);
        if (m_DayList.GetNumItems() == 0) 
        {
            m_CurrentSelectedDay = "";
            m_SelectedDayText.SetText("");
            m_StartHourEdit.SetText("");
            m_EndHourEdit.SetText("");
        } 
        else 
        {
            int newSelectedRow = Math.Clamp(selectedRow - 1, 0, m_DayList.GetNumItems() - 1);
            m_DayList.SelectRow(newSelectedRow);
            string newDayName;
            m_DayList.GetItemText(newSelectedRow, 0, newDayName);
            if (m_DayConfigs.Contains(newDayName)) 
            {
                DayConfig config = m_DayConfigs.Get(newDayName);
                m_StartHourEdit.SetText(config.startHour.ToString());
                m_EndHourEdit.SetText(config.endHour.ToString());
                m_SelectedDayText.SetText(newDayName);
                m_CurrentSelectedDay = newDayName;
            }
        }
    }
    void RemoveDayFromDayListGlobalPvP()
    {
        if (!m_DayListGlobalPvP || !m_SelectedDayTextGlobalPvP || !m_StartHourEditGlobalPvP || !m_EndHourEditGlobalPvP) 
        {
            return;
        }
        int itemCount = m_DayListGlobalPvP.GetNumItems();
        if (itemCount <= 0) 
        {
            return;
        }
        int selectedRow = m_DayListGlobalPvP.GetSelectedRow();
        if (selectedRow < 0 || selectedRow >= itemCount) 
        {
            return;
        }
        string dayName;
        m_DayListGlobalPvP.GetItemText(selectedRow, 0, dayName);
        if (dayName == "") 
        {
            return;
        }
        for (int i = 0; i < g_MainConfig.GlobalPvPZoneDays.Count(); i++) 
        {
            if (i >= g_MainConfig.GlobalPvPZoneDays.Count()) break; 
            DayConfig config = g_MainConfig.GlobalPvPZoneDays.Get(i);
            if (config && config.dayName == dayName) 
            {
                g_MainConfig.GlobalPvPZoneDays.Remove(i);
                break;
            }
        }
        m_DayListGlobalPvP.RemoveRow(selectedRow);
        itemCount = m_DayListGlobalPvP.GetNumItems();
        if (itemCount == 0) 
        {
            m_SelectedDayTextGlobalPvP.SetText("");
            m_StartHourEditGlobalPvP.SetText("");
            m_EndHourEditGlobalPvP.SetText("");
        } 
        else 
        {
            int newSelectedRow = Math.Clamp(selectedRow - 1, 0, itemCount - 1);
            m_DayListGlobalPvP.SelectRow(newSelectedRow);
            OnGlobalPvPDaySelected();
        }
    }
    void RemoveDayFromDayListGlobalPvE()
    {
        if (!m_DayListGlobalPvE || !m_SelectedDayTextGlobalPvE || !m_StartHourEditGlobalPvE || !m_EndHourEditGlobalPvE) 
        {
            return;
        }
        int itemCount = m_DayListGlobalPvE.GetNumItems();
        if (itemCount <= 0) 
        {
            return;
        }
        int selectedRow = m_DayListGlobalPvE.GetSelectedRow();
        if (selectedRow < 0 || selectedRow >= itemCount) 
        {
            return;
        }
        string dayName;
        m_DayListGlobalPvE.GetItemText(selectedRow, 0, dayName);
        if (dayName == "") 
        {
            return;
        }
        for (int i = 0; i < g_MainConfig.GlobalPvEZoneDays.Count(); i++) 
        {
            if (i >= g_MainConfig.GlobalPvEZoneDays.Count()) break; 
            DayConfig config = g_MainConfig.GlobalPvEZoneDays.Get(i);
            if (config && config.dayName == dayName) 
            {
                g_MainConfig.GlobalPvEZoneDays.Remove(i);
                break;
            }
        }
        m_DayListGlobalPvE.RemoveRow(selectedRow);
        itemCount = m_DayListGlobalPvE.GetNumItems();
        if (itemCount == 0) 
        {
            m_SelectedDayTextGlobalPvE.SetText("");
            m_StartHourEditGlobalPvE.SetText("");
            m_EndHourEditGlobalPvE.SetText("");
        } 
        else 
        {
            int newSelectedRow = Math.Clamp(selectedRow - 1, 0, itemCount - 1);
            m_DayListGlobalPvE.SelectRow(newSelectedRow);
            OnGlobalPvEDaySelected();
        }
    }  
    override bool OnClick(Widget w, int x, int y, int button)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
        ref array<ref ZoneBase> missionZones;
        ref array<Widget> panelsToShow = new array<Widget>();
        Param2<string,string> param2;
        Param1<string> reloadParam;
        Param1<ref MainConfig> configParam;
        Param1<string> param1Guid;
        string additionalClassname = ClassNameToAdd.GetText();
        string zoneName;
        string value;
        string name;
        string guid;
        int selectedRow = -1;
        int row         = -1;
        int count       = -1;
        string entry;
        TextListboxWidget list;
        vector pos = player.GetPosition();
        if (mission)
        {
            missionZones = mission.GetCachedZones();
        }
        if (w == m_AddToRaidingPlayersBtn)
        {
            row = m_OnlinePlayersList.GetSelectedRow();
            if (row >= 0)
            {
                m_OnlinePlayersList.GetItemText(row, 0, entry);
                param1Guid = new Param1<string>(entry);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "AddRaidingPlayerServer", param1Guid, true);
            }
            return true;
        }
        if (w == m_RemoveRaidingPlayerBtn)
        {
            row = m_AllowedPlayersRaidingList.GetSelectedRow();
            if (row >= 0)
            {
                m_AllowedPlayersRaidingList.GetItemText(row, 0, entry);
                param1Guid = new Param1<string>(entry);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "RemoveRaidingPlayerServer", param1Guid, true);
            }
            return true;
        }
        else if (w == RefreshPlayerListBTN)
        {
            RefreshOnlinePlayers();
            return true;
        }
        if (w && w.IsInherited(CheckBoxWidget))
        {
            UpdateCheckBoxColor(CheckBoxWidget.Cast(w));
        }
        if (w == m_ItemList)
        {
            int selectedRowClassList = m_ItemList.GetSelectedRow();
            if (selectedRowClassList >= 0)
            {
                string selectedItem;
                m_ItemList.GetItemText(selectedRowClassList, 0, selectedItem);
                if (m_ItemList.GetNumItems() > 0)
                {
                    m_ItemList.SelectRow(selectedRowClassList);
                    UpdateItemPreview(selectedItem);
                }
                else
                {
                    m_ItemList.SelectRow(-1);
                    UpdateItemPreview("");
                }
            }
            return true;
        }
        else if (w == m_ResetSearchBoxBtn)
        {
            if (m_SearchBox)
                m_SearchBox.SetText("");
            return true;
        }
        else if (m_FilterButtonMap && m_FilterButtonMap.Contains(w))
        {
            string baseClass = m_FilterButtonMap.Get(w);
            if (baseClass == "#EXPANSIONAI")
            {
                m_FilterByPrefixOnly = true;
                m_PrefixFilter = "eAI_";
                m_CurrentFilterBaseClass = "";
            }
            else
            {
                m_FilterByPrefixOnly = false;
                m_PrefixFilter = "";
                m_CurrentFilterBaseClass = baseClass;
            }
            ReloadItemList(m_SearchBox.GetText());
            HighlightActiveFilterButton(w);
            return true;
        }
        else if (w == IconBtn)
        {
            panelsToShow.Insert(IconPanel);
            GetGame().GetMission().GetHud().Show(true);
            if (SideBarWidget)
                SideBarWidget.Show(false);
            ShowOnlyPanels(panelsToShow);
            if (btnGeneralApply)
                btnGeneralApply.Show(false);
            if (btnGeneralApplyIcon)
                btnGeneralApplyIcon.Show(true);
            if (SaveZoneBtn)
                SaveZoneBtn.Show(false);
            return true;
        }
        else if (w == m_DayList)
        {
            OnDaySelected();
            return true;
        }
        else if (w == m_DayListGlobalPvP)
        {
            OnGlobalPvPDaySelected();
            return true;
        }
        else if (w == m_DayListGlobalPvE)
        {
            OnGlobalPvEDaySelected();
            return true;
        }
        else if (w == m_AddDayButton)
        {
            AddDayToDayList();
            return true;
        }
        else if (w == m_AddDayToDayListGlobalPvP)
        {
            AddDayToDayListGlobalPvP();
            return true;
        }
        else if (w == m_AddDayToDayListGlobalPvE)
        {
            AddDayToDayListGlobalPvE();
            return true;
        }
        else if (w == m_RemoveDayButton)
        {
            RemoveDayFromDayList();
            return true;
        }
        else if (w == m_RemoveDayFromDayListGlobalPvP)
        {
            RemoveDayFromDayListGlobalPvP();
            return true;
        }
        else if (w == m_RemoveDayFromDayListGlobalPvE)
        {
            RemoveDayFromDayListGlobalPvE();
            return true;
        }
        else if (w == zoneList)
        {
            int zoneRow = zoneList.GetSelectedRow();
            if (zoneRow >= 0)
            {
                zoneList.GetItemText(zoneRow, 0, zoneName);
                ZoneBase zoneToView = FindZoneByName(zoneName);
                if (zoneToView)
                {
                    PopulateZoneFields(zoneToView);
                    if (m_AdminMap)
                    {
                        m_AdminMap.JumpToPosition(zoneToView.center);
                    }
                    if (zonePropertiesPanel)
                        zonePropertiesPanel.Show(true);
                        RefreshAllCheckBoxes(zonePropertiesPanel);
                }
                else
                {
                    if (zonePropertiesPanel)
                        zonePropertiesPanel.Show(false);
                }
            }
            else
            {
                if (zonePropertiesPanel)
                    zonePropertiesPanel.Show(false);
            }
            return true;
        }
        else if (w == MainEdit)
        {
            panelsToShow.Clear();
            panelsToShow.Insert(SideBarWidget);
            panelsToShow.Insert(TitlePanel);
            panelsToShow.Insert(GeneralRootPanel);
            ShowOnlyPanels(panelsToShow);
            if (btnGeneralApply)
                btnGeneralApply.Show(true);
            if (SaveZoneBtn)
                SaveZoneBtn.Show(false);
            return true;
        }
        else if (w == BtnAddNBItemWhiteList)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("NBItemWhiteListList"));
            row = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddNBItemWhiteList", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            return true;
        }
        else if (w == RemoveNBItemWhiteList)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("NBItemWhiteListList"));
            row = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveNBItemWhiteList", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == m_BtnAddPaintballAmmo)
        {
            list = m_AllowedAmmoInPaintBallStateList;
            row = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddAllowedAmmoPaintballState", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            return true;
        }
        else if (w == m_BtnRemovePaintballAmmo)
        {
            list = m_AllowedAmmoInPaintBallStateList;
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveAllowedAmmoPaintballState", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == m_BtnAddSZItemWhiteList)
        {
            list = m_SZItemWhiteListList;
            row = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddSZItemWhiteList", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            return true;
        }
        else if (w == m_BtnRemoveSZItemWhiteList)
        {
            list = m_SZItemWhiteListList;
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveSZItemWhiteList", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == m_BtnAddPvEItem)
        {
            list = m_CantBeDamagedInPvEList;
            row = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddCantBeDamagedInPvE", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            return true;
        }
        else if (w == m_BtnRemovePvEItem)
        {
            list = m_CantBeDamagedInPvEList;
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveCantBeDamagedInPvE", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == m_BtnAddPvPItem)
        {
            list = m_CantBeDamagedInPvPList;
            row = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddCantBeDamagedInPvP", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            return true;
        }
        else if (w == m_BtnRemovePvPItem)
        {
            list = m_CantBeDamagedInPvPList;
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveCantBeDamagedInPvP", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == AddAllowedAmmoInPvEState)
        {
            list = AllowedAmmoInPvEStatelList;
            row = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddAllowedAmmoPvEState", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            return true;
        }
        else if (w == AllowedAmmoInPvEStateRemove)
        {
            list = AllowedAmmoInPvEStatelList;
            row = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveAllowedAmmoPvEState", value);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                list.RemoveRow(row);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == DeployRaidAdd)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("BlockDeployIfPlayerInRaidStateList"));
            row  = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddItemRaidDeploy", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            return true;
        }
        else if (w == DeployPvPAdd)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("BlockDeployIfPlayerInPvPStateList"));
            row  = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddItemPvPDeploy", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            return true;
        }
        else if (w == DeployPvEAdd)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("BlockDeployIfPlayerInPvEStateList"));
            row  = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddItemPvEDeploy", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            return true;
        }
        else if (w == BtnAddtoAnimals)
        {
            #ifdef NinjinsPvPPvE_Animal
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("CantBeDamagedAnimalsinPvEList"));
            row  = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddAnimalPvE", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            return true;
            #endif
        }
        else if (w == BtnAddCantBeDamagedOnGround)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("CantBeDamagedOnGroundList"));
            row  = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddCantBeDamagedOnGround", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            return true;
        }
        else if (w == BtnAddGrenades)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ChecksGrenadesList"));
            row  = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddGrenade", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            return true;
        }
        else if (w == BtnAddVehicle)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("DisallowedVehiclesPanelRulesList"));
            row  = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddVehicle", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            return true;
        }
        else if (w == BtnAddExplosives)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("PvEBlockedExplosivesDamageList"));
            row  = m_ItemList.GetSelectedRow();
            if (row >= 0)
                m_ItemList.GetItemText(row, 0, value);
            else
            {
                additionalClassname = additionalClassname.Trim();
                if (additionalClassname == "") 
                    return true;
                value = additionalClassname;
            }
            param2 = new Param2<string, string>("AddExplosive", value);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
            list.AddItem(value, NULL, 0);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            return true;
        }
        else if (w == DeployRaidRemove)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("BlockDeployIfPlayerInRaidStateList"));
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveItemRaidDeploy", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == DeployPvPRemove)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("BlockDeployIfPlayerInPvPStateList"));
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveItemPvPDeploy", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == DeployPvERemove)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("BlockDeployIfPlayerInPvEStateList"));
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveItemPvEDeploy", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == RemoveItemExplosive)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("PvEBlockedExplosivesDamageList"));
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveExplosive", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == VehicleRemove)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("DisallowedVehiclesPanelRulesList"));
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveVehicle", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == RemoveCantBeDamagedOnGround)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("CantBeDamagedOnGroundList"));
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveCantBeDamagedOnGround", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == RemoveChecksGrenades)
        {
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ChecksGrenadesList"));
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveGrenade", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
        }
        else if (w == BTNRemoveAnimal)
        {
            #ifdef NinjinsPvPPvE_Animal
            list = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("CantBeDamagedAnimalsinPvEList"));
            row  = list.GetSelectedRow();
            if (row >= 0)
            {
                list.GetItemText(row, 0, value);
                param2 = new Param2<string, string>("RemoveAnimalPvE", value);
                list.RemoveRow(row);
                count = list.GetNumItems();
                if (count > 0)
                    list.SelectRow(0);
                else
                    list.SelectRow(-1);
            }
            if (param2)
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ItemRuleActionRPC", param2, true);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadItemRulesMenu", NULL, true);
            }
            return true;
            #endif
        }
        else if (w == ItemRulesEdit)
        {
            panelsToShow.Clear();
            panelsToShow.Insert(SideBarWidget);
            panelsToShow.Insert(ItemRulesPanel);
            panelsToShow.Insert(ItemSearch);
            panelsToShow.Insert(PvEBlockedExplosivesDamagePanel);
            panelsToShow.Insert(DisallowedVehiclesPanelRules);
            panelsToShow.Insert(CantBeDamagedOnGround);
            panelsToShow.Insert(BypassZoneChecksGrenades);
            #ifdef NinjinsPvPPvE_Animal
            panelsToShow.Insert(CantBeDamagedAnimalsinPvE);
            #endif
            panelsToShow.Insert(BlockDeployIfPlayerInPvEStatePanel);
            panelsToShow.Insert(BlockDeployIfPlayerInPvPStatePanel);
            panelsToShow.Insert(BlockDeployIfPlayerInRaidStatePanel);
            if (btnGeneralApply)
                btnGeneralApply.Show(false);
            if (SaveZoneBtn)
                SaveZoneBtn.Show(false);
            ShowOnlyPanels(panelsToShow);
            if (g_ItemRules)
            {
                TextListboxWidget AllowedAmmoInPaintBallStateList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("AllowedAmmoInPaintBallStateList"));
                if (AllowedAmmoInPaintBallStateList1)
                {
                    AllowedAmmoInPaintBallStateList1.ClearItems();
                    foreach (string paintballAmmo : g_ItemRules.AllowedAmmoInPaintBallState)
                    {
                        AllowedAmmoInPaintBallStateList1.AddItem(paintballAmmo, NULL, 0);
                    }
                }
                TextListboxWidget SZItemWhiteListList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ListSZItemWhiteList"));
                if (SZItemWhiteListList1)
                {
                    SZItemWhiteListList1.ClearItems();
                    foreach (string szitem : g_ItemRules.SZItemWhiteList)
                    {
                        SZItemWhiteListList1.AddItem(szitem, NULL, 0);
                    }
                }
                TextListboxWidget nbItemWhiteList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("NBItemWhiteListList"));
                if (nbItemWhiteList1)
                {
                    nbItemWhiteList1.ClearItems();
                    foreach (string nbitem : g_ItemRules.NBItemWhiteList)
                    {
                        nbItemWhiteList1.AddItem(nbitem, NULL, 0);
                    }
                }
                TextListboxWidget pveExplosivesList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("PvEBlockedExplosivesDamageList"));
                if (pveExplosivesList1)
                {
                    pveExplosivesList1.ClearItems();
                    foreach (string explosive : g_ItemRules.PvEBlockedExplosivesDamage)
                    {
                        pveExplosivesList1.AddItem(explosive, NULL, 0);
                    }
                }
                TextListboxWidget disallowedVehiclesList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("DisallowedVehiclesPanelRulesList"));
                if (disallowedVehiclesList1)
                {
                    disallowedVehiclesList1.ClearItems();
                    foreach (string vehicle : g_ItemRules.DisallowedVehicles)
                    {
                        disallowedVehiclesList1.AddItem(vehicle, NULL, 0);
                    }
                }
                TextListboxWidget cantBeDamagedOnGroundList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("CantBeDamagedOnGroundList"));
                if (cantBeDamagedOnGroundList1)
                {
                    cantBeDamagedOnGroundList1.ClearItems();
                    foreach (string item : g_ItemRules.CantBeDamagedOnGround)
                    {
                        cantBeDamagedOnGroundList1.AddItem(item, NULL, 0);
                    }
                }
                TextListboxWidget ChecksGrenadesList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ChecksGrenadesList"));
                if (ChecksGrenadesList1)
                {
                    ChecksGrenadesList1.ClearItems();
                    foreach (string itemgrenade : g_ItemRules.BypassZoneChecksGrenades)
                    {
                        ChecksGrenadesList1.AddItem(itemgrenade, NULL, 0);
                    }
                }
                TextListboxWidget CantBeDamagedAnimalsinPvEList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("CantBeDamagedAnimalsinPvEList"));
                if (CantBeDamagedAnimalsinPvEList1)
                {
                    #ifdef NinjinsPvPPvE_Animal
                    CantBeDamagedAnimalsinPvEList1.ClearItems();
                    foreach (string AnimalPVE : g_ItemRules.CantBeDamagedAnimalsinPvE)
                    {
                        CantBeDamagedAnimalsinPvEList1.AddItem(AnimalPVE, NULL, 0);
                    }
                    #endif
                }
                TextListboxWidget BlockDeployIfPlayerInPvEStateList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("BlockDeployIfPlayerInPvEStateList"));
                if (BlockDeployIfPlayerInPvEStateList1)
                {
                    BlockDeployIfPlayerInPvEStateList1.ClearItems();
                    foreach (string DeployPVE : g_ItemRules.BlockDeployIfPlayerInPvEState)
                    {
                        BlockDeployIfPlayerInPvEStateList1.AddItem(DeployPVE, NULL, 0);
                    }
                }
                TextListboxWidget BlockDeployIfPlayerInPvPStateList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("BlockDeployIfPlayerInPvPStateList"));
                if (BlockDeployIfPlayerInPvPStateList1)
                {
                    BlockDeployIfPlayerInPvPStateList1.ClearItems();
                    foreach (string DeployPVP : g_ItemRules.BlockDeployIfPlayerInPvPState)
                    {
                        BlockDeployIfPlayerInPvPStateList1.AddItem(DeployPVP, NULL, 0);
                    }
                }
                TextListboxWidget BlockDeployIfPlayerInRaidStateList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("BlockDeployIfPlayerInRaidStateList"));
                if (BlockDeployIfPlayerInRaidStateList1)
                {
                    BlockDeployIfPlayerInRaidStateList1.ClearItems();
                    foreach (string DeployRaid : g_ItemRules.BlockDeployIfPlayerInRaidState)
                    {
                        BlockDeployIfPlayerInRaidStateList1.AddItem(DeployRaid, NULL, 0);
                    }
                }
                TextListboxWidget AllowedAmmoInPvEStatelList1 = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("AllowedAmmoInPvEStatelList"));
                if (AllowedAmmoInPvEStatelList1)
                {
                    AllowedAmmoInPvEStatelList1.ClearItems();
                    foreach (string AllowedAmmo : g_ItemRules.AllowedAmmoInPvEState)
                    {
                        AllowedAmmoInPvEStatelList1.AddItem(AllowedAmmo, NULL, 0);
                    }
                }
            }
            TextListboxWidget CantBeDamagedInPvEList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ListCantBeDamagedInPvE"));
            if (CantBeDamagedInPvEList)
            {
                CantBeDamagedInPvEList.ClearItems();
                foreach (string itempve : g_ItemRules.CantBeDamagedInPvE)
                {
                    CantBeDamagedInPvEList.AddItem(itempve, NULL, 0);
                }
            }
            TextListboxWidget CantBeDamagedInPvPList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ListCantBeDamagedInPvP"));
            if (CantBeDamagedInPvPList)
            {
                CantBeDamagedInPvPList.ClearItems();
                foreach (string itempvp : g_ItemRules.CantBeDamagedInPvP)
                {
                    CantBeDamagedInPvPList.AddItem(itempvp, NULL, 0);
                }
            }
            return true;
        }
        else if (w == ZoneEditBtn)
        {
            if (m_AdminMap)
            {
                m_AdminMap.UpdateZones();
            }
            PopulateZoneList();
            panelsToShow.Clear();
            panelsToShow.Insert(SideBarWidget);
            panelsToShow.Insert(ZoneEditContainer);
            panelsToShow.Insert(Info1);
            panelsToShow.Insert(Info2);
            panelsToShow.Insert(m_ActualMapContainer);
            panelsToShow.Insert(g_MapWidget);
            SaveZoneBtn.Show(true);
            ShowOnlyPanels(panelsToShow);
            if (btnGeneralApply)
                btnGeneralApply.Show(false);
            RefreshAllCheckBoxes(ZoneEditContainer);
            return true;
        }
        else if (w == CloseZoneEditBtn)
        {
            panelsToShow.Clear();
            panelsToShow.Insert(SideBarWidget);
            panelsToShow.Insert(TitlePanel);
            panelsToShow.Insert(GeneralRootPanel);
            ShowOnlyPanels(panelsToShow);
            if (btnGeneralApply)
                btnGeneralApply.Show(false);
            if (SaveZoneBtn)
                SaveZoneBtn.Show(false);
            return true;
        }
        else if (w == ButtonWidget.Cast(layoutRoot.FindAnyWidget("AddZone")))
        {
            if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "AddZone", null, true, player.GetIdentity());
                if (m_AdminMap)
                    GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_AdminMap.UpdateZones, 300, false);
                GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(RefreshZoneListUI, 700, false);
                GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(SelectNewestZone, 900, false);
            }
            if (zonePropertiesPanel)
                zonePropertiesPanel.Show(false);
            return true;
        }
        else if (w == ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveZone")))
        {
            selectedRow = zoneList.GetSelectedRow();
            if (selectedRow >= 0)
            {
                zoneList.GetItemText(selectedRow, 0, zoneName);
                Param1<string> removeParam = new Param1<string>(zoneName);
                if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
                {
                    GetRPCManager().SendRPC("NinjinsPvPPvE", "RemoveZone", removeParam, true, player.GetIdentity());
                }
            }
            if (m_AdminMap)
                GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_AdminMap.UpdateZones, 300, false);
            GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(RefreshZoneListUI, 900, false);
            if (zonePropertiesPanel)
                zonePropertiesPanel.Show(false);
            return true;
        }
        else if (w == PlayerPosButton)
        {
            if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
            {
                ZoneCenterXValue.SetText(pos[0].ToString());
                ZoneCenterYValue.SetText(pos[1].ToString());
                ZoneCenterZValue.SetText(pos[2].ToString());
            }
            return true;
        }
        else if (w == NoLogOutPosBTN)
        {
            if (!player) 
                return true;
            NoLogOutTeleportPosXValue.SetText(pos[0].ToString());
            NoLogOutTeleportPosYValue.SetText(pos[1].ToString());
            NoLogOutTeleportPosZValue.SetText(pos[2].ToString());
            return true;
        }
        else if (w == ButtonWidget.Cast(layoutRoot.FindAnyWidget("SaveZone")))
        {
            selectedRow = zoneList.GetSelectedRow();
            if (selectedRow >= 0)
            {
                zoneList.GetItemText(selectedRow, 0, zoneName);
                ZoneBase zoneToSave = FindZoneByName(zoneName);
                if (!zoneToSave)
                    return true;
                ZoneUpdateData updateData                       = new ZoneUpdateData();
                updateData.originalName                         = zoneToSave.name;
                updateData.updatedZone                          = new ZoneBase();
                updateData.updatedZone.name                     = ZoneNameValue.GetText();
                string newZoneName                              = updateData.updatedZone.name;
                updateData.updatedZone.HideWhenNested = HideWhenNestedTitleValue0.IsChecked();
                updateData.updatedZone.DrawNoBuildShape = ZoneDrawNoBuildShapeValue.IsChecked();
                updateData.updatedZone.type                     = Math.Clamp(ZoneTypeValue.GetCurrentItem() + 1, 1, ZoneTypeValue.GetNumItems());
                updateData.updatedZone.OnlyAllowExpansion2DMarker = EnableExpansion2DMarkerValue.IsChecked();
                updateData.updatedZone.EnableExpansion3DMarker  = EnableExpansion3DMarkerValue.IsChecked();
                updateData.updatedZone.ExpansionMarkerName      = ExpansionMarkerNameValue.GetText();
                updateData.updatedZone.ignoreHeightCheck = ZoneIgnoreHeightCheckValue.IsChecked();
                updateData.updatedZone.zoneMinHeight = ZoneMinHeightValue.GetText().ToFloat();
                updateData.updatedZone.zoneMaxHeight = ZoneMaxHeightValue.GetText().ToFloat();
                updateData.updatedZone.Expansion3DIcon          = Expansion3DIconValue.GetText();
                updateData.updatedZone.drawStrikeZone           = drawStrikeZoneValue.IsChecked();
                updateData.updatedZone.displayName              = displayNameValue.GetText();
                updateData.updatedZone.priority                 = ZonePriorityValue.GetText().ToInt();
                updateData.updatedZone.enableCustomMessages     = ZoneEnableCustomMessagesValue.IsChecked();
                updateData.updatedZone.customTitle              = ZoneCustomTitleValue.GetText();
                updateData.updatedZone.customMessageEnter       = ZoneCustomMessageEnterValue.GetText();
                updateData.updatedZone.customMessageExit        = ZoneCustomMessageExitValue.GetText();
                updateData.updatedZone.customIcon               = ZoneCustomIconValue.GetText();
                updateData.updatedZone.notificationColor        = ZoneNotificationColorValue.GetText().ToInt();
                updateData.updatedZone.dayConfigs = new array<ref DayConfig>();
                if (m_DayList && m_StartHourEdit && m_EndHourEdit) 
                {
                    if (m_CurrentSelectedDay != "" && m_DayConfigs.Contains(m_CurrentSelectedDay)) 
                    {
                        DayConfig currentConfig = m_DayConfigs.Get(m_CurrentSelectedDay);
                        currentConfig.startHour = m_StartHourEdit.GetText().ToInt();
                        currentConfig.endHour = m_EndHourEdit.GetText().ToInt();
                    }
                    updateData.updatedZone.dayConfigs = new array<ref DayConfig>();
                    for (int i = 0; i < m_DayList.GetNumItems(); i++) 
                    {
                        string dayName;
                        m_DayList.GetItemText(i, 0, dayName);
                        if (dayName != "" && m_DayConfigs.Contains(dayName)) 
                        {
                            DayConfig config = m_DayConfigs.Get(dayName);
                            updateData.updatedZone.dayConfigs.Insert(new DayConfig(dayName, config.startHour, config.endHour));
                        }
                    }
                }
                updateData.updatedZone.forceFirstPerson         = ZoneForceFirstPersonValue.IsChecked();
                updateData.updatedZone.UsesDisallowedVehicles   = ZoneNoVehicleValue.IsChecked();
                updateData.updatedZone.drawShape                = ZoneDrawShapeValue.IsChecked();
                updateData.updatedZone.radius                   = ZoneRadiusValue.GetText().ToFloat();
                updateData.updatedZone.zoneAlpha                = ZoneAlphaValue.GetText().ToInt();
                updateData.updatedZone.zoneRed                  = ZoneRedValue.GetText().ToInt();
                updateData.updatedZone.zoneGreen                = ZoneGreenValue.GetText().ToInt();
                updateData.updatedZone.zoneBlue                 = ZoneBlueValue.GetText().ToInt();
                updateData.updatedZone.ZonelabelOffsetX_Meters = ZoneLabelOffsetXValue.GetText().ToFloat();
                updateData.updatedZone.ZonelabelOffsetZ_Meters = ZoneLabelOffsetZValue.GetText().ToFloat();
                updateData.updatedZone.ZoneLabelColor = ZoneLabelColorValue.GetText().ToInt();
                updateData.updatedZone.noBuildRadius = ZoneNoBuildRadiusValue.GetText().ToFloat();
                updateData.updatedZone.Hide = HideWhenNestedTitleValue.IsChecked();
                int selectedShape = ShapeTypeValue.GetCurrentItem();
                if (selectedShape == 0)
                    updateData.updatedZone.shape = ZoneShape.CIRCLE;
                else
                    updateData.updatedZone.shape = ZoneShape.POLYGON;
                float centerX = ZoneCenterXValue.GetText().ToFloat();
                float centerY = ZoneCenterYValue.GetText().ToFloat();
                float centerZ = ZoneCenterZValue.GetText().ToFloat();
                updateData.updatedZone.center = Vector(centerX, centerY, centerZ);
                float noLogoutX = NoLogOutTeleportPosXValue.GetText().ToFloat();
                float noLogoutY = NoLogOutTeleportPosYValue.GetText().ToFloat();
                float noLogoutZ = NoLogOutTeleportPosZValue.GetText().ToFloat();
                updateData.updatedZone.NoLogOutTeleportPos = Vector(noLogoutX, noLogoutY, noLogoutZ);
                updateData.updatedZone.NoLogOut = NoLogOutValue.IsChecked();
                if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
                {
                    GetRPCManager().SendRPC("NinjinsPvPPvE", "SaveZone", new Param1<ref ZoneUpdateData>(updateData), true, player.GetIdentity());
                    if (m_AdminMap)
                    {
                        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_AdminMap.UpdateZones, 100, false);
                    }
                } 
                GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(RefreshZoneListUI, 500, false);
                GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(SelectZoneByName, 750, false, newZoneName);
                if (zonePropertiesPanel)
                    zonePropertiesPanel.Show(false);
            }
            return true;
        }
        else if (w == wReloadMainConfig)
        {
            if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
            {
                reloadParam = new Param1<string>("MainConfig");
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadConfig", reloadParam, true, player.GetIdentity());
            }
            GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(RefreshMainConfigUI, 500, false);
            return true;
        }
        else if (w == wReloadZones)
        {
            if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
            {
                reloadParam = new Param1<string>("Zones");
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadConfig", reloadParam, true, player.GetIdentity());
            }
            GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(RefreshZoneListUI, 500, false);
            PopulateZoneList();
            return true;
        }
        else if (w == wReloadItemRules)
        {
            if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
            {
                reloadParam = new Param1<string>("ItemRules");
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadConfig", reloadParam, true, player.GetIdentity());
            }
            return true;
        }
        else if (w == wReloadAdmins)
        {
            if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
            {
                reloadParam = new Param1<string>("AdminConfig");
                GetRPCManager().SendRPC("NinjinsPvPPvE", "ReloadConfig", reloadParam, true, player.GetIdentity());
            }
            return true;
        }
        else if (w == btnGeneral)
        {
            ShowOnlyPanel(GeneralRootPanel);
            return true;
        }
        else if (w == btnMap)
        {
            ShowOnlyPanel(MapRootPanel);
            return true;
        }
        else if (w == btnVehicle)
        {
            ShowOnlyPanel(VehicleRootPanel);
            return true;
        }
        else if (w == btnLockpick)
        {
            ShowOnlyPanel(LockpickRootPanel);
            return true;
        }
        else if (w == btnTerritory)
        {
            ShowOnlyPanel(TerritoryRootPanel);
            return true;
        }
        else if (w == btnAI)
        {
            ShowOnlyPanel(AIRootPanel);
            return true;
        }
        else if (w == btnOther)
        {
            ShowOnlyPanel(OtherRootPanel);
            return true;
        }
        else if (w == btnRaid)
        {
            ShowOnlyPanel(RaidPanelRoot);
            RefreshOnlinePlayers();
            PopulateAllowedRaidingPlayers();
            return true;
        }
        else if (w == btnGeneralApplyIcon)
        {
            if (!g_MainConfig) 
                return false;
            float iconX = IconsliderX.GetCurrent();
            float iconY = IconsliderY.GetCurrent();
            g_MainConfig.IconPositionX = iconX;
            g_MainConfig.IconPositionY = iconY;
            if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
            {
                configParam = new Param1<ref MainConfig>(g_MainConfig);
                GetRPCManager().SendRPC("NinjinsPvPPvE", "UpdateServerConfigAll", configParam, true, player.GetIdentity());
            }
            else
            {
                g_MainConfig.SaveConfig();
            }
            return true;
        }
        else if (w == btnGeneralApply)
        {
            if (!g_MainConfig) 
                return false;
            g_MainConfig.AdminCanSeeAllInactiveZones = AdminCanSeeAllInactiveZonesCheck.IsChecked();
            g_MainConfig.drawStrikeLinesForNB = DrawStrikeLinesForNBValue.IsChecked();
            g_MainConfig.noBuildZoneColor = NoBuildZoneColorValue.GetText().ToInt();
            array<string> preservedRaiders = new array<string>;
            preservedRaiders.Copy(g_MainConfig.AllowedRaidingPlayers);
            g_MainConfig.PvPIconColor      = PvPIconColorValue.GetText().ToInt();
            g_MainConfig.PvEIconColor      = PvEIconColorValue.GetText().ToInt();
            g_MainConfig.RaidIconColor     = RaidIconColorValue.GetText().ToInt();
            g_MainConfig.SafeZoneIconColor = SafeZoneIconColorValue.GetText().ToInt();
            g_MainConfig.NoBuildMessage = NoBuildMessageValue.GetText();
            g_MainConfig.MessageCannotDeployInSafeZone = MessageCannotDeployInSafeZoneValue.GetText();
            g_MainConfig.MessageBlockedItemDeployInPvE = MessageBlockedItemDeployInPvEValue.GetText();
            g_MainConfig.MessageBlockedItemDeployInPvP = MessageBlockedItemDeployInPvPValue.GetText();
            g_MainConfig.MessageBlockedItemDeployInRaid = MessageBlockedItemDeployInRaidValue.GetText();
            g_MainConfig.MessageItemRulesNotInitialized = MessageItemRulesNotInitializedValue.GetText();
            g_MainConfig.DynamicZoneRemovalRetrySeconds = ToInt(DynamicZoneRemovalRetrySecondsValue);
            g_MainConfig.AllowNoRelogOnServerCrash = AllowNoRelogOnServerCrashValue.IsChecked();
            g_MainConfig.RemoveDynamicZoneOnlyifNoPlayerInside = RemoveDynamicZoneOnlyifNoPlayerInsideValue.IsChecked();
            g_MainConfig.LB_ATMRobberyOnlyInPvP = ATMRobberyOnlyinPvPLBValue.IsChecked();
            g_MainConfig.LB_ATMRobberyEnableZoneCreation = ATMRobberyEnableZoneCreationValue.IsChecked();
            g_MainConfig.ExpansionReputationPenealtyPveEsPvE = ToInt(ExpansionReputationPenealtyPveEsPvEValue);
            g_MainConfig.EnableExpansionReputationPenaltyPvEvsPvE = EnableExpansionReputationPenaltyPvEvsPvEValue.IsChecked();
            g_MainConfig.StrikeLineTransparency = ToFloat(StrikeLineTransparencyValue);
            g_MainConfig.DisableActionBlockForAdmins = DisableActionBlockForAdminsValue.IsChecked();
            g_MainConfig.EVRStormSZNoShock = EVRStormSZNoShockValue.IsChecked();
            g_MainConfig.LB_AdminMapZones = LB_AdminMapValue.IsChecked();
            if (m_DayListGlobalPvP && g_MainConfig.GlobalPvPZoneDays && m_StartHourEditGlobalPvP && m_EndHourEditGlobalPvP)
            {
                int globalPvpSelectedRow = m_DayListGlobalPvP.GetSelectedRow();
                if (globalPvpSelectedRow >= 0)
                {
                    string selectedGlobalPvpDay;
                    m_DayListGlobalPvP.GetItemText(globalPvpSelectedRow, 0, selectedGlobalPvpDay);
                    for (int globalPvpIndex = 0; globalPvpIndex < g_MainConfig.GlobalPvPZoneDays.Count(); globalPvpIndex++)
                    {
                        DayConfig dayCfg = g_MainConfig.GlobalPvPZoneDays.Get(globalPvpIndex);
                        if (dayCfg && dayCfg.dayName == selectedGlobalPvpDay)
                        {
                            dayCfg.startHour = m_StartHourEditGlobalPvP.GetText().ToInt();
                            dayCfg.endHour = m_EndHourEditGlobalPvP.GetText().ToInt();
                            //Print("[NinjinsPvPPvE] Updated hours for " + selectedGlobalPvpDay + " (Start: " + dayCfg.startHour + ", End: " + dayCfg.endHour + ")");
                            break;
                        }
                    }
                }
            }
            if (m_DayListGlobalPvE && g_MainConfig.GlobalPvEZoneDays && m_StartHourEditGlobalPvE && m_EndHourEditGlobalPvE)
            {
                int globalPveSelectedRow = m_DayListGlobalPvE.GetSelectedRow();
                if (globalPveSelectedRow >= 0)
                {
                    string selectedGlobalPveDay;
                    m_DayListGlobalPvE.GetItemText(globalPveSelectedRow, 0, selectedGlobalPveDay);
                    for (int globalPveIndex = 0; globalPveIndex < g_MainConfig.GlobalPvEZoneDays.Count(); globalPveIndex++)
                    {
                        DayConfig pveDayCfg = g_MainConfig.GlobalPvEZoneDays.Get(globalPveIndex);
                        if (pveDayCfg && pveDayCfg.dayName == selectedGlobalPveDay)
                        {
                            pveDayCfg.startHour = m_StartHourEditGlobalPvE.GetText().ToInt();
                            pveDayCfg.endHour = m_EndHourEditGlobalPvE.GetText().ToInt();
                            //Print("[NinjinsPvPPvE] Updated GlobalPvE hours for " + selectedGlobalPveDay + " (Start: " + pveDayCfg.startHour + ", End: " + pveDayCfg.endHour + ")");
                            break;
                        }
                    }
                }
            }
            g_MainConfig.StrikeLineSpacingMeters = ToFloat(StrikeLineSpacingMetersValue);
            g_MainConfig.EnableItemSpawnZoneCreation = ToInt(EnableItemSpawnZoneCreationValue);
            g_MainConfig.EnableContaminatedZoneCreation = ToInt(EnableContaminatedZoneCreationValue);
            g_MainConfig.DisableAiZoneScanning = ToInt(DisableAiZoneScanningValue);
            g_MainConfig.DisableFallDamage = ToInt(DisableFallDamageValue);
            g_MainConfig.DisableFallDamageSZ = ToInt(DisableFallDamageSZValue);
            g_MainConfig.DisableFallDamagePvE = ToInt(DisableFallDamagePVEValue);
            g_MainConfig.StartingDayOfTheWeek = StartingDayOfTheWeekValue0.GetCurrentItem();
            g_MainConfig.BlockItemDamageStateorZones = BlockItemDamageStateorZonesValue0.GetCurrentItem();
            g_MainConfig.EnableReflectDamage  = ToInt(EnableReflectDamageValue0);
            g_MainConfig.PvPExitCountdown     = ToFloat(PvPExitCountdownValue);
            g_MainConfig.RaidExitCountdown    = ToFloat(RaidExitCountdownValue);
            g_MainConfig.SafeZoneExitCountdown = ToFloat(SafeZoneExitCountdownValue);
            g_MainConfig.PvEExitCountdown = ToFloat(PvEZoneExitCountDownValue);
            g_MainConfig.KillZombiesInSafeZone = ToInt(SafeZoneZombieKillPanelValue0);
            g_MainConfig.KillAnimalsInSafeZone = ToInt(SafeZoneAnimalKillPanelValue0);
            g_MainConfig.ZombieandAnimalSZKillScanInterval = ToFloat(SafeZoneZombieKillIntervalValue0);
            g_MainConfig.SZItemCleanUpInterval = SZItemCleanUpIntervalValue.GetText().ToFloat();
            g_MainConfig.DeleteItemsInSafeZone = DeleteItemsInSafeZoneValue.IsChecked();
            g_MainConfig.AllowRestrainTargetinPvE  = ToInt(AllowRestrainTargetinPvEValue0);
            g_MainConfig.AllowRestrainTargetinPvP  = ToInt(AllowRestrainTargetinPvPValue0);
            g_MainConfig.AllowRestrainTargetinRaid = ToInt(AllowRestrainTargetinRaidValue0);
            g_MainConfig.DisableGiveBloodTargetPvE  = ToInt(DisableGiveBloodTargetPvEValue);
            g_MainConfig.DisableForceFeedPvE  = ToInt(DisableForceFeedPvEValue);
            g_MainConfig.DisableForceDrinkPvE = ToInt(DisableForceDrinkPvEValue);
            g_MainConfig.DisableToxicExposureInPvE = ToInt(DisableToxicExposureInPvEValue);
            g_MainConfig.ThirdPersonOnlyDriver     = ToInt(ThirdPersonOnlyDriverValue0);
            g_MainConfig.EnablePvPEverywhere       = ToInt(EnablePvPEverywhereValue0);
            g_MainConfig.EnablePvEEverywhere       = ToInt(EnablePvEEverywhereValue0);
            g_MainConfig.ForceFirstPersonGlobalPvP = ToInt(ForceFirstPersonGlobalPvPValue0);
            g_MainConfig.ForceFirstPersonGlobalPvE = ToInt(ForceFirstPersonGlobalPvEValue0);
            g_MainConfig.BlockChemGasGrenadeOutsidePvP = ToInt(BlockChemGasGrenadeOutsidePvPValue0);
            g_MainConfig.EnableAFKKick = ToInt(EnableAFKKickValue);
            g_MainConfig.AFKKickTimeout = ToFloat(AFKKickTimeoutValue);
            g_MainConfig.LoggingLevel = ToInt(LoggingLevelValue0);
            g_MainConfig.AllowedRaidingPlayers.Clear();
            g_MainConfig.EnableMi8ZoneCreation = ToInt(Mi8CreationValue);
            g_MainConfig.EnableAirdropZoneCreation = ToInt(AirdropCreationValue);
            g_MainConfig.EnableAIMissionZoneCreation = ToInt(EnableAIMissionZoneCreationValue);
            g_MainConfig.EnableUH1YZoneCreation = ToInt(UH1YCreationValue);
            g_MainConfig.DisableArmExplosivePvE = ToInt(DisableArmExplosivePvEValue);
            g_MainConfig.CircleDrawingWidth = ToFloat(CircleDrawingWidthValue);
            g_MainConfig.AllowSameZoneTypeEnterNotifications = ToInt(AllowSameZoneTypeEnterNotificationsValue);
            #ifdef NinjinsPvPPvE_Vehicles
            g_MainConfig.VehicleZoneCheckInterval = ToFloat(VehicleZoneCheckIntervalValue);
            g_MainConfig.AlwaysAllowEnviroDmg = AlwaysAllowEnviroDmgValue.IsChecked();
            #endif
            #ifdef mz_koth
            g_MainConfig.EnableKOTHZoneCreation = ToInt(EnableKOTHZoneCreationValue);
            #endif
            #ifdef RizenKOTH
            g_MainConfig.EnableTKKOTHZoneCreation = ToInt(EnableTKKOTHZoneCreationValue);
            #endif
            g_MainConfig.DrawNamesOnZones       = ToInt(DrawNamesOnZonesValue0);
            g_MainConfig.LB_DrawMiniMapZones    = ToInt(LB_DrawMiniMapZonesValue0);
            g_MainConfig.LB_MiniMapDrawNames    = ToInt(LB_MiniMapDrawNamesValue0);
            g_MainConfig.DrawZonesOnVPPAdmin    = ToInt(DrawZonesOnVPPAdminValue0);
            g_MainConfig.DrawVPPAdminZoneLabels = ToInt(DrawVPPAdminZoneLabelsValue0);
            g_MainConfig.DrawZonesOnCOT         = ToInt(DrawZonesOnCOTValue0);
            g_MainConfig.DrawCOTAdminZoneLabels = ToInt(DrawCOTAdminZoneLabelsValue0);
            g_MainConfig.NoVehicleZoneExitBlockDelayMS = ToInt(NoVehicleZoneExitBlockDelayMSValue);
            g_MainConfig.NoVehicleZoneKillOrDestroyDelay = ToFloat(NoVehicleZoneKillOrDestroyDelayValue);
            if (NoVehicleKillPlayerOrDestroyVehicleValue0)
            {
                g_MainConfig.NoVehicleKillPlayerOrDestroyVehicle = NoVehicleKillPlayerOrDestroyVehicleValue0.GetCurrentItem();
            }
            g_MainConfig.NoVehicleWarningText            = NoVehicleWarningTextValue.GetText();
            g_MainConfig.NoVehicleWarningEffect = ComboText(NoVehicleWarningEffectValue);
            g_MainConfig.NoVehicleWarningEffectIntensity = ToFloat(NoVehicleWarningEffectIntensityValue);
            #ifdef NinjinsPvPPvE_Vehicles
            g_MainConfig.AllowVehicleDamagePvE           = ToInt(AllowVehicleDamagePvEValue);
            g_MainConfig.AllowVehicleDamagePvP           = ToInt(AllowVehicleDamagePvPValue);
            g_MainConfig.AllowVehicleDamageRaid          = ToInt(AllowVehicleDamageRaidValue);
            g_MainConfig.VehicleDamageLogging            = ToInt(VehicleDamageLoggingValue);
            #endif
            g_MainConfig.DestroyVehicleParts.Clear();
            {
                string rawParts = DestroyVehiclePartsValue.GetText().Trim();
                TStringArray splittedParts = new TStringArray;
                rawParts.Split(",", splittedParts);
                foreach (string part : splittedParts)
                {
                    part = part.Trim();
                    if (part != "")
                        g_MainConfig.DestroyVehicleParts.Insert(part);
                }
            }
            g_MainConfig.RemoveVehicleAttachments.Clear();
            {
                string rawAttachments = RemoveVehicleAttachmentsValue.GetText().Trim();
                TStringArray splittedAttachments = new TStringArray;
                rawAttachments.Split(",", splittedAttachments);
                foreach (string attach : splittedAttachments)
                {
                    attach = attach.Trim();
                    if (attach != "")
                        g_MainConfig.RemoveVehicleAttachments.Insert(attach);
                }
            }
            g_MainConfig.DestroyVehicleCargo.Clear();
            {
                string rawCargo = DestroyVehicleCargoValue.GetText().Trim();
                TStringArray splittedCargo = new TStringArray;
                rawCargo.Split(",", splittedCargo);
                foreach (string cargo : splittedCargo)
                {
                    cargo = cargo.Trim();
                    if (cargo != "")
                        g_MainConfig.DestroyVehicleCargo.Insert(cargo);
                }
            }
            g_MainConfig.OnlyAllowLockPickInPvP        = ToInt(OnlyAllowLockPickInPvPValue0);
            g_MainConfig.EnableLockpickingZoneCreation = ToInt(EnableLockpickingZoneCreationValue0);
            g_MainConfig.LockPickZoneDeletionTime      = ToFloat(LockPickZoneDeletionTimeValue);
            g_MainConfig.LockpickingZoneRadius         = ToFloat(LockpickingZoneRadiusValue);
            g_MainConfig.EnableLockpickingNotification = ToInt(EnableLockpickingNotificationValue0);
            g_MainConfig.LockpickNotificationBroadcastRadius = ToFloat(LockpickNotificationBroadcastRadiusValue);
            g_MainConfig.LockpickNotificationIconPath  = LockpickNotificationIconPathValue.GetText();
            g_MainConfig.LockpickNotificationTitle     = LockpickNotificationTitleValue.GetText();
            g_MainConfig.LockpickNotificationMessage   = LockpickNotificationMessageValue.GetText();
            g_MainConfig.LockpickNotificationColor     = ToInt(LockpickNotificationColorValue);
            g_MainConfig.DisableRaidingDialogActionOnFlagPole = ToInt(DisableRaidingDialogActionOnFlagPoleValue);
            g_MainConfig.AllowAnyPlayerInRaidZone             = ToInt(AllowAnyPlayerInRaidZoneValue);
            g_MainConfig.ExpansionGroupsFriendlyFireDisabled = ToInt(ExpansionGroupsFriendlyFireDisabledValue0);
            g_MainConfig.AiToPlayerDamageEverywhere   = ToInt(AiToPlayerDamageEverywhereValue0);
            g_MainConfig.PlayerToAiDamageEverywhere   = ToInt(PlayerToAiDamageEverywhereValue0);
            g_MainConfig.OnlyAllowAIToDoDamageIfPlayerIsPvP = ToInt(OnlyAllowAIToDoDamageIfPlayerIsPvPValue0);
            g_MainConfig.OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatus = ToInt(OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatusValue0);
            g_MainConfig.OnlyAllowAIToDoDamageIfPlayerIsPvE = ToInt(OnlyAllowAIToDoDamageIfPlayerIsPvEValue0);
            g_MainConfig.OnlyAllowDamageToAIIfPlayerHasPvEStatus = ToInt(OnlyAllowDamageToAIIfPlayerHasPvEStatusValue0);
            g_MainConfig.OnlyAllowAIToDamageInRaidMode      = ToInt(OnlyAllowAIToDamageInRaidModeValue0);
            g_MainConfig.OnlyAllowPlayersToDamageAIInRaidMode = ToInt(OnlyAllowPlayersToDamageAIInRaidModeValue0);
            g_MainConfig.EnableTerritoryFlagZones = ToInt(EnableTerritoryFlagZonesValue0);
            if (TerritoryFlagZoneCreateModeValue0)
                g_MainConfig.TerritoryFlagZoneCreateMode = TerritoryFlagZoneCreateModeValue0.GetCurrentItem();
            g_MainConfig.TerritoryFlagPvPZoneCheckInterval = ToFloat(TerritoryFlagPvPZoneCheckIntervalValue);   
            g_MainConfig.PvEImagePath  = PvEImagePathValue.GetText();
            g_MainConfig.PvPImagePath  = PvPImagePathValue.GetText();
            g_MainConfig.RaidImagePath = RaidImagePathValue.GetText();
            g_MainConfig.SafeZoneImagePath = SafeZoneImagePathValue.GetText();
            g_MainConfig.IconPositionX = ToFloat(IconXValue);
            g_MainConfig.IconPositionY = ToFloat(IconYValue);
            g_MainConfig.IconWidth     = ToFloat(IconWidthValue);
            g_MainConfig.IconHeight    = ToFloat(IconHeightValue);
            g_MainConfig.ExitZoneNotification = ToInt(ExitNotificationValue);
            g_MainConfig.PvPtoPvEBlockedNotification = ToInt(BlockedNotificationValue0);
            g_MainConfig.ExitNotificationText = ExitNotifMessage.GetText();
            g_MainConfig.ExitNotificationPanelPositionX = ToFloat(ExitNotifPanelXValue);
            g_MainConfig.ExitNotificationPanelPositionY = ToFloat(ExitNotifPanelYValue);
            g_MainConfig.NotificationPanelWidth         = ToFloat(ExitNotifPanelWidthValue);
            g_MainConfig.NotificationPanelHeight        = ToFloat(ExitNotifPanelHeightValue);
            g_MainConfig.AllowedRaidingPlayers = preservedRaiders;
            configParam = new Param1<ref MainConfig>(g_MainConfig);
            if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
            {
                GetRPCManager().SendRPC("NinjinsPvPPvE", "UpdateServerConfigAll", configParam, true, player.GetIdentity());
            }
            else
            {
                g_MainConfig.SaveConfig();
            }
            return true;
        }
        return super.OnClick(w, x, y, button);
    }
    void PopulateZoneList()
    {
        if (!zoneList)
            return;
        zoneList.ClearItems();
        ref array<ref ZoneBase> zones;
        MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
        if (mission)
            zones = mission.GetCachedZones();
        if (!zones || zones.Count() == 0)
            zones = ZoneManager.GetInstance().m_Zones;
        if (zones && zones.Count() > 0)
        {
            ref array<string> sortedNames = new array<string>();
            foreach (ZoneBase z : zones)
            {
                string zName = z.GetName();
                if (ShouldSkipZone(zName, skipPrefixes))
                    continue;
                sortedNames.Insert(zName);
            }
            sortedNames.Sort();
            foreach (string name : sortedNames)
            {
                zoneList.AddItem(name, NULL, 0);
            }
        }
        else
        {
            zoneList.AddItem("No zones available", NULL, 0);
        }
    }
    ref TStringArray skipPrefixes = {
        "UH1YZone_",
        "Mi8Zone_",
        "AirdropZone_",
        "Lockpick_",
        "FlagPvPZone_",
        "AIMission_",
        "KOTHZone_",
        "MZK_KOTHZone_",
        "ItemZone_",
        "ContaminatedArea_Dynamic_",
        "OldMi8Zone_",
        "DynamicPvPZone_ATMRobbery_"
    };
    bool ShouldSkipZone(string zoneName, TStringArray filters)
    {
        foreach (string prefix : filters)
        {
            if (zoneName.Contains(prefix))
                return true;
        }
        return false;
    }
    override bool OnDoubleClick(Widget w, int x, int y, int button)
    {
        if (!g_MapWidget || w != g_MapWidget)
            return super.OnDoubleClick(w, x, y, button);
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (button == MouseState.LEFT)
        {
            vector mapPos = g_MapWidget.ScreenToMap(Vector(x, y, 0));
            float ground = GetGame().SurfaceY(mapPos[0], mapPos[2]);
            mapPos[1] = ground;
            bool ctrlHeld = KeyState(KeyCode.KC_LCONTROL) > 0 || KeyState(KeyCode.KC_RCONTROL) > 0;
            bool altHeld = KeyState(KeyCode.KC_LMENU) > 0 || KeyState(KeyCode.KC_RMENU) > 0;
            bool shiftHeld = KeyState(KeyCode.KC_LSHIFT) > 0 || KeyState(KeyCode.KC_RSHIFT) > 0;
            Param3<float, float, float> posParam = new Param3<float, float, float>(0, 0, 0);
            if (altHeld)
            {
                if (NoLogOutTeleportPosXValue) NoLogOutTeleportPosXValue.SetText(mapPos[0].ToString());
                if (NoLogOutTeleportPosYValue) NoLogOutTeleportPosYValue.SetText(mapPos[1].ToString());
                if (NoLogOutTeleportPosZValue) NoLogOutTeleportPosZValue.SetText(mapPos[2].ToString());
            }
            else if (ctrlHeld)
            {
                if (player && player.GetIdentity())
                {
                    if (GetGame().IsMultiplayer() && GetGame().IsClient())
                    {
                        posParam.param1 = mapPos[0];
                        posParam.param2 = mapPos[1];
                        posParam.param3 = mapPos[2];
                        GetRPCManager().SendRPC("NinjinsPvPPvE", "TeleportPlayer", posParam, true, player.GetIdentity());
                    }
                }
            }
            else if (shiftHeld)
            {
                if (ZoneCenterXValue) ZoneCenterXValue.SetText(mapPos[0].ToString());
                if (ZoneCenterYValue) ZoneCenterYValue.SetText(mapPos[1].ToString());
                if (ZoneCenterZValue) ZoneCenterZValue.SetText(mapPos[2].ToString());
                if (GetGame().IsMultiplayer() && GetGame().IsClient() && player && player.GetIdentity())
                {
                    posParam.param1 = mapPos[0];
                    posParam.param2 = mapPos[1];
                    posParam.param3 = mapPos[2];
                    GetRPCManager().SendRPC("NinjinsPvPPvE", "AddZone", posParam, true, player.GetIdentity());
                    if (m_AdminMap)
                        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_AdminMap.UpdateZones, 300, false);
                    GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(RefreshZoneListUI, 700, false);
                    GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(SelectNewestZone, 900, false);
                }
                if (zonePropertiesPanel)
                    zonePropertiesPanel.Show(false);
            }
            else if (ZoneCenterXValue && ZoneCenterYValue && ZoneCenterZValue)
            {
                ZoneCenterXValue.SetText(mapPos[0].ToString());
                ZoneCenterYValue.SetText(mapPos[1].ToString());
                ZoneCenterZValue.SetText(mapPos[2].ToString());
            }
        }
        return super.OnDoubleClick(w, x, y, button);
    }
    void OnZoneSelected()
    {
        if (!zoneList) 
            return;
        int selectedIdx = zoneList.GetSelectedRow();
        if (selectedIdx < 0)
            return;
        string zoneName;
        zoneList.GetItemText(selectedIdx, 0, zoneName);
        ZoneBase selectedZone = FindZoneByName(zoneName);
        if (!selectedZone)
            return;
        PopulateZoneFields(selectedZone);
        if (m_AdminMap)
        {
            m_AdminMap.JumpToPosition(selectedZone.center);
        }
    }
    private ZoneBase FindZoneByName(string zoneName)
    {
        MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
        ref array<ref ZoneBase> zones;
        if (mission)
        {
            zones = mission.GetCachedZones();
        }
        if (!zones || zones.Count() == 0)
        {
            zones = ZoneManager.GetInstance().m_Zones;
        }
        for (int i = 0; i < zones.Count(); i++)
        {
            if (zones[i].name == zoneName)
            {
                return zones[i];
            }
        }
        return null;
    }
    void PopulateZoneFields(ZoneBase zone)
    {
        if (!zone) 
            return;
        ZoneNameValue.SetText(zone.name);
        int maxIndex = 5;
        int comboIndex = zone.type - 1;
        if (comboIndex < 0 || comboIndex > maxIndex)
        {
            comboIndex = 0;
        }
        int maxShapeIndex = 1;
        int shapeIndex = 0;
        if (zone.shape == ZoneShape.POLYGON)
            shapeIndex = 1;
        if (shapeIndex < 0 || shapeIndex > maxShapeIndex)
        {
            shapeIndex = 0;
        }
        HideWhenNestedTitleValue0.SetChecked(zone.HideWhenNested);
        ZoneDrawNoBuildShapeValue.SetChecked(zone.DrawNoBuildShape);
        ZoneIgnoreHeightCheckValue.SetChecked(zone.ignoreHeightCheck);
        ZoneMinHeightValue.SetText(zone.zoneMinHeight.ToString());
        ZoneMaxHeightValue.SetText(zone.zoneMaxHeight.ToString());
        ZoneNoBuildRadiusValue.SetText(zone.noBuildRadius.ToString());
        HideWhenNestedTitleValue.SetChecked(zone.Hide);
        EnableExpansion2DMarkerValue.SetChecked(zone.OnlyAllowExpansion2DMarker);
        EnableExpansion3DMarkerValue.SetChecked(zone.EnableExpansion3DMarker);
        ExpansionMarkerNameValue.SetText(zone.ExpansionMarkerName);
        Expansion3DIconValue.SetText(zone.Expansion3DIcon);
        ShapeTypeValue.SetCurrentItem(shapeIndex);
        ZoneTypeValue.SetCurrentItem(comboIndex);
        ZonePriorityValue.SetText(zone.priority.ToString());
        ZoneEnableCustomMessagesValue.SetChecked(zone.enableCustomMessages);
        displayNameValue.SetText(zone.displayName);
        ZoneCustomTitleValue.SetText(zone.customTitle);
        ZoneCustomMessageEnterValue.SetText(zone.customMessageEnter);
        ZoneCustomMessageExitValue.SetText(zone.customMessageExit);
        ZoneCustomIconValue.SetText(zone.customIcon);
        ZoneNotificationColorValue.SetText(zone.notificationColor.ToString());
        if (m_DayList) 
        {
            m_DayList.ClearItems();
            m_DayConfigs.Clear();
            m_CurrentSelectedDay = "";
            if (zone.dayConfigs && zone.dayConfigs.Count() > 0) 
            {
                foreach (DayConfig config : zone.dayConfigs) 
                {
                    int row = m_DayList.AddItem(config.dayName, NULL, 0);
                    DayConfig newConfig = new DayConfig(config.dayName, config.startHour, config.endHour);
                    m_DayConfigs.Set(config.dayName, newConfig);
                    if (row == 0) 
                    {
                        m_DayList.SelectRow(0);
                        m_CurrentSelectedDay = config.dayName;
                        if (m_StartHourEdit) m_StartHourEdit.SetText(config.startHour.ToString());
                        if (m_EndHourEdit) m_EndHourEdit.SetText(config.endHour.ToString());
                        if (m_SelectedDayText) m_SelectedDayText.SetText(config.dayName);
                    }
                }
            } 
            else 
            {     
                if (m_StartHourEdit) m_StartHourEdit.SetText("");
                if (m_EndHourEdit) m_EndHourEdit.SetText("");
                if (m_SelectedDayText) m_SelectedDayText.SetText("");
            }
        }
        ZoneForceFirstPersonValue.SetChecked(zone.forceFirstPerson);
        drawStrikeZoneValue.SetChecked(zone.drawStrikeZone);
        ZoneDrawShapeValue.SetChecked(zone.drawShape);
        ZoneRadiusValue.SetText(zone.radius.ToString());
        ZoneAlphaValue.SetText(zone.zoneAlpha.ToString());
        ZoneRedValue.SetText(zone.zoneRed.ToString());
        ZoneGreenValue.SetText(zone.zoneGreen.ToString());
        ZoneBlueValue.SetText(zone.zoneBlue.ToString());
        ZoneCenterXValue.SetText(zone.center[0].ToString());
        ZoneCenterYValue.SetText(zone.center[1].ToString());
        ZoneCenterZValue.SetText(zone.center[2].ToString());
        NoLogOutTeleportPosXValue.SetText(zone.NoLogOutTeleportPos[0].ToString());
        NoLogOutTeleportPosYValue.SetText(zone.NoLogOutTeleportPos[1].ToString());
        NoLogOutTeleportPosZValue.SetText(zone.NoLogOutTeleportPos[2].ToString());
        NoLogOutValue.SetChecked(zone.NoLogOut);
        ZoneNoVehicleValue.SetChecked(zone.UsesDisallowedVehicles);
        ZoneLabelOffsetXValue.SetText(zone.ZonelabelOffsetX_Meters.ToString());
        ZoneLabelOffsetZValue.SetText(zone.ZonelabelOffsetZ_Meters.ToString());
        ZoneLabelColorValue.SetText(zone.ZoneLabelColor.ToString());
        RefreshAllCheckBoxes(ZoneEditContainer);
    }
    override bool OnChange(Widget w, int x, int y, bool finished)
    {
        if (w == m_SearchBox)
        {
            UpdateList();
            return true;
        }
        else if (w == IconsliderX || w == IconsliderY)
        {
            if (!IconsliderX || !IconsliderY)
                return true;
            UpdatePreviewIconPosition();
            g_MainConfig.IconPositionX = IconsliderX.GetCurrent();
            g_MainConfig.IconPositionY = IconsliderY.GetCurrent();
            return true;
        }
        else if (w == PvPIconColorValue || w == PvEIconColorValue || w == RaidIconColorValue || w == SafeZoneIconColorValue)
        {
            EditBoxWidget colorBox = EditBoxWidget.Cast(w);
            if (colorBox)
            {
                string colorText = colorBox.GetText();
                int parsedColor = 0xFFFFFFFF;
                if (colorText != "" && colorText != "-")
                {
                    parsedColor = colorText.ToInt();
                }
                colorBox.SetColor(parsedColor);
            }
            return true;
        }
        return super.OnChange(w, x, y, finished);
    }
    override bool OnMouseButtonDown(Widget w, int x, int y, int button)
    {
        super.OnMouseButtonDown(w, x, y, button);
        if (w == m_ItemPreviewWidget && button == MouseState.LEFT)
        {
            GetGame().GetDragQueue().Call(this, "UpdateRotation");
            GetMousePos(m_MouseX, m_MouseY);
            return true;
        }
        return false;
    }
    override bool OnMouseWheel(Widget w, int x, int y, int wheel)
    {
        if (w == m_ItemPreviewWidget)
        {
            UpdateDistance(wheel);
            return true;
        }
        return super.OnMouseWheel(w, x, y, wheel);
    }
    void UpdateDistance(float drag)
    {
        m_Distance += drag * 0.1;
        m_ItemPreviewWidget.SetModelPosition(Vector(m_Distance, 0, 1.0 + m_Distance));
    }
/*
 * ===================================================================
 * HELPER FUNCTIONS
 * ===================================================================
 */
    ref array<string> GetAvailableItemsFromConfig()
    {
        ref array<string> itemsList = new array<string>;
        TStringArray configPaths = {"CfgVehicles", "CfgWeapons", "CfgMagazines", "CfgItems"};
        foreach (string configPath : configPaths)
        {
            int numClasses = GetGame().ConfigGetChildrenCount(configPath);
            for (int i = 0; i < numClasses; i++)
            {
                string className;
                GetGame().ConfigGetChildName(configPath, i, className);
                int scope = GetGame().ConfigGetInt(configPath + " " + className + " scope");
                if (scope == 2)
                {
                    itemsList.Insert(className);
                }
            }
        }
        return itemsList;
    }
    void UpdateList()
    {
        string userInput = m_SearchBox.GetText();
        userInput.ToLower();
        if (userInput != "")
        {
            TStringArray matchedItems = new TStringArray;
            TStringArray categoryPaths = new TStringArray;
            categoryPaths.Insert(CFG_VEHICLESPATH);
            categoryPaths.Insert(CFG_WEAPONSPATH);
            categoryPaths.Insert(CFG_MAGAZINESPATH);
            categoryPaths.Insert(CFG_NONAI_VEHICLES);
            for (int i = 0; i < categoryPaths.Count(); i++)
            {
                string currentPath = categoryPaths.Get(i);
                int totalClasses = GetGame().ConfigGetChildrenCount(currentPath);
                int classStartIndex = 0;
                if (i == 0) classStartIndex = 20;
                for (int j = classStartIndex; j < totalClasses; j++)
                {
                    string className;
                    GetGame().ConfigGetChildName(currentPath, j, className);
                    int itemScope = GetGame().ConfigGetInt(currentPath + " " + className + " scope");
                    if (itemScope == 0)
                        continue;
                    if (!GetGame().ConfigIsExisting(currentPath + " " + className + " model"))
                        continue;
                    string lowerClassName = className;
                    lowerClassName.ToLower();
                    if (lowerClassName.Contains(userInput))
                    {
                        matchedItems.Insert(className);
                    }
                }
            }
            if (matchedItems.Count() > 0)
            {
                matchedItems.Sort();
                m_ItemList.ClearItems();
                foreach (string item : matchedItems)
                {
                    m_ItemList.AddItem(item, NULL, 0);
                }
                m_ItemList.Update();
                int selectedRow = m_ItemList.GetSelectedRow();
                selectedRow = m_ItemList.GetSelectedRow();
                if (selectedRow >= 0)
                {
                    string selectedItem;
                    m_ItemList.GetItemText(selectedRow, 0, selectedItem);
                }
            }
            else
            {
                m_ItemList.ClearItems();
            }
        }
        else
        {
            m_ItemList.ClearItems();
        }
    }
    void RefreshOnlinePlayers()
    {
        if (!m_OnlinePlayersList) 
            return;
        m_OnlinePlayersList.ClearItems();
        GetRPCManager().SendRPC("NinjinsPvPPvE", "RequestOnlinePlayers", new Param1<int>(0), true, null);
    }
    void UpdateOnlinePlayersList(array<string> players)
    {
        if (!m_OnlinePlayersList) 
            return;
        m_OnlinePlayersList.ClearItems();
        foreach (string entry : players)
        {
            m_OnlinePlayersList.AddItem(entry, null, 0);
        }
    }
    void PopulateAllowedRaidingPlayers()
    {
        if (!m_AllowedPlayersRaidingList || !g_MainConfig)
            return;
        m_AllowedPlayersRaidingList.ClearItems();
        foreach (string entry : g_MainConfig.AllowedRaidingPlayers)
        {
            m_AllowedPlayersRaidingList.AddItem(entry, null, 0);
        }
    }
    void UpdateCheckBoxColor(CheckBoxWidget cb)
    {
        if (!cb)
            return;
        if (cb.IsChecked())
        {
            cb.SetColor(COLOR_CHECKED);
        }
        else
        {
            cb.SetColor(COLOR_UNCHECK);
        }
    }
    void RefreshAllCheckBoxes(Widget root)
    {
        if (!root) 
            return;
        Widget w = root.GetChildren();
        while (w)
        {
            if (w.IsInherited(CheckBoxWidget))
                UpdateCheckBoxColor(CheckBoxWidget.Cast(w));
            RefreshAllCheckBoxes(w);
            w = w.GetSibling();
        }
    }
    bool IsZoneEditContainerVisible() 
    {
        return layoutRoot.FindAnyWidget("ZoneEditContainer").IsVisible();
    }
    void UpdateRotation(int mouse_x, int mouse_y, bool is_dragging)
    {
        m_Orientation[0] = m_Orientation[0] + ((m_MouseY - mouse_y) * 0.01);
        m_Orientation[1] = m_Orientation[1] - ((m_MouseX - mouse_x) * 0.01);
        m_ItemPreviewWidget.SetModelOrientation(m_Orientation);
    }
    private void AddClassnameToListAndRPC(string classname, TextListboxWidget listWidget, string rpcMethod)
    {
        classname.Trim();
        if (classname == "") 
            return;
        Param1<string> param = new Param1<string>(classname);
        GetRPCManager().SendRPC("NinjinsPvPPvE", rpcMethod, param, true);
        listWidget.AddItem(classname, NULL, 0);
    }
    private float ToFloat(EditBoxWidget w)
    {
        if (!w) return 0.0;
        return w.GetText().ToFloat();
    }
    private int ToInt(EditBoxWidget w)
    {
        if (!w) return 0;
        return w.GetText().ToInt();
    }
    private int ToInt(CheckBoxWidget cb)
    {
        if (cb && cb.IsChecked())
            return 1;
        return 0;
    }
    private string ComboText(XComboBoxWidget combo)
    {
        switch (combo.GetCurrentItem())
        {
            case 0: return "shock";
            case 1: return "blur";
            case 2: return "blood";
            case 3: return "redscreen";
            case 4: return "blackscreen";
        }
        return "shock";
    }
    override void Update(float timeslice)
    {
        super.Update(timeslice);
        if (m_ActualMapContainer && m_ActualMapContainer.IsVisible() && m_AdminMap)
            m_AdminMap.TriggerUpdate();
    }
    NinjinsAdminMenuMap GetAdminMap()
    {
        return m_AdminMap;
    }
    private void ShowOnlyPanels(array<Widget> panelsToShow)
    {
        array<Widget> allPanels =
        {
            GeneralRootPanel, MapRootPanel, VehicleRootPanel, LockpickRootPanel,
            TerritoryRootPanel, AIRootPanel, OtherRootPanel, RaidPanelRoot,
            ZoneEditContainer, ItemRulesPanel, ItemSearch, zonePropertiesPanel,
            PvEBlockedExplosivesDamagePanel, DisallowedVehiclesPanelRules,
            CantBeDamagedOnGround, BypassZoneChecksGrenades,CantBeDamagedAnimalsinPvE,
            BlockDeployIfPlayerInPvEStatePanel,BlockDeployIfPlayerInPvPStatePanel,
            BlockDeployIfPlayerInRaidStatePanel, TitlePanel, Info1, Info2,
            m_ActualMapContainer, g_MapWidget, IconPanel};
        foreach (Widget panel : allPanels)
        {
            if (panel)
                panel.Show(panelsToShow.Find(panel) != -1);
        }
    }
    void RefreshZoneListUI()
    {
        PopulateZoneList();
        if (zoneList)
        {
            zoneList.SelectRow(-1);
        }
    }
    void RefreshMainConfigUI()
    {
        if (!g_MainConfig) 
            return;
        OnShow();
    }
    void SelectNewestZone()
    {
        PopulateZoneList();
        int count = zoneList.GetNumItems();
        if (count > 0)
        {
            int lastIndex = count - 1;
            zoneList.SelectRow(lastIndex);
            OnZoneSelected();
        }
    }
    void SelectZoneByName(string zoneName)
    {
        int count = zoneList.GetNumItems();
        for (int i = 0; i < count; i++)
        {
            string itemName;
            zoneList.GetItemText(i, 0, itemName);
            if (itemName == zoneName)
            {
                zoneList.SelectRow(i);
                OnZoneSelected();
                break;
            }
        }
    }
    void UpdateItemPreview(string itemClassName)
    {
        if (m_PreviewItem)
        {
            GetGame().ObjectDelete(m_PreviewItem);
            m_PreviewItem = null;
        }
        if (itemClassName == "")
        {
            if (m_ItemPreviewWidget)
                m_ItemPreviewWidget.Show(false);
            return;
        }
        m_PreviewItem = EntityAI.Cast(GetGame().CreateObject(itemClassName, vector.Zero, true, false, false));
        if (m_PreviewItem)
        {
            dBodyActive(m_PreviewItem, ActiveState.INACTIVE);
            m_PreviewItem.DisableSimulation(true);
            m_ItemPreviewWidget.SetItem(m_PreviewItem);
            m_ItemPreviewWidget.SetModelPosition("0 0 0.5");
            m_ItemPreviewWidget.SetModelOrientation("0 0 0");
            m_ItemPreviewWidget.Show(true);
        }
        else
        {
            if (m_ItemPreviewWidget)
                m_ItemPreviewWidget.Show(false);
        }
    }
    void UpdatePreviewIconPosition()
    {
        if (!previewIconChange || !IconsliderX || !IconsliderY)
            return;
        float posX = IconsliderX.GetCurrent();
        float posY = IconsliderY.GetCurrent();
        previewIconChange.SetPos(posX, posY, true);
        previewIconChange.Update();
        g_MainConfig.IconPositionX = posX;
        g_MainConfig.IconPositionY = posY;
    }
    void ReloadItemList(string searchText = "")
    {
        if (!m_ItemList) 
            return;
        m_ItemList.ClearItems();
        searchText.ToLower();
        TStringArray configPaths = { "CfgVehicles", "CfgWeapons", "CfgMagazines", "CfgItems" };
        TStringArray matchedItems = new TStringArray;
        foreach (string path : configPaths)
        {
            int count = GetGame().ConfigGetChildrenCount(path);
            for (int i = 0; i < count; i++)
            {
                string className;
                GetGame().ConfigGetChildName(path, i, className);
                string fullPath = path + " " + className + " scope";
                if (!GetGame().ConfigIsExisting(fullPath))
                    continue;
                int scope = GetGame().ConfigGetInt(fullPath);
                if (scope < 2)
                    continue;
                bool skip = false;
                if (m_FilterByPrefixOnly)
                {
                    if (className.IndexOf(m_PrefixFilter) != 0)
                        skip = true;
                }
                else if (m_CurrentFilterBaseClass != "")
                {
                    if (!GetGame().IsKindOf(className, m_CurrentFilterBaseClass))
                        skip = true;
                }
                if (skip)
                    continue;
                string lowerName = className;
                lowerName.ToLower();
                if (searchText == "" || lowerName.Contains(searchText))
                {
                    matchedItems.Insert(className);
                }
            }
        }
        matchedItems.Sort();
        foreach (string item : matchedItems)
        {
            m_ItemList.AddItem(item, NULL, 0);
        }
        m_ItemList.Update();
    }
    void HighlightActiveFilterButton(Widget activeButton)
    {
        foreach (Widget btn, string filter : m_FilterButtonMap)
        {
            if (btn)
            {
                if (btn == activeButton)
                {
                    btn.SetColor(ARGB(255, 50, 150, 250));
                }
                else
                {
                    btn.SetColor(ARGB(255, 200, 200, 200));
                }
            }
        }
    }
    static void ForceDisableInputs(bool state, inout TIntArray skipIDs = null)
    {
        if (!skipIDs)
            skipIDs = new TIntArray;
            skipIDs.Insert(UAUIBack);
            skipIDs.Insert(UAAdminMenu);
        TIntArray inputIDs = new TIntArray;
        GetUApi().GetActiveInputs(inputIDs);
        foreach (int inputID : inputIDs)
        {
            if (skipIDs.Find(inputID) == -1)
            {
                GetUApi().GetInputByID(inputID).ForceDisable(state);
            }
        }
    }
}
