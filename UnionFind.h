#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_


#include "Exceptions.h"

namespace Ehsan
{

    template<class T>   
    class UnionFind
    {
    private:
        int numberOfElements;
        int *size;//an array
        int *parent;//an array
        T *data;//an array
        //explanation:
        //the array size : is an array of the elements including the size of element i.
        //the array parent : is an array including the parent of a given element such 
        //that is the number and the index are equal it means that it is its own parent.
        //the array data : is an array including the Groups such that data[i] is the group with id equal to i.

    public:
        UnionFind(int numberOfElements);
        ~UnionFind();//virtual?
        //should I delete copy c'tor && operator=
        //the make(i) method that we saw in class is manually done at the beginning
        int Find(int i);
        void increasesize(int group_id, int increase = 1);
        void Merge(T& to_grow,int to_grow_index, T& to_delete,int to_delete_index);
        void Union(int p,int q);
    };
    
    template<class T>
    UnionFind<T>::UnionFind(int numberOfElements):
    numberOfElements(numberOfElements),
    size(new int[numberOfElements + 1]()),
    parent(new int[numberOfElements + 1]()),
    data(new T[numberOfElements+1]())
    {
        for (int i = 0; i < (numberOfElements+1) ; i++)
        {
            parent[i] = i;//parent[0] is abandoned.
            size[i] = 0; // should it be one?
        }
    }
    
    template<class T>
    UnionFind<T>::~UnionFind()
    {
        delete[] size;
        delete[] parent;
    }
    
    template<class T>
    int UnionFind<T>::Find(int i)
    {
        //check that the group is legal
        if ( i < 1 || i >= numberOfElements)// is : 1 <= groupID < k ?
        {
            throw GroupDoesntExist();
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
    void UnionFind<T>::increasesize(int group_id, int increase = 1)
    {
        int root = Find(group);
        size[root] += increase;
        return;
    }

    template<class T>
    void UnionFind<T>::Merge(T& to_grow,int to_grow_index, T& to_delete,int to_delete_index)
    {
        to_grow += to_delete;
        parent[to_delete] = to_grow;
        increasesize(to_grow,size[to_delete]);  
        // data[to_delete] = nullptr;
        return;
    }

    template<class T>
    void UnionFind<T>::Union(int q,int p)
    {
        //check that the union is legal
        if (Find(q) == Find(p))
        {
            // return;//error?
            throw CantUnionSameGroup();
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






// if (size[group_1_index] <= size[group_2_index])
//         {
//             if (size[group_1_index] == size[group_2_index])
//             {
//                 if (p > q)
//                 {
//                     // group_1 += group_2;
//                     // parent[group_2_index] = group_1_index;
//                     // increasesize(group_1_index,size[group_2_index]);
//                     // size[group_1_index] += size[group_2_index];  
//                     //data[group_2_index] = nullptr;
//                     Merge(group_1,group_1_index,group_2,group_2_index);
//                 }
//                 else
//                 {
//                     // group_2 += group_1;
//                     // parent[group_1_index] = group_2_index;
//                     // increasesize(group_2_index,size[group_1_index]);
//                     // size[group_2_index] += size[group_1_index];
//                     //data[group_1_index] = nullptr;
//                     Merge(group_2,group_2_index,group_1,group_1_index);
//                 }
//             }
//             else //size[group_1_index] < size[group_2_index] 
//             {
//                 // group_2 += group_1;//operator += is to be coded
//                 // parent[group_1_index] = group_2_index; 
//                 // increasesize(group_2_index,size[group_1_index]);
//                 // size[group_2_index] += size[group_1_index];
//                 // data[group_1_index] = nullptr;
//                 Merge(group_2,group_2_index,group_1,group_1_index);
//             }
//         }
//         else
//         {
//             // group_1 += group_2;//operator 2 is to be coded watch out : operator += isn't symmetric
//             // parent[group_2_index] = group_1_index;
//             // increasesize(group_1_index,size[group_2_index]); 
//             // size[group_1_index] += size[group_2_index];
//             // data[group_2_index] = nullptr;
//             Merge(group_1,group_1_index,group_2,group_2_index);
//         }