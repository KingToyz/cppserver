#include "mainepollagent.h"
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include "queue.h"
#include "connectionmgr.h"

int MainEpollAgent::Loop()
{
    e.Init(EPFD);
    std::vector<ep_events>evs;
    while(!stop){
        std::cout << "main start to wait" << std::endl;
        int ret = e.WaitEvent(evs);
        if(ret < 0)
        {
            std::cout << "stop:" << stop << std::endl;
        }
        std::vector<ep_events>reg;
        for(int i=0;i<evs.size();++i)
        {
            if(evs[i].EventType == ACCPET)
            {
                std::cout << "main accept" << std::endl;
                subEpollAgents[evs[i].Fd % subEpollAgents.size()]->AddConnection(evs[i].Fd);
            }
            else if(evs[i].Fd == e.exitfd[0])
            {
                stop = true;
            }
        }
        evs.clear();
    }
    for(int i = 0 ;i < subEpollAgents.size();i++)
    {
        subEpollAgents[i]->Stop();
    }
    return 0;
}

int MainEpollAgent::Init(int FD,int num)
{
    ConnectioMgr::GetInstance().Init();
    stop = false;
    subEpollAgents.reserve(num);
    for(int i = 0 ;i < num;i++)
    { 
        auto c = std::make_unique<SubEpollAgent>();
        subEpollAgents.push_back(std::move(c));
        subEpollAgents[i]->Init();
        subEpollAgents[i]->Loop();
    }
    EPFD = FD;
    return 0;
}


int MainEpollAgent::NotifyStop()
{
    e.StopEpollWait();
    return 0;
}

MainEpollAgent::~MainEpollAgent()
{  
    e.Stop();
}