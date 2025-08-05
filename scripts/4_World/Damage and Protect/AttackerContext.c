class AttackerContext
{
    EntityAI Source;
    PlayerBase Player;
    #ifdef EXPANSIONMODAI
    eAIBase AI;
    #endif
    int DamageSourceType;
    string EntityName;
    bool IsPlayer() 
    {
        return Player != NULL; 
    }
    #ifdef EXPANSIONMODAI
    bool IsAI() 
    {
        return AI != NULL; 
    }
    #endif
}
