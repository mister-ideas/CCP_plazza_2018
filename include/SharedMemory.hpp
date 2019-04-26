/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** SharedMemory
*/

#ifndef SHAREDMEMORY_HPP_
#define SHAREDMEMORY_HPP_

#include <mutex>

constexpr int MAX_KITCHENS = 1000;
constexpr int KEY = 12345;
constexpr int MSG_KEY = 1234;

struct Plazza {
    int status[MAX_KITCHENS][11];
    std::mutex mutex;
};

class SharedMemory {
	public:
		SharedMemory(int numberOfCooks);
		~SharedMemory() = default;

        void createSharedMemory();
        Plazza *openSharedMemory() const;

	private:
        Plazza *_sharedMemory;
        int _msqid;
};

#endif /* !SHAREDMEMORY_HPP_ */
