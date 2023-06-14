#include "subepollagent.h"
#include "epoll.h"
#include <iostream>
#include <string.h>
#include <unistd.h>

int SubEpollAgent::Loop()
{
    auto f = [&]()
    {
        std::vector<ep_events>evs;
        while(!stop){
            std::cout << "sub start to wait" << std::endl;
            e.WaitEvent(evs);
            for(int i=0;i<evs.size();++i)
            {
                if(evs[i].EventType == READ)
                {
                    auto iter = connections.find(evs[i].Fd);
                    if(iter != connections.end())
                    {
                        int ret = iter->second.SocketCanRead();
                        if(ret == 0)
                        {
                            RemoveConnection(evs[i].Fd);
                        }
                    }
                }
                else if(evs[i].EventType == WRITE)
                {
                    auto iter = connections.find(evs[i].Fd);
                    if(iter != connections.end())
                    {
                        int ret = iter->second.SocketCanWrite();
                        if(ret == 0)
                        {
                            RemoveConnection(evs[i].Fd);
                        }
                    }
                }
                else if(evs[i].Fd == e.exitfd[0])
                {
                    stop = true;
                }
            }
            evs.clear();
        }
        std::vector<int>StopFd;
        for(auto iter = connections.begin();iter != connections.end();iter++)
        {
            int FD = iter->first;
            StopFd.push_back(FD);
        }
        for(int i=0;i< StopFd.size();i++)
        {
            RemoveConnection(StopFd[i]);
        }
        e.Stop();
    };
    t = std::thread(f);
    return 0;
}

int SubEpollAgent::Init()
{
    SubEpFd = -1;
    hasexited = false;
    stop  = false;
    e.Init(SubEpFd);
    return 0;
}

int SubEpollAgent::AddConnection(int FD)
{
    if(stop)
    {
        return -1;
    }
    Connection c(FD,this);
    std::unique_lock<std::mutex>lock(m);
    connections.insert({FD,std::move(c)});
    struct epoll_event ev;
    ep_events evs(FD,READ,ev);
    e.Register(evs);
    m.unlock();
    return 0;
}

int SubEpollAgent::RemoveConnection(int FD)
{
    std::unique_lock<std::mutex>lock(m);
    auto iter = connections.find(FD);
    if(iter != connections.end())
    {
        connections.erase(iter);
    }
    struct epoll_event ev;
    ep_events evs(FD,DEL,ev);
    e.Register(evs);
    m.unlock();
    return 0;
}

int SubEpollAgent::Stop()
{
    stop = true;
    e.StopEpollWait();
    t.join();
    return 0;
}