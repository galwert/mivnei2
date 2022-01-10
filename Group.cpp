#include "Group.h"


namespace Ehsan
{

//    Group& Group::operator+=(const Group& other)
//    {
//        for(int i=1;i<=scale;i++)
//        {
//            players_by_scale[i]->uniteTrees(*other.players_by_scale[i]);
//            level_zero_scale[i]+=other.level_zero_scale[i];
//        }
//        players_by_level->uniteTrees(*(other.players_by_level));
//        level_zero_level+=other.level_zero_level;
//        this->num_of_players+=other.num_of_players;
//        return *this;
//    }

    void Group::increaseNumberOfPlayers(int increase)
    {
        this->num_of_players+=increase;
    }
    void Group::decreaseNumberOfPlayers(int decrease)
    {
        this->num_of_players+=decrease;
    }

    Group *Group::mergeGroups(Group *other) {
        for(int i=1;i<=scale;i++)
        {
            players_by_scale[i]->uniteTrees(*other->players_by_scale[i]);
            level_zero_scale[i]+=other->level_zero_scale[i];
        }
        players_by_level->uniteTrees(*(other->players_by_level));
        level_zero_level+=other->level_zero_level;
        this->num_of_players+=other->num_of_players;
        return this;
    }

    // Group& Group::MergeGeneric(Group& to_grow,Group& other)
    // {
    //     for(int i=1;i<=scale;i++)
    //     {
    //         players_by_scale[i]->uniteTrees(*other.players_by_scale[i]);
    //         level_zero_scale[i]+=other.level_zero_scale[i];
    //     }
    //     players_by_level->uniteTrees(*(other.players_by_level));
    //     level_zero_level+=other.level_zero_level;
    //     to_grow.num_of_players+=other.num_of_players;
    //     // should delete the other group!!
    //     /*
    //     **
    //     **
    //     **
    //     ***
    //     ***
    //     */
    //     return to_grow;
    // }

    


}