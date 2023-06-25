#pragma once
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>
#include "context.h"
#include "queue.h"
#include "message.h"

class SubEpollAgent;

class Connection {
public:
    Connection(int fd,SubEpollAgent* arg) : fd_(fd),context(fd,this),agent(arg){
        
    }

    int GetFd() const {
        return fd_;
    }
    int SocketCanRead();
    
    int SocketCanWrite(std::vector<Message>&&messages);
    int Destory();
    SubEpollAgent* GetAgent();
private:
    int fd_;
    
    MessageQueue<Message>mq;
    Context context;
    SubEpollAgent* agent;
};