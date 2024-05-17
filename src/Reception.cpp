#include "Reception.hpp"
#include "Kitchen.hpp"
#include "Pizza.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <memory>

Reception::Reception() = default;

void Reception::trim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

std::vector<std::string> Reception::getOrders() {
    std::string input;
    if (!std::getline(std::cin, input)) {
        throw std::runtime_error("Input error");
    }
    if (input == "exit") {
        std::cout << "Exiting program.\n";
        std::exit(0);
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
    return orders;
}

int Reception::processOrder(const std::string& single_order, std::vector<Kitchen>& kitchens_, int num_cooks, int restock_time, int multiplier) {
    std::istringstream iss(single_order);
    std::string type, size;
    int number;
    char xChar; // For reading the 'x' character

    if (!(iss >> type >> size >> xChar >> number) || xChar != 'x') {
        throw std::runtime_error("Invalid order format: " + single_order);
    }
    try {
        PizzaType pizzaType = Pizza::stringToPizzaType(type);
        PizzaSize pizzaSize = Pizza::stringToPizzaSize(size);
        Pizza newPizza(pizzaType, pizzaSize);

        int remainingPizzas = number;
        for (auto& kitchen : kitchens_) {
            while (remainingPizzas > 0 && kitchen.getFreeCooks() > 0) {
                kitchen.receiveOrder(newPizza);
                --remainingPizzas;
            }
        }

        while (remainingPizzas > 0) {
            createKitchen(kitchens_, num_cooks, restock_time, multiplier, newPizza, remainingPizzas);
        }
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Error processing order: " + std::string(e.what()));
    }
    return 0;
}

void Reception::createKitchen(std::vector<Kitchen>& kitchens_, int num_cooks, int restock_time, int multiplier, const Pizza& newPizza, int& remainingPizzas) {
    std::cout << "All kitchens are full. Initializing a new kitchen.\n";
    kitchens_.emplace_back(num_cooks, restock_time, multiplier);
    int pizzasToPlace = std::min(num_cooks, remainingPizzas);
    for (int i = 0; i < pizzasToPlace; i++) {
        kitchens_.back().receiveOrder(newPizza);
    }
    remainingPizzas -= pizzasToPlace;
    std::cout << "New kitchen initialized and order placed.\n";
}

void Reception::start(int multiplier, int num_cooks, int restock_time) {
    std::vector<Kitchen> kitchens_;

    while (true) {
        std::cout << "> ";
        try {
            std::vector<std::string> orders = getOrders();
            for (const auto& single_order : orders) {
                if (processOrder(single_order, kitchens_, num_cooks, restock_time, multiplier) == 84) {
                    std::cerr << "Error processing order: " << single_order << std::endl;
                    break;
                }
            }
            std::cout << "Orders processed.\n";
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}
