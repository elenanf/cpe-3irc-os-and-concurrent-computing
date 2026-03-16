#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PROCESSES 8

int main(int argc, char const *argv[])
{
    const char *path = argv[1];
    (void)argc;

    //open directory
    DIR* directory = opendir(path);

    if (!directory) {
        perror("opendir");
        return 1;
    }

    //entry of the directory
    struct dirent* entry;

    int nb_processes = 0;

    while ((entry = readdir(directory)) != NULL) {
        char input_path[1024];
        strcpy(input_path, path);
        strcat(input_path, "/");
        strcat(input_path, entry->d_name);

        char output_image[1024];
        strcpy(output_image, path);
        strcat(output_image, "/");
        strcat(output_image, "thumb_");
        strcat(output_image, entry->d_name);

        pid_t pid = fork();
        if (pid == 0) {
            int error = execlp("convert", "convert", input_path, "-resize", "10%", output_image, NULL);
            if (error == -1)
            {
                perror("convert failed");
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

    //close directory
    closedir(directory);

    return 0;
}
