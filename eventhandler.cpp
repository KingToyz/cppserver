#include "eventhandler.h"
#include <iostream>
int EventHandler::ProcessData(std::shared_ptr<Message>message)
{
    std::cout << "start to process" << std::endl;
    
    Json::Value root;
    Json::Reader reader;
    
    auto data = message->GetData();
    // for(auto c : data)
    // {
    //     std::cout << c ;
    // }
    bool success = reader.parse(data.data(),data.data()+data.size(), root);
    if (success) 
    {
        for (const auto& key : root.getMemberNames()) 
        {
            const auto& value = root[key];
            std::cout << "Key: " << key << ", Value: " << value.asString() << std::endl;
        }
        if(root.isMember("method"))
        {
            
        }
        else 
        {

        }
        
    } 
    else 
    {
        // TODO: handle parse error
        std::cout << "parse error" << std::endl;
        return -1;
    }
    return 0;
}

int EventHandler::Register()
{
    return 0;
}

int EventHandler::Init()
{
    return 0;
}