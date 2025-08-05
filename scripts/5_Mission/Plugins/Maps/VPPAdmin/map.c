#ifdef VPPADMINTOOLS
modded class MenuTeleportManager extends AdminHudSubMenu
{
    private ref MapDrawer m_ZoneDrawer;
    private CanvasWidget  m_ZoneCanvas;
    override void OnCreate(Widget RootW)
    {
        super.OnCreate(RootW);
        InitZoneDrawer(); 
        RequestZones();
    }
    override void OnMenuShow()
    {
        super.OnMenuShow();
        InitZoneDrawer();
        RequestZones();
    }
    override void OnMenuHide()
    {
        super.OnMenuHide();
        MapDrawer.ResetInstance(m_Map);
        m_ZoneDrawer = null;
        m_ZoneCanvas = null;
    }
    private void InitZoneDrawer()
    {
        if (!m_Map) 
            return;
        if (!g_MainConfig || !g_MainConfig.DrawZonesOnVPPAdmin) 
            return;
        CanvasWidget oldCanvas = CanvasWidget.Cast(m_Map.FindAnyWidget("ninjindrawCanvas"));
        if (oldCanvas) oldCanvas.Unlink();
        MapDrawer.ResetInstance(m_Map);
        Widget lay = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/NinjinsMapCanvasOnly.layout", m_Map);
        if (!lay) 
            return;
        m_ZoneCanvas = CanvasWidget.Cast(lay.FindAnyWidget("ninjindrawCanvas"));
        if (!m_ZoneCanvas) 
            return;
        m_ZoneDrawer = MapDrawer.GetInstance(m_Map, m_ZoneCanvas);
    }
    private void RequestZones()
    {
        GetRPCManager().SendRPC("NinjinsPvPPvE", "RequestZones", NULL, true, null);
        if (!g_MainConfig || !g_MainConfig.DrawZonesOnVPPAdmin) 
            return; 
        MissionGameplay m = MissionGameplay.Cast(GetGame().GetMission());
        if (!m || !m_ZoneDrawer) 
            return;
        array<ref ZoneBase> zones = m.GetCachedZones();
        bool drawLabels = g_MainConfig && g_MainConfig.DrawVPPAdminZoneLabels;
        m_ZoneDrawer.UpdateZones(zones, drawLabels, true); 
    }
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        if (m_ZoneDrawer && m_ZoneDrawer.HasValidWidget())
            m_ZoneDrawer.TriggerUpdate();
    }
}
#endif
