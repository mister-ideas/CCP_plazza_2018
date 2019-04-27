/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <vector>
#include "Pizza.hpp"
#include "SharedMemory.hpp"

class Reception {
	public:
		Reception(int multiplier, int numberOfCooks, int replaceTime);
		~Reception();

        void launchShell();
        void extractOrders(std::string &input);
        void addOrder(std::string type, std::string size, int number);
        void sendOrders() noexcept;
        void sendOrder(int kitchen, Pizza *pizza);
        int findFreeKitchen(int numberOfCooks) const noexcept;
        int findNewKitchen() const noexcept;

	private:
        std::vector<Pizza *> _orders;
        SharedMemory *_shm;
        Plazza *_sharedMemory;
        OrderMsg _sendBuffer;
        int _multiplier;
        int _numberOfCooks;
        int _replaceTime;
};

#endif /* !RECEPTION_HPP_ */
