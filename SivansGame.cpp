#include "SivansGame.h"
using namespace Ehsan;


SivansGame::SivansGame(int num_of_groups, int scale):
num_of_groups(num_of_groups),
scale(scale),
num_of_players(0),
groups( new UnionFind<Group>(num_of_groups,scale) ),
players_by_scale(new RankTree<int,int>*[scale+1]()),
players_by_level(new RankTree<int,int>()),
level_zero_level(0),
level_zero_scale( new int[scale+1]),
players(new DynamicArray<Player>(ARRAY_SIZE,BALANCE_FACTOR))
{
    for (int i = 1; i <= scale; i++) {
        players_by_scale[i] = new RankTree<int,int>();
        level_zero_scale[i] = 0;
    }

}
SivansGame::~SivansGame()
{
    for(int i=1;i<=scale;i++)
    {
        if(players_by_scale[i]!= nullptr) {
           delete players_by_scale[i];
        }
    }
    delete[] players_by_scale;
    delete[] level_zero_scale;
    delete groups;
    delete players_by_level;
    delete players;
}


Player* SivansGame::FindPlayer(int player_id)
{
    //Player *to_find = Player();// have to delete - probably in the calling function?
    //this->players->find(player_id,to_find); // should check for nullptr?
    return this->players->find(player_id);
}
Group* SivansGame::FindGroup(int group_id)
{
    Group* to_find;
    int index = groups->Find(group_id);
    if (index < 0)
    {
        return nullptr; // in case the groups doesnt exist
    }
    to_find =groups->data[index];
    return to_find;
}

SivansGame* SivansGame::InitGame(int k, int scale) {
    return new SivansGame(k,scale);
}

StatusType SivansGame::MergeGroups(int GroupID1, int GroupID2) {
if(GroupID1<=0||GroupID1>num_of_groups||GroupID2<=0||GroupID2>num_of_groups)
{
    return INVALID_INPUT;
}
this->groups->Union(GroupID1,GroupID2);
return SUCCESS;
}

void SivansGame::AddPlayerHelper(int PlayerID, Group* player_group, int GroupID, int score)
{
    this->level_zero_level++;
    this->level_zero_scale[score]++;
    this->num_of_players++;


    player_group->num_of_players++;
    player_group->level_zero_level++;
    player_group->level_zero_scale[score]++;


    this->groups->size[this->groups->Find(GroupID)]++;
    return;
}

StatusType SivansGame::AddPlayer(int PlayerID, int GroupID, int score) {
    if(PlayerID<=0||GroupID<=0||GroupID>num_of_groups||score>scale||score<=0)
    {
        return INVALID_INPUT;
    }
    // checking if the players already exists
    if(this->players->find(PlayerID)!= nullptr)
    {
        return FAILURE;
    }
    Player* player =new Player(GroupID,PlayerID,0,score);
    this->players->insert(PlayerID,player);
    Group* group_to_find = FindGroup(GroupID);
    AddPlayerHelper(PlayerID,group_to_find,GroupID,score);
    return SUCCESS;
}

void SivansGame::RemovePlayerFromGroupHelper(Player* player,Group* player_group,int score,int level)
{
    int group_index = this->groups->Find(player->original_group);
    player_group->num_of_players--;
    this->groups->size[group_index]--;
    if(level == 0)
    {
        player_group->level_zero_level--;
        player_group->level_zero_scale[score]--;
    }
    else
    {
        player_group->players_by_scale[score]->find(level)->decreaseAllNodesInTrack();
        player_group->players_by_level->find(level)->decreaseAllNodesInTrack();
        if( player_group->players_by_level->find(level)->data== 0) {
            player_group->players_by_level->remove(level);
        }
        if( player_group->players_by_scale[score]->find(level)->data== 0) {
            player_group->players_by_scale[score]->remove(level);
        }
    }

}

void SivansGame::RemovePlayerFromSivanHelper(int PlayerID,int score,int level)
{
    this->num_of_players--;
    if(level == 0)
    {
        level_zero_level--;
        level_zero_scale[score]--;
    }
    else
    {
        players_by_scale[score]->find(level)->decreaseAllNodesInTrack();
        players_by_level->find(level)->decreaseAllNodesInTrack();
        if( players_by_level->find(level)->data== 0) {
            players_by_level->remove(level);
        }
        if( players_by_scale[score]->find(level)->data== 0) {
            players_by_scale[score]->remove(level);
    }

    }
    return;
}

