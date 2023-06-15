#pragma once
#include "const.h"
#include <vector>
#include "queue.h"
#include "parse.h"
#include <memory>
class Context
{
    private:
        int fd;
        std::vector<char> recvdata;
        std::vector<char> senddata;
        Parser parser;
    public:
        Context(int FD):fd(FD),parser(this){
            
        }
        int Init();
        void Destory();
        int ParseRequst(const std::vector<char>& data);
        int SendResponse();
};