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
#define SEMREQUEST 98735
#define SEMRESPONSE 78689
#define N 3

int main()
{
    sem_delete(sem_get(MUTEXREQUEST));
    sem_delete(sem_get(MUTEXRESPONSE));
    sem_delete(sem_get(SEMREQUEST));
    

    for (int i = 0; i < N; i++) {
        sem_delete(sem_get(SEMRESPONSE + i));
    }

    int shmid1 = shmget(MUTEXREQUEST, N * sizeof(struct request_client_serveur),0);
    int res1 = shmctl(shmid1,IPC_RMID,NULL);
    if (res1 == -1) {
        perror("Delete Shm");
        exit(1);
    }

    int shmid2 = shmget(MUTEXRESPONSE, N * sizeof(struct result_client_serveur),0);
    int res2 = shmctl(shmid2,IPC_RMID,NULL);
    if (res2 == -1) {
        perror("Delete Shm");
        exit(1);
    }

    printf("Cleaned!");

    return 0;
}