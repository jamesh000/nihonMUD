CC = g++
CFLAGS = -c -Wall

nmudserver: Main.o
	$(CC) -o $@ $^

Main.o: Main.cpp
	$(CC) $(CFLAGS) $<
