#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include "shared.h"
#include "dijkstra.h"

#define MUTEXREQUEST 54321
#define MUTEXRESPONSE 54322
#define SEMREQUEST 98735
#define SEMRESPONSE 78689
#define N 3


int main()
{
    int shmrequestid = shmget(MUTEXREQUEST, 3 * sizeof(struct request_client_serveur),0);
    if (shmrequestid == -1) {
        perror("Shmget Memory");
    }
    struct request_client_serveur* memRequest = shmat(shmrequestid,NULL,0); // attach memory

    int shmresponseid = shmget(MUTEXRESPONSE, 3 * sizeof(struct result_client_serveur),0);
    if (shmresponseid == -1) {
        perror("Shmget Memory");
    }
    struct result_client_serveur* memResponse = shmat(shmresponseid,NULL,0); // attach memory

    int semRequest = sem_get(SEMREQUEST);
    int mutexRequest = sem_get(MUTEXREQUEST);
    int mutexResponse = sem_get(MUTEXRESPONSE);

    int semResponse[N];
    for (int i = 0; i < N; i++){
        semResponse[i] = sem_get(SEMRESPONSE + i);
    }

    for (int i = 0; i < N; i++) {
        if (fork() == 0) {
            srand(getpid());

            struct request_client_serveur request;

            request.clientId = getpid();
            request.nombre1 = rand() % 10;
            request.nombre2 = rand() % 5;
            request.op = (rand() % 2) == 0 ? '+' : '-';
            request.index = i;  
            request.ready = 1;

            P(mutexRequest);
            memRequest[i] = request;
            V(mutexRequest);
            V(semRequest);

            P(semResponse[i]);
            P(mutexResponse);
            struct result_client_serveur response = memResponse[i];
            V(mutexResponse);
            printf("The result for pid %d is %i \n", getpid(), response.resultat);

            exit(0);
        }
    }


    for(int i = 0; i < N; i++) {
        wait(NULL);
    }

    return 0;
}