#include <cstdio>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Starting client..." << endl;

    int serverSock;
    int status;
    addrinfo hints{};
    addrinfo *serverInfo;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    if ((status = getaddrinfo(argv[1], argv[2], &hints, &serverInfo)) != 0) {
        cerr << "getaddrinfo failed with status: " << gai_strerror(status) << endl;
        exit(1);
    }

    serverSock = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
    if (serverSock == -1) {
        cerr << "Failed to get socket" << endl;
        exit(1);
    }
    
    if (connect(serverSock, serverInfo->ai_addr, serverInfo->ai_addrlen) == -1) {
        perror("connect");
        exit(1);
    }

    // game loop
    for (;;) {
        string buffer;
        getline(cin, buffer);

        int bytesSent = send(serverSock, buffer.c_str(), buffer.length(), 0);
        if (bytesSent == -1)
            perror("send");
    }
    
    return 0;
}
