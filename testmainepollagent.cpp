#include "mainepollagent.h"
#include <csignal>
#include <iostream>
#include <unistd.h>  
#include <functional>
#include <vector>
#include "taskpool.h" 
#include "eventhandler.h"

void signal_handler(int signal)
{
    // std::cout << "start to quit" << std::endl;
    TaskPool::GetInstance().Stop();
    MainEpollAgent::GetInstance().NotifyStop();
}

int Test(const std::string& req,std::string& resp)
{
    resp = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html\r\n"
                           "Content-Length: 39\r\n"
                           "\r\n"
                           "<html><body>Hello, world!</body></html>";
    return 0;
}

int main()
{   
    MainEpollAgent::GetInstance().Init(12345,10);
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM,signal_handler);
    TaskPool::GetInstance().Init(100000,10);
    TaskPool::GetInstance().Start();
    EventHandler::GetInstance().Init();
    // EventHandler::GetInstance().Register();
    EventHandler::GetInstance().RegisterHandler("Test",Test);
    MainEpollAgent::GetInstance().Loop();
}