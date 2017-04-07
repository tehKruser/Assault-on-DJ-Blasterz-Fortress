/*****************************************************************************************
** Filename:        ControlRoom.hpp
** Author:          Justin Kruse
** Date:            03 Jun 2016
** Description:     This file contains the ControlRoom class prototypes and data members.
*****************************************************************************************/
#ifndef CONTROLROOM_HPP
#define CONTROLROOM_HPP
#include <string>
#include "Item.hpp"
#include "Weapon.hpp"
#include "Space.hpp"
#include "Hero.hpp"

class ControlRoom : public Space
{
    protected:
        bool showBeamOptions;
        bool showKeyOptions;
        bool showCrystalOptions;
        bool nodeUnprotected;
        bool firstCall;

        struct beam
        {
            std::string name;
            std::string defaultColor;
            std::string comboColor;
            Item *keyHole;
            Item *crystalMount;
        };
        beam leftBeam;
        beam midBeam;
        beam rightBeam;
        beam *activeBeam;
        Item *node;

        Item* getNode();
        void printRoomInfo();
        int printOptions();
        int printBeamOptions();
        int printKeyOptions();
        int printCrystalOptions();
        void printBeamInfo();
        void printBeamDisplay();
        void printNextLevel();
        void heroShootsNode();
        void heroReturnsKey(std::string c);
        void heroTakesKey();
        void heroReturnsCrystal(std::string c);
        void heroTakesCrystal();
        void updateBeam();
        void checkBeams();
        void changeTerrain();
        bool drainHero();
    public:
        ControlRoom();
        virtual ~ControlRoom(){};
        int showOptions();
        void special(int s, Space **as);

    private:
};

#endif // CONTROLROOM_HPP
