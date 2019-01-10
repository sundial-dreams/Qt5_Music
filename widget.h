#ifndef WIDGET_H
#define WIDGET_H
#include<QWidget>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QPixmap>
#include<QPalette>
#include<dwmapi.h>
#include<windowsx.h>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QAction>
#include<QtWinExtras>
#include<QMouseEvent>
#include<QList>
#include<QStringList>
#include<QPaintEvent>
#include<QSqlTableModel>
#include"dialog.h"
#include<QPropertyAnimation>
class QMediaPlayer;
class QMediaPlaylist;
class QMenu;
class QAction;
class QSqlTableModel;
class Dialog;
class Form;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    void updateInfo();//更新文本
    void updatePosition(qint64 position);//更新播放位置
    void updateDuration(qint64 duration);//更新播放进度
    void updatalistwidget_3(int value);//更新listWidget_3
    void updatalistwidget_2(int value);//更新listWidget_2
    void updatalistwidget(int value);//更新listWidget
    void changeVolume(int values);//改变音量
    void pushbuttonstyle();//效果设置  本地音乐按钮显示白色背景
    void pushbuttonstyle_2();//效果设置  我喜欢列表按钮显示白色背景
    void pushbuttonstyle_3();//效果设置  播放队列按钮显示白色背景
    void pushbuttonstyle_4();//效果设置  所有按钮背景都不变白色
    void pushbuttonstyle_5();

    void mouseDoubleClickEvent(QMouseEvent *);//双击切换至极简模式void mousePressEvent(QMouseEvent *event);//拖拽 移动窗口
    void mouseMoveEvent(QMouseEvent *event);//拖拽 移动窗口
    void mouseReleaseEvent(QMouseEvent *event);//拖拽 移动窗口
    void mousePressEvent(QMouseEvent *event);
    void ListItemToolTip();
   inline void init_Connect();
   inline void init_tooltip();
   inline  void init_icon();
   inline void init_action();
   inline  void init_list();
   inline  void init_win();
   inline  void init_else();
   inline QString MenuStyle();
   inline QString PlayStyle();
   inline QString PaseStyle();
   inline QString IlikeStyle();
   inline QString Ilike1Style();
   inline QString ShowListStyle();
   inline QString HideListStyle();
   inline QString RandomStyle();
   inline QString LoopStyle();
   inline QString LoopOneStyle();
   inline QString VoiceStyle();
   inline QString NoVoiceStyle();
   inline QString MusicListStyle();
   inline void ListFocus();
    ~Widget();
private slots:
    void on_pushButton_10_clicked();//跳至本地音乐
    void on_pushButton_11_clicked();//跳至自我喜欢
    void on_pushButton_12_clicked();//跳至播放队列
    void on_pushButton_2_clicked();//播放/暂停
    void on_pushButton_3_clicked();//播放下一曲
    void on_pushButton_4_clicked();//播放上一曲
    void on_pushButton_15_clicked();//隐藏stackedWidget
    void on_pushButton_9_clicked();//播放模式

    void on_listWidget_3_doubleClicked(const QModelIndex &index);//双击播放playlist 本地音乐列表
    void on_listWidget_2_doubleClicked(const QModelIndex &index);//双击播放playlist_2 本地音乐列表
    void on_listWidget_doubleClicked(const QModelIndex &index);//双击播放playlist_3 本地音乐列表
    void on_listWidget_4_doubleClicked(const QModelIndex &index);//双击播放playlist 本地音乐列表

    void action1_slot();//添加菜单  添加至所有音乐
    void action2_slot();//添加菜单  添加至我喜欢
    void action3_slot();//添加菜单  添加至播放队列
    void action4_1_slot();//设置菜单  透明度+5%
    void action4_2_slot();//设置菜单  透明度-5%
    void action5_1_slot();//设置默认壁纸1
    void action5_2_slot();//设置默认壁纸2
    void action5_4_slot();//3
    void action5_3_slot();//设置菜单  设置自定义壁纸
    void action6_slot();//设置  关于
    void action7_slot();//设置菜单  使用
    void action8_slot();//主窗口右键菜单 关闭
    void ClearALL_1_slot();//清除本地音乐
    void ClearALL_2_slot();//清除我喜欢列表
    void ClearALL_3_slot();//清除播放队列
    void ClearALL_4_slot();//清除所有
    void action9_slot();//主窗口右键菜单 播放下一曲
    void action10_slot();//主窗口右键菜单 播放上一曲

    void action11_slot();//暂停
    void action11_1_slot();//播放

    void action12_1_slot();//主窗口右键菜单 顺序播放
    void action12_2_slot();//主窗口右键菜单 随机播放
    void action12_3_slot();//主窗口右键菜单 单曲循环

    void Action1_slot();//listWidget_3右键菜单 播放歌曲
    void Action2_slot();//listWidget_3右键菜单 添加至我喜欢
    void Action3_slot();//listWidget_3右键菜单 删除
    void Action4_slot();//listWidget_3右键菜单 添加至播放队列
    void Action5_slot();//歌曲信息
    void Action7_slot();//多选模式
    void Action8_slot();//单选模式

    void Action1_2_slot();//listWidget_2右键菜单   播放
    void Action2_2_slot();//listWidget_2右键菜单 删除
    void Action3_2_slot();//添加至播放队列
    void Action4_2_slot();//歌曲信息
    void Action6_2_slot();//多选模式
    void Action7_2_slot();//单选模式

    void Action1_3_slot();//listWidget右键菜单 播放
    void Action2_3_slot();//listWidget右键菜单  删除
    void Action3_3_slot();//歌曲信息
    void Action5_3_slot();//多选模式
    void Action6_3_slot();//单选模式

    void Action_slot();//播放
    void Action_1_slot();//添加至我喜欢
    void Action_2_slot();//添加至播放队列
    void Action_3_slot();//删除
    void Action_4_slot();//歌曲信息

    void detila_slot();//歌曲详情
    void on_pushButton_7_clicked();//歌曲定位
    void contextMenuEvent(QContextMenuEvent *);//主窗口右键菜单
    void on_pushButton_17_clicked();//关闭
    void on_pushButton_16_clicked();//最小化
    void on_pushButton_8_clicked();//隐藏verticalSlider
    void on_listWidget_3_customContextMenuRequested(const QPoint &pos);//listWidget_3右键菜单 本地音乐列表
    void on_listWidget_2_customContextMenuRequested(const QPoint &pos);//listWidget_2右键菜单 我喜欢列表
    void on_listWidget_customContextMenuRequested(const QPoint &pos);//listWidget右键菜单  播放队列
    void music_stateChang(QMediaPlayer::State state);//播放状态改变
    void on_pushButton_13_clicked();//极简模式
    void on_pushButton_14_clicked();//添加至我喜欢
    void on_pushButton_18_clicked();//查找歌曲

    void on_listWidget_4_customContextMenuRequested(const QPoint &pos);//listWidget_4 菜单 搜索列表
    void Next_slot();//下一首
    void Pre_slot();//上一首
    void nextlist_slot();//下一个播放列表
    void prelist_slot();//上一个播放列表
    void addV_slot();//增加音量
    void subV_slot();//减少音量
    void Locale_slot();//定位
    void change_slot();//改变播放模式
    void love_slot();//添加至我喜欢
    void Data_slot(int row,int position,QMediaPlaylist *list,QMediaPlayer::State state,QMediaPlaylist::PlaybackMode model,QList<int> Index);//接收数据
    void on_lineEdit_returnPressed();//输入框回车查找
    void PlaylistModel_slot(QMediaPlaylist::PlaybackMode model);//播放模式改变
    void  Key_Space_slot();//播放/暂停
    void Multiselect_slot();//多选

    void on_pushButton_19_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_20_clicked();
    void on_listWidget_5_doubleClicked(const QModelIndex &index);
    void ClearHistory_Slot();
    void on_listWidget_5_customContextMenuRequested(const QPoint &pos);
    void listWidget_5_info();
    void playMusic_slot();
    void clearListWidget_slot();
