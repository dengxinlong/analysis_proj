#include "PacketHandle.h"
#include "Sqlite.h"

#include <time.h>

#include <iostream>

using namespace std;

//认证包
string PacketHandle::
authorize(char * buf, size_t length, int & ret)
{
    //分析客户端发送的认证包
    char cmd;
    strncpy(&cmd, buf, 1);
    // if (cmd != (char)0x61) {
    //    return string("error");
    // }

    //分析客户端ID号
    int id;
    ret = 1;
    memcpy((char *)&id, buf + 1, 4);
    char sql[1024];
    sprintf(sql, "select * from authorize where mac = %d", id);
    Sqlite userDB;
    userDB.open("userinfo.db");
    if (!userDB.query(sql)) {    //查询网关的ID是否在数据库中
        userDB.close();
        ret = 0;    //认证失败
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
    authorize_packet += (char)0x28;     //后面的指令内容没有添加星期，故报文长度少两个字节
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
    authorize_packet += (char)0x15;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    /*********具体指令内容***************/
    //认证结果
    if (ret)
        authorize_packet += (char)0x31;
    else
        authorize_packet += (char)0x30;
    authorize_packet += (char)0x23;

    //服务器当前时间，没有添加星期
    struct tm ptime;
    time_t now;
    time(&now);
    localtime_r(&now, &ptime);			//获取本地时区的时间
    authorize_packet += to_string(ptime.tm_year + 1900); //四个字节
    if (ptime.tm_mon + 1 < 10)
        authorize_packet += 0x30;
    authorize_packet += to_string(ptime.tm_mon + 1);    //两个字节
    if (ptime.tm_mday < 10)
        authorize_packet += 0x30;
    authorize_packet += to_string(ptime.tm_mday);       //两个字节
    if (ptime.tm_hour < 10)
        authorize_packet += 0x30;
    authorize_packet += to_string(ptime.tm_hour);       //两个字节
    if (ptime.tm_min < 10)
        authorize_packet += 0x30;
    authorize_packet += to_string(ptime.tm_min);        //两个字节
    if (ptime.tm_sec < 10)
        authorize_packet += 0x30;
    authorize_packet += to_string(ptime.tm_sec);        //两个字节

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

string PacketHandle::
query(void)
{
    //服务器端向客户端主动请求数据
    string authorize_packet;

    //拼接包头
    authorize_packet += (char)0xfe;
    authorize_packet += (char)0x5c;
    authorize_packet += (char)0x4b;
    authorize_packet += (char)0x89;

    //报文长度，按照网络字节序进行拼接
    authorize_packet += (char)0x1c;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //消息类型
    authorize_packet += (char)0x65;

    /*************客户端ID，后续可能需要修改**********************/
    //客户端ID
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //具体指令长度，网络字节序
    authorize_packet += (char)0x09;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    /*********具体指令内容***************/

    authorize_packet += (char)0xff;         //请求数据指令

    authorize_packet += (char)0x07;         //请求数据个数

    authorize_packet += (char)0x06;
    authorize_packet += (char)0x0b;
    authorize_packet += (char)0x0c;
    authorize_packet += (char)0x0d;
    authorize_packet += (char)0x0e;
    authorize_packet += (char)0x0f;
    authorize_packet += (char)0x10;

    //包尾
    authorize_packet += (char)0xff;
    authorize_packet += (char)0xff;

    return authorize_packet;
}

void PacketHandle::
handle_response(char * buf, size_t length)  //处理从客户端接收到的响应报文
{
    char cmd;
    int cmd_t = 0;
    memcpy((char *)&cmd_t, buf, 1);
    if (cmd_t == 0x65)
        cout << "-------------It is a response packet------------" << endl;

    RestroomStatus restroomstatus;            //用于存储采集到的数据

    int gatewayId;
    memcpy((char *)&gatewayId, buf + 1, 4);
    restroomstatus.setGatewayId(gatewayId);

    buf = buf + 1 + 4;
    int cmd_length = 0;
    memcpy((char *)&cmd_length, buf, 4);
    cout << "cmd_length: " << cmd_length << endl;
    buf += 4;
    //根据获取的数据按类别进行处理

    while (cmd_length > 0) {
        DataType datatype = get_type(buf);
        cout << "dataType: " << datatype << endl;
        buf += 4;
        cmd_length -= 4;
        string data;
        switch (datatype) {
            case EXTERNAL_IO_TYPE:
                restroomstatus.setIo(getTypeValue(buf));
                break;
            case TEMPERATURE_ONE_TYPE:
                restroomstatus.setTemperature(getTypeValue(buf));
                break;
            case MOISTURE_ONE_TYPE:
                restroomstatus.setMoisture(getTypeValue(buf));
                break;
            case HS_CONCENTRATION_ONE_TYPE:
                restroomstatus.setHsConcentration(getTypeValue(buf));
                break;
            case AMMONIA_CONCENTRATION_ONE_TYPE:
                restroomstatus.setAmmoniaConcentration(getTypeValue(buf));
                break;
            case VOC_CONCENTRATION_ONE_TYPE:
                restroomstatus.setVocConcentration(getTypeValue(buf));
                break;
            default:
                break;
        }
        buf = buf + 1 + data.size();
        cmd_length = cmd_length - 1 - data.size();
    }

    storeRestroomStatus(restroomstatus);    //存储数据库失败
}

void PacketHandle::
printData(string data)
{
    cout << "data.size: " << data.size() << endl;

}

DataType PacketHandle::
get_type(char * buf)
{
    int datatype = 0;
    ::memcpy((void *)&datatype, buf, 1);
    return DataType(datatype);
}

string PacketHandle::
getTypeValue(char * buf)
{
    int dataLength = 0;
    ::memcpy((void *)&dataLength, buf, 1);
    cout << "dataLength: " << dataLength << endl;
    buf += 1;
    string databuf;
    for (int i = 0; i < dataLength; i++) {
        databuf += (char)buf[i];
    }

    return databuf;
}

void PacketHandle::
storeRestroomStatus(RestroomStatus & restroomStatus)
{
    char sql[1024];
    sprintf(sql, "insert into userData (gatewayID, IO, temperature, moisture, HsConcentration, AmmoniaConcentration) " \
                 "values (%d, '%s', '%s', '%s', '%s', '%s');", \
                 restroomStatus.getGatewayId(),  \
                 restroomStatus.getIo().c_str(), \
                 restroomStatus.getTemperature().c_str(), \
                 restroomStatus.getMoisture().c_str(), \
                 restroomStatus.getHsConcentration().c_str(), \
                 restroomStatus.getAmmoniaConcentration().c_str());

    Sqlite userDB;
    userDB.open("userinfo.db");
    userDB.insert(sql);
    userDB.close();
//     INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)
// VALUES (1, 'Paul', 32, 'California', 20000.00 );
}

// //厕所蹲位信息包
// string PacketHandle::
// toilet_info(void)
// {
//     string toilet_info_pac;

//     //拼接包头
//     toilet_info_pac += (char)0xfe;
//     toilet_info_pac += (char)0x5c;
//     toilet_info_pac += (char)0x4b;
//     toilet_info_pac += (char)0x89;

//     //报文长度，网络字节序
//     toilet_info_pac += (char)0x20;
//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;

//     //报文类型
//     toilet_info_pac += (char)0x65;

//     //客户端ID
//     toilet_info_pac += (char)0x01;
//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;

//     //具体指令长度，网络字节序
//     toilet_info_pac += (char)0x0d;
//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;

//     //具体指令内容
//     toilet_info_pac += (char)0x06;
//     toilet_info_pac += (char)0xff;
//     toilet_info_pac += (char)0xff;
//     toilet_info_pac += (char)0xff;

//     toilet_info_pac += (char)0x08;
//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;

//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;
//     toilet_info_pac += (char)0x00;

//     toilet_info_pac += (char)0x00;
//     // printf("%d", toilet_info_pac.c_str()[18]);
//     // cout << hex << (int)(toilet_info_pac.c_str()[17]) << endl;
//     // if (toilet_info_pac.c_str()[18] == (char)0xff)
//     //     cout << "good" << endl;

//     // char words[] = "hello, world";
//     // cout << words[3] << endl;

//     //包尾
//     toilet_info_pac += (char)0xff;
//     toilet_info_pac += (char)0xff;

//     return toilet_info_pac;
// }