/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** SharedMemory
*/

#ifndef SHAREDMEMORY_HPP_
#define SHAREDMEMORY_HPP_

#include <mutex>
#include "../include/Pizza.hpp"

constexpr int MAX_KITCHENS = 100;

struct Plazza {
    int status[MAX_KITCHENS][10];
    std::mutex mutex;
};

struct OrderPizza {
    PizzaType type;
    PizzaSize size;
};

struct OrderMsg {
    long mtype;
    OrderPizza pizza;
};

class SharedMemory {
	public:
		SharedMemory();
		~SharedMemory();

        int getMsqid() const noexcept;

        void createSharedMemory();

	private:
        Plazza *_sharedMemory;
        int _shmid;
        int _msqid;
};

Plazza *openSharedMemory();

#endif /* !SHAREDMEMORY_HPP_ */
