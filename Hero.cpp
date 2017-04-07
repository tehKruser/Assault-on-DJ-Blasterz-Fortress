/*********************************************************************************
** Filename:        Hero.cpp
** Author:          Justin Kruse
** Date:            31 May 2016
** Description:     This file contains the Hero base class methods
**********************************************************************************/
#include "Hero.hpp"
#include <iostream>
#include <string>
#include "Queue.hpp"


using std::cout;
using std::endl;

/* Constructor */
Hero::Hero(std::string n)
{
    name = n;
    laser = NULL;
    inBackpack = 0;
    backpackCapacity = 3;
    health = 100;
    moves = 0;
}

/* Set method */
void Hero::setName(std::string n)
{
    name = n;
}

/* Get method */
std::string Hero::getName()
{
    return name;
}

/* Get method */
int Hero::getHealth()
{
    return health;
}

/* Get method */
Weapon* Hero::getWeapon()
{
    return laser;
}

/* Simple method to check if weapon pointer points to an object */
bool Hero::hasWeapon()
{
    if(laser == NULL)
        return false;
    else
        return true;
}

/******************************************************************************
**                          takeKey
** Description: Takes ownership of Key Item Object and stores in backpack queue.
**              Previous owner of key has its pointer set to NULL.
** Parameters:  Pointer to key.
******************************************************************************/
void Hero::takeKey(Item **k)
{
    cout << getName() << " the Hero has the ";
    printMyColor((*k)->getColor(), (*k)->getName());
    cout << "." << endl;

    backpack.add(&*k);
    inBackpack++;

    (*k) = NULL;
}

/******************************************************************************
**                          giveKey
** Description: Gives ownership of Key Item Object. Looks for the color of the
**              key to give. If specified key isn't in backpack, returns NULL.
** Parameters:  color of key to give.
** Returns:     Pointer to Item object.
******************************************************************************/
Item* Hero::giveKey(std::string keyColor)
{
    Item* tempKey;

    if(backpack.isEmpty())
    {
        cout << "There are no keys in the backpack." << endl;
        tempKey = NULL;
    }
    else
    {
        for(int i = 0; i < inBackpack; i++)
        {
            tempKey = backpack.remove();
            if(keyColor == tempKey->getColor())
            {
                i = inBackpack;
            }
            else
            {
                backpack.add(&tempKey);
                tempKey = NULL;
            }
        }

        if(tempKey != NULL)
        {
            cout << getName() << " the Hero has placed the ";
            printMyColor(tempKey->getColor(), tempKey->getName());
            cout << "." << endl;
        }
        else
        {
            cout << getName() << " the Hero cannot place any keys here." << endl;
        }
    }

    return tempKey;
}



/******************************************************************************
**                          takeWeapon
** Description: Takes ownership of weapon object.
**              Previous owner of weapon has its pointer set to NULL.
** Parameters:  Pointer to weapon.
** Returns:     Pointer to Item object.
******************************************************************************/
void Hero::takeWeapon(Weapon **w)
{
    if(!hasWeapon())
    {
        laser = (*w);
        (*w) = NULL;

        cout << getName() << " the Hero has the ";
        printMyColor(laser->getColor(), laser->getName());
        cout << "." << endl;
    }
    else
    {
        cout << "Hero can only hold one weapon." << endl;
    }
}


/******************************************************************************
**                          showInventory
** Description: Displays Hero Health, Keys, Weapon and Crystals in weapon.
** Parameters:  None.
******************************************************************************/
void Hero::showInventory()
{
    cout << getName() << " the Hero's Health: " << getHealth() << endl;

    cout << "Inventory: " << endl;
    cout << "Key: ";
    if(!backpack.isEmpty())
    {
        Item *tempKey;
        std::string front;
        bool atFront = false;

        tempKey = backpack.remove();
        printMyColor(tempKey->getColor(), tempKey->getName());
        cout << endl;

        front = tempKey->getColor();
        backpack.add(&tempKey);

        do
        {
            tempKey = backpack.remove();
            if(tempKey->getColor() == front)
            {
                atFront = true;
            }
            else
            {
                cout << "Key: ";
                printMyColor(tempKey->getColor(), tempKey->getName());
                cout << endl;
            }
            backpack.add(&tempKey);

        }while(!atFront);
    }
    else
        cout << "none." << endl;

    cout << endl << "Weapon: ";
    if(hasWeapon())
    {
        printMyColor(laser->getColor(), laser->getName());
        cout << endl;

        cout << endl << "Weapon info:" << endl;
        laser->weaponStatus();
    }
    else
    {
        cout << "none." << endl;
    }
    cout << endl;
}


/******************************************************************************
**                          fireWeapon
** Description: Hero fires weapon.
** Parameters:  None.
** Returns:     color of laser fired (string)
******************************************************************************/
std::string Hero::fireWeapon()
{
    cout << getName() << " the Hero aims the ";
    printMyColor(laser->getColor(), laser->getName());
    cout << " and fires." << endl << endl;
    delay(500);
    return laser->activateWeapon();
}


/******************************************************************************
**                          updateHealth
** Description: Hero health is decreased by 2 every 3 moves.
** Parameters:  None.
******************************************************************************/
void Hero::updateHealth()
{
    moves++;

    if(moves >= 3)
    {
       health -= 2;
       cout << endl << getName() << " the Hero is losing color from his life!" << endl;
       cout << "Color energy remaining: " << getHealth() << endl;
       moves = 0;
    }
}
