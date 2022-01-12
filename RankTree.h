//
// Created by galwe on 08/12/2021.
//


#ifndef AVL_RankTree_H
#define AVL_RankTree_H

#include <cstdlib>
#include <algorithm>
#include <ctgmath>
#include <iostream>
#include <memory>
namespace Ehsan {


    template<class T,class S>
    class BSTNode//---------------BSTNode-----------------------------
    {
    public:
        S key;
        T data;
        BSTNode *left;
        BSTNode *right;
        BSTNode *parent;
        int height;
        int rank;
        int sum;




        explicit BSTNode(S key, T data);

        BSTNode()=default;
        BSTNode(const BSTNode<T,S> &node);

        BSTNode *roll();


        BSTNode &operator=(const BSTNode &node);

        ~BSTNode() = default;

        int getSum() {
            if (this == nullptr) { // ?
                return 0;
            }
            if (this->left == nullptr && this->right == nullptr) {
                return (int)data;
            } else if (this->left == nullptr) {
                return (int)data + this->right->sum;
            } else if (this->right == nullptr) {
                return (int)data + this->left->sum;
            } else {
                return (int)data + this->left->sum+ this->right->sum;
            }
        }
        int getHeight() {
            if (this == nullptr) {
                return 0;
            }
            if (this->left == nullptr && this->right == nullptr) {
                return 1;
            } else if (this->left == nullptr) {
                return 1 + this->right->height;
            } else if (this->right == nullptr) {
                return 1 + this->left->height;
            } else {
                return 1 + std::max(this->left->height,
                                    this->right->height);
            }
        }
        int getRank() {
            if (this == nullptr) {
                return 0;
            }
            if (this->left == nullptr && this->right == nullptr) {
                return 1;
            } else if (this->left == nullptr) {
                return 1 + this->right->rank;
            } else if (this->right == nullptr) {
                return 1 + this->left->rank;
            } else {
                return 1 + this->left->rank + this->right->rank;
            }
        }
        void increaseAllNodesInTrack()
        {
            BSTNode<T,S> *node =this;
            node->data++;
            while(node!= nullptr)
            {
                node->sum++;
                node=node->parent;
            }
        }
        void decreaseAllNodesInTrack()
        {
            BSTNode<T,S> *node =this;
            node->data--;
            while(node!= nullptr)
            {
                node->sum--;
                node=node->parent;
            }
        }

    };//-------------------------------BSTNode END---------------------------


    template<class T,class S>
    class RankTree//-------------------------------RankTree---------------------------
    {
    public:
        BSTNode<T,S> *root;

        RankTree();
        static int countNodes(BSTNode<T,S> * node)
        {
            if(node== nullptr)
            {
                return 0;
            }
            return (countNodes(node->left) + countNodes(node->right) + 1);
        }
        void removeInternal(BSTNode<T,S> *node);

        static BSTNode<T,S> *getLeftestNode(BSTNode<T,S> *root)
        {
            if (root != nullptr)
            {
                while (root->left != nullptr)
                {
                    root = root ->left;
                }
            }
            return root;
        }

        static BSTNode<T,S> *getMostRightNode(BSTNode<T,S> *root)
        {
            if (root != nullptr)
            {
                while (root->right != nullptr)
                {
                    root = root ->right;
                }
            }
            return root;
        }

        static BSTNode<T,S> *leftRotate(BSTNode<T,S> *x) {

            BSTNode<T,S> *y = x->right;
            BSTNode<T,S> *T2 = y->left;

            y->left = x;
            x->right = T2;
            if(T2!=nullptr) {
                T2->parent = x;
            }
            if (x->parent != nullptr) {
                if (x->parent->right == x) {
                    x->parent->right = y;
                } else {
                    x->parent->left = y;
                }
            }
            y->parent = x->parent;
            x->parent = y;
            x->height = x->getHeight();
            y->height = y->getHeight();
            x->rank=x->getRank();
            y->rank=y->getRank();
            x->sum=x->getSum();
            y->sum=y->getSum();
            return y;

        }

