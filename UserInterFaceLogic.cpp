#include <iostream>
#include <limits>
#include "DataValidator.h"
#include "TradeManager.h"
#include "UserInterface.h"


//constructor for the UserInterface class
UserInterface::UserInterface(TradeManager& tm) : tradeManager(tm) {}

// Display the main menu to the user
void UserInterface::showMenu() {
    std::cout << "\n*** Stock Trading System *** \n";
    std::cout << "1. Buy Stock\n";
    std::cout << "2. Sell Stock\n";
    std::cout << "3. View Trade History\n";
    std::cout << "4. View Portfolio\n";
    std::cout << "5. Delete a stock from portfolio\n";
    std::cout << "6. Exit\n";
    std::cout << "Select an option: ";
}

// Collects user input and records a buy trade
void UserInterface::handleBuyStock() {
    //prompt user for stock symbol input and validate it
    std::string symbol;
    std::string input;
    bool validSymbol = false;
    int quantity;
    double price;
    do {
        std::cout << "Enter Stock Symbol: ";
        std::cin >> symbol;
        // Clear the buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (DataValidator::isValidSymbol(symbol)) {
            validSymbol = true;
        }
        else {
            std::cerr << "Error: Invalid Stock Symbol!\n";
        }
    } while (!validSymbol);

    // Quantity input and validation
    bool validQuantity = false;
    do {
        std::cout << "Enter Quantity: ";
        std::getline(std::cin, input);

        try {
            quantity = std::stoi(input);
            if (DataValidator::isValidQuantity(quantity)) {
                validQuantity = true;
            }
            else {
                std::cerr << "Error: Invalid Quantity!\n";
            }
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Invalid input: Please enter a valid integer for quantity." << std::endl;
        }
        catch (const std::out_of_range&) {
            std::cerr << "Invalid input: Number too large or small for an int." << std::endl;
        }
    } while (!validQuantity);

    // Price input and validation
    bool validPrice = false;
    do {
        std::cout << "Enter Price: ";
        std::getline(std::cin, input);

        try {
            price = std::stod(input);
            if (DataValidator::isValidPrice(price)) {
                validPrice = true;
            }
            else {
                std::cerr << "Error: Invalid Price!\n";
            }
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Invalid input: Please enter a valid number for price." << std::endl;
        }
        catch (const std::out_of_range&) {
            std::cerr << "Invalid input: Number too large or small for price." << std::endl;
        }
    } while (!validPrice);

    //record the buy trade
    tradeManager.buyStock(symbol, quantity, price);
    std::cout << "Trade recorded successfully!\n";
}


// Collects user input and records a sell trade
void UserInterface::handleSellStock() {
    //prompt user for stock symbol input and validate it
    std::string symbol;
    std::string input;

    int quantity;
    double price;
    bool validSymbol = false;
    do {
        std::cout << "Enter Stock Symbol: ";
        std::cin >> symbol;
        // Clear the buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (DataValidator::isValidSymbol(symbol)) {
            validSymbol = true;
        }
        else {
            std::cerr << "Error: Invalid Stock Symbol!\n";
        }
    } while (!validSymbol);

    // Check if the user owns this stock. If not, it does not proceed further
    if (!tradeManager.ownsStock(symbol)) {
        std::cerr << "Error: You don't own any stocks with this symbol!\n";
        return;
    }

    // Quantity input and validation
    bool validQuantity = false;
    do {
        std::cout << "Enter Quantity to Sell: ";
        std::getline(std::cin, input);


        try {
            quantity = std::stoi(input);
            if (DataValidator::isValidQuantity(quantity)) {
                if (tradeManager.canSellStock(symbol, quantity)) {
                    validQuantity = true;
                }
                else {
                    std::cerr << "Error: You don't own enough of this stock to sell the specified quantity!\n";
                }
            }
            else {
                std::cerr << "Error: Invalid Quantity!\n";
            }
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Invalid input: Please enter a valid integer for quantity." << std::endl;
        }
        catch (const std::out_of_range&) {
            std::cerr << "Invalid input: Number too large or small for an int." << std::endl;
        }

    } while (!validQuantity);

    // Price input and validation
    bool validPrice = false;
    do {
        std::cout << "Enter Selling Price: ";
        std::getline(std::cin, input);

        try {
            price = std::stod(input);
            if (DataValidator::isValidPrice(price)) {
                validPrice = true;
            }
            else {
                std::cerr << "Error: Invalid Price!\n";
            }
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Invalid input: Please enter a valid number for price." << std::endl;
        }
        catch (const std::out_of_range&) {
            std::cerr << "Invalid input: Number too large or small for price." << std::endl;
        }
    } while (!validPrice);

    tradeManager.sellStock(symbol, quantity, price);
    std::cout << "Trade recorded successfully!\n";
}

//displaying the trade history to the user
void UserInterface::displayTradeHistory() {
    tradeManager.viewTradeHistory();
}
//displaying detailed information about the user's portfolio
void UserInterface::displayPortfolioDetails() {
    std::cout << "\n===== Portfolio Details =====\n";
    //retrive all stock symbols from the portfolio
    auto symbols = tradeManager.getPortfolio().getAllStockSymbols();
    //checking if the portfolio is empty
    if (symbols.empty()) {
        std::cout << "Your portfolio is empty.\n";
        return;
    }
    //iterate through each stock symbol and display relevant details
    for (const auto& symbol : symbols) {
        int quantity = tradeManager.getPortfolio().getQuantity(symbol);
        double avgPrice = tradeManager.getPortfolio().getAveragePurchasePrice(symbol);
        double profitLoss = tradeManager.getPortfolio().getOverallProfitLoss(symbol);

        //checking if there is a profit or loss
        std::string profitOrLossString = profitLoss > 0 ? "Profit" : "Loss";
        //displaying the stock details
        std::cout << "Stock Symbol: " << symbol << std::endl;
        std::cout << "Quantity: " << quantity << std::endl;
        std::cout << "Average Purchase Price: $" << avgPrice << std::endl;
        std::cout << "Status: " << profitOrLossString << ": $" << std::abs(profitLoss) << std::endl;
        std::cout << "------------------------\n";
    }
}
//handles the deleting a stock from user's portfolio
void UserInterface::handleDeleteStock() {
    std::string symbol;
    std::cout << "Enter Stock Symbol to Delete: ";
    std::cin >> symbol;
    //delete the sepecified stock from portfolio
    tradeManager.getPortfolio().deleteStock(symbol);
    std::cout << "Stock deleted successfully!\n";
}
//main loop for running the user interface
void UserInterface::run() {
    int choice;
    do {
        //display the main menu and handle user input
        showMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        //process user choice based on the selected option
        switch (choice) {
        case 1:
            handleBuyStock();
            break;
        case 2:
            handleSellStock();
            break;
        case 3:
            displayTradeHistory();
            break;
        case 4:
            displayPortfolioDetails();
            break;
        case 5:
            handleDeleteStock();
            break;
        case 6:
            std::cout << "Thank you for using the Stock Trading System. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}
