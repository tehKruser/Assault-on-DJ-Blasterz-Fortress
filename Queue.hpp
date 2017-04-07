/*********************************************************************************
** Filename:        Queue.hpp
** Author:          Justin Kruse
** Date:            11 May 2016
** Description:     This file contains the Queue Class members and methods
**********************************************************************************/
#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "Item.hpp"

class Queue
{
    private:
        struct QueueNode
        {
            Item *aKey;
            QueueNode *next;
        };
        QueueNode *front;
        QueueNode *rear;
    public:
        Queue();
        ~Queue();
        void add(Item **k);
        Item* remove();
        bool isEmpty() const;
        void clear();

    protected:

};

#endif // QUEUE_HPP
