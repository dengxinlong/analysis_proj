#ifndef __RESROOMSTATUS__
#define __RESROOMSTATUS__

#include <string>
#include <iostream>

using namespace std;

class RestroomStatus
{
public:
    RestroomStatus()
    : _id(0)
    , _gatewayId(0)
    , _timestamp(0)
    { }

    long getId()    {   return _id; }

    void setId(long id)    {  _id = id;  }

    string getDateTime()    {   return _dateTime;   }

    void setDateTime(string dateTime) {
        _dateTime = dateTime;
    }

    string getIo() {
        return _io;
    }

    void setIo(string io) {
        _io = io;
    }

    void setPassengerFlow(string passengerFlow) {
        _passengerFlow = passengerFlow;
    }

    string getPassengerFlow(void) {
        return _passengerFlow;
    }

    string getSubEntityId() {
        return _subEntityId;
    }

    void setSubEntityId(string subEntityId) {
        _subEntityId = subEntityId;
    }

    string getTemperature() {
        return _temperature;
    }

    void setTemperature(string temperature) {
        _temperature = temperature;
    }

    string getMoisture() {
        return _moisture;
    }

    void setMoisture(string moisture) {
        _moisture = moisture;
    }

    string getHsConcentration() {
        return _hsConcentration;
    }

    void setHsConcentration(string hsConcentration) {
        _hsConcentration = hsConcentration;
    }

    string getAmmoniaConcentration() {
        return _ammoniaConcentration;
    }

    void setAmmoniaConcentration(string ammoniaConcentration) {
        _ammoniaConcentration = ammoniaConcentration;
    }

    string getVocConcentration() {
        return _vocConcentration;
    }

    void setVocConcentration(string vocConcentration) {
        _vocConcentration = vocConcentration;
    }

    int getGatewayId() {
        return _gatewayId;
    }

    void setGatewayId(int gatewayId) {
        _gatewayId = gatewayId;
    }

    long getTimestamp() {
        return _timestamp;
    }

    void setTimestamp(long timestamp) {
        _timestamp = timestamp;
    }

private:
    long _id;

    int _gatewayId;
    string _dateTime;
    long _timestamp;

    string _passengerFlow;

    string _subEntityId;
    string _io;
    string _temperature;
    string _moisture;
    string _hsConcentration;
    string _ammoniaConcentration;
    string _vocConcentration;
};







#endif