#ifndef SINGELDB_H
#define SINGELDB_H
#include "sqlite3.h"
#include <iostream>
using namespace std;

class SingelDB
{
public:
    ~SingelDB();
    //外部公共接口 获取model对象
    static SingelDB *getInstance();   
    //static void releaseInstence();
    //数据库执行
    int dosql(char *sql,char **&result,int &row, int &col);
    //打开数据库
    void openDataBase(const char *dbPath);
    //关闭数据库
    void closeDataBase();


private:
    SingelDB();//构造私有化
    static SingelDB *myDB;//静态私成员变量
    sqlite3 *sqldb;
    char *errmsg;  //用来存储错误信息字符串


};

#endif // SINGELDB_H
