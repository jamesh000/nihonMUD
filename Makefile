CC = g++
CFLAGS = -c -Wall

all: server client

server: object/server.o
	$(CC) -o $@ $^

client: object/client.o
	$(CC) -o $@ $^

object/server.o: src/server/server.cpp
	mkdir -p object
	$(CC) $(CFLAGS) $< -o $@

object/client.o: src/client/client.cpp
	mkdir -p object
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm client server object/*	
