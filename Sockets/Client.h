#pragma once
#include <netinet/in.h>
#include <string>

class SockClient
{
private:
    sockaddr_in addr;
    int sock;

public:

    bool Connect(std::string name,int duration,const char* ip,int port);
    
    bool Send(std::string Text);

    std::string Recvest();

    ~SockClient();
};


