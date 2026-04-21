#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "dijkstra.h"

#define SEMC 12345
#define SEMP 34257
#define MUTEX 54321
#define N 3

int main() {

    srand(getpid());
    int shmid = shmget(MUTEX, N * sizeof(int),0);
    if (shmid == -1) {
        perror("Shmget Memory");
    }
    int* mem = shmat(shmid,NULL,0); // attach memory
    int mutexId = sem_get(MUTEX);
    int semCId = sem_get(SEMC);
    int semPId = sem_get(SEMP);
    int WI = 0; // Write Index

    for (int i = 0; i < 2; i++) {
        pid_t son = fork();
        if (son == 0) {

            for (int j = 0; j < N; j++) {

                P(semPId);
                P(mutexId);
                mem[WI] = rand()%10;
                printf("I wrote mem[WI]: %i \n", mem[WI]);
                WI = (WI + 1) % N; // WI = 0 when pass past 14
                V(mutexId);
                V(semCId);
                sleep(1);
            }

            shmdt(mem); // detach memory
            exit(0);
        }
    }

    // Wait for all children
    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    return 0;
}