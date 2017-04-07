#include "MyFunctions.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include "ConsoleManip.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;


                            /* Running on Windows OS */
#ifdef _WIN32
    #include "conio.h"
    #include <windows.h>

    /******************************************************************************
    **                          Function:delay (Windows OS)
    ** Description: This function will place a delay in the program.
    **              Idea came from:
    **              http://www.cplusplus.com/forum/unices/10491/
    ** Parameters:  unsigned long for seconds
    ******************************************************************************/
    void delay( unsigned long ms )
    {
        Sleep(ms);
    }

    /******************************************************************************
    **                          Function:clearScreen (Windows OS)
    ** Description: This function clears the console window.
    ** Parameters:  none.
    ******************************************************************************/
    void clearScreen()
    {
        system("cls");
    }

    /******************************************************************************
    **                          Function:printMyColor (Windows OS)
    ** Description: This function outputs to the console a string in color.
    ** Parameters:  color of output, string to output
    ******************************************************************************/
    void printMyColor(std::string myColor, std::string myString)
    {
        /*
            The different color codes are

            0   BLACK
            1   BLUE
            2   GREEN
            3   CYAN
            4   RED
            5   MAGENTA
            6   BROWN
            7   LIGHTGRAY
            8   DARKGRAY
            9   LIGHTBLUE
            10  LIGHTGREEN
            11  LIGHTCYAN
            12  LIGHTRED
            13  LIGHTMAGENTA
            14  YELLOW
            15  WHITE

        */

        int color=15;

        if(myColor == "red")
            color = 12;
        else if(myColor == "green")
            color = 10;
        else if(myColor == "blue")
            color = 9;
        else if(myColor == "cyan")
            color = 11;
        else if(myColor == "magenta")
            color = 13;
        else if(myColor == "yellow")
            color = 14;
        else if(myColor == "white")
            color = 15;
        else if(myColor == "black")
            color = 0;
        else if(myColor == "gray")
            color = 7;


        HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
        WORD wOldColorAttrs;
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

        /*
         * First save the current color information
         */

        GetConsoleScreenBufferInfo(h, &csbiInfo);
        wOldColorAttrs = csbiInfo.wAttributes;

          /*
           * Set the new color information
            (h, FOREGROUND COLOR | BACKGROUND COLOR  | FOREGROUND INTENSITY | BACKGROUND INTENSITY)
           */

          if(color == 15)
            SetConsoleTextAttribute ( h, wOldColorAttrs);
          else
            SetConsoleTextAttribute ( h, color | 0 | color | 0 );

          std::cout << myString;

          /*
           * Restore the original colors
           */

            SetConsoleTextAttribute ( h, wOldColorAttrs);
    }

                            /* Running on Linux OS */
#else
    #include <unistd.h>

    /******************************************************************************
    **                          Function:delay (Linux OS)
    ** Description: This function will place a delay in the program.
    **              Idea came from:
    **              http://www.cplusplus.com/forum/unices/10491/
    ** Parameters:  unsigned long for seconds
    ******************************************************************************/
    void delay( unsigned long ms )
    {
        fflush(stdout);
        usleep(ms * 1000);
    }

    /******************************************************************************
    **                          Function:clearScreen (Linux OS)
    ** Description: This function clears the console window.
    ** Parameters:  none.
    ******************************************************************************/
    void clearScreen()
    {
        system("clear");
    }

    /******************************************************************************
    **                          Function:printMyColor (Windows OS)
    ** Description: This function outputs to the console a string in color.
    ** Parameters:  color of output, string to output
    ******************************************************************************/
    void printMyColor(std::string myColor, std::string myString)
    {


        /*
            This is a list of codes used in C++ to change the text color:

            black - 30
            red - 31
            green - 32
            brown - 33
            blue - 34
            magenta - 35
            cyan - 36
            lightgray - 37

            Usage of "\033[":
            This is to handle the console cursor.

            * 'm' character at the end of each of the following sentences is used as a stop character, where the system should stop and parse the \033[ syntax.

            \033[0m - is the default color for the console
            \033[0;#m - is the color of the text, where # is one of the codes mentioned above
            \033[1m - makes text bold
            \033[1;#m - makes colored text bold**
            \033[2;#m - colors text according to # but a bit darker
            \033[4;#m - colors text in # and underlines
            \033[7;#m - colors the background according to #
            \033[9;#m - colors text and strikes it
            \033[A - moves cursor one line above (carfull: it does not erase the previously written line)
            \033[B - moves cursor one line under
            \033[C - moves cursor one spacing to the right
            \033[D - moves cursor one spacing to the left
            \033[E - don't know yet
            \033[F - don't know yet

            \033[2K - erases everything written on line before this.
         */

        int color=37;

        if(myColor == "red")
            color = 31;
        else if(myColor == "green")
            color = 32;
        else if(myColor == "blue")
            color = 34;
        else if(myColor == "cyan")
            color = 36;
        else if(myColor == "magenta")
            color = 35;
        else if(myColor == "yellow")
            color = 33;
        else if(myColor == "white")
            color = 37;
        else if(myColor == "black")
            color = 30;
        else if(myColor == "gray")
            color = 37;

        std::string default_console = "\033[0m";

        std::stringstream ssColor;
        ssColor << color;

        std::string scolor = "\033[0;" + ssColor.str() +"m";

        if(myColor =="white")
            std::cout << default_console;

        std::cout << scolor << myString;

        std::cout << default_console;
    }

#endif

/******************************************************************************
 *                         Function:printPageTitleWithColor
 ** Description: This function prints a title
 ** Parameters:  String for title, int for total length of title across window
 ******************************************************************************/
 void printPageTitleWithColor(std::string c, std::string t, unsigned int l)
 {
    int bannerLength;

    if(l > t.length() + 2)
        bannerLength = (l - t.length()) / 2;
    else
        bannerLength = 2;

    string banner = string(bannerLength, '*');

    /* Print Page Header */
    cout << endl << banner;
    printMyColor(c, t);
    cout << banner << endl << endl;
 }

