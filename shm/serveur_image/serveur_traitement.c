#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "internal.h"
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
    char* output_dir = "output";

    int mutex = sem_get(MUTEX);
    int semP = sem_get(SEMP);
    int semC = sem_get(SEMC);
    int shmid = shmget(MUTEX,MAX * sizeof(struct Data),0);
    int shmid1 = shmget(RI,1 * sizeof(int),0);

    struct Data* mem = shmat(shmid,NULL,0);
    int* memRI = shmat(shmid1,NULL,0);

    P(mutex);
    memRI[0] = 0;
    V(mutex);

    for (int i = 0; i < 5; i++) {
        if (fork() == 0) {
            while(1) {
                puts("waiting for semC");
                P(semC);
                P(mutex);
                struct Data received = mem[memRI[0]];
                memRI[0] = (memRI[0] + 1) % MAX;
                V(mutex);
                puts("Processing image");
                process_image(received.filename, output_dir);
                V(semP);
                puts("Finished!");
            }
            exit(0);
        }

    }

    for (int i = 0; i < 5; i++) {
        wait(NULL);
    }
    shmdt(mem); // detach memory 
    shmdt(memRI);
    
    return 0;
}

