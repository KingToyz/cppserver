#pragma once
#include <mutex>
#include <condition_variable>
#include "connection.h"
#include <vector>
#include <unordered_map>
#include <thread>
#include "epoll.h"

class SubEpollAgent
{
    private:
        int SubEpFd;
        bool stop;
        bool hasexited;
        std::mutex m;
        std::condition_variable cv;
        std::mutex l;
        std::unordered_map<int,Connection>connections;
        ep e;
        std::thread t;
        
    public:
        int Loop();
        int Init();
        int Stop();
        int AddConnection(int fd);
        int RemoveConnection(int fd);
        int RegisterEvent(int fd);
        
};