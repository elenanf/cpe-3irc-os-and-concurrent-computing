// Init qui se chargera de créer les sémaphores nécessaires à l’exercice avec le nombre de jeton utile

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "dijkstra.h"

#define SEM0 12345
#define MUTEX 54321

int main()
{
    if (sem_create(SEM0, 0) == -1) {  // 0 pour bloquer
        perror("Erreur création sémaphore");
        exit(1);
    }

    if (sem_create(MUTEX, 1) == -1) { 
        perror("Erreur création sémaphore");
        exit(1);
    }

    shmget(MUTEX,1 * sizeof(int), IPC_CREAT|IPC_EXCL|0600);

    printf("Sémaphores créé avec succès.\n");
    return 0;
}