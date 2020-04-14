 ///
 /// @file    Socket.cc
 /// @author  CodedLong(1552549826@qq.com)
 /// @date    2020-04-06 16:55
 ///

#include "Socket.h"
#include "InetAddress.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


Socket::
Socket(int sockfd)
: _sockfd(sockfd)
{}

Socket::
Socket()
{
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == _sockfd) {
		perror("socket error");
	}

}

Socket::
~Socket()
{
	::close(_sockfd);
}

void Socket::
connect(const InetAddress & addr)
{
	if (::connect(_sockfd, (struct sockaddr *)addr.getSockAddrPtr(), sizeof(InetAddress)) == -1) {
		perror("connect error");
		exit(EXIT_FAILURE);
	}
}

void Socket::
setReuseAddr(bool flag)
{
	int on = (flag ? 1 : 0);
	if(::setsockopt(_sockfd,
					SOL_SOCKET,
					SO_REUSEADDR,
	 				&on,
	 				static_cast<socklen_t>(sizeof(on))) == -1) {
		perror("setsockopt reuseaddr error");
		::close(_sockfd);
		exit(EXIT_FAILURE);
	}
}

void Socket::
setReusePort(bool flag)
{
#ifdef SO_REUSEPORT
	int on = (flag ? 1 : 0);
	if(::setsockopt(_sockfd,
				    SOL_SOCKET,
					SO_REUSEPORT,
					&on,
					static_cast<socklen_t>(sizeof(on))) == -1)
	{
		perror("setsockopt reuseport error");
		::close(_sockfd);
		exit(EXIT_FAILURE);
	}
#else
	if(flag) {
		fprintf(stderr, "SO_REUSEPORT is not supported!\n");
	}
#endif
}

void Socket::
shutdownWrite()
{
	if(::shutdown(_sockfd, SHUT_WR) == -1) {
		perror("shutdown write error");
		//exit(EXIT_FAILURE);//若peer端已关闭，会导致server端崩溃
	}
}

InetAddress Socket::
getLocalAddr(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(sockaddr_in);
	if(::getsockname(sockfd, (struct sockaddr *)&addr, &len) == -1) {
		perror("getsockname error");
	}
	return InetAddress(addr);
}

InetAddress Socket::
getPeerAddr(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(sockaddr_in);
	if(::getpeername(sockfd, (struct sockaddr *)&addr, &len) == -1) {
		perror("getpeername error");
	}
	return InetAddress(addr);
}

