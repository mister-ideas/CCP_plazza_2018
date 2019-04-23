/*
** EPITECH PROJECT, 2018
** felix.barthes@epitech.eu
** File description:
** reception.cpp
*/

#include "reception.hpp"

reception::reception(float multi, int nb_cooks,int time)
{
    _multi = multi;
    _nb_cooks = nb_cooks;
    _time = time;
    _ptr_partage = create_shared_mem();
    for(int i = 0;i <= MAX_KITCHEN;i++) {
        _ptr_partage->list_kitchen[i] = true;
        _ptr_partage->cook_avaible[i] = _nb_cooks;
    }
}

int reception::get_free_kitchen()
{
     std::unique_lock<std::mutex> lock(_ptr_partage->mutex1);
     for(int i = 0; i < MAX_KITCHEN;i++) {
         if(_ptr_partage->list_kitchen[i] == true){
            lock.unlock();
            return (i);
        }
     }
     lock.unlock();
     return (-1);
}

int reception::get_nb_cooks()
{
    return (_nb_cooks);
}

int reception::get_nb_kitchen_used()
{
    int count = 0;
    std::unique_lock<std::mutex> lock(_ptr_partage->mutex1);

    for(int i = 0;i < MAX_KITCHEN;i++) {
        if(_ptr_partage->list_kitchen[i] == true)
            count++;
        }
        lock.unlock();
    return (count);
}

void reception::verrouille(int num_kitchen)
{
    std::unique_lock<std::mutex> lock(_ptr_partage->mutex1);
    _ptr_partage->list_kitchen[num_kitchen] = false;
    lock.unlock();
}

reception::~reception()
{
    shmdt(_ptr_partage);
}
