CC = gcc
CFLAGS =-O3

all: readproc tcpclient tcpserver

.PHONY: clean

clean:
	rm -rf *.o

tcpserver: tcpserver.o
	$(CC) -o tcpserver tcpserver.o

tcpserver.o: tcpserver2.c
	$(CC) $(CFLAGS) -c -o tcpserver.o tcpserver2.c
	
tcpclient: tcpclient.o
	$(CC) -o tcpclient tcpclient.o
	
tcpclient.o: tcpclient2.c
	$(CC) $(CFLAGS) -c -o tcpclient.o tcpclient2.c
	
readproc: readproc.o
	$(CC) -o readproc readproc.o

readproc.o: readproc.c
	$(CC) $(CFLAGS) -c -o readproc.o readproc.c
