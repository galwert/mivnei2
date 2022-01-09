#ifndef _GROUP_H_
#define _GROUP_H_

#include "RankTree.h"
#include "DynamicArray.h"
#define BALANCE_FACTOR 2
#define ARRAY_SIZE 16

namespace Ehsan
{
    
    class Group
    {
    public:
        int num_of_players;
        int scale;
        RankTree<int,int> **players_by_scale;
        RankTree<int,int> *players_by_level;
        int level_zero_level;
        int *level_zero_scale;



        // Group()=delete;
        explicit Group(int scale = 200):
        num_of_players(0),//initializes number of players
        scale(scale),
        players_by_scale(new RankTree<int,int>*[scale+1]()),
        players_by_level(new RankTree<int,int>()),
        level_zero_level(0),
        level_zero_scale( new int[scale+1])
        {
            for(int i=1;i<=scale;i++)
            {
                players_by_scale[i] = new RankTree<int,int>();// needed?
                level_zero_scale[i]=0;
            }
            level_zero_level=0;

        }
        ~Group()
        {
            for(int i=1;i<=scale;i++)
            {
              delete players_by_scale[i];
            }
            delete[] players_by_scale;
            delete[] level_zero_scale;
            delete players_by_level;
        }

        void increaseNumberOfPlayers(int increase = 1);
        void decreaseNumberOfPlayers(int decrease = -1);
        BSTNode<int,int>& findLevelNode(int level);

        // friend bool operator<(const Group& first_group,const Group& second_group);
        // friend bool operator>(const Group& first_group,const Group& second_group);
        Group& operator+=(const Group& other);
        // Group& MergeGeneric(Group& to_grow, Group& other);

    };

    // bool operator<(const Group& first_group,const Group& second_group)
    // {
    //     return (first_group.num_of_players < second_group.num_of_players);
    // }
    // bool operator>(const Group& first_group,const Group& second_group)
    // {
    //     return (first_group.num_of_players > second_group.num_of_players);
    // }
} // namespace Ehsan

#endif