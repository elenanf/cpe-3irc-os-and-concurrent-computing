#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf; /* Tampon pour IPC_INFO (spécifique à Linux) */
};

void P(int semid);
void V(int semid);
int  sem_get(key_t cle);
int  sem_create(key_t cle, int initval);
void sem_delete(int semid);

#endif