#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "dijkstra.h"

#define MUTEX 54321
#define SEMP0 43580
#define SEMP1 65486
#define SEMP2 34579
#define N 5

int main()
{
    sem_delete(sem_get(MUTEX));
    sem_delete(sem_get(SEMP1));
    sem_delete(sem_get(SEMP2));
    sem_delete(sem_get(SEMP0));

    int shmid = shmget(MUTEX, 3 * sizeof(int),0);
    int res = shmctl(shmid,IPC_RMID,NULL);
    if (res == -1) {
        perror("Delete Shm");
        exit(1);
    }

    printf("Cleaned!");

    return 0;
}