/*
** PLAZZA PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "Kitchen.hpp"
#include <vector>
#include <string>

class Reception {
public:
    Reception();
    void start(int multiplier, int num_cooks, int restock_time);

private:
    std::vector<Kitchen> kitchens_;
    void trim(std::string &s);

    std::vector<std::string> getOrders();

    void processOrder(const std::string &single_order, std::vector<Kitchen> &kitchens_, int num_cooks, int restock_time,
                      int multiplier);

    void
    createKitchen(std::vector<Kitchen> &kitchens_, int num_cooks, int restock_time, int multiplier,
                  const Pizza &newPizza,
                  int number);
};

#endif // RECEPTION_HPP_
