/*
 *  @file    InetAddress.h
 *  @author  CodedLong(1552549826@qq.com)
 *  @date    2020-4-6 16:29
 */


#ifndef __INETADDRESS__
#define __INETADDRESS__


#include <netinet/in.h>
#include <string>


class InetAddress
{
public:
	InetAddress(short port);		//IP地址为通配地址，port为指定值

	InetAddress(const char * pIp, short port);		//指定IP地址和端口号

	InetAddress(const struct sockaddr_in & addr);	//传入一个socket地址结构

	const struct sockaddr_in * getSockAddrPtr() const;
	std::string ip(void) const;				//获取该网络地址中的IP地址
	unsigned short port(void) const;		//获取该网络地址中的port

private:
	struct sockaddr_in _addr;
};



#endif
