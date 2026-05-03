#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "dijkstra.h"
#include "shared.h"

#define MUTEXREQUEST 54321
#define MUTEXRESPONSE 54322
#define SEMRESPONSE 78689

#define SEMC 12345 // conso
#define SEMP 34257 // prod

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        exit(1);
    }
    int N = atoi(argv[1]);

    if (sem_create(MUTEXREQUEST, 1) == -1) { 
        perror("Semaphore error");
        exit(1);
    }

    if (sem_create(MUTEXRESPONSE, 1) == -1) { 
        perror("Semaphore error");
        exit(1);
    }

    if (sem_create(SEMC, 0) == -1) { 
        perror("Semaphore error");
        exit(1);
    }

    if (sem_create(SEMP, N) == -1) { 
        perror("Semaphore error");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        if (sem_create(SEMRESPONSE + i, 0) == -1) {
            perror("Semaphore error");
            exit(1);
        }
    }

    shmget(MUTEXREQUEST, N * sizeof(struct request_client_serveur), IPC_CREAT|IPC_EXCL|0600);
    shmget(MUTEXRESPONSE, N * sizeof(struct result_client_serveur), IPC_CREAT|IPC_EXCL|0600);

    printf("Init successfull.\n");
    return 0;
}