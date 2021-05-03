CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -lm

all: rotate mirror frame
rotate: rotate.o pgm.o
frame: frame.o pgm.o
mirror: mirror.o pgm.o
rotate.o: pgm.o
frame.o: pgm.o
mirror.o: pgm.o
pgm.o: pgm.h

clean:
	rm -f rotate.o frame.o mirror.o pgm.o
	rm -f rotate frame mirror pgm