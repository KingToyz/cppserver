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
        bool gotCallBackID;
        const char* bodyData;
        int bodyLen;
        int callbackID;
    public:
        Parser(Context* c);
        std::pair<std::shared_ptr<Message>,int> Execute(const char* data,int size);
        void Destory();
        void SetGetCallBackID();
        void SetCallBackID(int CallBackID);
        int GetCallBackID();
        bool CheckCallBackID();
        Context* GetContext();
        void SetBody(const char* Data,int len);
};