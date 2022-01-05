//
// Created by galwe on 05/01/2022.
//

#ifndef MAIN_CPP_PLAYERSMANAGER_H
#define MAIN_CPP_PLAYERSMANAGER_H

#include "UnionFind.h"
#include "DynamicArray.h"

#include "Group.h"
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;
namespace Ehsan {

    class PlayersManager {

    public:
        UnionFind<Group> groups;
        DynamicArray<Player> players;
        RankTree<Player,int>* players_by_scale;
        RankTree<Player,int> players_by_rank;
        void *Init(int k, int scale);

        StatusType MergeGroups(void *DS, int GroupID1, int GroupID2);

        StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score);

        StatusType RemovePlayer(void *DS, int PlayerID);

        StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease);

        StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore);

        StatusType
        GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                             double *players);

        StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double *level);

        StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                                   int *LowerBoundPlayers, int *HigherBoundPlayers);

        void Quit(void **DS);
    };

}
#endif //MAIN_CPP_PLAYERSMANAGER_H
