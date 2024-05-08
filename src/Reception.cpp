#include "Reception.hpp"
#include "Kitchen.hpp"
#include "Pizza.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <memory>
#include <unistd.h>

Reception::Reception() {}

void Reception::trim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void Reception::start(int multiplier, int num_cooks, int restock_time) {
    std::vector<Kitchen> kitchens_;
    std::string input;

    while (true) {
        std::cout << "> ";
        if (!getline(std::cin, input)) {
            return; // Handles EOF or input error by exiting the loop
        }
        if (input == "exit") {
            std::cout << "Exiting the program." << std::endl;
            break; // Break out of the loop to end the program
        }

        std::vector<std::string> orders;
        std::stringstream ss(input);
        std::string order;

        while (std::getline(ss, order, ';')) {
            trim(order);
            if (!order.empty()) {
                orders.push_back(order);
            }
        }

        for (const auto& single_order : orders) {
            std::istringstream iss(single_order);
            std::string type, size;
            int number;
            char xChar; // For reading the 'x' character

            if (!(iss >> type >> size >> xChar >> number) || xChar != 'x') {
                std::cerr << "Invalid order format: " << single_order << std::endl;
                continue; // Skip to the next order if the format is invalid
            }
            try {
                PizzaType pizzaType = Pizza::stringToPizzaType(type);
                PizzaSize pizzaSize = Pizza::stringToPizzaSize(size);
                Pizza newPizza(pizzaType, pizzaSize);

                bool orderPlaced = false;
                for (auto& kitchen : kitchens_) {
                    if (kitchen.getFreeCooks() > 0) {
                        for (int i = 0; i < number; i++) {
                            kitchen.receiveOrder(newPizza);
                        }
                        orderPlaced = true;
                        break; // Order has been placed, no need to initialize a new kitchen
                    }
                }
                if (!orderPlaced) {
                    std::cout << "All kitchens are full. Initializing a new kitchen.\n";
                    kitchens_.emplace_back(num_cooks, restock_time, multiplier);
                    for (int i = 0; i < number; i++) {
                        kitchens_.back().receiveOrder(newPizza);
                    }
                    std::cout << "New kitchen initialized and order placed.\n";
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error processing order: " << e.what() << std::endl;
            }
        }
        sleep(10);
    }
}
