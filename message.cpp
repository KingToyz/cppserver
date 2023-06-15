#include "message.h"
#include "taskpool.h"
#include "eventhandler.h"

Message::Message(const char* s,int len):RawData(s,s+len)
{
    
}



std::vector<char> Message::GetData()
{
    return RawData;
}