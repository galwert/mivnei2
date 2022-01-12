#ifndef _SIVANS_GAME_H_
#define _SIVANS_GAME_H_

#include "UnionFind.h"
#include "Player.h"
#include "Group.h"


namespace Ehsan
{
    
    class SivansGame
    {
    public:
        int num_of_groups;
        int num_of_players;
        int scale;
        UnionFind<Group> *groups;
        RankTree<int,int> **players_by_scale;
        RankTree<int,int> *players_by_level;
        int level_zero_level;
        int *level_zero_scale;
        DynamicArray<Player> *players;

        SivansGame(int num_of_groups, int scale);
        ~SivansGame();

        Player *FindPlayer(int player_id);
        Group* FindGroup(int group_id);
        void AddPlayerHelper(int PlayerID, Group* player_group, int GroupID, int score);
        void RemovePlayerFromGroupHelper(Player* player,Group* player_group,int score,int level);
        void RemovePlayerFromSivanHelper(int PlayerID,int score,int level);
        void RemovePlayerFromOldLevelInSivan(Player* player);
        void RemovePlayerFromOldLevelInGroup(Player* player, Group* group);
        void AddPlayerToNewLevelInSivan(Player* player);
        void AddPlayerToNewLevelInGroup(Player* player, Group* group);
        void UpdateScoreInSivan(Player* player,int OldScore, int NewScore);
        void UpdateScoreInGroup(Player* player,Group* group,int OldScore, int NewScore);
        int GetNumberOfPlayersWithScoreInBounds(RankTree<int,int>** players_by_scale,int *level_zero_scale,int score, int lowerlevel, int higherlevel);
        SivansGame *InitGame(int k, int scale);
        StatusType MergeGroups(int GroupID1, int GroupID2);
        StatusType AddPlayer(int PlayerID, int GroupID, int score);
        StatusType RemovePlayer(int PlayerID);
        StatusType IncreasePlayerIDLevel(int PlayerID, int LevelIncrease);
        StatusType ChangePlayerIDScore(int PlayerID, int NewScore);
        StatusType GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,
                                                                                                 double * players);
        StatusType AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level);
        int GetNumberOfPlayersWithLevelsInBounds(RankTree<int, int> *levels_tree, int level_zero_level, int lowerlevel,
                                                 int higherlevel);
    };


} // namespace Ehsan

    // StatusType GetPlayersBound(int GroupID, int score, int m,
    //                                         int * LowerBoundPlayers, int * HigherBoundPlayers);
#endif