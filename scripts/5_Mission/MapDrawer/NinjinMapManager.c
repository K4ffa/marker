class NinjinMapManager {
    private MapWidget mapWidget;
    private CanvasWidget drawCanvas;
    private ref array<ref NinjinMapWrapper> markers = new array<ref NinjinMapWrapper>();
    private ref array<ref NinjinsCircle> circles = new array<ref NinjinsCircle>();
    private float lastMapScale;
    private vector lastMapPos;
    private float xOffset, yOffset;
    void NinjinMapManager(MapWidget mapW) 
    {
        mapWidget = mapW;
        drawCanvas = CanvasWidget.Cast(mapWidget.FindAnyWidget("ninjindrawCanvas"));
        mapWidget.GetScreenPos(xOffset, yOffset);
    }
    void UpdateOffsets() 
    {
        mapWidget.GetScreenPos(xOffset, yOffset);
    }
    NinjinsCircle AddCircle(vector pos, float radius, int color,bool drawStrike = false,bool hideWhenNested = true,int  priority = 1)
    {
        NinjinsCircle circle = new NinjinsCircle();
        circle.SetDrawCanvas(drawCanvas);
        circle.Init(pos, radius, color, priority);
        circle.SetDrawStrike(drawStrike);
        circle.SetHideWhenNested(hideWhenNested);
        markers.Insert(circle);
        circles.Insert(circle);
        return circle;
    }
    void AddPolygon(array<vector> verts, int color, bool drawStrike = false, bool hideWhenNested = true, int priority = 1) 
    {
        NinjinPolygon poly = new NinjinPolygon();
        poly.SetDrawCanvas(drawCanvas);
        poly.Init(verts, color);
        poly.SetDrawStrike(drawStrike);
        markers.Insert(poly);
    }
    void Update() 
    {
        if (!mapWidget || !drawCanvas)
            return;
        float scale = mapWidget.GetScale();
        vector pos = mapWidget.GetMapPos();
        UpdateOffsets();
        drawCanvas.Clear();
        foreach (NinjinsCircle c : circles) 
        {
            c.CirclesOthers(circles);
        }
        foreach (NinjinMapWrapper marker : markers) 
        {
            marker.Update(scale, pos, mapWidget, xOffset, yOffset);
        }
        lastMapScale = scale;
        lastMapPos = pos;
    }
    void ClearMarkers() 
    {
        if (drawCanvas) 
        {
            drawCanvas.Clear();
        }
        markers.Clear();
        circles.Clear();
    }
    bool HasMarkers() 
    {
        return markers && markers.Count() > 0;
    }
    void DrawZoneLabel(vector worldPos, string labelText, int color) 
    {
        if (!mapWidget || labelText == "") 
            return;
        mapWidget.AddUserMark(worldPos, labelText, color, "\\dz\\gear\\navigation\\data\\map_bush_ca.paa");
    }
}