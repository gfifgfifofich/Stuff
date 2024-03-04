#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "Server.h"
#include "fstream"
#include <mutex>
//sockid, mesage
std::vector<std::pair<int,std::string>> Clientslog;
std::mutex logaddMutex;


// per client
void RunThread(int sock)
{
    char buf[1024];
    int bytes_read;



    while(1)
        {
            using namespace std::chrono_literals;
            bytes_read = recv(sock, buf, 1024, 0);

            std::cout<<"ID "<<sock<<" sent a message: ";
            for(int i=0;i<bytes_read;i++)
                std::cout<<buf[i];

            if(bytes_read <= 0) break;

            std::cout<<"\n";
			logaddMutex.lock();
			Clientslog.push_back(std::pair<int, std::string>(sock,buf));


			std::cout<<"\n log: \n";
			for(auto x : Clientslog)
				std::cout<<x.second<<"\n";

			std::fstream fs;
			fs.open("log.txt");
			for(auto l : Clientslog)
			{
				fs<<l.second;
				fs<<"\n";
			}
			fs.close();
			logaddMutex.unlock();
			
        }
    close(sock);
}



bool SockServer::start(int port)
{
    listener = socket(AF_INET, SOCK_STREAM, 0);

    if(listener < 0)
    {
        perror("socket");
		return false;
    }



    addr.sin_family = AF_INET;
    addr.sin_port = htons(30000);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
		return false;
    }

    listen(listener, 8);

	std::cout<<"Starting\n";
  
      while(1)
    {
        int sock = accept(listener, NULL, NULL);


        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        std::cout<<"Accepted\n";
        

        threads.push_back(std::pair<int, std::thread*>(sock,new std::thread(RunThread, sock)));
    }
	return true;
}

void SockServer::stop()
{
	for(auto t : threads)
		t.second->~thread();
	threads.clear();
}




SockServer::~SockServer()
{
	stop();
}

