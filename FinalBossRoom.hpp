/*****************************************************************************************
** Filename:        FinalBossRoom.hpp
** Author:          04 Jun 2016
** Description:     This file contains the FinalBossRoom class prototypes and data members.
*****************************************************************************************/
#ifndef FINALBOSSROOM_HPP
#define FINALBOSSROOM_HPP
#include <string>
#include "Item.hpp"
#include "Weapon.hpp"
#include "Space.hpp"
#include "Hero.hpp"

class FinalBossRoom : public Space
{
    protected:
        bool turnTables;
        bool cartridges;
        bool records;
        bool mixer;
        bool light1;
        bool light2;
        bool light3;
        bool light4;
        bool light5;
        bool firstPass;
        bool nodeUnprotected;
        bool gameOver;
        Item *node;

        void printRoomInfo();
        void printLights();
        void printOptions();
        Item* getNode();
        void checkLights();
        void heroSetsTurnTable();
        void heroPlacesCartridges();
        void heroSpinsRecord();
        void heroAdjustsMixer();
        void showRoomHints();
        void heroShootsNode();
        bool drainHero();
    public:
        FinalBossRoom();
        virtual ~FinalBossRoom(){};
        int showOptions();
        void special(int s, Space **as);

    private:
};

#endif // FINALBOSSROOM_HPP
