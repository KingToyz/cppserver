#pragma once
#include <mutex>
#include <condition_variable>
#include "connection.h"
#include <vector>
#include <unordered_map>
#include <thread>
#include "epoll.h"
#include <mutex>
#include "connectionmgr.h"
#include "messagemap.h"
#include <unordered_set>
class SubEpollAgent
{
    private:
        int SubEpFd;
        bool stop;
        bool hasexited;
        std::mutex lockForWrite;
        ep e;
        std::thread t;
        // std::unordered_map<int,std::vector<int>>TimeFDToConnectioFDAndCallbackIDMap;
        // std::unordered_map<int,int>CallBackIDToTimeFDMap;
        // std::unordered_map<int,std::unordered_set<int>>ConnectionFDToTimeFDMap;
        MessageMap* messageMap;
        ConnectioMgr connectionMgr;
        int WriteFD[2];
    public:
        int Loop();
        int Init();
        int Stop();
        int AddConnection(int fd);
        int RemoveConnection(int fd);
        int RegisterWriteEvent(int CallBackID,int ConnectionFD,Message&& message);
        int AddMessagesToLeftMap(int ConnectionFD,Message&& m);
        int RegisterEpollInEvent(int ConnectionFD);
        int RegisterDelEvent(int ConnectionFD);
};