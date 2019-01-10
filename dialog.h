#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QPoint>
#include<QMouseEvent>
#include<QPixmap>
#include<QPalette>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QAction>
#include<QtWinExtras>
#include<QAction>
#include"widget.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
void mousePressEvent(QMouseEvent *event);//拖动窗体
void mouseMoveEvent(QMouseEvent *event);//拖动窗体
void mouseReleaseEvent(QMouseEvent *event);//拖动窗体
void mouseDoubleClickEvent(QMouseEvent *);//双击返回主窗口
void contextMenuEvent(QContextMenuEvent *);//右键菜单栏
void setPlaylist(QMediaPlaylist *list,int row,int position,int volume,QMediaPlayer::State state,QMediaPlaylist::PlaybackMode playmodel,int i);//设置数据
void updateText();//更新文本
void updatePosition(qint64 position);//更新位置
void updateDuration(qint64 duration);//更新状态
void stateChange(QMediaPlayer::State state);//状态改变
void PlaybackModel_slot(QMediaPlaylist::PlaybackMode model);//播放模式改变
signals:
void Data(int row,int position,QMediaPlaylist *list,QMediaPlayer::State state,QMediaPlaylist::PlaybackMode model,QList<int> Index);//发出数据
private slots:
    void on_pushButton_4_clicked();//退出


    void on_pushButton_5_clicked();//最小化

    void on_pushButton_2_clicked();//播放/暂停

    void on_pushButton_3_clicked();//下一曲

    void on_pushButton_clicked();//上一曲
    void play_slot();//播放
    void pause_slot();//暂停
    void next_slot();//下一首
    void pre_slot();//上一首
    void action1_slot();//默认皮肤1
    void action2_slot();//默认皮肤2
    void action3_slot();//默认皮肤3
    void action4_slot();//自定义皮肤
    void back_slot();
    void Action1_slot();//透明度加
    void Action2_slot();//透明度减
    void quit_slot();//退出
    void on_pushButton_7_clicked();//播放模式
    void UpdateIndex(int value);

private:
    Ui::Dialog *ui;
    QPoint offset;//点击的位置
    QPixmap pix;//图片
    QPalette pal;//调色板
    QAction *play;//播放
    QAction *pause;//暂停
    QAction *next;//下一首
    QAction *pre;//上一首
    QAction *back;//返回
    QAction *action;//设置皮肤
    QAction *action1;//默认皮肤1
    QAction *action2;//默认皮肤2
    QAction *action3;//默认皮肤3
    QAction *action4;//自定义皮肤
    QAction *Action;//设置透明度
    QAction *Action1;//透明度加
    QAction *Action2;//透明度减
    QAction *quit;//退出
    QMenu *menu;//右键菜单
    QMediaPlayer *music;//音乐
    QMediaPlaylist *playlist;//播放列表
    double TouMin;//透明度
//任务栏
    QWinThumbnailToolBar *toolbar;//任务栏工具栏
    QWinThumbnailToolButton *next1;//下一首
    QWinThumbnailToolButton *pre1;//上一首
    QWinThumbnailToolButton *pause1;//播放/暂停
    QWinTaskbarButton *Taskbotton;//任务栏
    QWinTaskbarProgress *TaskProgress;//任务栏进度条
    QString currentFile;
    QList<int> Index;
    bool flag = false;
};

#endif // DIALOG_H
