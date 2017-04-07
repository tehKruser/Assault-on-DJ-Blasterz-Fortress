/*********************************************************************************
** Filename:        ControlRoom.cpp
** Author:          Justin Kruse
** Date:            03 Jun 2016
** Description:     This file contains the ControlRoom base class methods
**********************************************************************************/
#include "ControlRoom.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include "MyFunctions.hpp"
#include "ConsoleManip.hpp"
#include "Space.hpp"
#include "Hero.hpp"
#include "FinalBossRoom.hpp"

#include "Space.hpp"

const int TITLE_LENGTH = 76;

using std::cout;
using std::endl;


/* Constructor */
ControlRoom::ControlRoom():Space("Control Room", "white")
{
    showBeamOptions = false;
    showKeyOptions = false;
    showCrystalOptions = false;
    nodeUnprotected = false;
    node = new Item("White Node", "white");
    leftBeam = {"Left Light Beam", "red", "red", NULL, NULL};
    midBeam = {"Middle Light Beam", "green", "green", NULL, NULL};
    rightBeam = {"Right Light Beam","blue", "blue", NULL, NULL};
    activeBeam = NULL;
    firstCall = true;
}


/* Get method */
Item* ControlRoom::getNode()
{
    Item *temp = node;
    return temp;
}



/******************************************************************************
**                          showOptions
** Description: Makes calls to print the options of the class.
**              Tiers of Options:
**              Main -> Beam Options (left, mid, right) ->
**              key options / crystal options
** Parameters:  None.
** Returns:     Number of options available. Returns 1000 to indicate game over.
******************************************************************************/
int ControlRoom::showOptions()
{
    int numOptions;

    if(drainHero())
    {
        return 1000;
    }
    else
    {
        printPageTitle(" DJ Blasterz Fortress - " + getRoomName() + " ", TITLE_LENGTH);
        printBeamDisplay();
        if(firstCall)
        {
            printRoomInfo();
            firstCall = false;
            clearScreen();
            printPageTitle(" DJ Blasterz Fortress - " + getRoomName() + " ", TITLE_LENGTH);
            printBeamDisplay();
        }

        if(!showBeamOptions)
            numOptions = printOptions();
        else if(showKeyOptions)
            numOptions = printKeyOptions();
        else if(showCrystalOptions)
            numOptions = printCrystalOptions();
        else
            numOptions = printBeamOptions();

        return numOptions;
    }
}


/******************************************************************************
**                          printOptions
** Description: Prints first tier options (main).
** Parameters:  None.
******************************************************************************/
int ControlRoom::printOptions()
{
    cout << "Please select one of the following options: " << endl;

    /* View information about the room */
    cout << "1. About this room." << endl;

    /* Option for the left beam */
    cout << "2. Investigate the Left Light Beam." << endl;

    /* Option for middle beam */
    cout << "3. Investigate the Middle Light Beam." << endl;

    /* Option for right beam */
    cout << "4. Investigate the Right Light Beam." << endl;

    /* Option for laser gun */
    cout << "5. Shoot the node with the laser gun." << endl;

    cout << "6. Go through portal to ";
    printMyColor(left->getRoomColor(), left->getRoomName());
    cout << "." << endl;

    cout << "7. Go through portal to ";
    printMyColor(right->getRoomColor(), right->getRoomName());
    cout << "." << endl;

    cout << "8. Go through portal to ";
    printMyColor(tunnel->getRoomColor(), tunnel->getRoomName());
    cout << "." << endl;

    cout << "9. View " << theHero->getName() << " the Hero's Health and Inventory." << endl;

    return 9;
}



/******************************************************************************
**                          printBeamOptions
** Description: Prints second tier options (beams).
** Parameters:  None.
******************************************************************************/
int ControlRoom::printBeamOptions()
{
    printPageTitle(activeBeam->name, TITLE_LENGTH);

    cout << endl << "Please select one of the following options: " << endl;

    cout << "1. About the beam." << endl;
    cout << "2. Insert a key into the beam." << endl;
    cout << "3. Insert a crystal into the beam." << endl;
    cout << "4. Investigate elsewhere." << endl;

    return 4;
}


