

#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "StockTrade.h"

//Class for stock portfolio
class Portfolio {
private:
    //maping stock symbol to quantity and average purchase price
    std::unordered_map<std::string, std::pair<int, double>> stockPositions;
    //maping stock symbol to profit or loss of each stock
    std::unordered_map<std::string, double> profitLossRecord;

public:
    //method to add a stock to the stock portfolio
    void addTrade(const StockTrade& trade);
    //method to get the quantity of a stock in stock portfolio
    int getQuantity(const std::string& symbol);
    //method to get average price of a stock in the stock portfolio
    double getAveragePurchasePrice(const std::string& symbol);
    //method to get the total value of all stocks in the stock portfolio
    double getTotalValue() const;
    //method to get teoveralll profit or loss for a stock in the stock portfolio
    double getOverallProfitLoss(const std::string& symbol);
    //method to get a list of all stock symnpls in stock portfolio
    std::vector<std::string> getAllStockSymbols() const;
    //method to record the profit or loss for a specific stock in the stock portfolio
    void recordProfitLoss(const std::string& symbol, double profitLoss);
    //method to delete a stock record from the stock portfolio
    void deleteStock(const std::string& symbol);
};


