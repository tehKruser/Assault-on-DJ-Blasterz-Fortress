/*****************************************************************************************
** Filename:        Item.hpp
** Author:          Justin Kruse
** Date:            31 May 2016
** Description:     This file contains the Item class prototypes and data members.
*****************************************************************************************/
#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>


class Item
{
    private:
    protected:
        std::string name;
        std::string color;
    public:
        Item(std::string n, std::string c);
        Item();
        virtual ~Item(){};
        void setName(std::string n);
        void setColor(std::string c);
        std::string getName();
        std::string getColor();

};

#endif // ITEM_HPP
