#include "singeldb.h"

SingelDB *SingelDB::myDB=nullptr;
//单例打开数据库路径
SingelDB::SingelDB()
{
    this->openDataBase("../data/video");
}
//外部公共接口 获取单例对象
SingelDB *SingelDB::getInstance()
{
    if(SingelDB::myDB==nullptr)
    {
        SingelDB::myDB=new SingelDB();
    }

    return SingelDB::myDB;

}
//数据库执行
int SingelDB::dosql(char *sql, char **&result, int &row, int &col)
{
    int res =sqlite3_get_table(sqldb, sql, &result, &row, &col, &errmsg);
    if(res!=SQLITE_OK)
    {
        cout<<sqlite3_errmsg(sqldb)<<endl;
        return res;
    }
    return 0;

}
//打开数据库
void SingelDB::openDataBase(const char *dbPath)
{
    int res = sqlite3_open(dbPath, &sqldb);
    if(res != SQLITE_OK)
    {
        cout<<sqlite3_errmsg(sqldb)<<endl;
        cout<<sqlite3_errcode(sqldb)<<endl;
    }


}
//关闭数据库
void SingelDB::closeDataBase()
{
    int res = sqlite3_close(sqldb);
    if(res != SQLITE_OK)
    {
        cout<<sqlite3_errmsg(sqldb)<<endl;
        cout<<sqlite3_errcode (sqldb) <<endl;
    }

}

