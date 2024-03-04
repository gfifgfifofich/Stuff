#include <iostream>
#include "Client.h"

#include <strstream>
#include <chrono>
#include <thread>

std::string currentDateTime() {

    // https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %T", &tstruct);

    return buf;
}
int main(int argc, char** argv)
{
    SockClient cli;




   std::strstream ss;


    if(argc<=2)
    {
        std::cout<<"Исполльзование:\n Client <name> <duration>\n Пример:\n Client Name1 1";
        exit(1);
    }

    ss<<argv[1];
    std::string name;
    ss>>name;
    ss.clear();

    ss<<argv[2];
    int d;
    ss>>d;

    cli.Connect(name, d,"127.0.0.1",30000);
    
    while (1)
    {
      


        while(1)
        {
            std::string logtext = '[' + currentDateTime() +"] " ; 
            logtext += " ";
            logtext += name;
            if(!cli.Send(logtext.c_str()))
            std::cout<<"failed ro send initial data to server";
            std::chrono::seconds timespan(d);
            std::this_thread::sleep_for(timespan);
        }


        // std::cin.get() skips one time for some reason
        //std::cout<<"looped\n";
        //std::cout<<cli.Recvest()<<"\n";
    }

    cli.~SockClient();
    return 0;
}
