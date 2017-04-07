/*********************************************************************************
** Filename:        FinalBossRoom.cpp
** Author:          Justin Kruse
** Date:            04 Jun 2016
** Description:     This file contains the FinalBossRoom base class methods
**********************************************************************************/
#include "FinalBossRoom.hpp"
#include <iostream>
#include <string>
#include "MyFunctions.hpp"
#include "ConsoleManip.hpp"
#include "Space.hpp"
#include "Hero.hpp"

#include "Space.hpp"

const int TITLE_LENGTH = 76;

using std::cout;
using std::endl;


/* Constructor */
FinalBossRoom::FinalBossRoom():Space("DJ Mixing Room", "white")
{
    turnTables = false;
    cartridges = false;
    records = false;
    mixer = false;
    light1 = false;
    light2 = false;
    light3 = false;
    light4 = false;
    light5 = false;
    nodeUnprotected = false;
    firstPass = true;
    node = new Item("White Node", "white");
    gameOver = false;
}


/* Get method */
Item* FinalBossRoom::getNode()
{
    Item *temp = node;
    return temp;
}


/******************************************************************************
**                          showOptions
** Description: Makes calls to print the display and options of the room.
** Parameters:  None.
** Returns:     Number of options available. Returns 1000 to indicate game over.
******************************************************************************/
int FinalBossRoom::showOptions()
{
    if(drainHero())
    {
        return 1000;
    }
    else if(gameOver)
    {
        return 1000;
    }
    else
    {
        if(firstPass)
        {
            printPageTitle(" DJ Blasterz Fortress - " + getRoomName() + " ", TITLE_LENGTH);
            printRoomInfo();
            firstPass = false;
        }
        printPageTitle(" DJ Blasterz Fortress - " + getRoomName() + " ", TITLE_LENGTH);
        printLights();
        checkLights();
        cout << "Please select one of the following options: " << endl;
        printOptions();

        return 11;
    }

}


/******************************************************************************
**                          printOptions
** Description: Prints main options for the room.
** Parameters:  None.
******************************************************************************/
void FinalBossRoom::printOptions()
{
    /* View information about the room */
    cout << "1. About this room." << endl;

    /* DJ options */
    cout << "2. Set the Turntables." << endl;
    cout << "3. Adjust the cartridges (needles)." << endl;
    cout << "4. Spin the records." << endl;
    cout << "5. Adjust the mixer." << endl;

    /* Shoot at the node */
    cout << "6. Shoot the node on DJ Blasterz." << endl;

    /* Options related to doors */
    cout << "7. Go through left door to ";
    printMyColor(left->getRoomColor(), left->getRoomName());
    cout << "." << endl;

    /* Options related to doors */
    cout << "8. Go through right door to ";
    printMyColor(right->getRoomColor(), right->getRoomName());
    cout << "." << endl;

    /* Options related to doors */
    cout << "9. Go through underground tunnel to ";
    printMyColor(tunnel->getRoomColor(), tunnel->getRoomName());
    cout << "." << endl;

    cout << "10. View " << theHero->getName() << " the Hero's Health and Inventory." << endl;

    cout << "11. Cheat and see a solution to the puzzle." << endl;

}


/******************************************************************************
**                          printRoomInfo
** Description: Prints information about the room to help the user solve it.
** Parameters:  None.
******************************************************************************/
void FinalBossRoom::printRoomInfo()
{
    std::cin.clear();
    std::cin.ignore();

    cout << "You've made it to DJ Blasterz Mixing Room!" << endl << endl;

    cout << "DJ Blasterz is all set up and about to make the beat drop again." << endl << endl;

    cout << "He is wearing a white power node, but it is being protected by " << endl
        << "5 lights. This looks similar to the puzzle in the lobby." << endl << endl
        << "It looks like there is an extra DJ set up that can change all those lights" << endl
        << "to green. If successful, the power node will be unprotected." << endl << endl;

    cout << theHero->getName() << " the Hero needs get on that other DJ set up," << endl
        << "out-DJ DJ Blasterz and neutralize his power node or he'll never stop" << endl
        << "trying to steal all the color!" << endl << endl;

    cout << "At the other DJ set up, there are a set of turntables, cartridges (needles " << endl
        << "for the records), records and a sound mixer." << endl
        << "Figure out how each DJ component affects the light colors." << endl << endl;

    cout << endl << "\t\t[ENTER] Back to pwning DJ Blasterz" << endl;
    std::cin.get();
    clearScreen();
}



