#include "context.h"
#include <iostream>
#include <sys/socket.h>
void Context::Destory()
{
    // conn->Destory();
    std::cout << "context destory" << std::endl;
}

int Context::ParseRequst(const std::vector<char>& data)
{
    parser.Execute(data);
    return 0;
}

int Context::SendResponse()
{
    std::string str = "testtestsetestsetset";
    std::copy(str.begin(),str.end(),std::back_inserter(senddata));
    int haswrite = send(fd,senddata.data(),senddata.size(),0);
    if(haswrite >= 0 )
    {
        return haswrite;
    }
    else
    {
        perror("write");
        return -1;
    }
    return 0;
}

