#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{

    pid_t pid1, pid2, pid3;

    pid1 = fork();
    if (pid1 == 0) {
        int error = execlp("du", "du", "-sh", "/usr/share", NULL);
        if (error == -1)
        {
            perror("du fail");
            exit(-1);
        }
    }
    wait(NULL);


    pid2 = fork();
    if (pid2 == 0) {
        int error = execlp("ls", "ls", "-l", NULL);
        if (error == -1)
        {
            perror("ls fail");
            exit(-1);
        }
    }
    wait(NULL);



    pid3 = fork();
    if (pid3 == 0) {
        int error = execlp("ps", "ps", NULL);
        if (error == -1)
        {
            perror("ls fail");
            exit(-1);
        }
    }
    wait(NULL);

    return 0;
}