#pragma once
#include "message.h"
#include <unordered_map>
#include <mutex>
class MessageMap
{
    private:
        std::mutex l;
        std::unordered_map<int,std::vector<Message>>ConnectionIDToMessages;
        std::unordered_map<int,std::vector<Message>>ConnectionIDToLeftMessages;
    public:
        int AddToMap(int ConnectionID, Message&& m);
        std::vector<Message>GetMessageFromMap(int ConnectionID);
        int AddToLeftMessageMap(int ConnectionID,Message&& m);
        int DelMessage(int ConnectionID);
};