/*
** PLAZZA PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include <iostream>

Kitchen::Kitchen(int numCooks) : numCooks_(numCooks) {}

void Kitchen::receiveOrder(const Pizza& pizza) {
    // Here you would add the pizza to a queue or directly to a cook depending on your design
    std::cout << "Order received for a pizza of type " << pizza.getType() << " and size " << pizza.getSize() << std::endl;
    // Implement logic to distribute this order among available cooks
}
