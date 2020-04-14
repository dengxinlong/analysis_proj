/*
 *  @file    Socket.h
 *  @author  CodedLong(1552549826@qq.com)
 *  @date    2020-4-6 16:29
 */

#ifndef __SOCKET__
#define __SOCKET__

#include "Noncopyable.h"

class InetAddress;				//声明InetAddress类

class Socket
: Noncopyable
{
public:
	Socket(int sockfd);
	Socket();
	~Socket();

	void connect(const InetAddress & addr);

	void shutdownWrite();
	int fd(){	return _sockfd;	}

	static InetAddress getLocalAddr(int sockfd);
	static InetAddress getPeerAddr(int sockfd);

private:
	void setReuseAddr(bool flag);
	void setReusePort(bool flag);
private:
	int _sockfd;
};


#endif
