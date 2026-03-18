#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int tube[2];    
    int res = pipe(tube);
    if (res == -1){
        perror("Création Pipe"); exit(-1);
    }

    int tube2[2];    
    int res2 = pipe(tube2);
    if (res2 == -1){
        perror("Création Pipe"); exit(-1);
    }

    if (fork() == 0) {

        close(tube[1]); // close the write end of pipe 1
        close(tube2[0]); // close the read end of pipe 2


        srand(time(NULL));
        int random = rand() % 100; // max 100 for simplicity

        while (1) {
            int nb;
            read(tube[0],&nb,sizeof(int));


            char returnChar;
            if (nb > random) {
                returnChar = '+';
            } else if (nb < random) {
                returnChar = '-';
            } else if (nb == random) {
                returnChar = '=';
            }
            
            write(tube2[1],&returnChar,sizeof(char));

             if (returnChar == '=') {
                close(tube[0]);
                close(tube2[1]);
                exit(0);
            }
        }

    } else {
        sleep(1);

        close(tube[0]);
        close(tube2[1]);

        while(1) {
            int nb;
            printf("Enter a number: \n");
            scanf("%d", &nb);

            write(tube[1],&nb,sizeof(int));

            char response;
            read(tube2[0],&response,sizeof(char));
            if (response == '=') {
                printf("Youpi! You guessed right. The number was %i \n", nb);
                close(tube[1]);
                close(tube2[0]);
                exit(0);
            } else {
                printf("Your number is %c than the number you're trying to guess! Try anothe one. \n", response);
            }
        }
    }

    return 0;
}