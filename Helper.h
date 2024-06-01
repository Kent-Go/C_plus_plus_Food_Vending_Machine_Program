#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>

class Helper
{
public:
    Helper();

    /**
     * @brief Check whether the given string is an integer or a float 
     * 
     * @param s The given string
     * @return true if the string is an integer or a float 
     * @return false if the string is neither an integer nor a float 
     */
    static bool isNumber(std::string s);

    /**
     * @brief Read the user input (a line) from keyboard
     * 
     * @return the user input.
     */
    static std::string readInput();

    /**
     * @brief Check if the price input is divisible by 5
     * 
     * @return true if the price is divisible by 5
     * @return false if the price is not divisible by 5
     */
    static bool isDivisibleByFiveCents(const std::string& price_str);

};
#endif