#include "mainepollagent.h"
#include <csignal>
#include <iostream>
#include <unistd.h>  
#include <functional>
#include <vector>
#include "taskpool.h" 
MainEpollAgent* mea;

void signal_handler(int signal)
{
    std::cout << "start to quit" << std::endl;
    mea->NotifyStop();
}

int main()
{   
    mea = new MainEpollAgent;
    mea->Init(12345,100);
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM,signal_handler);
    mea->Loop();
    TaskPool::GetInstance().Init(10,10);
    
    delete mea;
}