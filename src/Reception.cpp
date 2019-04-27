/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception
*/

#include <iostream>
#include <regex>
#include <chrono>
#include <thread>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "Reception.hpp"
#include "Error.hpp"
#include "SharedMemory.hpp"
#include "Kitchen.hpp"

Reception::Reception(int multiplier, int numberOfCooks, int replaceTime)
: _multiplier(multiplier), _numberOfCooks(numberOfCooks), _replaceTime(replaceTime)
{
}

Reception::~Reception()
{
    delete _shm;
}

void Reception::launchShell()
{
    _shm = new SharedMemory();
    _sharedMemory = openSharedMemory();
    std::string input;
    while (true) {
        if (!std::getline(std::cin, input))
            throw Error("You entered an invalid input");
        extractOrders(input);
        sendOrders();
        input.erase();
    }
}

void Reception::extractOrders(std::string &input)
{
    size_t pos = 0;
    std::smatch match;
    static std::regex const regex("^([a-zA-Z]+)\\s{1}(S|M|L|XL|XXL)\\s{1}x(\\d+)$");
    std::string order;
    std::string separator = "; ";

    try {
        while ((pos = input.find(separator)) != std::string::npos) {
            order = input.substr(0, pos);
            if (std::regex_search(order, match, regex))
                addOrder(match[1], match[2], stoi(match[3]));
            else
                throw Error("Bad order syntax!");
            input.erase(0, pos + separator.length());
        }
        if (std::regex_search(input, match, regex))
            addOrder(match[1], match[2], stoi(match[3]));
        else
            throw Error("Bad order syntax!");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Reception::addOrder(std::string type, std::string size, int number)
{
    PizzaType newType;
    PizzaSize newSize;

    for (int i = 0; i < number; i++) {
        if (type == "regina")
            newType = Regina;
        else if (type == "margarita")
            newType = Margarita;
        else if (type == "americana")
            newType = Americana;
        else
            newType = Fantasia;
        if (size == "S")
            newSize = S;
        else if (size == "M")
            newSize = M;
        else if (size == "L")
            newSize = L;
        else if (size == "XL")
            newSize = XL;
        else
            newSize = XXL;
        Pizza *pizza = new Pizza(newType, newSize);
        _orders.push_back(pizza);
    }
}

void Reception::sendOrders() noexcept
{
    int kitchen;

    while (_orders.size()) {
        std::this_thread::sleep_for (std::chrono::milliseconds(10));
        for (int i = _numberOfCooks; i > 0; i--){
            kitchen = findFreeKitchen(i);
            if (kitchen != -1)
                break;
        }
        if (kitchen != -1) {
            sendOrder(kitchen, _orders.back());
            _orders.pop_back();
        } else {
            int pid = fork();
            if (pid == 0) {
                kitchen = findNewKitchen();
                Kitchen k(kitchen, _multiplier, _numberOfCooks, _replaceTime);
                k.launchKitchen();
            }
        }
    }
}

void Reception::sendOrder(int kitchen, Pizza *pizza)
{
    _sendBuffer.pizza.type = pizza->getType();
    _sendBuffer.pizza.size = pizza->getSize();
    _sendBuffer.mtype = kitchen + 1;
    if (msgsnd(_shm->getMsqid(), &_sendBuffer, sizeof(Pizza), IPC_NOWAIT) < 0)
        throw Error("msgsnd failed");
}

int Reception::findFreeKitchen(int numberOfCooks) const noexcept
{
    std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
    for (int i = 0; i < MAX_KITCHENS; i++) {
        if (_sharedMemory->status[i][0] == numberOfCooks) {
            lock.unlock();
            return i;
        }
    }
    lock.unlock();
    return -1;
}

int Reception::findNewKitchen() const noexcept
{
    std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
    for (int i = 0; i < MAX_KITCHENS; i++) {
        if (_sharedMemory->status[i][0] == -1) {
            lock.unlock();
            return i;
        }
    }
    lock.unlock();
    return -1;
}
