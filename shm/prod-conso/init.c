// Init qui se chargera de créer les sémaphores nécessaires à l’exercice avec le nombre de jeton utile

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "dijkstra.h"

#define SEMC 12345
#define SEMP 34257
#define MUTEX 54321
#define N 3

int main()
{
    if (sem_create(SEMC, 0) == -1) {
        perror("Erreur création sémaphore");
        exit(1);
    }

    if (sem_create(SEMP, N) == -1) {
        perror("Erreur création sémaphore");
        exit(1);
    }

    if (sem_create(MUTEX, 1) == -1) { 
        perror("Erreur création sémaphore");
        exit(1);
    }

    shmget(MUTEX, N * sizeof(int), IPC_CREAT|IPC_EXCL|0600);

    printf("Sémaphores créé avec succès.\n");
    return 0;
}