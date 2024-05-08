/*
** PLAZZA PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include <iostream>

Kitchen::Kitchen(int numCooks, int restockTime, int multiplier) 
    : numCooks_(numCooks), freeCooks_(numCooks), restockTime_(restockTime), multiplier_(multiplier) {}

void Kitchen::receiveOrder(const Pizza& pizza) {
    if (freeCooks_ > 0) {
        orders_.push_back(pizza);
        --freeCooks_;
        std::cout << "Order for " << pizza.getType() << " size " << pizza.getSize() << " added to kitchen." << std::endl;
    } else {
        std::cerr << "No free cooks available in this kitchen." << std::endl;
    }
}

void Kitchen::restock() {
}

void Kitchen::completeOrder() {
    if (!orders_.empty()) {
        orders_.pop_back();
        ++freeCooks_;
    }
}