        static BSTNode<T,S> *rightRotate(BSTNode<T,S> *y) {
            BSTNode<T,S> *x = y->left;
            BSTNode<T,S> *T2 = x->right;

            x->right = y;
            y->left = T2;
            if(T2!=nullptr) {
                T2->parent = y;
            }
            if (y->parent != nullptr) {
                if (y->parent->right == y) {
                    y->parent->right = x;
                } else {
                    y->parent->left = x;
                }
            }
            x->parent = y->parent;
            y->parent = x;

            y->height = y->getHeight();
            x->height = x->getHeight();
            y->rank=y->getRank();
            x->rank=x->getRank();
            y->sum=y->getSum();
            x->sum=x->getSum();
            return x;
        }

        static void arrayToTree(BSTNode<T,S>* tree,S *keys, T *datas,int* index)
        {
            if (tree == nullptr)
            {
                return;
            }
            arrayToTree(tree->left,keys,datas,index);
            tree->data = datas[*index];
            tree->key = keys[*index];
            (*index)++;
            arrayToTree(tree->right,keys,datas,index);

        }
        static void treeToArray(S *keys, T *data,int * index, BSTNode<T,S> *tree_root)
        {
            if( tree_root == nullptr)
            {
                return;
            }
            treeToArray(keys,data,index,tree_root->left);
            data[*index] = tree_root->data;
            keys[*index] = tree_root->key;
            (*index)++;
            treeToArray(keys,data,index,tree_root->right);
        }

        void merge(T *a, S *a_h , int na, T *b,S *b_h, int nb, T *c,S *c_h);

        void uniteTrees(RankTree<T,S> &other);

        RankTree(const RankTree &tree);

        RankTree &operator=(const RankTree &tree);

        void treeDelete(BSTNode<T,S> *toDelete);

        ~RankTree();

        BSTNode<T,S> *select(int rank);

        BSTNode<T,S>* insert(S key, T data);

        void remove(S key);
        BSTNode<T,S> *find(S key);

        BSTNode<T,S> *copyTreeInternal(BSTNode<T,S>* tree, BSTNode<T,S>* toCopy);
        BSTNode<T,S>* createEmptyFullTree(S* keys,T*data,int min,int max);

        static int calcHeightDiff(BSTNode<T,S> *node);


        int FindInBoundMax(S key);

        int selectSumMin(int sum);

        int selectSumMax(int sum);

        int selectSumForAvgLevels(int sum);

        int selectSumForScoreInBoundMax(int level);

        int selectSumForScoreInBoundMin(int level);
    }; //-------------------------------RankTree END---------------------------


    template<class T,class S>
    BSTNode<T,S>::BSTNode(const BSTNode &node):
            key(node.key),
            data(node.data),
            left(node.left),
            right(node.right),
            parent(node.parent),
            height(node.height),
            rank(node.rank)
    {

    }

    template<class T,class S>
    BSTNode<T,S>::BSTNode(S key, T data):
            key(key),
            data(data),
            left(nullptr),
            right(nullptr),
            parent(nullptr),
            height(1),
            rank(1),
            sum((int)data)
    {}

    template<class T,class S>
    BSTNode<T,S> &BSTNode<T,S>::operator=(const BSTNode &node) {
        if (this == &node)
            return *this;
        delete this;
        this->data = node.data;
        this->left = node.left;
        this->right = node.right;
        this->height = node.height;
        this->key = node.key;
        this->height=node.height;
        this->rank=node.rank;
        return *this;
    }

    template<class T,class S>
    RankTree<T,S>::RankTree():root(nullptr) {
    }

    template<class T,class S>
    RankTree<T,S>::RankTree(const RankTree<T,S> &tree) {
        this->root = copyTreeInternal(this->root, tree.root);
    }

    template<class T,class S>
    RankTree<T,S> &RankTree<T,S>::operator=(const RankTree &tree) {
        if (this == &tree)
            return *this;
        treeDelete(this->root);
        copyTreeInternal(this, tree);
        return *this;
    }

