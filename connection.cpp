#include "connection.h"
#include <vector>
#include <sys/socket.h>
#include <iostream>
#include "subepollagent.h"

int Connection::SocketCanRead()
{
    std::vector<char>buf(MAX_BUF);
    int hasRead = recv(fd_,buf.data(),MAX_BUF,0);
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
        context.ParseRequst(buf);
        return hasRead;
    }
}

int Connection::Destory()
{
    // agent->RemoveConnection(fd_);
    std::cout << "conn destory" << std::endl;
    context.Destory();
    close(fd_);
    return 0;
}

int Connection::SocketCanWrite()
{
    // int hasWrite = context.SendResponse();
    
    // return hasWrite;
    return 0;
}

