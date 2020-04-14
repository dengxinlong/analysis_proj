#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
#include "WorkThread.h"

#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char ** argv)
{
    if (argc != 3) {
        cout << "argument is error.\n";
        exit(-1);
    }

    InetAddress servaddr(argv[1], atoi(argv[2]));       //创建一个socket地址结构

    Socket listen_socket;
    listen_socket.ready(servaddr);          //等待客户端的连接

    int nread = 0;
    for ( ; ; ) {
        int peerfd = listen_socket.accept();    //从以连接队列中取出已经完成连接的连接，建立连接过程由内核完成(三次握手)
        // SocketIO socketIO(peerfd);

        pthread_t pid;           //创建一个线程用于处理与客户端的交互
        ::pthread_create(&pid, NULL, pthread_work, (void *)&peerfd);


        // char buf[1024];
        // int cmd = 0;
        // // cout << "-------------" << endl;
        // while ( (nread = socketIO.readn((void *)&cmd, sizeof(cmd))) > 0) {
        //     // cout << "nread: " << nread << endl;
        //     // cout << "cmd = " << cmd << endl;
        //     cmdhandle.set(cmd);
        //     string ret = cmdhandle.resolve();
        //     // cout << "ret.size: " << ret.size() << endl;
        //     socketIO.writen((void *)ret.c_str(), ret.size());
        //     cmd = 0;
        //     // cout << "--------------------" << endl;
        // }
        // if (nread == 0)
        //     socketIO.shutdownWrite();
        // cout << "end end " << endl;
    }

    ::pthread_exit(NULL);
    return 0;
}