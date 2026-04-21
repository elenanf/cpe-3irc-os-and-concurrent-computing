CC = gcc
CFLAGS = -Wall -Wextra -g

all: rdv init clean

dijkstra.o: dijkstra.c dijkstra.h
	${CC} ${CFLAGS} -c dijkstra.c -o dijkstra.o

rdv: rdv.c dijkstra.o
	${CC} ${CFLAGS} rdv.c dijkstra.o -o rdv

init: init.c dijkstra.o
	${CC} ${CFLAGS} init.c dijkstra.o -o init

clean: clean.c dijkstra.o
	${CC} ${CFLAGS} clean.c dijkstra.o -o clean

delete:
	rm -f rdv init clean dijkstra.o