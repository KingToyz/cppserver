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
    std::cout << "start to quit" << std::endl;
    MainEpollAgent::GetInstance().NotifyStop();
    TaskPool::GetInstance().Stop();
}

int main()
{   
    
    MainEpollAgent::GetInstance().Init(12345,10);
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM,signal_handler);
    TaskPool::GetInstance().Init(10,10);
    TaskPool::GetInstance().Start();
    EventHandler::GetInstance().Init();
    EventHandler::GetInstance().Register();
    MainEpollAgent::GetInstance().Loop();

}