    template<class T,class S>
    BSTNode<T,S> *BSTNode<T,S>::roll() {
        int BF = RankTree<T,S>::calcHeightDiff(this);

        // Left Left Case
        if (BF > 1 &&
            RankTree<T,S>::calcHeightDiff(this->left) >= 0) {
            return RankTree<T,S>::rightRotate(this);
        }

        // Left Right Case
        if (BF > 1 &&
            RankTree<T,S>::calcHeightDiff(this->left) < 0) {
            RankTree<T,S>::leftRotate(this->left);
            return RankTree<T,S>::rightRotate(this);
        }

        // Right Right Case
        if (BF < -1 &&
            RankTree<T,S>::calcHeightDiff(this->right) <= 0)
            return RankTree<T,S>::leftRotate(this);

        // Right Left Case
        if (BF < -1 &&
            RankTree<T,S>::calcHeightDiff(this->right) > 0) {
            RankTree<T,S>::rightRotate(this->right);
            return RankTree<T,S>::leftRotate(this);
        }
        return this;
    }


    template<class T,class S>
    BSTNode<T,S> *RankTree<T,S>::copyTreeInternal(BSTNode<T,S>* tree,
                                                          BSTNode<T,S>* toCopy) {
        if (toCopy == nullptr) {
            tree = nullptr;
        } else {
            tree = new BSTNode<T,S>(toCopy->key,toCopy->data);
            tree->height = toCopy->height;
            copyTreeInternal(tree->left, toCopy->left);
            copyTreeInternal(tree->right, toCopy->right);
            if ( (tree->right != nullptr) && (tree->left != nullptr) )
            {
                tree->right->parent = tree;
                tree->left->parent = tree;
            }
        }
        return tree;
    }

    template<class T,class S>
    RankTree<T,S>::~RankTree() {
        treeDelete(this->root);
    }

    template<class T,class S>
    void RankTree<T,S>::treeDelete(BSTNode<T,S>* toDelete) {
        if (toDelete != nullptr) {

            treeDelete(toDelete->left);
            treeDelete(toDelete->right);
            delete toDelete;
        }
    }
    template<class T,class S>
    void printTree(BSTNode<T,S> * root) {
        std::cout.flush();
        if(root== nullptr)
            return;

        printTree(root->left);
        std::cout<<root->key;
        std::cout<<" BF: "<<RankTree<T,S>::calcHeightDiff(root)<<" Height: "<<root->height-1<<std::endl;
        printTree(root->right);
    }
    template<class T,class S>
    void insertInternal(BSTNode<T,S> *node, S key, T data) {

        if (key > node->key) {
            if(node->right==nullptr)
            {
                node->right= new BSTNode<T,S>(key, data);
                node->right->parent=node;
                rebalance(node);
            }
            else {
                insertInternal(node->right, key, data);

            }

        }
        if (key < node->key) {
            if(node->left==nullptr)
            {
                node->left= new BSTNode<T,S>(key, data);
                node->left->parent=node;
                rebalance(node);
            }
            else {
                insertInternal(node->left, key, data);

            }
        }
    }

    template<class T,class S>
    BSTNode<T,S> * selectInternal(BSTNode<T,S> *node,int rank) {
        if (node->left->rank == rank - 1) {
            return node;
        }
        if (node->left->rank > rank - 1) {
            selectInternal(node->left, rank);
        } else {
            selectInternal(node->right, rank-node->left->rank-1);
        }
    }

    template<class T,class S>
    BSTNode<T,S> *RankTree<T,S>::select(int rank) {
        if(rank>this->root->rank)
        {
            return nullptr;
        }
        return selectInternal(this->root,rank);
    }

    template<class T,class S>
    int selectSumForAvgLevelsInternal(BSTNode<T,S> *node,int sum) {
        if (node->left->sum <= sum && (node->left->sum) + node->data >= sum ) {
            return node->right->sum;
        }
        if (node->left->sum > sum) {
            selectSumForAvgLevelsInternal(node->left, sum);
        } else {
            selectSumForAvgLevelsInternal(node->right, sum-node->left->sum-node->data);
        }
    }

    // template<class T,class S>
    // int RankTree<T,S>::selectSumForAvgLevels(int sum) {
    //     if(sum<this->root->sum)
    //     {
    //         return 0;
    //     }
    //     return selectSumMaxInternal(this->root,sum);
    // }

    template<class T,class S>
    int RankTree<T,S>::selectSumForAvgLevels(int sum)
    {
        if (sum > this->root->sum)
        {
            return this->root->sum;
        }
        return selectSumForAvgLevelsInternal(this->root,sum);
        
    }


