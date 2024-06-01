#include "Menu.h"

// Menu constructor
Menu::Menu() {
}

// Menu destructor
Menu::~Menu() {
    // Iterate each item in map data structure
    for (auto command : command_map) {
        // delete Command instance
        delete command.second;
   }
}

// addCommand method definition
void Menu::addCommand(int option, Command* command) {
    // add new item (option, command) into the map
    command_map[option] = command;
}

// executeCommand method definition
void Menu::executeCommand(int option) {
    // Check if the iterator returned by find() is not equal to map.end()
    // if the condition is satisfied,
    //      this means the option exist in the map, thus returning 1
    // if the condition is not satisfied,
    //      this means the option does not exist in the map, thus returning 0
    bool inMap = command_map.find(option) != command_map.end();

    // run Command instance's execute method only if the integer option is found in the map
    if (inMap == 1) {
        command_map.find(option)->second->execute();
    }
}