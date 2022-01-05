#ifndef _SIVANS_GAME_H_
#define _SIVANS_GAME_H_

#include "UnionFind.h"
#include "Group.h"
#include "Player.h"
#include "library2.h"

namespace Ehsan
{
    
    class SivansGame
    {
    private:
        int num_of_groups;
        int max_score;//AKA scale
        int num_of_players;
        UnionFind<Group> groups;
        //AVLRANKTREE levels;
        //DynamicHashTable<Player> players;
    public:
        SivansGame(int num_of_groups, int max_score);
        ~SivansGame();
        SivansGame *Init(int k, int scale);
        StatusType MergeGroups(int GroupID1, int GroupID2);
        StatusType AddPlayer(int PlayerID, int GroupID, int score);
        StatusType RemovePlayer(int PlayerID);
        StatusType IncreasePlayerIDLevel(int PlayerID, int LevelIncrease);
        StatusType ChangePlayerIDScore(int PlayerID, int NewScore);
        StatusType GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,
                                                                                                 double * players);
        StatusType AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level);
        StatusType GetPlayersBound(int GroupID, int score, int m,
                                                int * LowerBoundPlayers, int * HigherBoundPlayers);
        void Quit();
    };
    
    SivansGame::SivansGame(int num_of_groups, int max_score):
    num_of_groups(num_of_groups),
    max_score(max_score),
    num_of_players(0),
    groups(UnionFind<Group>(num_of_groups))
    {
    }
    
    SivansGame::~SivansGame()
    {
    }
    


} // namespace Ehsan


#endif