    template<class T,class S>
    int selectSumForScoreInBoundMaxInternal(BSTNode<T,S> *node,int rank) {
      int sum=node->sum;
        if(node->rank==rank)
        {
            if(node->right== nullptr)
            {
                return node->sum;
            }
            return node->sum-node->right->sum;
        }
        if (node->left->sum > rank) {
            selectSumForScoreInBoundMaxInternal(node->left, rank);
        } else {
            selectSumForScoreInBoundMaxInternal(node->right, rank-node->left->sum-node->data);
        }
    }
    template<class T,class S>
    int RankTree<T,S>::selectSumForScoreInBoundMax(int level) {
        if(this->root== nullptr)
        {
            return 0;
        }
       int sum=0;
        BSTNode<T,S> *node= this->root;
       while(node!= nullptr)
       {
           if(node->key==level)
           {
               if(node->right!= nullptr)
               {
                   return sum+node->right->sum;
               }
               return sum;
           }
           else if(node->key<level)
           {
               node=node->right;
           }
           else if(node->key>level)
           {
               if(node->right!= nullptr)
               {
                   sum+=node->data+node->right->sum;
               }
               else
               {
                   sum+=node->data;
               }
               node=node->left;
           }
       }
        return sum;
    }
    template<class T,class S>
    int RankTree<T,S>::selectSumForScoreInBoundMin(int level) {
        if(this->root== nullptr)
        {
            return 0;
        }
        int sum=0;
        BSTNode<T,S> *node= this->root;
        while(node!= nullptr)
        {
            if(node->key==level)
            {
                if(node->left!= nullptr)
                {
                    return (sum + node->left->sum);
                }
                return sum;
            }
            else if(node->key < level)
            {
                if(node->left != nullptr)
                {
                    sum+=node->data+node->left->sum;
                }
                else
                {
                    sum+=node->data;
                }
                node=node->right;
            }
            else if(node->key>level)
            {
                node=node->left;
            }
        }
        return sum;
    }
    template<class T,class S>
    int RankTree<T,S>::FindInBoundMax(S key)
    {
        BSTNode<T,S> * node=this->root,*prev;

        while(node!= nullptr)
        {
            prev=node;
            if(key==node->key)
            {
                if(node->right!= nullptr)
                {
                    return node->right->sum;
                } else
                {
                    return 0;
                }
            }
            if(key>node->key)
            {
                node=node->right;
            }
            else
            {
                node=node->left;
            }
        }

    }
    template<class T,class S>
    BSTNode<T,S> *RankTree<T,S>::insert(S key, T data) {

        if (this->root == nullptr) {
            BSTNode<T,S> *newnode= new BSTNode<T,S>(key, data);
            this->root=newnode;
            return this->root;
        }
        insertInternal(this->root, key, data);


        if (this->root->parent!= nullptr) {
            this->root = this->root->parent;
        }
        return nullptr;
    }


    template<class T,class S>
    BSTNode<T,S> *RankTree<T,S>::find(S key) {
        BSTNode<T,S> *curr = this->root;
        while (curr != nullptr) {
            if (curr->key > key) {
                curr = curr->left;
            } else if (curr->key < key) {
                curr = curr->right;
            } else
                return curr;
        }
        return curr;
    }   
    template<class T,class S>
    int RankTree<T,S>::calcHeightDiff(BSTNode<T,S> *node) {
        return node->left->getHeight() - node->right->getHeight();
    }
    template<class T,class S>
    void rebalance (BSTNode<T,S>* start)
    {
        if(start==nullptr)
            return;
        while (start != nullptr)
        {
            start=start->roll();
            start->height = start->getHeight();
            start->rank=start->getRank();
            start->sum=start->getSum();
            start=start->parent;
        }
    }
    template<class T,class S>
    void RankTree<T,S>::remove(S key) {
        BSTNode<T,S> *toDelete = find(key);
        if (toDelete == nullptr) {
            return;
        }
        if (toDelete == this->root)
        {
            if(this->root->right==nullptr||this->root->left==nullptr)
            {
                BSTNode<T, S> *temp = this->root->left ? this->root->left : this->root->right;
                delete this->root;
                this->root=temp;
                if(temp==nullptr)
                {
                    return;
                }
                temp->height=1;
                temp->parent=nullptr;
                return;
            }
        }

        removeInternal(toDelete);
        if(this->root!=nullptr&&this->root->parent!=nullptr)
        {
            this->root=this->root->parent;
        }
    }

