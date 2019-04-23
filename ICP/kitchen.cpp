/*
** EPITECH PROJECT, 2018
** felix.barthes@epitech.eu
** File description:
** kitchen.cpp
*/

#include "kitchen.hpp"
using namespace std;
struct one_pizza *tab_cooks;

void *cook(void *i)
{
    int j = *((int *)i);

printf("thread %d\n",j);
    while(1){
    //printf("thread %d\n",j);
        if(tab_cooks[j].new_commande == 1) {
            printf("do command\n");
            std::this_thread::sleep_for (std::chrono::seconds(5));
            tab_cooks[j].new_commande = 2;
            printf("fun do command\n");
        }
        else
            std::this_thread::yield();
    }

}

kitchen::kitchen(int num_kitchen,int nb_cooks)
{
    //printf("kite con \n");
    _num_kitchen = num_kitchen;
    _nb_cooks = nb_cooks;
    _ptr_partage = open_shared_mem();
    std::unique_lock<std::mutex> lock(_ptr_partage->mutex1);
    _ptr_partage->list_kitchen[num_kitchen] = false;
    lock.unlock();
    printf("kitchen time\n");
}

void kitchen::run()
{

    pthread_t *thread_clients = new pthread_t [_nb_cooks];
    int ret;

    tab_cooks = new one_pizza [_nb_cooks];
    printf("nb cooks %d\n",_nb_cooks);
    for(int i =0;i < _nb_cooks;i++) {
        tab_cooks[i].new_commande = 0;
        std::cout<<"ici"<< i<<std::endl;
        ret = pthread_create (&thread_clients [i], NULL,cook,(void *) &i);
        std::this_thread::sleep_for (std::chrono::milliseconds(20));
    }
    tab_cooks[1].new_commande = 1;
    while(1)
    {
    //    printf("command = %d\n",tab_cooks[1].new_commande);
        std::this_thread::yield();
    }
}


kitchen::~kitchen ()
{
    std::unique_lock<std::mutex> lock(_ptr_partage->mutex1);
    _ptr_partage->list_kitchen[_num_kitchen] = true;
    lock.unlock();
}
