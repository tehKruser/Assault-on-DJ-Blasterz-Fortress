/*********************************************************************************
** Filename:        MyFunctions.hpp
** Author:          Justin Kruse
** Date:            19 Apr 2016
** Description:     This file contains function definitions. These functions
**                  tend to be reused in multiple programs.
**********************************************************************************/
#include "MyFunctions.hpp"
#include <iostream>
#include <cstdlib>
#include <stdio.h>



using std::cout;
using std::cin;
using std::endl;
using std::string;

/******************************************************************************
**                          Function:validateInput
** Description: This function validates user input of int type and returns a valid value
**              within the limits (if limits are true)
** Parameters:  use minimum value (true/false), minimum value,
**              use maximum value (true/false), maximum value.
******************************************************************************/
int validateInput(bool minOn, int minVal, bool maxOn, int maxVal)
{
    int userEntry;

    cin >> userEntry;
    while( (userEntry < minVal && minOn) || (userEntry > maxVal && maxOn ) || cin.fail() )
    {
        cin.clear();
        cin.ignore(256, 10);
        if(minOn)
            cout << "Please enter a value of at least " << minVal;
        if(maxOn)
            cout << " and no more than " << maxVal;
        if(!minOn && !maxOn)
            cout << "Please enter a whole number";
        cout << ": ";

        cin >> userEntry;
    }

    return userEntry;
}

/******************************************************************************
**                          Function:validateInput
** Description: This function validates user input of double type and returns a valid value
**              within the limits (if limits are true)
** Parameters:  use minimum value (true/false), minimum value,
**              use maximum value (true/false), maximum value.
******************************************************************************/
double validateInput(bool minOn, double minVal, bool maxOn, double maxVal)
{
    double userEntry;

    cin >> userEntry;

    while(( userEntry < minVal && minOn) || (userEntry > maxVal && maxOn ) || cin.fail() )
    {
        cin.clear();
        cin.ignore(256, 10);
        if(minOn)
            cout << "Please enter a value of at least " << minVal;
        if(maxOn)
            cout << " and no more than " << maxVal;
        if(!minOn && !maxOn)
            cout << "Please enter a number";
        cout << ": ";

        cin >> userEntry;
    }

    return userEntry;
}


 /******************************************************************************
 *                         Function:printPageTitle
 ** Description: This function prints a title
 ** Parameters:  String for title, int for total length of title across window
 ******************************************************************************/
 void printPageTitle(std::string t, unsigned int l)
 {
    int bannerLength;

    if(l > t.length() + 2)
        bannerLength = (l - t.length()) / 2;
    else
        bannerLength = 2;

    string banner = string(bannerLength, '*');

    /* Print Page Header */
    cout << endl << banner << t << banner << endl << endl;
 }


/******************************************************************************
 *                          randomNumber
 ** Description: This function returns a random number from a range
 ** Parameters:  lower bounds (l), upper bounds (u)
 ** Pre-conditions: srand() must be seeded in main program.
 ******************************************************************************/
int randomNumber(int l, int u)
{
    int upperBound = u;
    int lowerBound = l;
    int range = upperBound - lowerBound + 1;
    int randNum;

    /* Random value */
    randNum = rand() % range + lowerBound;
    //delay(100);

    return randNum;
}
