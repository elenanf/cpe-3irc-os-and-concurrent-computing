#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

struct structArg {
    pthread_mutex_t* mutex;
    int count;
    sem_t* sem;
    int n;
};

void* arrived(void* arg)
{
    struct structArg* args = arg;
    pthread_mutex_lock(args->mutex);
    args->count++;
    if (args->count == args->n) {
        pthread_mutex_unlock(args->mutex);
        puts("Everyone arrived!");

        for (int i = 0; i < args->n; i++) {
            sem_post(args->sem);
        }
    } else {
        pthread_mutex_unlock(args->mutex);
        puts("Arrived! Waiting");
        sem_wait(args->sem);
    }
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

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);
    sem_t sem;
    sem_init(&sem,0,0);

    pthread_t thread[N];
    struct structArg args;
    args.mutex = &mutex;
    args.sem = &sem;
    args.n=N;
    args.count = 0;

    for (int i =0; i < N; i++)
        pthread_create(&thread[i],NULL,arrived,&args);
    
    
    for (int i =0; i < N; i++)
        pthread_join(thread[i],NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
    
    return 0;
}