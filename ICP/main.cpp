/*
** EPITECH PROJECT, 2018
** felix.barthes@epitech.eu
** File description:
** main.cpp
*/

#include "main.hpp"
#include "reception.hpp"
#include "kitchen.hpp"
 #include <unistd.h>



int main()
{
    int num_kitchen;

    reception R(2,5,2000);
    while(1){
        num_kitchen = R.get_free_kitchen();

        //printf("%d\n",R.get_nb_kitchen_used());
        //std::cout<<num_kitchen<<"   dans le main"<<std::endl;
        if(num_kitchen == 0) {
            R.verrouille(num_kitchen);
            int pid = fork();
            if(pid == 0){
                printf("lala %d\n",num_kitchen);
                kitchen k1(num_kitchen,R.get_nb_cooks());
                k1.run();
                }
            }
        }
    return (0);
}
