// Init qui se chargera de créer les sémaphores nécessaires à l’exercice avec le nombre de jeton utile

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

#define CLE1 1
#define CLE2 2


int main()
{
    if (sem_create(CLE1, 1) == -1) {  // 
        perror("Erreur création sémaphore");
        exit(1);
    }

        if (sem_create(CLE2, 1) == -1) {  // 
        perror("Erreur création sémaphore");
        exit(1);
    }

    printf("Sémaphores créé avec succès.\n");
    return 0;
}