// Init qui se chargera de créer les sémaphores nécessaires à l’exercice avec le nombre de jeton utile

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define CLE 1234

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf; /* Tampon pour IPC_INFO (spécifique à Linux) */
};

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

int main()
{
    if (sem_create(CLE, 0) == -1) {  // 0 : second sera bloqué au départ
        perror("Erreur création sémaphore");
        exit(1);
    }

    printf("Sémaphore créé avec succès.\n");
    return 0;
}