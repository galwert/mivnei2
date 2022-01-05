#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_




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
        void Union(T& p,T& q);
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
            size[i] = 1;
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
        if ( i < 1 || i >= numberOfElements)// is : 1 <= groupID < k ?
        {
            //throw GroupDoesntExist();
            //return -1;?
        }
        int current = 0;

        while (current != parent[current])
        {
            current = parent[current];
        }

        return current;
    }

    template<class T>
    void UnionFind<T>::Union(T& p, T& q)
    {
        T& group_1 = data[Find(q)];
        T& group_2 = data[Find(p)];
        if (group_1 == group_2)
        {
            // throw ERROR();
            // return;
        }
        
        if (group_1 <= group_2)
        {
            group_2 += group1;//operator 2 is to be coded
            parent[Find(q)] = Find(p); 
            size[Find(q)]+=size[Find(p)];
        }
        else
        {
            group1 += group2;//operator 2 is to be coded watch out : operator += isn't symmetric
            parent[Find(p)] = Find(q);
            size[Find(p)]+=size[Find(q)];
        }

        
    }




} // namespace Ehsan


#endif