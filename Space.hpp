/*****************************************************************************************
** Filename:        Space.hpp
** Author:          Justin Kruse
** Date:            31 May 2016
** Description:     This file contains the Space class prototypes and data members.
*****************************************************************************************/
#ifndef SPACE_HPP
#define SPACE_HPP
#include <string>

#include "Item.hpp"
#include "Hero.hpp"
#include "Weapon.hpp"


class Space
{
    private:
    protected:
        std::string roomName;
        std::string roomColor;
        Space *left;
        Space *right;
        Space *tunnel;
        Space *portal;
        Hero *theHero;
    public:
        Space(std::string rn, std::string rc);
        virtual ~Space(){};
        virtual std::string getRoomName();
        virtual std::string getRoomColor();
        virtual void setHero(Hero **h);
        virtual void setSpaceRelationships(Space *l, Space *r, Space *t, Space *p);
        virtual Item* getNode() = 0;
        Space* goToSpace(int s);
        virtual int showOptions() = 0;
        virtual void special(int s, Space **as) = 0;
};

#endif // SPACE_HPP
