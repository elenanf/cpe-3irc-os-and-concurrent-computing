#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define N 5

struct threadArg {
    int buffer[N]; 
    int WI;
    int RI;
    pthread_mutex_t mutex;
    sem_t semP;
    sem_t semC;
};

void* produce(void* arg) {
    srand(getpid());

    struct threadArg* args = arg;

    while (1) {

        sem_wait(&args->semP);
        pthread_mutex_lock(&args->mutex);

        args->buffer[args->WI] = rand()%10;
        args->WI = (args->WI + 1) % N;
        pthread_mutex_unlock(&args->mutex);
        sem_post(&args->semC);
        sleep(1);
    }
    return NULL;
}

void* consume(void* arg)
{
    struct threadArg* args = arg;

    while (1) {

        sem_wait(&args->semC);
        pthread_mutex_lock(&args->mutex);

        int value = args->buffer[args->RI];
        printf("I read value: %i \n", value);

        args->RI = (args->RI + 1) % N;
        pthread_mutex_unlock(&args->mutex);
        sem_post(&args->semP);
        sleep(1);
    }
    return NULL;
}

int main()
{

    struct threadArg* args = malloc(sizeof(struct threadArg));
    sem_init(&args->semP, 0, N);
    sem_init(&args->semC, 0, 0);
    pthread_mutex_init(&args->mutex, NULL);
    
    pthread_t threadProd[N];
    pthread_t threadConso[N];

    for (int i = 0; i < N; i++) {
        pthread_create(&threadProd[i],NULL,produce,args);
        pthread_create(&threadConso[i],NULL,consume,args);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threadProd[i],NULL);
        pthread_join(threadConso[i],NULL);
    }

    sem_destroy(&args->semC);
    sem_destroy(&args->semP);
    pthread_mutex_destroy(&args->mutex);
    free(args);

    return 0;
}