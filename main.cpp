/*********************************************************************************
** Filename:        main.cpp
** Author:          Justin Kruse
** Date:            01 June 2016
** Description:     This file controls the game interaction between the player and
**                  the spaces the player interacts with.
**********************************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>   //Header file needed to use srand and rand
#include <ctime>    //Header file needed to use time
#include <string>
#include "MyFunctions.hpp"
#include "ConsoleManip.hpp"
#include "Space.hpp"
#include "ColorRoom.hpp"
#include "StartRoom.hpp"
#include "ControlRoom.hpp"
#include "Weapon.hpp"
#include "Hero.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::right;

const int TITLE_LENGTH = 76;


int main()
{
    /* Prototype function for Intro */
    void printIntro(Hero *h);

    /* Declare variables */
    int roomOptions;
    int choice;

    /* Create First Five Rooms */
    Space *spawnPoint = new StartRoom();
    Space *redRoom = new ColorRoom("Red Room", "red", "Red Key", "Red Crystal");
    Space *greenRoom = new ColorRoom("Green Room", "green", "Green Key", "Green Crystal");
    Space *blueRoom = new ColorRoom("Blue Room", "blue", "Blue Key", "Blue Crystal");
    Space *beamRoom = new ControlRoom();

    /* Set space relationships */
    spawnPoint->setSpaceRelationships(redRoom, blueRoom, greenRoom, NULL);
    redRoom->setSpaceRelationships(greenRoom, spawnPoint, blueRoom, beamRoom);
    greenRoom->setSpaceRelationships(blueRoom, redRoom, spawnPoint, beamRoom);
    blueRoom->setSpaceRelationships(spawnPoint, greenRoom, redRoom, beamRoom);
    beamRoom->setSpaceRelationships(redRoom, greenRoom, blueRoom, spawnPoint);

    /* Pointer for active room */
    Space *ActiveRoom = spawnPoint;

    /* Create our hero */
    Hero *userHero = new Hero("Zero");



    bool skipIntro = false;

    clearScreen();

    printPageTitle(" Assault on DJ Blasterz Fortress - Game Launcher ", TITLE_LENGTH);
    cout << "Would you like to skip the introduction?" << endl << endl;
    cout << "Note: Not recommended for first play through." << endl;
    cout << "      You'll miss the story if you do!" << endl << endl;
    cout << "1. No." << endl << "2. Yes." << endl << endl;
    cout << "Your choice: ";
    choice = validateInput(true, 1, true, 2);
    if(choice == 2)
        skipIntro = true;

    cin.clear();
    cin.ignore();

    clearScreen();
    printPageTitleWithColor("magenta", " Assault on DJ Blasterz Fortress ", TITLE_LENGTH);

    if(skipIntro)
        cout << userHero->getName() << " the Hero enters the fortress..." << endl << endl;
    else
        printIntro(userHero);

    ActiveRoom->setHero(&userHero);

    do
    {
        roomOptions = ActiveRoom->showOptions();
        if(roomOptions == 1000)
        {
            choice = roomOptions + 1;

            cout << endl <<"Game Over! Thanks for playing!" << endl << endl;

            cout << endl << "\t\t[ENTER] End Game" << endl;

            std::cin.get();
        }
        else
        {
            cout << roomOptions + 1 << ". Exit Program." << endl;
            cout << endl << "Please select your choice: ";
            choice = validateInput(true, 1, true, roomOptions + 1);
            cout << endl;
            clearScreen();
            ActiveRoom->special(choice, &ActiveRoom);

            if(choice == roomOptions + 1)
            {
                printPageTitle(" Game Paused ", TITLE_LENGTH);
                cout << "Are you sure you want to quit?" << endl;
                cout << "1. No." << endl << "2. Yes." << endl;
                cout << "Your choice: ";
                choice = validateInput(true, 1, true, 2);
                if(choice == 2)
                    choice = roomOptions + 1;
                else
                    clearScreen();
            }
        }
    }while(choice != roomOptions + 1);


  return 0;
}

/******************************************************************************
**                          Function:printIntro
** Description: Prints the Intro to Assault on DJ Blasterz Fortress
** Parameters:  Pointer to Hero object to set name.
******************************************************************************/
void printIntro(Hero *h)
{
    std::string heroName;

    cout << "Your hero comes to..." << endl << endl;
    delay(250);
    cout << "Uh oh, your hero has a massive headache and " << endl
        << "doesn't remember very much right now." << endl;

    cout << endl << "Please remind your hero what his name is: ";

    /* Get a name that is no more than 20 characters*/
    do
    {
        getline(cin, heroName);
        if(heroName.length() > 20)
        {
            cin.clear();
            cin.ignore();
            cout << endl << "That doesn't seem right." << endl
                << "Hero's name name is definitely shorter than that." << endl
                << "Please enter a shorter name: ";
        }
    }while(heroName.length() > 20);

    h->setName(heroName);

    cout << endl << "That's right! Of course the hero's name is " << h->getName() << "!" << endl;

    cout << endl << "Press ENTER to continue." << endl;
    cin.get();
    clearScreen();

    cout << "The last thing that " << h->getName() << " the Hero remembers " << endl
        << "is being at DJ Blasterz light show." << endl;

    delay(250);

    cout << endl << "DJ Blasterz was building up to the drop when... when..." << endl;

    cout << endl << "Press ENTER to continue." << endl;
    cin.get();
    clearScreen();

    cout << "... it happened! The dropped happened and " << endl
        << h->getName() << " the Hero's mind was blown!" << endl;

    delay(250);

    cout << endl << "There was so much sensory overload with all of the lights at the show." << endl;

    delay(250);

    cout << endl << "Everything just went dark. And now " << h->getName() << " woke up here." << endl;

    delay(250);

    cout << endl << "But where is here?" << endl;

    delay(250);

    cout << endl << "Oh, there is a sign! \"DJ Blasterz Fortress\"." << endl;

    delay(250);

    cout << endl << "What?! And look, above the fortress!" << endl;

    cout << endl << "Press ENTER to continue." << endl;
    cin.get();
    clearScreen();

    cout << "From the skies are beams of various color energy pouring into the fortress." << endl << endl;

    delay(250);

    cout << "This is like his light show, except something doesn't feel right about this..." << endl;

    delay(250);

    cout << endl << "Can it be? Is it even possible???" << endl;

    cout << endl << "Press ENTER to continue." << endl;
    cin.get();
    clearScreen();

    cout << "DJ Blasterz is stealing color from the world!" << endl << endl;

    delay(250);

    cout << h->getName() << " the Hero can feel the color draining from his life." << endl;
    cout << "Current Hero Color Health: " << h->getHealth() <<endl;

    cout << endl << "He must be stopped and who better to do it than..." << endl << endl;

    delay(250);

    cout << h->getName() << " the Hero!!!" << endl << endl;

    delay(250);

    cout << h->getName() << " the Hero enters the fortress..." << endl << endl;

    cout << endl << "Press ENTER to continue." << endl;
    cin.get();
    clearScreen();
}
