/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <vector>
#include "../include/Pizza.hpp"

class Reception {
	public:
		Reception(int multiplier, int numberOfCooks, int replaceTime);
		~Reception() = default;

        void launchShell();
        void extractOrders(std::string &input);
        void addOrder(std::string type, std::string size, int number);
        int getMultiplier() const noexcept;
        int getNumberOfCooks() const noexcept;
        int getReplaceTime() const noexcept;

	private:
        std::vector<Pizza> _orders;
        int _multiplier;
        int _numberOfCooks;
        int _replaceTime;
};

#endif /* !RECEPTION_HPP_ */
