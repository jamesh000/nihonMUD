CC = g++
CFLAGS = -c -Wall

nmudclient: Main.o
	$(CC) -o $@ $^

Main.o: Main.cpp
	$(CC) $(CFLAGS) $<
