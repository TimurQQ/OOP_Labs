#pragma once
#ifndef _UTILITIES_H_INCLUDED_
#define _UTILITIES_H_INCLUDED_
#include <iostream>

int GetNumber(const char* msg)
{
    std::cout << msg;
    int element;
    while (!(std::cin >> element))
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Error! Enter int!" << std::endl << msg;
    }
    std::cin.ignore(INT_MAX, '\n');
    return element;
}

#endif // _UTILITIES_H_INCLUDED_