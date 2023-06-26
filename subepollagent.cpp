#include "subepollagent.h"
#include "epoll.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <memory>
#include "connectionmgr.h"
#include <sys/timerfd.h>
int SubEpollAgent::Loop()
{
    auto f = [&]()
    {
        std::vector<ep_event>evs;
        bool waitstop = false;
        while(!waitstop){
            // std::cout << "sub start to wait" << std::endl;
            e.WaitEvent(evs);
            for(int i=0;i<evs.size();++i)
            {
                if(evs[i].Fd == WriteFD[0])
                {
                    char buf[1024];
                    int ret = read(WriteFD[0],buf,1024);
                    if(ret < 0)
                    {
                        perror("recv write");
                        continue;
                    }
                    auto MessagesPairs = messageMap->GetAllMessageFromMap();
                    for(auto& Message : MessagesPairs)
                    {
                        int connectionFD = Message.first;
                        std::cout << "connectionFD:"<< connectionFD << std::endl;
                        auto messages = Message.second;
                        auto c = connectionMgr.FindConnection(connectionFD);
                        if(c != nullptr)
                        {
                            int ret = c->SocketCanWrite(std::move(messages));
                            if(ret < 0)
                            {
                                std::cout << "agent write reomove" << std::endl;
                                RemoveConnection(c->GetFd());
                            }
                            else if(ret > 0)
                            {
                                RegisterEpollInEvent(c->GetFd());
                            }
                        }
                    }
                    
                }
                else if(evs[i].EventType == READ)
                {
                    // std::cout << "process read" << std::endl;
                    auto c = connectionMgr.FindConnection(evs[i].Fd);
                    if(c != nullptr)
                    {
                        int ret = c->SocketCanRead();
                        if(ret == 0)
                        {
                            std::cout << "start to remove" << std::endl;
                            RemoveConnection(c->GetFd());
                        }
                    }
                    else
                    {
                        std::cout << "not read fd:" << evs[i].Fd << std::endl;
                    }
                }
                else if(evs[i].EventType == WRITE)
                {
                    // std::cout << "process write" << std::endl;
                    auto c = connectionMgr.FindConnection(evs[i].Fd);
                    auto messages = messageMap->GetMessageFromMap(evs[i].Fd);
                    if(c != nullptr)
                    {
                        int ret = c->SocketCanWrite(std::move(messages));
                        if(ret < 0)
                        {
                            std::cout << "agent write1 reomove" << std::endl;
                            RemoveConnection(c->GetFd());
                        }
                        else if(ret > 0)
                        {
                            RegisterEpollInEvent(evs[i].Fd);
                        }
                        
                    }
                }
                else if(evs[i].EventType == EXIT)
                {
                    std::cout << "sub epoll exit" << std::endl;
                    waitstop = true;
                }
                else if(evs[i].EventType == ERROR)
                {
                    RemoveConnection(evs[i].Fd);
                }
            }
            evs.clear();
        }
        // std::cout << "loop out" << std::endl;
        connectionMgr.Destory();
        e.Stop();
    };
    t = std::thread(f);
    return 0;
}

int SubEpollAgent::Init()
{
    messageMap = new MessageMap;
    connectionMgr.Init(this);
    int ret = pipe(WriteFD);
    if(ret < 0)
    {
        perror("pipe");
        return -1;
    }
    SubEpFd = -1;
    hasexited = false;
    stop  = false;
    e.Init(SubEpFd);
    ep_event evs(WriteFD[0],READ);
    e.Register(evs);
    return 0;
}

int SubEpollAgent::AddConnection(int FD)
{
    if(stop)
    {
        return -1;
    }
    connectionMgr.AddToConnectionMap(FD,this);
    ep_event evs(FD,READ);
    e.Register(evs);
    return 0;
}

int SubEpollAgent::RemoveConnection(int FD)
{
    messageMap->DelMessage(FD);
    RegisterDelEvent(FD);
    connectionMgr.RemoveConnection(FD);
    int ret = close(FD);
    if(ret < 0)
    {
        perror("close");
    }
    return 0;
}

int SubEpollAgent::Stop()
{
    stop = true;
    e.StopEpollWait();
    t.join();
    return 0;
}


int SubEpollAgent::RegisterWriteEvent(int CallBackID,int ConnectionFD,Message&& message)
{
    std::cout << "add to map connectionID:" << ConnectionFD << std::endl;
    messageMap->AddToMap(ConnectionFD,std::forward<Message>(message));
    std::string s = std::to_string(ConnectionFD);
    std::unique_lock<std::mutex>lock(lockForWrite);
    // std::cout << "register write FD:" << s << std::endl;
    int ret = write(WriteFD[1],"1",1);
    if(ret < 0)
    {
        perror("write");
        return -1;
    }
    return 0;
}


int SubEpollAgent::AddMessagesToLeftMap(int ConnectionFD,Message&& m)
{
    return messageMap->AddToLeftMessageMap(ConnectionFD,std::forward<Message>(m));
}

int SubEpollAgent::RegisterEpollInEvent(int ConnectionFD)
{
    ep_event evs(ConnectionFD,WRITE);
    e.Register(evs);
    return 0;
}

int SubEpollAgent::RegisterDelEvent(int ConnectionFD)
{
    ep_event evs(ConnectionFD,DEL);
    e.Register(evs);
    return 0;
}