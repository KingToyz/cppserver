#include "context.h"
#include <iostream>
#include <sys/socket.h>
#include "connection.h"
#include "taskpool.h"
#include "eventhandler.h"

void Context::Destory()
{
    // conn->Destory();
    destory = true;
    // std::cout << "context destory" << std::endl;
}

int Context::ParseRequst(const char* data,int hasRead)
{
    auto ret = parser.Execute(data,hasRead);
    if(ret.first != nullptr)
    {
        auto f = [=]()
        {
            EventHandler::GetInstance().ProcessData(ret.first,GetConnection()->GetAgent(),fd,ret.second);
        };
        TaskPool::GetInstance().AddToPool(std::move(f));
        return 1;
    }
    return -1;
}

int Context::GetFD()
{
    return fd;
}

int Context::Init()
{
    return 0;
}

bool Context::IsDestory()
{
    return destory;
}

Connection* Context::GetConnection()
{
    return connection;
}