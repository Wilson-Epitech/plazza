/*
** PLAZZA PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <vector>
#include "Kitchen.hpp"

class Reception {
public:
    Reception();
    void start(int cooking_time, int num_cooks, int restock_time);

private:
    std::vector<Kitchen> kitchens_;
};

#endif // RECEPTION_HPP_
