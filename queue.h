#pragma once
#include <deque>
#include <mutex>
#include <condition_variable>
template<class T>
class MessageQueue
{
    private:
        std::deque<T>q;
        std::mutex l;
        int num;
        std::condition_variable cv1,cv2;
        bool shutdown;
    public:
        MessageQueue():shutdown(false),num(1){}
        MessageQueue(int n):shutdown(false),num(n){}
        int Init(int n)
        {
            num = n;
            return 0;
        }
        void close()
        {
            shutdown = true;
            cv1.notify_all();
            cv2.notify_all();
        }
        bool Add(T&& h)
        {
            while(!shutdown)
            {
                std::unique_lock<std::mutex>lock(l);
                while(!shutdown && q.size() > num)
                {
                    cv2.wait(lock);
                }
                if(shutdown)
                {
                    return false;
                }
                q.push_back(std::forward<T>(h));
                lock.unlock();
                cv1.notify_one();
                return true;
            }
            return false;
        }
        bool Pop(T &t)
        {
            while(!shutdown)
            {
                std::unique_lock<std::mutex>lock(l);
                while(!shutdown && q.empty())
                {
                    cv1.wait(lock);
                }
                if(shutdown)
                {
                    if(q.empty())
                    {
                        return false;
                    }
                }
                t = std::move(*q.begin());
                q.pop_front();
                lock.unlock();
                cv2.notify_one();
                return true;
            }
            return false;
        }
};