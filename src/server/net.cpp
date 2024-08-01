#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include "net.hpp"

int getListenerFd(in_port_t portNo)
{
    int listener;
    sockaddr_in servAddr{};
    int yes = 1;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener == -1) {
        return -1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(portNo);

    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    
    if (bind(listener, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1)
        return -1;
    
    if (listen(listener, 10) == -1) 
        return -1;

    return listener;
}

string getIP(sockaddr *sa)
{
    void *inAddr;
    char ip[INET6_ADDRSTRLEN];
    
    if (sa->sa_family == AF_INET)
        inAddr = &(((struct sockaddr_in*)sa)->sin_addr);
    else
        inAddr = &(((struct sockaddr_in6*)sa)->sin6_addr);

    inet_ntop(sa->sa_family, inAddr, ip, INET6_ADDRSTRLEN);
    
    return ip;
}

Poller::Poller()
{
    fdCount = 0;
    listSize = 10;
    fdList = new pollfd[listSize];
}

Poller::Poller(int size)
{
    if (size > 0) {
        fdCount = 0;
        listSize = size;
        fdList = new pollfd[listSize];
    } else {
        cerr << "Size of fdList must be greater than 0" << endl;
        exit(1);
    }
}

void Poller::addFd(int fd, short events)
{
    // Allocate more space for file descriptors if out of space
    if (fdCount == listSize) {
        pollfd *newList = new pollfd[2 * listSize];
        for (int i = 0; i < fdCount; i++)
            newList[i] = fdList[i];
    }

    // Add the new fd with events set
    fdList[fdCount].fd = fd;
    fdList[fdCount].events = events;

    fdCount++;
}

void Poller::delFd(int i)
{
    if (i < fdCount && i >= 0) {
        fdCount--;

        fdList[i] = fdList[fdCount];
    } else {
        cerr << "Out of range FD" << endl;
        exit(1);
    }
}

pollfd Poller::operator[](int i)
{
    if (i >= 0 && i < fdCount)
        return fdList[i];
    else {
        cerr << "Out of range FD" << endl;
        exit(1);
    }   
}

int Poller::poll(int timeout)
{
    int eventCount = ::poll(fdList, fdCount, timeout);

    if (eventCount == -1) {
        perror("poll");
        exit(1);
    }
    
    return eventCount;
}

int Poller::count()
{
    return fdCount;
}
