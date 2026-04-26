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
    int semP2Id = sem_get(SEMP2);
    int semP0Id = sem_get(SEMP0);

    for (int i = 0; i < N; i++) {
        P(semP1Id); // waiting on P1 and P2 to finish their first iteration
        P(semP2Id);

        P(mutexId); // check
        if (mem[2] == -1) {
            exit(0);
        }

        if (mem[0] > mem[1]) {
            int tmp = mem[0];
            mem[0] = mem[1];
            mem[1] = tmp;
        } else {
            mem[2] = -1;
        }
        V(mutexId);
        V(semP0Id); // comparison finished. release P0 semaphore 2 times, for P1 and P2
        V(semP0Id);
    }

    shmdt(mem); // detach memory
    
    return 0;
}