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
        players_by_scale[i] = new RankTree<int,int>();// needed?
        level_zero_scale[i] = 0;
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


Player* SivansGame::FindPlayer(int player_id)
{
    Player* to_find = new Player(); // have to delete - probably in the calling function?
    /*
    *
    * PAY ATTENTION!!!!!!!!!!!!!!! 
    */
    this->players->find(player_id,to_find); // should check for nullptr?
    return to_find;
}
Group* SivansGame::FindGroup(int group_id)
{
    Group* to_find = nullptr;
    int index = groups->Find(group_id);
    if (index < 0)
    {
        return nullptr; // in case the groups doesnt exist
    }
    to_find = groups->data+index;
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
    if(this->players->insert(PlayerID, Player(GroupID,PlayerID,0,score))!=SUCCESS) 
    {
        return FAILURE;
    }

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
        player_group->players_by_scale[score]->find(level)->data--;
        player_group->players_by_level->find(level)->data--;
    }
    BSTNode<int,int> *player_node = players_by_level->find(level);
    if( (player_node != nullptr) && (level != 0) &&  (player_node->data == 0) )
    {
        player_group->players_by_level->remove(level);
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
        players_by_level->find(level)->data--;
        players_by_scale[score]->find(level)->data--;
    }
    BSTNode<int,int> *player_node = players_by_level->find(level);
    if( (player_node != nullptr) && (level != 0) &&  (player_node->data == 0) )
    {
        players_by_level->remove(level);
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
        players_by_level->find(player->level)->data--;
        players_by_scale[player->score]->find(player->level)->data--;
    }
    if( (player->level != 0) && (players_by_level->find(player->level)->data == 0) )
    {
        players_by_level->remove(player->level);
    }
}
void SivansGame::RemovePlayerFromOldLevelInGroup(Player* player, Group* group)
{
    int group_index = this->groups->Find(player->original_group);
    // group_to_find->num_of_players--; // no need because we're gonna readd him in a sec
    this->groups->size[group_index]--;
    if(player->level == 0)
    {
        group->level_zero_level--;
        group->level_zero_scale[player->score]--;
    }
    else
    {
        group->players_by_scale[player->score]->find(player->level)->decreaseAllNodesInTrack();
        group->players_by_level->find(player->level)->decreaseAllNodesInTrack();
        group->players_by_scale[player->score]->find(player->level)->data--;
        group->players_by_level->find(player->level)->data--;
    }
    if( (player->level != 0) && (group->players_by_level->find(player->level)->data == 0) )
    {
        group->players_by_level->remove(player->level);
    }
    return;
}
void SivansGame::AddPlayerToNewLevelInGroup(Player* player, Group* group)
{
    if (group->players_by_scale[player->score]->find(player->level) == nullptr)
    {
        group->players_by_scale[player->score]->insert(player->level,0);// correct insertion - saleh?
        group->players_by_level->insert(player->level,0);// correct insertion - saleh?
    }
    group->players_by_scale[player->score]->find(player->level)->increaseAllNodesInTrack();
    group->players_by_level->find(player->level)->increaseAllNodesInTrack();
    group->players_by_level->find(player->level)->data++;
    group->players_by_scale[player->score]->find(player->level)->data++;
    return;  
}
void SivansGame::AddPlayerToNewLevelInSivan(Player* player)
{
    if (players_by_scale[player->score]->find(player->level) == nullptr)
    {
        players_by_scale[player->score]->insert(player->level,0);// correct insertion - saleh?
        players_by_level->insert(player->level,0);// correct insertion - saleh?
        
    }
    players_by_scale[player->score]->find(player->level)->increaseAllNodesInTrack();
    players_by_level->find(player->level)->increaseAllNodesInTrack();
    players_by_level->find(player->level)->data++;
    players_by_scale[player->score]->find(player->level)->data++;
    
    
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
    int group_index = this->groups->Find(player_to_find->original_group);
    
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
        level_zero_scale[OldScore]--;
    }
    else
    {
        group->players_by_scale[OldScore]->find(player->level)->decreaseAllNodesInTrack();
    }
    group->players_by_scale[NewScore]->find(player->level)->increaseAllNodesInTrack();
    // group->players_by_level->find(player->level) // no need because we don't change the level
}

void SivansGame::UpdateScoreInSivan(Player* player,int OldScore, int NewScore)   
{
    if (player->level == 0)
    {
        level_zero_scale[OldScore]--;
    }
    else
    {
        this->players_by_scale[OldScore]->find(player->level)->decreaseAllNodesInTrack();
    }
    this->players_by_scale[NewScore]->find(player->level)->increaseAllNodesInTrack();
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
    
    return SUCCESS;
}

int SivansGame::GetNumberOfPlayersWithScoreInBounds(RankTree<int,int>** players_by_scale,int *level_zero_scale,int score, int lowerlevel, int higherlevel)
{
    int lower_level_sum = level_zero_scale[score];// need to check for the levels!
    if (lowerlevel != 0)
    {
        lower_level_sum = players_by_scale[score]->find(lowerlevel)->getSum();
    }
    
    int higher_level_sum = players_by_scale[score]->find(higherlevel)->getSum();
    int higher_level_data_number = players_by_scale[score]->find(higherlevel)->data;
    return (lower_level_sum - higher_level_sum + higher_level_data_number);
    
}

