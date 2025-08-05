class MapDrawer {
	private MapWidget m_MapWidget;
	private CanvasWidget m_DrawCanvas;
	private ref NinjinClientZoneSettings m_ClientZoneSettings;
	private ref NinjinMapManager m_MarkerManager;
	private static ref map<int, ref MapDrawer> s_Instances = new map<int, ref MapDrawer>();
	private ref array<ref ZoneLabelWrapper> m_ZoneLabels = new array<ref ZoneLabelWrapper>();
	void MapDrawer(MapWidget mapWidget, CanvasWidget canvas) 
	{
		NinjinUtils.UpdateScreenSize();
		m_ClientZoneSettings = new NinjinClientZoneSettings();
		m_ClientZoneSettings.Load();
		m_MapWidget = mapWidget;
		m_DrawCanvas = canvas;
		if (!m_MapWidget || !m_DrawCanvas) 
		{
			NinjinsPvPPvE.LogWarning("[MapDrawer] ERROR: mapWidget or drawCanvas is NULL!");
			return;
		}
		m_MarkerManager = new NinjinMapManager(m_MapWidget);
	}
	static MapDrawer GetInstance(MapWidget mapWidget, CanvasWidget canvas) 
	{
		if (!mapWidget || !canvas)
			return null;
		int key = mapWidget.ToString().Hash();
		if (!s_Instances.Contains(key)) 
		{
			s_Instances[key] = new MapDrawer(mapWidget, canvas);
		}
		return s_Instances[key];
	}
	static void ResetInstance(MapWidget mapWidget = null) 
	{
		if (mapWidget) 
		{
			int key = mapWidget.ToString().Hash();
			if (s_Instances.Contains(key)) 
			{
				s_Instances[key].ClearMap();
				s_Instances.Remove(key);
			}
		} 
		else 
		{
			foreach (int id, MapDrawer drawer : s_Instances) 
			{
				drawer.ClearMap();
			}
			s_Instances.Clear();
		}
	}
	MapWidget GetMapWidget()
	{
		return m_MapWidget;
	}
	bool HasValidWidget()
	{
		return m_MapWidget && m_MapWidget.IsVisible();
	}
	CanvasWidget GetDrawCanvas()
	{
		return m_DrawCanvas;
	}
	void UpdateZones(array<ref ZoneBase> newZones, bool drawLabels = false, bool forceDraw = false)
	{
		if (!m_DrawCanvas || !m_MarkerManager || !m_MapWidget)
			return;	
		m_MarkerManager.ClearMarkers();
		m_DrawCanvas.Clear();
		m_MapWidget.ClearUserMarks();
		ClearZoneLabels();
		foreach (ZoneBase zone : newZones)
		{
			if (!zone)
				continue;
			if (zone.Hide)
				continue;
			if (!zone.IsActive())
				continue;
			if (zone.name.IndexOf("FlagPvPZone_") == 0 && !zone.drawShape && !forceDraw)
				continue;
			bool drawZoneShape = false;
			if (zone.drawShape || forceDraw)
				drawZoneShape = true;
			bool drawNoBuild = false;
			if (zone.noBuildRadius != -1 && zone.DrawNoBuildShape && g_MainConfig.DrawNoBuildRadius && m_ClientZoneSettings && m_ClientZoneSettings.showNoBuildRadius)
				drawNoBuild = true;
			if (!drawZoneShape && !drawNoBuild)
				continue;
			switch (zone.type)
			{
				case ZONE_TYPE_PVP:
					if (!m_ClientZoneSettings || !m_ClientZoneSettings.showPvP) 
					continue;
					break;
				case ZONE_TYPE_PVE:
					if (!m_ClientZoneSettings || !m_ClientZoneSettings.showPvE) 
					continue;
					break;
				case ZONE_TYPE_RAID:
					if (!m_ClientZoneSettings || !m_ClientZoneSettings.showRaid) 
					continue;
					break;
				case ZONE_TYPE_SAFEZONE:
					if (!m_ClientZoneSettings || !m_ClientZoneSettings.showSafeZone) 
					continue;
					break;
				case ZONE_TYPE_PAINTBALL:
					if (!m_ClientZoneSettings || !m_ClientZoneSettings.showPaintball) 
					continue;
					break;
				case ZONE_TYPE_VISUAL:
					if (!m_ClientZoneSettings || !m_ClientZoneSettings.showVisual) 
					continue;
					break;
			}
			int zoneColor = zone.GetColor();
			int labelColor = zone.ZoneLabelColor;
			if (labelColor == 0)
			{
				labelColor = zoneColor;
			}
			string label = GetShortZoneName(zone.name, zone.displayName);
			switch (zone.shape)
			{
				case ZoneShape.CIRCLE:
				{
					if (drawNoBuild)
					{
						float nbRadius = zone.radius + zone.noBuildRadius;
						int nbColor = g_MainConfig.noBuildZoneColor;
						if (nbColor == 0)
						{
							nbColor = ARGB(255, 0, 170, 255);
						}
						bool drawLine = g_MainConfig.drawStrikeLinesForNB;
						m_MarkerManager.AddCircle(zone.center, nbRadius, nbColor, drawLine, false, zone.priority - 1);
					}
					bool isNested = false;
					if (zone.HideWhenNested) 
					{
						foreach (ZoneBase otherZone : newZones) 
						{
							if (otherZone == zone)
								continue;
							//inside Circle
							if (otherZone.priority >= zone.priority && otherZone.shape == ZoneShape.CIRCLE) 
							{
								float dist = vector.Distance(Vector(zone.center[0], 0, zone.center[2]), Vector(otherZone.center[0], 0, otherZone.center[2]));
								if (dist + zone.radius <= otherZone.radius) 
								{
									isNested = true;
									break;
								}
							}
							//inside Polygon
							if (otherZone.priority >= zone.priority && otherZone.shape == ZoneShape.POLYGON && otherZone.vertices && otherZone.vertices.Count() >= 3) 
							{
								bool allPointsInside = true;
								int checkSteps = 8;
								float angleStep = Math.PI2 / checkSteps;
								for (int i = 0; i < checkSteps; i++) 
								{
									float angle = angleStep * i;
									vector point = zone.center + Vector(Math.Cos(angle) * zone.radius, 0, Math.Sin(angle) * zone.radius);
									if (!otherZone.IsInside(point)) 
									{
										allPointsInside = false;
										break;
									}
								}
								if (allPointsInside) 
								{
									isNested = true;
									break;
								}
							}
						}
					}
					if ((drawZoneShape && !isNested) || forceDraw)
					{
						m_MarkerManager.AddCircle(zone.center, zone.radius, zoneColor, zone.drawStrikeZone, zone.Hide, zone.priority);
					}
					if (drawLabels && m_ClientZoneSettings && m_ClientZoneSettings.showZoneLabels)
					{
						if (!isNested || forceDraw || !zone.HideWhenNested)
						{
							DrawTextAtMapPosition(zone.center, label, labelColor, zone);
						}
					}
					break;
				}
				case ZoneShape.POLYGON:
				{
					if (drawZoneShape && zone.vertices && zone.vertices.Count() >= 2)
					{
						m_MarkerManager.AddPolygon(zone.vertices, zoneColor, zone.drawStrikeZone, zone.Hide, zone.priority);
					}
					if (drawLabels && m_ClientZoneSettings && m_ClientZoneSettings.showZoneLabels)
					{
						if (!zone.HideWhenNested)
						{
							vector labelPosPoly = zone.center;
							if (labelPosPoly[0] == 0 && labelPosPoly[1] == 0 && labelPosPoly[2] == 0 && zone.vertices && zone.vertices.Count() >= 2)
							{
								labelPosPoly = CalcPolygonCentroid(zone.vertices);
							}
							DrawTextAtMapPosition(labelPosPoly, label, labelColor, zone);
						}
					}
					break;
				}
			}
		}
		m_MarkerManager.Update();
	}
	private vector CalcPolygonCentroid(array<vector> verts) 
	{
		float cx, cy, cz;
		foreach (vector v : verts) 
		{
			cx += v[0];
			cy += v[1];
			cz += v[2];
		}
		return Vector(cx / verts.Count(), cy / verts.Count(), cz / verts.Count());
	}
	void TriggerUpdate()
	{
		if (!m_MapWidget || !m_MarkerManager)
			return;
		m_MarkerManager.UpdateOffsets();
		m_MarkerManager.Update();
		foreach (ZoneLabelWrapper label : m_ZoneLabels)
		{
			if (label)
				label.UpdatePosition(m_MapWidget);
		}
	}
	void HideZoneLabels()
	{
		foreach (ZoneLabelWrapper label : m_ZoneLabels)
		{
			if (label && label.widget)
			{
				label.widget.Show(false);
			}
		}
	}
	void UpdateOffsets() 
	{
		if (m_MarkerManager)
			m_MarkerManager.UpdateOffsets();
	}
	void ClearMap()
	{
		if (m_DrawCanvas)
		{
			m_DrawCanvas.Clear();
			m_DrawCanvas.Unlink();
			m_DrawCanvas = null;
		}
		if (m_MarkerManager)
			m_MarkerManager.ClearMarkers();
		ClearZoneLabels();
	}
	void ClearZoneLabels()
	{
		foreach (ZoneLabelWrapper label : m_ZoneLabels)
		{
			if (label)
				label.Destroy();
		}
		m_ZoneLabels.Clear();
	}
	void DrawTextAtMapPosition(vector worldPos, string label, int color, ZoneBase zone = null, float offsetYPixels = 0)
	{
		if (!m_MapWidget || !m_DrawCanvas || label == "")
			return;
		vector offsetMeters = "0 0 0";
		if (zone) 
		{
			offsetMeters = Vector(zone.ZonelabelOffsetX_Meters, 0, zone.ZonelabelOffsetZ_Meters);
		}
		ZoneLabelWrapper labelWrapper = new ZoneLabelWrapper(m_DrawCanvas, worldPos, label, color, offsetMeters, offsetYPixels);
		m_ZoneLabels.Insert(labelWrapper);
	}
	string GetShortZoneName(string zoneName, string zoneDisplayName) 
	{
		if (zoneName.IndexOf("AIMission_") == 0)
			return "AI Mission";
		if (zoneDisplayName && zoneDisplayName != "")
			return zoneDisplayName;
		if (zoneName.IndexOf("Mi8Zone_") == 0) return "Mi8";
		if (zoneName.IndexOf("UH1YZone_") == 0) return "UH1Y";
		if (zoneName.IndexOf("DynamicPvPZone_Lockpick_") == 0) return "LockPick Zone";
		if (zoneName.IndexOf("FlagPvPZone_") == 0) return "Flag Zone";
		if (zoneName.IndexOf("AirdropZone_") == 0) return "Airdrop Zone";
		if (zoneName.IndexOf("OldMi8Zone_") == 0) return "Event Zone";
		if (zoneName.IndexOf("DynamicPvPZone_ATMRobbery_") == 0) return "ATM Robbery Zone";
		return zoneName;
	}
	void DrawFoundItems(map<string, vector> items, int color)
	{
		if (!m_MarkerManager)
		{
			Print("[MapDrawer] ERROR: MarkerManager is null.");
			return;
		}
		if (!items || items.Count() == 0)
		{
			return;
		}
		foreach (string label, vector pos : items)
		{
			m_MarkerManager.AddCircle(pos, 5.0, color, false, false, 0);
			m_MarkerManager.DrawZoneLabel(pos, label, color);
		}
		m_MarkerManager.Update();
	}
}
