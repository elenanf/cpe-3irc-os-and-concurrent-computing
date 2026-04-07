#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void redirect(int signum) {
    if (signum == SIGINT) {
        printf("SIGINT signal received");
    }
}

int main()
{

    pid_t son = fork();

    if (son == 0) {

        struct sigaction act;
        memset(&act,0,sizeof(act));
        act.sa_handler = redirect;
        sigaction(SIGINT,&act,NULL);
        
        while (1) {
            printf("child \n");
            sleep(1);
        }

    } else {
        for (int i = 0; i < 4; i++) {
            printf("%i \n", i);
            sleep(1);
        }
        wait(NULL);

    }

    return 0;
}