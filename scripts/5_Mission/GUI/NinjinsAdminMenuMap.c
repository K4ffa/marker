class NinjinsAdminMenuMap
{
	private MapWidget m_MapWidget;
	private CanvasWidget m_DrawCanvas;
	private ref MapDrawer m_MapDrawer;
	void NinjinsAdminMenuMap(MapWidget mapWidget)
	{
		m_MapWidget = mapWidget;
		InitializeMapDrawer();
	}
	private void InitializeMapDrawer()
	{
		if (!m_MapWidget)
		{
			NinjinsPvPPvE.LogWarning("[NinjinsAdminMenuMap] ERROR: MapWidget is NULL!");
			return;
		}
		if (!m_DrawCanvas)
		{
			Widget canvasLayout = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/NinjinsMapCanvasOnly.layout", m_MapWidget);
			if (!canvasLayout)
			{
				NinjinsPvPPvE.LogWarning("[NinjinsAdminMenuMap] ERROR: Failed to load canvas-only layout.");
				return;
			}
			m_DrawCanvas = CanvasWidget.Cast(canvasLayout.FindAnyWidget("ninjindrawCanvas"));
			if (!m_DrawCanvas)
			{
				NinjinsPvPPvE.LogWarning("[NinjinsAdminMenuMap] ERROR: drawCanvas not found in layout.");
				return;
			}
		}
		if (!m_MapDrawer)
		{
			m_MapDrawer = MapDrawer.GetInstance(m_MapWidget, m_DrawCanvas);
			if (!m_MapDrawer)
			{
				NinjinsPvPPvE.LogWarning("[NinjinsAdminMenuMap] ERROR: Failed to initialize MapDrawer.");
			}
		}
	}
	void UpdateZones()
	{
		if (!m_MapDrawer) 
			return;
		MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
		if (!mission || !mission.GetCachedZones()) 
			return;
		bool drawLabels = g_MainConfig && g_MainConfig.DrawNamesOnZones;
		m_MapDrawer.UpdateZones(mission.GetCachedZones(), drawLabels);
		NinjinsPvPPvE.LogDebug("[NinjinsAdminMenuMap] Zones updated on map.");
	}
	void JumpToPosition(vector worldPos)
	{
		if (!m_MapWidget) 
			return;
		float mapX = worldPos[0];
		float mapZ = worldPos[2];
		m_MapWidget.SetMapPos(Vector(mapX, 0, mapZ));
		NinjinsPvPPvE.LogDebug("[NinjinsAdminMenuMap] Jumped to map position: " + worldPos.ToString());
	}
	void OnOpen()
	{
		InitializeMapDrawer();
		if (!m_MapDrawer)
			return;	
		Param2<bool, bool> params = new Param2<bool, bool>(false, true);
		GetRPCManager().SendRPC("NinjinsPvPPvE", "RequestZones", params, true, null);

		m_MapDrawer.ClearMap();
		UpdateZones();
	}
	void OnClose()
	{
		MapDrawer.ResetInstance(m_MapWidget);
	}
	void TriggerUpdate()
	{
		if (m_MapDrawer)
			m_MapDrawer.TriggerUpdate();
	}
}
