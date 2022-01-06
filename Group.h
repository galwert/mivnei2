#ifndef _GROUP_H_
#define _GROUP_H_

#include "RankTree.h"
#include "Player.h"

namespace Ehsan
{
    
    class Group
    {
    public:
        int num_of_players;
         int scale;
         RankTree<int,int>** players_by_scale;
         RankTree<int,int> players_by_level;
       int level_zero_level;
       int* level_zero_scale;

        Group()=delete;
        explicit Group(int scale):num_of_players(0),
        scale(scale),
        players_by_scale(new RankTree<int,int>*[scale+1]),
                         players_by_level(),
                         level_zero_level(0),
                         level_zero_scale( new int[scale+1])
        {
            for(int i=1;i<=scale;i++)
            {
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
            delete[] level_zero_scale;
        }
        friend bool operator<(const Group& first_group,const Group& second_group);
        friend bool operator>(const Group& first_group,const Group& second_group);
        Group& operator+=(const Group& other)
        {
            for(int i=1;i<=scale;i++)
            {
                players_by_scale[i]->uniteTrees(*other.players_by_scale[i]);
                level_zero_scale[i]+=other.level_zero_scale[i];
            }
            players_by_level.uniteTrees(other.players_by_level);
            level_zero_level+=other.level_zero_level;
            this->num_of_players+=other.num_of_players;
            return *this;
        }
    };

    bool operator<(const Group& first_group,const Group& second_group)
    {
        return (first_group.num_of_players < second_group.num_of_players);
    }
    bool operator>(const Group& first_group,const Group& second_group)
    {
        return (first_group.num_of_players > second_group.num_of_players);
    }
} // namespace Ehsan

#endif