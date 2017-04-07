/*********************************************************************************
** Filename:        Weapon.cpp
** Author:          Justin Kruse
** Date:            31 May 2016
** Description:     This file contains the Weapon base class methods
**********************************************************************************/
#include "Weapon.hpp"
#include <iostream>
#include <string>
#include "Item.hpp"
#include "ConsoleManip.hpp"

using std::cout;
using std::endl;


/* Constructor */
Weapon::Weapon(std::string n, std::string t, std::string c)
{
    name = n;
    color = "white";
    ammoType = t;
    ammoColor = c;
    slot1 = NULL;
    slot2 = NULL;
}

/* Default Constructor */
Weapon::Weapon()
{
    name = "Weapon";
    color = "white";
    ammoType = "Ammo";
    ammoColor = "white";
    slot1 = NULL;
    slot2 = NULL;
}

/* Set method */
void Weapon::setName(std::string n)
{
    name = n;
}

/* Set method */
void Weapon::setAmmoColor(std::string c)
{
    ammoColor = c;
}

/* Get method */
std::string Weapon::getName()
{
    return name;
}

/* Get method */
std::string Weapon::getColor()
{
    return color;
}

/* Get method */
Item* Weapon::getSlot1()
{
    return slot1;
}

/* Get method */
Item* Weapon::getSlot2()
{
    return slot2;
}


/******************************************************************************
**                          activateWeapon
** Description: Returns the color of the laser based on the color combinations
**              of crystals:
**              Input                   Output
**              --------------------------------
**              None                    White
**              Red                     Red
**              Green                   Green
**              Blue                    Blue
**              Red + Green             Yellow
**              Red + Blue              Magenta
**              Green + Blue            Cyan
**              --------------------------------
** Parameters:  None.
** Returns:     color of laser fired (string)
******************************************************************************/
std::string Weapon::activateWeapon()
{
    int countRed = 0;
    int countGreen = 0;
    int countBlue = 0;
    int totalCount = 0;


    if(slot1 != NULL)
    {
        if(slot1->getColor() == "red")
            countRed++;
        else if(slot1->getColor() == "green")
            countGreen++;
        else if(slot1->getColor() == "blue")
            countBlue++;

        totalCount++;
    }

    if(slot2 != NULL)
    {
        if(slot2->getColor() == "red")
            countRed++;
        else if(slot2->getColor() == "green")
            countGreen++;
        else if(slot2->getColor() == "blue")
            countBlue++;

        totalCount++;
    }

    if(totalCount == 0)
        ammoColor = "white";
    else if(totalCount == 1)
    {
        if(countRed == 1)
            ammoColor = "red";
        else if(countGreen == 1)
            ammoColor = "green";
        else
            ammoColor = "blue";
    }
    else if(countRed == 1 && totalCount == 2)
    {
        if(countGreen == 1)
            ammoColor = "yellow";
        else
            ammoColor = "magenta";
    }
    else
    {
            ammoColor = "cyan";
    }


    printMyColor(getColor(), getName());
    cout << " shoots a ";
    printMyColor(ammoColor, ammoColor);
    cout << " ";
    printMyColor(ammoColor, ammoType);
    cout << "!" << endl << endl;
    return ammoColor;
}


/******************************************************************************
**                          loadCrystal
** Description: Takes ownership of a crystal and places it in one of the Item
**              *slots, if available.
** Parameters:  Pointer to Item
******************************************************************************/
void Weapon::loadCrystal(Item **c)
{
    Item *temp;

    cout << "Attempting to load ";
        printMyColor((*c)->getColor(), (*c)->getName());
        cout << " in ";
        printMyColor(getColor(), getName());
        cout << "..." << endl;

    delay(500);

    if(slot1 == NULL)
    {
        slot1 = (*c);
        printMyColor((*c)->getColor(), (*c)->getName());
        cout << " added to ";
        printMyColor(getColor(), getName());
        cout << "." << endl;
        temp = NULL;
    }
    else if(slot2 == NULL)
    {
        slot2 = (*c);
        printMyColor((*c)->getColor(), (*c)->getName());
        cout << " added to ";
        printMyColor(getColor(), getName());
        cout << "." << endl;
        temp = NULL;
    }
    else
    {
        cout << "Attempt failed! ";
        printMyColor(getColor(), getName());
        cout << " can only hold two crystals at once." << endl;
        temp = (*c);
    }

    cout << endl;
    weaponStatus();

    (*c) = temp;
}


/******************************************************************************
**                          removeCrystal
** Description: Gives ownership of crystal by returning a pointer to object.
**              Uses color of the crystal to return the crystal. Returns NULL
**              if color does not exist in slots.
** Parameters:  color of crystal to remove.
** Returns:     Pointer to Item Object
******************************************************************************/
Item* Weapon::removeCrystal(std::string c)
{
    Item *tempCrystal = NULL;

    if(slot1 != NULL)
    {
        if(c == slot1->getColor())
        {
            tempCrystal = slot1;
            slot1 = NULL;
        }
    }

    if(slot2 != NULL)
    {
        if(c == slot2->getColor())
        {
            tempCrystal = slot2;
            slot2 = NULL;
        }
    }

    if(tempCrystal != NULL)
    {
        printMyColor(tempCrystal->getColor(), tempCrystal->getName());
        cout << " removed from ";
        printMyColor(getColor(), getName());
        cout << "." << endl;
    }
    else
    {
        cout << "There is not a ";
        printMyColor(c, c + " crystal");
        cout << " in the ";
        printMyColor(getColor(), getName());
        cout << endl;
    }

    cout << endl;
    weaponStatus();

    return tempCrystal;
}


/******************************************************************************
**                          weaponStatus
** Description: Prints the Items in the Slots of the weapon.
** Parameters:  None.
******************************************************************************/
void Weapon::weaponStatus()
{
    printMyColor(getColor(), getName());
    cout << " equipped with:" << endl;

    cout << "Slot 1: ";
    if(slot1 != NULL)
    {
        printMyColor(slot1->getColor(), slot1->getName());
        cout << endl;
    }
    else
    {
        cout << "empty" << endl;
    }


    cout << "Slot 2: ";
    if(slot2 != NULL)
    {
        printMyColor(slot2->getColor(), slot2->getName());
        cout << endl;
    }
    else
    {
        cout << "empty" << endl;
    }
}
