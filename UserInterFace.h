

#pragma once
#include <iostream>
#include <limits>
#include "DataValidator.h"
#include "TradeManager.h"

//class for user interface for stock trading 
class UserInterface {
private:
    //Reference to TradeManager, this allows the user interface to interact with trade manager functionalities
    TradeManager& tradeManager;

public:
    //constructoer that takes a refrence to tradeManager
    UserInterface(TradeManager& tm);
    //method to display the main menu of the stock trading
    void showMenu();
    //method to handle user interactions for buying and selling stock
    void handleBuyStock();
    void handleSellStock();
    //method to display trade hostory and portfolio details
    void displayTradeHistory();
    void displayPortfolioDetails();
    //method to handle the deleting a stock from stock portfolio
    void handleDeleteStock();
    //main method to run the user interface and interact with the stock trading
    void run();
};

