#pragma once
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>
#include "context.h"
class SubEpollAgent;

class Connection {
public:
    Connection(int fd,SubEpollAgent* agent) : fd_(fd),context(fd),agent(agent){
    }

    int GetFd() const {
        return fd_;
    }
    int SocketCanRead();
    
    int SocketCanWrite();
    int Destory();
private:
    int fd_;
    Context context;
    SubEpollAgent* agent;
};