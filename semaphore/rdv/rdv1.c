#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/sem.h>
#include "dijkstra.h"


int main()
{
    puts("1 is here! \n");
    sleep(1);

    V(sem_get(1));
    puts("Waiting for 2 \n");

    P(sem_get(2));

    puts("2 arrived! Continue \n");
    sleep(2);

    return 0;
}