private:
    void CreateSortCut();//创建快捷键

    Ui::Widget *ui;
    QMediaPlayer *music=NULL;//音乐

    QMediaPlaylist *playlist=NULL;//播放列表1
    QMediaPlaylist *playlist_2=NULL;//播放列表2
    QMediaPlaylist *playlist_3=NULL;//播放列表3
    QMediaPlaylist *playlist_4 = NULL;//历史

    QPixmap pix;//图片
    QPalette pal;//调色板

    QAction *action1;//添加至本地音乐
    QAction *action2;//添加至我喜欢
    QAction *action3;//添加至播放队列
    QAction *add;//增加菜单
    QAction *location;//定位

    QAction *action4;//透明度设置
    QAction *action4_1;//透明度加
    QAction *action4_2;//透明度减
    QAction *action5;//皮肤设置
    QAction *action5_1;//默认皮肤1
    QAction *action5_2;//默认皮肤2
    QAction *action5_4;
    QAction *action5_3;//自定义皮肤
    QAction *action6;//关于
    QAction *action7;//使用介绍
    QAction *action8;//退出
    QAction *ClearALL;//清除菜单
    QAction *ClearALL_1;//清除本地音乐
    QAction *ClearALL_2;//清除我喜欢
    QAction *ClearALL_3;//清除播放队列
    QAction *ClearALL_4;//清除所有
    QAction *ClearHistory;
//右键菜单
    QAction *action9;//下一首
    QAction *action10;//上一首
    QAction *action11;//播放
    QAction *action11_1;//暂停
    QAction *action12;//播放模式
    QAction *action12_1;//顺序播放
    QAction *action12_2;//随机播放
    QAction *action12_3;//单曲循环
    QAction *action13;//退出
    QAction *detila;//歌曲详情
    QMenu *menu;//右键菜单
    QPoint offset;//点
    double transparency;//透明度

    QSqlTableModel *model;//播放列表1模型
    QSqlTableModel *model_2;//播放列表2模型
    QSqlTableModel *model_3;//播放列表3模型

    QList<int> load;//映射
    QStringList labelText1;
    QStringList labelText2;
    Dialog *Music=NULL;//副窗口

    QWinThumbnailToolBar *toolbar;//任务栏工具栏
    QWinThumbnailToolButton *next;//下一首按钮
    QWinThumbnailToolButton *pre;//上一首按钮
    QWinThumbnailToolButton *pause;//播放/暂停按钮
    QWinTaskbarButton *Taskbotton;//任务栏
    QWinTaskbarProgress *TaskProgress;//任务栏进度条
    QVector<QString> currentFileName;
    QVector<int> list1;
    QList<int> map;
    QVector<QString> FilePath;

};

#endif // WIDGET_H
