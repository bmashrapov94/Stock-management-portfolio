

#pragma once
#include <string>

//class for stock trade
class StockTrade {
private:
    //private member variables for trade details
    int tradeIdentifier;
    double price;
    std::string stockSbl;
    std::string Ttype;
    int quantity;



public:
    // Constructor to initialize the StockTrade instance with trade details
    StockTrade(int id, const std::string& symbol, const std::string& type,
        int qty, double pr)
        : tradeIdentifier(id), stockSbl(symbol), Ttype(type),
        quantity(qty), price(pr) {}

    // Getters for retrieving trade details
    int getTradeIdentifier() const { return tradeIdentifier; }
    std::string getStockSymbol() const { return stockSbl; }
    std::string getTradeType() const { return Ttype; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }


    // Setters for the StockTrade class to modify trade details
    void setTradeID(int id) { tradeIdentifier = id; }
    void setStockSymbol(const std::string& symbol) { stockSbl = symbol; }
    void setTradeType(const std::string& type) { Ttype = type; }
    void setQuantity(int qty) { quantity = qty; }
    void setPrice(double pr) { price = pr; }
};


