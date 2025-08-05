/*
---------------------------------------------------------------------
Day Configuration
---------------------------------------------------------------------
*/
    class DayConfig
    {
        string dayName;
        int startHour;
        int endHour;
        void DayConfig(string day = "", int start = 0, int end = 24)
        {
            dayName = day;
            startHour = start;
            endHour = end;
        }
    }
/*
---------------------------------------------------------------------
DynamicZones Zone Class
---------------------------------------------------------------------
*/
    class DynamicZones
    {
        float zoneMinHeight;
        float zoneMaxHeight;
        bool ignoreHeightCheck;
        float ZonelabelOffsetX_Meters;
        float ZonelabelOffsetZ_Meters;
        int ZoneLabelColor;
        int type;
        int priority;
        bool NoLogOut;
        vector NoLogOutTeleportPos;
        bool Hide;
        bool HideWhenNested;
        bool DrawNoBuildShape;
        bool enableCustomMessages;
        string customTitle;
        string customMessageEnter;
        string customMessageExit;
        string customIcon;
        int notificationColor;
        ref array<ref DayConfig> dayConfigs = new array<ref DayConfig>();
        int zoneAlpha;
        int zoneRed;
        int zoneGreen;
        int zoneBlue;
        bool forceFirstPerson;
        float radius;
        float offsetMinMultiplier;
        float offsetMaxMultiplier;
        bool EnableExpansion3DMarker;
        bool OnlyAllowExpansion2DMarker;
        string ExpansionMarkerName;
        string Expansion3DIcon;
        bool drawShape;
        bool drawStrikeZone;
        bool UsesDisallowedVehicles;
        // legacy
        string days;          
        int    startHour;
        int    endHour;
    }
