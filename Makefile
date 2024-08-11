# Compilation options
CC = g++
CFLAGS = -c -Wall
LIBS = -lcapnp -lkj

# Directories
ODIR = obj
SDIR = src

DEPS = $(SDIR)/net.hpp

# Required object files
OBJ = $(ODIR)/net.o $(ODIR)/serial.capnp.o
CLIOBJ = $(ODIR)/client.o
SERVOBJ = $(ODIR)/server.o

all: server client

server: $(SERVOBJ) $(OBJ)
	$(CC) $(LIBS) -o $@ $^

client: $(CLIOBJ) $(OBJ)
	$(CC) $(LIBS) -o $@ $^

# Object files
$(CLIOBJ) $(SERVOBJ) $(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) objdir
	$(CC) $(CFLAGS) $< -o $@

$(SDIR)/%.capnp.cpp: $(SDIR)/%.capnp.c++
	mv $< $@

$(SDIR)/%.capnp.c++ $(SDIR)/%.capnp.h: $(SDIR)/%.capnp
	capnp compile -oc++ $<

objdir:
	mkdir -p $(ODIR)

clean:
	rm -f client server $(ODIR)/* $(SDIR)/*.capnp.*
