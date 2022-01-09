#include "SivansGame.h"
#include "library2.h"


using namespace Ehsan;


void *Init(int k, int scale)
{
    return (static_cast<void*>(new SivansGame(k,scale))); 
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<SivansGame*>(DS)->MergeGroups(GroupID1,GroupID2));
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<SivansGame*>(DS)->AddPlayer(PlayerID,GroupID,score));

}

StatusType RemovePlayer(void *DS, int PlayerID)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<SivansGame*>(DS)->RemovePlayer(PlayerID));
}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<SivansGame*>(DS)->IncreasePlayerIDLevel(PlayerID,LevelIncrease));
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<SivansGame*>(DS)->ChangePlayerIDScore(PlayerID,NewScore));
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                            double * players)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<SivansGame*>(DS)->GetPercentOfPlayersWithScoreInBounds(GroupID,score,lowerLevel,higherLevel,players));
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<SivansGame*>(DS)->AverageHighestPlayerLevelByGroup(GroupID,m,level));
}

StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                                         int * LowerBoundPlayers, int * HigherBoundPlayers)
{
    return SUCCESS;
}

void Quit(void** DS)
{
    if (DS == NULL || (*DS) == NULL)
    {
        return;
    }
    SivansGame::QuitGame(static_cast<SivansGame*>(*DS));
}