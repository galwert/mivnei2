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
        void AntiInOrderInTree(BSTNode<int,int>* root,BSTNode<int,int>* leftest_node,int level_zero,int *sum,int *num_of_players, int m);
        int GetNumberOfPlayersWithScoreInBounds(RankTree<int,int>** players_by_scale,int *level_zero_scale,int score, int lowerlevel, int higherlevel);
        int GetTotalNumberOfPlayersBounds(RankTree<int,int> *players_by_level, int lowerlevel, int higherlevel);
        StatusType GetPercentOfPlayersWithScoreInBoundsHelper(RankTree<int,int>** players_by_scale,RankTree<int,int> *players_level,
                                                                    int *levelzero_scale,int score,int lowerLevel,int higherLevel,double * players);
        SivansGame *InitGame(int k, int scale);
        StatusType MergeGroups(int GroupID1, int GroupID2);
        StatusType AddPlayer(int PlayerID, int GroupID, int score);
        StatusType RemovePlayer(int PlayerID);
        StatusType IncreasePlayerIDLevel(int PlayerID, int LevelIncrease);
        StatusType ChangePlayerIDScore(int PlayerID, int NewScore);
        StatusType GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,
                                                                                                 double * players);
        StatusType AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level);
        // StatusType GetPlayersBound(int GroupID, int score, int m,
        //                                         int * LowerBoundPlayers, int * HigherBoundPlayers);
        static void QuitGame(SivansGame* game);


        int GetNumberOfPlayersWithLevelsInBounds(RankTree<int, int> *levels_tree, int level_zero_level, int lowerlevel,
                                                 int higherlevel);
    };

    // SivansGame::SivansGame(int num_of_groups, int scale):
    // num_of_groups(num_of_groups),
    // scale(scale),
    // num_of_players(0),
    // groups( new UnionFind<Group>(num_of_groups,scale) ),
    // players_by_scale(new RankTree<int,int>*[scale+1]),
    // players_by_level(),
    // level_zero_level(0),
    // level_zero_scale( new int[scale+1]),
    // players(new DynamicArray<Player>(ARRAY_SIZE,BALANCE_FACTOR))
    // {
    //     for (int i = 1; i <= scale; i++) {
    //         level_zero_scale[i] = 0;
    //     }

    // }
    // SivansGame::~SivansGame()
    // {
    //     for(int i=1;i<=scale;i++)
    //     {
    //         delete players_by_scale[i];
    //     }
    //     delete[] level_zero_scale;
    //     delete groups; 
    //     delete players_by_level;
    //     delete players;
    // }

    


} // namespace Ehsan


#endif