/*
---------------------------------------------------------------------
ZONE BASE CLASS
---------------------------------------------------------------------
*/
    class ZoneBase
    {
        string name;
        string displayName;
        float ZonelabelOffsetX_Meters;
        float ZonelabelOffsetZ_Meters;
        int ZoneLabelColor;
        int type;
        int priority;
        bool NoLogOut;
        vector NoLogOutTeleportPos;
        bool Hide;
        bool HideWhenNested;
        bool enableCustomMessages;
        string customTitle;
        string customMessageEnter;
        string customMessageExit;
        string customIcon;
        int notificationColor;
        ref array<ref DayConfig> dayConfigs = new array<ref DayConfig>();
        int zoneAlpha;
        int zoneRed;
        int zoneGreen;
        int zoneBlue;
        bool forceFirstPerson;
        bool UsesDisallowedVehicles ;
        ZoneShape shape;
        bool drawShape;
        bool drawStrikeZone;
        float radius;
        float noBuildRadius;
        bool DrawNoBuildShape;
        bool EnableExpansion3DMarker;
        bool OnlyAllowExpansion2DMarker;
        string ExpansionMarkerName;
        string Expansion3DIcon;
        vector center;
        bool ignoreHeightCheck;
        float zoneMinHeight;
        float zoneMaxHeight;
        ref array<vector> vertices = new array<vector>();
        // legacy
        string days;          
        int    startHour;
        int    endHour;
        void ZoneBase()
        {
            priority = 1;
            ZoneLabelColor = -65536;
            UsesDisallowedVehicles = false;
            ZonelabelOffsetX_Meters = 0.0;
            ZonelabelOffsetZ_Meters = 0.0;
            noBuildRadius = 0.0;
            dayConfigs.Insert(new DayConfig("Monday"));
            dayConfigs.Insert(new DayConfig("Tuesday"));
            dayConfigs.Insert(new DayConfig("Wednesday"));
            dayConfigs.Insert(new DayConfig("Thursday"));
            dayConfigs.Insert(new DayConfig("Friday"));
            dayConfigs.Insert(new DayConfig("Saturday"));
            dayConfigs.Insert(new DayConfig("Sunday"));
            DrawNoBuildShape = true;
            Hide = false;
            NoLogOut = false;
            HideWhenNested = false;
            NoLogOutTeleportPos = vector.Zero;
        }
/*
--------------------------------------------------
IsActive - Checks if the zone is active based on the current time and day
--------------------------------------------------
*/
    bool IsActive()
    {
        #ifdef SERVER
            NinjinsZoneTimeSettings currentTime = NinjinsZoneTimeSettings.Now();
            int currentDay = NinjinsZoneTimeSettings.GetDayOfWeek();
            string currentDayName = NinjinsZoneTimeSettings.GetDayName(currentDay);
            foreach (DayConfig config : dayConfigs)
            {
                if (config.dayName == currentDayName)
                {
                    int normalizedStart = config.startHour % 24;
                    int normalizedEnd = config.endHour % 24;
                    int currentHour = currentTime.Hour;
                    if (normalizedStart < normalizedEnd)
                        return (currentHour >= normalizedStart && currentHour < normalizedEnd);
                    else
                        return (currentHour >= normalizedStart || currentHour < normalizedEnd);
                }
            }
            return false;
        #else
            return true;
        #endif
    }
/*
--------------------------------------------------
IsInside - Checks by Shape
--------------------------------------------------
*/
    bool IsInside(vector position)
    {
        if (!IsActive()) 
            return false;
        if (!ignoreHeightCheck)
        {
            if (zoneMinHeight != 0.0 && position[1] < zoneMinHeight)
                return false;
            if (zoneMaxHeight != 0.0 && position[1] > zoneMaxHeight)
                return false;
        }
        switch (shape)
        {
            case ZoneShape.CIRCLE:
            {
                float dist;
                vector a = Vector(position[0], 0, position[2]);
                vector b = Vector(center[0], 0, center[2]);
                dist = vector.Distance(a, b);
                return dist <= radius;
            }
            case ZoneShape.POLYGON:
            {
                return CheckPolygon(position);
            }
        }
        return false;
    }
/*
--------------------------------------------------
Ray Cast Polygon Check
--------------------------------------------------
*/
    protected bool CheckPolygon(vector position)
    {
        if (!vertices || vertices.Count() == 0)
            return false;
        bool inside = false;
        float px = position[0];
        float pz = position[2];
        int numVerts = vertices.Count();
        for (int i = 0, j = numVerts - 1; i < numVerts; j = i++)
        {
            vector vi = vertices[i];
            vector vj = vertices[j];
            float xi = vi[0];
            float zi = vi[2];
            float xj = vj[0];
            float zj = vj[2];
            bool intersects = ((zi > pz) != (zj > pz));
            if (intersects)
            {
                float slope = (xj - xi) / (zj - zi);
                float intersectX = xi + slope * (pz - zi);
                if (px < intersectX)
                    inside = !inside;
            }
        }
        return inside;
    }
/*
--------------------------------------------------
GETTERS
--------------------------------------------------
*/
    string GetName() 
    { 
        return name; 
    }
    int GetColor() 
    { 
        return ARGB(zoneAlpha, zoneRed, zoneGreen, zoneBlue); 
    }
    vector GetPolygonCentroid()
    {
        if (!vertices || vertices.Count() == 0)
            return "0 0 0";
        float x = 0;
        float z = 0;
        foreach (vector v : vertices)
        {
            x += v[0];
            z += v[2];
        }
        x /= vertices.Count();
        z /= vertices.Count();
        return Vector(x, 0, z);
    }
    bool HasNoBuild() 
    { 
        return noBuildRadius > 0.0; 
    }
    float GetNoBuildRadius() 
    { 
        return radius + noBuildRadius; 
    }
    bool IsInsideNoBuild(vector pos)
    {
        if (!HasNoBuild())       
            return false;
        switch (shape)
        {
            case ZoneShape.CIRCLE:
                vector a = Vector(pos[0], 0, pos[2]);
                vector b = Vector(center[0], 0, center[2]);
                return vector.Distance(a, b) <= (radius + noBuildRadius);
            case ZoneShape.POLYGON:
                if (CheckPolygon(pos))
                    return true;
                if (noBuildRadius > 0)
                {
                    vector a2 = Vector(pos[0], 0, pos[2]);
                    vector b2 = GetPolygonCentroid();
                    float dist = vector.Distance(a2, b2);
                    return dist <= (GetApproxPolyRadius() + noBuildRadius);
                }
                return false;
        }
        return false;
    }
    float GetApproxPolyRadius()
    {
        float maxDist = 0;
        vector c = GetPolygonCentroid();
        foreach (vector v : vertices)
        {
            float d = vector.Distance(Vector(v[0],0,v[2]), Vector(c[0],0,c[2]));
            if (d > maxDist) maxDist = d;
        }
        return maxDist;
    }
};