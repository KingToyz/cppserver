#pragma once
#include "message.h"
#include "singleton.h"
class EventHandler: public Singleton<EventHandler>
{
    public:
        int ProcessData(std::shared_ptr<Message>message);
        int Init();
        int Register();
};