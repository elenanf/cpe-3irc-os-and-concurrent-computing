// Clean qui se chargera de supprimer les sémaphores une fois l’exécution de vos programmes terminés

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main()
{
    sem_delete(sem_get(1234));
    printf("Cleaned!");

    return 0;
}