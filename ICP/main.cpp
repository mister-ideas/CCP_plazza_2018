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



int main(int ac, char **av)
{
    int num_kitchen;
    int nb_cooks = atoi(av[2]);
    reception R(atof(av[1]),nb_cooks,atoi(av[3]));
//Normalement bloquer ici si pas de commande
    while(1){
        //if(nombredecommande >= 0) {
            std::this_thread::sleep_for (std::chrono::milliseconds(1000));
            printf("new command\n");
            for(int i = nb_cooks;i > 0;i--){  // cherche la premiere cuisine avec le plus grand nombre de cuisiner libre, -1 si aucune cuisine libre
                num_kitchen = R.find_kitchen(i);
                if(num_kitchen != -1){
                    printf("find\n");
                    break;
                }
                //printf("ici 2 num kitchen = %d\n",num_kitchen);
            }
        //Normalement
        //printf("ici\n");
        printf("num kitchen main = %d\n",num_kitchen);
            if(num_kitchen != -1)  {//unr kitchen libre exist et c'est la cuisine avec le plusn de cook dispo
                printf("send command \n");
                R.send_commande(num_kitchen,Regina,S); //  envois la commande a cette kitchen
            }
            else{          //sinon création d'une nouvelle cuisine
                int pid = fork();
                if(pid == 0){
                    num_kitchen = R.get_new_kitchen();  //recupération d'une cuisine close
                    printf("lala %d\n",num_kitchen);
                    kitchen k1(num_kitchen,nb_cooks);   //init cuisine
                    k1.run();
                }
            }
        //}

        //nombredecommande--;
        //printf("nombredecommande =  %d\n",nombredecommande);
    }
    return (0);
}
