class NoVehicleZoneEnforcer
{
    ref map<PlayerBase, float> m_PlayerEntryTimes;
    float m_GracePeriod;
    ref array<PlayerBase> m_TrackedPlayers;
    ref array<string> m_DisallowedVehicles;
    ref array<string> m_DamageZoneParts;
    ref array<string> m_AttachmentParts;
    ref array<string> m_CargoParts;
    void NoVehicleZoneEnforcer()
    {
        m_PlayerEntryTimes = new map<PlayerBase, float>;
        m_TrackedPlayers = new array<PlayerBase>;
        if (g_MainConfig)
        {
            m_GracePeriod = g_MainConfig.NoVehicleZoneKillOrDestroyDelay * 1000;
            m_DamageZoneParts = g_MainConfig.DestroyVehicleParts;
            m_AttachmentParts = g_MainConfig.RemoveVehicleAttachments;
            m_CargoParts = g_MainConfig.DestroyVehicleCargo;
        }
        if (g_ItemRules)
        {
            m_DisallowedVehicles = g_ItemRules.DisallowedVehicles;
        }
        if (!m_DisallowedVehicles || m_DisallowedVehicles.Count() == 0)
        {
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] No DisallowedVehicles found.");
        }
        else
        {
            for (int i = 0; i < m_DisallowedVehicles.Count(); i++)
            {
                NinjinsPvPPvE.LogDebug("[" + i + "]: " + m_DisallowedVehicles.Get(i));
            }
        }
        if (GetGame())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(Update, 1000, true);
        }
    }
    void ~NoVehicleZoneEnforcer()
    {  
        if (GetGame())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(Update);
        }
        foreach (PlayerBase player : m_TrackedPlayers)
        {
            RemoveWarningEffect(player);
            HideTextWarningEffect(player);
        }
        m_TrackedPlayers.Clear();
        m_PlayerEntryTimes.Clear();
    }

    void ApplyWarningEffect(PlayerBase player)
    {
        if (player && player.GetIdentity() && GetRPCManager() && g_MainConfig)
        {
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ApplyVehicleWarningEffect", null, true, player.GetIdentity());
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Warning effect applied to player " + player.GetIdentity().GetName() + " with intensity: " + g_MainConfig.NoVehicleWarningEffectIntensity);
        }
    }
    void RemoveWarningEffect(PlayerBase player)
    {
        if (player && player.GetIdentity() && GetRPCManager())
        {
            GetRPCManager().SendRPC("NinjinsPvPPvE", "RemoveVehicleWarningEffect", null, true, player.GetIdentity());
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Warning effect removed for player " + player.GetIdentity().GetName());
        }
    }
    void ShowTextWarningEffect(PlayerBase player)
    {
        if (player && player.GetIdentity() && GetRPCManager() && g_MainConfig)
        {
            float remainingTime = 0;
            if (m_PlayerEntryTimes.Contains(player))
            {
                float enteredAt = m_PlayerEntryTimes.Get(player);
                float elapsed = GetGame().GetTime() - enteredAt;
                if (elapsed < m_GracePeriod)
                {
                    remainingTime = Math.Ceil((m_GracePeriod - elapsed) / 1000);
                }
            }
            string warningText = g_MainConfig.NoVehicleWarningText;
            warningText.Replace("{countdown}", remainingTime.ToString());
            Param1<string> msg = new Param1<string>(warningText);
            GetRPCManager().SendRPC("NinjinsPvPPvE", "ShowNoVehicleWarning", msg, true, player.GetIdentity());
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Showing NoVehicleWarning UI with countdown for player " + player.GetIdentity().GetName());
        }
    }
    void HideTextWarningEffect(PlayerBase player)
    {
        if (player && player.GetIdentity() && GetRPCManager())
        {
            GetRPCManager().SendRPC("NinjinsPvPPvE", "HideNoVehicleWarning", null, true, player.GetIdentity());
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Hiding NoVehicleWarning UI for player " + player.GetIdentity().GetName());
        }
    }
    void UpdateMainConfigSettings()
    {
        if (!g_MainConfig)
            return;
        m_GracePeriod = g_MainConfig.NoVehicleZoneKillOrDestroyDelay * 1000;
        m_PlayerEntryTimes.Clear();
        m_DamageZoneParts = g_MainConfig.DestroyVehicleParts;
        m_AttachmentParts = g_MainConfig.RemoveVehicleAttachments;
        m_CargoParts = g_MainConfig.DestroyVehicleCargo;
        NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Main config updated: grace period = " + m_GracePeriod.ToString());
    }
    void UpdateItemRulesSettings()
    {
        if (g_ItemRules)
        {
            m_DisallowedVehicles = g_ItemRules.DisallowedVehicles;
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Item rules updated: disallowed vehicles = " + m_DisallowedVehicles.ToString());
        }
    }
    void OnPlayerGetInTransport(PlayerBase player)
    {
        if (player && player.GetIdentity() && m_TrackedPlayers.Find(player) == -1)
        {
            m_TrackedPlayers.Insert(player);
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Added player " + player.GetIdentity().GetName() + " for tracking disallowed vehicles.");
        }
    }
    void OnPlayerExitTransport(PlayerBase player)
    {
        if (player && player.GetIdentity() && m_TrackedPlayers.Find(player) != -1)
        {
            m_TrackedPlayers.RemoveItem(player);
            m_PlayerEntryTimes.Remove(player);
            RemoveWarningEffect(player);
            HideTextWarningEffect(player);
            NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Removed player " + player.GetIdentity().GetName() + " from tracking.");
        }
    }
    void DestroyVehiclePartsAndAttachments(Transport vehicle)
    {
        if (!vehicle)
            return;
        CarScript car;
        bool hasDamageZones = CarScript.CastTo(car, vehicle);
        if (m_DamageZoneParts && hasDamageZones)
        {
            foreach (string dmgPart : m_DamageZoneParts)
            {
                array<string> compNames = new array<string>;
                if (DamageSystem.GetComponentNamesFromDamageZone(car, dmgPart, compNames) && compNames.Count() > 0)
                {
                    float zoneHealth = car.GetHealth01(dmgPart, "");
                    if (zoneHealth >= 0)
                    {
                        car.SetHealth(dmgPart, "", 0);
                        NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Destroyed damage zone: " + dmgPart);
                    }
                }
            }
        }
        if (m_AttachmentParts)
        {
            foreach (string attPart : m_AttachmentParts)
            {
                array<EntityAI> attachmentsToProcess = new array<EntityAI>;
                EntityAI attachment = vehicle.FindAttachmentBySlotName(attPart);
                if (attachment)
                {
                    attachmentsToProcess.Insert(attachment);
                }
                array<EntityAI> allAttachments = new array<EntityAI>;
                vehicle.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, allAttachments);
                InventoryLocation loc = new InventoryLocation;
                foreach (EntityAI currentAttachment : allAttachments)
                {
                    if (currentAttachment.GetInventory().GetCurrentInventoryLocation(loc) && loc.GetType() != InventoryLocationType.CARGO && currentAttachment.GetType().Contains(attPart))
                    {
                        if (attachmentsToProcess.Find(currentAttachment) == -1)
                        {
                            attachmentsToProcess.Insert(currentAttachment);
                        }
                    }
                }
                foreach (EntityAI processedAttachment : attachmentsToProcess)
                {
                    if (!processedAttachment.IsRuined())
                    {
                        processedAttachment.Delete();
                        NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Removed attachment: " + processedAttachment.GetType());
                    }
                }
            }
        }
        if (m_CargoParts)
        {
            array<EntityAI> cargoItems = new array<EntityAI>;
            vehicle.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, cargoItems);
            InventoryLocation invLoc = new InventoryLocation;
            foreach (EntityAI item : cargoItems)
            {
                if (item && !item.IsRuined() && item.GetInventory().GetCurrentInventoryLocation(invLoc))
                {
                    if (invLoc.GetType() == InventoryLocationType.CARGO && m_CargoParts.Find(item.GetType()) != -1)
                    {
                        item.SetHealth(0);
                        NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Destroyed cargo attachment: " + item.GetType());
                    }
                }
            }
        }
    }
    void Update()
    {
        float currentTime = GetGame().GetTime();
        ZoneManager zoneManager = ZoneManager.GetInstance();
        if (!zoneManager || !m_DisallowedVehicles || m_DisallowedVehicles.Count() == 0)
            return;
        for (int i = m_TrackedPlayers.Count() - 1; i >= 0; i--)
        {
            PlayerBase player = m_TrackedPlayers[i];
            if (!player)
            {
                m_TrackedPlayers.Remove(i);
                continue;
            }
            Transport vehicle = Transport.Cast(player.GetParent());
            if (!vehicle)
            {
                OnPlayerExitTransport(player);
                continue;
            }
            string vehicleType = vehicle.GetType();
            bool isDisallowed = false;
            foreach (string disallowedType : m_DisallowedVehicles)
            {
                typename disallowedTypename = disallowedType.ToType();
                if ((disallowedTypename && vehicle.IsInherited(disallowedTypename)) || vehicleType == disallowedType)
                {
                    isDisallowed = true;
                    break;
                }
            }
            if (!isDisallowed)
            {
                OnPlayerExitTransport(player);
                continue;
            }
            vector pos = player.GetPosition();
            bool inRestrictedZone = false;
            foreach (ZoneBase zone : zoneManager.m_Zones)
            {
                if (zone.UsesDisallowedVehicles && zone.IsInside(pos))
                {
                    inRestrictedZone = true;
                    break;
                }
            }
            if (!inRestrictedZone)
            {
                foreach (ZoneBase dynamicZone : zoneManager.m_DynamicZones)
                {
                    if (dynamicZone.UsesDisallowedVehicles && dynamicZone.IsInside(pos))
                    {
                        inRestrictedZone = true;
                        break;
                    }
                }
            }
            if (inRestrictedZone)
            {
                if (!m_PlayerEntryTimes.Contains(player))
                {
                    m_PlayerEntryTimes.Insert(player, currentTime);
                    NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Recorded entry time for " + player.GetIdentity().GetName());                
                    ApplyWarningEffect(player);
                    ShowTextWarningEffect(player);
                }
                else
                {
                    float entryTime = m_PlayerEntryTimes.Get(player);
                    float elapsed = currentTime - entryTime;
                    if (elapsed >= m_GracePeriod)
                    {
                        RemoveWarningEffect(player);
                        HideTextWarningEffect(player);
                        switch (g_MainConfig.NoVehicleKillPlayerOrDestroyVehicle)
                        {
                            case NFZA_DESTROY_VEHICLE:
                                DestroyVehiclePartsAndAttachments(vehicle);
                                NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Vehicle partially destroyed for " + player.GetIdentity().GetName());
                                break;
                            case NFZA_DELETE_VEHICLE:
                                vehicle.Delete();
                                NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Entire vehicle deleted for " + player.GetIdentity().GetName());
                                break;
                            case NFZA_KILL:
                            default:
                                player.SetHealth(0);
                                NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Player " + player.GetIdentity().GetName() + " killed for vehicle violation.");
                                break;
                        }
                        m_PlayerEntryTimes.Remove(player);
                        m_TrackedPlayers.Remove(i);
                    }
                    else
                    {          
                        ApplyWarningEffect(player);
                        ShowTextWarningEffect(player);
                    }
                }
            }
            else if (m_PlayerEntryTimes.Contains(player))
            {
                m_PlayerEntryTimes.Remove(player);
                RemoveWarningEffect(player);
                HideTextWarningEffect(player);
                NinjinsPvPPvE.LogDebug("[NoVehicleZoneEnforcer] Player " + player.GetIdentity().GetName() + " exited NoVehicleZone.");
            }
        }
    }
}
