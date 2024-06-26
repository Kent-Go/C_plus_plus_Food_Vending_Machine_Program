#ifndef COIN_H
#define COIN_H

// Coin.h defines the coin structure for managing currency in the system. 
#define DELIM ","  // delimiter 

#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>  
#include <iostream>
#include <algorithm>

// enumeration representing the various types of currency available in the system. 
enum Denomination
{
    FIVE_CENTS = 5,
    TEN_CENTS = 10,
    TWENTY_CENTS = 20,
    FIFTY_CENTS = 50, 
    ONE_DOLLAR = 100, 
    TWO_DOLLARS = 200, 
    FIVE_DOLLARS = 500, 
    TEN_DOLLARS = 1000, 
    TWENTY_DOLLARS = 2000,
    FIFTY_DOLLARS = 5000
};


// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    // the denomination type
    enum Denomination denom;
    
    // the count of how many of these are in the cash register
    unsigned count;

    /**
     * @brief load coin data from coin file
     * 
     * @param filename the file name reference
     */
    static std::vector<Coin> loadCoinData(const std::string& filename);

    /**
     * @brief increment/decrement the amount of coin
     * 
     * @param amount the amount of coin to be added
     */
    void addCount(int amount);

    /**
     * @brief sort the coins based on denominator
     * 
     * @param coin1 the first Coin instance
     * @param coin2 the second Coin instance
     */
    static bool compareCoins(const Coin& coin1, const Coin& coin2);
};

#endif // COIN_H
