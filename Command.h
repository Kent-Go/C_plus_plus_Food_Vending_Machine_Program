#ifndef COMMAND_H
#define COMMAND_H

#include "LinkedList.h"
#include "Helper.h"
#include <iostream>
#include <map>

/**
 * Command interface which declare execute() method for executing a command.
 */
class Command {
    public:
        /**
         * @brief Command destructor
         * 
         */
        virtual ~Command();

        /**
         * @brief Command abstract execute() method
         * 
         */
        virtual void execute() = 0;
};

/**
 * displayMealOptions implement Command interface with execute() overiden.
 */
class displayMealOptions : public Command {
    private:
        LinkedList& foodList;
    public:
        /**
         * @brief displayMealOptions constructor
         * 
         * @param foodList the foodList LinkedList reference
         */
        explicit displayMealOptions(LinkedList& foodList);
        
        /**
         * @brief overriden abstract execute() method for displayMealOptions instance
         */
        void execute() override;
};

/**
 * purchaseMeal implement Command interface with execute() overiden.
 */
class purchaseMeal : public Command {
    private:
        LinkedList& foodList;
        std::vector<Coin>& coins;
        bool& enableHelp;
    public:
        /**
         * @brief purchaseMeal constructor
         * 
         * @param foodList the foodList LinkedList reference
         * @param coins the coins vector reference
         * @param enableHelp the boolean enableHelpPtr reference
         */
        explicit purchaseMeal(LinkedList& foodList, std::vector<Coin>& coins, bool& enableHelp);

        /**
         * @brief overriden abstract execute() method for purchaseMeal instance
         */
        void execute() override;
};

/**
 * saveAndExit implement Command interface with execute() overiden.
 */
class saveAndExit : public Command {
    private:
        const char *food_file;
        const char *coin_file;
        LinkedList& foodList;
        std::vector<Coin>& coins;
        bool& exitProgram;
    public:
        /**
         * @brief saveAndExit constructor
         * 
         * @param food_file the food_file pointer
         * @param coin_file the coin_file pointer
         * @param foodList the foodList LinkedList reference
         * @param coins the coins vector reference
         */
        explicit saveAndExit(const char *food_file, const char *coin_file, LinkedList& foodList, std::vector<Coin>& coins, bool& exitProgram);
       
        /**
         * @brief overriden abstract execute() method for saveAndExit instance
         */
       void execute() override;
};

/**
 * addFood implement Command interface with execute() overiden.
 */
class addFood : public Command {
    private:
        LinkedList& foodList;
        bool& enableHelp;
    public:
        /**
         * @brief addFood constructor
         * 
         * @param foodList the foodList LinkedList reference
         * @param enableHelp the boolean enableHelpPtr reference
         */
        explicit addFood(LinkedList& foodList, bool& enableHelp);

        /**
         * @brief overriden abstract execute() method for addFood instance
         */
        void execute() override;
};

/**
 * removeFood implement Command interface with execute() overiden.
 */
class removeFood : public Command {
    private:
        LinkedList& foodList;
        bool& enableHelp;
    public:
        /**
         * @brief removeFood constructor
         * 
         * @param foodList the foodList LinkedList reference
         * @param enableHelp the boolean enableHelpPtr reference
         */
        explicit removeFood(LinkedList& foodList, bool& enableHelp);

        /**
         * @brief overriden abstract execute() method for removeFood instance
         */
        void execute() override;
};

/**
 * displayBalance implement Command interface with execute() overiden.
 */
class displayBalance : public Command {
    private:
        std::vector<Coin>& coins;
    public:
        /**
         * @brief displayBalance constructor
         * 
         * @param coins the vector coins reference
         */
        explicit displayBalance(std::vector<Coin>& coins);

        /**
         * @brief overriden abstract execute() method for displayBalance instance
         */
        void execute() override;
};

/**
 * helpMessageConfiguration implement Command interface with execute() overiden.
 */
class helpMessageConfiguration : public Command {
    private:
        bool& enableHelp;

    public:
        /**
         * @brief helpMessageConfiguration constructor
         * 
         * @param enableHelp the boolean enableHelpPtr reference
         */
        explicit helpMessageConfiguration(bool& enableHelp);

        /**
         * @brief overriden abstract execute() method for helpMessageConfiguration instance
         */
        void execute() override;
};

/**
 * abortProgram implement Command interface with execute() overiden.
 */
class abortProgram : public Command {
    private:
        bool& exitProgram;

    public:
        /**
         * @brief abortProgram constructor
         * 
         * @param exitProgram the boolean exitProgram reference
         */
        explicit abortProgram(bool& exitProgram);

        /**
         * @brief overriden abstract execute() method for abortProgram instance
         */
        void execute() override;
};

#endif // COMMAND_H