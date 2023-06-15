#pragma once
#include "epoll.h"
#include "subepollagent.h"
#include <vector>
#include <condition_variable>
#include <memory>
#include "singleton.h"
class MainEpollAgent:public Singleton<MainEpollAgent>
{
    private:
        int EPFD;
        bool stop;
        ep e;
        std::vector<std::unique_ptr<SubEpollAgent>>subEpollAgents;

    public:
        int Loop();
        int Init(int FD,int agentnum);
        int NotifyStop();
        ~MainEpollAgent();
};  