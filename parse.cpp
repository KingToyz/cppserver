#include "parse.h"
#include "context.h"
#include <iostream>
#include "taskpool.h"
#include "message.h"
int on_message_begin(http_parser* parser)
{
    std::cout << "start to parse" << std::endl;
    return 0;
}
int on_url(http_parser* parser, const char* at, size_t len)
{
    std::string str;
    str.assign(at,len);
    std::cout << "get url "  << str << std::endl;
    return 0;
}
int on_header_field(http_parser* parser, const char* at, size_t len)
{
    std::string str;
    str.assign(at,len);
    std::cout << "get header field "  << str << std::endl;
    return 0;
}
int on_header_value(http_parser* parser, const char* at, size_t len)
{
    std::string str;
    str.assign(at,len);
    std::cout << "get header value "  << str << std::endl;
    return 0;
}
int on_headers_complete(http_parser* parser)
{
    std::cout << "on header complete "  << std::endl;
    return 0;
}
int on_body(http_parser* parser, const char* at, size_t len)
{
    std::string str;
    str.assign(at,len);
    std::cout << "get body "  << str << std::endl;
    Message message(at,len);
    
    return 0;
}
int on_message_complete(http_parser* parser)
{
    std::cout << "complete" << std::endl;
    return 0;
}
Parser::Parser(Context* c):context(c)
{
    parser.data = this;
    http_parser_settings_init(&settings);
    settings.on_message_begin = on_message_begin;
    settings.on_url = on_url;
    settings.on_header_field = on_header_field;
    settings.on_header_value = on_header_value;
    settings.on_headers_complete = on_headers_complete;
    settings.on_body = on_body;
    settings.on_message_complete = on_message_complete;
    http_parser_init(&parser, HTTP_REQUEST);

}
int Parser::Execute(const std::vector<char>&data)
{
    std::string str(data.begin(),data.end());
    std::cout << str;
    // std::string request("GET / HTTP/1.1\r\n"
    //                     "Host: 127.0.0.1\r\n"
    //                     "User-Agent: curl/7.61.1\r\n"
    //                     "Accept: */*\r\n"
    //                     "Connection: keep-alive\r\n\r\n");
    // std::cout << request;
    size_t nparsed = http_parser_execute(&parser, &settings, str.c_str(), str.size());
    if (nparsed != str.size()) {
        std::cout << "Error: " << http_errno_description(HTTP_PARSER_ERRNO(&parser)) << std::endl;
    }
    return 0;
}

int Parser::Send()
{
    context->SendResponse();
    context->Destory();
    return 0;
}
