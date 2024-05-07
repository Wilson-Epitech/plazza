/*
** PLAZZA PROJECT, 2024
** Plazza
** File description:
** pizzas
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <string>

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

class Pizza {
public:
    Pizza(PizzaType type, PizzaSize size);
    static PizzaType stringToPizzaType(const std::string& type);
    static PizzaSize stringToPizzaSize(const std::string& size);
    PizzaType getType() const { return type_; }
    PizzaSize getSize() const { return size_; }
private:
    PizzaType type_;
    PizzaSize size_;
};

#endif /* !PIZZAS_HPP_ */
