/*
 *  @file    SocketIO.h
 *  @author  CodedLong(1552549826@qq.com)
 *  @date    2020-4-6 16:29
 */
#ifndef __SOCKETIO__
#define __SOCKETIO__
#include <stdio.h>


class SocketIO
{
public:
	SocketIO(int sockfd);

	size_t send(const void * buf, size_t len, int flags);
	size_t readn(void * buf, size_t count);
	size_t writen(const void * buf, size_t count);
	size_t readline(void * buf, size_t max_len);

private:
	size_t recv_peek(void * buf, size_t count);

private:
	int _sockfd;
};




#endif

