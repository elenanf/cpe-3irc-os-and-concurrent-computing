#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

int fin = false;

void redirect(int signum) {
    if (signum == SIGINT) {
        fin = true;
    }
}

int main(void)
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler = redirect;
    sigaction(SIGINT,&act,NULL);

    while(!fin) {
        printf("Hello! \n");
        sleep(2);
    }

    puts("end \n");
    return 0;
}