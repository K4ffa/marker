#ifdef LBmaster_Groups
modded class LBGroupUI
{
    private ref MapDrawer m_MapDrawer;
    private CanvasWidget  m_DrawCanvas;
    private MapWidget     m_MapWidget;
    private float         m_LastZoneRequestTime = 0;
    private const float   ZONE_REQUEST_COOLDOWN = 10.0;
    override void OnShow()
    {
        super.OnShow();
        InitializeMapDrawer();
        RequestZonesFromServer();
    }
    private void InitializeMapDrawer()
    {
        MapWidget currentMap = MapWidget.Cast(layoutRoot.FindAnyWidget("Map"));
        if (!currentMap) 
            return;
        CanvasWidget oldCanvas = CanvasWidget.Cast(currentMap.FindAnyWidget("ninjindrawCanvas"));
        if (oldCanvas)
        {
            oldCanvas.Unlink();
            oldCanvas = null;
        }
        if (!m_MapDrawer || m_MapDrawer.GetMapWidget() != currentMap)
        {
            MapDrawer.ResetInstance(m_MapWidget);
            m_MapWidget = currentMap;
            Widget canvasLayout = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/NinjinsMapCanvasOnly.layout", m_MapWidget);
            if (!canvasLayout) 
                return;
            m_DrawCanvas = CanvasWidget.Cast(canvasLayout.FindAnyWidget("ninjindrawCanvas"));
            if (!m_DrawCanvas) 
                return;
            m_MapDrawer = MapDrawer.GetInstance(m_MapWidget, m_DrawCanvas);
        }
    }
    private void RequestZonesFromServer()
    {
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
    override void OnHide()
    {
        super.OnHide();
        MapDrawer.ResetInstance(m_MapWidget);
        m_MapDrawer  = null;
        m_DrawCanvas = null;
    }
    override void Update(float timeslice)
    {
        super.Update(timeslice);
        if (m_MapDrawer && m_MapDrawer.HasValidWidget())
        {          
            m_MapDrawer.TriggerUpdate();
        }
    }
}
#endif
