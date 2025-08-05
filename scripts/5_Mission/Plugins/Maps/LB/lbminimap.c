#ifdef LBmaster_Groups
modded class LB_GPSHud
{
    private ref MapDrawer m_ZoneDrawer;
    private CanvasWidget  m_ZoneCanvas;
    private bool          m_ZonesLoaded;
    private float         m_LastZoneRequestTime = 0;
    private const float   ZONE_REQUEST_COOLDOWN = 10.0;
    override void Init()
    {
        super.Init();
        CreateDrawer();                   
        RequestZones();                   
    }
    override void Show(bool show)
    {
        super.Show(show);
        if (show)
        {
            if (!m_ZoneDrawer || !m_ZoneDrawer.HasValidWidget())
                CreateDrawer();
            if (!m_ZonesLoaded)
                RequestZones();
        }
        else
        {
            if (m_ZoneDrawer)
            {
                MapDrawer.ResetInstance(mapWidget);
                m_ZoneDrawer  = null;
                m_ZoneCanvas  = null;
                m_ZonesLoaded = false;
            }
        }
    }
    override void UpdateHud(float timeslice)
    {
        super.UpdateHud(timeslice);
/*         NinjinClientZoneSettings settings = new NinjinClientZoneSettings();
        settings.Load();
        if (!settings.drawMiniMapZones)
            return; */
        if (m_ZoneDrawer && m_ZoneDrawer.HasValidWidget())
            m_ZoneDrawer.TriggerUpdate();
    }
    private void CreateDrawer()
    {
        if (!mapWidget)
            return;
        CanvasWidget old = CanvasWidget.Cast(mapWidget.FindAnyWidget("ninjindrawCanvas"));
        if (old) old.Unlink();
        MapDrawer.ResetInstance(mapWidget);
        Widget lay = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/NinjinsMapCanvasOnly.layout",mapWidget);
        if (!lay) 
            return;
        m_ZoneCanvas = CanvasWidget.Cast(lay.FindAnyWidget("ninjindrawCanvas"));
        if (!m_ZoneCanvas) 
            return;
        m_ZoneDrawer = MapDrawer.GetInstance(mapWidget, m_ZoneCanvas);
    }
    private void RequestZones()
    {
        float currentTime = GetGame().GetTickTime();
        float timeSinceLastRequest = currentTime - m_LastZoneRequestTime;
        if (timeSinceLastRequest > ZONE_REQUEST_COOLDOWN)
        {
            GetRPCManager().SendRPC("NinjinsPvPPvE", "RequestZones", NULL, true, null);
            m_LastZoneRequestTime = currentTime;
        }
        if (!m_ZoneDrawer)
            return;
        NinjinClientZoneSettings clientSettings = new NinjinClientZoneSettings();
        clientSettings.Load();
        if (!clientSettings.drawMiniMapZones)
        {
            m_ZoneDrawer.ClearMap();
            return;
        }
        MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
        if (!mission)
            return;
        array<ref ZoneBase> zones = mission.GetCachedZones();
        if (zones && zones.Count() > 0)
        {
            bool drawLabels = g_MainConfig && g_MainConfig.LB_MiniMapDrawNames && clientSettings.drawMiniMapLabels;
            m_ZoneDrawer.UpdateZones(zones, drawLabels, false);
            m_ZonesLoaded = true;
        }
    }
    void ~LB_GPSHud()
    {
        if (mapWidget)
            MapDrawer.ResetInstance(mapWidget);
    }
}
#endif