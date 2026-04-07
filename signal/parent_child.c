#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{

    pid_t son = fork();

    if (son == 0) {

        while(1) {
            printf("child \n");
            sleep(1);
        }

    } else {
        for (int i = 0; i < 4; i++) {
            printf("%i \n", i);
            sleep(1);
            if (i == 3) {
                kill(son,SIGKILL);
            }
        }
        wait(NULL);

    }

    return 0;
}