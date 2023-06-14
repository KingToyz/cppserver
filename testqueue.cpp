#include "queue.h"
#include <thread>
#include <string>
#include <iostream>
#include <unistd.h>

int main()
{
    MessageQueue<std::string>mq(10);
    auto f1 = [&]()
    {
        for(int i = 0;i< 10 ;i++)
        {
            std::string t = "f1 add one";
            t += " " + std::to_string(i);
            mq.Add(std::move(t));
        } 
        sleep(1);
        mq.close();

    };   
    auto f2 = [&]()
    {
        for(int i = 0;i< 10 ;i++)
        {
            std::string t = "f2 add one";
            t += " " + std::to_string(i);
            mq.Add(std::move(t));
        }
        
    };
    auto f3 = [&]()
    {
        for(int i = 0;i < 21 ;i++)
        {
            std::string t;
            bool b = mq.Pop(t);
            if(b)
            {
                std::cout << "get " << t << std::endl;
            }
        }
    };
    std::thread t1(f1);
    std::thread t2(f2);
    std::thread t3(f3);
    t1.join();
    t2.join();
    t3.join();
}