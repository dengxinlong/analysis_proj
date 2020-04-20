#include "Sqlite.h"

bool Sqlite::
query(const char *sql)
{
    int ret;
    char **presult;
    int row = 0, column = 0;
    ret = ::sqlite3_get_table(_db, sql, &presult, &row, &column, &_zErrMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", _zErrMsg);
        sqlite3_free(_zErrMsg);
    }

    return row != 0 ? true : false;
}

bool Sqlite::
insert(const char * sql)
{
   char *zErrMsg = 0;
   int rc;

   /* Execute SQL statement */
   rc = sqlite3_exec(_db, sql, NULL, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return false;
   }else{
      fprintf(stdout, "Records created successfully\n");
      return true;
   }
}