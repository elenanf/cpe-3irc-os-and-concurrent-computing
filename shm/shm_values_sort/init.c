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
    if (sem_create(MUTEX, 1) == -1) { 
        perror("Error creating the semaphore");
        exit(1);
    }

    if (sem_create(SEMP1, 0) == -1) { 
        perror("Error creating the semaphore");
        exit(1);
    }

    if (sem_create(SEMP2, 0) == -1) { 
        perror("Error creating the semaphore");
        exit(1);
    }

    if (sem_create(SEMP0, 0) == -1) { 
        perror("Error creating the semaphore");
        exit(1);
    }

    shmget(MUTEX, 3 * sizeof(int), IPC_CREAT|IPC_EXCL|0600);

    printf("Semaphores & shared memory created successfully.\n");
    return 0;
}