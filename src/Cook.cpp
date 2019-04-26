/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Cook
*/

#include "Cook.hpp"

Cook::Cook()
: _activeOrder(false)
{
}

bool Cook::getActiveOrder() const noexcept
{
    return _activeOrder;
}

void Cook::setActiveOrder(bool activeOrder) noexcept
{
    _activeOrder = activeOrder;
}

Pizza *Cook::getPizza() const noexcept
{
    return _pizza;
}

void Cook::setPizza(Pizza *pizza) noexcept
{
    _pizza = pizza;
}