StatusType SivansGame::RemovePlayer(int PlayerID) {
    if(PlayerID <= 0)
    {
        return INVALID_INPUT;
    }
    Player* player_to_find = FindPlayer(PlayerID);
    if( player_to_find == nullptr)
    {
        return FAILURE;
    }
    Group* group_to_find = FindGroup(player_to_find->original_group);

    RemovePlayerFromSivanHelper(PlayerID,player_to_find->score,player_to_find->level);
    RemovePlayerFromGroupHelper(player_to_find,group_to_find,player_to_find->score,player_to_find->level);
    
    players->remove(PlayerID);
    return SUCCESS;
}

void SivansGame::RemovePlayerFromOldLevelInSivan(Player* player)
{
    // this->num_of_players--; // no need because we're gonna readd him in a second
    if(player->level == 0)
    {
        level_zero_level--;
        level_zero_scale[player->score]--;
    }
    else
    {
        players_by_scale[player->score]->find(player->level)->decreaseAllNodesInTrack();
        players_by_level->find(player->level)->decreaseAllNodesInTrack();
        if( players_by_level->find(player->level)->data == 0 )
        {
            players_by_level->remove(player->level);
        }
        if( players_by_scale[player->score]->find(player->level)->data == 0 )
        {
            players_by_scale[player->score]->remove(player->level);
        }
    }


}
void SivansGame::RemovePlayerFromOldLevelInGroup(Player* player, Group* group)
{
    if(player->level == 0)
    {
        group->level_zero_level--;
        group->level_zero_scale[player->score]--;
    }
    else {
        group->players_by_scale[player->score]->find(player->level)->decreaseAllNodesInTrack();
        group->players_by_level->find(player->level)->decreaseAllNodesInTrack();
        if (group->players_by_level->find(player->level)->data == 0) {

            group->players_by_level->remove(player->level);
        }
        if (group->players_by_scale[player->score]->find(player->level)->data == 0)
        {
            group->players_by_scale[player->score]->remove(player->level);
        }
    }
    return;
}
void SivansGame::AddPlayerToNewLevelInGroup(Player* player, Group* group)
{
    if (group->players_by_scale[player->score]->find(player->level) == nullptr)
    {
        group->players_by_scale[player->score]->insert(player->level,0);
    }
    if(group->players_by_level->find(player->level) == nullptr)
    {
        group->players_by_level->insert(player->level,0);
    }
    group->players_by_scale[player->score]->find(player->level)->increaseAllNodesInTrack();
    group->players_by_level->find(player->level)->increaseAllNodesInTrack();
    return;  
}
void SivansGame::AddPlayerToNewLevelInSivan(Player* player)
{
    if (players_by_scale[player->score]->find(player->level) == nullptr)
    {
        players_by_scale[player->score]->insert(player->level,0);
    }
    if( players_by_level->find(player->level) == nullptr)
    {
        players_by_level->insert(player->level,0);
    }
    players_by_scale[player->score]->find(player->level)->increaseAllNodesInTrack();
    players_by_level->find(player->level)->increaseAllNodesInTrack();
//    players_by_level->find(player->level)->data++;
//    players_by_scale[player->score]->find(player->level)->data++;
//
    
    return;
}

StatusType SivansGame::IncreasePlayerIDLevel(int PlayerID, int LevelIncrease) {

    if(PlayerID <= 0 || LevelIncrease<=0)
    {
        return INVALID_INPUT;
    }
    Player* player_to_find = FindPlayer(PlayerID);
    if(player_to_find == nullptr)
    {
        return FAILURE;
    }
    Group* group_to_find = FindGroup(player_to_find->original_group);
    
    RemovePlayerFromOldLevelInSivan(player_to_find);
    RemovePlayerFromOldLevelInGroup(player_to_find,group_to_find);
    
    player_to_find->level+=LevelIncrease;//update the player's level to the new one

    AddPlayerToNewLevelInSivan(player_to_find);
    AddPlayerToNewLevelInGroup(player_to_find,group_to_find);

    return SUCCESS;
}

