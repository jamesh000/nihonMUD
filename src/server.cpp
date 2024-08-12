#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "net.hpp"
#include <capnp/message.h>
#include <capnp/serialize.h>
#include "serial.capnp.h"

using namespace std;

int main(int argc, char *argv[]) {
    Poller netFds;

    int listener = getListenerFd(8888);

    if (listener == -1) {
        cerr << "Could not create listening port" << endl;
        exit(1);
    }

    // For accepting connections
    int clientFd;
    sockaddr_storage clientAddr;
    socklen_t addrLen;
    
    netFds.addFd(listener, POLLIN);

    for (;;) {
        int eventCount = netFds.poll(-1);
        for (int i = 0; i < netFds.count(); i++) {
            // Found a file descriptor read to read
            if (netFds[i].revents & POLLIN) {
                // If the file descriptor is the listener, set up a new connection
                if (netFds[i].fd == listener) {
                    
                    addrLen = sizeof clientAddr;
                    clientFd = accept(listener, (sockaddr*)&clientAddr, &addrLen);
                    
                    if (clientFd == -1)
                        perror("accept");
                    else {
                        netFds.addFd(clientFd, POLLIN);
                        cout << "New connection from " << getIP((sockaddr*)&clientAddr) << endl;
                    }
                } else {
                    // Read in the message
                    capnp::StreamFdMessageReader message(netFds[i].fd);
                    Command::Reader userCmd = message.getRoot<Command>();
                    
                    // This is where the 
                    switch (userCmd.getPredicate()) {
                    case ::Command::Type::GO: cout << "go "; break;
                    case ::Command::Type::ATTACK: cout << "attack "; break;
                    case ::Command::Type::TALK: cout << "attack "; break;
                    case ::Command::Type::BUY: cout << "buy "; break;
                    case ::Command::Type::SELL: cout << "sell "; break;
                    }
                    cout << userCmd.getSubject() << endl;
                }

                eventCount--;
                if (eventCount == 0)
                    break;
            }
        }
    }

    return 0;
}

