/*****************************************************************************************
** Filename:        ColorRoom.hpp
** Author:          Justin Kruse
** Date:            31 May 2016
** Description:     This file contains the ColorRoom class prototypes and data members.
*****************************************************************************************/
#ifndef COLORROOM_HPP
#define COLORROOM_HPP
#include <string>
#include "Item.hpp"
#include "Weapon.hpp"

#include "Space.hpp"

class ColorRoom : public Space
{
    protected:
        Item *node;
        Item *key;
        Item *crystal;
        bool keyUnlocked;

        void printOption1();
        void printOption2();
        void printOption3();
        void printOption4();
        void printOption5();
        void printOption6();
        void printOption7();
        void printOption8();
        void setNode(std::string rc);
        Item* getNode();
        Item* getKey();
        Item* getCrystal();
        bool hasKey();
        bool hasCrystal();
        void heroShootsNode();
        void heroTakesKey();
        void heroReturnsKey();
        void heroTakesCrystal();
        void heroReturnsCrystal();
        bool drainHero();
    public:
        ColorRoom(std::string rn, std::string rc, std::string kn, std::string cn);
        virtual ~ColorRoom(){};
        int showOptions();
        void special(int s, Space **as);
    private:
};

#endif // COLORROOM_HPP