void SivansGame::UpdateScoreInGroup(Player* player,Group* group,int OldScore, int NewScore)
{
    if (player->level == 0)
    {
        group->level_zero_scale[OldScore]--;
        group->level_zero_scale[NewScore]++;
    }
    else
    {
        group->players_by_scale[OldScore]->find(player->level)->decreaseAllNodesInTrack();
        if(group->players_by_scale[OldScore]->find(player->level)->data==0)
        {
            group->players_by_scale[OldScore]->remove(player->level);
        }
        if(group->players_by_scale[NewScore]->find(player->level)== nullptr)
        {
            group->players_by_scale[NewScore]->insert(player->level,0);
        }
        group->players_by_scale[NewScore]->find(player->level)->increaseAllNodesInTrack();
    }
    // group->players_by_level->find(player->level) // no need because we don't change the level
}

void SivansGame::UpdateScoreInSivan(Player* player,int OldScore, int NewScore)   
{
    if (player->level == 0)
    {
        level_zero_scale[OldScore]--;
        level_zero_scale[NewScore]++;
    }
    else
    {
        this->players_by_scale[OldScore]->find(player->level)->decreaseAllNodesInTrack();
        if(this->players_by_scale[OldScore]->find(player->level)->data==0)
        {
            this->players_by_scale[OldScore]->remove(player->level);
        }
        if(this->players_by_scale[NewScore]->find(player->level)== nullptr)
        {
            this->players_by_scale[NewScore]->insert(player->level,0);
        }
        this->players_by_scale[NewScore]->find(player->level)->increaseAllNodesInTrack();
    }
    // this->players_by_level->find(player->level) // no need because we don't change the level
}

StatusType SivansGame::ChangePlayerIDScore(int PlayerID, int NewScore)
{
    if(PlayerID <= 0 || NewScore<=0 || NewScore > scale)
    {
        return INVALID_INPUT;
    }
    Player* player_to_find = FindPlayer(PlayerID);
    if(player_to_find == nullptr)
    {
        return FAILURE;
    }
    Group* group_to_find = FindGroup(player_to_find->original_group);
    // int group_index = groups->Find(player_to_find->original_group);
    
    UpdateScoreInSivan(player_to_find,player_to_find->score,NewScore); // correct?
    UpdateScoreInGroup(player_to_find,group_to_find,player_to_find->score,NewScore); // correct?
    player_to_find->score=NewScore;
    return SUCCESS;
}

int SivansGame::GetNumberOfPlayersWithScoreInBounds(RankTree<int,int>** players_by_scale,int *level_zero_scale,int score, int lowerlevel, int higherlevel)
{
    int lower_level_sum=0;
    int higher_level_sum =0;
    if (lowerlevel > 0)
    {
        lower_level_sum = level_zero_scale[score];
    }
    if(players_by_scale[score]->root== nullptr)
    {
        return level_zero_scale[score]-lower_level_sum;
    }
    lower_level_sum += players_by_scale[score]->selectSumForScoreInBoundMin(lowerlevel);
    higher_level_sum += players_by_scale[score]->selectSumForScoreInBoundMax(higherlevel);
    return (level_zero_scale[score] + (players_by_scale[score]->root->sum) - (higher_level_sum) - lower_level_sum);
    
}
int SivansGame::GetNumberOfPlayersWithLevelsInBounds(RankTree<int,int>* levels_tree,int level_zero_level, int lowerlevel, int higherlevel)
{
    int lower_level_sum = 0;
    int higher_level_sum = 0;
    if (lowerlevel > 0)
    {
        lower_level_sum = level_zero_level;
    }
    if(levels_tree->root== nullptr)
    {
        return level_zero_level-lower_level_sum;
    }
    lower_level_sum += levels_tree->selectSumForScoreInBoundMin(lowerlevel);
    higher_level_sum += levels_tree->selectSumForScoreInBoundMax(higherlevel);
    return (level_zero_level + (levels_tree->root->sum )- (higher_level_sum) - lower_level_sum);

}


