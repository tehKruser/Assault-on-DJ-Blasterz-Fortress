/*********************************************************************************
** Filename:        MyFunctions.hpp
** Author:          Justin Kruse
** Date:            19 Apr 2016
** Description:     This file contains prototype functions. These functions
**                  tend to be reused in multiple programs.
**********************************************************************************/
#ifndef MYFUNCTIONS_HPP
#define MYFUNCTIONS_HPP
#include <string>

int validateInput(bool minOn, int minVal, bool maxOn, int maxVal);
double validateInput(bool minOn, double minVal, bool maxOn, double maxVal);
void printPageTitle(std::string t, unsigned int l);
int randomNumber(int l, int u);

#endif // MYFUNCTIONS_HPP
