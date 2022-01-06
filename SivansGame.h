#ifndef _SIVANS_GAME_H_
#define _SIVANS_GAME_H_

#include "UnionFind.h"
#include "Group.h"
#include "Player.h"
#include "library2.h"
#include "RankTree.h"
#include "DynamicArray.h"
#define BALANCE_FACTOR 2
#define ARRAY_SIZE 16

namespace Ehsan
{
    
    class SivansGame
    {
    public:
        int num_of_groups;
        int num_of_players;
        int scale;
        UnionFind<Group> groups;
        RankTree<int,int>** players_by_scale;
        RankTree<int,int> players_by_level;

        int level_zero_level;
        int* level_zero_scale;
        DynamicArray<Player>* players;

        SivansGame(int num_of_groups, int scale);
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


    SivansGame::SivansGame(int num_of_groups, int scale):
    num_of_groups(num_of_groups),
    scale(scale),
    num_of_players(0),
    groups(new UnionFind<Group>(num_of_groups,scale)),
    players_by_scale(new RankTree<int,int>*[scale+1]),
    players_by_level(),
    level_zero_level(0),
    level_zero_scale( new int[scale+1]),
    players(new DynamicArray<Player>(ARRAY_SIZE,BALANCE_FACTOR))
    {
        for (int i = 1; i <= scale; i++) {
            level_zero_scale[i] =0;
        }

    }
    SivansGame::~SivansGame()
    {
        for(int i=1;i<=scale;i++)
        {
            delete players_by_scale[i];
        }
        delete[] level_zero_scale;
        delete groups;
        delete players_by_level;
        delete players;
    }

    SivansGame *SivansGame::Init(int k, int scale) {
        return new SivansGame(k,scale);
    }

    StatusType SivansGame::MergeGroups(int GroupID1, int GroupID2) {
        if(GroupID1<=0||GroupID1>num_of_groups||GroupID2<=0||GroupID2>num_of_groups)
        {
            return INVALID_INPUT;
        }
        this->groups.Union(GroupID1,GroupID2);
        return SUCCESS;
    }

    StatusType SivansGame::AddPlayer(int PlayerID, int GroupID, int score) {
        if(PlayerID<=0||GroupID<=0||GroupID>num_of_groups||score>scale||score<=0)
        {
            return INVALID_INPUT;
        }
        if(this->players->insert(PlayerID, Player(PlayerID,0,score))!=SUCCESS)
        {
            return FAILURE;
        }
        this->level_zero_level++;
        this->level_zero_scale[score]++;
        this->num_of_players++;
        this->groups.data[this->groups.Find(GroupID)].num_of_players++;
        this->groups.data[this->groups.Find(GroupID)].level_zero_level++;
        this->groups.data[this->groups.Find(GroupID)].level_zero_scale[score]++;
        this->groups.size[this->groups.Find(GroupID)]++;
        return SUCCESS;
    }

    StatusType SivansGame::RemovePlayer(int PlayerID) {
        if(PlayerID <= 0)
        {
            return INVALID_INPUT;
        }
        Player* to_find;
        if(this->players->find(PlayerID,to_find) == FAILURE)
        {
            return FAILURE;
        }
        int to_find_group = groups.Find(to_find->original_group);


        this->num_of_players--;
        if(to_find->level==0)
        {
            level_zero_level--;
            level_zero_scale[to_find->score]--;
        }
        else
            {
            players_by_scale[to_find->score]->find(to_find->level)->decreaseAllNodesInTrack();
            players_by_level.find(to_find->level)->decreaseAllNodesInTrack();
            players_by_level.find(to_find->level)->data--;
            players_by_scale[to_find->score]->find(to_find->level)->data--;
        }
        if(players_by_level.find(to_find->level)->data == 0)
        {
            players_by_level.remove(to_find->level);
        }
        this->groups.data[to_find_group].num_of_players--;
        this->groups.size[to_find_group]--;
        if(to_find->level==0)
        {
            this->groups.data[to_find_group].level_zero_level--;
            this->groups.data[to_find_group].level_zero_scale[to_find->score]--;
        }
        else
            {
            groups.data[to_find_group].players_by_scale[to_find->score]->find(to_find->level)->decreaseAllNodesInTrack();
            groups.data[to_find_group].players_by_level.find(to_find->level)->decreaseAllNodesInTrack();
            groups.data[to_find_group].players_by_scale[to_find->score]->find(to_find->level)->data--;
            groups.data[to_find_group].players_by_level.find(to_find->level)->data--;
        }
        if(groups.data[to_find_group].players_by_level.find(to_find->level)->data == 0 )
        {
            groups.data[to_find_group].players_by_level.remove(to_find->level);
        }
        players->remove(PlayerID);
        return SUCCESS;
    }
    StatusType SivansGame::IncreasePlayerIDLevel(int PlayerID, int LevelIncrease) {

        if(PlayerID <= 0||LevelIncrease<=0)
        {
            return INVALID_INPUT;
        }
        Player* to_find;
        if(this->players->find(PlayerID,to_find) == FAILURE)
        {
            return FAILURE;
        }
        int to_find_group = groups.Find(to_find->original_group);
        this->num_of_players--;
        if(to_find->level==0)
        {
            level_zero_level--;
            level_zero_scale[to_find->score]--;
        }
        else
        {
            players_by_scale[to_find->score]->find(to_find->level)->decreaseAllNodesInTrack();
            players_by_level.find(to_find->level)->decreaseAllNodesInTrack();
            players_by_level.find(to_find->level)->data--;
            players_by_scale[to_find->score]->find(to_find->level)->data--;
        }
        if(players_by_level.find(to_find->level)->data == 0)
        {
            players_by_level.remove(to_find->level);
        }
        this->groups.data[to_find_group].num_of_players--;
        this->groups.size[to_find_group]--;
        if(to_find->level==0)
        {
            this->groups.data[to_find_group].level_zero_level--;
            this->groups.data[to_find_group].level_zero_scale[to_find->score]--;
        }
        else
        {
            groups.data[to_find_group].players_by_scale[to_find->score]->find(to_find->level)->decreaseAllNodesInTrack();
            groups.data[to_find_group].players_by_level.find(to_find->level)->decreaseAllNodesInTrack();
            groups.data[to_find_group].players_by_scale[to_find->score]->find(to_find->level)->data--;
            groups.data[to_find_group].players_by_level.find(to_find->level)->data--;
        }
        if(groups.data[to_find_group].players_by_level.find(to_find->level)->data == 0 )
        {
            groups.data[to_find_group].players_by_level.remove(to_find->level);
        }
        to_find->level+=LevelIncrease;
        players_by_scale[to_find->score]->find(to_find->level)->increaseAllNodesInTrack();
        players_by_level.find(to_find->level)->increaseAllNodesInTrack();
        players_by_level.find(to_find->level)->data++;
        players_by_scale[to_find->score]->find(to_find->level)->data++;
        groups.data[to_find_group].players_by_scale[to_find->score]->find(to_find->level)->increaseAllNodesInTrack();
        groups.data[to_find_group].players_by_level.find(to_find->level)->increaseAllNodesInTrack();
        groups.data[to_find_group].players_by_level.find(to_find->level)->data++;
        groups.data[to_find_group]. players_by_scale[to_find->score]->find(to_find->level)->data++;

        return SUCCESS;
    }


} // namespace Ehsan


#endif