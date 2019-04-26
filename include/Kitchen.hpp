/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <vector>
#include "SharedMemory.hpp"
#include "Cook.hpp"

struct ThreadParams {
    Cook *cook;
    Plazza *sharedMemory;
    int number;
    int kitchenNumber;
};

class Kitchen {
	public:
		Kitchen(int number, int numberOfCooks);
		~Kitchen() = default;

        void run();

	private:
        std::vector<Cook *> _cooks;
        Plazza *_sharedMemory;
        OrderMsg *_receiveBuffer;
        int _msqid;
        int _number;
        int _numberOfCooks;
};

void *launchThread(void *number);

#endif /* !KITCHEN_HPP_ */
