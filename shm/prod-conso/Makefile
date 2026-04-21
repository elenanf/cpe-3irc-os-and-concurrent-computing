CC = gcc
CFLAGS = -Wall -Wextra -g

all: prod conso init clean

dijkstra.o: dijkstra.c dijkstra.h
	${CC} ${CFLAGS} -c dijkstra.c -o dijkstra.o

prod: prod.c dijkstra.o
	${CC} ${CFLAGS} prod.c dijkstra.o -o prod

conso: conso.c dijkstra.o
	${CC} ${CFLAGS} conso.c dijkstra.o -o conso

init: init.c dijkstra.o
	${CC} ${CFLAGS} init.c dijkstra.o -o init

clean: clean.c dijkstra.o
	${CC} ${CFLAGS} clean.c dijkstra.o -o clean

delete:
	rm -f prod conso init clean dijkstra.o