#ifndef RECEPTION_HPP
#define RECEPTION_HPP

#include <vector>
#include <string>
#include "Pizza.hpp"
#include "Kitchen.hpp"

class Reception {
public:
    Reception();
    std::vector<std::string> getOrders();
    void start(int multiplier, int num_cooks, int restock_time);
    static void trim(std::string &s);
    int processOrder(const std::string& single_order, std::vector<Kitchen>& kitchens_, int num_cooks, int restock_time, int multiplier);

private:
    std::vector<Pizza> pizzas_;
    void createKitchen(std::vector<Kitchen>& kitchens_, int num_cooks, int restock_time, int multiplier, const Pizza& newPizza, int& remainingPizzas);
};

#endif // RECEPTION_HPP
