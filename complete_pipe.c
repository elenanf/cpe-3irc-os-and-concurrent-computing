#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// cut -f 1,3 -d : < /etc/passwd | sed 's+^\(.*\):\(.*\)+\2:\1+' | sort -n > users

int main()
{
    int tube[2];
    int res = pipe(tube);

    if (res == -1) {
        perror("Création Pipe");
        exit(-1);
    }

    if (fork() == 0) {

        int tube2[2];
        int res2 = pipe(tube2);
        if (res2 == -1) {
            perror("Création Pipe");
            exit(-1);
        }

        close(tube[1]);

        dup2(tube[0], 0);
        close(tube[0]);

        dup2(tube2[1], 1);
        close(tube2[1]);

        if (fork() == 0) {
            dup2(tube2[0],0);
            close(tube2[0]);
            
            int users = open("users", O_CREAT|O_WRONLY|O_TRUNC, 0644);
            dup2(users, 1);
            close(users);
            execlp("sort","sort","-n", NULL);
            perror("execlp sort"); exit(-1);
        }

        close(tube2[0]);
        
        execlp("sed", "sed", "s+^\\(.*\\):\\(.*\\)+\\2:\\1+", NULL);
        perror("sed"); exit(-1);

    } else {
        close(tube[0]);
        dup2(tube[1],1);
        close(tube[1]);

        int file = open("/etc/passwd", O_RDONLY);
        dup2(file, 0);
        execlp("cut","cut","-f", "1,3", "-d", ":", NULL);
        perror("cut"); exit(-1);
        close(file);
    }
    return 0;
}

