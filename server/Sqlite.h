#ifndef __MYSQLITE__
#define __MYSQLITE__

#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sqlite3.h>

class Sqlite
{
public:
    bool open(const char * filename)
    {
        return ::sqlite3_open(filename, &_db) == 0 ? true : false;
    }

    bool query(const char * sql);

    bool insert(const char * sql);

    void close(void) { ::sqlite3_close(_db);  }

private:
    sqlite3 * _db;
    char * _zErrMsg;
};







#endif