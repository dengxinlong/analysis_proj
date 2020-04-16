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
    string authorize_pac = packet.send_authorize();   //生成认证包
    socketIO.writen((void *)authorize_pac.c_str(), authorize_pac.size());  //发送认证报文

    //接收从服务端发送过来的认证结果
    char buf[1024];
    int nread = socketIO.readn((void *)buf, 4); //先读取包头
    cout << "----------------" << endl;

    int length = 0;
    socketIO.readn((void *)&length, sizeof(length)); //再读取包的大小值
    cout << "length: " << length << endl;

    char * left_buf = new char[length - 4 - 4]{0};
    nread = socketIO.readn((void *)left_buf, (length - 4 - 4));   //读取认证报文中的剩余部分
    cout << "nread: " << nread << endl;
    authorize_pac = packet.recv_authorize(left_buf, nread);

    //接收从服务端发送过来的请求包
    socketIO.readn((void *)buf, 4);
    socketIO.readn((void *)&length, sizeof(length));
    // cout << "query length: " << length << endl;
    delete [] left_buf;
    left_buf = new char[length - 4 - sizeof(length)]{0};
    nread = socketIO.readn((void *)left_buf, (length - 4 -sizeof(length)));
    packet.recv_query(left_buf, nread);
    //可以根据packet.recv_query()返回的类型判断需要发送什么响应报文
    string response = packet.generate_response();
    socketIO.writen((void *)response.c_str(), response.size()); //发送响应报文




















    /********************************************************/
    memset(buf, 0, sizeof(buf));
    length = 0;
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
        cout << "====================" << endl;
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