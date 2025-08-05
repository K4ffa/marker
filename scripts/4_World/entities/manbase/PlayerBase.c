modded class PlayerBase
{
    bool netSync_IsInPvPZone = false;
    bool netSync_IsInPvEZone = false;
    bool netSync_IsInRaidMode = false;
    bool netSync_IsInSafeZone = false;
    bool netSync_IsInNoBuildZone = false;
    bool netSync_IsInPaintBallMode = false;
    bool netSync_IsInNoLogOutZone = false;
    bool netSync_ForceFirstPerson = false;
    bool netSync_ForceFirstPersonGlobalPvP = false;
    bool netSync_ForceFirstPersonGlobalPvE = false;
    vector m_LastKnownPosition;
    private bool lastForceFirstPerson = false;
    protected bool m_IsAdmin = false;
    protected vector m_NoLogOutTeleportPos = "0 0 0";
/*
---------------------------------------------------------------------------------------------
Getter + Helpers
---------------------------------------------------------------------------------------------
*/
    bool IsAdmin()
    {
        return m_IsAdmin;
    }
    bool IsDriver() 
    {
        Transport transport = Transport.Cast(GetParent());
        if (transport) 
        {
            int crewIndex = transport.CrewMemberIndex(this);
            return crewIndex == 0;
        }
        return false;
    }
    bool IsExplosiveOrGrenade(EntityAI source)
    {
        if (!source || !g_ItemRules || !g_ItemRules.PvEBlockedExplosivesDamage)
            return false;
        foreach (string className : g_ItemRules.PvEBlockedExplosivesDamage)
        {
            if (source.IsKindOf(className)) 
            {
                NinjinsPvPPvE.LogDebug("[PvE Block] Source " + source.GetType() + " is kind of " + className);
                return true;
            }
        }
        return false;
    }
    bool ShouldBypassActionBlock()
    {
        bool configAllows = g_MainConfig.DisableActionBlockForAdmins;
        bool isAdmin = IsAdmin();
        NinjinsPvPPvE.LogDebug("[ActionBlockCheck] DisableActionBlockForAdmins: " + configAllows + ", IsAdmin: " + isAdmin);
        return configAllows && isAdmin;
    }
    void SaveLastPosition()
    {
        m_LastKnownPosition = GetPosition();
    }
    void TeleportTo(vector newPos)
    {
        SetPosition(newPos);
    }
    void RemoveMostSignificantBleed()
    {
        if (GetBleedingManagerServer())
        {
            GetBleedingManagerServer().RemoveMostSignificantBleedingSource();
            NinjinsPvPPvE.LogDebug("[BleedCleanup] Most significant bleed removed.");
        }
    }
    void CleanupBleedDiseases()
    {
        if (GetGame().IsServer())
        {
            ModifiersManager modifiers = GetModifiersManager();
            if (modifiers)
            {
                bool wasActive1 = modifiers.IsModifierActive(eModifiers.MDF_WOUND_INFECTION1);
                bool wasActive2 = modifiers.IsModifierActive(eModifiers.MDF_WOUND_INFECTION2);
                if (wasActive1)
                {
                    modifiers.DeactivateModifier(eModifiers.MDF_WOUND_INFECTION1);
                    NinjinsPvPPvE.LogDebug("[ModifierCleanup] Removed MDF_WOUND_INFECTION1");
                }
                if (wasActive2)
                {
                    modifiers.DeactivateModifier(eModifiers.MDF_WOUND_INFECTION2);
                    NinjinsPvPPvE.LogDebug("[ModifierCleanup] Removed MDF_WOUND_INFECTION2");
                }
                if (!wasActive1 && !wasActive2)
                {
                    NinjinsPvPPvE.LogDebug("[ModifierCleanup] No wound infection modifiers were active.");
                }
            }
            if (m_AgentPool)
            {
                int woundAgentCount = GetSingleAgentCount(eAgents.WOUND_AGENT);
                if (woundAgentCount > 0)
                {
                    m_AgentPool.RemoveAgent(eAgents.WOUND_AGENT);
                    NinjinsPvPPvE.LogDebug("[AgentCleanup] Removed WOUND_AGENT. Count before removal: " + woundAgentCount);
                }
                else
                {
                    NinjinsPvPPvE.LogDebug("[AgentCleanup] No WOUND_AGENT present.");
                }
            }
        }
    }    
/*
---------------------------------------------------------------------------------------------
Admin status
---------------------------------------------------------------------------------------------
*/
    void SetAdminStatus(bool isAdmin)
    {
        m_IsAdmin = isAdmin;
        if (isAdmin)
        {
            NinjinsPvPPvE.LogDebug("[AdminStatus] Player " + GetIdentity().GetName() + " was granted admin status.");
        }
        else
        {
            NinjinsPvPPvE.LogDebug("[AdminStatus] Player " + GetIdentity().GetName() + " is not an admin.");
        }
    }
/*
---------------------------------------------------------------------------------------------
Anti-Logout related
---------------------------------------------------------------------------------------------
*/
    void SetNoLogOutTeleportPos(vector pos)
    {
        m_NoLogOutTeleportPos = pos;
    }
    vector GetNoLogOutTeleportPos()
    {
        return m_NoLogOutTeleportPos;
    }
    void TeleportToNoLogOutPos(PlayerIdentity id)
    {
        if ( !GetGame().IsServer() )
            return;
        if ( m_NoLogOutTeleportPos == "0 0 0" )
            return;
        SaveLastPosition();
        TeleportTo( m_NoLogOutTeleportPos );
        PlayerIdentity identity = GetIdentity();
        string playerName = "Player had no Identity anymore (Alt+4 or X out the Game? Or Client Crash.)";
        if (identity)
        {
            playerName = identity.GetName();
        }
        NinjinsPvPPvE.LogDebug("[NoLogOut] " + playerName +  " Teleported to " + m_NoLogOutTeleportPos.ToString());
        if ( id )
        {
            string msg = "You logged out inside a No-Log-Out zone.\n" + "You were moved to a safe spot - please reconnect.";
            Param1<string> payload = new Param1<string>( msg );
            GetGame().RPCSingleParam( this,NinjinCustomRPCs.RPC_FORCE_RELOG,payload, true, id );
        }
    }
    override void OnConnect()
    {
        super.OnConnect();
        if ( !GetGame().IsServer() )
            return;
        if ( !netSync_IsInNoLogOutZone )
            return;
        if ( g_MainConfig && g_MainConfig.AllowNoRelogOnServerCrash )
        {
            TeleportToNoLogOutPos( GetIdentity() );
        }
    }
    override void OnDisconnect()
    {
        super.OnDisconnect();
        if ( GetGame().IsServer() && netSync_IsInNoLogOutZone )
        {
            TeleportToNoLogOutPos( GetIdentity() );
        }
    }
/*
---------------------------------------------------------------------------------------------
Apply Unauthorized Raid Effects
---------------------------------------------------------------------------------------------
*/
    void ApplyUnauthorizedRaidBleeding()
    {
        PlayerIdentity identity = GetIdentity();
        string playerName = "Unknown";
        if (identity)
        {
            playerName = identity.GetName();
        }
        array<string> bleedingZones = { "Neck", "Pelvis" };
        foreach (string zoneName : bleedingZones)
        {
            if (GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(zoneName))
            {
                NinjinsPvPPvE.LogDebug("Bleeding source added: " + zoneName + " to player: " + playerName);
            }
            else
            {
                NinjinsPvPPvE.LogDebug("Failed to add bleeding source: " + zoneName + " to player: " + playerName);
            }
        }
    }
/*
---------------------------------------------------------------------------------------------
Force First Person
---------------------------------------------------------------------------------------------
*/
    bool IsForceFirstPerson() 
    {
        if (IsDriver() && g_MainConfig.ThirdPersonOnlyDriver == 1) 
        {
            return false;
        }
        if (netSync_ForceFirstPerson) 
        {
            return true;
        }
        if (netSync_ForceFirstPersonGlobalPvP || netSync_ForceFirstPersonGlobalPvE) 
        {
            return true;
        }
        return false;
    }
    void UpdateForceFirstPerson(bool force) 
    {
        PlayerIdentity identity = GetIdentity();
        string playerName = "Unknown";
        if (identity) 
        {
            playerName = identity.GetName();
        }
        if (netSync_ForceFirstPerson != force) 
        {
            netSync_ForceFirstPerson = force;
            NinjinsPvPPvE.LogDebug("ForceFirstPerson changed for " + playerName + ": " + force);
            SetSynchDirty();
        }
        if (GetGame().IsServer() && identity) 
        {
            Param1<bool> paramForce = new Param1<bool>(force);
            GetGame().RPCSingleParam(this, NinjinCustomRPCs.RPC_UPDATE_FORCE_FIRST_PERSON, paramForce, true, identity);
        }
    }
/*
---------------------------------------------------------------------------------------------
Update Players state  PvE/PvP/Raid/SZ/NoLogOut
---------------------------------------------------------------------------------------------
*/
    void UpdatePvPState(bool isInPvPZone)
    {
        PlayerIdentity identity = GetIdentity();
        string playerName = "Unknown";
        if (identity) 
        {
            playerName = identity.GetName();
        }
        if (netSync_IsInPvPZone != isInPvPZone) 
        {
            netSync_IsInPvPZone = isInPvPZone;
            NinjinsPvPPvE.LogDebug("PvP Mode state changed for " + playerName + ": " + isInPvPZone);
            SetSynchDirty();
        }
        if (GetGame().IsServer() && identity) 
        {
            Param1<bool> paramPVP = new Param1<bool>(isInPvPZone);
            GetGame().RPCSingleParam(this, NinjinCustomRPCs.RPC_UPDATE_PVP_STATE, paramPVP, true, identity);
        }
    }
    void UpdatePvEState(bool isInPvEZone)
    {
        PlayerIdentity identity = GetIdentity();
        string playerName = "Unknown";
        if (identity) 
        {
            playerName = identity.GetName();
        }
        if (netSync_IsInPvEZone != isInPvEZone) 
        {
            netSync_IsInPvEZone = isInPvEZone;
            NinjinsPvPPvE.LogDebug("PvE Mode state changed for " + playerName + ": " + isInPvEZone);
            SetSynchDirty();
        }
        if (GetGame().IsServer() && identity) 
        {
            Param1<bool> paramPvE = new Param1<bool>(isInPvEZone);
            GetGame().RPCSingleParam(this, NinjinCustomRPCs.RPC_UPDATE_PVE_STATE, paramPvE, true, identity);
        }
    }
    void UpdateRaidMode(bool isInRaidMode)
    {
        PlayerIdentity identity = GetIdentity();
        string playerName = "Unknown";
        if (identity) 
        {
            playerName = identity.GetName();
        }
        if (netSync_IsInRaidMode != isInRaidMode) 
        {
            netSync_IsInRaidMode = isInRaidMode;
            NinjinsPvPPvE.LogDebug("Raid Mode state changed for " + playerName + ": " + isInRaidMode);
            SetSynchDirty();
        }
        if (GetGame().IsServer() && identity) 
        {
            Param1<bool> paramRaid = new Param1<bool>(isInRaidMode);
            GetGame().RPCSingleParam(this, NinjinCustomRPCs.RPC_UPDATE_RAID_MODE, paramRaid, true, identity);
        }
    }
    void UpdateSafeZoneState(bool isInSafeZone)
    {
        PlayerIdentity identity = GetIdentity();
        string playerName = "Unknown";
        if (identity) 
        {
            playerName = identity.GetName();
        }
        if (netSync_IsInSafeZone != isInSafeZone) 
        {
            netSync_IsInSafeZone = isInSafeZone;
            NinjinsPvPPvE.LogDebug("SafeZone state changed for " + playerName + ": " + isInSafeZone);
            SetSynchDirty();
        }
        if (GetGame().IsServer() && identity) 
        {
            Param1<bool> paramSafeZone = new Param1<bool>(isInSafeZone);
            GetGame().RPCSingleParam(this, NinjinCustomRPCs.RPC_UPDATE_SAFEZONE_STATE, paramSafeZone, true, identity);
        }
    }
    void UpdateNoLogOutState(bool isInNoLogOutZone)
    {
        PlayerIdentity identity = GetIdentity();
        string playerName;
        if (identity)
            playerName = identity.GetName();
        else
            playerName = "Unknown";
        if (netSync_IsInNoLogOutZone != isInNoLogOutZone)
        {
            netSync_IsInNoLogOutZone = isInNoLogOutZone;
            NinjinsPvPPvE.LogDebug("NoLogOut state changed for " + playerName + ": " + isInNoLogOutZone);
            SetSynchDirty();
        }
        if (GetGame().IsServer() && identity)
        {
            Param1<bool> p = new Param1<bool>(isInNoLogOutZone);
            GetGame().RPCSingleParam(this, NinjinCustomRPCs.RPC_UPDATE_NOLOGOUT_STATE, p, true, identity);
        }
    }
    void UpdatePaintBallMode(bool isInPaintBallMode)
    {
        PlayerIdentity identity = GetIdentity();
        string playerName;
        if (identity)
            playerName = identity.GetName();
        else
            playerName = "Unknown";
        if (netSync_IsInPaintBallMode != isInPaintBallMode)
        {
            netSync_IsInPaintBallMode = isInPaintBallMode;
            NinjinsPvPPvE.LogDebug("PaintBallMode state changed for " + playerName + ": " + isInPaintBallMode);
            SetSynchDirty();
        }
        if (GetGame().IsServer() && identity)
        {
            Param1<bool> paramPaint = new Param1<bool>(isInPaintBallMode);
            GetGame().RPCSingleParam(this, NinjinCustomRPCs.RPC_UPDATE_PAINTBALL_MODE, paramPaint, true, identity);
        }
    }
/*
---------------------------------------------------------------------------------------------
No Build Related
---------------------------------------------------------------------------------------------
*/
    void UpdateNoBuildState(bool isInNoBuild)
    {
        PlayerIdentity id = GetIdentity();
        string pname;
        if (id)
            pname = id.GetName();
        else
            pname = "Unknown";
        if (netSync_IsInNoBuildZone != isInNoBuild)
        {
            netSync_IsInNoBuildZone = isInNoBuild;
            NinjinsPvPPvE.LogDebug("NoBuild state changed for " + pname + ": " + isInNoBuild);
            SetSynchDirty();
        }
        if (GetGame().IsServer() && id)
        {
            Param1<bool> p = new Param1<bool>(isInNoBuild);
            GetGame().RPCSingleParam(this, NinjinCustomRPCs.RPC_UPDATE_NOBUILD_STATE, p, true, id);
        }
    }
/*
---------------------------------------------------------------------------------------------
OnRPC - to controll custom RPCs for updating states
---------------------------------------------------------------------------------------------
*/
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) 
    {
        super.OnRPC(sender, rpc_type, ctx);
        switch (rpc_type) 
        {
            case NinjinCustomRPCs.RPC_UPDATE_NOBUILD_STATE:
            {
                Param1<bool> nbd;
                if (ctx.Read(nbd))
                {
                    netSync_IsInNoBuildZone = nbd.param1;
                    SetSynchDirty();
                }
                break;
            }
            case NinjinCustomRPCs.RPC_UPDATE_PAINTBALL_MODE:
            {
                Param1<bool> paramPaint;
                if (ctx.Read(paramPaint))
                {
                    netSync_IsInPaintBallMode = paramPaint.param1;
                    NinjinsPvPPvE.LogDebug("[PlayerBase][Client] PaintBallMode state changed: " + netSync_IsInPaintBallMode);
                    SetSynchDirty();
                }
                break;
            }
            case NinjinCustomRPCs.RPC_UPDATE_NOLOGOUT_STATE:
            {
                Param1<bool> paramNoLog;
                if (ctx.Read(paramNoLog))
                {
                    netSync_IsInNoLogOutZone = paramNoLog.param1;
                    NinjinsPvPPvE.LogDebug("[PlayerBase][Client] NoLogOut state changed: " + netSync_IsInNoLogOutZone);
                    SetSynchDirty();
                }
                break;
            }
            case NinjinCustomRPCs.RPC_UPDATE_PVP_STATE: {
                Param1<bool> paramPVP;
                if (ctx.Read(paramPVP)) 
                {
                    if (netSync_IsInPvPZone != paramPVP.param1) 
                    {
                        netSync_IsInPvPZone = paramPVP.param1;
                        NinjinsPvPPvE.LogDebug("[PlayerBase][Client] PvP state changed: " + netSync_IsInPvPZone);
                        SetSynchDirty();
                    }
                }
                break;
            }
            case NinjinCustomRPCs.RPC_UPDATE_PVE_STATE: {
                Param1<bool> paramPvE;
                if (ctx.Read(paramPvE)) 
                {
                    if (netSync_IsInPvEZone != paramPvE.param1) 
                    {
                        netSync_IsInPvEZone = paramPvE.param1;
                        NinjinsPvPPvE.LogDebug("[PlayerBase][Client] PvE state changed: " + netSync_IsInPvEZone);
                        SetSynchDirty();
                    }
                }
                break;
            }
            case NinjinCustomRPCs.RPC_UPDATE_RAID_MODE: {
                Param1<bool> paramRaid;
                if (ctx.Read(paramRaid)) 
                {
                    if (netSync_IsInRaidMode != paramRaid.param1) 
                    {
                        netSync_IsInRaidMode = paramRaid.param1;
                        NinjinsPvPPvE.LogDebug("[PlayerBase][Client] Raid Mode state changed: " + netSync_IsInRaidMode);
                        SetSynchDirty();
                    }
                }
                break;
            }
            case NinjinCustomRPCs.RPC_UPDATE_SAFEZONE_STATE:
            {
                Param1<bool> paramSafeZone;
                if (ctx.Read(paramSafeZone)) 
                {
                    netSync_IsInSafeZone = paramSafeZone.param1;
                }
                break;
            }
            case NinjinCustomRPCs.RPC_UPDATE_FORCE_FIRST_PERSON: 
            {
                Param1<bool> paramForce;
                if (ctx.Read(paramForce)) 
                {
                    if (netSync_ForceFirstPerson != paramForce.param1) 
                    {
                        netSync_ForceFirstPerson = paramForce.param1;
                        NinjinsPvPPvE.LogDebug("[PlayerBase][Client] Zone-Based ForceFirstPerson state changed: " + netSync_ForceFirstPerson);
                        SetSynchDirty();
                    }
                }
                break;
            }
            case NinjinCustomRPCs.RPC_UPDATE_FORCE_FIRST_PERSON_GLOBAL_PVP: {
                Param1<bool> paramForceGlobalPvP;
                if (ctx.Read(paramForceGlobalPvP)) 
                {
                    if (netSync_ForceFirstPersonGlobalPvP != paramForceGlobalPvP.param1) 
                    {
                        netSync_ForceFirstPersonGlobalPvP = paramForceGlobalPvP.param1;
                        NinjinsPvPPvE.LogDebug("[PlayerBase][Client] Global PvP ForceFirstPerson state changed: " + netSync_ForceFirstPersonGlobalPvP);
                        SetSynchDirty();
                    }
                }
                break;
            }
            case NinjinCustomRPCs.RPC_UPDATE_FORCE_FIRST_PERSON_GLOBAL_PVE: 
            {
                Param1<bool> paramForceGlobalPvE;
                if (ctx.Read(paramForceGlobalPvE)) 
                {
                    if (netSync_ForceFirstPersonGlobalPvE != paramForceGlobalPvE.param1) 
                    {
                        netSync_ForceFirstPersonGlobalPvE = paramForceGlobalPvE.param1;
                        NinjinsPvPPvE.LogDebug("[PlayerBase][Client] Global PvE ForceFirstPerson state changed: " + netSync_ForceFirstPersonGlobalPvE);
                        SetSynchDirty();
                    }
                }
                break;
            }
        }
    }
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        if (!IsPlayer() || !GetIdentity()) 
            return;
        vector deathPos = GetPosition();
        string playerName = GetIdentity().GetName();
        string state = "No Active state";
        if (netSync_IsInPvPZone) state = "In PvP";
        else if (netSync_IsInPvEZone) 
            state = "In PvE";
        else if (netSync_IsInRaidMode) 
            state = "In Raid";
        else if (netSync_IsInSafeZone) 
            state = "In SafeZone";
        DamageUtils dmgUtils = DamageUtils.GetInstance();
        AttackerContext ctx = dmgUtils.ResolveAttacker(EntityAI.Cast(killer));
        dmgUtils.GrenadeAttackerContext(ctx, EntityAI.Cast(killer));
        string killerInfo = "Unknown";
        bool selfKill = false;
        if (ctx.IsPlayer() && ctx.Player)
        {
            if (ctx.Player == this)
            {
                selfKill = true;
                killerInfo = "Self-Inflicted";
            }
            else if (ctx.Player.GetIdentity())
            {
                killerInfo = ctx.Player.GetIdentity().GetName();
            }
        }
        else if (ctx.Source)
        {
            killerInfo = ctx.Source.GetType();
        }
        if (selfKill)
        {
            NinjinsPvPPvE.LogKillsDamage("[DEATH] Player: " + playerName + " died (self-inflicted) at position: " + deathPos.ToString() + ", state: " + state);
        }
        else
        {
            NinjinsPvPPvE.LogKillsDamage("[DEATH] Player: " + playerName + " was killed by " + killerInfo + " at position: " + deathPos.ToString() + ", state: " + state);
        }
    }
    override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        if (!IsAlive() || (GetGame().IsMultiplayer() && !GetGame().IsServer()))
            return true;
        if (this.netSync_IsInSafeZone)
        {
            return false;
        }
        DamageUtils dmgUtils = DamageUtils.GetInstance();
        AttackerContext ctx = dmgUtils.ResolveAttacker(source);
        dmgUtils.GrenadeAttackerContext(ctx, source);
        bool allowDamage = dmgUtils.ShouldAllowDamage(this, damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
        if (g_ItemRules)
        {
            if (ammo != "" && g_ItemRules.AllowedAmmoInPvEState.Find(ammo) != -1)
            {
                NinjinsPvPPvE.LogDebug("[PvE Allow] Ammo allowed inside PvE: " + ammo);
                return true;
            }
            if (source && g_ItemRules.AllowedAmmoInPvEState.Find(source.GetType()) != -1)
            {
                NinjinsPvPPvE.LogDebug("[PvE Allow] Source entity allowed inside PvE: " + source.GetType());
                return true;
            }
        }
        #ifdef EXPANSIONMODAI
        if (IsInherited(eAIBase))
        {
            ZoneManager zm = ZoneManager.GetInstance();
            if (ctx && ctx.IsAI() && ctx.AI && zm.IsPositionInZone(ctx.AI.GetPosition(), ZONE_TYPE_SAFEZONE))
            {
                NinjinsPvPPvE.LogKillsDamage("[SAFEZONE] Blocked AI vs AI damage inside SafeZone.");
                return false;
            }
        }
        #endif
        if (dmgUtils.ShouldLog(ctx, this))
        {
            string attackerInfo = "Unknown Attacker";
            #ifdef EXPANSIONMODAI
            if (ctx.AI)
            {
                attackerInfo = "AI Attacker: " + ctx.AI.ToString();
            }
            #endif
            if (ctx.Player && ctx.Player.GetIdentity())
            {
                attackerInfo = "Player Attacker: " + ctx.Player.GetIdentity().GetName();
            }
            string victimInfo;
            PlayerIdentity victimIdentity = GetIdentity();
            if (victimIdentity)
            {
                victimInfo = "Player: " + victimIdentity.GetName();
            }
            #ifdef EXPANSIONMODAI
            else if (IsInherited(eAIBase))
            {
                victimInfo = "AI Entity: " + GetType();
            }
            #endif
            else
            {
                victimInfo = "Unknown victim: " + GetType();
            }
            if (!allowDamage)
            {
                bool isBoltAmmo = DamageUtils.GetInstance().BoltAmmoTypes.Find(ammo) != -1;
                bool isInPvE = this.netSync_IsInPvEZone;
                if (isBoltAmmo && isInPvE)
                {   
                    NinjinsPvPPvE.LogDebug("[BleedCleanup] Scheduling bleed and disease cleanup due to bolt hit in PvE. Ammo: " + ammo);
                    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.RemoveMostSignificantBleed, 100, false);
                    GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CleanupBleedDiseases, 1000, false);
                }
                NinjinsPvPPvE.LogDebug(" [PlayerBase][DamageUtils] Damage DENIED:");
                NinjinsPvPPvE.LogDebug(" Victim: " + victimInfo);
                NinjinsPvPPvE.LogDebug(" Attacker: " + attackerInfo);
                NinjinsPvPPvE.LogDebug(" DamageType: " + damageType.ToString());
                NinjinsPvPPvE.LogDebug(" Ammo: " + ammo);
                string sourceType;
                if (source)
                    sourceType = source.GetType();
                else
                    sourceType = "null";
                NinjinsPvPPvE.LogDebug(" Source: " + sourceType);
                NinjinsPvPPvE.LogDebug(" Component: " + component.ToString());
                NinjinsPvPPvE.LogDebug(" DamageZone: " + dmgZone);
                NinjinsPvPPvE.LogDebug(" SpeedCoef: " + speedCoef.ToString());
                return false;
            }
            else
            {
                NinjinsPvPPvE.LogDebug(" [PlayerBase][DamageUtils] Damage allowed to " + victimInfo + " from " + attackerInfo);
            }
        }
        return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
    }
}
