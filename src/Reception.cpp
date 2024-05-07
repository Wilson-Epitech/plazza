/*
** PLAZZA PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include <iostream>
#include <string>
#include <sstream>

Reception::Reception() {
}

void Reception::start(int multiplier, int num_cooks, int restock_time)
{
    Kitchen defaultKitchen(num_cooks);
    kitchens_.push_back(defaultKitchen);
    std::string input;
    while (true) {
        std::cout << "> ";
        if (!getline(std::cin, input))
            return;
        if (input == "exit") {
            std::cout << "Exiting the program." << std::endl;
            break;
        }
        std::istringstream iss(input);
        std::string type, size;
        int number;
        iss >> type >> size >> number;
        try {
            PizzaType pizzaType = Pizza::stringToPizzaType(type);
            PizzaSize pizzaSize = Pizza::stringToPizzaSize(size);
            Pizza newPizza(pizzaType, pizzaSize);
            if (kitchens_.empty()) {
                std::cerr << "No kitchens available. Initializing a new kitchen." << std::endl;
                Kitchen newKitchen(5);
                kitchens_.push_back(newKitchen);
            }
            kitchens_.at(0).receiveOrder(newPizza);
        } catch (const std::exception& e) {
            std::cerr << "Error processing order: " << e.what() << std::endl;
        }
    }
}

