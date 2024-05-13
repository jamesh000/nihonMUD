CC = clang
CFLAGS = -c -Wall

all: nmudserver nmudclient

nmudserver:
	make -C Server
	cp Server/nmudserver .

nmudclient:
	make -C Client
	cp Client/nmudclient .

clean:
	make -C Server clean
	make -C client clean
	rm nmudclient nmudserver
