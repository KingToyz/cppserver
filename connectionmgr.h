#pragma once
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include "singleton.h"
#include "connection.h"
#include <memory>
class SubEpollAgent;
class ConnectioMgr
{
    private:
       std::mutex l;
       std::unordered_map<int,std::shared_ptr<Connection>>connections;

       SubEpollAgent* agent;
    public:
        int Init(SubEpollAgent* agent);
        int AddToConnectionMap(int FD, SubEpollAgent* agent);
        int RemoveConnection(int FD);
        int Destory();
        std::shared_ptr<Connection>FindConnection(int FD);
        
};