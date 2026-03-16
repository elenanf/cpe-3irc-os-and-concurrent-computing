#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char* argv[])
{
    (void)argc;
    int n  =  atoi(argv[1]);

    int child_status = 0;
    for(int i = 0; i < n; i++) {
        pid_t child = fork();
        pid_t parent = getppid();

        if (child == 0) {
            sleep(2*i);
            printf("(PID: %d, my parent PPID: %d) I woke up! \n", child, parent);
            exit(i);
        }
    }

    for (int i = 0; i < n; i++) {
        pid_t terminated_child = wait(&child_status);
        printf("Child: %d, Status: %d\n",terminated_child, WEXITSTATUS(child_status));
    }

    return 0;
}