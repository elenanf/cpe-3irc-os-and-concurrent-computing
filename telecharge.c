#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PROCESSES 4

int main(int argc, char const *argv[])
{
    const char *destination_path = argv[argc-1];

    int nb_processes = 0;

    for (int i = 1; i < argc-2; i++) {

        const char* url = argv[i];
        pid_t pid = fork();
        if (pid == 0) {
            int error = execlp("wget", "wget", "-P", destination_path, url, NULL);
            if (error == -1)
            {
                perror("wget failed");
                exit(-1);
            }
        }

        nb_processes++;

        if (nb_processes >= MAX_PROCESSES) {
            wait(NULL);
            nb_processes--;
        }
    }

    while (nb_processes > 0) {
        wait(NULL);
        nb_processes--;
    }

    return 0;
}
