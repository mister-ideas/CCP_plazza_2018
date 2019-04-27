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
    int multiplier;
    int replaceTime;
};

class Kitchen {
	public:
		Kitchen(int number, int multiplier, int numberOfCooks, int replaceTime);
		~Kitchen() = default;

        void run();

	private:
        std::vector<Cook *> _cooks;
        Plazza *_sharedMemory;
        OrderMsg _receiveBuffer;
        int _msqid;
        int _number;
        int _multiplier;
        int _numberOfCooks;
        int _replaceTime;
};

void *launchThread(void *number);
void executeOrder(ThreadParams *readParams) noexcept;

#endif /* !KITCHEN_HPP_ */
