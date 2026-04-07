#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void redirect(int signum) {
    if (signum == SIGINT) {
        printf("SIGINT signal received");
        exit(0);
    }
}

int main(void)
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler = redirect;
    sigaction(SIGINT,&act,NULL);

    while(1) {
        printf("Hello! \n");
        sleep(2);
    }

    puts("end");
    return 0;
}