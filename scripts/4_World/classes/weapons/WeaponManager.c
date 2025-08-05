modded class WeaponManager
{
    override bool CanFire(Weapon_Base wpn)
    {
        PlayerBase player = PlayerBase.Cast(wpn.GetHierarchyRootPlayer());
        if (player)
        {
            if (player.netSync_IsInSafeZone)
            {
                return false;
            }
        }
        return super.CanFire(wpn);
    }
}