StatusType SivansGame::GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, 
                                                                            int higherLevel,double * players)
{
    if (GroupID < 0 || GroupID > this->groups->numberOfElements || players == nullptr)
    {
        return INVALID_INPUT;
    }
    if(higherLevel<0||score>scale||score<=0|| lowerLevel > higherLevel )
    {
        return FAILURE;
    }
    int total_number_of_people_in_interval;
    int number_of_players_in_bound;
    if (GroupID == 0)
    {
        if(this->players_by_level->root== nullptr&&this->level_zero_level==0)
        {
            return FAILURE;
        }
        else {
                total_number_of_people_in_interval = GetNumberOfPlayersWithLevelsInBounds(this->players_by_level,this->level_zero_level,lowerLevel,higherLevel);
        }
        number_of_players_in_bound = 100*GetNumberOfPlayersWithScoreInBounds(this->players_by_scale,level_zero_scale,score,lowerLevel,higherLevel);
    }
    else // if (GroupID > 0)
    {

        Group* group_to_find = FindGroup(GroupID);
        if(group_to_find->players_by_level->root== nullptr&&group_to_find->level_zero_level==0)
        {
            return FAILURE;
        }
        else {
            total_number_of_people_in_interval = GetNumberOfPlayersWithLevelsInBounds(group_to_find->players_by_level,group_to_find->level_zero_level,lowerLevel,higherLevel);
        }
        number_of_players_in_bound = 100*GetNumberOfPlayersWithScoreInBounds(group_to_find->players_by_scale,group_to_find->level_zero_scale,score,lowerLevel,higherLevel);
    }
    if(total_number_of_people_in_interval==0)
    {
        return FAILURE;
    }
    *players = (double)number_of_players_in_bound/(double)total_number_of_people_in_interval;
    return SUCCESS;
}

StatusType AverageHighestPlayerLevelByGroupInternal(BSTNode<int,int> * root, int *num_of_players, int * sum)
{
    if(root== nullptr||*num_of_players<=0)
    {
        return SUCCESS;
    }

    while (*num_of_players<root->sum)
    {
        if(root->right== nullptr)
        {
            if(root->data>=*num_of_players)
            {
                *sum+=*num_of_players*root->key;
            }
            else
            {
                *sum+=root->data*root->key+root->left->key*(*num_of_players-root->data);
            }
            return SUCCESS;
        }
        root=root->right;
    }
    if(root->parent== nullptr)
    {
        *sum += root->sum_for_avg;
        *num_of_players -=  root->sum;
        return SUCCESS;
    }
    root=root->parent;

        if(*num_of_players<=root->data + root->right->sum)
        {
            *sum += root->right->sum_for_avg +root->key*(*num_of_players-root->right->sum);
            *num_of_players = 0;
            return SUCCESS;
        }
        *sum += root->right->sum_for_avg + root->data * root->key;
        *num_of_players -= root->data + root->right->sum;
        return AverageHighestPlayerLevelByGroupInternal(root->left,num_of_players,sum);
}
StatusType SivansGame::AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level)
{   
    //do the following route on the rank tree : right,root,left (anti inorder)
    //it should provide the m highest levels in the tree
    if (GroupID < 0 || m <= 0 || GroupID > this->groups->numberOfElements || level == nullptr)
    {
        return INVALID_INPUT;
    }

    Group* group_to_find = nullptr;
    if (GroupID > 0)
    {
        group_to_find = FindGroup(GroupID);
    }
    
    if ( (m > this->num_of_players) || ( (GroupID > 0) && (GroupID <= this->num_of_groups) && (m > group_to_find->num_of_players) ) )
    {
        // if m>this->num_of_players then it's definitely bigger than the number of players in any given group!
        return FAILURE;
    }
    

    int *num_of_players = new int();
    *num_of_players=m;
    int *sum = new int();
    *sum =0;
    if (GroupID == 0)
    {
        if(this->players_by_level->root== nullptr)
        {
            *sum=0;
        }
        else
        {
            if (this->players_by_level->root->sum < m)
            {
                if(this->players_by_level->root!= nullptr) {
                    *sum = this->players_by_level->root->sum_for_avg;
                }
            }
            else {
                AverageHighestPlayerLevelByGroupInternal(this->players_by_level->root, num_of_players, sum);
            }
        }
    }
    else // 1 <= GroupID <= k
    {
        if (group_to_find->players_by_level->root == nullptr) {
            *sum = 0;
        } else {
            if (group_to_find->players_by_level->root->sum < m) {
                if (group_to_find->players_by_level->root != nullptr) {
                    *sum = group_to_find->players_by_level->root->sum_for_avg;
                }
            } else {
                AverageHighestPlayerLevelByGroupInternal(group_to_find->players_by_level->root, num_of_players, sum);
            }
        }
    }
    (*level) = (double)(*sum)/(double)m;
    delete sum;
    delete num_of_players;
    return SUCCESS;
}
