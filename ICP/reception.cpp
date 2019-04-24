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
    msgflg = IPC_CREAT | 0666;
    _nb_cooks = nb_cooks;
    _time = time;
    _ptr_partage = create_shared_mem();   // crée et ouvre memoir partagé
    for(int i = 0;i <= MAX_KITCHEN;i++) {
        _ptr_partage->list_kitchen[i] = -1; //init toutes les cuisine a close
    }
    key_t key = KEY_MSG;
    if ((msqid = msgget(key, msgflg )) < 0) {  //ouvre canal msg
        perror("msgget");
        exit(1);
    }
}

int reception::get_new_kitchen()// retourne numero de cuisne close
{

     std::unique_lock<std::mutex> lock(_ptr_partage->mutex1);
     for(int i = 0; i < MAX_KITCHEN;i++) {
         if(_ptr_partage->list_kitchen[i] == -1){
            lock.unlock();
            return (i);
        }
     }
     lock.unlock();
     return (-1);
}

int reception::find_kitchen(int nb_cooks)// retourne num kitchen avec n cook libre
{
    std::unique_lock<std::mutex> lock(_ptr_partage->mutex1,std::adopt_lock);
     for(int i = 0; i < MAX_KITCHEN;i++) {
         if(_ptr_partage->list_kitchen[i] == nb_cooks){
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

int reception::get_nb_kitchen_used() // sert a savoir cb de cuisine sont open
{
    int count = 0;
    std::unique_lock<std::mutex> lock(_ptr_partage->mutex1);

    for(int i = 0;i < MAX_KITCHEN;i++) {
        if(_ptr_partage->list_kitchen[i] >=0)
            count++;
        }
        lock.unlock();
    return (count);
}

void reception::send_commande(int num_kitchen,PizzaType type,PizzaSize size)
{
    sbuf.piz.size = size;
    sbuf.piz.type = type;
    sbuf.mtype = num_kitchen+1;
    if (msgsnd(msqid, &sbuf, sizeof(pizza), IPC_NOWAIT) < 0) {   //envois du msg a la kitchen mtype (dans sbuf) qui égale a num_kitchen + 1
        perror("msgsnd");
        exit(1);
    }else
      printf("Message: Sent\n");
}

reception::~reception()
{
    shmdt(_ptr_partage);
}
