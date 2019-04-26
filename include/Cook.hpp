/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include "Pizza.hpp"

class Cook {
	public:
		Cook();
		~Cook() = default;

        bool getActiveOrder() const noexcept;
        void setActiveOrder(bool activeOrder) noexcept;
        Pizza *getPizza() const noexcept;
        void setPizza(Pizza *pizza) noexcept;

	private:
        bool _activeOrder;
        Pizza *_pizza;
};

#endif /* !COOK_HPP_ */