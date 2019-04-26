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

struct OrderMsg {
    long mtype;
    Pizza *pizza;
};

class SharedMemory {
	public:
		SharedMemory();
		~SharedMemory() = default;

        int getMsqid() const noexcept;

        void createSharedMemory();

	private:
        Plazza *_sharedMemory;
        int _msqid;
};

Plazza *openSharedMemory();

#endif /* !SHAREDMEMORY_HPP_ */
