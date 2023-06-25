#include "connection.h"
#include <vector>
#include <sys/socket.h>
#include <iostream>
#include "subepollagent.h"

int Connection::SocketCanRead()
{
    char buf[MAX_BUF];
    int hasRead = recv(fd_,buf,MAX_BUF,0);
    if(hasRead == 0)
    {
        return 0;
    }
    else if(hasRead < 0 )
    {
        perror("read");
        return -1;
    }
    else
    {
        int ret = context.ParseRequst(buf,hasRead);
        return ret;
    }
}

int Connection::Destory()
{
    // agent->RemoveConnection(fd_);
    std::cout << "conn destory" << std::endl;
    context.Destory();
    return 0;
}

int Connection::SocketCanWrite(std::vector<Message>&&messages)
{
    // int hasWrite = context.SendResponse();
    
    // return hasWrite;
    
    for(auto& message:messages)
    {
        int Pos = message.GetWritePos();
        int HasWrite = send(fd_,message.GetData()+Pos,message.GetLen()-Pos,0);
        if(HasWrite < 0)
        {
            if(errno == EAGAIN)
            {
                break;
            }
            else
            {
                perror("-1");
                return -1;
            }
        }
        else
        {
            message.SetHasWrite(HasWrite);
        }
    }
    bool NeedtoWrite = false;
    for(auto& message:messages)
    {
        if(message.GetLen() == message.GetWritePos())
        {
            if(message.GetLast())
            {
                return -1;
            }
        }
        else
        {
            agent->AddMessagesToLeftMap(fd_,std::move(message));
            NeedtoWrite = true;
        }
    }
    if(NeedtoWrite)
    {
        return 1;
    }
    return 0;
}

SubEpollAgent* Connection::GetAgent()
{
    return agent;
}