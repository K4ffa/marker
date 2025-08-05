modded class ItemBase
{
/*
---------------------------------------------------------------------------------------------
Item Zone creation
---------------------------------------------------------------------------------------------
*/
    string m_NinItemZoneID;
    bool m_NinHasBeenPickedUp = false;
    protected bool m_IsInSafeZone = false;
    override void EEInit()
    {
        super.EEInit();
        if (!GetGame().IsServer()) 
            return;
        string typeName = GetType();
        if (!g_MainConfig || !g_MainConfig.EnableItemSpawnZoneCreation) 
            return;
        if (!g_ItemRules || !g_ItemRules.CreateZoneWhenItemSpawned.Contains(typeName)) 
            return;
        if (ShouldBlockZoneCreation())
        {
            m_NinHasBeenPickedUp = true;
            NinjinsPvPPvE.LogDebug("[ItemZone] Zone creation blocked for " + typeName + " due to location.");
            return;
        }
        if (!m_NinHasBeenPickedUp)
        {
            DynamicZones zoneDef = g_ItemRules.CreateZoneWhenItemSpawned.Get(typeName);
            CreateItemZone(zoneDef);
        }
        else
        {
            NinjinsPvPPvE.LogDebug("[ItemZone] Spawn blocked for already picked up item: " + typeName);
        }
    }
    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);
        if (!GetGame().IsServer()) 
            return;
        string typeName = GetType();
        if (!g_MainConfig || !g_MainConfig.EnableItemSpawnZoneCreation) 
            return;
        if (g_ItemRules && g_ItemRules.CreateZoneWhenItemSpawned.Contains(typeName))
        {
            RemoveDynamicZoneBase();
        }
    }
    override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner)
    {
        super.OnItemLocationChanged(old_owner, new_owner);
        if (!GetGame().IsServer()) 
            return;
        if (!g_MainConfig || !g_MainConfig.EnableItemSpawnZoneCreation) 
            return;
        if (!g_ItemRules || !g_ItemRules.CreateZoneWhenItemSpawned.Contains(GetType())) 
            return;
        if (ShouldBlockZoneCreation())
        {
            if (!m_NinHasBeenPickedUp)
            {
                RemoveDynamicZoneBase();
                m_NinHasBeenPickedUp = true;
                NinjinsPvPPvE.LogDebug("[ItemZone] Zone removed due to item going into inventory/cargo.");
            }
        }
    }
    bool ShouldBlockZoneCreation()
    {
        InventoryLocation loc = new InventoryLocation();
        if (GetInventory().GetCurrentInventoryLocation(loc) && loc.IsValid())
        {
            int locType = loc.GetType();
            if (locType == InventoryLocationType.CARGO || locType == InventoryLocationType.PROXYCARGO)
            {
                NinjinsPvPPvE.LogDebug("[ItemZone] Blocked zone creation: item is inside cargo.");
                return true;
            }
        }
        EntityAI parent = GetHierarchyParent();
        if (parent && parent.IsInherited(PlayerBase))
        {
            NinjinsPvPPvE.LogDebug("[ItemZone] Blocked zone creation: item is attached to a player.");
            return true;
        }
        return false;
    }
    void CreateItemZone(DynamicZones def)
    {
        if (m_NinItemZoneID != "") 
            return;
        if (!GetGame().IsServer()) 
            return;
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (!zoneManager) 
            return;
        vector pos = GetPosition();
        float radius     = def.radius;
        float minOffset  = radius * def.offsetMinMultiplier;
        float maxOffset  = radius * def.offsetMaxMultiplier;
        float angle      = Math.RandomFloatInclusive(0, Math.PI2);
        float distance   = Math.RandomFloatInclusive(minOffset, maxOffset);
        float offsetX    = Math.Cos(angle) * distance;
        float offsetZ    = Math.Sin(angle) * distance;
        vector center    = Vector(pos[0] + offsetX, pos[1], pos[2] + offsetZ);
        m_NinItemZoneID = "ItemZone_" + GetType() + "_" + center[0].ToString() + "_" + center[2].ToString();
        ZoneBase zone = new ZoneBase();
        zone.name                        = m_NinItemZoneID;
        zone.HideWhenNested              = def.HideWhenNested;
        zone.DrawNoBuildShape            = def.DrawNoBuildShape;
        zone.zoneMinHeight               = def.zoneMinHeight;
        zone.zoneMaxHeight               = def.zoneMaxHeight;
        zone.ignoreHeightCheck           = def.ignoreHeightCheck;
        zone.displayName                 = def.customTitle;
        zone.type                        = def.type;
        zone.noBuildRadius               = -1;
        zone.priority                    = def.priority;
        zone.shape                       = ZoneShape.CIRCLE;
        zone.center                      = center;
        zone.radius                      = radius;
        zone.zoneAlpha                   = def.zoneAlpha;
        zone.zoneRed                     = def.zoneRed;
        zone.zoneGreen                   = def.zoneGreen;
        zone.zoneBlue                    = def.zoneBlue;
        zone.dayConfigs = new array<ref DayConfig>();
        foreach (DayConfig config : def.dayConfigs)
        {
            zone.dayConfigs.Insert(new DayConfig(config.dayName, config.startHour, config.endHour));
        }
        zone.enableCustomMessages        = def.enableCustomMessages;
        zone.customTitle                 = def.customTitle;
        zone.customMessageEnter          = def.customMessageEnter;
        zone.customMessageExit           = def.customMessageExit;
        zone.customIcon                  = def.customIcon;
        zone.notificationColor           = def.notificationColor;
        zone.forceFirstPerson            = def.forceFirstPerson;
        zone.drawShape                   = def.drawShape;
        zone.UsesDisallowedVehicles      = def.UsesDisallowedVehicles;
        zone.EnableExpansion3DMarker     = def.EnableExpansion3DMarker;
        zone.OnlyAllowExpansion2DMarker  = def.OnlyAllowExpansion2DMarker;
        zone.Expansion3DIcon             = def.Expansion3DIcon;
        zone.ExpansionMarkerName         = def.ExpansionMarkerName;
        zone.drawStrikeZone              = def.drawStrikeZone;
        zone.ZonelabelOffsetX_Meters = def.ZonelabelOffsetX_Meters;
        zone.ZonelabelOffsetZ_Meters = def.ZonelabelOffsetZ_Meters;
        zone.ZoneLabelColor          = def.ZoneLabelColor;
        zone.Hide          = def.Hide;
        zone.NoLogOut                     = def.NoLogOut;
        zone.NoLogOutTeleportPos          = def.NoLogOutTeleportPos;
        zoneManager.RegisterDynamicZone(zone);
        NinjinsPvPPvE.LogDebug("[ItemZone] Zone created for " + GetType() + ": " + m_NinItemZoneID);
    }
    void RemoveDynamicZoneBase()
    {
        if (m_NinItemZoneID != "" && ZoneManager.GetInstance())
        {
            bool success = ZoneManager.GetInstance().RemoveDynamicZone(m_NinItemZoneID);
            if (success)
            {
                NinjinsPvPPvE.LogDebug("[ItemZone] Zone removed: " + m_NinItemZoneID);
            }
            m_NinItemZoneID = "";
        }
    }
