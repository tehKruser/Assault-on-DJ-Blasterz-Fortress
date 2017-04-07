/*********************************************************************************
** Filename:        ColorRoom.cpp
** Author:          Justin Kruse
** Date:            31 May 2016
** Description:     This file contains the ColorRoom base class methods
**********************************************************************************/
#include "ColorRoom.hpp"
#include <iostream>
#include <string>
#include "MyFunctions.hpp"
#include "ConsoleManip.hpp"

#include "Space.hpp"

const int TITLE_LENGTH = 76;

using std::cout;
using std::endl;


/* Constructor */
ColorRoom::ColorRoom(std::string rn, std::string rc, std::string kn, std::string cn):Space(rn, rc)
{
    //this->roomColor = roomcolor;
    keyUnlocked = false;
    setNode(rc);
    key = new Item(kn, rc);
    crystal = new Item(cn, rc);
}


/* Set method for Node Item*/
void ColorRoom::setNode(std::string rc)
{
    /* Node is initialized with a particular color based on the room color */
    if(rc == "red")
        node = new Item("Yellow Node", "yellow");
    else if(rc == "green")
        node = new Item("Cyan Node", "cyan");
    else if(rc == "blue")
        node = new Item("Magenta Node", "magenta");
}

/* Get method */
Item* ColorRoom::getNode()
{
    Item *temp = node;
    return temp;
}


/* Get method */
Item* ColorRoom::getKey()
{
    Item *temp = key;
    return temp;
}


/* Get method */
Item* ColorRoom::getCrystal()
{
    Item *temp = crystal;
    return temp;
}


/* Simple method to check if Space has the key item */
bool ColorRoom::hasKey()
{
    if(key != NULL)
        return true;
    else
        return false;
}


/* Simple method to check if Space has the crystal item */
bool ColorRoom::hasCrystal()
{
    if(crystal != NULL)
        return true;
    else
        return false;
}


/******************************************************************************
**                          printOption1
** Description: Prints option: Use Laser
** Parameters:  None.
******************************************************************************/
void ColorRoom::printOption1()
{
    cout << "1. Use laser on ";
        printMyColor(getNode()->getColor(), getNode()->getName());
        cout << "." << endl;
}


/******************************************************************************
**                          printOption2
** Description: Prints option: Take crystal or return crystal
** Parameters:  None.
******************************************************************************/
void ColorRoom::printOption2()
{
    if(hasCrystal())
    {
        cout << "2. Take ";
            printMyColor(getCrystal()->getColor(), getCrystal()->getName());
            cout << "." << endl;
    }
    else
    {
        cout << "2. Return crystal." << endl;
    }
}


/******************************************************************************
**                          printOption3
** Description: Prints option: Take key or return key
** Parameters:  None.
******************************************************************************/
void ColorRoom::printOption3()
{
    if(hasKey())
    {
        cout << "3. Take ";
            printMyColor(getKey()->getColor(), getKey()->getName());
            cout << "." << endl;
    }
    else
    {
        cout << "3. Return key." << endl;
    }
}


/******************************************************************************
**                          printOption4
** Description: Prints option: Go to different space - left
** Parameters:  None.
******************************************************************************/
void ColorRoom::printOption4()
{
    cout << "4. Go through left door to ";
        printMyColor(left->getRoomColor(), left->getRoomName());
        cout << "." << endl;
}


/******************************************************************************
**                          printOption5
** Description: Prints option: Go to different space - right
** Parameters:  None.
******************************************************************************/
void ColorRoom::printOption5()
{
    cout << "5. Go through right door to ";
        printMyColor(right->getRoomColor(), right->getRoomName());
        cout << "." << endl;
}


/******************************************************************************
**                          printOption6
** Description: Prints option: Go to different space - tunnel
** Parameters:  None.
******************************************************************************/
void ColorRoom::printOption6()
{
    cout << "6. Get into underground tunnel and go to ";
        printMyColor(tunnel->getRoomColor(), tunnel->getRoomName());
        cout << "." << endl;
}


/******************************************************************************
**                          printOption7
** Description: Prints option: Go to different space - portal
** Parameters:  None.
******************************************************************************/
void ColorRoom::printOption7()
{
    cout << "7. Take portal to ";
        printMyColor(portal->getRoomColor(), portal->getRoomName());
        cout << "." << endl;
}


/******************************************************************************
**                          printOption8
** Description: Prints option: Show Hero's Health and Inventory
** Parameters:  None.
******************************************************************************/
void ColorRoom::printOption8()
{
    cout << "8. See " << theHero->getName() << " the Hero's Health and Inventory." << endl;
}



/******************************************************************************
**                          showOptions
** Description: Makes calls to print the options of the class.
** Parameters:  None.
** Returns:     Number of options available. Returns 1000 to indicate game over.
******************************************************************************/
int ColorRoom::showOptions()
{
    if(drainHero())
    {
        return 1000;
    }
    else
    {
        printPageTitleWithColor(getRoomColor(), " DJ Blasterz Fortress - " + getRoomName() + " ", TITLE_LENGTH);

        printOption1();
        printOption2();
        printOption3();
        printOption4();
        printOption5();
        printOption6();
        printOption7();
        printOption8();

        return 8;
    }
}



