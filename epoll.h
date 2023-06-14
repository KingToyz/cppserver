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

class ep_events {
    public:
        uint32_t EventType;
        int Fd;
        epoll_event Ev;
        ep_events(int fd,uint32_t type,epoll_event ev):EventType(type),Fd(fd),Ev(ev){

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
    public:
        int exitfd[2];
        ep(){
            int ret = pipe(exitfd);
            if(ret != 0)
            {
                perror("pipe");
                exit(1);
            }
        }
        int Init(int port);
        int WaitEvent(std::vector<ep_events>&eventLists);
        int Register(const ep_events &event);
        int StopEpollWait();
        int Stop();
};
