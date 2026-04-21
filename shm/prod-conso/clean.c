// Clean qui se chargera de supprimer les sémaphores une fois l’exécution de vos programmes terminés

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
    sem_delete(sem_get(SEMP));
    sem_delete(sem_get(SEMC));
    sem_delete(sem_get(MUTEX));

    int shmid = shmget(MUTEX, N * sizeof(int),0);
    int res = shmctl(shmid,IPC_RMID,NULL);
    if (res == -1) {
        perror("Delete Shm");
        exit(1);
    }

    printf("Cleaned!");

    return 0;
}