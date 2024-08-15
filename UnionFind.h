
#ifndef DATASTRUCTURES_HW2_UNIONFIND_H
#define DATASTRUCTURES_HW2_UNIONFIND_H

#include "datastructures.h"
#include <iostream>
#include <memory>

using namespace std;

typedef enum
{
    UNION_NULL_ARGS,
    UNION_SUCCESS,
    UNION_MEM_FAIL
} statusUnion;

class UnionFind : public std::enable_shared_from_this<UnionFind>
{
public:
    int fleetId;
    int size;  // num of ships in the fleet
    int extra; // represents the extra value for rank the pirates got

    int numofships;
    shared_ptr<UnionFind> father;

    // UnionFind()=default;
    explicit UnionFind(int fleet_id) : fleetId(fleet_id), size(0), extra(0), numofships(1)
    {

        father = nullptr;
    }

    //    ~UnionFind() {
    //        if (father != nullptr) {
    //            delete father;
    //            //father = nullptr;
    //        }
    //    };

    ////// my destructor

    ~UnionFind()
    {
        // if (father != nullptr) {
        //     delete father;
        // }
    }

    shared_ptr<UnionFind> find()
    {
        auto tmp = shared_from_this();

        while (tmp->father != nullptr)
        {
            tmp = tmp->father;
        }
        return tmp;
        // auto it=this;
        // //if (it== nullptr) return tmp;
        // while (it->father!= nullptr)
        // {
        //     auto x=it->father;
        //     it->father=tmp;
        //     it=x;
        // }
        // return tmp;
    }

    int getSize()
    {
        return size;
    }

    // shared_ptr<UnionFind> findHead(int group_id){
    shared_ptr<UnionFind> findhead()
    {

        shared_ptr<UnionFind> tmp1;
        // shared_ptr<UnionFind> tmp2;
        shared_ptr<UnionFind> head;
        // get the head
        tmp1 = shared_from_this();
        while (tmp1->father != nullptr)
        {
            tmp1 = tmp1->father;
        }
        head = tmp1; // root found

        auto tmp = shared_from_this();
        int sum_t = tmp->extra;

        while (tmp != head && tmp->father != head)
        {
            sum_t += tmp->father->extra;
            tmp = tmp->father;
        }

        auto iterate = shared_from_this();
        auto compress = iterate;
        int substract = 0;
        while (iterate != head && iterate->father != head)
        {
            compress = iterate->father;
            iterate->father = head;
            substract = iterate->extra;
            iterate->extra = sum_t;
            iterate = compress;
            sum_t -= substract;
        }
        return head;
    }
};

// UnionFind *UnionFind::findhead() {
//     auto tmp=this;
//     while (tmp->father!= nullptr)
//     {
//         tmp=tmp->father;
//     }

//     return tmp;
// }

#endif // DATASTRUCTURES_HW2_UNIONFIND_H
