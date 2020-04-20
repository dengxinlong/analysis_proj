#ifndef __PACKETHANDLE__
#define __PACKETHANDLE__

#include "ResroomStatus.h"

#include <string.h>

#include <string>

using namespace std;

typedef enum DataType {
    EXTERNAL_IO_TYPE = 6,
    PASSENGER_FLOW_VALOUM = 2,
    TEMPERATURE_ONE_TYPE = 11,
    MOISTURE_ONE_TYPE = 12,
    HS_CONCENTRATION_ONE_TYPE = 13,
    AMMONIA_CONCENTRATION_ONE_TYPE = 14,
    VOC_CONCENTRATION_ONE_TYPE = 15,
    TEMPERATURE_TWO_TYPE = 16,
    MOISTURE_TWO_TYPE = 17,
    HS_CONCENTRATION_TWO_TYPE = 18,
    AMMONIA_CONCENTRATION_TWO_TYPE = 19,
    VOC_CONCENTRATION_TWO_TYPE = 20
}DataType;

class PacketHandle
{
public:
    PacketHandle(void) :_command(0) {}

    void set(int command) {  _command = command; }

    string authorize(char * buf, size_t length, int & ret);    //接收客户端发送的认证包进行必要的处理
    string query(void);
    void handle_response(char * buf, size_t length);
    // string toilet_info(void);  //厕所蹲位信息

private:
    DataType get_type(char * buf);
    string getIOValue(char * buf, int length);
    string getTypeValue(char * buf);
    void printData(string data);
    void storeRestroomStatus(RestroomStatus & restroomStatus);

private:
    int _command;
};










#endif