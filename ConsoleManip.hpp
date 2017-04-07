#ifndef CONSOLEMANIP_HPP
#define CONSOLEMANIP_HPP

#include <string>

void delay( unsigned long ms );
void clearScreen();
void printMyColor(std::string myColor, std::string myString);
void printPageTitleWithColor(std::string c, std::string s, unsigned int l);

#endif // CONSOLEMANIP_HPP
