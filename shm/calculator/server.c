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

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        exit(1);
    }
    int N = atoi(argv[1]);

    int shmrequestid = shmget(MUTEXREQUEST, N * sizeof(struct request_client_serveur),0);
    if (shmrequestid == -1) {
        perror("Shmget Memory");
    }
    struct request_client_serveur* memRequest = shmat(shmrequestid,NULL,0); // attach memory

    int shmresponseid = shmget(MUTEXRESPONSE, N * sizeof(struct result_client_serveur),0);
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
            P(semRequest);
            P(mutexRequest);
            struct request_client_serveur received;
            for (int j = 0; j < N; j++) {
                if (memRequest[j].ready == 1) {
                    received = memRequest[j];
                    memRequest[j].ready = 0;
                    break;
                }
            }
            V(mutexRequest);

            struct result_client_serveur response;
            response.nombre1 = received.nombre1;
            response.nombre2 = received.nombre2;
            response.op = received.op;
            printf("Serveur: %d %c %d\n", received.nombre1, received.op, received.nombre2);

            if (response.op == '+') {
                response.resultat = response.nombre1 + response.nombre2;
            } else if (response.op == '-') {
                response.resultat = response.nombre1 - response.nombre2;
            };

            P(mutexResponse);
            memResponse[received.index] = response;
            V(mutexResponse);
            V(semResponse[received.index]);

            exit(0);
        }
    }


    for(int i = 0; i < N; i++) {
        wait(NULL);
    }

    return 0;
}