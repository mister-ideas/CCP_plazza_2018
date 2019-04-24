/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception
*/

#include <iostream>
#include <regex>
#include "../include/Reception.hpp"
#include "../include/Error.hpp"

Reception::Reception(int multiplier, int numberOfCooks, int replaceTime)
: _multiplier(multiplier), _numberOfCooks(numberOfCooks), _replaceTime(replaceTime)
{
}

void Reception::launchShell() const
{
    std::string input;

    std::string line;
    std::smatch match;
    static std::regex const regex("^([a-zA-Z]+)\\s{1}(S|M|L|XL|XXL)\\s{1}x(\\d+)$");

    while (true) {
        try {
            std::cout << "plazza > ";
            if (!std::getline(std::cin, input) || input.empty())
                throw Error("You entered an invalid input");

            size_t pos = 0;
            std::string order;
            std::string separator = "; ";
            while ((pos = input.find(separator)) != std::string::npos) {
                order = input.substr(0, pos);
                if (std::regex_search(order, match, regex)) {
                    //add order
                } else
                    throw Error("Bad order syntax!");
                input.erase(0, pos + separator.length());
            }
            if (std::regex_search(input, match, regex)) {
                //add order
            } else
                throw Error("Bad order syntax!");
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
