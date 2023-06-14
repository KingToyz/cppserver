#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    // 创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        cerr << "Failed to create socket." << endl;
        return 1;
    }

    // 设置服务器地址和端口号
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器 IP 地址
    server_addr.sin_port = htons(12345); // 服务器端口号

    // 连接服务器
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        cerr << "Failed to connect to server." << endl;
        return 1;
    }

    // 接收数据
    // char buffer[1024] = {0};
    // if (recv(sock, buffer, 1024, 0) == -1) {
    //     cerr << "Failed to receive message." << endl;
    //     return 1;
    // }
    // cout << "Received message: " << buffer << endl;

    // 发送数据
    char message[] = "Hello, server!";
    if (send(sock, message, strlen(message), 0) == -1) {
        cerr << "Failed to send message." << endl;
        return 1;
    }


    // 关闭套接字
    close(sock);

    return 0;
}