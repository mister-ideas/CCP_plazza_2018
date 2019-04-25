/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Pizza
*/

#include "Pizza.hpp"

Pizza::Pizza(PizzaType type, PizzaSize size)
: _type(type), _size(size)
{
}

PizzaType Pizza::getType() const noexcept
{
    return _type;
}

PizzaSize Pizza::getSize() const noexcept
{
    return _size;
}
