#pragma once
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include "singleton.h"
#include "connection.h"

class ConnectioMgr: public Singleton<ConnectioMgr>
{
    private:
        std::mutex m;
        std::condition_variable cv;
        std::unordered_map<int,Connection*>connections;
        
    public:
        int Init();
        int AddToConnectionMap(Connection* c);
        int RemoveConnection(int FD);
        int Destory();
        Connection* FindConnection(int FD);
};