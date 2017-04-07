/*****************************************************************************************
** Filename:        StartRoom.hpp
** Author:          Justin Kruse
** Date:            02 Jun 2016
** Description:     This file contains the StartRoom class prototypes and data members.
*****************************************************************************************/
#ifndef STARTROOM_HPP
#define STARTROOM_HPP
#include <string>
#include "Item.hpp"
#include "Weapon.hpp"
#include "Space.hpp"
#include "Hero.hpp"

class StartRoom : public Space
{
    protected:
        bool aLever;
        bool aButton;
        bool aSwitch;
        bool light1;
        bool light2;
        bool light3;
        bool weaponUnlocked;
        bool firstPass;
        bool doorsUnlocked;
        bool showLightOptions;
        Item *node;
        Weapon *laserGun;

        void printRoomInfo();
        void printLightInfo();
        void printLights();
        void printOptions();
        void printLightOptions();
        void printGameTutorial();
        void printColorRoomInfo();
        Item* getNode();
        void checkLights();
        void weaponActions();
        void heroPullsLever();
        void heroPushesButton();
        void heroFlipsSwitch();
        void showRoomHints();
        void heroShootsNode();
        bool drainHero();
    public:
        StartRoom();
        virtual ~StartRoom(){};
        int showOptions();
        void special(int s, Space **as);
    private:
};

#endif // STARTROOM_HPP
