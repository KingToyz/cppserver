#pragma once
#include "message.h"
#include "singleton.h"
#include <unordered_map>
#include <functional>
#include "context.h"
#include "subepollagent.h"
class EventHandler: public Singleton<EventHandler>
{
    public:
        friend class Singleton<EventHandler>;
        int ProcessData(std::shared_ptr<Message>message,SubEpollAgent* agent,int ConnectionFD,int CallBackID);
        int Init();
        int RegisterHandler(std::string method,std::function<int(const std::string& req,std::string& resp)>&&f);
    private:
        std::unordered_map<std::string,std::function<int(const std::string& req,std::string& resp)>>FunctionMap;
        std::string MakeTimeoutResponse(int CallbackID);
        std::string MakeErrorMethodResponse(int CallbackID);
        std::string MakeSuccessResponse(int CallbackID);
};