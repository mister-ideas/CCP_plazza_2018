/*
** EPITECH PROJECT, 2018
** felix.barthes@epitech.eu
** File description:
** reception.hpp
*/

#include "main.hpp"

class reception {
private:
    float _multi;
    int _nb_cooks;
    int _time;
    plazza *_ptr_partage;
    int msqid;
    int msgflg;
    key_t key;
    message_buf sbuf;
public:
    reception (float multi, int nb_cooks,int time);
    int get_new_kitchen();// retourne une cuisne non crée
    int get_nb_cooks();
    void send_commande(int num_kitchen,PizzaType type,PizzaSize size);
    int get_nb_kitchen_used();
    int find_kitchen(int nb_cooks);// retourne la kitchen avec n cook libre
    ~reception ();
};
