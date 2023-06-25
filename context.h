#pragma once
#include "const.h"
#include <vector>
#include "queue.h"
#include "parse.h"
#include <memory>
class Connection;
class Context
{
    private:
        int fd;
        Connection* connection;
        Parser parser;
        bool destory;
    public:
        Context(int FD,Connection* connection):fd(FD),parser(this),connection(connection),destory(false){
            
        }
        int Init();
        void Destory();
        int ParseRequst(const char* data,int hasRead);
        int GetFD();
        bool IsDestory();
        Connection* GetConnection();
};