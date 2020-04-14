#ifndef __PACKETHANDLE__
#define __PACKETHANDLE__

#include <string>

using namespace std;

class PacketHandle
{
public:
    PacketHandle(void) :_command(0) {}

    void set(int command) {  _command = command; }

    string authorize(void);    //构造认证包
    string toilet_info(void);  //厕所蹲位信息

private:
    int _command;
};










#endif