/*
---------------------------------------------------------------------------------------------
Utils + helpters
---------------------------------------------------------------------------------------------
*/
    bool IsWhitelistedFromSZCleanup()
    {
        if (!g_ItemRules || !g_ItemRules.SZItemWhiteList)
            return false;
        foreach (string className : g_ItemRules.SZItemWhiteList)
        {
            if (IsKindOf(className))
                return true;
        }
        return false;
    }
    PlayerBase GetOwnerPlayer()
    {
        EntityAI parent = GetHierarchyParent();
        PlayerBase player = PlayerBase.Cast(parent);
        if (player && player.IsAlive())
        {
            return player;
        }
        return null;
    }
/*
---------------------------------------------------------------------------------------------
EEOnDamageCalculated - Called when damage is calculated on item, uses DamageUtils
---------------------------------------------------------------------------------------------
*/
    override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        if (!IsAlive())
            return true;
        if (GetGame().IsMultiplayer() && !GetGame().IsServer())
            return true;
        DamageUtils damageUtils = DamageUtils.GetInstance();
        bool allowDamage;
        allowDamage = damageUtils.ShouldAllowItemDamage(this, damageResult, damageType, source, dmgZone, ammo, modelPos, speedCoef);
        if (!allowDamage)
        {
            NinjinsPvPPvE.LogDebug("[ItemBase] Damage denied on item: " + GetType());
            return false;
        }
        return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
    }
}