/******************************************************************************
**                          printKeyOptions
** Description: Prints third tier options (key actions).
** Parameters:  None.
******************************************************************************/
int ControlRoom::printKeyOptions()
{
    printPageTitle(activeBeam->name + " Key Options ", TITLE_LENGTH);

    cout << endl << "Please select one of the following options: " << endl;

    int optionNum = 0;

    if(activeBeam->keyHole == NULL)
    {
        cout << "1. Insert a ";
        printMyColor("red", "red key");
        cout << endl;
        cout << "2. Insert a ";
        printMyColor("green", "green key");
        cout << endl;
        cout << "3. Insert a ";
        printMyColor("blue", "blue key");
        cout << endl;

        optionNum = 3;

    }
    else
    {
        cout << "1. Remove ";
        printMyColor((activeBeam->keyHole)->getColor(), (activeBeam->keyHole)->getName());
        cout << "." << endl;

        optionNum = 1;
    }

    optionNum++;
    cout << optionNum << ". Other beam options." << endl;

    return optionNum;

}



/******************************************************************************
**                          printCrystalOptions
** Description: Prints third tier options (crystal actions).
** Parameters:  None.
******************************************************************************/
int ControlRoom::printCrystalOptions()
{
    printPageTitle(activeBeam->name + " Crystal Options ", TITLE_LENGTH);

    cout << endl << "Please select one of the following options: " << endl;

    int optionNum = 0;

    if(activeBeam->crystalMount == NULL)
    {
        cout << "1. Insert a ";
        printMyColor("red", "red crystal");
        cout << endl;
        cout << "2. Insert a ";
        printMyColor("green", "green crystal");
        cout << endl;
        cout << "3. Insert a ";
        printMyColor("blue", "blue crystal");
        cout << endl;

        optionNum = 3;
    }
    else
    {
        optionNum++;
        cout << "1. Take the ";
        printMyColor( (activeBeam->crystalMount)->getColor(), (activeBeam->crystalMount)->getName());
        cout << "." << endl;

        optionNum = 1;
    }

    optionNum++;
    cout << optionNum << ". Other beam options." << endl;

    return optionNum;

}



/******************************************************************************
**                          printRoomInfo
** Description: Prints information about the room to help the user solve it.
** Parameters:  None.
******************************************************************************/
void ControlRoom::printRoomInfo()
{
    std::cin.clear();
    std::cin.ignore();

    cout << "This is DJ Blasterz Control Room!" << endl << endl;
    cout << "Three beams of energy are directed at a node." << endl << endl;
    cout << "As long as those beams have color," << endl
        << "\tDJ Blasterz is stealing color from the world!" << endl << endl;
    cout << "Combine different colored keys and crystals" << endl
        << "\twith the beams' light source colors to create white light." << endl << endl;
    cout << "When all three beams emit white light," << endl
        <<"\tthe node in the room will become unprotected." << endl << endl;
    cout << "That's when you take your chance to shoot the node!" << endl << endl;

    cout << "Don't worry, you can figure this out! Ready?" << endl;

    cout << endl << "\t\t[ENTER] Ready!" << endl;
    std::cin.get();
    clearScreen();
}


/******************************************************************************
**                          printBeamInfo
** Description: Prints information about the beams to help the user solve the puzzle.
** Parameters:  None.
******************************************************************************/
void ControlRoom::printBeamInfo()
{
    std::cin.ignore();
    std::cin.clear();

    cout << "Try combining different keys and crystals to" << endl
        << "\tget the output of the light beam to become white light." << endl << endl;

    cout << endl << "\t\t[ENTER] Back to investigating the beam" << endl;
    std::cin.get();
    clearScreen();
}



