#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

using namespace std;

int main(int argc, char *argv[]) {
    int mainSocket, newSocket;
    sockaddr_in servAddr{};
    in_port_t port = 8888;


    // Check arguments code will go here
    // -p [port] plus whatever else we can think of
    
    cout << "Starting server on port " << port << "..." << endl;

    mainSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mainSocket == -1) {
        perror("Couldn't create socket...");
        exit(1);
    }
    
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = port;

    if (bind(mainSocket, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
        perror("Couldn't bind socket...");
        exit(1);
    }

    if (listen(mainSocket, 10) == -1) {
        perror("Failed to listen on socket...");
        exit(1);
    }

    // Past this point I will have to decide how I will handle multiple clients which I will do another day (tomorrow)

    return 0;
}

