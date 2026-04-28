#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

struct Processus
{
    int pid;
    int index;
    int value;
};


int main()
{
    int n;
    printf("Please enter the value: \n");

    if (scanf("%i", &n) != 1) {
        printf("That's not a valid integer!\n");
        return 1;
    }

    int tube[n][2];

    // Create all of the tubes before
    for (int i = 0; i < n; i++) {
        pipe(tube[i]);
    }

    for (int i = 0; i < n; i++) {

        if (fork() == 0) {
            int next = i+1;
            if (i == (n-1)) next = 0;
            struct Processus received = {0, 0, 0};
            
            for (int j = 0; j < n; j++) {
                if (j != i) close(tube[j][0]);
                if (j != next) close(tube[j][1]);
            }

            if (i != 0) {
                read(tube[i][0],&received,sizeof(struct Processus));
            }

            srand(getpid());
            int random = rand() % 50;

            struct Processus current_processus;
            current_processus.index = i;
            current_processus.pid = getpid();
            current_processus.value = random;

            printf("processus pid %i numéro %i val = %i \n", current_processus.pid, current_processus.index, current_processus.value);

            struct Processus to_send = current_processus;
            if (received.value > current_processus.value) {
                to_send = received;
            } 
            
            if (i == 0) {
                write(tube[next][1], &to_send, sizeof(struct Processus));
                close(tube[next][1]);

                struct Processus winner;
                read(tube[i][0], &winner, sizeof(struct Processus));
                close(tube[i][0]);
                printf("Gagnant: pid=%d numéro=%d val=%d\n", winner.pid, winner.index, winner.value);
            } else {
                write(tube[next][1],&to_send,sizeof(struct Processus)); 
                close(tube[next][1]);
            }


            exit(0);
        }
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}