#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// wc < /etc/passwd

int main()
{
    int file = open("/etc/passwd",O_RDONLY);
    dup2(file, 0);
    execlp("wc","wc",NULL);
    close(file);
    return 0;
}