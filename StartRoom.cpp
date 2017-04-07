/*********************************************************************************
** Filename:        StartRoom.cpp
** Author:          Justin Kruse
** Date:            02 Jun 2016
** Description:     This file contains the StartRoom base class methods
**********************************************************************************/
#include "StartRoom.hpp"
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
StartRoom::StartRoom():Space("Lobby", "white")
{
    aLever = false;
    aButton = false;
    aSwitch = false;
    light1 = false;
    light2 = false;
    light3 = false;
    showLightOptions = false;
    weaponUnlocked = false;
    doorsUnlocked = false;
    firstPass = true;
    node = new Item("White Node", "white");
    laserGun = new Weapon("Laser Gun", "laser", "white");
}


/* Get method */
Item* StartRoom::getNode()
{
    Item *temp = node;
    return temp;
}

/******************************************************************************
**                          printLights
** Description: Prints 3 lights - a circle representation for each.
**              Red if the lights are false, green if they are true.
** Parameters:  None.
******************************************************************************/
void StartRoom::printLights()
{
    std::string lightColor1;
    std::string lightColor2;
    std::string lightColor3;

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
        cout << endl;

        if(line2Print)
        {
            for(int j = 0; j < 2; j++)
            {
                /* Print Line 2 */
                printMyColor(lightColor1, line2);
                printMyColor(lightColor2, line2);
                printMyColor(lightColor3, line2);
                cout << endl;

                if(line3Print)
                {
                    for(int k = 0; k < 2; k++)
                    {
                        /* Print Line 3 */
                        printMyColor(lightColor1, line3);
                        printMyColor(lightColor2, line3);
                        printMyColor(lightColor3, line3);
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
** Description: Checks the status of the 3 lights. Unlocks weapons if all true.
** Parameters:  None.
******************************************************************************/
void StartRoom::checkLights()
{
    if(light1 && light2 && light3 && !weaponUnlocked)
    {
        weaponUnlocked = true;
        printMyColor(laserGun->getColor(), laserGun->getName());
        cout << " has been unlocked!" << endl;
    }
}



/******************************************************************************
**                          showOptions
** Description: Makes calls to print the options of the class.
**              Based on showLightOptions, will show:
**              (F) Main options of room / (T) Light Puzzle Options
** Parameters:  None.
** Returns:     Number of options available. Returns 1000 to indicate game over.
******************************************************************************/
int StartRoom::showOptions()
{
    if(drainHero())
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
            clearScreen();
        }


        if(!showLightOptions)
        {
            printPageTitle(" DJ Blasterz Fortress - " + getRoomName() + " ", TITLE_LENGTH);
            cout << "Please select one of the following options: " << endl;
            printOptions();
        }
        else
        {
            printPageTitle(" Investigating Lights ", TITLE_LENGTH);
            printLights();
            checkLights();
            cout << endl << "Please select one of the following options: " << endl;
            printLightOptions();
        }

        if(!showLightOptions)
            return 7;
        else
            return 5;
    }
}


/******************************************************************************
**                          printOptions
** Description: Prints main options for the room.
** Parameters:  None.
******************************************************************************/
void StartRoom::printOptions()
{
    /* View information about the room */
    cout << "1. About this room." << endl;

    /* Option for lights */
    cout << "2. Investigate lights on the wall." << endl;

    /* Options related to laser gun */
    if(laserGun != NULL && !weaponUnlocked)
        cout << "3. Investigate locker." << endl;
    else if(laserGun != NULL && weaponUnlocked)
        cout << "3. Take laser gun from locker." << endl;
    else
        cout << "3. Use laser gun on node." << endl;

    /* Options related to doors */
    cout << "4. Go through left door to ";
    printMyColor(left->getRoomColor(), left->getRoomName());
    cout << "." << endl;

    cout << "5. Go through right door to ";
    printMyColor(right->getRoomColor(), right->getRoomName());
    cout << "." << endl;

    cout << "6. Go through underground tunnel passage to ";
    printMyColor(tunnel->getRoomColor(), tunnel->getRoomName());
    cout << "." << endl;

    cout << "7. View " << theHero->getName() << " the Hero's Health and Inventory." << endl;

}



/******************************************************************************
**                          printLightOptions
** Description: Prints options for the light puzzle.
** Parameters:  None.
******************************************************************************/
void StartRoom::printLightOptions()
{
    cout << "1. About the lights." << endl;
    cout << "2. Pull lever." << endl;
    cout << "3. Push button." << endl;
    cout << "4. Flip switch." << endl;
    cout << "5. Investigate elsewhere." << endl;
}


/******************************************************************************
**                          printRoomInfo
** Description: Prints information about the room to help the user solve it.
** Parameters:  None.
******************************************************************************/
void StartRoom::printRoomInfo()
{
    cout << theHero->getName() << " the Hero entered the lobby of DJ Blasterz Fortress." << endl << endl;
    cout << "There are 3 lights up on the wall." << endl
            << "Below them are a lever, a button and a switch." << endl << endl;
    cout << "Right now, the lights are: " << endl << endl;
    printLights();
    cout << endl;

    delay(500);

    if(laserGun != NULL)
    {
        cout << "There is a laser gun in a locker near the 3 lights." << endl;
        if(!weaponUnlocked)
            cout << "The locker appears locked. A power cable runs from the lights to the locker." << endl;
        else
            cout << "The locker is open. Maybe that laser gun has some use." << endl;

        delay(500);
    }

    cout << endl << "There is a power node on the wall above the doors. " << endl;

    if(getNode()->getColor() == "white")
    {
        cout << "The node glows a bright white." << endl
            << "Power cables run from the node to all of the room's exits." << endl
            << "Is that what is keeping the exits locked?" << endl;
    }
    else
    {
        cout << "The node has been ";
        printMyColor("grey", "neutralized");
        cout << " by the Hero's laser." << endl;
    }

    delay(500);

    cout << endl << "There are 3 ";
    if(doorsUnlocked)
        cout << "unlocked";
    else
        cout << "locked";
    cout << " exits in this room:" << endl
        << "a right door, a left door and an underground tunnel." << endl << endl;

    delay(500);

    cout << endl << "\t\t[ENTER] Back to investigating the Lobby" << endl;
    std::cin.get();
    clearScreen();

}


/***********************************************************************************
**                          printLightInfo
** Description: Prints information about the light puzzle to help the user solve it.
** Parameters:  None.
************************************************************************************/
void StartRoom::printLightInfo()
{
    std::cin.ignore();
    std::cin.clear();

    cout << "There are 3 lights up on the wall." << endl << endl;
    cout << "Below them are a lever, a button and a switch." << endl << endl;
    cout << "Perhaps those operate the lights?" << endl;

    cout << endl << "\t\t[ENTER] Back to investigating the lights" << endl;
    std::cin.get();
    clearScreen();
}



/***********************************************************************************
**                          special
** Description: Executes the main options based on selection of option.
** Parameters:  user selection for special action, Pointer for moving between spaces.
************************************************************************************/
void StartRoom::special(int s, Space **as)
{
    if(!showLightOptions)
    {
        switch(s)
        {
            case 1: printRoomInfo();
                    break;

            case 2: showLightOptions = true;
                    break;

            case 3: weaponActions();
                    break;

            case 4: if(doorsUnlocked)
                        *as = goToSpace(1);
                    else
                    {
                        std::cin.ignore();
                        std::cin.clear();
                        cout << "Left door is locked. There must be a way to unlock it." << endl;
                        cout << endl << "\t\t[ENTER] Back to investigating the Lobby" << endl;
                        std::cin.get();
                        clearScreen();
                    }

                    break;

            case 5: if(doorsUnlocked)
                        *as = goToSpace(2);
                    else
                    {
                        std::cin.ignore();
                        std::cin.clear();
                        cout << "Right door is locked. There must be a way to unlock it." << endl;
                        cout << endl << "\t\t[ENTER] Back to investigating the Lobby" << endl;
                        std::cin.get();
                        clearScreen();
                    }

                    break;

            case 6: if(doorsUnlocked)
                        *as = goToSpace(3);
                    else
                    {
                        std::cin.ignore();
                        std::cin.clear();
                        cout << "Door to tunnel is locked. There must be a way to unlock it." << endl;
                        cout << endl << "\t\t[ENTER] Back to investigating the Lobby" << endl;
                        std::cin.get();
                        clearScreen();
                    }
                    break;

            case 7: theHero->showInventory();
                    break;
        }
    }
    else
    {
        switch(s)
        {
            case 1: printLightInfo();
                    break;

            case 2: heroPullsLever();
                    break;

            case 3: heroPushesButton();
                    break;

            case 4: heroFlipsSwitch();
                    break;

            case 5: showLightOptions = false;
                    break;
        }
    }
}



/***********************************************************************************
**                          weaponActions
** Description: Controls actions related to the weapon class object.
**              - Hero object takes ownership of weapon.
**              - Hints hot to get the weapon
**              - Hero object shoots weapon.
** Parameters:  None.
************************************************************************************/
void StartRoom::weaponActions()
{
    if(laserGun != NULL)
    {
        if(weaponUnlocked)
        {
            theHero->takeWeapon(&laserGun);          // grab weapon
            delay(500);
            printGameTutorial();
        }
        else
        {
            std::cin.clear();
            std::cin.ignore();

            cout << "There is a laser gun is secured in that locker." << endl << endl
                << "There has to be a way to unlock it." << endl;

            cout << endl << "\t\t[ENTER] Back to investigating the Lobby" << endl;
            std::cin.get();
            clearScreen();
        }
    }
    else
    {
        heroShootsNode();                           // shoot the node
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
void StartRoom::heroShootsNode()
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

            doorsUnlocked = true;

            delay(500);
            cout << endl << "Doors to ";
            printMyColor(left->getRoomColor(), left->getRoomName() + ", ");
            printMyColor(right->getRoomColor(), right->getRoomName());
            cout << " and ";
            printMyColor(tunnel->getRoomColor(), tunnel->getRoomName());
            cout << " are unlocked!." << endl;
            delay(1000);
            printColorRoomInfo();
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
**                          heroPullsLever
** Description: Action for Light Puzzle. Lever toggles values for:
**              - ( F ) light1
**              - ( T ) light1 & light3
** Parameters:  None.
************************************************************************************/
void StartRoom::heroPullsLever()
{
    if(!weaponUnlocked)
    {
        if(!aLever)
        {
            light1 = !light1;
        }
        else
        {
            light1 = !light1;
            light3 = !light3;
        }
        aLever = !aLever;
    }
    else
    {
        cout << "Nothing happens. ";
       showRoomHints();
    }
}



/***********************************************************************************
**                          heroPushesButton
** Description: Action for Light Puzzle. Button toggles values for:
**              - ( F ) light1 & light2
**              - ( T ) light1 & light3
** Parameters:  None.
************************************************************************************/
void StartRoom::heroPushesButton()
{
    if(!weaponUnlocked)
    {
        if(!aButton)
        {
            light1 = !light1;
            light2 = !light2;
        }
        else
        {
            light2 = !light2;
            light3 = !light3;
        }
        aButton = !aButton;
    }
    else
    {
        cout << "Nothing happens. ";
        showRoomHints();
    }
}



/***********************************************************************************
**                          heroFlipsSwitch
** Description: Action for Light Puzzle. Button toggles values for:
**              - ( F | T ) light3
** Parameters:  None.
************************************************************************************/
void StartRoom::heroFlipsSwitch()
{
    if(!weaponUnlocked)
    {
        light3 = !light3;
        aSwitch = !aSwitch;
    }
    else
    {
        cout << "Nothing happens. ";
        showRoomHints();
    }
}



/***********************************************************************************
**                          printGameTutorial
** Description: Prints a general tutorial for the basic premise of the game.
** Parameters:  None.
************************************************************************************/
void StartRoom::printGameTutorial()
{
    std::cin.clear();
    std::cin.ignore();

    printPageTitle(" Game Tutorial ", TITLE_LENGTH);
    cout << "Congratulations!" << endl << endl;
    cout << "Here are some things your hero should know about the game" << endl
        << "\tbefore continuing on:" << endl << endl;
    delay(250);
    cout << "- The laser gun has 2 spots to hold crystals." << endl;
    delay(250);
    cout << "- Crystals change the gun's laser color." << endl;
    delay(250);
    cout << "- Combinations of different crystal colors produce " << endl
        << "\tunique laser colors. HINT: RGB color combos!" << endl;
    delay(250);
    cout << "- No crystals in the laser gun produce white lasers." << endl;
    cout << "- There are nodes of various colors throughout DJ Blasterz Fortress." << endl
        << "\tYou must match the color of the laser to the node" << endl
        << "\tin order to neutralize the node." << endl;
    delay(250);
    cout << "- The laser gun can hold 0, 1, or 2 crystals at a time." << endl;
    delay(250);
    cout << "- Due to the immense power of the crystals," << endl
        << "\tonly the laser gun is capable of holding crystals," << endl
        << "\twhich means you can not carry them in your backpack." << endl << endl;
    delay(250);

    cout << "The laser gun currently has no crystals." << endl << endl;
    delay(250);

    cout << "Now, go face the challenges of DJ Blasterz Fortress to stop him" << endl
        << "\tfrom stealing all the color in the world!" << endl << endl;
    delay(250);

    cout << endl << "\t\t[ENTER] Ready!" << endl;
    std::cin.get();
    clearScreen();
}


/***********************************************************************************
**                          printColorRoomInfo
** Description: Prints a message about the next available rooms when they are unlocked.
**              Rooms unlocked in the heroShootsNode() function.
** Parameters:  None.
************************************************************************************/
void StartRoom::printColorRoomInfo()
{
    std::cin.clear();
    std::cin.ignore();
    cout << endl << theHero->getName() << " the Hero now has access to 4 rooms: " << endl;
    printMyColor("red", "Red Room");
    cout << ", ";
    printMyColor("green", "Green Room");
    cout << ", ";
    printMyColor("blue", "Blue Room");
    cout << " and ";
    printMyColor("white", "Control Room");
    cout << "." << endl << endl;

    delay(250);

    cout << "Each of these rooms has a node that must " << endl
        << "\nbe neutralized with the laser gun." << endl << endl;

    delay(250);

    cout << "In the colored rooms, neutralize the nodes to get the keys." << endl << endl;
    cout << "Perhaps those keys can be used in the Control Room..." << endl << endl;
    firstPass = false;

    delay(250);

    cout << endl << "\t\t[ENTER] Let's go!" << endl;
    std::cin.get();
    clearScreen();
}



/******************************************************************************
**                          showRoomHints
** Description: Helps the user with hints on what to do.
** Parameters:  None.
******************************************************************************/
void StartRoom::showRoomHints()
{
    if(laserGun == NULL)
        cout << "That laser gun looks like it could be useful...";
    else if(!doorsUnlocked)
        cout << "I wonder what that laser gun can do...";
    else
        cout << "Perhaps there is something to do in the other rooms...";
    cout << endl;
}


/******************************************************************************
**                          drainHero
** Description: Takes health from the hero object. Every 3 moves drains 2 health.
** Parameters:  None.
** Returns:     True if hero dies, else false for alive.
******************************************************************************/
bool StartRoom::drainHero()
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
