class ItemSearchMenu extends UIScriptedMenu
{
	private ref array<string> m_LastFilteredItems = new array<string>();
	private int m_LastSelectedIndex = -1;
	private string m_LastSearchText = "";
	private string m_LastSelectedItem = "";
	private Widget m_ActiveFilterButton = null;
	private Widget m_ItemSearchRoot;
	private Widget m_PanelItemSearchOnMap;
	private ScrollWidget m_ScrollItemSearchMap;
	private Widget m_ItemSearchPanelSettings;
	private Widget m_ItemSearchTitlePanel;
	private TextWidget m_ItemSearchTitle;
	private Widget m_MainItemSearch;
	private Widget m_Content;
	private TextListboxWidget m_ItemList;
	private EditBoxWidget m_SearchBox;
	private ButtonWidget m_SearchBtn;
	private MapWidget m_Map;
	private string m_SelectedItem;
	private ButtonWidget m_FoundItemsBtn;
	private ref array<string> m_AvailableItems;
	private ref array<string> m_FilteredItems;
	private TextListboxWidget m_FoundItemList;
	private ButtonWidget m_FoundItemsCopyBtn;
	private string m_CurrentFilterBaseClass = "";
	private ButtonWidget m_FilterVehiclesBtn;
	private ButtonWidget m_FilterWeaponsBtn;
	private ButtonWidget m_FilterMagazinesBtn;
	private ButtonWidget m_FilterItemsBtn;
	private ButtonWidget m_FilterAllBtn;
	private ButtonWidget m_FilterFoodBtn;
	private ButtonWidget m_FilterClothingBtn;
	private ButtonWidget m_FilterAIButton;
	private ButtonWidget m_FilterExpansionAIBtn;
	private ButtonWidget m_ClearMapBtn;
	private ButtonWidget m_ResetSearchBoxBtn;
	private bool m_FilterByPrefixOnly = false;
	private string m_PrefixFilter = "";
	private ref map<Widget, string> m_FilterButtonMap = new map<Widget, string>();
	private ref map<int, vector> m_FoundItemPositions = new map<int, vector>();
	private ref map<string, vector> m_LastFoundItems = new map<string, vector>();
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/ItemSearchPanel.layout");
		if (!layoutRoot)
		{
			Print("[ItemSearchMenu] Failed to load layout!");
			return null;
		}
		m_Map                     = MapWidget.Cast(layoutRoot.FindAnyWidget("MapWidgetItemSearchDisplay"));
		m_ItemSearchRoot          = layoutRoot;
		m_PanelItemSearchOnMap    = layoutRoot.FindAnyWidget("ItemSearchOnMap");
		m_ScrollItemSearchMap     = ScrollWidget.Cast(layoutRoot.FindAnyWidget("scrollItemSearchMap"));
		m_ItemSearchPanelSettings = layoutRoot.FindAnyWidget("ItemSearchPanelSettings0");
		m_ItemSearchTitlePanel    = layoutRoot.FindAnyWidget("ItemSearchTitlePanel0");
		m_ItemSearchTitle         = TextWidget.Cast(layoutRoot.FindAnyWidget("ItemSearchPanel0"));
		m_MainItemSearch          = layoutRoot.FindAnyWidget("MainItemSearch0");
		m_Content                 = layoutRoot.FindAnyWidget("content0");
		m_SearchBox               = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SearchBoxXMLNameSearch"));
		m_ItemList                = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ItemListBoxXML1"));
		m_SearchBtn               = ButtonWidget.Cast(layoutRoot.FindAnyWidget("SearchItemMapBtn"));
		m_FoundItemList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ItemListBoxXMLFound"));
		m_FoundItemsBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FoundItemsButton"));
		m_FoundItemsCopyBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FoundItemsButtonCopyCLipBoardCoords"));
		m_FilterVehiclesBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterVehiclesBtn"));
		m_FilterWeaponsBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterWeaponsBtn"));
		m_FilterAllBtn        = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterAllBtn"));
		m_FilterFoodBtn       = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterFoodBtn"));
		m_FilterClothingBtn   = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterClothingBtn"));
		m_FilterAIButton      = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterAIButton"));
		m_FilterItemsBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterItemsBtn"));
		m_FilterMagazinesBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterMagazinesBtn"));
		m_FilterExpansionAIBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("FilterExpansionAIBtn"));
		m_ClearMapBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ClearMapBtn"));
		m_ResetSearchBoxBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ResetSearchBoxXMLNameSearch"));
		m_FilterButtonMap.Insert(m_FilterExpansionAIBtn, "#EXPANSIONAI");
		m_FilterButtonMap.Insert(m_FilterAllBtn, "");
		m_FilterButtonMap.Insert(m_FilterFoodBtn, "edible_base");
		m_FilterButtonMap.Insert(m_FilterVehiclesBtn, "transport");
		m_FilterButtonMap.Insert(m_FilterWeaponsBtn, "weapon_base");
		m_FilterButtonMap.Insert(m_FilterMagazinesBtn, "Magazine_Base");
		m_FilterButtonMap.Insert(m_FilterClothingBtn, "clothing_base");
		m_FilterButtonMap.Insert(m_FilterItemsBtn, "inventory_base");
		m_FilterButtonMap.Insert(m_FilterAIButton, "dz_lightai");
		Widget canvasLayout = GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/NinjinsMapCanvasOnly.layout", m_Map);
		if (!canvasLayout)
		{
			Print("[ItemSearchMenu] ERROR: Failed to load canvas layout.");
			return layoutRoot;
		}
		CanvasWidget drawCanvas = CanvasWidget.Cast(canvasLayout.FindAnyWidget("ninjindrawCanvas"));
		if (!drawCanvas)
		{
			Print("[ItemSearchMenu] ERROR: drawCanvas not found.");
			return layoutRoot;
		}
		MapDrawer mapDrawer = MapDrawer.GetInstance(m_Map, drawCanvas);
		if (!mapDrawer)
		{
			Print("[ItemSearchMenu] ERROR: Failed to initialize MapDrawer.");
		}
		if (m_LastFoundItems && m_LastFoundItems.Count() > 0)
		{
			mapDrawer.DrawFoundItems(m_LastFoundItems, ARGB(255, 0, 255, 0));
			SetFoundItems(m_LastFoundItems);
		}
		if (m_LastSearchText != "" && m_SearchBox)
			m_SearchBox.SetText(m_LastSearchText);
		m_AvailableItems = GetAvailableItemsFromConfig();
		m_FilteredItems = new array<string>();
		ApplyFilter("");
		if (m_LastFilteredItems && m_LastFilteredItems.Count() > 0)
		{
			m_ItemList.ClearItems();
			foreach (string item : m_LastFilteredItems)
			{
				m_ItemList.AddItem(item, NULL, 0);
			}
			if (m_LastSelectedIndex > -1 && m_LastSelectedIndex < m_ItemList.GetNumItems())
			{
				m_ItemList.SelectRow(m_LastSelectedIndex);
			}
			m_ItemList.Update();
		}
		return layoutRoot;
	}
	void ApplyFilter(string filterText)
	{
		if (!m_ItemList) 
			return;
		filterText.ToLower();
		m_ItemList.ClearItems();
		TStringArray configPaths = { "CfgVehicles", "CfgWeapons", "CfgMagazines", "CfgItems" };
		TStringArray matchedItems = new TStringArray;
		foreach (string path : configPaths)
		{
			int count = GetGame().ConfigGetChildrenCount(path);
			for (int i = 0; i < count; i++)
			{
				string className;
				GetGame().ConfigGetChildName(path, i, className);
				string fullPath = path + " " + className + " scope";
				if (!GetGame().ConfigIsExisting(fullPath)) continue;
				int scope = GetGame().ConfigGetInt(fullPath);
				if (scope < 2) continue;
				bool skip = false;
				if (m_FilterByPrefixOnly)
				{
					if (className.IndexOf(m_PrefixFilter) != 0)
						skip = true;
				}
				else if (m_CurrentFilterBaseClass != "")
				{
					if (!GetGame().IsKindOf(className, m_CurrentFilterBaseClass))
						skip = true;
				}
				if (skip)
					continue;
				string lowerName = className;
				lowerName.ToLower();
				if (filterText == "" || lowerName.Contains(filterText))
				{
					matchedItems.Insert(className);
				}
			}
		}
		matchedItems.Sort();
		foreach (string item : matchedItems)
		{
			m_ItemList.AddItem(item, NULL, 0);
		}
		m_ItemList.Update();
	}
	private array<string> GetAvailableItemsFromConfig()
	{
		array<string> itemsList = {};
		TStringArray configPaths = { "CfgVehicles", "CfgWeapons", "CfgMagazines", "CfgItems" };
		foreach (string path : configPaths)
		{
			int count = GetGame().ConfigGetChildrenCount(path);
			for (int i = 0; i < count; i++)
			{
				string name;
				GetGame().ConfigGetChildName(path, i, name);
				string fullPath = path + " " + name + " scope";
				if (!GetGame().ConfigIsExisting(fullPath)) continue;
				int scope = GetGame().ConfigGetInt(fullPath);
				if (scope < 2) continue;
				if (m_CurrentFilterBaseClass != "" && !GetGame().IsKindOf(name, m_CurrentFilterBaseClass)) continue;
				itemsList.Insert(name);
			}
		}
		return itemsList;
	}
	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		if (button != MouseState.LEFT)
			return super.OnDoubleClick(w, x, y, button);
		if (w == m_Map)
		{
			vector mapPos = m_Map.ScreenToMap(Vector(x, y, 0));
			mapPos[1] = GetGame().SurfaceY(mapPos[0], mapPos[2]);
			TeleportToWorldPosition(mapPos);
			return true;
		}
		if (w == m_FoundItemList)
		{
			int selectedRow = m_FoundItemList.GetSelectedRow();
			if (selectedRow > -1 && m_FoundItemPositions.Contains(selectedRow))
			{
				vector pos = m_FoundItemPositions.Get(selectedRow);
				TeleportToWorldPosition(pos);
				return true;
			}
		}
		return super.OnDoubleClick(w, x, y, button);
	}
	void TeleportToWorldPosition(vector pos)
	{
		if (!pos) 
			return;
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !player.GetIdentity()) 
			return;
		Param3<float, float, float> p = new Param3<float, float, float>(pos[0], pos[1], pos[2]);
		GetRPCManager().SendRPC("NinjinsPvPPvE", "TeleportPlayer", p, true, player.GetIdentity());
	}
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (w == m_SearchBtn)
		{
			ClearMapCanvasAndMarkers();
			if (m_FoundItemList) m_FoundItemList.ClearItems();
			if (m_FoundItemPositions) m_FoundItemPositions.Clear();
			string itemName;
			if (m_ItemList.GetSelectedRow() > -1)
				m_ItemList.GetItemText(m_ItemList.GetSelectedRow(), 0, itemName);
			else
				itemName = m_SearchBox.GetText();
			m_LastSearchText = itemName;
			if (itemName != "")
			{
				GetRPCManager().SendRPC("NinjinsPvPPvE", "ScanItemsOnMap", new Param1<string>(itemName), true);
			}
			if (m_FoundItemsBtn)
				m_FoundItemsBtn.SetText("Found Items: 0");
			return true;
		}
		if (w == m_FoundItemList)
		{
			int selectedRow = m_FoundItemList.GetSelectedRow();
			if (selectedRow > -1 && m_FoundItemPositions.Contains(selectedRow))
			{
				vector pos = m_FoundItemPositions.Get(selectedRow);
				vector flatPos = Vector(pos[0], 0, pos[2]);
				m_Map.SetMapPos(flatPos);
				m_Map.SetScale(0.2);
				return true;
			}
		}
		if (w == m_FoundItemsCopyBtn)
		{
			if (!m_FoundItemList || !m_FoundItemPositions || m_FoundItemPositions.Count() == 0)
				return true;
			string output;
			for (int i = 0; i < m_FoundItemList.GetNumItems(); i++)
			{
				string label;
				m_FoundItemList.GetItemText(i, 0, label);
				vector itemPos = m_FoundItemPositions.Get(i);
				output += label + "\n";
				output += "Pos: " + itemPos[0].ToString() + ", " + itemPos[1].ToString() + ", " + itemPos[2].ToString() + "\n";
			}
			GetGame().CopyToClipboard(output);
			return true;
		}
		if (m_FilterButtonMap.Contains(w))
		{
			string baseClass = m_FilterButtonMap.Get(w);
			if (baseClass == "#EXPANSIONAI")
			{
				m_FilterByPrefixOnly = true;
				m_PrefixFilter = "eAI_";
				m_CurrentFilterBaseClass = "";
			}
			else
			{
				m_FilterByPrefixOnly = false;
				m_PrefixFilter = "";
				m_CurrentFilterBaseClass = baseClass;
			}
			m_AvailableItems = GetAvailableItemsFromConfig();
			ApplyFilter(m_SearchBox.GetText());
			m_ActiveFilterButton = w;
			HighlightActiveFilterButton(m_ActiveFilterButton);
			return true;
		}
		if (w == m_ClearMapBtn)
		{
			ClearMapCanvasAndMarkers();
			if (m_FoundItemList)
				m_FoundItemList.ClearItems();
			if (m_FoundItemPositions)
				m_FoundItemPositions.Clear();
			if (m_FoundItemsBtn)
				m_FoundItemsBtn.SetText("");
			m_LastFoundItems.Clear();
			return true;
		}
		if (w == m_ResetSearchBoxBtn)
		{
			if (m_SearchBox)
				m_SearchBox.SetText("");
			ApplyFilter("");
			return true;
		}
		return super.OnClick(w, x, y, button);
	}
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		if (w == m_SearchBox)
		{
			string searchText = m_SearchBox.GetText();
			m_LastSearchText = searchText; 
			ApplyFilter(searchText);
			return true;
		}
		return super.OnChange(w, x, y, finished);
	}
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		if (!m_Map)
			return;
		MapDrawer mapDrawer = MapDrawer.GetInstance(m_Map, CanvasWidget.Cast(m_Map.FindAnyWidget("ninjindrawCanvas")));
		if (mapDrawer)
			mapDrawer.TriggerUpdate();
	}
	MapWidget GetItemSearchMap()
	{
		return m_Map;
	}
	void SetFoundItems(map<string, vector> results)
	{
		if (!m_FoundItemList || !results) 
			return;
		m_LastFoundItems = results;
		m_LastSearchText = m_SearchBox.GetText();
		m_FoundItemList.ClearItems();
		m_FoundItemPositions.Clear();
		int index = 0;
		foreach (string key, vector pos : results)
		{
			string display = string.Format("[%1] %2", (index + 1).ToString(), key);
			m_FoundItemList.AddItem(display, NULL, 0);
			m_FoundItemPositions.Insert(index, pos);
			index++;
		}
		if (m_FoundItemsBtn)
			m_FoundItemsBtn.SetText("Found Items: " + results.Count().ToString());
		m_FoundItemList.Update();	
		CanvasWidget canvas = CanvasWidget.Cast(m_Map.FindAnyWidget("ninjindrawCanvas"));
		MapDrawer mapDrawer = MapDrawer.GetInstance(m_Map, canvas);
		if (mapDrawer)
		{
			mapDrawer.DrawFoundItems(m_LastFoundItems, ARGB(255, 0, 255, 0));
		}
	}
	void ClearMapCanvasAndMarkers()
	{
		if (!m_Map)
			return;
		CanvasWidget canvas = CanvasWidget.Cast(m_Map.FindAnyWidget("ninjindrawCanvas"));
		MapDrawer mapDrawer = MapDrawer.GetInstance(m_Map, canvas);
		if (mapDrawer)
			mapDrawer.ClearMap();
		m_Map.ClearUserMarks();
	}
	override void OnShow()
	{
		super.OnShow();
		SetFocus(layoutRoot);
		TIntArray skip = { UAUIBack, UAItemSearchMenu };
		ForceDisableInputs(true, skip);
		PPEffects.SetBlurMenu(0.5);
		GetGame().GetInput().ChangeGameFocus(1);
		GetGame().GetUIManager().ShowUICursor(true);
		GetGame().GetMission().GetHud().Show(false);
	}
	override void OnHide()
	{
		super.OnHide();	
		m_LastFilteredItems.Clear();
		for (int i = 0; i < m_ItemList.GetNumItems(); i++)
		{
			string itemName;
			m_ItemList.GetItemText(i, 0, itemName);
			m_LastFilteredItems.Insert(itemName);
		}
		m_LastSelectedIndex = m_ItemList.GetSelectedRow();
		ForceDisableInputs(false);
		PPEffects.SetBlurMenu(0);
		GetGame().GetInput().ResetGameFocus();
		GetGame().GetUIManager().ShowUICursor(false);
		GetGame().GetMission().GetHud().Show(true);
	}
	void HighlightActiveFilterButton(Widget activeButton)
	{
		foreach (Widget btn, string filter : m_FilterButtonMap)
		{
			if (btn)
			{
				if (btn == activeButton)
				{
					btn.SetColor(ARGB(255, 50, 150, 250));
				}
				else
				{
					btn.SetColor(ARGB(255, 200, 200, 200));
				}
			}
		}
	}
	static void ForceDisableInputs(bool state, inout TIntArray skipIDs = null)
    {
        if (!skipIDs)
            skipIDs = new TIntArray;
        skipIDs.Insert(UAUIBack);
        skipIDs.Insert(UAItemSearchMenu);
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
};
