#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char tab[argc-2][1024];
    for(int i = 1; (i-1) < (argc - 2); i++) {
        strcpy(tab[i-1], argv[i]);
        if (fork() == 0) {
            char* arguments[4] = {"gcc","-c", argv[i], NULL};
            int error = execvp("gcc",arguments);
            if (error == -1)
            {
                printf("Compilation error with the following file: %s", argv[i]);
                exit(-1);
            }
        }
    }

    for(int i = 1; (i-1) < (argc - 2); i++) {
        wait(NULL);
    }

    char* args[argc + 2];
    args[0] = "gcc";
    int count = 1;
    for(int i = 1; i < (argc - 1); i++) {
        tab[i-1][strlen(tab[i-1]) - 1] = 'o';
        args[i] = tab[i-1];
        count++;
    }
    
    args[count] = "-o";
    args[count + 1] = argv[argc-1];
    args[count + 2] = NULL;
    
    int error1 = execvp("gcc", args);
    if (error1 == -1)
    {
        perror("Exec fail");
        exit(-1);
    }

    return 0;
}