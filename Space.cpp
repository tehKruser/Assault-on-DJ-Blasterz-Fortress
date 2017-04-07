/*********************************************************************************
** Filename:        Space.cpp
** Author:          Justin Kruse
** Date:            31 May 2016
** Description:     This file contains the Space base class methods
**********************************************************************************/
#include "Space.hpp"
#include "iostream"
#include <string>

/* Constructor */
Space::Space(std::string rn, std::string rc)
{
    roomName = rn;
    roomColor = rc;
    left = NULL;
    right = NULL;
    tunnel = NULL;
    portal = NULL;
    theHero = NULL;
}

/* Set method */
void Space::setSpaceRelationships(Space *l, Space *r, Space *t, Space *p)
{
    left = l;
    right = r;
    tunnel = t;
    portal = p;
}

void Space::setHero(Hero **h)
{
    theHero = (*h);
}

/* Get method */
std::string Space::getRoomName()
{
    return roomName;
}

/* Get method */
std::string Space::getRoomColor()
{
    return roomColor;
}


Space* Space::goToSpace(int s)
{
    Space *temp;

    switch(s)
    {
        case 1: temp = left;
                break;
        case 2: temp = right;
                break;
        case 3: temp = tunnel;
                break;
        case 4: temp = portal;
                break;
    }

    std::cout << theHero->getName() << " the Hero goes to ";
    printMyColor(temp->getRoomColor(), temp->getRoomName());
    std::cout << "..." << std::endl << std::endl;

    delay(500);

    temp->setHero(&theHero);
    theHero = NULL;

    return temp;
}
