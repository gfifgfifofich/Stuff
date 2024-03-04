#ifndef ServerH
#define ServerH
#include <netinet/in.h>
#include <string>

#include <thread>
#include <vector>

#include <map>
inline std::vector<int> Socks;

//sockid, thread
inline std::vector<std::pair<int,std::thread*>> threads;

inline std::map<int,float> connections;

class SockServer
{
    int listener;
    struct sockaddr_in addr;

public:


    char buf[1024];
    int bufSize;

    bool start(int port);
    void stop();



    ~SockServer();
};
#endif
