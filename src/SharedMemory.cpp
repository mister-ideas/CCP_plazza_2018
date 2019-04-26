/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** SharedMemory
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
#include "../include/SharedMemory.hpp"
#include "../include/Error.hpp"

SharedMemory::SharedMemory(int numberOfCooks)
{
    createSharedMemory();
    for (int i = 0; i < MAX_KITCHENS; i++) {
        _sharedMemory->status[i][0] = -1;
        _sharedMemory->status[i][1] = numberOfCooks;
        _sharedMemory->status[i][2] = 5;
        _sharedMemory->status[i][3] = 5;
        _sharedMemory->status[i][4] = 5;
        _sharedMemory->status[i][5] = 5;
        _sharedMemory->status[i][6] = 5;
        _sharedMemory->status[i][7] = 5;
        _sharedMemory->status[i][8] = 5;
        _sharedMemory->status[i][9] = 5;
        _sharedMemory->status[i][10] = 5;
    }
    key_t key = MSG_KEY;
    if ((_msqid = msgget(key, IPC_CREAT | 0666)) < 0)
        throw Error("msgget failed");
}

int SharedMemory::getMsqid() const noexcept
{
    return _msqid;
}

void SharedMemory::createSharedMemory()
{
    int mem_ID;

	if ((mem_ID = shmget(KEY, sizeof(Plazza), 0666 | IPC_CREAT)) < 0)
        throw Error("shmget failed");
    if ((_sharedMemory = (Plazza *)shmat(mem_ID, NULL, 0)) == (void *) -1)
        throw Error("shmat failed");
}

Plazza *SharedMemory::openSharedMemory() const
{
    void *sharedMemory;
    int mem_ID;

	if ((mem_ID = shmget(KEY, sizeof(Plazza), 0666)) < 0)
        throw Error("shmget failed");
    if ((sharedMemory = shmat(mem_ID, NULL, 0)) == (void *) -1)
        throw Error("shmat failed");
    return (Plazza *)sharedMemory;
}