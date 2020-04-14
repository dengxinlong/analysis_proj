#include "PacketHandle.h"
#include "Sqlite.h"

#include <time.h>

#include <iostream>

using namespace std;

//认证包
string PacketHandle::
authorize(char * buf, size_t length)
{
    //分析客户端发送的认证包
    char cmd;
    strncpy(&cmd, buf, 1);
    if (cmd != (char)0x61) {
       return string("error");
    }

    //分析客户端ID号
    int id;
    memcpy((char *)&id, buf + 1, 4);
    char sql[1024];
    sprintf(sql, "select * from authorize where mac = %d", id);
    Sqlite userDB;
    userDB.open("userinfo.db");
    if (!userDB.query(sql)) {    //查询网关的ID是否在数据库中
        userDB.close();
        return string("error");
    }

    /*************************************************************/
    /*******对buf后面数据的处理，为指令的长度和指令的具体内容*********/
    /*************************************************************/
    // cout << id << " is in sqlite" << endl;

    //网关的ID在数据库中，发送认证回传包给客户端
    string authorize_packet;

    //拼接包头
    authorize_packet += (char)0xfe;
    authorize_packet += (char)0x5c;
    authorize_packet += (char)0x4b;
    authorize_packet += (char)0x89;

    //报文长度，按照网络字节序进行拼接
    authorize_packet += (char)0x2a;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //消息类型
    authorize_packet += (char)0x62;

    /*************客户端ID，后续可能需要修改**********************/
    //客户端ID
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //具体指令长度，网络字节序
    authorize_packet += (char)0x17;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    /*********具体指令内容***************/
    //认证结果
    authorize_packet += (char)0x31;

    authorize_packet += (char)0x23;

    //服务器当前时间
    struct tm ptime;
    time_t now;
    time(&now);
    localtime_r(&now, &ptime);			//获取本地时区的时间
    authorize_packet += to_string(ptime.tm_year + 1900);
    if (ptime.tm_mon + 1 < 10)
        authorize_packet += 0x30;
    authorize_packet += to_string(ptime.tm_mon + 1);
    if (ptime.tm_mday < 10)
        authorize_packet += 0x30;
    authorize_packet += to_string(ptime.tm_mday);
    if (ptime.tm_hour < 10)
        authorize_packet += 0x30;
    authorize_packet += to_string(ptime.tm_hour);
    if (ptime.tm_min < 10)
        authorize_packet += 0x30;
    authorize_packet += to_string(ptime.tm_min);
    if (ptime.tm_sec < 10)
        authorize_packet += 0x30;
    authorize_packet += to_string(ptime.tm_sec);

    authorize_packet += 0x23;

    //心跳时间
    authorize_packet += 0x30;
    authorize_packet += 0x35;
    authorize_packet += 0x30;

    authorize_packet += 0x23;

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