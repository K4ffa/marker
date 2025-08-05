class NinjinClientSettingsMenu extends UIScriptedMenu
{
	private CheckBoxWidget m_CheckDrawMiniMapZones;
    private CheckBoxWidget m_CheckDrawMiniMapLabels;
	private SliderWidget m_SliderX;
	private SliderWidget m_SliderY;
	private SliderWidget m_SliderWidth;
	private SliderWidget m_SliderHeight;
	private CheckBoxWidget m_CheckShowPvP;
	private CheckBoxWidget m_CheckShowPvE;
	private CheckBoxWidget m_CheckShowRaid;
	private CheckBoxWidget m_CheckShowSafeZone;
	private CheckBoxWidget m_CheckShowPaintball;
	private CheckBoxWidget m_CheckShowVisual;
	private CheckBoxWidget m_CheckShowZoneLabels;
	private CheckBoxWidget m_CheckShowNoBuildRadius;
	private Widget m_MapLegendRoot;
	private ButtonWidget m_SaveBtn;
	private Widget m_PreviewIcon;
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/ClientSettingsMenu.layout");
		m_SliderX = SliderWidget.Cast(layoutRoot.FindAnyWidget("IconsliderX"));
		m_SliderY = SliderWidget.Cast(layoutRoot.FindAnyWidget("IconsliderY"));
		m_SliderWidth = SliderWidget.Cast(layoutRoot.FindAnyWidget("SliderIconWidth"));
		m_SliderHeight = SliderWidget.Cast(layoutRoot.FindAnyWidget("SliderIconHeight"));
		m_SaveBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnGeneralApplyIcon"));
		m_PreviewIcon = layoutRoot.FindAnyWidget("previewIconChange");
		m_CheckShowPvP           = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckShowPvP"));
		m_CheckShowPvE           = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckShowPvE"));
		m_CheckShowRaid          = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckShowRaid"));
		m_CheckShowSafeZone      = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckShowSafeZone"));
		m_CheckShowPaintball     = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckShowPaintball"));
		m_CheckShowVisual        = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckShowVisual"));
		m_CheckShowZoneLabels    = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckShowZoneLabels"));
		m_CheckShowNoBuildRadius = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckShowNoBuildRadius"));
		m_MapLegendRoot 		 = Widget.Cast(layoutRoot.FindAnyWidget("mapLegend"));
		m_CheckDrawMiniMapZones   = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckDrawMiniMapZones"));
        m_CheckDrawMiniMapLabels  = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("CheckDrawMiniMapLabels"));

		NinjinClientZoneSettings settings = new NinjinClientZoneSettings();
		settings.Load();
		if (m_CheckDrawMiniMapZones)  
			m_CheckDrawMiniMapZones.SetChecked(settings.drawMiniMapZones);
        if (m_CheckDrawMiniMapLabels) 
			m_CheckDrawMiniMapLabels.SetChecked(settings.drawMiniMapLabels);
		if (m_SliderX)
			m_SliderX.SetCurrent(settings.iconPosX);
		if (m_SliderY)
			m_SliderY.SetCurrent(settings.iconPosY);
		if (m_SliderWidth)
			m_SliderWidth.SetCurrent(settings.iconWidth);
		if (m_SliderHeight)
			m_SliderHeight.SetCurrent(settings.iconHeight);
		if (m_CheckShowPvP)           
			m_CheckShowPvP.SetChecked(settings.showPvP);
		if (m_CheckShowPvE)          
			m_CheckShowPvE.SetChecked(settings.showPvE);
		if (m_CheckShowRaid)          
			m_CheckShowRaid.SetChecked(settings.showRaid);
		if (m_CheckShowSafeZone)      
			m_CheckShowSafeZone.SetChecked(settings.showSafeZone);
		if (m_CheckShowPaintball)     
			m_CheckShowPaintball.SetChecked(settings.showPaintball);
		if (m_CheckShowVisual)        
			m_CheckShowVisual.SetChecked(settings.showVisual);
		if (m_CheckShowZoneLabels)    
			m_CheckShowZoneLabels.SetChecked(settings.showZoneLabels);
		if (m_CheckShowNoBuildRadius) 
			m_CheckShowNoBuildRadius.SetChecked(settings.showNoBuildRadius);
		UpdatePreviewIconPosition();
		PopulateMapLegend();
		return layoutRoot;
	}
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (w == m_SaveBtn)
		{
			NinjinClientZoneSettings settings = new NinjinClientZoneSettings();
			settings.Load();
			if (m_CheckDrawMiniMapZones)
                settings.drawMiniMapZones = m_CheckDrawMiniMapZones.IsChecked();
            if (m_CheckDrawMiniMapLabels)
                settings.drawMiniMapLabels = m_CheckDrawMiniMapLabels.IsChecked();
			if (m_SliderX)
				settings.iconPosX = m_SliderX.GetCurrent();
			if (m_SliderY)
				settings.iconPosY = m_SliderY.GetCurrent();
			if (m_SliderWidth)
				settings.iconWidth = m_SliderWidth.GetCurrent();
			if (m_SliderHeight)
				settings.iconHeight = m_SliderHeight.GetCurrent();
			if (m_CheckShowPvP)
				settings.showPvP = m_CheckShowPvP.IsChecked();
			if (m_CheckShowPvE)
				settings.showPvE = m_CheckShowPvE.IsChecked();
			if (m_CheckShowRaid)
				settings.showRaid = m_CheckShowRaid.IsChecked();
			if (m_CheckShowSafeZone)
				settings.showSafeZone = m_CheckShowSafeZone.IsChecked();
			if (m_CheckShowPaintball)
				settings.showPaintball = m_CheckShowPaintball.IsChecked();
			if (m_CheckShowVisual)
				settings.showVisual = m_CheckShowVisual.IsChecked();
			if (m_CheckShowZoneLabels)
				settings.showZoneLabels = m_CheckShowZoneLabels.IsChecked();
			if (m_CheckShowNoBuildRadius)
				settings.showNoBuildRadius = m_CheckShowNoBuildRadius.IsChecked();
			settings.Save();
			MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
			if (mission)
			{
				mission.ApplyIconPosition();
				mission.ApplyIconSize();
			}	
			return true;
		}
		return false;
	}
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		if (w == m_SliderX || w == m_SliderY)
		{
			UpdatePreviewIconPosition();
			return true;
		}
		return super.OnChange(w, x, y, finished);
	}
	private void UpdatePreviewIconPosition()
	{
		if (!m_PreviewIcon || !m_SliderX || !m_SliderY)
			return;
		float x = m_SliderX.GetCurrent();
		float y = m_SliderY.GetCurrent();
		m_PreviewIcon.SetPos(x, y, true);
	}
	override void OnShow()
	{
        super.OnShow();
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        PPEffects.SetBlurMenu(0.5);
        GetGame().GetInput().ChangeGameFocus(1);
        GetGame().GetUIManager().ShowUICursor(true);
        GetGame().GetMission().GetHud().Show(true);
        TIntArray skip = { UAUIBack, UAAdminMenu  };
        ForceDisableInputs(true, skip);
		PopulateMapLegend();
        SetFocus(layoutRoot);
	}
    override void OnHide()
    {
        super.OnHide();   
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        ForceDisableInputs(false);
        PPEffects.SetBlurMenu(0);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor(false);
        GetGame().GetMission().GetHud().Show(true);
        Close();
    }
    static void ForceDisableInputs(bool state, inout TIntArray skipIDs = null)
    {
        if (!skipIDs)
            skipIDs = new TIntArray;
            skipIDs.Insert(UAUIBack);
            skipIDs.Insert(UAClientZoneSettingsMenu);
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
	private void PopulateMapLegend()
	{
		if (!m_MapLegendRoot || !g_MainConfig || !g_MainConfig.mapLegend)
			return;
		while (m_MapLegendRoot.GetChildren())
			m_MapLegendRoot.GetChildren().Unlink();
		float totalHeight = 0;
		float widgetWidth = 420;
		float spacing = 16;
		if (g_MainConfig.mapLegendTitle != "")
		{
			TextWidget title = TextWidget.Cast(layoutRoot.FindAnyWidget("MapLegendTitle"));
			if (title)
			{
				title.SetText(g_MainConfig.mapLegendTitle);
				title.SetColor(ARGB(255, 255, 255, 255));
			}
			totalHeight += 60 + spacing;
		}
		foreach (MapLegendEntry entry : g_MainConfig.mapLegend)
		{
			TextWidget label = TextWidget.Cast(NinjinLayoutManager.CreateLayout("MapLegendLabel", m_MapLegendRoot));
			if (label)
			{
				label.SetText(entry.name);
				label.SetColor(ARGB(entry.ColorAlpha, entry.ColorRed, entry.ColorGreen, entry.ColorBlue));
				label.SetSize(widgetWidth, 40);
				label.SetPos(0, totalHeight);
				totalHeight += 40 + spacing;
			}
		}
		Widget parent = m_MapLegendRoot.GetParent();
		if (parent)
			parent.SetSize(widgetWidth, totalHeight + spacing);
		m_MapLegendRoot.SetSize(widgetWidth, totalHeight + spacing);
		m_MapLegendRoot.SetPos(0, 0);
	}
}
class NinjinLayoutManager
{
	static string GetLayoutPath(string name)
	{
		if (name == "MapLegendLabel")
			return "NinjinsPvPPvE/gui/layouts/MapLegendLabel.layout";
		return ""; 
	}
	static Widget CreateLayout(string name, Widget parent)
	{
		string path = GetLayoutPath(name);
		if (path != "")
			return GetGame().GetWorkspace().CreateWidgets(path, parent);
		return null;
	}
}
