#pragma once
#include "epoll.h"
#include "subepollagent.h"
#include <vector>
#include <condition_variable>
class MainEpollAgent
{
    private:
        int EPFD;
        bool stop;
        ep e;
        std::vector<SubEpollAgent*>subEpollAgents;

    public:
        int Loop();
        int Init(int FD,int agentnum);
        int NotifyStop();
        ~MainEpollAgent();
};  