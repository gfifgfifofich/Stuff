#include "Client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <ctime>
#include <chrono>



bool SockClient::Connect(std::string name,int duration,const char* ip,int port)
{

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }
    // incorrect format of date
//    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

//     std::string timestr = std::ctime(&t);

//     timestr += " ";
//     timestr += name;
//     timestr += " ";
    //     timestr += std::to_string(duration); 


    
    return true;
}
SockClient::~SockClient()
{
    close(sock);
}
bool SockClient::Send(std::string Text)
{

    if(send(sock, Text.c_str(), Text.size(), 0)<0)
        return false;
    else 
        return true;

}

std::string SockClient::Recvest()
{
    char buf[1024];
    int size = recv(sock, buf, 1024, 0);
    std::string msg;

    for(int i=0;i<size;i++)
        msg+= buf[i];

    return msg;
}
