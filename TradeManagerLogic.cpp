#include <iostream>
#include "TradeManager.h"
#include <stdexcept>
#include <iomanip>
#include <utility>

//method to execute a stock purchase in the trade manager
void TradeManager::buyStock(const std::string& stockSymbol, int quantity, double price) {
    //checking if the provided quantity and price is valid which greater than 0
    if (quantity <= 0 || price <= 0) {
        //if it is not valid input, it gives an error message 
        std::cerr << "Error: Invalid trade details provided!" << std::endl;
        //exit the method without executing the trade
        return;
    }

    // Create a trade using a vector for the trade 
    // Trade ID is one indexed and not zero indexed
    int tradeID = static_cast<int>(tradeHistory.size()) + 1;
    //create a new stocktrade instance wuth the caculated trade id, stock symbol, buy type, quantity and purchase price
    StockTrade newTrade(tradeID, stockSymbol, "buy", quantity, price);
    //record the created trade in the trade history
    tradeHistory.push_back(newTrade);

    // Update the portfolio with the information of new trade
    portfolio.addTrade(newTrade);
}

//method for executing a stock sale in the trade manager
void TradeManager::sellStock(const std::string& stockSymbol, int quantity, double price) {
    //getting the quantity for the transaction from the available quantity for a given symbol
    int ownedQuantity = portfolio.getQuantity(stockSymbol);
    //checking if the requested quantity to sell is greater than the quantity owned in portfolio
    if (quantity > ownedQuantity) {
        //if the requested quantity to sell is greater than quantity owned, it displays this error 
        std::cerr << "Error: You are attempting to sell more stocks than owned!" << std::endl;
        return;
    }

    //checking if provided quantity or price are invalid which is less than or equal to zero
    //or if the requested quantity to sell exceeds the avaliable quantity in the portfolio
    if (quantity <= 0 || price <= 0 || quantity > portfolio.getQuantity(stockSymbol)) {
        //if the requested quantity to sell exceeds the avaliable quantity in portfolio, it displays this error
        // without processing the trade
        std::cerr << "Error: Invalid trade details provided!" << std::endl;
        return;
    }

    // Create a trade
    //calculate a trade id, one indexed
    int tradeID = static_cast<int>(tradeHistory.size()) + 1;
    //create a new stocktrade instance represanting a sell transaction with the calculated trade ID, stock symbol
    //quantity and purchase price
    StockTrade newTrade(tradeID, stockSymbol, "sell", quantity, price);
    //record the newly created sell trade in the trade history vector
    tradeHistory.push_back(newTrade);

    // Update the portfolio with information about the sell trade
    portfolio.addTrade(newTrade);
}

//method to display the trade history in the trade manager
void TradeManager::viewTradeHistory() {
    //print a header for the trade history
    std::cout << "Trade History: " << std::endl;
    //iterate through each trade in the trade history vector
    for (const StockTrade& trade : tradeHistory) {
        //display details of each trade including trade id, symbol, type, quantity, and price
        std::cout << "[Trade ID: " << trade.getTradeIdentifier()
            << ", Symbol: " << trade.getStockSymbol()
            << ", Type: " << trade.getTradeType()
            << ", Quantity: " << trade.getQuantity()
            << ", Price: " << trade.getPrice() << "]"
            << std::endl;
    }
}

//method to execute a trade by adding it to the portfolio
void TradeManager::executeTrade(const StockTrade& trade) {
    //execute the trade by adding it to the portfolio
    portfolio.addTrade(trade);
}

//method to check if the user owns any quantity of a given stock
bool TradeManager::ownsStock(const std::string& stockSymbol) {
    //returns true if the user owns any quantity of the specified stock, otherwise returns false
    return portfolio.getQuantity(stockSymbol) > 0;
}

//method to cehck if the user can sell a certain quantity of a stock
bool TradeManager::canSellStock(const std::string& stockSymbol, int quantity) {
    //returns true if the user can sell the specified quantity of the stock, otherwise returns false
    return quantity <= portfolio.getQuantity(stockSymbol);
}