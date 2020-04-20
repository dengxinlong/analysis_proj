#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include <sys/time.h>
#include <signal.h>

using namespace std;

void sig_handler(int signo);
void *pthread_work(void * ptr);

// class Test
// {
// public:
//     Test(int value) : _value(value) {}
//     ~Test()
//     {
//         ::pthread_exit(NULL);
//     }

//     void pthread_create(void)
//     {
//         ::pthread_create(&_pid, NULL, this->fac, NULL);
//     }


//     static void * fac(void * ptr)
//     {
//         cout << "hello, world.\n";
//         return NULL;
//     }

// private:
//     int _value;
//     pthread_t _pid;
// };

// void * fac(void * ptr)
// {
//     int value = (int)ptr;
//     cout << value << " hello, world" << endl;

//     return NULL;
// }

static int callback(void * data, int argc, char ** argv, char ** azColName)
{
    if (argc == 0)
        cout << "emmpty.\n";
    cout << argc << endl;
    cout << "------------" << endl;
    // return 1;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(int argc, char **argv)
{
    // //Open database
    // sqlite3 * db;
    // char * zErrMsg = 0;
    // if ( sqlite3_open("testDB.db", &db) ) {
    //     fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    //     exit(1);
    // }else {
    //     fprintf(stdout, "Opened database successfully.\n");
    // }

    // //Create SQL statement
    // // const char * sql =  "insert into company_t(id, name, age, address, salary)" \
    // //                     "values(1, 'Paul', 32, 'California', 10000);" \
    // //                     "insert into company_t(id, name, age, address, salary)" \
    // //                     "values(2, 'Allen', 22, 'California', 20000);" \
    // //                     "insert into company_t(id, name, age, address, salary)" \
    // //                     "values(3, 'Teddy', 42, 'California', 19000);";
    // const char * sql = "select * from company_t where id = 55";
    // //Execute SQL statement
    // int ret;
    // char ** presult;
    // int row = 0, column = 0;
    // ret = sqlite3_get_table(db, sql, &presult, &row, &column, &zErrMsg);
    // if (ret != SQLITE_OK) {
    //     fprintf(stderr, "SQL error: %s\n", zErrMsg);
    //     sqlite3_free(zErrMsg);
    // }
    // cout << row << endl;
    // if (row == 0)
    //     cout << "Empty.\n";
    // ret = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    // if (ret != SQLITE_OK) {
    //     fprintf(stderr, "SQL error: %s\n", zErrMsg);
    //     sqlite3_free(zErrMsg);
    // }else {
    //     fprintf(stdout, "Tablee created successfully\n");
    // }
    // sqlite3_close(db);


    // //分析客户端发送的认证包

    // string authorize_packet;

    // //拼接包头
    // authorize_packet += (char)0xfe;
    // authorize_packet += (char)0x5c;
    // authorize_packet += (char)0x4b;
    // authorize_packet += (char)0x89;

    // cout << hex << authorize_packet;
    pthread_t pid;
    ::pthread_create(&pid, NULL, pthread_work, NULL);
    cout << "I'm main" << endl;
    ::pthread_create(&pid, NULL, pthread_work, NULL);
    ::pthread_create(&pid, NULL, pthread_work, NULL);

    ::pthread_exit(NULL);


    return 0;
}

void *pthread_work(void * ptr)
{
    // struct timeval interval;
    // struct itimerval timer;
    // interval.tv_sec = 10;
    // interval.tv_usec = 0;

    // timer.it_interval = interval;
    // timer.it_value.tv_sec = 1;
    // timer.it_value.tv_usec = 0;
    // setitimer(ITIMER_REAL, &timer, NULL);

    // signal(SIGALRM, sig_handler);
    // while (1);
    cout << "I'm a child thread.\n";

}

void sig_handler(int signo)
{
    cout << "hello, world" << endl;
}