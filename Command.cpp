#include "Command.h"

// Command destructor
Command::~Command() {
}

// displayMealOptions constructor definition
displayMealOptions::displayMealOptions(LinkedList& foodList)
    : foodList(foodList) {
}

// displayMealOptions execute() method definition
void displayMealOptions::execute() {
    foodList.printList();
}

// saveAndExit constructor definition
saveAndExit::saveAndExit(const char *food_file, const char *coin_file, LinkedList& foodList, std::vector<Coin>& coins, bool& exitProgram)
    : food_file(food_file), coin_file(coin_file), foodList(foodList), coins(coins), exitProgram(exitProgram) {
}

// saveAndExit execute() method definition
void saveAndExit::execute() {
    // open the food_file to write
    std::ofstream file(food_file);

    // if file does not exist, display error message
    if (!file) {
        std::cerr << "Error: could not open file " << food_file << std::endl;
        exit(EXIT_FAILURE);
    }

    // write the food item into foods.dat
    foodList.writeAllFoods(file);

    // Close the food_file
    file.close();

    // clear error flag
    file.clear();
    
    // open the coin_file to write
    file.open(coin_file);

    // if file does not exist, display error message
    if (!file) {
        std::cerr << "Error: could not open file " << coin_file << std::endl;
        exit(EXIT_FAILURE);
    }

    // write the coin details into coins.dat
    for(const Coin& coin : coins) {
        file << coin.denom << "," 
            << coin.count << std::endl;
    }

    // Close the coin_file
    file.close();

    // set exitProgram  value to true to exit the program
    exitProgram = true;
}

// purchaseMeal constructor definition
purchaseMeal::purchaseMeal(LinkedList& foodList, std::vector<Coin>& coins, bool& enableHelp)
    : foodList(foodList), coins(coins), enableHelp(enableHelp) {
}

