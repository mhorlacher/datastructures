#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

class Skiplist
{
    private:

        //node element in skiplist
        struct ListNode
        {
            //value of node
            int _val;

            //pointer to right node
            ListNode *_right;
            //pointer to blow node
            ListNode *_down;

            ListNode(int val, ListNode *right, ListNode *down)
            {
                _val = val;
                _right = right;
                _down = down;
            }


        };
        ListNode *_StartNode;

        unsigned GetRandomLevel();

    public:

        Skiplist();
        virtual ~Skiplist();

        //returns total hight of skiplist
        unsigned height() const;
        //returns number of (unique) elements in skiplist
        size_t numElem() const;

        bool insert(const int iVal);
        bool find(const int sVal);
        bool remove(const int rVal);

        //visualize the skiplist row by row
        void visualize();

};

#endif /* SKIPLIST_H */