int SivansGame::GetTotalNumberOfPlayersBounds(RankTree<int,int> *players_by_level, int lowerlevel, int higherlevel)
{
    
    int lower_level_sum = players_by_level->find(lowerlevel)->getSum();
    int higher_level_sum = players_by_level->find(higherlevel)->getSum();
    int higher_level_data_number = players_by_level->find(higherlevel)->data;
    return (lower_level_sum - higher_level_sum + higher_level_data_number);
    
}

StatusType SivansGame::GetPercentOfPlayersWithScoreInBoundsHelper(RankTree<int,int>** players_scale,RankTree<int,int> *players_level,
                                                                                int *levelzero_scale,int score,int lowerLevel,int higherLevel,double * players)
{
    BSTNode<int,int>* most_right_node =  RankTree<int,int>::getMostRightNode(this->players_by_level->root);
    int highest_level = 0;
    if (most_right_node != nullptr)
    {
        highest_level = RankTree<int,int>::getMostRightNode(this->players_by_level->root)->key;
    }
    
    // int highest_level = RankTree<int,int>::getMostRightNode(this->players_by_level->root)->key;
    if (higherLevel < 0 || lowerLevel > highest_level )
    {
        return FAILURE;
    }
    int new_lower_level = lowerLevel, new_higher_level = higherLevel;
    if ( lowerLevel < 0)
    {
        new_lower_level = 0;
    }
    else if (higherLevel > highest_level)
    {
        new_higher_level = highest_level;
    }

    int number_of_players_in_bound = GetNumberOfPlayersWithScoreInBounds(players_scale,levelzero_scale,score,new_lower_level,new_higher_level);
    if (number_of_players_in_bound == 0)
    {
        return FAILURE;
    }
    int total_number_of_people_in_interval = GetTotalNumberOfPlayersBounds(players_level,lowerLevel,higherLevel);
    *players = (double)number_of_players_in_bound/(double)total_number_of_people_in_interval;
    return SUCCESS;
}

StatusType SivansGame::GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, 
                                                                            int higherLevel,double * players)
{
    if (GroupID < 0 || GroupID > this->groups->numberOfElements || players == nullptr)
    {
        return INVALID_INPUT;
    }

    if (GroupID == 0)
    {
        return GetPercentOfPlayersWithScoreInBoundsHelper(this->players_by_scale,this->players_by_level,
                                                                        this->level_zero_scale,score,lowerLevel,higherLevel,players);
        
    }
    else // if (GroupID > 0)
    {
        Group* group_to_find = FindGroup(GroupID);
        return GetPercentOfPlayersWithScoreInBoundsHelper(group_to_find->players_by_scale,group_to_find->players_by_level,
                                                            group_to_find->level_zero_scale,score,lowerLevel,higherLevel,players);
        
    }

    return SUCCESS; // should never get here
    
}

void SivansGame::AntiInOrderInTree(BSTNode<int,int>* root,BSTNode<int,int>* leftest_node,int level_zero,
                                                                            int *sum,int *num_of_players,int m)
{

    // note that the lowest possible level is 0 hence if we assume that it's in the tree it's always to the left of some node
    // However the way we designed the tree, level zero is outside the tree and therefore if we arrive at level 1 at somepoint
    // we have to check level 0 manually to the left of it.

    if (root == leftest_node && ( (*num_of_players) < m) )
    {   
        (*num_of_players) += level_zero;
        if ( (*num_of_players) >= m)
        {
            return; // level zero doesnt affect the sum.
        }
    }
    
    if (root == nullptr)
    {
        return;
    }
    

    AntiInOrderInTree(root->right,leftest_node,level_zero,sum,num_of_players,m);
    (*sum) += root->data * (root->key);// number_of_players_in_level * level
    (*num_of_players) = root->data;
    if ( (*num_of_players) >= m)
    {
        (*sum) -= ( (*num_of_players) - (root->data) ) * (root->key); // remove the extra players that we added    
        return;        
    }

    AntiInOrderInTree(root->left,leftest_node,level_zero,sum,num_of_players,m);
    if ( (*num_of_players) >= m)
    {
        (*sum) -= ( (*num_of_players) - (root->data) ) * (root->key); // remove the extra players that we added   
        return;         
    }

}

StatusType SivansGame::AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level)
{
    //do the following route on the rank tree : right,root,left (anti inorder)
    //it should provide the m highest levels in the tree
    if (GroupID < 0 || m <= 0 || GroupID > this->groups->numberOfElements || level == nullptr)
    {
        return INVALID_INPUT;
    }

    Group* group_to_find = FindGroup(GroupID);
    if ( (m > this->num_of_players) || ( (GroupID > 0) && (m > group_to_find->num_of_players) ) )
    {
        // if m>this->num_of_players then it's definitely bigger than the number of players in any given group!
        return FAILURE;
    }
    

    int *num_of_players = new int();
    int *sum = new int();
    BSTNode<int,int>* leftest_node = RankTree<int,int>::getLeftestNode(this->players_by_level->root);
    //should probably check the case in which leftest_node in null
    if (GroupID == 0)
    {
        //do the anti inorder in Sivans
        AntiInOrderInTree(this->players_by_level->root,leftest_node,this->level_zero_level,sum,num_of_players,m);
    }
    else // 1 <= GroupID < k
    {
        // do the anti inorder in Group
        AntiInOrderInTree(group_to_find->players_by_level->root,leftest_node,group_to_find->level_zero_level,sum,num_of_players,m);
    }

    (*level) = (double)(*sum)/(double)m;
    delete sum;
    delete num_of_players;

    return SUCCESS;
}

void SivansGame::QuitGame(SivansGame* game)
{
    delete game;
}