void FinalBossRoom::showRoomHints()
{
    cout << "While there are many solutions, one of them is as follows." << endl << endl;
    cout << "With all lights red:" << endl;
    cout << "Mixer x 1" << endl;
    cout << "Record x 2" << endl;
    cout << "Cartridge X 2" << endl;
}


/***********************************************************************************
**                          special
** Description: Executes the main options based on selection of option.
** Parameters:  user selection for special action, Pointer for moving between spaces.
************************************************************************************/
void FinalBossRoom::special(int s, Space **as)
{
    switch(s)
    {
        case 1: printRoomInfo();
                break;

        case 2: heroSetsTurnTable();
                break;

        case 3: heroPlacesCartridges();
                break;

        case 4: heroSpinsRecord();
                break;

        case 5: heroAdjustsMixer();
                break;

        case 6: heroShootsNode();
                break;

        case 7: *as = goToSpace(1);
                break;

        case 8: *as = goToSpace(2);
                break;

        case 9: *as = goToSpace(3);
                break;

        case 10: theHero->showInventory();
                break;

        case 11: showRoomHints();
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
void FinalBossRoom::heroShootsNode()
{
    std::string laserColor;
    laserColor = theHero->fireWeapon();

    if(!nodeUnprotected)
    {
        cout << "Node on DJ Blasterz is under protection from lasers!" << endl <<endl;
        cout << "The Hero needs to out DJ him to make the node vulnerable." << endl;
    }
    else if(getNode()->getColor() != "gray")
    {
        if(laserColor == getNode()->getColor())
        {
            node->setName("Neutralized Node");
            node->setColor("gray");
            cout << "Node has been neutralized! It becomes ";
            printMyColor("gray", "dim");
            cout << " and powerless." << endl;

            cout << endl << theHero->getName() << " the Hero did it! DJ Blasterz has been defeated!" << endl << endl;

            cout << "Color is now safe. Now, if only " << theHero->getName() << " can just find" << endl
            << "his way back to the club's parking lot to get his car." << endl << endl;

            cout << "You think there is a bus stop nearby? ..." << endl << endl;

            cout << theHero->getName() << " the Hero End of Game Health: " << theHero->getHealth();

            gameOver = true;

            delay(500);
        }
        else
        {
            printMyColor(node->getColor(), node->getName());
            cout << endl << " is unaffected by " << laserColor << " lasers." << endl;
        }
    }
    else
    {
        printMyColor(node->getColor(), node->getName());
        cout << " is already neutralized." << endl;
    }
    delay(500);

}


/***********************************************************************************
**                          heroSetsTurnTable
** Description: Action for Light Puzzle. Lever toggles values for:
**              - ( F ) light1 & light3
**              - ( T ) light4 & light5
** Parameters:  None.
************************************************************************************/
void FinalBossRoom::heroSetsTurnTable()
{
    if(!nodeUnprotected)
    {
        if(!turnTables)
        {
            light1 = !light1;
            light3 = !light3;
        }
        else
        {
            light4 = !light4;
            light5 = !light5;
        }
        turnTables = !turnTables;
    }
    else
    {
        cout << "Nothing happens. DJ Blasterz has already been defeated!" << endl;
    }
}


/***********************************************************************************
**                          heroPlacesCartridges
** Description: Action for Light Puzzle. Lever toggles values for:
**              - ( F ) light5
**              - ( T ) light2 & light3 & light5
** Parameters:  None.
************************************************************************************/
void FinalBossRoom::heroPlacesCartridges()
{
    if(!nodeUnprotected)
    {
        if(!cartridges)
        {
            light5 = !light5;
        }
        else
        {
            light2 = !light2;
            light3 = !light3;
            light5 = !light5;
        }
        cartridges = !cartridges;
    }
    else
    {
        cout << "Nothing happens. DJ Blasterz has already been defeated!" << endl;
    }
}


/***********************************************************************************
**                          heroPlacesCartridges
** Description: Action for Light Puzzle. Lever toggles values for:
**              - ( F ) light1
**              - ( T ) light1 & light3 & light4
** Parameters:  None.
************************************************************************************/
void FinalBossRoom::heroSpinsRecord()
{
    if(!nodeUnprotected)
    {
        if(!records)
        {
            light1 = !light1;
        }
        else
        {
            light1 = !light1;
            light3 = !light3;
            light4 = !light4;
        }
        records = !records;

    }
    else
    {
        cout << "Nothing happens. DJ Blasterz has already been defeated!" << endl;
    }
}


/***********************************************************************************
**                          heroPlacesCartridges
** Description: Action for Light Puzzle. Lever toggles values for:
**              - ( F ) light1 & light3 & light5
**              - ( T ) light1 & light2
** Parameters:  None.
************************************************************************************/
void FinalBossRoom::heroAdjustsMixer()
{
    if(!nodeUnprotected)
    {
        if(!mixer)
        {
            light1 = !light1;
            light3 = !light3;
            light5 = !light5;
        }
        else
        {
            light1 = !light1;
            light2 = !light2;
        }
        mixer = !mixer;
    }
    else
    {
        cout << "Nothing happens. DJ Blasterz has been already defeated!" << endl;
    }
}


/******************************************************************************
**                          printLights
** Description: Prints 5 lights - a circle representation for each.
**              Red if the lights are false, green if they are true.
** Parameters:  None.
******************************************************************************/
void FinalBossRoom::printLights()
{
    std::string lightColor1;
    std::string lightColor2;
    std::string lightColor3;
    std::string lightColor4;
    std::string lightColor5;

    if(light1)
        lightColor1 = "green";
    else
        lightColor1 = "red";

    if(light2)
        lightColor2 = "green";
    else
        lightColor2 = "red";

    if(light3)
        lightColor3 = "green";
    else
        lightColor3 = "red";

    if(light4)
        lightColor4 = "green";
    else
        lightColor4 = "red";

    if(light5)
        lightColor5 = "green";
    else
        lightColor5 = "red";

    std::string line1 = "   ##   ";
    std::string line2 = "  ####  ";
    std::string line3 = " ###### ";

    bool line2Print = true;
    bool line3Print = true;

    for(int i = 0; i < 2; i++)
    {
         /* Print Line 1 */
        printMyColor(lightColor1, line1);
        printMyColor(lightColor2, line1);
        printMyColor(lightColor3, line1);
        printMyColor(lightColor4, line1);
        printMyColor(lightColor5, line1);
        cout << endl;

        if(line2Print)
        {
            for(int j = 0; j < 2; j++)
            {
                /* Print Line 2 */
                printMyColor(lightColor1, line2);
                printMyColor(lightColor2, line2);
                printMyColor(lightColor3, line2);
                printMyColor(lightColor4, line2);
                printMyColor(lightColor5, line2);
                cout << endl;

                if(line3Print)
                {
                    for(int k = 0; k < 2; k++)
                    {
                        /* Print Line 3 */
                        printMyColor(lightColor1, line3);
                        printMyColor(lightColor2, line3);
                        printMyColor(lightColor3, line3);
                        printMyColor(lightColor4, line3);
                        printMyColor(lightColor5, line3);
                        cout << endl;
                    }
                    line3Print = false;
                }
            }
            line2Print = false;
        }
    }

    cout << endl;
}



/******************************************************************************
**                          checkLights
** Description: Checks the status of the 5 lights. Unlocks weapons if all true.
** Parameters:  None.
******************************************************************************/
void FinalBossRoom::checkLights()
{
    if(light1 && light2 && light3 && light4 && light5)
    {
        nodeUnprotected = true;
        cout << endl << "The node on DJ Blasterz has been exposed!" << endl << endl
            << theHero->getName() << " the Hero needs to use the laser gun on it!" << endl << endl;
    }
}



/******************************************************************************
**                          drainHero
** Description: Takes health from the hero object. Every 3 moves drains 2 health.
** Parameters:  None.
** Returns:     True if hero dies, else false for alive.
******************************************************************************/
bool FinalBossRoom::drainHero()
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
