class NinjinMapWrapper 
{
    protected vector position;
    protected vector lastPosition;
    protected int lastColor;
    protected bool changed = false;
    protected CanvasWidget drawCanvas;
    void SetDrawCanvas(CanvasWidget canvas) 
    {
        drawCanvas = canvas;
    }
    bool SetPosition(vector pos) 
    {
        if (vector.DistanceSq(lastPosition, pos) > 0.01) 
        {
            position = pos;
            lastPosition = pos;
            changed = true;
            return true;
        }
        return false;
    }
    bool SetColor(int color) 
    {
        if (lastColor != color) 
        {
            lastColor = color;
            changed = true;
            return true;
        }
        return false;
    }
    void Update(float mapScale, vector mapPos, MapWidget mapWidget, float xOffset, float yOffset)
    {
    }
    vector GetPosition() 
    {
        return position;
    }
    int GetColor() 
    {
        return lastColor;
    }
}