/***********************************************************************************
**                          special
** Description: Executes the main options based on selection of option.
**              Switch statements for scenarios:
**              - Main room actions
**              - Single beam actions
**              - key item actions
**              - crystal item actions
** Parameters:  user selection for special action, Pointer for moving between spaces.
************************************************************************************/
void ControlRoom::special(int s, Space **as)
{
    if(!showBeamOptions)
    {
        switch(s)
        {
            case 1: printRoomInfo();
                    break;

            case 2: showBeamOptions = true;
                    activeBeam = &leftBeam;
                    break;

            case 3: showBeamOptions = true;
                    activeBeam = &midBeam;
                    break;

            case 4: showBeamOptions = true;
                    activeBeam = &rightBeam;
                    break;

            case 5: heroShootsNode();
                    break;

            case 6: *as = goToSpace(1);
                    break;

            case 7: *as = goToSpace(2);
                    break;

            case 8: *as = goToSpace(3);
                    break;

            case 9: theHero->showInventory();
                    break;
        }
    }
    else if(showKeyOptions)
    {
        if(activeBeam->keyHole == NULL)
        {
            switch(s)
            {
                case 1: heroReturnsKey("red");
                        break;

                case 2: heroReturnsKey("green");
                        break;

                case 3: heroReturnsKey("blue");
                        break;

                case 4: showKeyOptions = false;
                        break;
            }
        }
        else
        {
            switch(s)
            {
                case 1: heroTakesKey();
                        break;

                case 2: showKeyOptions = false;
                        break;
            }
        }

    }
    else if(showCrystalOptions)
    {
        if(activeBeam->crystalMount == NULL)
        {
            switch(s)
            {
                case 1: heroReturnsCrystal("red");
                        break;

                case 2: heroReturnsCrystal("green");
                        break;

                case 3: heroReturnsCrystal("blue");
                        break;

                case 4: showCrystalOptions = false;
                        break;
            }
        }
        else
        {
            switch(s)
            {
                case 1: heroTakesCrystal();
                        break;

                case 2: showCrystalOptions = false;
                        break;
            }
        }
    }
    else
    {
        switch(s)
        {
            case 1: printBeamInfo();
                    break;

            case 2: showKeyOptions = true;
                    break;

            case 3: showCrystalOptions = true;
                    break;

            case 4: showBeamOptions = false;
                    activeBeam = NULL;
                    break;
        }
    }
    updateBeam();
    checkBeams();
}


/***********************************************************************************
**                          heroTakesKey
** Description: Hero object takes ownership of key item and places it into backpack queue.
** Parameters:  None.
************************************************************************************/
void ControlRoom::heroReturnsKey(std::string c)
{
    cout << theHero->getName() << " the Hero reaches into backpack for a ";
    printMyColor(c, c + " key");
    cout << "..." << endl;
    activeBeam->keyHole = theHero->giveKey(c);
}


/***********************************************************************************
**                          heroReturnsCrystal
** Description: Hero object returns ownership of crystal item to class object.
** Parameters:  None.
************************************************************************************/
void ControlRoom::heroTakesKey()
{
    cout << theHero->getName() << " the Hero reaches for the key..." << endl;
    theHero->takeKey(&activeBeam->keyHole);
}


/***********************************************************************************
**                          heroReturnsCrystal
** Description: Hero object returns ownership of crystal item to class object.
** Parameters:  None.
************************************************************************************/
void ControlRoom::heroReturnsCrystal(std::string c)
{
    cout << endl << theHero->getName() << " the Hero opens the ";
    printMyColor( (theHero->getWeapon())->getColor(), (theHero->getWeapon())->getName() );
    cout << " to get the crystal..." << endl;
    activeBeam->crystalMount = (theHero->getWeapon())->removeCrystal(c);
}


