#include "epoll.h"
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
void SetNoBlock(int fd)
{
    int fl = fcntl(fd, F_GETFL); //文件描述符的属性取出来存入fl中
    if (fl < 0)
    { //执行失败返回-1并报错
        perror("fcntl");
        return;
    }
    fcntl(fd, F_SETFL, fl | O_NONBLOCK); //设置fl | O_NONBLOCK 类似位图填充类型设置
}


int ep_events::GetEventFd()
{
    return Fd;
}

int ep::Init(int port)
{
    epfd = epoll_create1(0);
    if (0 > epfd) 
    { 
        perror("epoll_create1"); exit(1); 
    }
    epev.events = EPOLLIN | EPOLLET;
    epev.data.fd = STDIN_FILENO; // for quit
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &epev);
    if (0 > ret) 
    { 
        perror("epoll_ctl_STDIN_FILENO");exit(1); 
    }
    epev.events = EPOLLIN | EPOLLET;
    epev.data.fd = exitfd[0]; // for quit
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, exitfd[0], &epev);
    if (0 > ret) 
    { 
        perror("epoll_ctl_exitfd");exit(1); 
    }
    if(port != -1)
    {
        socklen = sizeof(struct sockaddr);
        memset(&ssin, 0, socklen);
        ssin.sin_family      = AF_INET;
        ssin.sin_port    = htons(port);
        ssin.sin_addr.s_addr = htonl(INADDR_ANY);
        fd = socket(AF_INET, SOCK_STREAM, 0);
        if(0 > fd)
        {
            perror("socket");
            // exit(1);
        }
        std::cout << "fd:" << fd << std::endl;
        if (0 > bind(fd, (struct sockaddr *)&ssin, socklen)) 
        { 
            perror("bind"); 
            exit(1); 
        }
    
        if (0 > listen(fd, 5)) 
        { 
            perror("listen"); 
            exit(1); 
        }
        epev.data.fd = fd;
        ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &epev);
        if (0 > ret) 
        {
            perror("epoll_ctl_EPOLL_CTL_ADD"); exit(1); 
        }
    }
    return 0;
}

int ep::WaitEvent(std::vector<ep_events>&eventLists)
{
    char buf[BUFSIZ];
    int buflen;
    int nfds = epoll_wait(epfd,evlist,MAX,-1);
    std::cout << "nfds:" << nfds << std::endl;
    if(nfds < 0)
    {
        perror("WaitEvent epoll_wait");
        return -1;
    }
    for(int i = 0;i < nfds;i++)
    {
        std::cout << "waitfd:" << evlist[i].data.fd << std::endl;
        if (evlist[i].data.fd == STDIN_FILENO)
        {
            fgets(buf, BUFSIZ-1, stdin);
            if (!strcmp(buf, "quit") || !strcmp(buf, "exit"))
            {
                close(fd);
                std::cout << "fd:" << fd << "quit" << std::endl;
                exit(1);
            }
        }
        else if (evlist[i].data.fd == fd)
        {
            cfd = accept(fd,(struct sockaddr *)&csin,&socklen);
            std::cout << "acceptfd:" << cfd << std::endl;
            if(cfd < 0) 
            {
                perror("accept");
                continue;
            }
            SetNoBlock(cfd);
      
            // epev.events = EPOLLIN | EPOLLET;
            // epev.data.fd = cfd;
            // int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
            // if (ret < 0) 
            // { 
            //     perror("epoll_ctl_read");
            // }
            ep_events e(cfd,ACCPET,evlist[i]);
            eventLists.push_back(e);
        }
        else if (evlist[i].events & EPOLLOUT)
        {
            std::cout << "get out" << std::endl;
            // cfd = evlist[i].data.fd;
            // buflen = read(cfd,buf,BUFSIZ-1);
            ep_events e(evlist[i].data.fd,WRITE,evlist[i]);
            eventLists.push_back(e);
        }
        else if (evlist[i].events & EPOLLIN)
        {
            std::cout << "get in" << std::endl;
            ep_events e(evlist[i].data.fd,READ,evlist[i]);
            eventLists.push_back(e);
        }
    }
    return 0;
}

int ep::Register(const ep_events& event)
{
        if(event.EventType == DEL)
        {
            std::cout << "reg del" << std::endl;
            int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, event.Fd, NULL);
            if (ret < 0) 
            { 
                perror("epoll_ctl_del");
            }
        }
        else if(event.EventType == WRITE)
        {
            std::cout << "reg write" << std::endl;
            epev.events = EPOLLOUT | EPOLLET | EPOLLIN;
            epev.data.fd = event.Fd;
            int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, event.Fd, &epev);
            if (ret < 0) 
            { 
                perror("epoll_ctl_write");
            }
        }
        else if(event.EventType == READ)
        {
            std::cout << "reg read:" << event.Fd << std::endl;
            epev.events = EPOLLET | EPOLLIN;
            epev.data.fd = event.Fd;
            int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, event.Fd, &epev);
            if (ret < 0) 
            { 
                perror("epoll_ctl_read");
            }
        }
        return 0;
}

int ep::StopEpollWait()
{
    write(exitfd[1],"1",1);
    return 0;
}

int ep::Stop()
{
    close(epfd);
    return 0;
}