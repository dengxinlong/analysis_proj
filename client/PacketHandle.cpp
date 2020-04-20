#include "PacketHandle.h"

#include <iostream>

using namespace std;

//认证包
string PacketHandle::
send_authorize(void)
{
    string authorize_packet;

    //拼接包头
    authorize_packet += (char)0xfe;
    authorize_packet += (char)0x5c;
    authorize_packet += (char)0x4b;
    authorize_packet += (char)0x89;

    //报文长度，按照网络字节序进行拼接
    authorize_packet += (char)0x14;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //消息类型
    authorize_packet += (char)0x61;

    //客户端ID
    authorize_packet += (char)0x01;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x01;
    authorize_packet += (char)0x00;

    //具体指令长度，网络字节序
    authorize_packet += (char)0x01;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //具体指令内容
    authorize_packet += (char)0x00;

    //包尾
    authorize_packet += (char)0xff;
    authorize_packet += (char)0xff;

    return authorize_packet;
}

string PacketHandle::
recv_authorize(char * buf, size_t length)
{
    //接收服务器端发送的消息类型
    char cmd;
    strncpy(&cmd, buf, 1);
    // if (cmd == (char)0x62)
    //     cout << "good" << endl;

    buf = buf + 1 + 4;   //此时buf指向具体指令长度字段

    int cmd_length = 0;
    memcpy((char *)&cmd_length, buf, 4);
    cout << "cmd_length: " << cmd_length << endl;

    buf += 4;
    char ret = 0;
    memcpy(&ret, buf, 1);
    //处理认证的结果..............
    cout << "authorize ret: " << ret << endl;

    //后面的处理表示认证通过
    buf += 1;
    buf += 1;

    //处理服务端发送过来的时间.............这里只是向标准输出输出这些时间
    char date[512] = {0};
    memcpy(date, buf, 14);
    cout << "date: " << date << endl;

    buf += 14;
    buf += 1;

    //处理心跳时间..............这里打印出来
    char heartbeat[4] = {0};
    memcpy(heartbeat, buf, 3);
    cout << "heartbeat: " << heartbeat << endl;

    return string("success");
}

string PacketHandle::
recv_query(char * buf, size_t length)
{
    //接收到请求，处理请求
    //接收服务器端发送的消息类型
    char cmd;
    strncpy(&cmd, buf, 1);
    if (cmd == (char)0x65)
        cout << "-------------It is a query packet------------" << endl;
    //后续的请求处理

    return string("success");
}

string PacketHandle::
generate_response(void)
{
    //服务器端向客户端主动请求数据
    string authorize_packet;

    //拼接包头
    authorize_packet += (char)0xfe;
    authorize_packet += (char)0x5c;
    authorize_packet += (char)0x4b;
    authorize_packet += (char)0x89;

    //报文长度，网络字节序
    authorize_packet += (char)0x32;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //报文类型
    authorize_packet += (char)0x65;

    //客户端ID
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //具体指令长度，网络字节序
    authorize_packet += (char)0x1f;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //具体指令内容
    authorize_packet += (char)0x02;  //一种消息类型
    authorize_packet += (char)0x00;
    authorize_packet += (char)0xff;
    authorize_packet += (char)0xff;
    authorize_packet += (char)0x06;
    authorize_packet += (char)0x30;
    authorize_packet += (char)0x20;
    authorize_packet += (char)0x20;
    authorize_packet += (char)0x20;
    authorize_packet += (char)0x20;
    authorize_packet += (char)0x20;

    authorize_packet += (char)0x0b;   //另一种消息类型  04 -> 0b
    authorize_packet += (char)0x00;
    authorize_packet += (char)0xff;
    authorize_packet += (char)0xff;
    authorize_packet += (char)0x06;
    authorize_packet += (char)0x30;
    authorize_packet += (char)0x20;
    authorize_packet += (char)0x20;
    authorize_packet += (char)0x20;
    authorize_packet += (char)0x20;
    authorize_packet += (char)0x20;

    authorize_packet += (char)0x06;   //另一种消息类型
    authorize_packet += (char)0x00;
    authorize_packet += (char)0xff;
    authorize_packet += (char)0xff;
    authorize_packet += (char)0x04;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    // printf("%d", authorize_packet.c_str()[18]);
    // cout << hex << (int)(authorize_packet.c_str()[17]) << endl;
    // if (authorize_packet.c_str()[18] == (char)0xff)
    //     cout << "good" << endl;

    // char words[] = "hello, world";
    // cout << words[3] << endl;

    //包尾
    authorize_packet += (char)0xff;
    authorize_packet += (char)0xff;

    return authorize_packet;
}

//厕所蹲位信息包
string PacketHandle::
toilet_info(void)
{
    string toilet_info_pac;

    //拼接包头
    toilet_info_pac += (char)0xfe;
    toilet_info_pac += (char)0x5c;
    toilet_info_pac += (char)0x4b;
    toilet_info_pac += (char)0x89;

    //报文长度，网络字节序
    toilet_info_pac += (char)0x20;
    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;

    //报文类型
    toilet_info_pac += (char)0x65;

    //客户端ID
    toilet_info_pac += (char)0x01;
    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;

    //具体指令长度，网络字节序
    toilet_info_pac += (char)0x0d;
    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;

    //具体指令内容
    toilet_info_pac += (char)0x06;
    toilet_info_pac += (char)0xff;
    toilet_info_pac += (char)0xff;
    toilet_info_pac += (char)0xff;

    toilet_info_pac += (char)0x08;
    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;

    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;
    toilet_info_pac += (char)0x00;

    toilet_info_pac += (char)0x00;
    // printf("%d", toilet_info_pac.c_str()[18]);
    // cout << hex << (int)(toilet_info_pac.c_str()[17]) << endl;
    // if (toilet_info_pac.c_str()[18] == (char)0xff)
    //     cout << "good" << endl;

    // char words[] = "hello, world";
    // cout << words[3] << endl;

    //包尾
    toilet_info_pac += (char)0xff;
    toilet_info_pac += (char)0xff;

    return toilet_info_pac;
}