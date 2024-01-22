

#include <iostream>
#include "TradeManager.h"
#include "UserInterFace.h"
#include "Portfolio.h"
#include "DataValidator.h"

//main functiion where the stock trading is initialized and executed
int main() {
    //create instances of TradeManager and UserInterface
    TradeManager tradeManager;
    UserInterface ui(tradeManager);
    //run the user inteface and allowing the user to interact with the stock trading 
    ui.run();

    //return 0 for the successul program execution
    return 0;
}