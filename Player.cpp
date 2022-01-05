#include "Player.h"

namespace Ehsan
{

    int Player::GetPlayerID()
    {
        return this->player_id;
    }

    int Player::GetPlayerLevel()
    {
        return this->level;
    }

    int Player::GetPlayerScore()
    {
        return this->score;
    }

    void Player::ChangePlayerID(int new_id)
    {
        this->player_id = new_id;
    }

    void Player::ChangePlayerLevel(int new_level)
    {
        this->level = new_level;
    }

    void Player::ChangePlayerScore(int new_score)
    {
        this->score = new_score;
    }

}
