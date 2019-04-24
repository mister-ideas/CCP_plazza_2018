/*
** EPITECH PROJECT, 2018
** felix.barthes@epitech.eu
** File description:
** kitchen.cpp
*/

#include "kitchen.hpp"
using namespace std;
struct one_pizza *tab_cooks;
plazza *ptr;
int num_kitch;


void *cook(void *i)   //thread d'un cuisinier
{
    int j = *((int *)i);

//printf("thread %d\n",j);
    while(1){
    //printf("thread %d\n",j);
        if(tab_cooks[j].new_commande == 1) { //test si commande
            printf("do command\n");   // faire commande
            std::this_thread::sleep_for (std::chrono::seconds(7));
            tab_cooks[j].new_commande = 0;
            printf("fin do command,  cuisine %d  cuisiner %d\n",num_kitch,j);
            std::unique_lock<std::mutex> lock(ptr->mutex1);
            ptr->list_kitchen[num_kitch] += 1; // commande terminée le cuisiner est libre
            lock.unlock();
        }
        else
            std::this_thread::yield(); // se rendor pour quelque milliseconds
    }

}

kitchen::kitchen(int num_kitchen,int nb_cooks)
{
    //printf("kite con \n");
    _num_kitchen = num_kitchen;
    _nb_cooks = nb_cooks;
    _ptr_partage = open_shared_mem();
    std::unique_lock<std::mutex> lock(_ptr_partage->mutex1);
    _ptr_partage->list_kitchen[num_kitchen] = nb_cooks; //init le nombre de cook libre de num kitchen
    lock.unlock();
    buf_length = sizeof(pizza);
     key = KEY_MSG;
     if((msqid = msgget(key, 0666)) < 0) {   //open connection msg
        perror("msgget");
        exit(1);
    }
    printf("kitchen time\n");
    ptr = _ptr_partage;        //accés globale a _ptr_partage et num_kitchen a cause de pthread_create
    num_kitch = num_kitchen;
}

void kitchen::run() //lancement cuisine
{

    pthread_t *thread_clients = new pthread_t [_nb_cooks];
    int ret;

    tab_cooks = new one_pizza [_nb_cooks];
    printf("nb cooks %d\n",_nb_cooks);
    for(int i =0;i < _nb_cooks;i++)
        tab_cooks[i].new_commande = 0; // init a pas de nouvelle commande

    for(int i =0;i < _nb_cooks;i++) {  //lancement de tous les threads
        std::cout<<"ici"<< i<<std::endl;
        ret = pthread_create (&thread_clients [i], NULL,cook,(void *) &i);
        std::this_thread::sleep_for (std::chrono::milliseconds(20));
    }
    while(1)
    {
        if (msgrcv(msqid, &rbuf,buf_length ,_num_kitchen+1, MSG_NOERROR) < 0) { // attend de recevoir un msg de type 1
            perror("msgrcv ....");
            exit(1);
        }
        std::unique_lock<std::mutex> lock(_ptr_partage->mutex1);
        _ptr_partage->list_kitchen[_num_kitchen] -= 1;   //  un cuisiner de dispo de moins
        lock.unlock();
        printf("La cuisine %d a recu une commande de %d\n",_num_kitchen,rbuf.piz.type);
int i;
        for( i =0;i < _nb_cooks;i++) { // recher et envois de la commande a un cuisinier
            if(tab_cooks[i].new_commande == 0) { // test cuisiner dispo
                tab_cooks[i].type = rbuf.piz.type;
                tab_cooks[i].size = rbuf.piz.size;
                tab_cooks[i].new_commande =1; // signale nouvelle commande aux cook numero i
                break;
                }
            }
            printf("le cuisiner est use %d\n",i);
    }
}


kitchen::~kitchen ()
{
    std::unique_lock<std::mutex> lock(_ptr_partage->mutex1);
    _ptr_partage->list_kitchen[_num_kitchen] = -1;
    lock.unlock();
}
