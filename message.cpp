#include "message.h"
#include <iostream>
int Message::ProcessData()
{
    Json::Value root;
    Json::Reader reader;
    bool success = reader.parse(RawData.data(),RawData.data()+RawData.size(), root);
    if (success) 
    {
        for (const auto& key : root.getMemberNames()) 
        {
            const auto& value = root[key];
            std::cout << "Key: " << key << ", Value: " << value.asString() << std::endl;
        }
        // TODO: handle JSON data
    } 
    else 
    {
        // TODO: handle parse error
    }
    return 0;
}

Message::Message(const char* s,int len):RawData(s,s+len)
{
    
}