// purchaseMeal execute() method definition
void purchaseMeal::execute() {
    /*Instead of modifying the coins vector directly, we create a copy.
    Upon a successful purchase, update the original with the copy
    Otherwise, such as a case of unsuccessful refund, we don't modify the original coins vector at all*/
    std::vector<Coin> coinCopy = coins;

    bool cancel = false;    //Has the user cancelled their purchase?
    bool pickedFood = false;//Has the user selected a valid food item?
    Node* food = nullptr;   //Pointer to the food node in the linked list
    int amountOwed = 0;     //How much the user has to pay

    std::string input;  //Variable that accepts input

    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;

    while(!pickedFood && !cancel){
        // prompt user for food id
        std::cout << "Please enter the ID of the food you wish to purchase(or leave empty to cancel):" << std::endl;
        input = Helper::readInput();
        
        // get the food item (node) based on input id
        food = foodList.getNode(input);
        
        // if user request for help and help message configuration is enabled
        if (input == "help" && enableHelp == true) {
                std::cout << "Please enter a food ID. A list of food ID is available in meal options (Main Menu Option 1).\n" << std::endl;
            }
        // check if the returned Node pointer contain the Node (id found)
        else if(food != nullptr){

            if(food->data->on_hand > 0){
                //We have the food in stock, so set the amount the user will owe, as well as the description
                amountOwed = food->data->price.dollars * 100 + food->data->price.cents;

                std::cout << "You have selected \"" << food->data->name << " - " << food->data->description << "\". This will cost you $" <<
                amountOwed/100 << "." << std::setw(2) << std::setfill('0') << amountOwed%100 << "." << std::setfill(' ') << std::endl;
                pickedFood = true;
            }
            else{
                //User entered a valid ID, but the food isn't in stock.
                std::cout << "Sorry, this item isn't available at the moment." << std::endl;
            }
        }
        // if user cancel their order, User left empty input
        else if(input == ""){
            cancel = true;
        }
        // if user enter invalid input
        else {
            //User entered invalid food ID.
            std::cout << "Invalid input. The ID entered doesn't correspond to any item on our menu." << std::endl;
        }
    }

    //Make sure the user hasn't canceled their order
    if(!cancel){
        std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
        std::cout << "Please enter Ctrl+D or enter on a new line to cancel this purchase." << std::endl;

        //Current coin the user is entering
        int coinValue;

        //Map to keep track of the coins the user has entered - key is denomination, value is counter
        std::map<int, int> userCoins;

        while(!cancel && amountOwed > 0){

            std::cout << "You still need to give us $" << amountOwed/100 << "." << std::setw(2) << std::setfill('0') << amountOwed%100 << "." << std::setfill(' ') << ": ";
            input = Helper::readInput();

            // if user request for help and help message configuration is enabled
        if (input == "help" && enableHelp == true) {
                std::cout << "Please enter the valid amount in note or coin." << std::endl;
                std::cout << "You may enter:" << std::endl;
                std::cout << "  - 5000 for $50" << std::endl;
                std::cout << "  - 2000 for $20" << std::endl;
                std::cout << "  - 1000 for $10" << std::endl;
                std::cout << "  - 500  for $5" << std::endl;
                std::cout << "  - 200  for $2" << std::endl;
                std::cout << "  - 100  for $1" << std::endl;
                std::cout << "  - 50   for 50c" << std::endl;
                std::cout << "  - 20   for 20c" << std::endl;
                std::cout << "  - 10   for 10c" << std::endl;
                std::cout << "  - 5    for 5c\n" << std::endl;
            }
            // if user provide input
            else if(input != ""){
                // check if the input is a number
                if(Helper::isNumber(input)){
                    coinValue = std::stoi(input);

                    //This check could be its own function, makes sure the denomination is valid
                    if(coinValue == FIVE_CENTS || coinValue == TEN_CENTS || coinValue == TWENTY_CENTS || coinValue == FIFTY_CENTS ||
                    coinValue == ONE_DOLLAR || coinValue == TWO_DOLLARS || coinValue == FIVE_DOLLARS || coinValue == TEN_DOLLARS ||
                    coinValue == TWENTY_DOLLARS || coinValue == FIFTY_DOLLARS)
                    {
                        //Denomination is valid, subtract from the amount owed and add/increment map value;
                        amountOwed -= coinValue;
                        
                        if(userCoins.count(coinValue) > 0){
                            userCoins[coinValue]++;
                        }
                        else {
                            //When we add a new coin type to the map, start as 1 since the user has already entered it
                            userCoins[coinValue] = 1;
                        }
                    }
                    else{
                        std::cout << "Error: invalid denomination encountered." << std::endl;
                    }
                }
                // output error message if the input is not a number
                else{
                    std::cout << "Error: the coin/note value must be a number." << std::endl;
                }
            }
             // if user cancel their order, User left empty input
            else{
                cancel = true;
            }
        }

        //We need another cancellation check before handling the changes to the total balance
        if(!cancel){

            //Add the user-inserted money to the exisitng balance
            for (Coin& coin : coinCopy) {
                if(userCoins.count(coin.denom) > 0){
                    //remember that userCoins is a map where denomination is the key, and the value is the count.
                    coin.addCount(userCoins[coin.denom]);
                    // remove the item from userCoins
                    userCoins.erase(coin.denom);
                }
            }

            // Add the user-inserted money which its denom is not previously existed in coinCopy
            if (userCoins.size() > 0) {
                for (const std::pair<int, int> userCoin : userCoins) {
                    // cast the int value into valid data types
                    Denomination denom = static_cast<Denomination>(userCoin.first);
                    unsigned count = userCoin.second;
                    // Create Coin object and add to coinCopy vector
                    Coin coin;
                    coin.denom = denom;
                    coin.count = count;
                    coinCopy.push_back(coin);
                }

                // Sort the coins by denomination
                std::sort(coinCopy.begin(), coinCopy.end(), Coin::compareCoins);
            }

            //amountOwed would be negative (or 0), so we need to flip the sign.
            //In a way, amountOwed now refers to the amount the vending machine owes the customer rather than the other way around.
            amountOwed *= -1;

            //Since the coins are ordered in ascending order, we need to start at the end of the coin vector
            int i = coinCopy.size() - 1;
            
            //This vector will store all the change the machine gives back to the user.
            std::vector<int> change;

            //Refund loop - note that if we have given the exact money, amountOwed == 0, so we won't go in this loop at all.
            while(amountOwed != 0 && i >= 0){
                //Give back the largest coin/note possible until we need to move to a smaller one
                //or we run out of said coin.
                while(amountOwed >= coinCopy[i].denom && coinCopy[i].count > 0){
                    //We found a valid coin to refund, so decrement the counter in the list,
                    //subtract the coin from the amount owed, and add the coin to the change vector
                    amountOwed -= coinCopy[i].denom;
                    change.push_back(coinCopy[i].denom);
                    coinCopy[i].count--;
                }
                i--;
            }

            // Check if the change can be provide to user
            if(amountOwed == 0){
                //Purchase successful, print out the change refunded if there is any
                if(change.size() > 0){
                    std::cout << "Your change is: ";

                    for(unsigned i = 0; i < change.size(); i++){
                        if(change[i] >= 100){
                            //Denomination is greater than or equal to 100, so it's a dollar
                            std::cout << "$" << change[i] / 100 << " ";
                        }
                        else {
                            //Denomination is less than 100, so it's cents
                            std::cout << change[i] << "c ";
                        }
                    }
                    std::cout << std::endl;
                }

                //Update the food node and coin vector in the system accordingly.
                food->data->on_hand--;
                coins = coinCopy;
            }
            else{
                std::cout << "Error: The system cannot refund the exact change. Purchase cancelled." << std::endl;
            }
        }

    }
}

