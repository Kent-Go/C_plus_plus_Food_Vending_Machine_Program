#ifndef MENU_H
#define MENU_H

#include"Command.h"
#include <map>

class Menu {
    private:
        // map data structure to store Command instance
        std::map<int, Command*> command_map;

    public:
        // Menu constructor
        Menu();
        // Menu destructor
        ~Menu();

        /**
         * @brief add option number, Command instance into map data structure
         * 
         * @param option the menu option number
         * @param command the Command pointer
         */
        void addCommand(int option, Command* command);

        /**
         * @brief run the Command instance based on given option
         * 
         * @param option the menu option number
         */
        void executeCommand(int option);
};

#endif // MENU_H