CC = gcc
CFLAGS = -Wall -Wextra -g

all: rdv1 rdv2 init clean

dijkstra.o: dijkstra.c dijkstra.h
	${CC} ${CFLAGS} -c dijkstra.c -o dijkstra.o

rdv1: rdv1.c dijkstra.o
	${CC} ${CFLAGS} rdv1.c dijkstra.o -o rdv1

rdv2: rdv2.c dijkstra.o
	${CC} ${CFLAGS} rdv2.c dijkstra.o -o rdv2

init: init.c dijkstra.o
	${CC} ${CFLAGS} init.c dijkstra.o -o init

clean: clean.c dijkstra.o
	${CC} ${CFLAGS} clean.c dijkstra.o -o clean

delete:
	rm -f rdv1 rdv2 init clean dijkstra.o