#ifdef EXPANSIONMODCORE
modded class ExpansionWorld: ExpansionGame
{
    override void FirearmEffects(Object source,Object directHit,int componentIndex,string surface,vector pos,vector surfNormal,vector exitPos,vector inSpeed,vector outSpeed,bool isWater,bool deflected,string ammoType)
    {
        if (GetGame().IsServer())
        {
            if (source && source.ShootsExplosiveAmmo() && !deflected && outSpeed == vector.Zero && (ammoType == "ExpansionRocketRPG" || ammoType == "ExpansionRocketLAW"))
            {
                EntityAI entitySource = EntityAI.Cast(source);
                if (entitySource)
                {
                    EntityAI rootEntity = EntityAI.Cast(entitySource.GetHierarchyRoot());
                    if (rootEntity)
                    {
                        PlayerBase playerAttacker = PlayerBase.Cast(rootEntity);
                        if (playerAttacker)
                        {
                            AttackerUtils.SetRecentAttacker(playerAttacker);
                            PlayerIdentity attackerIdentity = playerAttacker.GetIdentity();
                            if (attackerIdentity)
                            {
                                NinjinsPvPPvE.LogDebug("[FirearmEffects] Recent attacker set: " + attackerIdentity.GetName());
                            }
                        }
                        else
                        {
                            NinjinsPvPPvE.LogDebug("[FirearmEffects] WARNING: No player attacker found for explosive shot!");
                        }
                    }
                }
            }
        }
        super.FirearmEffects(source, directHit, componentIndex, surface, pos, surfNormal, exitPos, inSpeed, outSpeed, isWater, deflected, ammoType);
    }
}
#endif
