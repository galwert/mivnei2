#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_


#include "Exceptions.h"

namespace Ehsan
{

    template<class T>   
    class UnionFind
    {
    public:
        int numberOfElements;
        int *size;//an array
        int *parent;//an array
        T *data;//an array
        int scale;//additional info
        //explanation:
        //the array size : is an array of the elements including the size of element i.
        //the array parent : is an array including the parent of a given element such 
        //that is the number and the index are equal it means that it is its own parent.
        //the array data : is an array including the Groups such that data[i] is the group with id equal to i.


        UnionFind(int numberOfElements,int scale);
        ~UnionFind();
        int Find(int i);
        void increasesize(int group_id, int increase = 1);
        void Merge(T& to_grow,int to_grow_index, T& to_delete,int to_delete_index);
        void Union(int p,int q);
    };
    
    template<class T>
    UnionFind<T>::UnionFind(int numberOfElements,int scale):
    numberOfElements(numberOfElements),
    size(new int[numberOfElements + 1]()),
    parent(new int[numberOfElements + 1]()),
    data(new T[numberOfElements+1]())
    {
        for (int i = 0; i < (numberOfElements+1) ; i++)
        {
            parent[i] = i;
            size[i] = 0;
            // data[i]=new T(scale);
        }
    }
    
    template<class T>
    UnionFind<T>::~UnionFind()
    {
        delete[] size;
        delete[] parent;
        // for (int i = 0; i < (numberOfElements+1) ; i++)
        // {
        //     delete data[i];
        // }
        delete[] data;
    }
    
    template<class T>
    int UnionFind<T>::Find(int i)
    {
        //check that the group is legal
        if ( i < 0 || i >= numberOfElements)// is : 1 <= groupID < k ?
        {
            return -1;
        }

        //find the main parent of i
        int current = i;
        while (current != parent[current])
        {
            current = parent[current];
        }

        //shrinking paths
        int root = current;
        current = i;
        while (current != parent[current])
        {
            int old_parent = parent[current];
            parent[current] = root;
            current = parent[old_parent];
        }

        return root;
    }

    template<class T>
    void UnionFind<T>::increasesize(int group_id, int increase)
    {
        int root = Find(group_id);
        size[root] += increase;
        return;
    }

    template<class T>
    void UnionFind<T>::Merge(T& to_grow,int to_grow_index, T& to_delete,int to_delete_index)
    {
        to_grow += to_delete;
        // MergeGeneric(to_grow,to_delete);
        // delete to_delete;
        /**
         * **
         * **
         * **
         * **
         * **
         * should delete the to_delete group
         */
        parent[to_delete_index] =  to_grow_index;
        increasesize(to_grow_index,size[to_delete_index]);
        // data[to_delete] = nullptr;
        return;
    }

    template<class T>
    void UnionFind<T>::Union(int q,int p)
    {
        //check that the union is legal
        if (Find(q) == Find(p))
        {
            return;
        }

        // find the groups that you want to Union
        int group_1_index = Find(q);
        int group_2_index = Find(p);
        T& group_1 = data[group_1_index];
        T& group_2 = data[group_2_index];
        
        // Unite the groups according to size
        if (size[group_1_index] <= size[group_2_index])
        {
            if (size[group_1_index] == size[group_2_index])
            {
                if (q > p) // q - is group_1 and p - is group_2
                {
                    Merge(group_1,group_1_index,group_2,group_2_index);
                }
                else
                {
                    Merge(group_2,group_2_index,group_1,group_1_index);
                }
            }
            else //size[group_1_index] < size[group_2_index] 
            {
                Merge(group_2,group_2_index,group_1,group_1_index);
            }
        }
        else
        {
            Merge(group_1,group_1_index,group_2,group_2_index);
        }

        return;
    }




} // namespace Ehsan


#endif