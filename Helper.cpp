#include "Helper.h"

using std::string;
using std::vector;

Helper::Helper(){}

// readInput method definition
// Helper method to read the user input (a line) from keyboard
std::string Helper::readInput() {
    std::string input;
    // if Ctril+D (end of file) is not pressed
    if(!std::cin.eof()) {
        std::getline(std::cin, input);
    }    
    else{ // If the user presses Ctrl+D, exit the program     
        std::cerr << "\nGoodbye!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return input;
}

// isNumber method definition
// Adapted from Assignment 1 Starter Code
// Helper method to check whether the given string is an integer or a float 
bool Helper::isNumber(std::string s) {
    if (s.empty()){
        return false;
    }

    // Create an iterator to traverse the string from the beginning
    std::string::const_iterator it = s.begin();
    char dot = '.';
    int nb_dots = 0;

    // Loop through each character in the string
    while (it != s.end()) {
        if (*it == dot) {
            nb_dots++;
            
            // If more than one dot is found, it's not a valid number, return false
            if (nb_dots > 1) {
                return false;
            }

        // If the current character is not a digit, return false
        } else if (!isdigit(*it)) {
            return false;
        }

        // Move to the next character in the string
        ++it;
    }

    return s[0] != dot;
}

// isDivisibleByFiveCents method definition
// Helper method to check if the price is divisible by 5 cents
bool Helper::isDivisibleByFiveCents(const std::string& price_str) {
    double price = std::stod(price_str); // Convert string to double
    int price_cents = static_cast<int>(std::round(price * 100)); // Convert to cents
    return price_cents % 5 == 0; // Check if divisible by 5 cents
}