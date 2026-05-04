#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "dijkstra.h"
#include "data.h"

#define MUTEX 87559
#define RI 86549
#define SEMP 34797
#define SEMC 34598 
#define STR_LEN 10000
#define MAX 5

int main(void)
{
    int shmid = shmget(MUTEX,MAX * sizeof(struct Data),0);
    int res = shmctl(shmid,IPC_RMID,NULL);
    if (res == -1) {
        perror("Delete Shm");
    }

    int shmid1 = shmget(RI,1 * sizeof(int),0);
    int res1 = shmctl(shmid1,IPC_RMID,NULL);
    if (res1 == -1) {
        perror("Delete Shm");
    }

    sem_delete(sem_get(MUTEX));
    sem_delete(sem_get(SEMP));
    sem_delete(sem_get(SEMC));
    
    printf("Cleared!");

    return 0;
}