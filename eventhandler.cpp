#include "eventhandler.h"
#include "errorcode.h"
#include <iostream>
int EventHandler::ProcessData(std::shared_ptr<Message>message,SubEpollAgent* agent,int ConnectionFD,int CallBackID)
{
    std::cout << "start to process" << std::endl;
    
    Json::Value root;
    Json::Reader reader;
    bool success = reader.parse(message->GetData(),message->GetData()+message->GetLen(), root);
    if (success) 
    {
        for (const auto& key : root.getMemberNames()) 
        {
            const auto& value = root[key];
            std::cout << "Key: " << key << ", Value: " << value.asString() << std::endl;
        }
        if(root.isMember("method"))
        {
            // std::string response = "HTTP/1.1 200 OK\r\n"
            //                "Content-Type: text/html\r\n"
            //                "Content-Length: 29\r\n"
            //                "\r\n"
            //                "<html><body>Hello, world!</body></html>";
            // Message m(response.c_str(),response.size(),true);
            // agent->RegisterWriteEvent(CallBackID,ConnectionFD,std::move(m));
            auto iter = FunctionMap.find(root["method"].asString());
            if(iter != FunctionMap.end())
            {
                auto RespData = MakeSuccessResponse(CallBackID);
                Message m(RespData,true);
                agent->RegisterWriteEvent(CallBackID,ConnectionFD,std::move(m));
            }
            else
            {   
                auto RespData = MakeErrorMethodResponse(CallBackID);

                Message m(RespData,true);
                agent->RegisterWriteEvent(CallBackID,ConnectionFD,std::move(m));
            }
        }
        else 
        {

        }
        
    } 
    else 
    {
        // TODO: handle parse error
        std::cout << "parse error" << std::endl;
        return ERRORCODE::PARSEWRONG;
    }
    return ERRORCODE::SUCCESS;
}

int EventHandler::RegisterHandler(std::string method,std::function<int(const std::string& req,std::string& resp)>&&f)
{
    FunctionMap[method] = std::forward<std::function<int(const std::string& req,std::string& resp)>>(f);
    return 0;
}

int EventHandler::Init()
{
    return 0;
}


std::string EventHandler::MakeTimeoutResponse(int CallbackID)
{
   
    std::string data = "{CallBackID:\""+std::to_string(CallbackID)+"\",\"Error\":\"Timeout\"}";
    std::string ret = HTTPHEADER + "Content-Length:"+std::to_string(data.size())+"\r\n" + data;
    return data;
}

std::string EventHandler::MakeErrorMethodResponse(int CallbackID)
{
    std::string data = "{CallBackID:\""+std::to_string(CallbackID)+"\",\"Error\":\"Wrong Method\"}";
    std::string ret = HTTPHEADER + "Content-Length:"+std::to_string(data.size())+"\r\n" + data;
    return data;
}

std::string EventHandler::MakeSuccessResponse(int CallbackID)
{
    return "";
}