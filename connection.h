#ifndef CONNECTION_H
#define CONNECTION_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include<dwmapi.h>
#include<windowsx.h>
static bool CreatConnection()
{

QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");//建库
db.setDatabaseName("mymusic.db");
if(!db.open())
{
    return false;
}
QSqlQuery query;
 query.exec(QString("create table LocalMusic (id int,MusicName varchar,FileName varchar,biaoji int,primary key(id,MusicName,FileName))"));//本地音乐列表数据
 query.exec(QString("create table LikeMusic (id int,MusicName varchar,FileName varchar,primary key(id,MusicName,FileName))"));//我喜欢列表数据
 query.exec(QString("create table CollectMusic (id int,MusicName varchar,FileName varchar,primary key(id,MusicName,FileName))"));//播放队列数据
 query.exec(QString("create table WALLPAPER_DATA (FileName varchar primary key)"));//主窗口壁纸数据
 query.exec(QString("create table TRA_DATA (TRA double primary key)"));//主窗口透明度
 query.exec(QString("create table Bizi_DATA (FileName varchar primary key)"));//副窗口壁纸
 query.exec(QString("create table Toumin_DATA (TouMin double primary key)"));//副窗口透明度
return true;
}

#endif // CONNECTION_H
