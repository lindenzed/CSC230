CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -lm

all: encrypt decrypt
text.o: text.h
operations.o: operations.h
decrypt: decrypt.o
encrypt: encrypt.o
encrypt.o: text.o operations.o
decrypt.o: text.o operations.o
clean:
	rm -f text.o operations.o decrypt.o encrypt.o
	rm -f encrypt decrypt
	rm -f o.txt