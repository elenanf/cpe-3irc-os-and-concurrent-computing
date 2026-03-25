#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/sem.h>

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

int main()
{
    printf("First!");

    srand(time(NULL));
    int max_number = 5;
    int min_number = 3;
    int random = rand() % (max_number + 1 - min_number) + min_number; // entre 3 et 5

    sleep(random);
    printf("%i", random);

    V(sem_get(1234));

    return 0;
}