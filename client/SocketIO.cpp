 ///
 /// @file    SocketIO.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2015-11-05 16:14:19
 ///

#include "SocketIO.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <iostream>

using namespace std;


SocketIO::
SocketIO(int sockfd)
: _sockfd(sockfd)
{}

size_t SocketIO::
send(const void * buf, size_t len, int flags)
{
	int ret;
	if ( (ret = ::send(_sockfd, buf, len, flags)) == -1) {
		perror("send is fail.");
		exit(-1);
	}

	return ret;
}


size_t SocketIO::
readn(void * buf, size_t count)
{
	size_t nleft = count;
	char * pbuf = (char *)buf;
	while(nleft > 0)
	{
		int nread = ::read(_sockfd, pbuf, nleft);
		if(-1 == nread)
		{
			if(errno == EINTR)
				continue;
			return EXIT_FAILURE;
		}
		else if(0 == nread) //EOF
		{
			break;
		}
		pbuf += nread;
		nleft -= nread;
	}
	return (count - nleft);
}


size_t SocketIO::
writen(const void * buf, size_t count)
{
	size_t nleft = count;
	const char * pbuf = (const char * )buf;
	while(nleft > 0)
	{
		int nwrite = ::write(_sockfd, pbuf, nleft);
		// cout << "nwrite: " << nwrite << endl;
		if(nwrite <= 0)
		{
			if(nwrite < 0 && errno == EINTR)
				nwrite = 0;
			else
				return EXIT_FAILURE;
		}
		nleft -= nwrite;
		pbuf += nwrite;
	}
	return (count - nleft);
}

size_t SocketIO::
recv_peek(void * buf, size_t count)
{
	int nread;
	do
	{
		nread = ::recv(_sockfd, buf, count, MSG_PEEK);
	}while(nread == -1 && errno == EINTR);
	return nread;
}

size_t SocketIO::
readline(void * buf, size_t maxlen)
{
	size_t nleft = maxlen - 1;
	char * pbuf = (char *)buf;
	size_t total = 0;
	while(nleft > 0)
	{
		int nread = recv_peek(pbuf, nleft);
		if(nread <= 0)
			return nread;


		for(size_t idx = 0; idx != nread; ++idx)
		{
			if(pbuf[idx] == '\n')
			{
				size_t nsize = idx + 1;
				if(readn(pbuf, nsize) != nsize)
					return EXIT_FAILURE;
				pbuf += nsize;
				total += nsize;
				*pbuf = 0;
				return total;
			}
		}
		if(readn(pbuf, nread) != nread)
			return EXIT_FAILURE;
		pbuf += nread;
		nleft -= nread;
		total += nread;
	}
	*pbuf = 0;
}

void SocketIO::
shutdownWrite(void)
{
	// cout << "shutdownWrite" << endl;
	if(::shutdown(_sockfd, SHUT_WR) == -1) {
		perror("shutdown write error");
		//exit(EXIT_FAILURE);//若peer端已关闭，会导致server端崩溃
	}
}

