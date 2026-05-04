#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "data.h"

#define MUTEX 87559
#define RI 86549
#define SEMP 34797
#define SEMC 34598 
#define STR_LEN 10000
#define MAX 5

int main(void)
{
    if (sem_create(MUTEX, 1) == -1) {
        perror("Sem Create");
        exit(1);
    }

    if (sem_create(SEMP, MAX) == -1) {
        perror("Sem Create");
        exit(1);
    }

    if (sem_create(SEMC, 0) == -1) {
        perror("Sem Create");
        exit(1);
    }

    int shmid = shmget(MUTEX, MAX * sizeof(struct Data), IPC_CREAT|IPC_EXCL|0600);
    if (shmid == -1) {
        perror("Shmget Memory");

        exit(1);
    }

    int shmid1 = shmget(RI, 1*sizeof(int), IPC_CREAT|IPC_EXCL|0600);
    if (shmid1 == -1) {
        perror("Shmget Memory");
        exit(1);
    }


    puts("Init successfull");

    return 0;
}