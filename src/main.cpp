#include "Reception.hpp"
#include <iostream>

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
    Reception reception;
    reception.start(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

    return 0;
}
