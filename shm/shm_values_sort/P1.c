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
    int semP1Id = sem_get(SEMP1);
    int semP0Id = sem_get(SEMP0);

    int tab[N] = {1, 6, 3, 8, 5};

    for (int i = 0; i < N; i++) {
        P(mutexId);
        int maxIndex = 0; // find the max value index
        for (int j = 1; j < N; j++) {
            if (tab[j] > tab[maxIndex]){
                maxIndex = j;
            }
        }
        mem[0] = tab[maxIndex];
        V(mutexId);
        V(semP1Id); // release the semaphore P1 which starts with 0

        P(semP0Id); // waiting or P0 to compare
        P(mutexId);
        if (mem[2] == -1) { // is the comparison over?
            print_tab(tab, N); // then we print and exit
            V(mutexId);
            V(semP1Id); //release the semaphore so P0 could check for the mem[2] == -1
            exit(0);
        }
        tab[maxIndex] = mem[0]; // take the value P0 put into the P1 shmem case
        V(mutexId);
    }

    shmdt(mem); // detach memory

    return 0;
}