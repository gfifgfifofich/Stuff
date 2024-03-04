#include <iostream>

#include <thread>
#include <vector>

#include <chrono>
#include "Server.h"

#include <strstream>


int main(int argc, char** argv)
{

    SockServer serv;

    std::strstream ss;


    if(argc<=1)
    {
        std::cout<<"Исполльзование:\n Server <port>\n Пример:\n Server 3000";
        exit(1);
    }

    ss<<argv[1];
    int port;
    ss>>port;

    if(!serv.start(port))
        std::cout<<"failed to start the server";
    
    serv.stop();
    return 0;
} 