/***********************************************************************************
**                          heroTakesCrystal
** Description: Hero object takes ownership of crystal item and loads it into weapon.
** Parameters:  None.
************************************************************************************/
void ControlRoom::heroTakesCrystal()
{
    cout << theHero->getName() << " the Hero reaches for the crystal..." << endl;
    (theHero->getWeapon())->loadCrystal(&activeBeam->crystalMount);
}



/***********************************************************************************
**                          heroShootsNode
** Description: Hero object fires weapon at node:
**              - Node is already neutralized, nothing happens.
**              - Laser color neutralizes node.
**              - Laser color doesn't match node color. Node is unaffected.
** Parameters:  None.
************************************************************************************/
void ControlRoom::heroShootsNode()
{

    std::string laserColor;
    laserColor = theHero->fireWeapon();

    if(!nodeUnprotected)
    {
        cout << "Failed! Node is under protection from the 3 beams of light." << endl << endl;
        cout << "White light from all 3 beams may drop the node's defenses." << endl << endl;
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

            delay(500);
            changeTerrain();
            printNextLevel();
        }
        else
        {
            printMyColor(node->getColor(), node->getName());
            cout << " is unaffected by " << laserColor << " lasers." << endl;
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
**                          updateBeam
** Description: Controls the color of the output beams based on colors of:
**              Source beam, Key, Crystal
**                Inputs                  Output Beam Color
**               ------------------------------------------------
**                red                     red
**                green                   green
**                blue                    blue
**                red + blue              magenta
**                red + green             yellow
**                blue + green            cyan
**                red + green + blue      white
**               -------------------------------------------------
** Parameters:  None.
************************************************************************************/
void ControlRoom::updateBeam()
{
    if(activeBeam != NULL)
    {
        if(!nodeUnprotected)
        {
            bool hasRed = false;
            bool hasGreen = false;
            bool hasBlue = false;

            if(activeBeam->defaultColor == "red")
                hasRed = true;
            else if(activeBeam->defaultColor == "green")
                hasGreen = true;
            else if(activeBeam->defaultColor == "blue")
                hasBlue = true;

            if(activeBeam->keyHole != NULL)
            {
                if( (activeBeam->keyHole)->getColor() == "red")
                    hasRed = true;
                else if( (activeBeam->keyHole)->getColor() == "green")
                    hasGreen = true;
                else if( (activeBeam->keyHole)->getColor() == "blue")
                    hasBlue = true;
            }

            if(activeBeam->crystalMount != NULL)
            {
                if( (activeBeam->crystalMount)->getColor() == "red")
                    hasRed = true;
                else if( (activeBeam->crystalMount)->getColor() == "green")
                    hasGreen = true;
                else if( (activeBeam->crystalMount)->getColor() == "blue")
                    hasBlue = true;
            }


            if(hasRed && hasGreen && hasBlue)
            {
                if(activeBeam->comboColor != "white")
                {
                    cout << "The " << activeBeam->name << " is surging with ";
                    printMyColor("white", "white light");
                    cout << "!" << endl << endl
                    << "The protection on the node is losing strength!" << endl;
                }
                activeBeam->comboColor = "white";
            }
            else if(hasRed && !hasGreen && !hasBlue)
                activeBeam->comboColor = "red";
            else if(!hasRed && hasGreen && !hasBlue)
                activeBeam->comboColor = "green";
            else if(!hasRed && !hasGreen && hasBlue)
                activeBeam->comboColor = "blue";
            else if(hasRed && hasGreen && !hasBlue)
                activeBeam->comboColor = "yellow";
            else if(hasRed && !hasGreen && hasBlue)
                activeBeam->comboColor = "magenta";
            else if(!hasRed && hasGreen && hasBlue)
                activeBeam->comboColor = "cyan";
        }
    }
}



/***********************************************************************************
**                          checkBeams
** Description: Checks for red + blue + green combo to get output beam color of white.
**              Sets nodeUnprotected to true if all beams are white.
** Parameters:  None.
************************************************************************************/
void ControlRoom::checkBeams()
{
    if(leftBeam.comboColor == "white" && midBeam.comboColor == "white" && rightBeam.comboColor == "white")
    {
        if(!nodeUnprotected)
        {
            cout << "All the beams are surging with white light!" << endl << endl
            << "The node is left completely unprotected, do something quick!" << endl;

            nodeUnprotected = true;
        }
    }
}



/***********************************************************************************
**                          printBeamDisplay
** Description: Prints a color display of the source beams, keys, crystals and output beams
** Parameters:  None.
************************************************************************************/
void ControlRoom::printBeamDisplay()
{
    std::string header = "Light Beam    ";
    std::string row1 = "Source Light: ";
    std::string row2 = "Key:          ";
    std::string row3 = "Crystal:      ";
    std::string row4 = "Output Light: ";
    std::string hBorder = std::string(70,'-');

    unsigned colLength = header.length();

    std::string beamSource = std::string(12, '/');
    std::string beamOutput = std::string(12, '/');
    std::string leftBeamSourceColor = leftBeam.defaultColor;
    std::string midBeamSourceColor = midBeam.defaultColor;
    std::string rightBeamSourceColor = rightBeam.defaultColor;

    std::string leftBeamOutputColor = leftBeam.comboColor;
    std::string midBeamOutputColor = midBeam.comboColor;
    std::string rightBeamOutputColor = rightBeam.comboColor;

    std::string leftBeamKey;
    std::string midBeamKey;
    std::string rightBeamKey;

    std::string leftBeamKeyColor;
    std::string midBeamKeyColor;
    std::string rightBeamKeyColor;

    if(leftBeam.keyHole == NULL)
    {
        leftBeamKey = "None.";
        leftBeamKeyColor = "white";
    }
    else
    {
        leftBeamKey = leftBeam.keyHole->getName();
        leftBeamKeyColor = leftBeam.keyHole->getColor();
    }

    if(midBeam.keyHole == NULL)
    {
        midBeamKey = "None.";
        midBeamKeyColor = "white";
    }
    else
    {
        midBeamKey = midBeam.keyHole->getName();
        midBeamKeyColor = midBeam.keyHole->getColor();
    }

    if(rightBeam.keyHole == NULL)
    {
        rightBeamKey = "None.";
        rightBeamKeyColor = "white";
    }
    else
    {
        rightBeamKey = rightBeam.keyHole->getName();
        rightBeamKeyColor = rightBeam.keyHole->getColor();
    }

    std::string leftBeamCrystal;
    std::string midBeamCrystal;
    std::string rightBeamCrystal;

    std::string leftBeamCrystalColor;
    std::string midBeamCrystalColor;
    std::string rightBeamCrystalColor;

    if(leftBeam.crystalMount == NULL)
    {
        leftBeamCrystal = "None.";
        leftBeamCrystalColor = "white";
    }
    else
    {
        leftBeamCrystal = leftBeam.crystalMount->getName();
        leftBeamCrystalColor = leftBeam.crystalMount->getColor();
    }

    if(midBeam.crystalMount == NULL)
    {
        midBeamCrystal = "None.";
        midBeamCrystalColor = "white";
    }
    else
    {
        midBeamCrystal = midBeam.crystalMount->getName();
        midBeamCrystalColor = midBeam.crystalMount->getColor();
    }

    if(rightBeam.crystalMount == NULL)
    {
        rightBeamCrystal = "None.";
        rightBeamCrystalColor = "white";
    }
    else
    {
        rightBeamCrystal = rightBeam.crystalMount->getName();
        rightBeamCrystalColor = rightBeam.crystalMount->getColor();
    }

    cout << std::string(colLength, ' ') <<  "\t" << header << "\t" << header << "\t" << header << endl;
    cout << hBorder << endl;

    /* row 1 print with colors */
    cout << row1 << "\t";
    printMyColor(leftBeamSourceColor, beamSource + std::string(colLength - beamSource.length(), ' ') + "\t");
    printMyColor(midBeamSourceColor, beamSource + std::string(colLength - beamSource.length(), ' ') + "\t");
    printMyColor(rightBeamSourceColor, beamSource + std::string(colLength - beamSource.length(), ' ') + "\t");
    cout << endl;

    /* row 2 print with colors */
    cout << row2 << "\t";
    printMyColor(leftBeamKeyColor, leftBeamKey + std::string(colLength - leftBeamKey.length(), ' ') + "\t");
    printMyColor(midBeamKeyColor, midBeamKey + std::string(colLength - midBeamKey.length(), ' ') + "\t");
    printMyColor(rightBeamKeyColor, rightBeamKey + std::string(colLength - rightBeamKey.length(), ' ') + "\t");
    cout << endl;

    /* row 3 print with colors */
    cout << row3 << "\t";
    printMyColor(leftBeamCrystalColor, leftBeamCrystal + std::string(colLength - leftBeamCrystal.length(), ' ') + "\t");
    printMyColor(midBeamCrystalColor, midBeamCrystal + std::string(colLength - midBeamCrystal.length(), ' ') + "\t");
    printMyColor(rightBeamCrystalColor, rightBeamCrystal + std::string(colLength - rightBeamCrystal.length(), ' ') + "\t");
    cout << endl;

     /* row 4 print with colors */
    cout << row4 << "\t";
    printMyColor(leftBeamOutputColor, beamOutput + std::string(colLength - beamOutput.length(), ' ') + "\t");
    printMyColor(midBeamOutputColor, beamOutput + std::string(colLength - beamOutput.length(), ' ') + "\t");
    printMyColor(rightBeamOutputColor, beamOutput + std::string(colLength - beamOutput.length(), ' ') + "\t");
    cout << endl;

    cout << endl;
}



/***********************************************************************************
**                          printNextLevel
** Description: Print when puzzle complete. Informs the user that a new room is available.
** Parameters:  None.
************************************************************************************/
void ControlRoom::printNextLevel()
{
    std::cin.ignore();
    std::cin.clear();

    cout << endl << "Your hero has defeated DJ Blasterz control room!" << endl << endl;
    cout << "The combination of white beam energy and the laser gun" << endl
        << "\thas caused a critical power surge in the Fortress!" << endl << endl;
    delay(250);
    cout << "The top of the Fortress has exploded, and the Mixing Studio that" << endl
    << "DJ Blasterz is in has fallen and destroyed the lobby." << endl << endl;
    delay(250);
    cout << "Head over to the Mixing Studio and put an end to DJ Blasterz!" << endl
    << "You'll have to go through one of the colored rooms to get there." << endl << endl;

    cout << endl << "\t\t[ENTER] Let's finish this!" << endl;
    std::cin.get();
    clearScreen();
}



/***********************************************************************************
**                          changeTerrain
** Description: Deletes the object being pointed to by portal and replaces it
**              with a new Space: FinalBossRoom.
**              Resets all of the pointers for the connected Space objects.
** Parameters:  None.
************************************************************************************/
void ControlRoom::changeTerrain()
{
    delete portal;
    portal = NULL;
    Space *finalRoom = new FinalBossRoom();

    left->setSpaceRelationships(right, finalRoom, tunnel, this);
    right->setSpaceRelationships(tunnel, left, finalRoom, this);
    tunnel->setSpaceRelationships(finalRoom, right, left, this);
    this->setSpaceRelationships(left, right, tunnel, portal);
    finalRoom->setSpaceRelationships(left, tunnel, right, NULL);
}


/******************************************************************************
**                          drainHero
** Description: Takes health from the hero object. Every 3 moves drains 2 health.
** Parameters:  None.
** Returns:     True if hero dies, else false for alive.
******************************************************************************/
bool ControlRoom::drainHero()
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
