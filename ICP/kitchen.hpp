/*
** EPITECH PROJECT, 2018
** felix.barthes@epitech.eu
** File description:
** kitchen.hpp
*/

#include "main.hpp"

class kitchen {
private:
    plazza *_ptr_partage;
    int _num_kitchen;
    std::thread tab_thread;
    int _nb_cooks;
public:
    kitchen (int num_kitchen,int nb_cooks);
    void run();
//void cook(int i);
    ~kitchen ();
};
