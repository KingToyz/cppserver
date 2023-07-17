#pragma once
#include "singleton.h"
#include "queue.h"
#include <vector>
#include <thread>
#include <functional>
#include <iostream>
#include <coroutine>

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

class CoroutineTaskPool: public Singleton<CoroutineTaskPool> {
    private:
        MessageQueue<std::coroutine_handle<>>mq;
        int QueueSize;
        int ThreadSize;
        std::vector<std::thread>ThreadPool;
    public:
        int Init(int QSize,int TSize) {   
            // stop = false;
            mq.Init(QSize);
            ThreadSize = TSize;
            ThreadPool.resize(ThreadSize);

            return 0;
        }
        friend class Singleton<TaskPool>;
        struct promise_type;
        struct awaitable {
            bool await_ready() {
                return false;
            }
            void await_suspend(std::coroutine_handle<>h) {
                TaskPool->mq.Add(h);
            }
            void await_resume() {}
            CoroutineTaskPool* TaskPool;
            awaitable(CoroutineTaskPool* pool):TaskPool(pool){}
        };
        struct task {
            struct promise_type {
                task get_return_object() { return {}; }
                std::suspend_never initial_suspend() { return {}; }
                std::suspend_never final_suspend() noexcept { return {}; }
                void return_void() {}
                void unhandled_exception() {}
                promise_type() {}
            };
        };
        task AddToPool(std::function<void()>f) {
            co_await awaitable(this);
            f();
        }
        int Stop() {
            mq.close();
            // std::cout << "mq close " << std::endl;
            for(int i = 0;i < ThreadSize;i++)
            {
                ThreadPool[i].join();
            }
            return 0;
        }

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
                    std::coroutine_handle<>handle;
                    bool ret = mq.Pop(handle);
                    if(ret)
                    {
                        handle.resume();
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
};

