#include "PacketHandle.h"

#include <iostream>

using namespace std;

//认证包
string PacketHandle::
authorize(void)
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