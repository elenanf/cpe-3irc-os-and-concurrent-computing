#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int ends_with_c(const char* filename) {
    size_t len = strlen(filename);
    return len >= 2 && filename[len-2] == '.' && filename[len-1] == 'c';
}

int main(int argc, char* argv[])
{
    char tab[argc-2][1024];
    int obj_count = 0;

    for(int i = 1; i < (argc - 1); i++) {
        if (!ends_with_c(argv[i])) continue;

        strcpy(tab[obj_count], argv[i]);
        obj_count++;
        
        if (fork() == 0) {
            char* arguments[] = {"gcc",  "-Wall", "-Wextra", "-c", argv[i], NULL};
            int error = execvp("gcc",arguments);
            if (error == -1)
            {
                perror("execvp failed");
                exit(-1);
            }
        }
    }

    int has_error = 0;
    for (int i = 0; i < obj_count; i++) {
        int status;
        wait(&status);
        if (WEXITSTATUS(status) != 0)
            has_error = 1;
    }

    if (has_error) {
        printf("Compilation error.\n");
        exit(-1);
    }

    char* args[obj_count + 4];
    args[0] = "gcc";

    for(int i = 0; i < obj_count; i++) {
        tab[i][strlen(tab[i]) - 1] = 'o';
        args[i + 1] = tab[i];
    }
    
    args[obj_count + 1] = "-o";
    args[obj_count + 2] = argv[argc - 1];
    args[obj_count + 3] = NULL;

    
    int error1 = execvp("gcc", args);
    if (error1 == -1)
    {
        perror("Exec fail");
        exit(-1);
    }

    return 0;
}