/*
** EPITECH PROJECT, 2018
** felix.barthes@epitech.eu
** File description:
** main.hpp
*/
#define MAX_KITCHEN 500
#define CLEF 157847



#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <pthread.h>
#include <mutex>
#include <map>
#include <stdlib.h>

#ifndef MAIN_HPP
#define MAIN_HPP

//typedef struct plazza plazza;
struct plazza {
    bool list_kitchen[MAX_KITCHEN];
    int cook_avaible[MAX_KITCHEN];
    std::mutex mutex1;
};

plazza *open_shared_mem();
plazza *create_shared_mem();

enum  PizzaType
{
Regina = 1,
Margarita = 2,
Americana = 4,
Fantasia = 8
};
enum  PizzaSize
{
S = 1,
M = 2,
L = 4,
XL = 8,
XXL = 16
};

struct one_pizza{
    int new_commande;
    PizzaType type;
    PizzaSize size;
};

#endif
