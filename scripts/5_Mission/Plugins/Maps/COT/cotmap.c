#ifdef JM_COT
modded class JMMapForm : JMFormBase
{
    private ref MapDrawer m_MapDrawer;
    private MapWidget     m_MapWidget;
    private CanvasWidget  m_DrawCanvas;
    override void OnInit()
    {
        super.OnInit();
        m_MapWidget = MapWidget.Cast(layoutRoot.FindAnyWidget("map_widget"));
        if (!m_MapWidget)
        {
            NinjinsPvPPvE.LogWarning("[JMMapForm] ERROR: MapWidget not found.");
            return;
        }
        CanvasWidget oldCanvas = CanvasWidget.Cast(m_MapWidget.FindAnyWidget("ninjindrawCanvas"));
        if (oldCanvas)
        {
            oldCanvas.Unlink();
            oldCanvas = null;
        }
        MapDrawer.ResetInstance(m_MapWidget);
        Widget canvasLayout = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/NinjinsMapCanvasOnly.layout", m_MapWidget);
        if (!canvasLayout) 
            return;
        m_DrawCanvas = CanvasWidget.Cast(canvasLayout.FindAnyWidget("ninjindrawCanvas"));
        if (!m_DrawCanvas) 
            return;
        m_MapDrawer = MapDrawer.GetInstance(m_MapWidget, m_DrawCanvas);
        if (!m_MapDrawer)
            NinjinsPvPPvE.LogWarning("[JMMapForm] ERROR: Failed to initialize MapDrawer.");
    }
    override void OnShow()
    {
        super.OnShow();
        UpdateMapMarkers();
    }
    override void UpdateMapMarkers()
    {
        super.UpdateMapMarkers();
        GetRPCManager().SendRPC("NinjinsPvPPvE", "RequestZones", NULL, true, null);
        if (!m_MapDrawer) 
            return;
        if (g_MainConfig && g_MainConfig.DrawZonesOnCOT == 0) 
            return;
        MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
        if (!mission) 
            return;
        array<ref ZoneBase> zones = mission.GetCachedZones();
        bool drawLabels = g_MainConfig && g_MainConfig.DrawCOTAdminZoneLabels == 1;
        m_MapDrawer.UpdateZones(zones, drawLabels, true);
        UpdatePlayers();
    }
    override void Update()
    {
        super.Update();
        if (m_MapDrawer && m_MapDrawer.HasValidWidget())
            m_MapDrawer.TriggerUpdate();
    }
    override void OnHide()
    {
        super.OnHide();
        MapDrawer.ResetInstance(m_MapWidget);
        m_MapDrawer  = null;
        m_DrawCanvas = null;
    }
}
#endif
