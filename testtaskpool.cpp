#include "taskpool.h"
#include <iostream>
#include <unistd.h>
#include <csignal>
bool flag;
void signal_handler(int signal)
{
    TaskPool::GetInstance().Stop();
    flag = true;
}

void f(int x)
{
    std::cout << "thread: "<< x << " start"<< std::endl;
    for(int i = 0;i < 10;i++)
    {
        std::cout << "thread: "<< x << " output " << i << std::endl;
        sleep(1);
    }
}

int main()
{   
    flag = false;
    TaskPool::GetInstance().Init(100,100);
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM,signal_handler);
    TaskPool::GetInstance().Start();
    for(int i = 0 ; i < 100 ;i++)
    {
        auto f1 = [=]()
        {
            f(i);
        };
        TaskPool::GetInstance().AddToPool(std::move(f1));
    }
    for(;!flag;){}
    auto f1 = []()
        {
            f(101);
        };
    TaskPool::GetInstance().AddToPool(f1);
}