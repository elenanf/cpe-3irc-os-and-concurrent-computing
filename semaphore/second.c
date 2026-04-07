#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/sem.h>
#include "dijkstra.h"


int main()
{
    printf("Second! \n");

    P(sem_get(1234));

    srand(time(NULL));
    int max_number = 4;
    int min_number = 1;
    int random = rand() % (max_number + 1 - min_number) + min_number; // entre 1 et 4

    sleep(random);

    printf("Second terminated \n");
    V(sem_get(1234));

    return 0;
}