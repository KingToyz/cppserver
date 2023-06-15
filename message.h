#pragma once
#include <json/json.h>
#include <vector>
class Message
{
    private:    
        std::vector<char>RawData;
    public:
        // int ProcessData();
        Message(const char* s,int len);
        
        std::vector<char> GetData();
};