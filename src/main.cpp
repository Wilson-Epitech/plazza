#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib> // Include for using atoi and exit

int check_pizza(const std::string& type, const std::string& size, const std::string& number)
{
    if (type != "regina" && type != "margarita" && type != "americana" && type != "fantasia") {
        std::cerr << "Invalid pizza type: " << type << std::endl;
        return 84;
    }
    if (size != "S" && size != "M" && size != "L" && size != "XL") {
        std::cerr << "Invalid pizza size: " << size << std::endl;
        return 84;
    }
    if (atoi(number.c_str() + 1) <= 0) {
        std::cerr << "Invalid pizza number: " << number << std::endl;
        return 84;
    }
    return 0;
}

void processToken(const std::string& token)
{
    std::istringstream stream(token);
    std::string type, size, number;

    try {
        if (stream >> type >> size >> number) {
            std::cout << "Type: " << type << std::endl;
            std::cout << "Size: " << size << std::endl;
            std::cout << "Number: " << number << std::endl;
            check_pizza(type, size, number);
        } else {
            std::cerr << "Failed to parse token correctly: " << token << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred while processing token: " << e.what() << std::endl;
    }
}

void parser(int multiplier, int cooking_time, int restock_time)
{
    while (true) {
        std::string order;
        std::cout << "> ";
        std::getline(std::cin, order);

        if (order == "exit") {
            std::cout << "Exiting the program." << std::endl;
            break;
        }
        std::istringstream stream(order);
        std::string token;
        try {
            while (getline(stream, token, ';')) {
                processToken(token);
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred while parsing orders: " << e.what() << std::endl;
        }
    }
}

int check_args(char *multiplier, char *cooking_time, char *restock_time)
{
    int multiplier_int = atoi(multiplier);
    int cooking_time_int = atoi(cooking_time);
    int restock_time_int = atoi(restock_time);

    if (multiplier_int <= 0 || cooking_time_int <= 0 || restock_time_int <= 0)
        return 84;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return 84;
    if (check_args(argv[1], argv[2], argv[3]) == 84)
        return 84;

    parser(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    return 0;
}
