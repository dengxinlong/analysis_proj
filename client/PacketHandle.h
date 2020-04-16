#ifndef __PACKETHANDLE__
#define __PACKETHANDLE__

#include <string.h>

#include <string>

using namespace std;

class PacketHandle
{
public:
    PacketHandle(void) :_command(0) {}

    void set(int command) {  _command = command; }

    string send_authorize(void);    //构造认证包
    string recv_authorize(char * buf, size_t length);        //接收并处理服务器端发送的认证包
    string recv_query(char * buf, size_t length);
    string generate_response(void);
    string toilet_info(void);  //厕所蹲位信息

private:
    int _command;
};










#endif