#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/sem.h>
#include "dijkstra.h"


int main()
{
    puts("2 is here! \n");
    sleep(1);

    V(sem_get(2));
    puts("Waiting for 1 \n");

    P(sem_get(1));

    puts("1 arrived! Continue \n");
    sleep(2);

    return 0;
}