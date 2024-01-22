

#pragma once
#include <vector>
#include <iostream>
#include "StockTrade.h"
#include "Portfolio.h"

//class for managing stock trades and portfolio updates
class TradeManager {
private:
    //vector to store the history of stock trades
    std::vector<StockTrade> tradeHistory;
    //instance of the portfolio class to manage stock holdings 
    Portfolio portfolio;

public:
    //Method to buy stock. record the trade, and update the portfolio
    void buyStock(const std::string& stockSymbol, int quantity, double price);

    //method to Sell stock, record the trade and update the portfolio
    void sellStock(const std::string& stockSymbol, int quantity, double price);

    //method to view the trade history
    void viewTradeHistory();

    //method to access the portfolio instance
    Portfolio& getPortfolio() { return portfolio; }

    //method to execute a trade by adding it to the portfolio
    void executeTrade(const StockTrade& trade);

    //method to check if the user owns any quantity of specific stock
    bool ownsStock(const std::string& stockSymbol);

    //method to check if the user can sell a certain quantity of a specific stock
    bool canSellStock(const std::string& stockSymbol, int quantity);
};
