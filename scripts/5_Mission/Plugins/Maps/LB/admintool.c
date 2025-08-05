#ifdef LBmaster_AdminTools
modded class LBAdminMenuFrame_PlayerMap : LBAdminMenuFrame 
{
    private ref MapDrawer m_MapDrawerZones;
    private CanvasWidget  m_DrawCanvasZones;
    private MapWidget     m_MapWidgetZones;
    override void OnShow() 
    {
        super.OnShow();
        InitializeZoneDrawer();
        DrawZoneData();
    }
    private void InitializeZoneDrawer() 
    {
        m_MapWidgetZones = MapWidget.Cast(layoutRoot.FindAnyWidget("mapWidget"));
        if (!m_MapWidgetZones) 
        {
            NinjinsPvPPvE.LogWarning("[LBAdminMenuFrame_PlayerMap] ERROR: MapWidget not found.");
            return;
        }
        CanvasWidget oldCanvas = CanvasWidget.Cast(m_MapWidgetZones.FindAnyWidget("ninjindrawCanvas"));
        if (oldCanvas) 
        {
            oldCanvas.Unlink();
            oldCanvas = null;
        }
        MapDrawer.ResetInstance(m_MapWidgetZones);
        Widget canvasLayout = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/NinjinsMapCanvasOnly.layout", m_MapWidgetZones);
        if (!canvasLayout) 
        {
            NinjinsPvPPvE.LogWarning("[LBAdminMenuFrame_PlayerMap] ERROR: Failed to load canvas-only layout.");
            return;
        }
        m_DrawCanvasZones = CanvasWidget.Cast(canvasLayout.FindAnyWidget("ninjindrawCanvas"));
        if (!m_DrawCanvasZones) 
        {
            NinjinsPvPPvE.LogWarning("[LBAdminMenuFrame_PlayerMap] ERROR: drawCanvas not found in layout.");
            return;
        }
        m_MapDrawerZones = MapDrawer.GetInstance(m_MapWidgetZones, m_DrawCanvasZones);
    }
    private void DrawZoneData() 
    {
        GetRPCManager().SendRPC("NinjinsPvPPvE", "RequestZones", NULL, true, null);
        if (!m_MapDrawerZones || !g_MainConfig || !g_MainConfig.LB_AdminMapZones)
            return;
        MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
        if (!mission)
            return;
        array<ref ZoneBase> zones = mission.GetCachedZones();
        bool drawLabels = g_MainConfig.DrawNamesOnZones;
        m_MapDrawerZones.UpdateZones(zones, drawLabels, true);
    }
    override void Update(float timeslice, bool otherMenu, bool leftClicked) 
    {
        super.Update(timeslice, otherMenu, leftClicked);
        if (m_MapDrawerZones && m_MapDrawerZones.HasValidWidget()) 
        {
            m_MapDrawerZones.TriggerUpdate();
        }
    }
    override void OnHide() 
    {
        super.OnHide();
        MapDrawer.ResetInstance(m_MapWidgetZones);
        m_MapDrawerZones = null;
        m_DrawCanvasZones = null;
    }
}
#endif
