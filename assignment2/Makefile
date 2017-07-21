
CC=g++
CFLAGS=-Wall -c -g 
LFLAGS =-Wall -g
SOBJS=server.o
COBJS=client.o



all: server client

server: server.o
	$(CC) -std=c++11 $(LFLAGS) $(SOBJS) -o server

server.o : server.cpp
	$(CC) -std=c++11 $(CFLAGS) server.cpp

client: client.o
	$(CC) -std=c++11 $(LFLAGS) $(COBJS) -o client

client.o : client.cpp
	$(CC) -std=c++11 $(CFLAGS) client.cpp

.PHONY: clean
clean:
	-rm *.o server client

