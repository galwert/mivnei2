#include "Group.h"


namespace Ehsan
{


    int Group::GetNumberOfPlayers()
    {
        return this->num_of_players;
    }

    void Group::IncreasePlayers(int increase = 1)
    {
        this->num_of_players+=increase;
    }

}