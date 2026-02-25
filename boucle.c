#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    for(int i=0; i<3; i++)
    {
        pid_t child = fork();
        pid_t parent = getppid();
        pid_t myself = getpid();

        printf("%d: Je suis le processus %d, mon père est le processus %d, fork a retourné %d\n", i, myself, parent, child);
    }
    return 0;
}