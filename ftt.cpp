#include "Menu.h"
#include "Helper.h"
#include "Command.h"
#include "LinkedList.h"
#include "Coin.h"

void loadFoodData(const char *food_file, LinkedList &foodList);
void displayMainMenu(bool& enableHelpPtr);

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    // Validate command line arguments
    // TODO
    std::vector<Coin> coins;
    std::vector<Coin>* coinsPtr = &coins;

    // Check if the number of arguments is correct (2 arguments)
    if (argc != 3) {
        std::cerr << "To run the program: " << argv[0] << " <food_file> <coin_file>"  << std::endl;
        return EXIT_FAILURE;
    }

    // Load food data from food file into doubly-linked list
    LinkedList* foodList = new LinkedList();
    loadFoodData(argv[1], *foodList);

    // Load coin data from coin file into doubly-linked list
    try {
        coins = Coin::loadCoinData(argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        delete foodList;
        foodList = nullptr;
        return EXIT_FAILURE;
    }

    // Create a pointer holding exitProgram's memory address
    bool exitProgram = false;
    bool* exitProgramPtr = &exitProgram;

    // help message is a configurable enhacement where user could enable/disable at runtime
    // Create a pointer holding enableHelp's memory address
    bool enableHelp = false;
    bool* enableHelpPtr = &enableHelp;

    // Create a Menu pointer pointing to Menu instance
    // The Menu instance acts as a invoker in Command Design Pattern
    Menu* menu_ptr = new Menu();

    // Menu pointer runs Menu instance's method (addCommand) to store commands for option 1 - 7
    menu_ptr->addCommand(1, new displayMealOptions(*foodList));
    menu_ptr->addCommand(2, new purchaseMeal(*foodList, *coinsPtr, *enableHelpPtr));
    menu_ptr->addCommand(3, new saveAndExit(argv[1], argv[2], *foodList, *coinsPtr, *exitProgramPtr));
    menu_ptr->addCommand(4, new addFood(*foodList, *enableHelpPtr));
    menu_ptr->addCommand(5, new removeFood(*foodList, *enableHelpPtr));
    menu_ptr->addCommand(6, new displayBalance(*coinsPtr));
    menu_ptr->addCommand(7, new helpMessageConfiguration(*enableHelpPtr));
    menu_ptr->addCommand(8, new abortProgram(*exitProgramPtr));

    // Run the program
    while (!(*exitProgramPtr)) {
        displayMainMenu(*enableHelpPtr);
        std::string string_input = Helper::readInput();

        // if user request for help and help message configuration is enabled
        if (string_input == "help" && *enableHelpPtr == true) {
            std::cout << "Please enter an option displayed in main menu. i.e. a number between 1 and 8." << std::endl;
        }
        // if user input is a valid number
        else if (Helper::isNumber(string_input) == true && ((std::stoi(string_input) >= 1 && std::stoi(string_input) <= 8))) {
            // Menu pointer runs Menu instance's method (executeCommand)
            // to run the commands based on user input
            menu_ptr->executeCommand(std::stoi(string_input));
        }
        // if user enter invalid input
        else {
            std::cout << "Invalid input. Please enter a number between 1 and 8." << std::endl;
        }
        std::cout << std::endl;
    }

    // Free memory
    delete foodList;
    delete menu_ptr;
    
    foodList = nullptr;
    menu_ptr = nullptr;
    
    return EXIT_SUCCESS;
}

// Function to load food data into linked list based on provided .dat file
void loadFoodData(const char *food_file, LinkedList &foodList) {
    // Open the file to read
    std::ifstream file(food_file);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << food_file << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        FoodItem* foodItem = new FoodItem;

        // Count how many value are in the line separated by '|', must be 3
        int count = 0;
        for (char c : line) {
            if (c == '|') {
                count++;
            }
        }
        if (count != 3) {
            std::cerr << "Error: Incorrect number of values in " << food_file << std::endl;
            exit(EXIT_FAILURE);
        }

        // Extracting ID
        std::getline(iss, token, '|');
        // If the ID is not in the correct format (Fxxxx), exit the program
        if (token.length() != IDLEN || token.substr(0, 1) != "F"){
            // Error: ID format is incorrect
            std::cerr << "Error: ID format is incorrect" << std::endl;
            exit(EXIT_FAILURE);
        }
        foodItem->id = token;

        // Extracting Name
        std::getline(iss, token, '|');
        if (token.length() > NAMELEN) {
            // Error: Name is too long
            std::cerr << "Error: Name is too long" << std::endl;
            exit(EXIT_FAILURE);
        }
        foodItem->name = token;

        // Extracting Description
        std::getline(iss, token, '|');
        if (token.length() > DESCLEN) {
            // Error: Description is too long
            std::cerr << "Error: Description is too long" << std::endl;
            exit(EXIT_FAILURE);
        }
        foodItem->description = token;

        //Set the food stock to the default level
        foodItem->on_hand = DEFAULT_FOOD_STOCK_LEVEL;

        // Extracting Price into dollars and cents
        std::getline(iss, token, '|');
        size_t decimalPointPos = token.find('.'); // Find the position of the dot
        if (decimalPointPos == std::string::npos ||
            decimalPointPos <= 0 || // Decimal point should not be at the beginning
            decimalPointPos >= token.length() - 1 || // Decimal point should not be at the end
            !std::all_of(token.begin(), token.begin() + decimalPointPos, ::isdigit) || // Digits before and after decimal point
            !std::all_of(token.begin() + decimalPointPos + 1, token.end(), ::isdigit) ||
            token.substr(token.find('.') + 1).length() != 2 ||
            std::stod(token) <= 0.00 || // Price is should be greater than 0.00
            !Helper::isDivisibleByFiveCents(token)) {  // Price should be divisible by 5 cents so that the vending machine can give change

            std::cerr << "Error: Price format is incorrect" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::string string_dollars = token.substr(0, decimalPointPos);
        std::string string_cents = token.substr(decimalPointPos + 1);
        foodItem->price.dollars = std::stoi(string_dollars);
        foodItem->price.cents = std::stoi(string_cents);

        // Create a new node and add it to the doubly-linked list
        Node* node = new Node;
        node->data = foodItem;
        foodList.addNode(node);
    }
    file.close();
}

// Display main menu
void displayMainMenu(bool& enableHelpPtr){
    std::cout<<"Main Menu: "<<std::endl;
    std::cout<<"   1. Display Meal Options "<<std::endl;
    std::cout<<"   2. Purchase Meal "<<std::endl;
    std::cout<<"   3. Save and Exit "<<std::endl;
    std::cout<<"Administrator-Only Menu: "<<std::endl;
    std::cout<<"   4. Add Food "<<std::endl;
    std::cout<<"   5. Remove Food "<<std::endl;
    std::cout<<"   6. Display Balance "<<std::endl;
    if (enableHelpPtr == true) {
        std::cout<<"   7. Disable Help Message "<<std::endl;
    }
    else {
        std::cout<<"   7. Enable Help Message "<<std::endl;
    }
    std::cout<<"   8. Abort Program "<<std::endl;
    std::cout<<"Select your option (1-8): ";
}