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
#include "../include/SharedMemory.hpp"

Reception::Reception(int multiplier, int numberOfCooks, int replaceTime)
: _multiplier(multiplier), _numberOfCooks(numberOfCooks), _replaceTime(replaceTime)
{
}

void Reception::launchShell()
{
    SharedMemory shm(_numberOfCooks);
    std::string input;
    while (true) {
        try {
            std::cout << "plazza > ";
            if (!std::getline(std::cin, input) || input.empty())
                throw Error("You entered an invalid input");
            extractOrders(input);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Reception::extractOrders(std::string &input)
{
    size_t pos = 0;
    std::smatch match;
    static std::regex const regex("^([a-zA-Z]+)\\s{1}(S|M|L|XL|XXL)\\s{1}x(\\d+)$");
    std::string order;
    std::string separator = "; ";

    while ((pos = input.find(separator)) != std::string::npos) {
        order = input.substr(0, pos);
        if (std::regex_search(order, match, regex))
            addOrder(match[1], match[2], stoi(match[3]));
        else
            throw Error("Bad order syntax!");
        input.erase(0, pos + separator.length());
    }
    if (std::regex_search(input, match, regex))
        addOrder(match[1], match[2], stoi(match[3]));
    else
        throw Error("Bad order syntax!");
}

void Reception::addOrder(std::string type, std::string size, int number)
{
    PizzaType newType;
    PizzaSize newSize;

    for (int i = 0; i < number; i++) {
        if (type == "regina")
            newType = Regina;
        else if (type == "margarita")
            newType = Margarita;
        else if (type == "americana")
            newType = Americana;
        else
            newType = Fantasia;

        if (size == "S")
            newSize = S;
        else if (size == "M")
            newSize = M;
        else if (size == "L")
            newSize = L;
        else if (size == "XL")
            newSize = XL;
        else
            newSize = XXL;

        Pizza pizza(newType, newSize);
        _orders.push_back(pizza);
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
