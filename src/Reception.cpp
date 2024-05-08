#include "Reception.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm> // For std::remove_if and std::isspace

Reception::Reception() {}

void trim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void Reception::start(int multiplier, int num_cooks, int restock_time)
{
    std::string input;
    while (true) {
        std::cout << "> ";
        if (!getline(std::cin, input)) {
            return;
        }
        if (input == "exit") {
            std::cout << "Exiting the program." << std::endl;
            break;
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
                continue;
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
                        break;
                    } else {
                        std::cout << "Kitchen full, cannot place order.\n";
                    }
                }
                if (!orderPlaced) {
                    std::cout << "All kitchens are full. Initializing a new kitchen.\n";
                    Kitchen newKitchen(num_cooks, restock_time, multiplier);
                    for (int i = 0; i < number; i++) {
                        newKitchen.receiveOrder(newPizza);
                    }
                    kitchens_.push_back(newKitchen);
                    std::cout << "New kitchen initialized and order placed.\n";
                }
            } catch (const std::exception& e) {
                std::cerr << "Error processing order: " << e.what() << std::endl;
            }
        }
    }
}
