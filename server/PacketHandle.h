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

    string authorize(char * buf, size_t length);    //接收客户端发送的认证包进行必要的处理
    string query(void);
    void handle_response(char * buf, size_t length);
    string toilet_info(void);  //厕所蹲位信息

private:
    int _command;
};










#endif