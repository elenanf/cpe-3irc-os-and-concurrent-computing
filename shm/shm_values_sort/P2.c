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
    int shmid = shmget(MUTEX, 3 * sizeof(int),0);
    if (shmid == -1) {
        perror("Shmget Memory");
    }
    int* mem = shmat(shmid,NULL,0); // attach memory
    int mutexId = sem_get(MUTEX);
    int semP2Id = sem_get(SEMP2);
    int semP0Id = sem_get(SEMP0);

    int tab[N] = {9, 2, 7, 4, 10};

    for (int i = 0; i < N; i++) {
        P(mutexId);
        int minIndex = 0;
        for (int j = 1; j < N; j++) {
            if (tab[j] < tab[minIndex]){
                minIndex = j;
            }
        }
        mem[1] = tab[minIndex];
        V(mutexId);
        V(semP2Id);

        P(semP0Id);
        P(mutexId);
        if (mem[2] == -1) {
            print_tab(tab, N);
            V(mutexId);
            V(semP2Id);
            exit(0);
        }
        tab[minIndex] = mem[1];
        V(mutexId);
    }

    shmdt(mem); // detach memory

    return 0;
}