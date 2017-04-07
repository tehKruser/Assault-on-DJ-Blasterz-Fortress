/*********************************************************************************
** Filename:        Queue.cpp
** Author:          Justin Kruse
** Date:            11 May 2016
** Description:     This file contains the definitions for Queue Class methods.
**********************************************************************************/
#include "Queue.hpp"
#include "Item.hpp"
#include <iostream>
#include <cstddef>

/* Constructor */
Queue::Queue()
{
    front = NULL;
    rear = NULL;
}


/* Destructor */
Queue::~Queue()
{
    clear();
}


/******************************************************************************
**                          Queue:add()
** Description: This function creates a new queue node in the rear of the queue
**              for a character value.
** Parameters:  character value
******************************************************************************/
void Queue::add(Item **k)
{
    if(isEmpty())
    {
        front = new QueueNode{(*k), NULL};
        rear = front;
    }
    else
    {
        rear->next = new QueueNode{(*k), NULL};
        rear = rear->next;
    }
}


/******************************************************************************
**                          Queue:remove()
** Description: This function removes a queue node from the front of the queue
**              and returns the value that was in the queue node.
** Parameters:  none.
******************************************************************************/
Item* Queue::remove()
{
    QueueNode *tempN;
    Item *tempK;

    if(isEmpty())
    {
        std::cout << "The queue is empty!" << std::endl;
        tempK = NULL;
    }
    else
    {
        tempN = front;
        tempK = front->aKey;

        front = front->next;
        delete tempN;
    }

    return tempK;
}


/******************************************************************************
**                          Queue:isEmpty()
** Description: This function returns true if queue is empty, else false.
** Parameters:  none.
******************************************************************************/
bool Queue::isEmpty() const
{
    if(front == NULL)
        return true;
    else
        return false;
}


/******************************************************************************
**                          Queue:clear()
** Description: This function removes all queue nodes from the queue
** Parameters:  none.
******************************************************************************/
void Queue::clear()
{
    Item *k; /* Dummy Creature */

    while(!isEmpty())
    {
        k = remove();
        delete k;
    }

}

