/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception
*/

#include "../include/Reception.hpp"

Reception::Reception(int multiplier, int numberOfCooks, int replaceTime)
: _multiplier(multiplier), _numberOfCooks(numberOfCooks), _replaceTime(replaceTime)
{
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
