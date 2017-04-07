/*********************************************************************************
** Filename:        Item.cpp
** Author:          Justin Kruse
** Date:            31 May 2016
** Description:     This file contains the Item base class methods
**********************************************************************************/
#include "Item.hpp"
#include <string>

/* Constructor */
Item::Item(std::string n, std::string c)
{
    name = n;
    color = c;
}

/* Default Constructor */
Item::Item()
{
    name = "Item";
    color = "white";
}

/* Set method */
void Item::setName(std::string n)
{
    name = n;
}

/* Set method */
void Item::setColor(std::string c)
{
    color = c;
}



/* Get method */
std::string Item::getName()
{
    return name;
}

/* Get method */
std::string Item::getColor()
{
    return color;
}
