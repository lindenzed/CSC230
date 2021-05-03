CC = gcc
CFLAGS = -D_GNU_SOURCE -Wall -std=c99 -g
LDFLAGS = -lm

all: decode encode
decode: decode.o j10.o image.o bits.o
encode: encode.o j10.o image.o bits.o
bits.o: bits.h
image.o: image.h
j10.o: j10.h bits.h bits.o image.h image.o
clean:
	rm -f decode encode decode.o encode.o j10.o image.o bits.o
