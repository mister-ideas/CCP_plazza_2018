/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <thread>
#include <iostream>
#include "Kitchen.hpp"
#include "Error.hpp"

Kitchen::Kitchen(int number, int numberOfCooks)
: _number(number), _numberOfCooks(numberOfCooks)
{
    _sharedMemory = openSharedMemory();
    std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
    _sharedMemory->status[_number][1] = _numberOfCooks;
    lock.unlock();
    key_t key = MSG_KEY;
    if ((_msqid = msgget(key, 0666)) < 0)
        throw Error("msgget failed");
}

void Kitchen::run()
{
    pthread_t *cooks = new pthread_t[_numberOfCooks];
    for (int i = 0; i < _numberOfCooks; i++) {
        Cook *cook;
        _cooks.push_back(cook);
        ThreadParams *params = new ThreadParams;
        params->cook = _cooks[i];
        params->sharedMemory = _sharedMemory;
        params->number = i;
        params->kitchenNumber = _number;
        pthread_create(&cooks[i], NULL, launchThread, (void*)params);
    }
    while (true) {
        if (msgrcv(_msqid, &_receiveBuffer, sizeof(Plazza), _number + 1, MSG_NOERROR) < 0)
            throw Error("msgrcv failed");
        std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
        _sharedMemory->status[_number][1] -= 1;
        lock.unlock();
        for (int i = 0; i < _numberOfCooks; i++) {
            if (!_cooks[i]->getActiveOrder()) {
                _cooks[i]->setPizza(_receiveBuffer->pizza);
                _cooks[i]->setActiveOrder(true);
                break;
            }
        }
    }
}

void *launchThread(void *params)
{
    ThreadParams *readParams = (ThreadParams*)params;
    while (true) {
        if (readParams->cook->getActiveOrder()) {
            //do order
            readParams->cook->setActiveOrder(false);
            //log
            std::unique_lock<std::mutex> lock(readParams->sharedMemory->mutex);
            readParams->sharedMemory->status[readParams->kitchenNumber][1] += 1;
            lock.unlock();
        } else
            std::this_thread::yield();
    }
}
