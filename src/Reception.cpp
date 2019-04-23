/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception
*/

#include <iostream>
#include "../include/Reception.hpp"
#include "../include/Error.hpp"

Reception::Reception(int multiplier, int numberOfCooks, int replaceTime)
: _multiplier(multiplier), _numberOfCooks(numberOfCooks), _replaceTime(replaceTime)
{
}

void Reception::launchShell() const
{
    std::string input;

    while (true) {
        try {
            std::cout << "plazza > ";
            if (!std::getline(std::cin, input) || input.empty())
                throw Error("You entered an invalid input");
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

int Reception::getMultiplier() const noexcept
{
    return _multiplier;
}

int Reception::getNumberOfCooks() const noexcept
{
    return _numberOfCooks;
}

int Reception::getReplaceTime() const noexcept
{
    return _replaceTime;
}
