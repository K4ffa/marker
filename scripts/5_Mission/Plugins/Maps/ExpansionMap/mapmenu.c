#ifdef EXPANSIONMODNAVIGATION
modded class ExpansionMapMenu extends UIScriptedMenu
{
    private ref MapDrawer m_MapDrawer;
    private CanvasWidget  m_DrawCanvas;
    private MapWidget     m_MapWidget;
    private float         m_LastZoneRequestTime = 0;
    private const float   ZONE_REQUEST_COOLDOWN = 10.0; 
    override Widget Init()
    {
        super.Init();
        m_MapWidget = MapWidget.Cast(layoutRoot.FindAnyWidget("Map"));
        if (!m_MapWidget)
        {
            NinjinsPvPPvE.LogWarning("[ExpansionMapMenu] ERROR: MapWidget not found.");
            return layoutRoot;
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
        {
            NinjinsPvPPvE.LogWarning("[ExpansionMapMenu] ERROR: Failed to load canvas-only layout.");
            return layoutRoot;
        }
        m_DrawCanvas = CanvasWidget.Cast(canvasLayout.FindAnyWidget("ninjindrawCanvas"));
        if (!m_DrawCanvas)
        {
            NinjinsPvPPvE.LogWarning("[ExpansionMapMenu] ERROR: drawCanvas not found in layout.");
            return layoutRoot;
        }
        m_MapDrawer = MapDrawer.GetInstance(m_MapWidget, m_DrawCanvas);
        if (!m_MapDrawer)
        {
            NinjinsPvPPvE.LogWarning("[ExpansionMapMenu] ERROR: Failed to initialize MapDrawer.");
        }
        return layoutRoot;
    }
    override void OnShow()
    {
        super.OnShow();
        float currentTime = GetGame().GetTickTime();
        float timeSinceLastRequest = currentTime - m_LastZoneRequestTime;
        if (timeSinceLastRequest > ZONE_REQUEST_COOLDOWN)
        {
            GetRPCManager().SendRPC("NinjinsPvPPvE", "RequestZones", NULL, true, null);
            m_LastZoneRequestTime = currentTime;
        }     
        if (!m_MapDrawer)
            return;
        MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
        if (!mission)
            return;
        array<ref ZoneBase> zones = mission.GetCachedZones();
        if (zones && zones.Count() > 0)
        {
            bool drawLabels = g_MainConfig && g_MainConfig.DrawNamesOnZones;
            m_MapDrawer.UpdateZones(zones, drawLabels);
        }
    }
    override void Update(float timeslice)
    {
        super.Update(timeslice);      
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
