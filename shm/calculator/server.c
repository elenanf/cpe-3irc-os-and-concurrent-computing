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

    int semPId = sem_get(SEMP);
    int semCId = sem_get(SEMC);

    int mutexRequest = sem_get(MUTEXREQUEST);
    int mutexResponse = sem_get(MUTEXRESPONSE);

    int semResponse[N];
    for (int i = 0; i < N; i++){
        semResponse[i] = sem_get(SEMRESPONSE + i);
    }

    int RI = 0; // Read Index

    for (int i = 0; i < N; i++) {
        if (fork() == 0) {
            P(semCId);
            P(mutexRequest);
            struct request_client_serveur received;
            received = memRequest[RI];
            RI = (RI + 1) % N; // RI = 0 when pass past 9
            V(mutexRequest);
            V(semPId);


            struct result_client_serveur response;
            response.nombre1 = received.nombre1;
            response.nombre2 = received.nombre2;
            response.op = received.op;
            printf("Serveur: %d %c %d\n", received.nombre1, received.op, received.nombre2);

            if (response.op == '+') {
                response.resultat = response.nombre1 + response.nombre2;
            } else if (response.op == '-') {
                response.resultat = response.nombre1 - response.nombre2;
            } else if (response.op == '*') {
                response.resultat = response.nombre1 * response.nombre2;
            } else if (response.op == '/') {
                if (response.nombre2 == 0) {
                    printf("Division par zéro !\n");
                    response.resultat = 0;
                } else {
                    response.resultat = response.nombre1 / response.nombre2;
                }
            }

            P(mutexResponse);
            memResponse[received.index] = response;
            V(mutexResponse);
            V(semResponse[received.index]);

            exit(0);
        }
    }

    shmdt(memRequest);
    shmdt(memResponse);



    for(int i = 0; i < N; i++) {
        wait(NULL);
    }

    return 0;
}