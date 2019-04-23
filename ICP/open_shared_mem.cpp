/*
** EPITECH PROJECT, 2018
** felix.barthes@epitech.eu
** File description:
** open_shared_mem.cpp
*/

#include "main.hpp"

plazza *create_shared_mem()
{
    int mem_ID; //	identificateur du segment de mémoire partagée associé à CLEF
	void* ptr_mem_partagee; //	pointeur sur l'adresse d'attachement du segment de mémoire partagée

	if ((mem_ID = shmget(CLEF, sizeof(plazza), 0666 | IPC_CREAT)) < 0)	//	je crée un nouveau segment mémoire de taille "taille de ma structure data" octets, avec des droits d'écriture et de lecture
	{
		perror("shmget");											//	et je m'assure que l'espace mémoire a été correctement créé
		exit(1);
	}

	if ((ptr_mem_partagee = shmat(mem_ID, NULL, 0)) == (void*) -1)	//	J'attache le segment de mémoire partagée identifié par mem_ID au segment de données du processus A dans une zone libre déterminée par le Système d'exploitation
	{
		perror("shmat");											//	et je m'assure que le segment de mémoire a été correctement attaché à mon processus
		exit(1);
	}
    return ((plazza*)ptr_mem_partagee);
}

plazza *open_shared_mem()
{
    int mem_ID; //	identificateur du segment de mémoire partagée associé à CLEF
	void* ptr_mem_partagee; //	pointeur sur l'adresse d'attachement du segment de mémoire partagée

    if ((mem_ID = shmget(CLEF, sizeof(plazza), 0666 | IPC_CREAT)) < 0)	//	je crée un nouveau segment mémoire de taille "taille de ma structure data" octets, avec des droits d'écriture et de lecture
	{
		perror("shmget");											//	et je m'assure que l'espace mémoire a été correctement créé
		exit(1);
	}

	if ((ptr_mem_partagee = shmat(mem_ID, NULL, 0)) == (void*) -1)	//	J'attache le segment de mémoire partagée identifié par mem_ID au segment de données du processus A dans une zone libre déterminée par le Système d'exploitation
	{
		perror("shmat");											//	et je m'assure que le segment de mémoire a été correctement attaché à mon processus
		exit(1);
	}
    return ((plazza*)ptr_mem_partagee);
}
