CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -lm

all: movies
input.o: input.h
database.o: database.h
movies.o: input.o database.o
movies: movies.o
clean:
	rm -f movies movies.o input.o database.o