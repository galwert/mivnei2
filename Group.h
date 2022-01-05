#ifndef _GROUP_H_
#define _GROUP_H_

#include "RankTree.h"
#include "Player.h"

namespace Ehsan
{
    
    class Group
    {
    private:
        int num_of_players;
        // int max_score;//AKA scale - I think it's not needed since score <= 200 therefore we can just use an array of size 200

        //Node* level_zero;
    public:
        Group();
        ~Group();
        int GetNumberOfPlayers();
        void IncreasePlayers(int increase = 1);
        // bool operator<(const Group& second_group)
        // {
        //     return (this->num_of_players < second_group.num_of_players);
        // }
        friend bool operator<(const Group& first_group,const Group& second_group);
    };
    
    Group::Group():
    num_of_players(0)
    {
    }
    
    Group::~Group()
    {
    }

    bool operator<(const Group& first_group,const Group& second_group)
    {
        return (first_group.num_of_players <= second_group.num_of_players);
    }
    


} // namespace Ehsan


#endif