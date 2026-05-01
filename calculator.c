#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

struct request_client_serveur {
    int clientPid;
    int nombre1;
    int nombre2;
    char operator;
    int index;
};

struct result_client_serveur {
    int nombre1;
    int nombre2;
    int resultat;
    char operator;
    int index;
};

int main()
{
    printf("Please enter the number of clients: \n");
    int n;
    if (scanf("%i", &n) != 1) {
        printf("That's not a valid integer!\n");
        return 1;
    };

    int tube_server[2];
    pipe(tube_server);

    int tube_client[n][2];

    for(int i = 0; i < n; i++) {
        pipe(tube_client[i]);

        if (fork() == 0) {
            pid_t pid = getpid();
            close(tube_server[0]);

            struct request_client_serveur request;

            srand(pid);
            request.clientPid = pid;
            request.nombre1 = rand() % 10;
            request.nombre2 = rand() % 5;
            request.operator = (rand() % 2) == 0 ? '+' : '-';            
            request.index = i;
            printf("PID %d request the following expression: %i %c %i \n", pid, request.nombre1, request.operator, request.nombre2);
            
            write(tube_server[1], &request, sizeof(struct request_client_serveur));
            close(tube_server[1]);

            struct result_client_serveur result;
            read(tube_client[i][0], &result, sizeof(struct result_client_serveur));

            close(tube_client[i][0]);
            printf("The result for pid %d is %i \n", pid, result.resultat);

            exit(0);
        }
    }

    close(tube_server[1]);

    for (int i = 0; i < n; i++) {

        struct request_client_serveur received;
        read(tube_server[0], &received, sizeof(struct request_client_serveur));
        close(tube_client[received.index][0]);

        struct result_client_serveur response;
        response.nombre1 = received.nombre1;
        response.nombre2 = received.nombre2;
        response.operator = received.operator;
        response.index = received.index;

        if (response.operator == '+') {
            response.resultat = response.nombre1 + response.nombre2;
        } else if (response.operator == '-') {
            response.resultat = response.nombre1 - response.nombre2;
        }

        write(tube_client[received.index][1], &response, sizeof(struct result_client_serveur));
        close(tube_client[received.index][1]);
    }

    close(tube_server[0]);

    for(int i = 0; i < n; i++) {
        wait(NULL);
    }


    return 0;
}