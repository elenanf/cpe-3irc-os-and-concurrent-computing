#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/sem.h>
#include "dijkstra.h"


int main()
{
    printf("First! \n");

    srand(time(NULL));
    int max_number = 5;
    int min_number = 3;
    int random = rand() % (max_number + 1 - min_number) + min_number; // entre 3 et 5

    sleep(random);
    printf("%i \n", random);

    V(sem_get(1234));

    return 0;
}