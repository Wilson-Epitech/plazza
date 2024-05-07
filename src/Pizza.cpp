/*
** PLAZZA PROJECT, 2024
** Plazza
** File description:
** Pizza
*/

#include "Pizza.hpp"
#include <stdexcept>

Pizza::Pizza(PizzaType type, PizzaSize size) : type_(type), size_(size) {}

PizzaType Pizza::stringToPizzaType(const std::string& type) {
    if (type == "regina") return Regina;
    if (type == "margarita") return Margarita;
    if (type == "americana") return Americana;
    if (type == "fantasia") return Fantasia;
    throw std::invalid_argument("Invalid pizza type");
}

PizzaSize Pizza::stringToPizzaSize(const std::string& size) {
    if (size == "S") return S;
    if (size == "M") return M;
    if (size == "L") return L;
    if (size == "XL") return XL;
    if (size == "XXL") return XXL;
    throw std::invalid_argument("Invalid pizza size");
}
