class NinjinClientZoneSettings
{
	bool showPvP = true;
	bool showPvE = true;
	bool showRaid = true;
	bool showSafeZone = true;
	bool showPaintball = true;
	bool showVisual = true;
	bool showZoneLabels = true;
	bool showNoBuildRadius = true;
	bool drawMiniMapZones   = true;
    bool drawMiniMapLabels  = true;
	float iconPosX = -1;
	float iconPosY = -1;
	float iconWidth = -1;
	float iconHeight = -1;
	static const string SETTINGS_PATH = "$profile:NinjinsPvPPvE\\ClientZoneSettings.json";
	void NinjinClientZoneSettings(){}
	void Load()
	{
		JsonFileLoader<NinjinClientZoneSettings>.JsonLoadFile(SETTINGS_PATH, this);		
		bool needsSave = false;
		if (!IsFieldDefined("drawMiniMapZones"))  
		{ 
			drawMiniMapZones  = true; 
			needsSave = true; 
		}
        if (!IsFieldDefined("drawMiniMapLabels")) 
		{ 
			drawMiniMapLabels = true;
			needsSave = true; 
		}
		if (!FileExist(SETTINGS_PATH))
		{
			Print("[ClientZoneSettings] Load failed. File does not exist.");
			return;
		}
		if (!IsFieldDefined("iconWidth"))
		{
			iconWidth = -1;
			needsSave = true;		
		}
		if (!IsFieldDefined("iconHeight"))
		{
			iconHeight = -1;
			needsSave = true;
		}
		if (!IsFieldDefined("iconPosX"))
		{
			iconPosX = -1;
			needsSave = true;
		}
		if (!IsFieldDefined("iconPosY"))
		{
			iconPosY = -1;
			needsSave = true;
		}
		if (!IsFieldDefined("showZoneLabels")) 
		{
			showZoneLabels = true;
			needsSave = true;
		}
		if (!IsFieldDefined("showSafeZone")) 
		{
			showSafeZone = true;
			needsSave = true;
		}
		if (!IsFieldDefined("showPaintball")) 
		{
			showPaintball = true;
			needsSave = true;
		}
		if (!IsFieldDefined("showVisual")) 
		{
			showVisual = true;
			needsSave = true;
		}
		if (!IsFieldDefined("showNoBuildRadius")) 
		{
			showNoBuildRadius = true;
			needsSave = true;		
		}
		if (needsSave) 
		{
			Save();
		}
	}
	void Save()
	{
		JsonFileLoader<NinjinClientZoneSettings>.JsonSaveFile(SETTINGS_PATH, this);
		if (FileExist(SETTINGS_PATH))
		{
			Print("[ClientZoneSettings] Save successful. File exists at: " + SETTINGS_PATH);
		}
		else
		{
			Print("[ClientZoneSettings] Save failed. File not found at: " + SETTINGS_PATH);
		}
	}
	static ref NinjinClientZoneSettings Init()
	{	
		NinjinClientZoneSettings settings = new NinjinClientZoneSettings();
		if (!FileExist(SETTINGS_PATH))
		{
			Print("[ClientZoneSettings] Config file missing. Creating default...");
			settings.Save();
		}
		else
		{
			settings.Load();
		}
		return settings;
	}
	bool IsFieldDefined(string fieldName)
	{
		FileHandle handle = OpenFile(SETTINGS_PATH, FileMode.READ);
		if (!handle) 
			return false;
		string line;
		string search = "\"" + fieldName + "\"";
		while (FGets(handle, line) > 0)
		{
			if (line.Contains(search))
			{
				CloseFile(handle);
				return true;
			}
		}
		CloseFile(handle);
		return false;
	}
}