// addFood constructor definition
addFood::addFood(LinkedList& foodList, bool& enableHelp)
    : foodList(foodList), enableHelp(enableHelp) {
}

// addFood execute() method definition
void addFood::execute() {
    std::string lastID = foodList.generateFoodID();
    std::string name;
    std::string description;
    std::string price;
    std::cout << "This new meal item will have the Item id of " << lastID << std::endl;
    // Prompt user for food name
    bool valid_name = false;
    while (!valid_name) {
        std::cout << "Enter the item name: ";
        name = Helper::readInput();

        // if user request for help and help message configuration is enabled
        if (name == "help" && enableHelp == true) {
                std::cout << "Please enter the food item name. The name must not exceed 40 characters.\n" << std::endl;
        }
        // display error message if exceed expected name length, ask for a valid name
        else if (name.size() > NAMELEN) {
            std::cout << "Invalid input. Please enter a valid name with a maximum length of " << NAMELEN << " characters.\n" << std::endl;
        }
        // if hitting enter on an empty line
        else if (name.size() == 0) {
            return; // return to main menu 
        }
        else {
            //Capitalise the first letter of the new food name so that the list stays in alphabetical order
            name[0] = toupper(name[0]);
            valid_name = true;
        }
    }

    // prompt user for food description
    bool valid_description = false;
    while (!valid_description) {
        std::cout << "Enter the item description: ";
        description = Helper::readInput();

        // if user request for help and help message configuration is enabled
        if (description == "help" && enableHelp == true) {
            std::cout << "Please enter the food item description. The description must not exceed 255 characters.\n" << std::endl;
        }
        // display error message if exceed expected description length, ask for a valid description
        else if (description.size() > DESCLEN) {
            std::cout << "Invalid input. Please enter a valid description with a maximum length of " << DESCLEN << " characters.\n" << std::endl;
        }
        // if hitting enter on an empty line
        else if (description.size() == 0) {
            return; // return to main menu
        }
        else {
            valid_description = true;
        }
    }

    // prompt user for food price
    bool valid_price = false;
    while (!valid_price) {
        std::cout << "Enter the price for this item (in dollars and cents): ";
        price = Helper::readInput();
        // return to main menu if hitting enter on an empty line
        if (price.size() == 0) {
            return;
        }

        // if user request for help and help message configuration is enabled
        if (price == "help" && enableHelp == true)  {
            std::cout << "Please enter the amount for this item's price. The dollar and cent must be separated by \".\" E.g. 15.20\n" << std::endl;
        }
        else {
            // Check if input has a decimal point and consists of digits before and after it
            size_t decimalPointPos = price.find('.');
            if (decimalPointPos != std::string::npos &&
                decimalPointPos > 0 && // Decimal point should not be at the beginning
                decimalPointPos < price.length() - 1 && // Decimal point should not be at the end
                std::all_of(price.begin(), price.begin() + decimalPointPos, ::isdigit) && // Digits before and after decimal point
                std::all_of(price.begin() + decimalPointPos + 1, price.end(), ::isdigit) &&
                price.substr(price.find('.') + 1).length() == 2 && 
                std::stod(price) > 0.00 && // Price is should be greater than 0.00
                Helper::isDivisibleByFiveCents(price)) {  // Price should be divisible by 5 cents so that the vending machine can give change

                valid_price = true;
            }

            // If input is invalid, clear input buffer and prompt again
            if (!valid_price) {
                std::cout << "Invalid input. Please enter a valid price (in cents) with a decimal point and digits only.\n" << std::endl;
            }
        }
    }

    // Add food item to the foodList using given inputs
    FoodItem* foodItem = new FoodItem;
    foodItem->id = lastID;
    foodItem->name = name;
    foodItem->description = description;
    foodItem->price.dollars = std::stoi(price.substr(0, price.find('.')));
    foodItem->price.cents = std::stoi(price.substr(price.find('.') + 1));
    foodItem->on_hand = DEFAULT_FOOD_STOCK_LEVEL;

    // Create a new node and add it to the linked list
    Node* node = new Node;
    node->data = foodItem;
    foodList.addNode(node);

    // Display food added success message
    std::cout << "\nThis item \"" << name << " - " << description << "\" has now been added to the food menu" << std::endl;
}

