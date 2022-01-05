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

        Player(int id = 0, int level = 0, int score = 0);
        ~Player();
        int GetPlayerID();
        int GetPlayerLevel();
        int GetPlayerScore();
        void ChangePlayerID(int new_id);
        void ChangePlayerLevel(int new_level);
        void ChangePlayerScore(int new_score);

    };
    
    Player::Player(int original_group,int id , int level , int score):
    original_group(original_group),
    player_id(id),
    level(level),
    score(score)
    {
    }
    
    Player::~Player()
    {
    }
    


} // namespace Ehsan


#endif