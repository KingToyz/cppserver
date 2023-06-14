#pragma once
#include "http_parser.h"
#include <vector>
#include "message.h"
class Context;
class Parser
{
    private:
        http_parser_settings settings;
        http_parser parser;
        Context* context;
        bool keepalive;
        
    public:
        Parser(Context* c);
        int Execute(const std::vector<char>&data);
        int Send();
        void Destory();
};