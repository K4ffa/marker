class AttackerUtils
{
    private static PlayerBase s_RecentAttacker;
/*
-------------------------------------------------------------------------------------
SetRecentAttacker - Sets the player as the recent attacker - Used for Expansion RPG Stuff
-------------------------------------------------------------------------------------
*/
    static void SetRecentAttacker(PlayerBase attacker)
    {
        if (!attacker)
        {
            NinjinsPvPPvE.LogWarning("Attempted to set a null attacker.");
            return;
        }
        s_RecentAttacker = attacker;
        if (attacker.GetIdentity())
        {
            NinjinsPvPPvE.LogDebug("Recent attacker set: " + attacker.GetIdentity().GetName());
        }
        else
        {
            NinjinsPvPPvE.LogDebug("Recent attacker set: No Identity");
        }
    }
/*
-------------------------------------------------------------------------------------
GetRecentAttacker - Retrieves the most recently set attacker - Used for Expansion RPG Stuff
-------------------------------------------------------------------------------------
*/
    static PlayerBase GetRecentAttacker()
    {
        if (s_RecentAttacker)
        {
            if (s_RecentAttacker.GetIdentity())
            {
                NinjinsPvPPvE.LogDebug("Returning recent attacker: " + s_RecentAttacker.GetIdentity().GetName());
            }
            else
            {
                NinjinsPvPPvE.LogDebug("Returning recent attacker: No Identity");
            }
        }
        else
        {
            NinjinsPvPPvE.LogDebug("No recent attacker available.");
        }
        return s_RecentAttacker;
    }
/*
-------------------------------------------------------------------------------------
ClearRecentAttacker - Clears the stored attacker reference - Used for Expansion RPG Stuff
-------------------------------------------------------------------------------------
*/
    static void ClearRecentAttacker()
    {
        if (s_RecentAttacker)
        {
            if (s_RecentAttacker.GetIdentity())
            {
                NinjinsPvPPvE.LogDebug("[AttackerUtils] Clearing recent attacker: " + s_RecentAttacker.GetIdentity().GetName());
            }
            else
            {
                NinjinsPvPPvE.LogDebug("[AttackerUtils] Clearing recent attacker: No Identity found.");
            }
            s_RecentAttacker = null;
        }
        else
        {
            NinjinsPvPPvE.LogDebug("[AttackerUtils] No recent attacker to clear.");
        }
    }
}