/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** main
*/

#include <iostream>
#include <memory>
#include "../include/Error.hpp"
#include "../include/Reception.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 4)
            throw Error("USAGE: ./plazza [multiplier] [cooks_per_kitchen] [replace_ingredients_time]");
        if (std::atoi(av[1]) < 0)
            throw Error("Multiplier can't be a negative value");
        if (std::atoi(av[2]) < 0)
            throw Error("Number of cooks can't be a negative value");
        if (std::atoi(av[3]) < 0)
            throw Error("Replace time can't be a negative value");
        std::unique_ptr<Reception> reception = std::make_unique<Reception>(std::atoi(av[1]), std::atoi(av[2]), std::atoi(av[3]));
        reception->launchShell();
        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
