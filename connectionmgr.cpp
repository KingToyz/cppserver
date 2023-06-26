#include "connectionmgr.h"
#include "subepollagent.h"
#include <iostream>
int ConnectioMgr::AddToConnectionMap(int FD, SubEpollAgent* agent)
{
    std::unique_lock<std::mutex>lock(l);
    if(connections.find(FD) != connections.end())
    {
        return -1;
    }
    // std::cout << "add connection:" << FD << std::endl;
    connections[FD]  = std::make_shared<Connection>(FD,agent);
    return 0;
}

std::shared_ptr<Connection> ConnectioMgr::FindConnection(int FD)
{
    std::unique_lock<std::mutex>lock(l);
    if(connections.find(FD) != connections.end())
    {
       return connections[FD];
    }
    return nullptr;
}

int ConnectioMgr::RemoveConnection(int FD)
{
    std::cout << "mgr remove:" << FD << std::endl;
    std::unique_lock<std::mutex>lock(l);
    auto iter = connections.find(FD);
    if(iter != connections.end())
    {
       connections.erase(iter);
       iter->second->Destory();
    }
    return 0;
}

int ConnectioMgr::Init(SubEpollAgent* pagent)
{
    agent = pagent;
    return 0;
}

int ConnectioMgr::Destory()
{
    std::unique_lock<std::mutex>lock(l);
    for(auto iter = connections.begin();iter != connections.end();iter++)
    {
        iter->second->Destory();
        close(iter->first);
    }
    // std::cout << "ConnectioMgr destory finished" << std::endl;
    return 0;
}