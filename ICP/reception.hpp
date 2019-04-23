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

public:
    reception (float multi, int nb_cooks,int time);
    int get_free_kitchen();
    int get_nb_cooks();
    int get_nb_kitchen_used();
    void verrouille(int num_kitchen);
    ~reception ();
};
