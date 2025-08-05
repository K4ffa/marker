class NinjinsCircle : NinjinMapWrapper {
    const float EPS = 0.01;
    int circleWidth = 2;
    int  m_Priority = 1;
    bool m_HideWhenNested = false;
    bool drawStrikeLines = false;
    bool TotallyInsideOtherCircle = false;
    float radius = 100.0;
    ref array<ref NinjinsCircle> zoneCheckList = new array<ref NinjinsCircle>();
    ref array<ref Param2<float, float>> intersecangles = new array<ref Param2<float, float>>();
    bool needUpdate = true;
    bool isZoneNested = false;
    float lastcircumf = -1;
    ref array<ref Param4<bool, bool, float, bool>> drawStepsPrepared = new array<ref Param4<bool, bool, float, bool>>();
    void Init(vector center, float radius_, int color, int prio)
    {
        this.position = center;
        this.radius = radius_;
        this.lastColor = color;
        this.m_Priority = prio;
        NinjinUtils.UpdateScreenSize();
        if (g_MainConfig && g_MainConfig.CircleDrawingWidth > 0) 
        {
            circleWidth = g_MainConfig.CircleDrawingWidth;
        } 
        else 
        {
            circleWidth = 2;
        }
    }
    void SetHideWhenNested(bool hide) 
    { 
        m_HideWhenNested = hide; 
    }
    void SetDrawStrike(bool enable) 
    { 
        drawStrikeLines = enable; 
    }
    override void Update(float mapScale, vector mapPos, MapWidget mapWidget, float xOffset, float yOffset)
    {
        if (m_HideWhenNested)
            return;
        if (!drawCanvas)
            return;
        vector screenPos = mapWidget.MapToScreen(position) + Vector(-xOffset, -yOffset, 0);
        float height = NinjinUtils.screenHeight * 1.33333333;
        if (height > NinjinUtils.screenWidth)
            height = NinjinUtils.screenWidth;
        float screenScale  = height / g_Game.GetWorld().GetWorldSize();
        float mapToScreen  = mapScale / screenScale;
        float radiusScreen = radius / mapToScreen;
        if (radiusScreen <= 0)
            return;
        float radiusRoot    = Math.Sqrt(radius);
        float circumf = 2.0 * Math.PI * radiusRoot;
        float part          = 1.0 / radiusRoot;
        if (needUpdate)
            CalcEveryCircleIntersection();
        if (needUpdate || lastcircumf != circumf)
        {
            MathForCircleIntersections(circumf, part);
            lastcircumf = circumf;
        }
        needUpdate = false;
        float angle2  = 0.0;
        float rawX2   = radius;
        float rawY2   = 0.0;
        float newX2   = screenPos[0] + radius / mapToScreen;
        float newY2   = screenPos[1];
        int i = 0;
        foreach (Param4<bool, bool, float, bool> param : drawStepsPrepared)
        {
            ++i;
            float angle1 = angle2;
            angle2       = part * i;
            float rawX1  = rawX2;
            rawX2        = radius * Math.Cos(angle2);
            float rawY1  = rawY2;
            rawY2        = -radius * Math.Sin(angle2);
            float newX1  = newX2;
            newX2        = screenPos[0] + rawX2 / mapToScreen;
            float newY1  = newY2;
            newY2        = screenPos[1] + rawY2 / mapToScreen;
            if (param.param1)
                continue;
            if (param.param2)
            {
                float offset    = 0.0015;
                float edgeAngle = param.param3;
                if (param.param4)
                    edgeAngle += offset;
                else
                    edgeAngle -= offset;
                float newX3 = screenPos[0] + radius * Math.Cos(edgeAngle) / mapToScreen;
                float newY3 = screenPos[1] - radius * Math.Sin(edgeAngle) / mapToScreen;
                if (param.param4)
                    drawCanvas.DrawLine(newX3, newY3, newX2, newY2, circleWidth, lastColor);
                else
                    drawCanvas.DrawLine(newX3, newY3, newX1, newY1, circleWidth, lastColor);
                continue;
            }
            drawCanvas.DrawLine(newX1, newY1, newX2, newY2, circleWidth, lastColor);
        }
        if (drawStrikeLines)
            DrawStrikeOverlay(mapToScreen, screenPos, mapWidget, xOffset, yOffset);
    }
    void DrawStrikeOverlay(float mapToScreen, vector screenPos, MapWidget mapWidget, float xOffset, float yOffset)
    {
        if (!drawStrikeLines)
            return;
        float worldSpacingMeters;
        if (g_MainConfig && g_MainConfig.StrikeLineSpacingMeters > 0)
            worldSpacingMeters = g_MainConfig.StrikeLineSpacingMeters;
        else
            worldSpacingMeters = 20.0;
        float pixelStride = worldSpacingMeters / mapToScreen;
        if (pixelStride < 2.0)
            pixelStride = 2.0;
        float radiusScreen = radius / mapToScreen;
        if (radiusScreen <= 0)
            return;
        int   lineCount = (radiusScreen * 2) / pixelStride + 1;
        int   radPart   = radiusScreen / pixelStride;
        float sqStride2 = pixelStride / Math.Sqrt(2.0);
        float screen_X     = screenPos[0] / 2.0;
        float start_Offset =  screen_X - (int)(screen_X / sqStride2) * sqStride2;
        float screen_Y = screenPos[1] / 2.0;
        start_Offset  += (screen_Y - (int)(screen_Y / sqStride2) * sqStride2);
        float start1 = radPart * sqStride2 - start_Offset + sqStride2;
        float start2 = radPart * sqStride2 - start_Offset + sqStride2;
        if (lineCount > 1000)
            return;
        int fadedColor = ((0xff000000 | lastColor) & 0x50ffffff);
        float cx = screenPos[0];
        float cy = screenPos[1];
        for (int i = 1; i <= lineCount; ++i)
        {
            float otherLen = Math.Sqrt(radiusScreen * radiusScreen - (start1 * start1 + start2 * start2));
            float begin1 = 0.7071067 * otherLen;
            float begin2 = -0.7071067 * otherLen;
            float end1 = cx + start1 - begin1;
            float end2 = cy + start2 - begin2;
            begin1 += cx + start1;
            begin2 += cy + start2;
            start1 -= sqStride2;
            start2 -= sqStride2;
            drawCanvas.DrawLine(begin1, begin2, end1, end2, circleWidth, fadedColor);
        }
    }
    void CalcEveryCircleIntersection()
    {
        intersecangles.Clear();
        if (!zoneCheckList)
            return;
        for (int i = 0; i < zoneCheckList.Count(); i++)
        {
            NinjinsCircle circ = zoneCheckList.Get(i);
            if (circ == this)
                continue;
            if (circ.m_Priority < m_Priority)
                continue;
            float dx = circ.position[0] - position[0];
            float dz = circ.position[2] - position[2];
            float d  = Math.Sqrt(dx * dx + dz * dz);
            if (d >= radius + circ.radius || d <= 0)
                continue;
            float a  = (radius * radius - circ.radius * circ.radius + d * d) / (2.0 * d);
            float h  = Math.Sqrt(radius * radius - a * a);
            float hd = h / d;
            float px = position[0] + dx * a / d;
            float pz = position[2] + dz * a / d;
            float x1 = (px + hd * (circ.position[2] - position[2])) - position[0];
            float z1 = (pz - hd * (circ.position[0] - position[0])) - position[2];
            float x2 = (px - hd * (circ.position[2] - position[2])) - position[0];
            float z2 = (pz + hd * (circ.position[0] - position[0])) - position[2];
            float dist1 = Math.Sqrt(x1 * x1 + z1 * z1);
            float dist2 = Math.Sqrt(x2 * x2 + z2 * z2);
            if (dist1 <= 0 || dist2 <= 0)
                continue;
            float ang1 = Math.Acos(x1 / dist1);
            if (z1 < 0) ang1 = Math.PI2 - ang1;
            float ang2 = Math.Acos(x2 / dist2);
            if (z2 < 0) ang2 = Math.PI2 - ang2;
            if (ang1 < ang2)
                intersecangles.Insert(new Param2<float,float>(ang1, ang2));
            else
            {
                intersecangles.Insert(new Param2<float,float>(-1, ang2));
                intersecangles.Insert(new Param2<float,float>(ang1, Math.PI2 + 1));
            }
        }
    }
    void CalculateInsideCircle()
    {
        TotallyInsideOtherCircle = false;
        foreach (NinjinsCircle circ : zoneCheckList)
        {
            if (circ == this)
                continue;
            if ( !m_HideWhenNested && (circ.m_Priority < m_Priority) )
                continue;
            float dx = circ.position[0] - position[0];
            float dz = circ.position[2] - position[2];
            float d  = Math.Sqrt(dx * dx + dz * dz);
            if (d + radius <= circ.radius + EPS)
            {
                TotallyInsideOtherCircle = true;
            }
        }
    }
    void MathForCircleIntersections(float circumf, float part)
    {
        drawStepsPrepared.Clear();
        float ang2 = 0.0;
        for (int i = 1; i <= circumf + 1; i++)
        {
            float ang1 = ang2;
            ang2 = part * i;
            bool intersecting = false;
            bool edge         = false;
            float edgeAngle   = 0.0;
            bool clipDirectionForward      = false;
            foreach (Param2<float, float> span : intersecangles)
            {
                if (ang2 > span.param1 && ang1 < span.param2)
                {
                    if (span.param1 < ang1)
                    {
                        edgeAngle = span.param2;
                        clipDirectionForward   = true;
                    }
                    else
                    {
                        edgeAngle = span.param1;
                        clipDirectionForward   = false;
                    }
                    edge = true;
                }
                if (ang1 > span.param1 && ang2 < span.param2)
                {
                    intersecting = true;
                    break;
                }
            }
            drawStepsPrepared.Insert(
                new Param4<bool, bool, float, bool>(intersecting, edge, edgeAngle, clipDirectionForward));
        }
    }
    void CirclesOthers(array<ref NinjinsCircle> circles)
    {
        zoneCheckList.Clear();
        foreach (NinjinsCircle circ : circles)
            zoneCheckList.Insert(circ);
        needUpdate = true;
        CalculateInsideCircle();
    }
}