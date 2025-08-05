class NinjinPolygon : NinjinMapWrapper 
{
    private ref array<vector> vertices;
    void Init(array<vector> verts, int color) 
    {
        if (!verts || verts.Count() < 2) 
            return;
        vertices = verts;
        SetColor(color);
        position = CalcPolygonCenter(verts);
        SetPosition(position);
        NinjinUtils.UpdateScreenSize();
    }
    bool m_DrawStrikeLines = false;
    void SetDrawStrike(bool enable) 
    {
        m_DrawStrikeLines = enable;
    }
    override void Update(float mapScale, vector mapPos, MapWidget mapWidget, float xOffset, float yOffset) 
    {
        if (!vertices || vertices.Count() < 2) 
            return;
        float height = NinjinUtils.screenHeight * 1.33333333;
        if (height > NinjinUtils.screenWidth)
            height = NinjinUtils.screenWidth;
        float screenScale = height / g_Game.GetWorld().GetWorldSize();
        float mapToScreen = mapScale / screenScale;
        for (int j = 0; j < vertices.Count(); j++) 
        {
            vector start = mapWidget.MapToScreen(vertices[j]) + Vector(-xOffset, -yOffset, 0);
            vector end = mapWidget.MapToScreen(vertices[(j + 1) % vertices.Count()]) + Vector(-xOffset, -yOffset, 0);
            drawCanvas.DrawLine(start[0], start[1], end[0], end[1], 2, lastColor);
        }
        if (m_DrawStrikeLines && g_MainConfig && g_MainConfig.StrikeLineSpacingMeters > 0) 
        {
            DrawStrikeLines(mapWidget, xOffset, yOffset, mapScale);
        }
    }
    private vector CalcPolygonCenter(array<vector> verts) 
    {
        float cx, cy, cz;
        foreach (vector v : verts) 
        {
            cx += v[0]; cy += v[1]; cz += v[2];
        }
        return Vector(cx / verts.Count(), cy / verts.Count(), cz / verts.Count());
    }
    void DrawStrikeLines(MapWidget mapWidget, float xOffset, float yOffset, float mapScale) 
    {
        if (vertices.Count() < 3) 
            return;
        float spacing = g_MainConfig.StrikeLineSpacingMeters;
        int alpha = Math.Clamp(Math.Floor(g_MainConfig.StrikeLineTransparency * 255), 0, 255);
        int fadedColor = (alpha << 24) | (lastColor & 0x00ffffff);
        array<vector> screenVerts = new array<vector>();
        float minX = 1e9, minY = 1e9, maxX = -1e9, maxY = -1e9;
        foreach (vector v : vertices) 
        {
            vector screenV = mapWidget.MapToScreen(v) + Vector(-xOffset, -yOffset, 0);
            screenVerts.Insert(screenV);
            minX = Math.Min(minX, screenV[0]);
            maxX = Math.Max(maxX, screenV[0]);
            minY = Math.Min(minY, screenV[1]);
            maxY = Math.Max(maxY, screenV[1]);
        }
        float screenHeightAdj = NinjinUtils.screenHeight * 1.33333333;
        if (screenHeightAdj > NinjinUtils.screenWidth)
            screenHeightAdj = NinjinUtils.screenWidth;
        float screenScale = screenHeightAdj / g_Game.GetWorld().GetWorldSize();
        float mapToScreen = mapScale / screenScale;
        float pixelSpacing = spacing / mapToScreen;
        float diagSpacing = pixelSpacing * 1.4142;
        float width = maxX - minX;
        float height = maxY - minY;
        for (float offset = -height; offset < width; offset += diagSpacing) 
        {
            float x1 = minX + offset;
            float y1 = minY;
            float x2 = minX + offset + height;
            float y2 = maxY;
            vector p1 = Vector(x1, y1, 0);
            vector p2 = Vector(x2, y2, 0);
            array<vector> intersections = new array<vector>();
            for (int k = 0; k < screenVerts.Count(); k++) 
            {
                vector a = screenVerts[k];
                vector b = screenVerts[(k + 1) % screenVerts.Count()];
                vector intersection;
                if (LineIntersect(p1, p2, a, b, intersection)) 
                {
                    intersections.Insert(intersection);
                }
            }
            if (intersections.Count() < 2)
                continue;
            SortIntersections(intersections, p1, p2);
            for (int m = 0; m + 1 < intersections.Count(); m += 2) 
            {
                vector start = intersections[m];
                vector end = intersections[m + 1];
                drawCanvas.DrawLine(start[0], start[1], end[0], end[1], 1, fadedColor);
            }
        }
    }
    bool LineIntersect(vector a1, vector a2, vector b1, vector b2, out vector intersection) 
    {
        float s1_x = a2[0] - a1[0];
        float s1_y = a2[1] - a1[1];
        float s2_x = b2[0] - b1[0];
        float s2_y = b2[1] - b1[1];
        float denom = (-s2_x * s1_y + s1_x * s2_y);
        if (Math.AbsFloat(denom) < 0.00001)
            return false;
        float s = (-s1_y * (a1[0] - b1[0]) + s1_x * (a1[1] - b1[1])) / denom;
        float t = ( s2_x * (a1[1] - b1[1]) - s2_y * (a1[0] - b1[0])) / denom;
        if (s >= 0 && s <= 1 && t >= 0 && t <= 1) 
        {
            intersection = Vector(a1[0] + (t * s1_x), a1[1] + (t * s1_y), 0);
            return true;
        }
        return false;
    }
    void SortIntersections(array<vector> points, vector refPoint, vector dirEnd) 
    {
        float dx = dirEnd[0] - refPoint[0];
        float dy = dirEnd[1] - refPoint[1];
        for (int i = 0; i < points.Count() - 1; i++) 
        {
            for (int j = i + 1; j < points.Count(); j++) 
            {
                vector pi = points[i];
                vector pj = points[j];
                float di = (pi[0] - refPoint[0]) * dx + (pi[1] - refPoint[1]) * dy;
                float dj = (pj[0] - refPoint[0]) * dx + (pj[1] - refPoint[1]) * dy;
                if (di > dj) 
                {
                    vector temp = points[i];
                    points[i] = points[j];
                    points[j] = temp;
                }
            }
        }
    }
}
