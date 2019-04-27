/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen
*/

#include <thread>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include "Kitchen.hpp"
#include "Error.hpp"

Kitchen::Kitchen(int number, int multiplier, int numberOfCooks, int replaceTime)
: _number(number), _multiplier(multiplier), _numberOfCooks(numberOfCooks), _replaceTime(replaceTime)
{
    _sharedMemory = openSharedMemory();
    std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
    _sharedMemory->status[_number][0] = _numberOfCooks;
    lock.unlock();
    key_t key = ftok("/etc/bashrc", 'B');
    if ((_msqid = msgget(key, 0666)) < 0)
        throw Error("msgget failed");
}

void Kitchen::createCooks() noexcept
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
}

void Kitchen::launchKitchen() noexcept
{
    createCooks();
    std::clock_t clk = std::clock();
    double duration = 0;
    while (true) {
        duration = (std::clock() - clk) / (double)(CLOCKS_PER_SEC/1000);
        if (duration == 5000) {
            std::cout << duration << std::endl;
            clk = std::clock();
        }
        if (msgrcv(_msqid, &_receiveBuffer, sizeof(Pizza), _number + 1, MSG_NOERROR | IPC_NOWAIT) > 0)
            assignOrder();
    }
}

void Kitchen::assignOrder() noexcept
{
    for (int i = 0; i < _numberOfCooks; i++) {
        if (!_cooks[i]->getActiveOrder()) {
            std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
            _sharedMemory->status[_number][0] -= 1;
            lock.unlock();
            Pizza *pizza = new Pizza(_receiveBuffer.pizza.type, _receiveBuffer.pizza.size);
            _cooks[i]->setPizza(pizza);
            _cooks[i]->setActiveOrder(true);
            break;
        }
    }
}

void *launchThread(void *params)
{
    ThreadParams *readParams = (ThreadParams*)params;
    while (true) {
        if (readParams->cook->getActiveOrder())
            executeOrder(readParams);
        else
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
                std::unique_lock<std::mutex> lock(readParams->sharedMemory->mutex);
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][3] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                lock.unlock();
                displayAndLog(readParams, "Margarita");
            }
            break;
        case Regina:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][3] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][4] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][5] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(2 * readParams->multiplier));
                std::unique_lock<std::mutex> lock(readParams->sharedMemory->mutex);
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][3] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][4] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][5] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                lock.unlock();
                displayAndLog(readParams, "Regina");
            }
            break;
        case Americana:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][3] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][6] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(2 * readParams->multiplier));
                std::unique_lock<std::mutex> lock(readParams->sharedMemory->mutex);
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][3] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][6] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                lock.unlock();
                displayAndLog(readParams, "Americana");
            }
            break;
        case Fantasia:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][7] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][8] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][9] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(4 * readParams->multiplier));
                std::unique_lock<std::mutex> lock(readParams->sharedMemory->mutex);
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][7] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][8] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][9] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                lock.unlock();
                displayAndLog(readParams, "Fantasia");
            }
            break;
    }
}

void displayAndLog(ThreadParams *readParams, const std::string &type) noexcept
{
    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);

    std::ofstream logFile;
    logFile.open("log.txt", std::ios::app);

    readParams->cook->setActiveOrder(false);
    switch (readParams->cook->getPizza()->getSize()) {
        case S:
            std::cout << "Cooked 1 " << type << " with size S" << std::endl;
            logFile << asctime(ti) << "Cooked 1 " << type << " with size S" << std::endl << std::endl;
            break;
        case M:
            std::cout << "Cooked 1 " << type << " with size M" << std::endl;
            logFile << asctime(ti) << "Cooked 1 " << type << " with size M" << std::endl << std::endl;
            break;
        case L:
            std::cout << "Cooked 1 " << type << " with size L" << std::endl;
            logFile << asctime(ti) << "Cooked 1 " << type << " with size L" << std::endl << std::endl;
            break;
        case XL:
            std::cout << "Cooked 1 " << type << " with size XL" << std::endl;
            logFile << asctime(ti) << "Cooked 1 " << type << " with size XL" << std::endl << std::endl;
            break;
        case XXL:
            std::cout << "Cooked 1 " << type << " with size XXL" << std::endl;
            logFile << asctime(ti) << "Cooked 1 " << type << " with size XXL" << std::endl << std::endl;
            break;
    }
    logFile.close();
}