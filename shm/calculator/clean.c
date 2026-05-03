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

    sem_delete(sem_get(MUTEXREQUEST));
    sem_delete(sem_get(MUTEXRESPONSE));
    sem_delete(sem_get(SEMC));
    sem_delete(sem_get(SEMP));


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