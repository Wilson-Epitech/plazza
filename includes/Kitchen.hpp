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
    Kitchen(int numCooks);
    void receiveOrder(const Pizza& pizza);
private:
    int numCooks_;
};

#endif /* !KITCHEN_HPP_ */
