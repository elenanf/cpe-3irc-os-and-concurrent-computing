#ifndef SHARED__H
#define SHARED__H

struct request_client_serveur {
    int clientId;
    int nombre1;
    int nombre2;
    char op;
    int index;
    int ready;
};

struct result_client_serveur {
    int nombre1;
    int nombre2;
    int resultat;
    char op;
};

#endif