#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//cut -f 1 -d : /etc/passwd | tr a-z A-Z

int main()
{
int tube[2];
int res = pipe(tube);
    if (res == -1) {
        perror("Création Pipe");
        exit(-1);
    }
    if (fork() == 0) {
        close(tube[1]);
        dup2(tube[0],0);
        close(tube[0]);
        execlp("tr","tr","a-z", "A-Z", NULL);
    } else {
        close(tube[0]);
        dup2(tube[1],1);
        close(tube[1]);
        execlp("cut","cut","-f", "1", "-d", ":", "/etc/passwd", NULL);
    }
    return 0;
}

