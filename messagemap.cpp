#include "messagemap.h"
int MessageMap::AddToMap(int ConnectionID,Message&& m)
{
    std::unique_lock<std::mutex>lock(l);
    ConnectionIDToMessages[ConnectionID].push_back(std::forward<Message>(m));
    return 0;
}
std::vector<Message> MessageMap::GetMessageFromMap(int ConnectionID)
{
    std::vector<Message>ret;
    std::unique_lock<std::mutex>lock(l);
    auto iter = ConnectionIDToMessages.find(ConnectionID);
    if(iter != ConnectionIDToMessages.end())
    {
        ret = std::move(iter->second);
        ConnectionIDToMessages.erase(iter);   
    }
    lock.unlock();
    iter = ConnectionIDToLeftMessages.find(ConnectionID);
    if(iter != ConnectionIDToLeftMessages.end())
    {
        ret.insert(ret.end(),std::make_move_iterator(iter->second.begin()),std::make_move_iterator(iter->second.end()));
        ConnectionIDToLeftMessages.erase(iter);
    }
    return ret;
}

int MessageMap::AddToLeftMessageMap(int ConnectionID,Message&& m)
{
    ConnectionIDToLeftMessages[ConnectionID].push_back(std::forward<Message>(m));
    return 0;
}


int MessageMap::DelMessage(int ConnectionID)
{
    ConnectionIDToLeftMessages.erase(ConnectionID);
    std::unique_lock<std::mutex>lock(l);
    ConnectionIDToMessages.erase(ConnectionID);
    return 0;
}

std::unordered_map<int,std::vector<Message>> MessageMap::GetAllMessageFromMap()
{
    std::unordered_map<int,std::vector<Message>> ret;
    std::unique_lock<std::mutex>lock(l);
    ret = std::move(ConnectionIDToMessages);
    ConnectionIDToMessages.clear();
    lock.unlock();
    for(auto& iter:ConnectionIDToLeftMessages)
    {
        ret[iter.first].insert(ret[iter.first].end(),std::make_move_iterator(iter.second.begin()),std::make_move_iterator(iter.second.end()));
    }
    ConnectionIDToLeftMessages.clear();
    return ret;
}