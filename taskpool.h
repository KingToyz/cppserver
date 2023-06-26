#pragma once
#include "singleton.h"
#include "queue.h"
#include <vector>
#include <thread>
#include <functional>
#include <iostream>
class TaskPool: public Singleton<TaskPool> {
    private:
        MessageQueue<std::function<void()>>mq;
        int QueueSize;
        int ThreadSize;
        std::vector<std::thread>ThreadPool;
        // bool stop;
    public:
        friend class Singleton<TaskPool>;
        int Start()
        {
            // std::cout << "start" << std::endl;
            auto f = [&]()
            {
                // std::cout << "consumer to get" << std::endl;
                bool threadStop = false;
                while(!threadStop)
                {
                    // std::cout << "start to get" << std::endl;
                    std::function<void()>para;
                    bool ret = mq.Pop(para);
                    if(ret)
                    {
                        para();
                    }
                    else
                    {
                        threadStop = true;
                    }
                }
                std::cout << "consumer to exit" << std::endl;
            };
            // std::cout << "threadsize " << ThreadSize << std::endl;
            for(int i = 0;i < ThreadSize; i++)
            {
                // std::cout << "thread " << i << " start" << std::endl;
                ThreadPool[i] = std::thread(f);
                // std::cout << "thread " << i << " start finish" << std::endl;
            }
            return 0;
        }
        
        int Stop()
        {
            mq.close();
            // std::cout << "mq close " << std::endl;
            for(int i = 0;i < ThreadSize;i++)
            {
                ThreadPool[i].join();
            }
            return 0;
        }
        int Init(int QSize,int TSize)
        {   
            // stop = false;
            mq.Init(QSize);
            ThreadSize = TSize;
            ThreadPool.resize(ThreadSize);

            return 0;
        }
        int AddToPool(std::function<void()>&&f)
        {
            // std::cout << "start to add" << std::endl;
            bool flag = mq.Add(std::forward<std::function<void()>>(f));
            if(!flag)
            {
                // std::cout << "add failed" << std::endl;
            }
            return 0;
        }
        
};