// Clean qui se chargera de supprimer les sémaphores une fois l’exécution de vos programmes terminés

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
    sem_delete(sem_get(SEM0));
    sem_delete(sem_get(MUTEX));

    int shmid = shmget(MUTEX,1 * sizeof(int),0);
    int res = shmctl(shmid,IPC_RMID,NULL);
    if (res == -1) {
        perror("Delete Shm");
    }

    printf("Cleaned!");

    return 0;
}