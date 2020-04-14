 ///
 /// @file    Noncopyable.h
 /// @author  CodeLong(1552549826@qq.com)
 /// @date    2020-4-6 16:49
 ///


#ifndef __NONCOPYABLE__
#define __NONCOPYABLE__


class Noncopyable
{
protected:
	Noncopyable(){}
private:
	Noncopyable(const Noncopyable & rhs);
	Noncopyable & operator=(const Noncopyable & rhs);
};


#endif
