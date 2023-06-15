#include "subepollagent.h"
#include "epoll.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <memory>
#include "connectionmgr.h"
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
                    auto c = ConnectioMgr::GetInstance().FindConnection(evs[i].Fd);
                    if(c != nullptr)
                    {
                        int ret = c->SocketCanRead();
                        if(ret == 0)
                        {
                            RemoveConnection(evs[i].Fd);
                        }
                    }
                }
                else if(evs[i].EventType == WRITE)
                {
                    auto c = ConnectioMgr::GetInstance().FindConnection(evs[i].Fd);
                    if(c != nullptr)
                    {
                        int ret = c->SocketCanWrite();
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
        ConnectioMgr::GetInstance().Destory();
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
    auto c = new Connection(FD,this);
    ConnectioMgr::GetInstance().AddToConnectionMap(c);
    struct epoll_event ev;
    ep_events evs(FD,READ,ev);
    e.Register(evs);
    return 0;
}

int SubEpollAgent::RemoveConnection(int FD)
{
    ConnectioMgr::GetInstance().RemoveConnection(FD);
    struct epoll_event ev;
    ep_events evs(FD,DEL,ev);
    e.Register(evs);
    close(FD);
    return 0;
}

int SubEpollAgent::Stop()
{
    stop = true;
    e.StopEpollWait();
    t.join();
    return 0;
}