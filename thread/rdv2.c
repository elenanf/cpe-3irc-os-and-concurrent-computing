#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

struct structArg {
    pthread_barrier_t* barrier;
};

void* arrived(void* arg)
{
    struct structArg* args = arg;
    puts("Arrived! Waiting");
    pthread_barrier_wait(args->barrier);    
    puts("Released");
    sleep(1);
    return NULL;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s, numbr of threads", argv[0]);
        exit(0);
    }

    int N = atoi(argv[1]);

    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier,NULL, N);

    pthread_t thread[N];
    struct structArg args;
    args.barrier = &barrier;

    for (int i =0; i < N; i++)
        pthread_create(&thread[i],NULL,arrived,&args);
    
    for (int i =0; i < N; i++)
        pthread_join(thread[i],NULL);

    pthread_barrier_destroy(&barrier);
    return 0;
}