#pragma once
#include "const.h"
#include <vector>
#include "queue.h"
#include "parse.h"
class Connection;
class Context
{
    private:
        int fd;
        Connection* conn;
        std::vector<char> recvdata;
        std::vector<char> senddata;
        Parser parser;
    public:
        Context(int FD):fd(FD),parser(this){
            
        }
        void Destory();
        int ParseRequst(const std::vector<char>& data);
        int SendResponse();
};