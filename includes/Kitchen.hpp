/*
** PLAZZA PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <vector>
#include "Pizza.hpp"

class Kitchen {
public:
    Kitchen(int numCooks, int restockTime, int multiplier);
    void receiveOrder(const Pizza& pizza);
    void restock();
    int getFreeCooks() const { return freeCooks_; }
    void completeOrder();
private:
    int numCooks_;
    std::vector<Pizza> orders_;
    int freeCooks_;
    int restockTime_;
    int multiplier_;
};

#endif /* !KITCHEN_HPP_ */
