#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int hits = 1000000;

void* calcul(void* arg)
{
    int* nb_hits = arg;
    int* success = malloc(sizeof(int));
    int seed = rand();

    for (int i = 0; i < *nb_hits; i++) {
        float x = rand_r() / (float)RAND_MAX; // rand a un mutex!
        float y = rand_r() / (float)RAND_MAX;
        if (x*x + y*y < 1)
            (*success)++;
    }
    return success;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("usage: %s number_of_threads\n", argv[0]);
    }

    int nb_thread = 0;
    int success = sscanf(argv[1], "%d", &nb_thread); // instead of atoi, it is better to use sscanf

    pthread_t threads[nb_thread];
    int nb_hits = hits / nb_thread;
    for (int i = 0; i < nb_thread; i++) {
        pthread_create(&threads[i], NULL, calcul, &nb_hits);
    }

    int res = 0;
    for (int i = 0; i < nb_thread; i++) {
        int* ptr = NULL; // pointeur vers mon success
        pthread_join(threads[i], (void**)&ptr);
        res += *ptr;
        free(ptr);
    }
    int res = calcul();
    printf("%f\n", 4*res / (float)hits;
    return 0;
}