/***********************************************************************************
**                          special
** Description: Executes the main options based on selection of option.
** Parameters:  user selection for special action, Pointer for moving between spaces.
************************************************************************************/
void ColorRoom::special(int s, Space **as)
{
    switch(s)
    {
        case 1: heroShootsNode();
                break;

        case 2: if(hasCrystal())
                    heroTakesCrystal();
                else
                    heroReturnsCrystal();
                break;

        case 3: if(hasKey())
                    heroTakesKey();
                else
                    heroReturnsKey();
                break;

        case 4: *as = goToSpace(1);
                break;

        case 5: *as = goToSpace(2);
                break;

        case 6: *as = goToSpace(3);
                break;

        case 7: *as = goToSpace(4);
                break;

        case 8: theHero->showInventory();
                break;
    }
}



/***********************************************************************************
**                          heroShootsNode
** Description: Hero object fires weapon at node:
**              - Node is already neutralized, nothing happens.
**              - Laser color neutralizes node.
**              - Laser color doesn't match node color. Node is unaffected.
** Parameters:  None.
************************************************************************************/
void ColorRoom::heroShootsNode()
{
    std::string laserColor;
    laserColor = theHero->fireWeapon();

    if(getNode()->getColor() != "gray")
    {
        if(laserColor == getNode()->getColor())
        {
            node->setName("Neutralized Node");
            node->setColor("gray");
            cout << "Node has been neutralized! It becomes ";
            printMyColor("gray", "dim");
            cout << " and powerless." << endl;

            keyUnlocked = true;
            printMyColor(key->getColor(), key->getName());
            cout << " has been unlocked!" << endl << endl;

        }
        else
        {
            printMyColor(node->getColor(), node->getName());
            cout << " is unaffected by " << laserColor << " lasers." << endl << endl;
        }
    }
    else
    {
        printMyColor(node->getColor(), node->getName());
        cout << " is already neutralized." << endl << endl;
    }
    delay(500);
}



/***********************************************************************************
**                          heroTakesCrystal
** Description: Hero object takes ownership of crystal item and loads it into weapon.
** Parameters:  None.
************************************************************************************/
void ColorRoom::heroTakesCrystal()
{
    if(!hasCrystal())
        cout << "There is no crystal here." << endl;
    else
    {
        cout << theHero->getName() << " the Hero reaches for the crystal..." << endl;
        delay(500);
        (theHero->getWeapon())->loadCrystal(&crystal);
        delay(500);
    }
}


/***********************************************************************************
**                          heroReturnsCrystal
** Description: Hero object returns ownership of crystal item to class object.
** Parameters:  None.
************************************************************************************/
void ColorRoom::heroReturnsCrystal()
{
    if(hasCrystal())
        cout << "There is already a crystal here." << endl;
    else
    {
        cout << theHero->getName() << " the Hero opens the ";
        printMyColor( (theHero->getWeapon())->getColor(), (theHero->getWeapon())->getName() );
        cout << "to get the crystal..." << endl;
        crystal = (theHero->getWeapon())->removeCrystal(getRoomColor());
    }
    delay(500);
}


/***********************************************************************************
**                          heroTakesKey
** Description: Hero object takes ownership of key item and places it into backpack queue.
** Parameters:  None.
************************************************************************************/
void ColorRoom::heroTakesKey()
{
    if(!hasKey())
        cout << "There is no key here." << endl;
    else if(!keyUnlocked)
    {
        cout << "Key is immovable. Perhaps that ";
        printMyColor(node->getColor(), node->getName());
        cout << " has something to do with it..." << endl;
    }
    else
    {
        cout << theHero->getName() << " the Hero reaches for the key..." << endl;
        theHero->takeKey(&key);
    }
}



/***********************************************************************************
**                          heroReturnsCrystal
** Description: Hero object returns ownership of crystal item to class object.
** Parameters:  None.
************************************************************************************/
void ColorRoom::heroReturnsKey()
{
    if(hasKey())
        cout << "There is already a key here!" << endl;
    else
    {
        cout << theHero->getName() << " the Hero reaches into backpack for a ";
        printMyColor(this->roomColor, this->roomColor + " key");
        cout << "..." << endl;
        key = theHero->giveKey(this->roomColor);
    }
}



/******************************************************************************
**                          drainHero
** Description: Takes health from the hero object. Every 3 moves drains 2 health.
** Parameters:  None.
** Returns:     True if hero dies, else false for alive.
******************************************************************************/
bool ColorRoom::drainHero()
{
    bool heroDies = false;

    theHero->updateHealth();

    if(theHero->getHealth() <= 0)
    {
        clearScreen();
        printPageTitle(" Game Over! ", TITLE_LENGTH);
        heroDies = true;
        cout << "Oh no! DJ Blasterz has drained all the color from the world!" << endl << endl;

        cout << theHero->getName() << " the Hero has been defeated and can no longer continue!" << endl;
    }

    return heroDies;
}
