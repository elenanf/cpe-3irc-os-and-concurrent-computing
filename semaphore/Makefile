CC = gcc
CFLAGS = -Wall -Wextra -g

all: first second init clean

dijkstra.o: dijkstra.c dijkstra.h
	${CC} ${CFLAGS} -c dijkstra.c -o dijkstra.o

first: first.c dijkstra.o
	${CC} ${CFLAGS} first.c dijkstra.o -o first

second: second.c dijkstra.o
	${CC} ${CFLAGS} second.c dijkstra.o -o second

init: init.c dijkstra.o
	${CC} ${CFLAGS} init.c dijkstra.o -o init

clean: clean.c dijkstra.o
	${CC} ${CFLAGS} clean.c dijkstra.o -o clean

delete:
	rm -f first second init clean dijkstra.o