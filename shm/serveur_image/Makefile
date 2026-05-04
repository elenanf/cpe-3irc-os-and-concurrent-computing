CC = gcc
CFLAGS=-Wall -Wextra -g

all: serveur_traitement client init clear

serveur_traitement: internal.o serveur_traitement.o dijkstra.o

internal.o: internal.c internal.h dijkstra.h
serveur_traitement.o: serveur_traitement.c internal.h dijkstra.h data.h
dijkstra.o: dijkstra.c dijkstra.h

init: init.c dijkstra.o data.h
	${CC} ${CFLAGS} init.c dijkstra.o -o init

client: client.c dijkstra.o data.h
	${CC} ${CFLAGS} client.c dijkstra.o -o client

clear: clear.c dijkstra.o data.h
	${CC} ${CFLAGS} clear.c dijkstra.o -o clear

clean:
	rm *.o serveur_traitement init client clear
