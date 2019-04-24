/*
** EPITECH PROJECT, 2018
** felix.barthes@epitech.eu
** File description:
** main.hpp
*/
#define MAX_KITCHEN 500
#define CLEF 15785
#define KEY_MSG 1245



#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <pthread.h>
#include <mutex>
#include <map>
#include <sys/msg.h>
#include <stdlib.h>

#ifndef MAIN_HPP
#define MAIN_HPP

//typedef struct plazza plazza;
struct plazza {
    int list_kitchen[MAX_KITCHEN];// mémoire partagé -1 si kitchen close ou si different de 0 nombre de cook libre
    std::mutex mutex1;
};

plazza *open_shared_mem();
plazza *create_shared_mem();// crée memoire partagé

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

struct pizza {      // contient les infos envoyer a une cuisine
    PizzaType type;
    PizzaSize size;
};

struct message_buf {     // structure d'un  message
    long    mtype;  //permet d'envoyer le msg a la bonne kitchen
    pizza    piz;      // structure contenant les infos a envoyer
};

struct one_pizza{
    int new_commande;
    PizzaType type;
    PizzaSize size;
};

#endif
