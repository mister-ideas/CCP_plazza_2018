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

Kitchen::Kitchen(int number, int multiplier, int numberOfCooks, int replaceTime)
: _number(number), _multiplier(multiplier), _numberOfCooks(numberOfCooks), _replaceTime(replaceTime)
{
    _sharedMemory = openSharedMemory();
    std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
    _sharedMemory->status[_number][0] = _numberOfCooks;
    lock.unlock();
    key_t key = ftok("~/Documents/Epitech/mr_clean", 'B');
    if ((_msqid = msgget(key, 0666)) < 0)
        throw Error("msgget failed");
}

void Kitchen::run()
{
    pthread_t *cooks = new pthread_t[_numberOfCooks];
    for (int i = 0; i < _numberOfCooks; i++) {
        Cook *cook = new Cook;
        cook->setActiveOrder(false);
        _cooks.push_back(cook);
        ThreadParams *params = new ThreadParams;
        params->cook = _cooks[i];
        params->sharedMemory = _sharedMemory;
        params->number = i;
        params->kitchenNumber = _number;
        params->multiplier = _multiplier;
        params->replaceTime = _replaceTime;
        pthread_create(&cooks[i], NULL, launchThread, (void*)params);
    }
    while (true) {
        if (msgrcv(_msqid, &_receiveBuffer, sizeof(Pizza), _number + 1, MSG_NOERROR) < 0)
            throw Error("msgrcv failed");
        std::cout << "Received : " << _receiveBuffer.pizza.type << " " << _receiveBuffer.pizza.size << std::endl;
        std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
        _sharedMemory->status[_number][0] -= 1;
        lock.unlock();
        for (int i = 0; i < _numberOfCooks; i++) {
            if (!_cooks[i]->getActiveOrder()) {
                Pizza *pizza = new Pizza(_receiveBuffer.pizza.type, _receiveBuffer.pizza.size);
                _cooks[i]->setPizza(pizza);
                _cooks[i]->setActiveOrder(true);
                std::cout << "Choosed cook : " << i << std::endl; //
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
            std::unique_lock<std::mutex> lock(readParams->sharedMemory->mutex);
            executeOrder(readParams);
            lock.unlock();
        } else
            std::this_thread::yield();
    }
}

void executeOrder(ThreadParams *readParams) noexcept
{
    switch (readParams->cook->getPizza()->getType()) {
        case Margarita:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][3] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(1 * readParams->multiplier));
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][3] -= 1;
                readParams->cook->setActiveOrder(false);
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                std::cout << "Done " << Margarita << " " << readParams->cook->getPizza()->getSize() << std::endl; //
            }
            break;
        case Regina:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][3] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][4] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][5] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(2 * readParams->multiplier));
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][3] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][4] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][5] -= 1;
                readParams->cook->setActiveOrder(false);
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                std::cout << "Done " << Regina << " " << readParams->cook->getPizza()->getSize() << std::endl; //
            }
            break;
        case Americana:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][3] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][6] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(2 * readParams->multiplier));
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][3] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][6] -= 1;
                readParams->cook->setActiveOrder(false);
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                std::cout << "Done " << Americana << " " << readParams->cook->getPizza()->getSize() << std::endl; //
            }
            break;
        case Fantasia:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][7] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][8] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][9] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(4 * readParams->multiplier));
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][7] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][8] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][9] -= 1;
                readParams->cook->setActiveOrder(false);
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                std::cout << "Done " << Fantasia << " " << readParams->cook->getPizza()->getSize() << std::endl; //
            }
            break;
    }
}
