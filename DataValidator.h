

#pragma once
#include <iostream>
using namespace std;
#include "TradeManager.h"

//class containting static method for validating stock data
class DataValidator {
public:
    // Validate stock symbol, valid stock symbol is an uppercase string of 2-5 characters
    static bool isValidSymbol(const std::string& symbol) {
        //checking the symbol length is within the valid range of 2 to 5 characters
        if (symbol.length() <= 2 || symbol.length() > 5) return false;

        //check if all characters in the symbol are uppercase
        for (char ch : symbol) {
            if (!isupper(ch)) return false;
        }
        //if both conditions are true the symbol is considered valid
        return true;
    }

    //Validate stock quantity, Positive integer
    static bool isValidQuantity(int quantity) {
        //checking if the quantity is a positive integer
        return quantity > 0;
    }

    //Validate stock price, Positive number
    static bool isValidPrice(double price) {
        //checking if the price is a positive number
        return price > 0.0;
    }
};









