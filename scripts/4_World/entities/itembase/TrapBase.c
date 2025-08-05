/*
    ============================================================================================
    =                               MODDED CLASS: TrapBase                                     =
    =  This modded TrapBase class tracks which player placed the trap, and prevents the trap    =
    =  from snapping on a victim if that victim is in a PvE state. Vehicle checks are also       =
    =  included                             =
    ============================================================================================
*/
modded class TrapBase
{
    private PlayerBase m_PlayerThatPlaced;
    override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
    {
        super.OnPlacementComplete(player, position, orientation);
        m_PlayerThatPlaced = PlayerBase.Cast(player);
    }
    PlayerBase GetPlayerThatPlaced()
    {
        return m_PlayerThatPlaced;
    }
    override void SnapOnObject(EntityAI victim)
    {
        bool allowSnap = false;
        if (g_ItemRules && g_ItemRules.AllowedAmmoInPvEState)
        {
            for (int i = 0; i < GetInventory().AttachmentCount(); i++)
            {
                ItemBase attachment = ItemBase.Cast(GetInventory().GetAttachmentFromIndex(i));
                if (attachment)
                {
                    foreach (string allowedClass : g_ItemRules.AllowedAmmoInPvEState)
                    {
                        if (attachment.IsKindOf(allowedClass))
                        {
                            allowSnap = true;
                            NinjinsPvPPvE.LogDebug("[TrapBase] Attachment (" + attachment.GetType() + ") matches allowed class (" + allowedClass + "), allowing snap.");
                            break;
                        }
                    }
                }
                if (allowSnap)
                    break;
            }
        }
        if (allowSnap)
        {
            super.SnapOnObject(victim);
            return;
        }
        PlayerBase playerVictim = PlayerBase.Cast(victim);
        if (playerVictim)
        {
            if (playerVictim.netSync_IsInPvEZone)
            {
                NinjinsPvPPvE.LogDebug("[TrapBase] PvE player detected, preventing trap snap.");
                return;
            }
        }
        else
        {
            CarScript vehicle = CarScript.Cast(victim);
            if (vehicle)
            {
                PlayerBase driver = PlayerBase.Cast(vehicle.CrewMember(DayZPlayerConstants.VEHICLESEAT_DRIVER));
                if (driver && driver.netSync_IsInPvEZone)
                {
                    NinjinsPvPPvE.LogDebug("[TrapBase] PvE driver detected in vehicle, preventing trap snap.");
                    return;
                }
            }
        }
        super.SnapOnObject(victim);
    }
    override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        bool handled = super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
        if (m_PlayerThatPlaced) 
            return handled;
        PlayerBase attacker = PlayerBase.Cast(source.GetHierarchyRootPlayer());
        if (attacker)
        {
            m_PlayerThatPlaced = attacker;
            if (attacker.GetIdentity())
                NinjinsPvPPvE.LogDebug("[TrapBase] Attacker resolved via hierarchy lookup & registered: " + attacker.GetIdentity().GetName());
            else
                NinjinsPvPPvE.LogDebug("[TrapBase] Attacker resolved via hierarchy lookup but has no Identity.");
        }
        return handled;
    }
};
