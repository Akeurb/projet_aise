CC = gcc
CFLAGS =-O3

all: testGTK2 tcpserver tcpclient

.PHONY: clean

clean:
	rm -rf *.o

testGTK2: testGTK2.c
	$(CC) -o testGTK2 testGTK2.c -lprocps `pkg-config --cflags --libs gtk+-3.0`

tcpserver: tcpserver.o
	$(CC) -o tcpserver tcpserver.o

tcpserver.o: tcpserver2.c
	$(CC) $(CFLAGS) -c -o tcpserver.o tcpserver2.c

tcpclient: tcpclient.o
	$(CC) -o tcpclient tcpclient.o
	
tcpclient.o: tcpclient2.c
	$(CC) $(CFLAGS) -c -o tcpclient.o tcpclient2.c
