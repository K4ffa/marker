class DamageUtils
{  
    private static ref DamageUtils s_Instance;
    private static bool isReflectingDamage = false;
    ref static set<string> BoltAmmoTypes;
    ref map<string, float> m_LastPvPBlockedNotificationTime;
    void DamageUtils()
    {
        if (!m_LastPvPBlockedNotificationTime)
            m_LastPvPBlockedNotificationTime = new map<string, float>();
        if (!BoltAmmoTypes)
        {
            BoltAmmoTypes = new set<string>();
            BoltAmmoTypes.Insert("Bullet_HuntingBolt");
            BoltAmmoTypes.Insert("Bullet_ImprovisedBolt_1");
            BoltAmmoTypes.Insert("Bullet_ImprovisedBolt_2");
            BoltAmmoTypes.Insert("Bullet_CupidsBolt");
            BoltAmmoTypes.Insert("Bullet_ArrowComposite");
            BoltAmmoTypes.Insert("Bullet_ArrowPrimitive");
            BoltAmmoTypes.Insert("Bullet_ArrowBoned");
            BoltAmmoTypes.Insert("Bullet_ArrowBolt");
            BoltAmmoTypes.Insert("Bullet_SharpStick");
        }
    }
    static DamageUtils GetInstance()
    {
        if (!s_Instance)
        {
            s_Instance = new DamageUtils();
        }
        return s_Instance;
    }
    string GetZoneState(bool isPvP, bool isPvE, bool isRaid) 
    {
        if (isPvP) return "In PvP";
        if (isPvE) return "In PvE";
        if (isRaid) return "In Raid";
        return "No Active Zone";
    }
    bool ShouldAllowDamage(PlayerBase victim, TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        if (!victim || !damageResult) 
            return false;
        #ifdef EXPANSIONMODWEAPONS
        if (source && (source.IsInherited(Expansion_RPG_Explosion) || source.IsInherited(Expansion_LAW_Explosion)))
        {
            if (victim.netSync_IsInPvEZone)
            {
                NinjinsPvPPvE.LogDebug("[PvE Block] Blocked RPG/LAW explosion damage to player in PvE state");
                return false;
            }
            NinjinsPvPPvE.LogDebug("[DamageUtils] Clearing recent attacker due to RPG/LAW explosion.");
            AttackerUtils.ClearRecentAttacker();
        }
        #endif
        string sourceName = "null";
        if (source)
            sourceName = source.GetType();
        AttackerContext ctx = ResolveAttacker(source);
        GrenadeAttackerContext(ctx, source);
        PlayerBase attacker = ctx.Player;
        if (!IsAllowedPaintballDamage(attacker, victim, ammo, source))
        {
            return false;
        }
        //lockpick zone dmg stuff (needs re-work)
        if (attacker && attacker.GetIdentity() && victim && victim.GetIdentity())
        {
            ZoneManager zm = ZoneManager.GetInstance();
            if (zm)
            {
                string attackerID = attacker.GetIdentity().GetId();
                string victimID   = victim.GetIdentity().GetId();
                string attackerLockpickerID = zm.GetLockpickingPlayerIDAtPosition(attacker.GetPosition());
                string victimLockpickerID   = zm.GetLockpickingPlayerIDAtPosition(victim.GetPosition());
                bool inLockpickZone = (attackerLockpickerID != "" || victimLockpickerID != "");
                if (inLockpickZone)
                {
                    bool attackerIsLockpicker = (attackerLockpickerID == attackerID);
                    bool victimIsLockpicker   = (victimLockpickerID   == victimID);
                    if (attackerIsLockpicker || victimIsLockpicker)
                    {
                        return true;
                    }
                    return false;
                }
            }
        }
        if (ShouldLog(ctx, victim))
        {
            LogEntityContext(ctx, null, "[ATTACKER]", ammo, dmgZone, source.GetType(), GetDamageSourceTypeName(ctx.DamageSourceType));
            LogEntityContext(null, victim, "[VICTIM]", ammo, dmgZone);
        }
        bool victimInPvP = victim.netSync_IsInPvPZone;
        bool victimInPvE = victim.netSync_IsInPvEZone;
        bool victimInRaid = victim.netSync_IsInRaidMode;
        bool attackerInPvP = attacker && attacker.netSync_IsInPvPZone;
        bool attackerInPvE = attacker && attacker.netSync_IsInPvEZone;
        bool attackerInRaid = attacker && attacker.netSync_IsInRaidMode;
        #ifdef EXPANSIONMODGROUPS
        if (ctx.IsPlayer() && victim && g_MainConfig.ExpansionGroupsFriendlyFireDisabled != 0)
        {
            if (ctx.Player == victim) 
                return true;
            if (ctx.Player.Expansion_IsFriendly(victim)) 
                return false;
        }
        #endif
        #ifdef EXPANSIONMODAI
        eAIBase aiAttacker = ctx.AI;
        if (aiAttacker && eAIBase.Cast(victim)) 
            return true;
        if (aiAttacker)
        {
            if (g_MainConfig.AiToPlayerDamageEverywhere) 
                return true;
            if (g_MainConfig.OnlyAllowAIToDoDamageIfPlayerIsPvP && victimInPvP) 
                return true;
            if (g_MainConfig.OnlyAllowAIToDoDamageIfPlayerIsPvE && victimInPvE) 
                return true;
            if (g_MainConfig.OnlyAllowAIToDamageInRaidMode && victimInRaid) 
                return true;
            return false;
        }
        if (eAIBase.Cast(victim))
        {
            if (g_MainConfig.PlayerToAiDamageEverywhere) 
                return true;
            if (g_MainConfig.OnlyAllowDamageToAIOnlyIfPlayerHasPvPStatus && attackerInPvP) 
                return true;
            if (g_MainConfig.OnlyAllowDamageToAIIfPlayerHasPvEStatus && attackerInPvE) 
                return true;
            if (g_MainConfig.OnlyAllowPlayersToDamageAIInRaidMode && attackerInRaid) 
                return true;
            return false;
        }
        #endif
        if (attacker && attacker == victim) 
            return true;
        if (!victimInPvP && !victimInPvE && !victimInRaid) 
            return true;
        #ifdef EXPANSIONMODHARDLINE
        if (g_MainConfig.EnableExpansionReputationPenaltyPvEvsPvE)
        {
            if (victimInPvE && attackerInPvE && attacker != victim)
            {
                int penalty = g_MainConfig.ExpansionReputationPenealtyPveEsPvE;
                if (penalty > 0)
                    attacker.Expansion_DecreaseReputation(penalty);
            }
        }
        #endif
        if (victimInPvP && attackerInPvP) 
            return true;
        if (victimInRaid && attackerInRaid) 
            return true;
        if ((victimInRaid && attackerInPvP) || (victimInPvP && attackerInRaid)) 
            return true;
        if (victimInPvE && attackerInPvP)
        {
            if (attacker && attacker.GetIdentity())
            {
                if (g_MainConfig.PvPtoPvEBlockedNotification)
                {
                    string attackerID_Notify = attacker.GetIdentity().GetId();
                    float currentTime = GetGame().GetTime();
                    if (!m_LastPvPBlockedNotificationTime)
                        m_LastPvPBlockedNotificationTime = new map<string, float>();
                    if (!m_LastPvPBlockedNotificationTime.Contains(attackerID_Notify) || currentTime - m_LastPvPBlockedNotificationTime.Get(attackerID_Notify) > 30000)
                    {
                        m_LastPvPBlockedNotificationTime.Set(attackerID_Notify, currentTime);
                        NotificationSystem.Create(new StringLocaliser("PvP Blocked"),new StringLocaliser("This player is in a PvE zone. You cannot damage them."),"NinjinsPvPPvE/gui/exclamation.edds",ARGB(255, 255, 150, 0),10.0,attacker.GetIdentity());
                    }
                }
            }
            return false;
        }
        if ((victimInPvP && attackerInPvE) || (victimInPvE && attackerInPvE) || (victimInRaid && attackerInPvE))
        {
            ReflectDamageToAttacker(attacker, damageResult);
            return false;
        }
        if (victimInPvE && attackerInRaid) 
            return false;
        #ifdef EXPANSIONMODWEAPONS
        if (source && (source.IsInherited(Expansion_RPG_Explosion) || source.IsInherited(Expansion_LAW_Explosion)))
        {
            NinjinsPvPPvE.LogDebug("[DamageUtils] Clearing recent attacker due to RPG/LAW explosion.");
            AttackerUtils.ClearRecentAttacker();
        }
        #endif
        return true;
    }
    bool ShouldAllowItemDamage(ItemBase item, TotalDamageResult damageResult, int damageType, EntityAI source, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        if (!item || !damageResult) 
            return false;
        AttackerContext ctx = ResolveAttacker(source);
        GrenadeAttackerContext(ctx, source);
        PlayerBase attacker = ctx.Player;
        #ifdef EXPANSIONMODAI
        eAIBase aiAttacker = ctx.AI;
        #endif
        PlayerBase owner = item.GetOwnerPlayer();
        if (owner && owner.netSync_IsInSafeZone) 
            return false;
        bool ownerInPvP = owner && owner.netSync_IsInPvPZone;
        bool ownerInPvE = owner && owner.netSync_IsInPvEZone;
        bool ownerInRaid = owner && owner.netSync_IsInRaidMode;
        bool attackerInPvP = ctx.Player && ctx.Player.netSync_IsInPvPZone;
        bool attackerInPvE = ctx.Player && ctx.Player.netSync_IsInPvEZone;
        bool attackerInRaid = ctx.Player && ctx.Player.netSync_IsInRaidMode;
        if (g_ItemRules)
        {
            bool attackerPB = attacker && attacker.netSync_IsInPaintBallMode;
            bool ownerPB    = owner    && owner.netSync_IsInPaintBallMode;
            if (attackerPB || ownerPB)
            {
                bool allowed = (ammo != "" && g_ItemRules.AllowedAmmoInPaintBallState.Find(ammo) != -1) || (source && g_ItemRules.AllowedAmmoInPaintBallState.Find(source.GetType()) != -1);
                if (!allowed)
                    return false;
            }
        }
        if (ownerInPvE && (ctx.DamageSourceType == NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_EXPLOSIVE || ctx.DamageSourceType == NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_EXPANSION_EXPLOSIVE)) 
            return false;
        if (ownerInPvE && ctx.DamageSourceType == NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_UNKNOWN && source && source.IsInherited(ExplosivesBase)) 
            return false;
        if (IsFireplaceExplosion(source)) 
            return true;
        string lockpickingPlayerID = ZoneManager.GetInstance().GetLockpickingPlayerIDAtPosition(item.GetPosition());
        if (lockpickingPlayerID != "")
        {
            if (owner && owner.GetIdentity() && owner.GetIdentity().GetId() == lockpickingPlayerID) 
                return true;
            return false;
        }
        bool isOnGround = IsOnGround(item);
        if (isOnGround && g_ItemRules)
        {
            foreach (string itemType : g_ItemRules.CantBeDamagedOnGround)
            {
                if (itemType == item.GetType())
                {
                    if (ctx.IsPlayer())
                    {
                        bool inZone = ctx.Player.netSync_IsInPvPZone || ctx.Player.netSync_IsInPvEZone || ctx.Player.netSync_IsInRaidMode;
                        if (inZone) 
                            return false;
                        return true;
                    }
                    return true;
                }
            }
        }
        if (g_ItemRules)
        {
            string type = item.GetType();
            string attackerName = "Unknown";
            if (ctx.Player && ctx.Player.GetIdentity())
            {
                attackerName = ctx.Player.GetIdentity().GetName();
            }
            bool isInPvEZone = false;
            bool isInPvPZone = false;
            if (g_MainConfig && g_MainConfig.BlockItemDamageStateorZones == 0)
            {
                if (ctx.Player)
                {
                    isInPvEZone = ctx.Player.netSync_IsInPvEZone;
                    isInPvPZone = ctx.Player.netSync_IsInPvPZone;
                    //NinjinsPvPPvE.LogDebug("[ItemProtect] Using player state for item damage block. PvE: " + isInPvEZone + ", PvP: " + isInPvPZone);
                }
            }
            else
            {
                vector itemPos = item.GetPosition();
                ZoneManager zm = ZoneManager.GetInstance();
                isInPvEZone = (zm && zm.IsPvEZone(itemPos)) || (g_MainConfig && g_MainConfig.IsPvEEverywhereActive());
                isInPvPZone = (zm && zm.IsPvPZone(itemPos)) || (g_MainConfig && g_MainConfig.IsPvPEverywhereActive());
                //NinjinsPvPPvE.LogDebug("[ItemProtect] Using zone position for item damage block. PvE: " + isInPvEZone + ", PvP: " + isInPvPZone);
            }
            if (isInPvEZone)
            {
                foreach (string protectedTypePvE : g_ItemRules.CantBeDamagedInPvE)
                {
                    if (item.IsKindOf(protectedTypePvE))
                    {
                        NinjinsPvPPvE.LogDebug("[ItemProtect] Blocked PvE damage to item '" + type + "' from attacker '" + attackerName + "'");
                        return false;
                    }
                }
            }
            if (isInPvPZone)
            {
                foreach (string protectedTypePvP : g_ItemRules.CantBeDamagedInPvP)
                {
                    if (item.IsKindOf(protectedTypePvP))
                    {
                        NinjinsPvPPvE.LogDebug("[ItemProtect] Blocked PvP damage to item '" + type + "' from attacker '" + attackerName + "'");
                        return false;
                    }
                }
            }
        }
        #ifdef EXPANSIONMODGROUPS
        if (ctx.IsPlayer() && owner && g_MainConfig.ExpansionGroupsFriendlyFireDisabled != 0)
        {
            if (ctx.Player == owner) 
                return true;
            if (ctx.Player.Expansion_IsFriendly(owner)) 
                return false;
        }
        #endif
        if (ctx.Player && ctx.Player == owner) 
            return true;
        #ifdef EXPANSIONMODAI
        if (aiAttacker) 
            return true;
        #endif
        if (!ctx.Player) 
            return true;
        if ((ownerInPvE && (attackerInPvP || attackerInPvE || attackerInRaid)) || (ownerInRaid && attackerInPvE) || (ownerInPvP && attackerInPvE)) 
            return false;
        if (ownerInPvP && attackerInPvP) 
            return true;
        if (ownerInRaid && attackerInRaid) 
            return true;
        if ((ownerInRaid && attackerInPvP) || (ownerInPvP && attackerInRaid)) 
            return true;
        return true;
    }
    static bool ShouldBlockFallDamage(PlayerBase player)
    {
        if (!g_MainConfig || !player)
            return false;

        if (g_MainConfig.DisableFallDamage)
        {
            return true;
        }

        if (g_MainConfig.DisableFallDamageSZ && player.netSync_IsInSafeZone)
        {
            return true;
        }

        if (g_MainConfig.DisableFallDamagePvE && player.netSync_IsInPvEZone)
        {     
            return true;
        }

        return false;
    }
    void ReflectDamageToAttacker(EntityAI attacker, TotalDamageResult damageResult)
    {
        if (g_MainConfig && !g_MainConfig.EnableReflectDamage) 
            return;
        if (attacker && !isReflectingDamage)
        {
            isReflectingDamage = true;
            float damage = damageResult.GetDamage("GlobalHealth", "Health");
            if (damage > 0)
            {
                PlayerBase playerAttacker = PlayerBase.Cast(attacker);
                if (playerAttacker)
                {
                    playerAttacker.AddHealth("GlobalHealth", "Health", -damage);
                }
            }
            isReflectingDamage = false;
        }
    }
    static bool IsOnGround(ItemBase item)
    {
        InventoryLocation location = new InventoryLocation();
        if (item.GetInventory().GetCurrentInventoryLocation(location))
        {
            return location.GetType() == InventoryLocationType.GROUND;
        }
        return false;
    }
     void GrenadeAttackerContext(AttackerContext ctx, EntityAI source)
     {
         if (!ctx || !source) 
            return;
         if (!ctx.Player && source.IsInherited(Grenade_Base))
         {
            Grenade_Base grenade = Grenade_Base.Cast(source);
            PlayerBase grenadeThrower = grenade.GetThrower();
            if (!grenadeThrower) grenadeThrower = grenade.GetOwnerPlayer();
            if (grenadeThrower)
            {
            ctx.Player = grenadeThrower;
            ctx.Source = grenade;
            }
         }
         if (!ctx.Player && source.IsInherited(Ammo_40mm_Base))
         {
            Ammo_40mm_Base proj = Ammo_40mm_Base.Cast(source);
            PlayerBase shooter = proj.GetThrower();
            if (!shooter) shooter = proj.GetOwnerPlayer();
            if (shooter)
            {
            ctx.Player = shooter;
            ctx.Source = proj;
            }
         }
     }
    AttackerContext ResolveAttacker(EntityAI source)
    {
        AttackerContext ctx = new AttackerContext();
        ctx.Source = source;
        if (!source) return ctx;
        if (source.IsInherited(SurvivorBase))
        {
            ctx.Player = PlayerBase.Cast(source);
            ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_FISTS;
            return ctx;
        }
        if (source.IsInherited(DayZInfected) || source.IsInherited(AnimalBase))
        {
            ctx.Source = source;
            ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_FISTS;
            return ctx;
        }
        if (source.IsInherited(ExplosivesBase))
        {
            ctx.Player = GetThrowerOrPlacer(source);
            ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_EXPLOSIVE;
            return ctx;
        }
        #ifdef EXPANSIONMODAI
        if (source.IsInherited(eAIBase))
        {
            ctx.AI = eAIBase.Cast(source);
            ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_AI;
            return ctx;
        }
        #endif
        #ifdef EXPANSIONMODWEAPONS
        if (source.IsInherited(Expansion_RPG_Explosion) || source.IsInherited(Expansion_LAW_Explosion))
        {
            PlayerBase recentAttacker = AttackerUtils.GetRecentAttacker();
            if (recentAttacker)
            {
                ctx.Player = recentAttacker;
                ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_EXPANSION_EXPLOSIVE;
                NinjinsPvPPvE.LogDebug("[ResolveAttacker] Found recent attacker: " + recentAttacker.GetIdentity().GetName() + " for RPG/LAW explosion.");
                return ctx;
            }
            else
            {
                NinjinsPvPPvE.LogDebug("[ResolveAttacker] No recent attacker found for RPG/LAW explosion.");
            }
        }
        #endif
        #ifdef EXPANSIONMODBASEBUILDING
        if (source.IsInherited(Expansion_C4_Explosion))
        {
            EntityAI placer;
            if (source.GetHierarchyRootPlayer())
                placer = source.GetHierarchyRootPlayer();
            else if (source.GetHierarchyParent())
                placer = source.GetHierarchyParent();
            ctx.Player = PlayerBase.Cast(placer);
            ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_EXPANSION_EXPLOSIVE;
            if (ctx.Player && ctx.Player.GetIdentity())
                NinjinsPvPPvE.LogDebug("[ResolveAttacker] C4 Explosion detected. Placer: " + ctx.Player.GetIdentity().GetName());
            else
                NinjinsPvPPvE.LogDebug("[ResolveAttacker] C4 Explosion detected. Placer: Unknown");
            return ctx;
        }
        #endif
        if (source.IsInherited(Grenade_Base) || source.IsInherited(TrapBase) || source.IsInherited(ExplosivesBase))
        {
            ctx.Player = GetThrowerOrPlacer(source);
            ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_EXPLOSIVE;
            return ctx;
        }
        if (source.IsWeapon() || source.IsMeleeWeapon())
        {
            EntityAI weapon = EntityAI.Cast(source);
            EntityAI wielder = weapon.GetHierarchyParent();
            ctx.Player = PlayerBase.Cast(wielder);
            #ifdef EXPANSIONMODAI
            if (wielder && wielder.IsInherited(eAIBase))
            {
                ctx.AI = eAIBase.Cast(wielder);
                ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_AI;
                return ctx;
            }
            #endif
            ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_WEAPON;
            return ctx;
        }
        if (source.IsInherited(CarScript))
        {
            CarScript car = CarScript.Cast(source);
            Human driver = Human.Cast(car.CrewMember(0));
            ctx.Player = PlayerBase.Cast(driver);
            ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_VEHICLE;
            return ctx;
        }
        ctx.DamageSourceType = NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_UNKNOWN;
        return ctx;
    }
    bool IsFireplaceExplosion(EntityAI source)
    {
        Grenade_Base grenade = Grenade_Base.Cast(source);
        if (grenade)
        {
            return grenade.IsFireplaceExplosion();
        }
        return false;
    }
    PlayerBase GetThrowerOrPlacer(EntityAI source)
    {
        PlayerBase player = null;
        if (source.IsInherited(Grenade_Base))
        {
            Grenade_Base grenade = Grenade_Base.Cast(source);
            player = grenade.GetThrower();
            if (!player)
                player = grenade.GetOwnerPlayer();
        }
        else if (source.IsInherited(TrapBase))
        {
            TrapBase trap = TrapBase.Cast(source);
            player = trap.GetPlayerThatPlaced();
            if (!player)
                player = trap.GetOwnerPlayer();
        }
        else if (source.IsInherited(ExplosivesBase))
        {
            ExplosivesBase explosive = ExplosivesBase.Cast(source);
            player = explosive.GetPlacer();
            if (!player)
                player = explosive.GetOwnerPlayer();
        }
        return player;
    }
    string GetDamageSourceTypeName(int damageSourceType)
    {
        switch (damageSourceType)
        {
            case NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_EXPLOSIVE: return "Explosive";
            case NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_EXPANSION_EXPLOSIVE: return "Expansion Explosive";
            case NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_WEAPON: return "Weapon";
            case NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_VEHICLE: return "Vehicle";
            case NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_FISTS: return "Fists";
            case NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_AI: return "AI";
            case NinjinsPvPPvE_DAMAGE_SOURCE_TYPE_UNKNOWN: return "Unknown";
        }
        return "Unknown";
    }
    void LogEntityContext(AttackerContext ctx, PlayerBase player, string prefix, string ammo = "", string dmgZone = "", string weapon = "", string damageSourceType = "")
    {
        if (ammo == "EnviroDmg" && damageSourceType == "Vehicle")
            return;
        string entityName = "Unknown";
        string zoneState = "N/A";
        if (ctx)
        {
            if (ctx.IsPlayer() && ctx.Player)
            {
                if (ctx.Player.GetIdentity())
                    entityName = ctx.Player.GetIdentity().GetName();
                else
                    entityName = ctx.Player.ToString();
                zoneState = GetZoneState(ctx.Player.netSync_IsInPvPZone, ctx.Player.netSync_IsInPvEZone, ctx.Player.netSync_IsInRaidMode);
            }
            #ifdef EXPANSIONMODAI
            else if (ctx.IsAI() && ctx.AI)
            {
                entityName = ctx.AI.ToString();
            }
            #endif
            else if (ctx.Source)
            {
                entityName = ctx.Source.GetType();
            }
        }
        else if (player)
        {
            if (player.GetIdentity())
                entityName = player.GetIdentity().GetName();
            else
                entityName = player.ToString();
            zoneState = GetZoneState(player.netSync_IsInPvPZone, player.netSync_IsInPvEZone, player.netSync_IsInRaidMode);
        }
        string log = prefix + " Name: " + entityName + ", State: " + zoneState;
        if (weapon != "")
            log += ", Weapon: " + weapon;
        if (ammo != "")
            log += ", Ammo: " + ammo;
        if (dmgZone != "")
            log += ", DmgZone: " + dmgZone;
        if (damageSourceType != "")
            log += ", DamageSourceType: " + damageSourceType;
        NinjinsPvPPvE.LogKillsDamage(log);
    }
    bool ShouldLog(AttackerContext ctx, PlayerBase victim)
    {
        if (!victim) 
            return false;
        bool attackerIsPlayer = ctx.IsPlayer() && ctx.Player != null;
        bool victimIsPlayer = victim.IsInherited(PlayerBase);
        #ifdef EXPANSIONMODAI
            bool attackerIsAI = ctx.IsAI() && ctx.AI != null;
            bool victimIsAI = victim.IsInherited(eAIBase);
        #else
            bool attackerIsAI = false;
            bool victimIsAI = false;
        #endif
        if (attackerIsPlayer && ctx.Player == victim)
            return false;
        if ((attackerIsPlayer && victimIsPlayer) || (attackerIsPlayer && victimIsAI) || (attackerIsAI && victimIsPlayer))
        {
            return true;
        }
        return false;
    }
    bool IsAllowedPaintballDamage(PlayerBase attacker, PlayerBase victim, string ammo, EntityAI source)
    {
        if (!g_ItemRules)
            return true;
        bool attackerPB = attacker && attacker.netSync_IsInPaintBallMode;
        bool victimPB   = victim   && victim.netSync_IsInPaintBallMode;
        if (!attackerPB && !victimPB)
            return true;
        bool whitelistedAmmo = (ammo != "" && g_ItemRules.AllowedAmmoInPaintBallState.Find(ammo) != -1) || (source && g_ItemRules.AllowedAmmoInPaintBallState.Find(source.GetType()) != -1);
        if (attackerPB && victimPB && whitelistedAmmo)
            return true;
        return false;
    }
}