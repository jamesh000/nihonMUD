#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>


using namespace std;

int getListenerFd(in_port_t portNo);
string getIP(sockaddr *sa);
    
class Poller {
    pollfd *fdList;
    int fdCount;
    int listSize;
    
public:
    Poller();
    Poller(int size);
    void addFd(int fd, short events);
    void delFd(int i);
    pollfd operator[](int i);
    int poll(int timeout);
    int count();
};
