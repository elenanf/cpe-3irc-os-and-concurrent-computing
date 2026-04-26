CC = gcc
CFLAGS = -Wall -Wextra -g

all: P0 P1 P2 init clean

dijkstra.o: dijkstra.c dijkstra.h
	${CC} ${CFLAGS} -c dijkstra.c -o dijkstra.o

P0: P0.c dijkstra.o
	${CC} ${CFLAGS} P0.c dijkstra.o -o P0

P1: P1.c dijkstra.o
	${CC} ${CFLAGS} P1.c dijkstra.o -o P1

P2: P2.c dijkstra.o
	${CC} ${CFLAGS} P2.c dijkstra.o -o P2

init: init.c dijkstra.o
	${CC} ${CFLAGS} init.c dijkstra.o -o init

clean: clean.c dijkstra.o
	${CC} ${CFLAGS} clean.c dijkstra.o -o clean

delete:
	rm -f P0 P1 P2 init clean dijkstra.o