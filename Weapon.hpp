/*****************************************************************************************
** Filename:        Weapon.hpp
** Author:          Justin Kruse
** Date:            31 May 2016
** Description:     This file contains the Weapon class prototypes and data members.
*****************************************************************************************/
#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <string>
#include "Item.hpp"


class Weapon
{
    private:
    protected:
        std::string name;
        std::string color;
        std::string ammoType;
        std::string ammoColor;
        Item *slot1;
        Item *slot2;
    public:
        Weapon(std::string n, std::string t, std::string c);
        Weapon();
        virtual ~Weapon(){};
        void setName(std::string n);
        void setAmmoColor(std::string c);
        std::string getName();
        std::string getColor();
        Item* getSlot1();
        Item* getSlot2();
        std::string activateWeapon();
        void loadCrystal(Item **c);
        Item* removeCrystal(std::string c);
        void weaponStatus();
};

#endif // WEAPON_HPP
