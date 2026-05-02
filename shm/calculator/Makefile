CC = gcc
CFLAGS = -Wall -Wextra -g

all: client server init clean

dijkstra.o: dijkstra.c dijkstra.h
	${CC} ${CFLAGS} -c dijkstra.c -o dijkstra.o

client: client.c dijkstra.o shared.h
	${CC} ${CFLAGS} client.c dijkstra.o -o client

server: server.c dijkstra.o shared.h
	${CC} ${CFLAGS} server.c dijkstra.o -o server

init: init.c dijkstra.o shared.h
	${CC} ${CFLAGS} init.c dijkstra.o -o init

clean: clean.c dijkstra.o shared.h
	${CC} ${CFLAGS} clean.c dijkstra.o -o clean

delete:
	rm -f client server init clean dijkstra.o