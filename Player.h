#ifndef _PLAYER_H_
#define _PLAYER_H_




namespace Ehsan
{
    
    class Player
    {
    public:
        int original_group;
        int player_id;
        int level;
        int score;

        Player(int original_group = 0 ,int id = 0 , int level = 0 , int score=  0 ):
        original_group(original_group),
        player_id(id),
        level(level),
        score(score)
        {}
        Player(Player * player):
                original_group(player->original_group),
                player_id(player->player_id),
                level(player->level),
                score(player->score)
        {

        }
        ~Player() = default;
        Player& operator=(const Player& player) = default;

    };
    
    


} // namespace Ehsan


#endif