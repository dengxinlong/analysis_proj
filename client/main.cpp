#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
#include "PacketHandle.h"
// #include "TcpConnection.h"
// #include "TcpServer.h"

#include <stdlib.h>
#include <string.h>

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

    Socket sockfd;
    sockfd.connect(servaddr);          //连接到服务器端

    SocketIO socketIO(sockfd.fd());     //用于和服务器端通信


    //发送认证包给服务器端，用于登录到服务器，服务器端查询数据库是否允许该客户端登录
    PacketHandle packet;
    string authorize_pac = packet.authorize();   //生成认证包
    socketIO.writen((void *)authorize_pac.c_str(), authorize_pac.size());  //发送认证报文
    //----------------------------------------

    char buf[1024];
    int length = 0;
    int cmd = 0;
    while ( 1 ) {
        // char sendline[1024];
        // snprintf(sendline, sizeof(sendline), "%s%s", buf, "\n");
        // cout << sizeof(sendline) << " " << strlen(sendline) << endl;
        cout << "cmd: "  << cmd << endl;
        socketIO.send((void *)&cmd, sizeof(cmd), 0);
        // socketIO.writen((void *)str.c_str(), strlen(str.c_str()));
        // cout << sendline;

        //先读取包头
        socketIO.readn((void *)buf, 4);
        cout << "----------------" << endl;
        //再读取包的大小值
        socketIO.readn((void *)&length, sizeof(int));
        cout << "length = " << length << endl;
        if (length == 0x00000020)
            cout << "good" << endl;
        length = 0;
        // cout << buf;
    }


    return 0;
}