#include "connectionmgr.h"

int ConnectioMgr::AddToConnectionMap(Connection* c)
{
    std::unique_lock<std::mutex>lock(m);
    if(connections.find(c->GetFd()) != connections.end())
    {
        return -1;
    }
    connections[c->GetFd()]  = c;
    return 0;
}

Connection* ConnectioMgr::FindConnection(int FD)
{
    std::unique_lock<std::mutex>lock(m);
    if(connections.find(FD) != connections.end())
    {
       return connections[FD];
    }
    return nullptr;
}

int ConnectioMgr::RemoveConnection(int FD)
{
    std::unique_lock<std::mutex>lock(m);
    if(connections.find(FD) != connections.end())
    {
       connections.erase(FD);
    }
    return 0;
}

int ConnectioMgr::Init()
{
    return 0;
}

int ConnectioMgr::Destory()
{
    std::unique_lock<std::mutex>lock(m);
    for(auto iter = connections.begin();iter != connections.end();iter++)
    {
        iter->second->Destory();
    }
    return 0;
}