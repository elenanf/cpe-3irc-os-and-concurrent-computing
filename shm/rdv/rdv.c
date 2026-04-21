#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "dijkstra.h"

#define SEM0 12345
#define MUTEX 54321
#define N 5

int main() {

    int shmid = shmget(MUTEX,1 * sizeof(int),0);
    if (shmid == -1) {
        perror("Shmget Memory");
    }
    int* mem = shmat(shmid,NULL,0);
    
    int mutexId = sem_get(MUTEX);

    for (int i = 0; i < N; i++) {
        pid_t son = fork();
        if (son == 0) {
            printf("Child %i arrived \n", i);

            // incrementer le compteur
            P(mutexId);
            mem[0]++;
            printf("Count incremented = %i \n", mem[0]);

            if (mem[0] == N) {
                V(mutexId);
                puts("Je suis le dernier");
                for (int j = 0; j < N; j++) {
                    V(sem_get(SEM0));
                }
            } else {
                V(mutexId);
                printf("Child %i waiting \n", i);
                P(sem_get(SEM0)); // il attend
            }


            sleep(1);
            shmdt(mem); //détacher la mémoire
            exit(0);
        }
    }



    // Wait for all children
    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    return 0;
}