    template<class T,class S>
    void RankTree<T,S>::removeInternal(BSTNode<T,S>* node) {
        if (node == nullptr)
            return;
        if ((node->left == nullptr) || (node->right == nullptr)) {
            BSTNode<T, S> *temp = node->left ? node->left : node->right;
            BSTNode<T, S> *startfrom=node->parent;
            if (temp != nullptr) {
                if (node->parent->right == node) {
                    startfrom->right = temp;
                    temp->parent = node->parent;
                }
                if (node->parent->left == node) {
                    startfrom->left = temp;
                    temp->parent = node->parent;
                }
            } else {
                if (node->parent->left == node) {
                    startfrom->left = nullptr;
                }
                if (node->parent->right == node) {
                    startfrom->right = nullptr;
                }
            }
            delete node;
            rebalance(startfrom);
            return;
        } else {
            BSTNode<T, S> *temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->key = temp->key;
            node->data = temp->data;
            removeInternal(temp);
        }
    }
    template<class T,class S>
    BSTNode<T,S>* RankTree<T,S>::createEmptyFullTree(S* keys,T*data,int min,int max)
    {
        if(min==max)
        {
            BSTNode<T,S>* newroot =new BSTNode<T,S>(keys[min],data[min]);
            newroot->height=1;
            return newroot;
        }
        else if(min>max)
        {
            return nullptr;
        }
        int mid=(min+max)/2;
        BSTNode<T,S>* newroot = new BSTNode<T,S>(keys[mid],data[mid]);
        newroot->left = createEmptyFullTree(keys,data,min,mid-1);
        newroot->right = createEmptyFullTree(keys,data,mid+1,max);
        newroot->height =newroot->getHeight();
        newroot->rank=newroot->getRank();
        newroot->sum=newroot->getSum();

        if(newroot->right!= nullptr)
        {
            newroot->right->parent=newroot;
        }
        if(newroot->left!= nullptr)
        {
            newroot->left->parent=newroot;
        }
        return newroot;
    }

    template<class T, class S>
    void RankTree<T, S>::merge(T *a, S *a_h , int na, T *b,S *b_h, int nb, T *c,S *c_h)
    {
        int ia, ib, ic;
        for(ia = ib = ic = 0; (ia < na) && (ib < nb); ic++)
        {
            if(a_h[ia] < b_h[ib])
            {
                c[ic] = a[ia];
                c_h[ic] = a_h[ia];
                ia++;
            }
            else
            {
                c[ic] = b[ib];
                c_h[ic] = b_h[ib];
                ib++;
            }
        }
        for(;ia < na; ia++, ic++)
        {
            c[ic] = a[ia];
            c_h[ic] = a_h[ia];
        }
        for(;ib < nb; ib++, ic++)
        {
            c[ic] = b[ib];
            c_h[ic] = b_h[ib];
        }
    }

    template<class T, class S>
    void RankTree<T, S>::uniteTrees(RankTree<T, S> &other)
    {
        int this_nodes = countNodes(this->root);
        int other_nodes =  countNodes(other.root);
        if(this_nodes+other_nodes==0)
        {
            return;
        }
        if(this_nodes+other_nodes==1)
        {
            if(other_nodes==1)
            {
                this->root=other.root;
            }
            return;
        }
        int *index = new int();
        S this_keys [this_nodes];
        T this_data [this_nodes];
        treeToArray(this_keys,this_data,index,this->root);
        (*index) = 0;
        S other_keys [other_nodes];
        T other_data [other_nodes];
        treeToArray(other_keys,other_data,index,other.root);
        (*index) = 0;
        S total_keys [this_nodes + other_nodes];
        T total_data[this_nodes + other_nodes];
        merge(this_data,this_keys,this_nodes,other_data,other_keys,other_nodes,total_data,total_keys);
        //treeDelete(other.root);
        BSTNode<T,S> *newtree = createEmptyFullTree(total_keys,total_data,0,this_nodes + other_nodes-1);
        this->root = newtree;
        delete index;
    }


}
#endif //AVL_RANKTREE_H
