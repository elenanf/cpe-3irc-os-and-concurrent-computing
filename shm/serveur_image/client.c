#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include "dijkstra.h"
#include "data.h"

#define MUTEX 87559
#define SEMP 34797
#define SEMC 34598 
#define STR_LEN 10000
#define MAX 5

int main(void)
{
    DIR* directory = opendir("images");

    if (!directory) {
        perror("opendir");
        return 1;
    }

    //entry of the directory
    struct dirent* entry;

    int mutex = sem_get(MUTEX);
    int semP = sem_get(SEMP);
    int semC = sem_get(SEMC);
    int shmid = shmget(MUTEX,MAX * sizeof(struct Data),0);
    struct Data* mem = shmat(shmid,NULL,0);

    // char* pointers[5];
    // for (int i = 0; i < MAX; i++) {
    //     pointers[i] = (char*)mem + i*STR_LEN; // caster mem en char pour éviter d'avoir *4 (car int initiallement)
    // }

    int WI = 0; // writing index
    while ((entry = readdir(directory)) != NULL) {

        struct Data image;
        strcpy(image.filename, "images");
        strcat(image.filename, "/");
        strcat(image.filename, entry->d_name);

        P(semP);
        P(mutex);
        mem[WI] = image;
        WI = (WI + 1) % MAX; // Pour ramener IE à 0 si >= 5
        V(mutex);
        V(semC);
        puts("Releasing read sem");
    }

    shmdt(mem); // detach memory 

    return 0;
}