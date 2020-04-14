#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

using namespace std;

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


    //分析客户端发送的认证包

    //分析客户端ID号
    int id = 65537;
    char * ptr = (char *)&id;
    cout << "-----------" << endl;
    cout << (char)*(ptr + 1) << endl;

    struct tm p;
    tm ptur;
    time_t Nowt;
    time(&Nowt);
    localtime_r(&Nowt, &p);			//获取本地时区的时间
	printf("1970到目前经历的秒数通过localtime转换成struct tm结构体时间：\n");
	printf("%d年%d月%d日%d时%d分%d秒\n",p.tm_year+1900,p.tm_mon+1,p.tm_mday,p.tm_hour,p.tm_min,p.tm_sec);		//1900年为基准，月份是0-11月
    string str_time;
    char buf[10];
    sprintf(buf, "%d%d%d", p.tm_year + 1900, p.tm_mon + 1, p.tm_mday);
    cout << "buf: " << buf << endl;
    cout << strlen(str_time.c_str()) << endl;
    cout << str_time << endl;
    cout << p.tm_hour << endl;
    string hour = to_string(p.tm_year + 1900);
    cout << strlen(hour.c_str()) << endl;
    // char hour = p.tm_hour;
    cout << hour << endl;
    // cout << sizeof()
    //网关的ID在数据库中，发送认证回传包给客户端
    string authorize_packet;

    //拼接包头
    authorize_packet += (char)0xfe;
    authorize_packet += (char)0x5c;
    authorize_packet += (char)0x4b;
    authorize_packet += (char)0x89;

    //报文长度，按照网络字节序进行拼接
    authorize_packet += (char)0x2a;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //消息类型
    authorize_packet += (char)0x62;

    //客户端ID
    authorize_packet += (char)0x01;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //具体指令长度，网络字节序
    authorize_packet += (char)0x01;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;
    authorize_packet += (char)0x00;

    //具体指令内容
    authorize_packet += (char)0x00;

    //包尾
    authorize_packet += (char)0xff;
    authorize_packet += (char)0xff;

    return 0;
}