class Not_SmallStone_Base: Inventory_Base {};
modded class Not_SmallStone_Base
{
    override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        return false;
    }
    override bool CanPutInCargo(EntityAI parent)
    {
        return false;
    }
    override bool CanRemoveFromCargo(EntityAI parent)
    {
        return false;
    }
    override bool CanPutIntoHands(EntityAI parent)
    {
        return false;
    }
    override bool CanPutAsAttachment(EntityAI parent)
    {
        return false;
    }
};