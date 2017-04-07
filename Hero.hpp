/*****************************************************************************************
** Filename:        Hero.hpp
** Author:          Justin Kruse
** Date:            31 May 2016
** Description:     This file contains the Hero class prototypes and data members.
*****************************************************************************************/
#ifndef HERO_HPP
#define HERO_HPP
#include <string>
#include "ConsoleManip.hpp"

#include "Item.hpp"
#include "Weapon.hpp"
#include "Queue.hpp"


class Hero
{
    private:
    protected:
        std::string name;
        Queue backpack;
        Weapon *laser;
        int inBackpack;
        int backpackCapacity;
        int health;
        int moves;
    public:
        Hero(std::string n);
        virtual ~Hero(){};
        void setName(std::string n);
        std::string getName();
        int getHealth();
        Weapon* getWeapon();
        void takeKey(Item **k);
        void takeWeapon(Weapon **w);
        Item* giveKey(std::string keyColor);
        bool hasWeapon();
        void showInventory();
        std::string fireWeapon();
        void updateHealth();
};

#endif // HERO_HPP
