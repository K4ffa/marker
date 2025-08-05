class ZoneLabelWrapper 
{
    vector worldPos;
    string text;
    int color;
    TextWidget widget;
    float offsetY;
    float mapScale;
    vector mapPos;
    float xOffset;
    float yOffset;
    vector labelOffset;
    void ZoneLabelWrapper(CanvasWidget parentCanvas, vector pos, string label, int col, vector offsetMeters = "0 0 0", float offsetYPixels = 0) 
    {
        worldPos = pos;
        text = label;
        color = col;
        offsetY = offsetYPixels;
        labelOffset = offsetMeters;
        widget = TextWidget.Cast(GetGame().GetWorkspace().CreateWidgets("NinjinsPvPPvE/gui/layouts/ZoneLabel.layout", parentCanvas));
        if (widget) 
        {
            widget.SetText(text);
            widget.SetColor(color);
        }
    }
    void UpdatePosition(MapWidget mapWidget) 
    {
        if (!widget || !mapWidget)
            return;
        mapScale = mapWidget.GetScale();
        mapPos = mapWidget.GetMapPos();
        mapWidget.GetScreenPos(xOffset, yOffset);
        vector offsetWorldPos = worldPos + Vector(labelOffset[0], 0, labelOffset[2]);
        float screenHeight = NinjinUtils.screenHeight * 1.33333333;
        if (screenHeight > NinjinUtils.screenWidth)
            screenHeight = NinjinUtils.screenWidth;
        float screenScale = screenHeight / g_Game.GetWorld().GetWorldSize();
        float mapToScreen = mapScale / screenScale;
        vector screenPos = mapWidget.MapToScreen(offsetWorldPos);
        float finalX = screenPos[0] - xOffset;
        float finalY = screenPos[1] - yOffset - offsetY;
        int textHeight;
        int textWidth;
        widget.GetTextSize(textWidth, textHeight);
        float correctedY = finalY - (textHeight / 2);
        widget.SetPos(finalX, correctedY, true);
        widget.Show(true);
    }
    void Destroy() 
    {
        if (widget)
            widget.Unlink();
    }
}