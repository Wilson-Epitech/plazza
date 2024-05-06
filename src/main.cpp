#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib> // Include for using atoi and exit

void processToken(const std::string& token)
{
    std::istringstream stream(token);
    std::string type, size, number;

    try {
        if (stream >> type >> size >> number) {
            std::cout << "Type: " << type << std::endl;
            std::cout << "Size: " << size << std::endl;
            std::cout << "Number: " << number << std::endl;
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
        std::cout << "Enter order (type 'exit' to quit): ";
        std::getline(std::cin, order);

        if (order == "exit") {
            std::cout << "Exiting the program." << std::endl;
            break; // Exit the loop
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

    parser(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])); // This function now contains the loop

    return 0; // Normal termination
}
