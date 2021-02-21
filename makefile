CC = gcc
CFLAGS =-O3
all: interface

.PHONY: clean

clean:
	rm -rf *.o

interface: interface.o
	$(CC) -o interface interface.o

interface.o: interface.c
	$(CC) $(CFLAGS) -c -o interface.o interface.c
