#pragma once
#include <cstdio>
#include <cerrno>
#include <stdlib.h>
 #include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "const.h"
#include <vector>

class ep_event {
    public:
        EVENTTYPE EventType;
        int Fd;
        ep_event(int fd,uint32_t type):EventType(type),Fd(fd){

        }
        int GetEventFd();
        
};

class ep {
    private:
        struct sockaddr_in ssin, csin;
        int epfd;
        struct epoll_event epev;
        struct epoll_event evlist[MAX];
        int fd;
        int cfd;
        
        socklen_t socklen;
        int exitfd[2];
    public:
        ep(){
            int ret = pipe(exitfd);
            if(ret != 0)
            {
                perror("pipe");
                exit(1);
            }
        }
        int Init(int port);
        int WaitEvent(std::vector<ep_event>&eventLists);
        int Register(const ep_event &event);
        int StopEpollWait();
        int Stop();
};
