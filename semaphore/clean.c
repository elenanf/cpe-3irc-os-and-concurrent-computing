// Clean qui se chargera de supprimer les sémaphores une fois l’exécution de vos programmes terminés

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

void sem_delete(int semid)
{
if (semctl(semid,0,IPC_RMID,0) == -1)
    perror("Erreur dans destruction sémaphore");
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

int main()
{
    sem_delete(sem_get(1234));

    return 0;
}