// removeFood constructor definition
removeFood::removeFood(LinkedList& foodList, bool& enableHelp)
    : foodList(foodList), enableHelp(enableHelp) {
}

// removeFood execute() method definition
void removeFood::execute() {
        bool valid_id = false;
    while(!valid_id) {
        std::cout << "Enter the food id of the food to remove from the menu: ";
        std::string string_id = Helper::readInput();

        // return to main menu if hitting enter on an empty line
        if (string_id.size() == 0) {
            return;
        }
        
        // if user request for help and help message configuration is enabled
        if (string_id == "help" && enableHelp == true) {
            std::cout << "Please enter a food ID. A list of food ID is available in meal options (Main Menu Option 1).\n" << std::endl;
        }
        else {
            // get the food item (node) based on input id
            Node* toRemove = foodList.getNode(string_id);

            // check if the returned Node pointer contain the Node (id found)
            if (toRemove != nullptr) {
                // Display item removed message on console
                std::cout << "\"" << toRemove->data->id << " – " 
                    << toRemove->data->description << "\"" 
                    << " has been removed from the system." << std::endl;
                // remove the food item from the menu
                foodList.removeNode(toRemove);
                valid_id = true;
            }
            // display error message if food id not found, ask for a valid id
            else{
                std::cout << "Invalid input. Please enter a valid food id." << std::endl;
            }
        }
    }
}

// displayBalance constructor definition
displayBalance::displayBalance(std::vector<Coin>& coins)
    : coins(coins) {
}

// displayBalance execute() method definition
void displayBalance::execute() {
    double totalBalance = 0;

    // Calculate total balance
    for (const Coin& coin : coins) {
        totalBalance += coin.count * coin.denom / 100.0;       
    }

    // Find the length of the highest value to format the output
    int maxValueLength = std::to_string(totalBalance).length() + 2;

    // Display balance to console
    std::cout << "\nBalance Summary" << std::endl;
    std::cout << std::string(15, '-') << std::endl;
    std::cout << "Denom  | Quantity | Value"<< std::endl;
    std::cout << std::string(15 + maxValueLength, '-') << std::endl;

    for (const Coin& coin : coins) {
        std::cout << std::left << std::setw(7) << coin.denom << "| ";
        std::cout << std::left << std::setw(9) << coin.count << "|";
        std::cout << std::right << "$" << std::setw(maxValueLength - 5) << std::fixed << std::setprecision(2) << (coin.count * coin.denom / 100.0) << std::endl;
    }

    // Round the total balance to the nearest dollar
    int roundedTotalBalance = static_cast<int>(totalBalance);

    std::cout << std::string(15 + maxValueLength, '-') << std::endl;
    std::cout << std::right << std::setw(21) << "$ " << std::fixed << std::setprecision(2) << roundedTotalBalance << ".00" << std::endl;
}

// abortProgram constructor definition
abortProgram::abortProgram(bool& exitProgram)
    : exitProgram(exitProgram) {
}

// abortProgram execute() method definition
void abortProgram::execute() {
    // set exitProgram  value to true to exit the program
    exitProgram = true;
}

// helpMessageConfiguration constructor definition
helpMessageConfiguration::helpMessageConfiguration(bool& enableHelp)
    : enableHelp(enableHelp) {
}

// helpMessageConfiguration execute() method definition
void helpMessageConfiguration::execute() {
    // set enableHelp  value to true to if is previously false
    if (enableHelp == false) {
        enableHelp = true;
        std::cout << "Help message configuration is enabled." << 
            " Type \"help\" to display the command guideline" << 
            " in Main Menu, Purchase Meal, Add Food and Remove Food." << std::endl;
    }
    // set enableHelp  value to false to if is previously true
    else {
        enableHelp = false;
        std::cout << "Help message configuration is disabled." << std::endl;
    }
}