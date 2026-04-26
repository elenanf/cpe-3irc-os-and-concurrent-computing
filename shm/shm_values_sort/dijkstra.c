#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

void P(int semid)
{
    struct sembuf sempar;
    sempar.sem_num = 0;
    sempar.sem_op = -1;
    sempar.sem_flg = 0;
    if (semop(semid, &sempar, 1) == -1)
        perror("Erreur operation P");
}

void V(int semid)
{
    struct sembuf sempar;
    sempar.sem_num = 0;
    sempar.sem_op = 1;
    sempar.sem_flg = 0;
    if (semop(semid, &sempar, 1) == -1)
        perror("Erreur opération V");
}

int sem_get(key_t cle)
{
    int semid = semget(cle,1, 0600);
    if (semid == -1)
    {
        perror("Erreur semget()");
        exit(1);
    }
    return semid;
}

int sem_create(key_t cle, int initval)
{
    int semid;
    union semun arg_ctl;

    semid = semget(cle, 1, IPC_CREAT | IPC_EXCL | 0600);
    if (semid == -1) {
        perror("Erreur semget");
        return -1;
    }

    arg_ctl.val = initval;
    if (semctl(semid, 0, SETVAL, arg_ctl) == -1) {
        perror("Erreur initialisation sémaphore");
        exit(1);
    }

    return semid;
}

void sem_delete(int semid)
{
if (semctl(semid,0,IPC_RMID,0) == -1)
    perror("Erreur dans destruction sémaphore");
}

void print_tab(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%i, ", tab[i]);
    }
    printf("\n");
}