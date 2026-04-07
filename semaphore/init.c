// Init qui se chargera de créer les sémaphores nécessaires à l’exercice avec le nombre de jeton utile

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

#define CLE 1234

int main()
{
    if (sem_create(CLE, 0) == -1) {  // 0 : second sera bloqué au départ
        perror("Erreur création sémaphore");
        exit(1);
    }

    printf("Sémaphore créé avec succès.\n");
    return 0;
}