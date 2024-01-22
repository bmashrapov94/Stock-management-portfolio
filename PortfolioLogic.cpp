

#include <unordered_map>
#include <string>
#include <iostream>
#include "Portfolio.h"
#include "StockTrade.h"

//method to add a stock trade to the portfolio
void Portfolio::addTrade(const StockTrade& trade) {
    //extract relevant details from trade
    std::string symbol = trade.getStockSymbol();
    int qty = trade.getQuantity();
    double price = trade.getPrice();

    //handleing buy trade
    if (trade.getTradeType() == "buy") {
        //checking if the stock is not already in the portfolio
        if (stockPositions.find(symbol) == stockPositions.end()) {
            stockPositions[symbol] = { qty, price };
        }
        else {
            //update average purchase price and quantity for an exisiting stock
            double oldAvgPrice = stockPositions[symbol].second;
            int oldQty = stockPositions[symbol].first;
            double newAvgPrice = ((oldAvgPrice * oldQty) + (price * qty)) / (oldQty + qty);
            stockPositions[symbol].first += qty;
            stockPositions[symbol].second = newAvgPrice;
        }
    }
    //handling sell trade
    else if (trade.getTradeType() == "sell") {
        //checking if the stock is present in the portfolio and if the quantity is sufficeient for selling
        if (stockPositions.find(symbol) != stockPositions.end() && stockPositions[symbol].first >= qty) {
            //updating quantity and record profit/loss
            stockPositions[symbol].first -= qty;
            double profitLoss = (price - stockPositions[symbol].second) * qty;
            recordProfitLoss(symbol, profitLoss);
            //if quantity becomes zero, it will rest
            if (stockPositions[symbol].first == 0) {
                stockPositions[symbol].first = 0;
            }
        }
        else {
            //display an error if selling more stocks than owned or stock not present in portfolio
            std::cerr << "Error: Selling more stocks than owned or stock not present!" << std::endl;
        }
    }
}
//method to get the quantity of a speciofic stock in the portfolio
int Portfolio::getQuantity(const std::string& symbol) {
    //return the quantity if the stock is present in the portfolio otherwise returns 0
    if (stockPositions.find(symbol) != stockPositions.end()) {
        return stockPositions[symbol].first;
    }
    return 0;
}
//method to get the average purchase price of a specific stock in portfolio
double Portfolio::getAveragePurchasePrice(const std::string& symbol) {
    //return the average purchase price if the stock is present in the portfolio otherwise returns 0
    if (stockPositions.find(symbol) != stockPositions.end()) {
        return stockPositions[symbol].second;
    }
    return 0.0;
}
//method to calculate the total value of all stocks in the portfolio
double Portfolio::getTotalValue() const {
    double totalValue = 0.0;
    //iterate through each stock position and add its total value to the overal total
    for (const auto& position : stockPositions) {
        totalValue += position.second.first * position.second.second;
    }
    return totalValue;
}
//method to get the overall profit or loss for a specific stock in the portfolio
double Portfolio::getOverallProfitLoss(const std::string& symbol) {
    //return the profit or loss for a specified stock if present in the record otherwise return 0
    if (profitLossRecord.find(symbol) != profitLossRecord.end()) {
        return profitLossRecord[symbol];
    }
    return 0.0;
}
//method to get a list of all stock symbols in the portfolio
std::vector<std::string> Portfolio::getAllStockSymbols() const {
    std::vector<std::string> symbols;
    //iterate thrown each stock position and add its symbol to the list
    for (const auto& pair : stockPositions) {
        symbols.push_back(pair.first);
    }
    return symbols;
}

//method to record the profit or loss for a particular stock in the portfolio
void Portfolio::recordProfitLoss(const std::string& symbol, double profitLoss) {
    profitLossRecord[symbol] += profitLoss;
}

//method to delete a stock from the portfolio
void Portfolio::deleteStock(const std::string& symbol) {
    //remove the stock position and profit/loss record for the specified stock symbol
    stockPositions.erase(symbol);
    profitLossRecord.erase(symbol);
}
