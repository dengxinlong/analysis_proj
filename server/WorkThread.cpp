/*
 *  @file    WorkThread.cpp
 *  @author  CodedLong(1552549826@qq.com)
 *  @date    2020-4-12 16:29
 */

#include "WorkThread.h"
#include "PacketHandle.h"

void *pthread_work(void *ptr)
{
    //  sockfd = *(SocketIO *)ptr;
    SocketIO socketIO(*(int *)ptr);
    char buf[1024];
    int nread = 0;
    int length = 0;      //报文长度
    PacketHandle packet; //服务器发送给客户端的报文

    //读取客户端发送的认证包
    socketIO.readn((void *)buf, 4); //先读取包头
    cout << "----------------" << endl;
    socketIO.readn((void *)&length, sizeof(int)); //再读取包的大小值
    cout << "length: " << length << endl;
    char * left_buf = new char[length - 4 - 4];
    nread = socketIO.readn((void *)left_buf, sizeof(length - 4 - 4));   //读取认证报文中的剩余部分
    packet.authorize(left_buf, nread);

    while (1) ;
    // int cmd;
    // while ((nread = socketIO.readn((void *)&cmd, sizeof(cmd))) > 0) {
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

    return NULL;
}