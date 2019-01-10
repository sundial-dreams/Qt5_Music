#include "widget.h"
#include "ui_widget.h"
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QFileDialog>
#include<QUrl>
#include<QDir>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlTableModel>
#include<QMenu>
#include<dwmapi.h>
#include<windowsx.h>
#include<QPainter>
#include<QScrollBar>
#include<qmath.h>
#include<QShortcut>
#include<QMessageBox>
#include<QProgressBar>
#include<QProgressDialog>
#include"dialog.h"
#include<QGraphicsDropShadowEffect>
#include<QFile>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
    ui->lineEdit->setPlaceholderText(("输入歌手或歌曲"));
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(1,1);
    effect->setColor(QColor(0,0,0,100));
    effect->setBlurRadius(15);
    ui->frame->setGraphicsEffect(effect);
    ui->frame->setAutoFillBackground(true);
    currentFileName.push_back("D:/");
    currentFileName.push_back("D:/");
    currentFileName.push_back("D:/");
    currentFileName.push_back("D:/");
    CreateSortCut();
    init_else();
    init_icon();
    init_list();
    init_tooltip();
    init_win();
    init_action();
    init_Connect();
    ListItemToolTip();

}
 inline void Widget::init_else()
{
    labelText1.push_back("You may only be a person in this world,");
    labelText2.push_back("but for someone,you're the world.");
    labelText1.push_back("May there be enough clouds in your life");
    labelText2.push_back("        to make a beautiful sunset.");
    labelText1.push_back("The best feeling the world is when you");
    labelText2.push_back("        know your heart is smiling.");
    labelText1.push_back("Love begins with a smile,grows with a");
    labelText2.push_back("         kiss and ends with a tear.");
    labelText1.push_back("Life is not lack of beauty,but lack");
    labelText2.push_back("        of the eyes to find beauty.");
    labelText1.push_back("The shortest distance between");
    labelText2.push_back("             two people is a smile.");
    labelText1.push_back("Life is not about waiting for the storm to pass.");
    labelText2.push_back("It's about learning to dance in the rain.");
    labelText1.push_back("In order to be irrepaceable,one");
    labelText2.push_back("          must always be different.");
    labelText1.push_back("The minute you think of giving up,think of");
    labelText2.push_back("the reason why you held on so long.");
    labelText1.push_back("Life is a shipwreck,but we must not");
    labelText2.push_back("   forget to sing in the lifeboats.");
    labelText1.push_back("Give everything a shot.You never know what or");
    labelText2.push_back("who is going to change your life.");
    ui->listWidget->verticalScrollBar()->setCursor(Qt::PointingHandCursor);
    ui->listWidget_2->verticalScrollBar()->setCursor(Qt::PointingHandCursor);
    ui->listWidget_3->verticalScrollBar()->setCursor(Qt::PointingHandCursor);
    ui->listWidget_4->verticalScrollBar()->setCursor(Qt::PointingHandCursor);
    QString listWidgetStyle = "QScrollBar:vertical"
                              "{"
                                      "width:8px;"
                                      "background-color:transparent;"
                                      "margin:0px,0px,0px,0px;"
                                     " padding-top:12px;   /*上预留位置*/"
                                     " padding-bottom:12px;    /*下预留位置*/"
                                  "}"


                                "  QScrollBar::handle:vertical"
                                 " {"
                                      "width:8px;"
                                     " background-color:rgba(255,255,255,0.2);"
                                     " border-radius:4px;"
                                     " min-height:20px;"
                                 " }"


                              "    QScrollBar::handle:vertical:hover"
                               "   {"
                                "      width:9px;"
                                     " background-color:rgba(255,255,255,0.5);"
                                   "   border-radius:4px;"
                                 "     min-height:20;"
                                "  }"

                                "  QScrollBar::add-line:vertical"
                                "  {"
                                     " height:12px;"
                                 "     width:10px;"
                              "        border-image:url(:/selectfile/scroll/3.png);"
                                     " subcontrol-position:bottom;"
                              "    }"

                              "    QScrollBar::sub-line:vertical"
                              "    {"
                              "        height:12px;"
                                      "width:10px;"
                                   "   border-image:url(:/selectfile/scroll/1.png);"
                                      "subcontrol-position:top;"
                               "   }"
                              "    QScrollBar::add-line:vertical:hover"
                               "   {"
                                     " height:12px;"
                                      "width:10px;"
                                     " border-image:url(:/selectfile/scroll/4.png);"
                                      "subcontrol-position:bottom;"
                                 " }"


                                 " QScrollBar::sub-line:vertical:hover"
                                 " {"
                                 "     height:12px;"
                                    "  width:10px;"
                                    "  border-image:url(:/selectfile/scroll/2.png);"
                                     " subcontrol-position:top;"
                                 " }"

                                 " QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                                 " {"
                                     " background-color:transparent;"
                                   "   border-radius:4px;"
                                  "}";
    ui->listWidget_2->verticalScrollBar()->setStyleSheet(listWidgetStyle);
    ui->listWidget_3->verticalScrollBar()->setStyleSheet(listWidgetStyle);
    ui->listWidget->verticalScrollBar()->setStyleSheet(listWidgetStyle);
    ui->listWidget_4->verticalScrollBar()->setStyleSheet(listWidgetStyle);
    ui->listWidget_5->verticalScrollBar()->setStyleSheet(listWidgetStyle);
    Music=new Dialog();//小播放器
    Music->setWindowFlags(Qt::FramelessWindowHint);//设置窗体类型
     QSqlQuery query;
    query.exec("select * from WALLPAPER_DATA");//主窗口壁纸数据
    query.next();
    QString FileName=query.value(0).toString();
    QString FileName1;
    if(FileName.isEmpty())
    {
       FileName1 = ":/image/image/background/bg8.jpg";
    }
    else
    {
       FileName1 = FileName;

    }
    query.exec("select * from TRA_DATA");//主窗口透明度数据
    query.next();
    QString Values=query.value(0).toString();
    if(Values.isEmpty())
    {
        transparency=1;
    }
    else
    {
        transparency=Values.toDouble();
    }
    ui->frame->setWindowOpacity(transparency);//设置透明度
    ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:5px;border-image: url(%1);}").arg(FileName1));
    music=new QMediaPlayer(this);

    playlist =new QMediaPlaylist(this);//本地音乐播放列表
    playlist->setPlaybackMode(QMediaPlaylist::Loop);//随机播放
    playlist_2=new QMediaPlaylist(this);//我喜欢播放列表
    playlist_2->setPlaybackMode(QMediaPlaylist::Loop);//随机播放
    playlist_3=new QMediaPlaylist(this);//我的收藏播放列表
    playlist_3->setPlaybackMode(QMediaPlaylist::Loop);//随机播放
    playlist_4 = new QMediaPlaylist(this);
    playlist_4->setPlaybackMode(QMediaPlaylist::Loop);

    ui->verticalSlider->hide();
    ui->verticalSlider->setValue(100);


    ui->horizontalSlider->setValue(0);
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_10->setStyleSheet("QPushButton"
    "{"
    "background-image: url(:/image/image/image-hover/music-hover.png);"
    "background-repeat:no-repeat;"
    "background-position:center center;"
    "border:none;"

    "}"

    "QPushButton:hover{"

        "background-image: url(:/image/image/image-hover/music-hover.png);"
    "background-repeat:no-repeat;"
    "background-position:center center;"


    "}"
    "QPushButton:pressed{"
    "background-image: url(:/image/image/image/music.png);"
    "background-repeat:no-repeat;"
    "background-position:center center;"

    "}"

);




}

 inline void Widget::init_win()
{


    QMenu *ToolMenu=new QMenu(this);//任务栏菜单
    if(QtWin::isCompositionEnabled())
    {

        QtWin::enableBlurBehindWindow(ToolMenu);

    }
    else
    {

        QtWin::disableBlurBehindWindow(ToolMenu);
        ToolMenu->hide();
    }
    toolbar=new QWinThumbnailToolBar(this);
    toolbar->setWindow(windowHandle());
    next=new QWinThumbnailToolButton(this);//下一首
    pre=new QWinThumbnailToolButton(this);//上一首
    pause=new QWinThumbnailToolButton(this);//播放暂停
    next->setToolTip(("下一首"));
    next->setIcon(QIcon(":/image/image/next1.png"));
    connect(next,&QWinThumbnailToolButton::clicked,this,&Widget::action9_slot);//下一首->action10_slot槽
    pre->setToolTip(("上一首"));
    pre->setIcon(QIcon(":/image/image/pre1.png"));
    connect(pre,&QWinThumbnailToolButton::clicked,this,&Widget::action10_slot);//上一首->action9_slot槽
    pause->setToolTip(("暂停"));
    pause->setIcon(QIcon(":/image/image/bf13.png"));
    connect(pause,&QWinThumbnailToolButton::clicked,this,&Widget::on_pushButton_2_clicked);//播放/暂停->on_pushButton_2_clicked槽
    toolbar->addButton(pre);//任务栏增加按钮
    toolbar->addButton(pause);//任务栏增加按钮
    toolbar->addButton(next);//任务栏增加按钮
    Taskbotton=new QWinTaskbarButton(this);//任务栏
    TaskProgress=new QWinTaskbarProgress(this);//进度条

    Taskbotton->setWindow(windowHandle());
    TaskProgress=Taskbotton->progress();//获取任务栏的进度条
    connect(ui->horizontalSlider,&QSlider::valueChanged,TaskProgress,&QWinTaskbarProgress::setValue);//进度条数值改变->设置任务栏进度条数值
    connect(ui->horizontalSlider,&QSlider::rangeChanged,TaskProgress,&QWinTaskbarProgress::setRange);//进度条范围改变->设置任务栏进度条范围
}
 inline void Widget::init_Connect(){


    connect(music,&QMediaPlayer::metaDataAvailableChanged,this,&Widget::updateInfo);//音乐歌名改变->更新显示文本
    connect(music,&QMediaPlayer::positionChanged,this,&Widget::updatePosition);//播放的位置改变->更新进度条播放位置
    connect(music,&QMediaPlayer::durationChanged,this,&Widget::updateDuration);//播放歌曲改变->更新进度条
    connect(ui->horizontalSlider,&QSlider::sliderMoved,music,&QMediaPlayer::setPosition);//进度条移动->更新音乐的播放位置
    connect(playlist,&QMediaPlaylist::currentIndexChanged,this,&Widget::updatalistwidget_3);//本地音乐播放列表位置改变->更新listWidget_3的位置
    connect(playlist_2,&QMediaPlaylist::currentIndexChanged,this,&Widget::updatalistwidget_2);//我喜欢播放列表位置改变->更新listWidget_2的位置
    connect(playlist_3,&QMediaPlaylist::currentIndexChanged,this,&Widget::updatalistwidget);//我的收藏播放列表位置改变->更新listWidget的位置
    connect(action1,&QAction::triggered,this,&Widget::action1_slot);//添加至本地音乐动作点击->执行action1_slot槽
    connect(action2,&QAction::triggered,this,&Widget::action2_slot);//添加我喜欢动作点击->执行action2_slot槽
    connect(action3,&QAction::triggered,this,&Widget::action3_slot);//添加我的收藏动作点击->执行action3_slot槽
    connect(action4_1,&QAction::triggered,this,&Widget::action4_1_slot);//透明度加动作点击->执行action4_1_slot槽
    connect(action4_2,&QAction::triggered,this,&Widget::action4_2_slot);//透明度减动作点击->执行action4_2_slot槽
    connect(action5_1,&QAction::triggered,this,&Widget::action5_1_slot);//默认皮肤1动作点击->执行action5_1_slot槽
    connect(action5_2,&QAction::triggered,this,&Widget::action5_2_slot);//默认皮肤2动作点击->执行action5_2_slot槽
    connect(action5_3,&QAction::triggered,this,&Widget::action5_3_slot);//自定义皮肤动作点击->执行action5_3_slot槽
    connect(action5_4,&QAction::triggered,this,&Widget::action5_4_slot);//3
    connect(action6,&QAction::triggered,this,&Widget::action6_slot);//关于动作点击->执行action6_slot槽
    connect(action7,&QAction::triggered,this,&Widget::action7_slot);//使用介绍动作点击->执行action7_slot槽
    connect(action8,&QAction::triggered,this,&Widget::action8_slot);//退出动作点击->执行action8_slot槽
    connect(ClearALL_1,&QAction::triggered,this,&Widget::ClearALL_1_slot);//清除本地音乐动作点击->执行ClearALL_1_slot槽
    connect(ClearALL_2,&QAction::triggered,this,&Widget::ClearALL_2_slot);//清除我喜欢动作点击->执行ClearALL_2_slot槽
    connect(ClearALL_3,&QAction::triggered,this,&Widget::ClearALL_3_slot);//清除我的收藏动作点击->执行ClearALL_3_slot槽
    connect(ClearALL_4,&QAction::triggered,this,&Widget::ClearALL_4_slot);//清除所有音乐动作点击->执行ClearALL_4_slot槽
    connect(action13,&QAction::triggered,this,&Widget::action8_slot);//退出动作点击->执行action8_slot槽
    connect(action9,&QAction::triggered,this,&Widget::action9_slot);//播放上一首动作点击->执行action9_slot槽
    connect(action10,&QAction::triggered,this,&Widget::action10_slot);//播放下一首动作点击->执行action10_slot槽
    connect(action11,&QAction::triggered,this,&Widget::action11_slot);//暂停动作点击->执行action11_slot槽
    connect(action11_1,&QAction::triggered,this,&Widget::action11_1_slot);//播放动作点击->执行action11_1_slot槽
    connect(action12_1,&QAction::triggered,this,&Widget::action12_1_slot);//顺序播放动作点击->执行action12_1_slot槽
    connect(action12_2,&QAction::triggered,this,&Widget::action12_2_slot);//随机播放动作点击->执行action12_2_slot槽
    connect(action12_3,&QAction::triggered,this,&Widget::action12_3_slot);//单曲循环播放动作点击->执行action12_3_slot槽
    connect(ui->verticalSlider,&QSlider::valueChanged,this,&Widget::changeVolume);//音量进度条置的改变->音量改变
    connect(music,&QMediaPlayer::stateChanged,this,&Widget::music_stateChang);//音乐的播放状态改变->执行music_stateChang槽
    connect(Music,&Dialog::Data,this,&Widget::Data_slot);//接收极简播放器的数据
    connect(detila,&QAction::triggered,this,&Widget::detila_slot);//歌曲详情动作点击->执行detila_slot槽
    connect(playlist,&QMediaPlaylist::playbackModeChanged,this,&Widget::PlaylistModel_slot);//播放列表模型改变->执行Widget::PlaylistModel_slot槽
    connect(location,&QAction::triggered,this,&Widget::on_pushButton_7_clicked);//定位动作点击->执行on_pushButton_7_clicked槽
    connect(ClearHistory,&QAction::triggered,this,&Widget::ClearHistory_Slot);

}
 inline void Widget::init_tooltip()
{
    ui->horizontalSlider->setToolTip(("播放进度"));
    ui->pushButton->setToolTip(("添加歌曲"));
    ui->pushButton_2->setToolTip(("暂停"));
    ui->pushButton_3->setToolTip(("下一首"));
    ui->pushButton_4->setToolTip(("上一首"));
    ui->pushButton_5->setToolTip(("设置"));
    ui->pushButton_6->setToolTip(("更换皮肤"));
    ui->pushButton_7->setToolTip(("定位"));
    ui->pushButton_8->setToolTip(("音量"));
    ui->pushButton_9->setToolTip(("顺序播放"));
    ui->pushButton_10->setToolTip(("本地音乐"));
    ui->pushButton_11->setToolTip(("我喜欢"));
    ui->pushButton_12->setToolTip(("我的收藏"));
    ui->pushButton_13->setToolTip(("切换至极简模式/双击"));
    ui->pushButton_15->setToolTip(("隐藏播放列表"));
    ui->pushButton_17->setToolTip(("关闭"));
    ui->pushButton_16->setToolTip(("最小化"));


}
 inline void Widget::init_icon()
{
    ui->pushButton_2->setIconSize(QSize(48,48));//暂停/播放
    ui->pushButton_2->setIcon(QIcon(":/image/image/image/pase.png"));
    ui->pushButton_2->setStyleSheet(PaseStyle());
    ui->pushButton_15->setIconSize(QSize(32,32));//隐藏/显示播放列表
    ui->pushButton_15->setIcon(QIcon(":/image/image/image/left.png"));
    ui->pushButton_15->setStyleSheet(HideListStyle());
    ui->pushButton_9->setIconSize(QSize(32,32));//播放模式
    ui->pushButton_9->setIcon(QIcon(":/image/image/image/loop.png"));
    ui->pushButton_9->setStyleSheet(LoopStyle());
    ui->pushButton_14->setIconSize(QSize(32,32));//我喜欢
    ui->pushButton_14->setIcon(QIcon(":/image/image/image/Ilike.png"));
    ui->pushButton_14->setStyleSheet(IlikeStyle());
    ui->pushButton_8->setIconSize(QSize(32,32));//音量
    ui->pushButton_8->setStyleSheet(VoiceStyle());
    ui->pushButton_8->setIcon(QIcon(":/image/image/image/music-voice.png"));


}
 inline void Widget::init_action()
{

    action1=new QAction(this);//添加至本地音乐
    action2=new QAction(this);//添加至我喜欢
    action3=new QAction(this);//添加至我的收藏
    action1->setIcon(QIcon(":/image/image/music_32px_1125557_easyicon.net.png"));
    action1->setText(("添加至本地音乐"));
    action1->setShortcut(QKeySequence("Ctrl+O"));
    action2->setIcon(QIcon(":/image/image/like_outline_32px_1101681_easyicon.net.png"));
    action2->setText(("添加至我喜欢"));
    action2->setShortcut(QKeySequence("Ctrl+A"));
    action3->setIcon(QIcon(":/image/image/list_32px_1074296_easyicon.net.png"));
    action3->setText(("添加至我的收藏"));
    action3->setShortcut(QKeySequence("Ctrl+Z"));


    QMenu *menu1=new QMenu(this);//添加菜单
    menu1->addAction(action1);
    menu1->addAction(action2);
    menu1->addAction(action3);
    add=new QAction(this);//添加歌曲
    add->setIcon(QIcon(":/image/image/add.png"));
    add->setText(("添加歌曲"));
    add->setMenu(menu1);
    menu1->setStyleSheet(
              MenuStyle()
                );
    ui->pushButton->setMenu(menu1);

    location=new QAction(this);//定位
    location->setText(("定位"));
    location->setIcon(QIcon(":/image/image/location_32px_1074876_easyicon.net.png"));

    action4=new QAction(this);//设置透明度
    action5=new QAction(this);//设置皮肤

    action5_1=new QAction(this);//默认皮肤1
    action5_2=new QAction(this);//默认皮肤2
    action5_3=new QAction(this);//自定义皮肤
    action5_4 = new QAction(this);
    action6=new QAction(this);//关于
    action7=new QAction(this);//使用介绍
    action8=new QAction(this);//退出
    ClearALL=new QAction(this);//清除
    ClearALL_1=new QAction(this);//清除本地音乐
    ClearALL_2=new QAction(this);//清除我喜欢
    ClearALL_3=new QAction(this);//清除我的收藏
    ClearALL_4=new QAction(this);//清除所有
    ClearHistory = new QAction(this);//清除历史记录
    action4->setIcon(QIcon(":/image/image/ooopic_1500874104.png"));
    action4->setText(("设置透明度           "));

    action4_1=new QAction(this);//透明度加
    action4_2=new QAction(this);//透明度减
    action4_1->setIcon(QIcon(":/image/image/add.png"));
    action4_1->setText(("+5%"));
    action4_1->setShortcut(QKeySequence("Ctrl++"));
    action4_2->setIcon(QIcon(":/image/image/sub.png"));
    action4_2->setText(("-5%"));
    action4_2->setShortcut(QKeySequence("Ctrl+-"));
    QMenu *temp=new QMenu(this);//透明度菜单
    temp->addAction(action4_1);
    temp->addAction(action4_2);
    temp->setStyleSheet(
          MenuStyle()
            );
    action4->setMenu(temp);

    action5->setIcon(QIcon(":/image/image/pf.png"));
    action5->setText(("设置皮肤"));

    action5_1->setIcon(QIcon(":/image/image/pf2.png"));
    action5_1->setText(("绿色"));

    action5_2->setIcon(QIcon(":/image/image/pf5.png"));
    action5_2->setText(("动漫"));
    action5_4->setIcon(QIcon(":/image/image/pf.png"));
    action5_4->setText(("蓝色"));
    action5_3->setIcon(QIcon(":/image/image/pf4.png"));
    action5_3->setText(("自定义"));

    action5_3->setShortcut(QKeySequence("Ctrl+X"));
    QMenu *ChangeBackGroundMenu=new QMenu(this);//设置皮肤菜单
    ChangeBackGroundMenu->addAction(action5_1);
    ChangeBackGroundMenu->addAction(action5_2);
    ChangeBackGroundMenu->addAction(action5_4);
    ChangeBackGroundMenu->addAction(action5_3);
    ChangeBackGroundMenu->setStyleSheet(
          MenuStyle()
            );
    action5->setMenu(ChangeBackGroundMenu);

    ui->pushButton_6->setMenu(ChangeBackGroundMenu);

    action6->setIcon(QIcon(":/image/image/ooopic_1500873230.png"));
    action6->setText(("关于"));
    action7->setIcon(QIcon(":/image/image/ooopic_1500873272.png"));
    action7->setText(("使用介绍"));
    ClearALL->setIcon(QIcon(":/image/image/edit_clear_locationbar_ltr_32px_539686_easyicon.net.png"));
    ClearALL->setText(("清除"));

    ClearALL_1->setIcon(QIcon(":/image/image/Music_32px_1144946_easyicon.net.png"));
    ClearALL_1->setText(("清除本地音乐列表"));
    ClearALL_1->setShortcut(QKeySequence("Ctrl+M"));
    ClearALL_2->setIcon(QIcon(":/image/image/like_outline_32px_1170275_easyicon.net.png"));
    ClearALL_2->setText(("清除我喜欢列表"));
    ClearALL_2->setShortcut(QKeySequence("Ctrl+N"));
    ClearALL_3->setIcon(QIcon(":/image/image/list_32px_1142913_easyicon.net.png"));
    ClearALL_3->setText(("清除我的收藏"));
    ClearALL_3->setShortcut(QKeySequence("Ctrl+B"));
    ClearALL_4->setIcon(QIcon(":/image/image/playlist_27.690544412607px_1187707_easyicon.net.png"));
    ClearALL_4->setText(("清除所有列表"));
    ClearALL_4->setShortcut(QKeySequence("Ctrl+V"));
    ClearHistory->setIcon(QIcon(":/image/image/nextbo.png"));
    ClearHistory->setText(("清除历史记录"));
    ClearHistory->setShortcut(QKeySequence("Ctrl+Shift+S"));
    QMenu *M=new QMenu(this);//清除菜单

    M->addAction(ClearALL_1);
    M->addAction(ClearALL_2);
    M->addAction(ClearALL_3);
    M->addAction(ClearALL_4);
    M->addAction(ClearHistory);
    M->setStyleSheet(MenuStyle());
    ClearALL->setMenu(M);

    action8->setIcon(QIcon(":/image/image/tc.png"));
    action8->setText(("退出"));
    action8->setShortcut(QKeySequence("Ctrl+Q"));
    QMenu *menu2=new QMenu(this);//设置键菜单
    menu2->addAction(action4);
    menu2->addAction(action5);
    menu2->addAction(action6);
    menu2->addAction(action7);
    menu2->addAction(ClearALL);
    menu2->addAction(action8);
    menu2->setStyleSheet(MenuStyle());
    ui->pushButton_5->setMenu(menu2);

    action9=new QAction(this);//播放上一首
    action9->setIcon(QIcon(":/image/image/pre1.png"));
    action9->setText(("播放上一首"));

    action10=new QAction(this);//播放下一首
    action10->setIcon(QIcon(":/image/image/next1.png"));
    action10->setText(("播放下一首"));

    action11=new QAction(this);//暂停
    action11->setIcon(QIcon(":/image/image/zangting.png"));
    action11->setText(("暂停"));

    action11_1=new QAction(this);//播放
    action11_1->setIcon(QIcon(":/image/image/bf2.png"));
    action11_1->setText(("播放"));


    action12=new QAction(this);//播放模式
    action12->setIcon(QIcon(":/image/image/moshi1.png"));
    action12->setText(("播放模式"));
    action12_1=new QAction(this);//顺序播放
    action12_1->setIcon(QIcon(":/image/image/player-icons_32px_1137007_easyicon.net.png"));
    action12_1->setText(("顺序播放"));
    action12_2=new QAction(this);//随机播放
    action12_2->setIcon(QIcon(":/image/image/player-icons_32px_1137005_easyicon.net.png"));
    action12_2->setText(("随机播放"));
    action12_3=new QAction(this);//单曲循环
    action12_3->setIcon(QIcon(":/image/image/player-icons_32px_1137006_easyicon.net.png"));
    action12_3->setText(("单曲循环"));
    QMenu *temp1=new QMenu(this);//播放模式菜单
    temp1->addAction(action12_1);
    temp1->addAction(action12_2);
    temp1->addAction(action12_3);
    temp1->setStyleSheet(
           MenuStyle()

            );
    action12->setMenu(temp1);
    action13=new QAction(this);//退出
    action13->setIcon(QIcon(":/image/image/tc.png"));
    action13->setShortcut(QKeySequence("Ctrl+Q"));
    action13->setText(("退出"));
    detila = new QAction(this);//歌曲详情
    detila->setIcon(QIcon(":/image/image/inf.png"));
    detila->setText(("歌曲信息"));

}
 inline void Widget::init_list()
{

     QSqlQuery query;
    model=new QSqlTableModel(this);//本地音乐列表数据库模型
    model->setTable("LocalMusic");
    model->select();
    model_2=new QSqlTableModel(this);//我喜欢列表数据库模型
    model_2->setTable("LikeMusic");
    model_2->select();
    model_3=new QSqlTableModel(this);//我的收藏数据库模型
    model_3->setTable("  CollectMusic");
    model_3->select();
    query.exec("select * from LocalMusic");
    while(query.next())//初始化本地音乐播放列表
    {
        QString Name=query.value(1).toString();
        QString FileName=query.value(2).toString();
        if(!Name.isEmpty()&&!FileName.isEmpty())
        {
        QListWidgetItem *item1=new QListWidgetItem;
        item1->setIcon(QIcon(":/image/image/Music_32px_1144946_easyicon.net.png"));
        item1->setText(Name);
        ui->listWidget_3->addItem(item1);
        playlist->addMedia(QUrl::fromLocalFile(FileName));
        list1.push_back(0);
        FilePath.push_back(FileName);
        }
         

    }
    query.exec("select * from LikeMusic");
    while(query.next())//初始化我喜欢播放列表
    {
        QString Name=query.value(1).toString();
        QString FileName=query.value(2).toString();
        if(!Name.isEmpty()&&!FileName.isEmpty())
        {
        QListWidgetItem *item4=new QListWidgetItem;
        item4->setIcon(QIcon(":/image/image/like_outline_32px_1170275_easyicon.net.png"));
        item4->setText(Name);
        ui->listWidget_2->addItem(item4);
        playlist_2->addMedia(QUrl::fromLocalFile(FileName));


        }

    }
    query.exec("select * from  CollectMusic");
    while(query.next())//初始化我的收藏播放列表
    {
        QString Name=query.value(1).toString();
        QString FileName=query.value(2).toString();
        if(!Name.isEmpty()&&!FileName.isEmpty())
        {
        QListWidgetItem *item5=new QListWidgetItem;
        item5->setIcon(QIcon(":/image/image/music_not_25.570093457944px_1171234_easyicon.net.png"));
        item5->setText(Name);
        ui->listWidget->addItem(item5);
        playlist_3->addMedia(QUrl::fromLocalFile(FileName));


        }

    }
    music->setPlaylist(playlist);
    ui->listWidget_5->clear();
    


}
 inline QString Widget::MusicListStyle(){

     return  "QPushButton"
             " {"
             "background-image:url(:/image/image/image/music.png);"
           "   background-repeat:no-repeat;"
            "  background-position:center center;"
           "   border:none;"

          "    }"

              "QPushButton:hover{"
            "  background-repeat:no-repeat;"
           "   background-position:center center;"
           "background-image:url(:/image/image/image/music.png);"

             " }"
             " QPushButton:pressed{"
              "background-repeat:no-repeat;"
             " background-position:center center;"
             " background-image:url(:/image/image/image/music.png);"

               "}";

 }

 inline QString Widget::MenuStyle()
 {
     return     " QMenu {"
            " background: white; "
                "border-radius:2px;"
             "border:1px solid rgb(200,200,200);"

       "  }"
       "  QMenu::item {"

            " background-color: transparent;"
            " padding:5px 30px;"
      "       margin:0px 0px;"
            " border-bottom:0px solid #DBDBDB;"
         "}"
        " QMenu::item:selected { "
             "background-color: aqua;"
         "}";

 }

 inline QString Widget::PlayStyle()
 {
     
     return "QPushButton"
    " {"
    "background-image:url(:/image/image/image/play.png);"
  "   background-repeat:no-repeat;"
   "  background-position:center center;"
  "   border:none;"
     
 "    }"
     
     "QPushButton:hover{"
   "  background-repeat:no-repeat;"
  "   background-position:center center;"
  "background-image:url(:/image/image/image-hover/play-hover.png);"
     
    " }"
    " QPushButton:pressed{"
     "background-repeat:no-repeat;"
    " background-position:center center;"
    " background-image:url(:/image/image/image/play.png);"
     
      "}";

 }
 inline QString Widget::PaseStyle()
 {


     return "QPushButton"
    " {"
    "background-image:url(:/image/image/image/pase.png);"
  "   background-repeat:no-repeat;"
   "  background-position:center center;"
  "   border:none;"

 "    }"

     "QPushButton:hover{"
   "  background-repeat:no-repeat;"
  "   background-position:center center;"
  "background-image:url(:/image/image/image-hover/pase-hover.png);"

    " }"
    " QPushButton:pressed{"
     "background-repeat:no-repeat;"
    " background-position:center center;"
    " background-image:url(:/image/image/image/pase.png);"

      "}";

 }
inline QString Widget::IlikeStyle()
{


    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/Ilike.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/Ilike-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/Ilike.png);"

     "}";

}
inline QString Widget::Ilike1Style()
{


    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/Ilike1.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/Ilike1-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/Ilike1.png);"

     "}";

}
inline QString Widget::ShowListStyle()
{
    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/right.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/right-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/right.png);"

     "}";

}
inline QString Widget::HideListStyle()
{
    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/left.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/left-light.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/left.png);"

     "}";
}
inline QString Widget::RandomStyle()
{
    
    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/play-random.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/play-random-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/play-random.png);"

     "}";
    
}
inline QString Widget::LoopStyle()
{


    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/loop.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/loop-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/loop.png);"

     "}";

}
inline QString Widget::LoopOneStyle()
{


    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/loop-one.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/loop-one-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/loop-one.png);"

     "}";

}
inline QString Widget::VoiceStyle()
{

    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/music-voice.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/music-voice-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/music-voice.png);"

     "}";
}
inline QString Widget::NoVoiceStyle()
{

    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/none-music.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/none-music-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/none-music.png);"

     "}";
}

Widget::~Widget()//析构
{
    delete ui;
}
static QString Time(qint64 time)//转换时间
{
    qint64 seconds=time/1000;
    const qint64 minutes=seconds/60;
    seconds-=minutes*60;
    return QStringLiteral("%1:%2")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'));
}
void Widget::updateInfo()//更新文本
{

    QString info;
    info=("正在播放:  ");
    if(music->isMetaDataAvailable())
    {
        QString title=music->metaData(QStringLiteral("Title")).toString();
        if(!title.isEmpty())
        {
            info+=title;
        }
        else
        {
            info+=("未知歌曲");
        }
        info+="-";
        QString author=music->metaData(QStringLiteral("Author")).toString();
        if(!author.isEmpty())
        {
            info+=author;
        }
        else
        {
          info+=("未知作者");
        }
    }
    //判断该歌曲是不是我喜欢歌曲
    ui->label->setText(info);
    if(music->playlist()==playlist_2)
    {
        ui->pushButton_14->setIcon(QIcon(":/image/image/image/Ilike1.png"));
        ui->pushButton_14->setStyleSheet(Ilike1Style());
        ui->pushButton_14->setToolTip(("我喜欢"));
    }
    else if(music->playlist()==playlist_3)
    {

        ui->pushButton_14->setIcon(QIcon(":/image/image/image/music.png"));
         ui->pushButton_14->setStyleSheet(MusicListStyle());
        ui->pushButton_14->setToolTip(("我的收藏"));

    }
    else if(music->playlist()==playlist_4)
    {
        ui->pushButton_14->setIcon(QIcon(":/image/image/image/music.png"));
        ui->pushButton_14->setStyleSheet(MusicListStyle());
        ui->pushButton_14->setToolTip(("播放历史"));
    }
    else
    {
        //判断该歌曲是不是我喜欢歌曲
        QSqlQuery query;
        query.exec("select * from LocalMusic");
        model->setTable("LocalMusic");
        model->select();
        int row=playlist->currentIndex();
        int flag;
         flag=model->data(model->index(row,3)).toInt();
        if(flag)
        {

            ui->pushButton_14->setIcon(QIcon(":/image/image/image/Ilike1.png"));
            ui->pushButton_14->setStyleSheet(Ilike1Style());
            ui->pushButton_14->setToolTip(("我喜欢"));

        }
        else
        {

            ui->pushButton_14->setIcon(QIcon(":/image/image/image/Ilike.png"));
            ui->pushButton_14->setStyleSheet(IlikeStyle());
            ui->pushButton_14->setToolTip(("添加至我喜欢"));

        }

      }

    int x=qrand()%11;
    ui->label_3->setText(labelText1.at(x));
    ui->label_4->setText(labelText2.at(x));
}
void Widget::updatePosition(qint64 position)//更新播放位置
{
    ui->horizontalSlider->setValue(position);
    ui->label_2->setText(Time(position)+"/"+Time(music->duration()));
}
void Widget::updateDuration(qint64 duration)//更新播放进度
{

    ui->horizontalSlider->setRange(0,duration);
    ui->horizontalSlider->setEnabled(duration>0);
    ui->horizontalSlider->setPageStep(duration/10);
}
void Widget::pushbuttonstyle_5()
{

    ui->pushButton_10->setStyleSheet("QPushButton"
                                     "{"
                                    "background-image: url(:/image/image/image/music.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"
                                     "border:none;"

                                     "}"

                                     "QPushButton:hover{"

                                         "background-image: url(:/image/image/image-hover/music-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"


                                     "}"
                                     "QPushButton:pressed{"
                                     "background-image: url(:/image/image/image/music.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"

                                     "}"
);
    ui->pushButton_11->setStyleSheet(

               " QPushButton"
                "{"
                "background-image: url(:/image/image/image/like.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"
                "border:none;"

                "}"

                "QPushButton:hover{"

                    "background-image: url(:/image/image/image-hover/like-hover.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"


                "}"
                "QPushButton:pressed{"
                "background-image: url(:/image/image/image/like.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"

                "}"

                                     );

    ui->pushButton_12->setStyleSheet( "QPushButton"
                                      "{"
                                      "background-image: url(:/image/image/image/list.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"
                                      "border:none;"

                                      "}"

                                      "QPushButton:hover{"

                                          "background-image: url(:/image/image/image-hover/list-hover.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"


                                      "}"
                                      "QPushButton:pressed{"
                                      "background-image: url(:/image/image/image/list.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"

                                      "}"
                                     );
    ui->pushButton_22->setStyleSheet("QPushButton"
                                     "{"
                                     "background-image: url(:/image/image/image-hover/play-resently-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"
                                     "border:none;"

                                     "}"

                                     "QPushButton:hover{"

                                         "background-image: url(:/image/image/image-hover/play-resently-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"


                                     "}"
                                     "QPushButton:pressed{"
                                     "background-image: url(:/image/image/image/play-resently.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"

                                     "}");
}

void Widget::pushbuttonstyle()//效果设置  本地音乐按钮显示白色背景
{
    
    ui->pushButton_10->setStyleSheet("QPushButton"
                                     "{"
                                     "background-image: url(:/image/image/image-hover/music-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"
                                     "border:none;"

                                     "}"

                                     "QPushButton:hover{"

                                         "background-image: url(:/image/image/image-hover/music-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"


                                     "}"
                                     "QPushButton:pressed{"
                                     "background-image: url(:/image/image/image/music.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"

                                     "}"
);
    ui->pushButton_11->setStyleSheet(

               " QPushButton"
                "{"
                "background-image: url(:/image/image/image/like.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"
                "border:none;"

                "}"

                "QPushButton:hover{"

                    "background-image: url(:/image/image/image-hover/like-hover.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"


                "}"
                "QPushButton:pressed{"
                "background-image: url(:/image/image/image/like.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"

                "}"

                                     );

    ui->pushButton_12->setStyleSheet( "QPushButton"
                                      "{"
                                      "background-image: url(:/image/image/image/list.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"
                                      "border:none;"

                                      "}"

                                      "QPushButton:hover{"

                                          "background-image: url(:/image/image/image-hover/list-hover.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"


                                      "}"
                                      "QPushButton:pressed{"
                                      "background-image: url(:/image/image/image/list.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"

                                      "}"
                                     );
    ui->pushButton_22->setStyleSheet("QPushButton"
                                     "{"
                                     "background-image: url(:/image/image/image/play-resently.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"
                                     "border:none;"

                                     "}"

                                     "QPushButton:hover{"

                                         "background-image: url(:/image/image/image-hover/play-resently-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"


                                     "}"
                                     "QPushButton:pressed{"
                                     "background-image: url(:/image/image/image/play-resently.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"

                                     "}");

}
void Widget::pushbuttonstyle_2()//效果设置  我喜欢列表按钮显示白色背景
{
    ui->pushButton_10->setStyleSheet("QPushButton"
                                     "{"
                                    "background-image:url(:/image/image/image/music.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"
                                     "border:none;"

                                     "}"

                                     "QPushButton:hover{"

                                         "background-image: url(:/image/image/image-hover/music-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"


                                     "}"
                                     "QPushButton:pressed{"
                                     "background-image:url(:/image/image/image/music.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"

                                     "}"
);
    ui->pushButton_11->setStyleSheet(

               " QPushButton"
                "{"
                 "background-image: url(:/image/image/image-hover/like-hover.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"
                "border:none;"

                "}"

                "QPushButton:hover{"

                    "background-image: url(:/image/image/image-hover/like-hover.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"


                "}"
                "QPushButton:pressed{"
                "background-image: url(:/image/image/image/like.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"

                "}"

                                     );

    ui->pushButton_12->setStyleSheet( "QPushButton"
                                      "{"
                                      "background-image: url(:/image/image/image/list.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"
                                      "border:none;"

                                      "}"

                                      "QPushButton:hover{"

                                          "background-image: url(:/image/image/image-hover/list-hover.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"


                                      "}"
                                      "QPushButton:pressed{"
                                      "background-image: url(:/image/image/image/list.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"

                                      "}"
                                     );
    ui->pushButton_22->setStyleSheet("QPushButton"
                                     "{"
                                     "background-image: url(:/image/image/image/play-resently.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"
                                     "border:none;"

                                     "}"

                                     "QPushButton:hover{"

                                         "background-image: url(:/image/image/image-hover/play-resently-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"


                                     "}"
                                     "QPushButton:pressed{"
                                     "background-image: url(:/image/image/image/play-resently.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"

                                     "}");


}
void Widget::pushbuttonstyle_3()//效果设置  我的收藏按钮显示白色背景
{

    ui->pushButton_10->setStyleSheet("QPushButton"
                                     "{"
                                    "background-image:url(:/image/image/image/music.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"
                                     "border:none;"

                                     "}"

                                     "QPushButton:hover{"

                                         "background-image: url(:/image/image/image-hover/music-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"


                                     "}"
                                     "QPushButton:pressed{"
                                     "background-image:url(:/image/image/image/music.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"

                                     "}"
);
    ui->pushButton_11->setStyleSheet(

               " QPushButton"
                "{"
              "background-image: url(:/image/image/image/like.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"
                "border:none;"

                "}"

                "QPushButton:hover{"

                    "background-image: url(:/image/image/image-hover/like-hover.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"


                "}"
                "QPushButton:pressed{"
                "background-image: url(:/image/image/image/like.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"

                "}"

                                     );

    ui->pushButton_12->setStyleSheet( "QPushButton"
                                      "{"
                                      "background-image: url(:/image/image/image-hover/list-hover.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"
                                      "border:none;"

                                      "}"

                                      "QPushButton:hover{"

                                          "background-image: url(:/image/image/image-hover/list-hover.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"


                                      "}"
                                      "QPushButton:pressed{"
                                      "background-image: url(:/image/image/image/list.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"

                                      "}"
                                     );
    ui->pushButton_22->setStyleSheet("QPushButton"
                                     "{"
                                     "background-image: url(:/image/image/image/play-resently.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"
                                     "border:none;"

                                     "}"

                                     "QPushButton:hover{"

                                         "background-image: url(:/image/image/image-hover/play-resently-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"


                                     "}"
                                     "QPushButton:pressed{"
                                     "background-image: url(:/image/image/image/play-resently.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"

                                     "}");

}
void Widget::pushbuttonstyle_4()//效果设置  所有按钮背景都不变白色
{

    ui->pushButton_10->setStyleSheet("QPushButton"
                                     "{"
                                    "background-image:url(:/image/image/image/music.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"
                                     "border:none;"

                                     "}"

                                     "QPushButton:hover{"

                                         "background-image: url(:/image/image/image-hover/music-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"


                                     "}"
                                     "QPushButton:pressed{"
                                     "background-image:url(:/image/image/image/music.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"

                                     "}"
);
    ui->pushButton_11->setStyleSheet(

               " QPushButton"
                "{"
              "background-image: url(:/image/image/image/like.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"
                "border:none;"

                "}"

                "QPushButton:hover{"

                    "background-image: url(:/image/image/image-hover/like-hover.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"


                "}"
                "QPushButton:pressed{"
                "background-image: url(:/image/image/image/like.png);"
                "background-repeat:no-repeat;"
                "background-position:center center;"

                "}"

                                     );

    ui->pushButton_12->setStyleSheet( "QPushButton"
                                      "{"
                                      "background-image: url(:/image/image/image/list.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"
                                      "border:none;"

                                      "}"

                                      "QPushButton:hover{"

                                          "background-image: url(:/image/image/image-hover/list-hover.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"


                                      "}"
                                      "QPushButton:pressed{"
                                      "background-image: url(:/image/image/image/list.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"

                                      "}"
                                     );
    ui->pushButton_22->setStyleSheet("QPushButton"
                                     "{"
                                     "background-image: url(:/image/image/image/play-resently.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"
                                     "border:none;"

                                     "}"

                                     "QPushButton:hover{"

                                         "background-image: url(:/image/image/image-hover/play-resently-hover.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"


                                     "}"
                                     "QPushButton:pressed{"
                                     "background-image: url(:/image/image/image/play-resently.png);"
                                     "background-repeat:no-repeat;"
                                     "background-position:center center;"

                                     "}");

}

void Widget::on_pushButton_10_clicked()//跳至本地音乐
{   ui->listWidget_2->setSelectionMode(QListWidget::SingleSelection);
    ui->listWidget->setSelectionMode(QListWidget::SingleSelection);
    ui->stackedWidget->setCurrentIndex(0);
    pushbuttonstyle();
    ListFocus();
}
void Widget::on_pushButton_11_clicked()//跳至自我喜欢
{
    ui->listWidget_3->setSelectionMode(QListWidget::SingleSelection);
    ui->listWidget->setSelectionMode(QListWidget::SingleSelection);
    ui->stackedWidget->setCurrentIndex(1);
    pushbuttonstyle_2();
    ListFocus();
}
void Widget::on_pushButton_12_clicked()//跳至我的收藏
{   ui->listWidget_2->setSelectionMode(QListWidget::SingleSelection);
    ui->listWidget_3->setSelectionMode(QListWidget::SingleSelection);
    ui->stackedWidget->setCurrentIndex(2);
    pushbuttonstyle_3();
    ListFocus();
}
void Widget::on_pushButton_22_clicked()//历史记录
{
      ui->listWidget->setSelectionMode(QListWidget::SingleSelection);
      ui->listWidget_2->setSelectionMode(QListWidget::SingleSelection);
      ui->listWidget_3->setSelectionMode(QListWidget::SingleSelection);
      ui->stackedWidget->setCurrentIndex(4);
      pushbuttonstyle_5();
      ListFocus();
}
void Widget::detila_slot()//歌曲详情
{
    ListFocus();
    if(music->playlist()==playlist)
    {
        int row=playlist->currentIndex();
        QString temp=ui->label->text();
        QString Author=temp.split("-").last();
        QString MusicName=temp.remove("-"+Author).split(":  ").last();
        QString time=ui->label_2->text().split("/").last();
        model->setTable("LocalMusic");
        model->select();
        QString FileName=model->data(model->index(row,2)).toString();
        QMessageBox::about(this,"歌曲信息",QString("歌曲名 : %1  \n"
                                                 "作者 : %2 \n"
                                                 "时长 : %3 \n"
                                                 "文件路径 : %4\n").arg(MusicName).arg(Author).arg(time).arg(FileName));


    }
    else if(music->playlist()==playlist_2)
    {

        int row=playlist_2->currentIndex();
        QString temp=ui->label->text();
        QString Author=temp.split("-").last();
        QString MusicName=temp.remove("-"+Author).split(":  ").last();
        QString time=ui->label_2->text().split("/").last();
        model_2->setTable("LikeMusic");
        model_2->select();
        QString FileName=model_2->data(model_2->index(row,2)).toString();
        QMessageBox::about(this,"歌曲信息",QString("歌曲名 : %1  \n"
                                                 "作者 : %2 \n"
                                                 "时长 : %3 \n"
                                                 "文件路径 : %4\n").arg(MusicName).arg(Author).arg(time).arg(FileName));

    }
    else if(music->playlist()==playlist_3)
    {
        int row=playlist_3->currentIndex();
        QString temp=ui->label->text();
        QString Author=temp.split("-").last();
        QString MusicName=temp.remove("-"+Author).split(":  ").last();
        QString time=ui->label_2->text().split("/").last();
        model_3->setTable("  CollectMusic");
        model_3->select();
        QString FileName=model_3->data(model_3->index(row,2)).toString();
        QMessageBox::about(this,"歌曲信息",QString("歌曲名 : %1  \n"
                                                 "作者 : %2 \n"
                                                 "时长 : %3 \n"
                                                 "文件路径 : %4\n").arg(MusicName).arg(Author).arg(time).arg(FileName));


    }
    else
    {
        int row=playlist_4->currentIndex();
        QString temp=ui->label->text();
        QString Author=temp.split("-").last();
        QString MusicName=temp.remove("-"+Author).split(":  ").last();
        QString time=ui->label_2->text().split("/").last();
        QString FileName = FilePath[row];
        QMessageBox::about(this,"歌曲信息",QString("歌曲名 : %1  \n"
                                                 "作者 : %2 \n"
                                                 "时长 : %3 \n"
                                                 "文件路径 : %4\n").arg(MusicName).arg(Author).arg(time).arg(FileName));

        
    }
}

void Widget::ClearALL_1_slot()//清除本地音乐
{
    int values=QMessageBox::information(this,("清除本地音乐列表"),("确定清除本地音乐列表?                              ."),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(values==QMessageBox::Yes)
    {
        QSqlQuery query;
    query.exec("select * from LocalMusic");
    query.exec("delete from LocalMusic");
    ui->listWidget_3->clear();
    playlist->clear();
    list1.clear();
    map.clear();
    FilePath.clear();
    ui->listWidget_5->clear();
    if(music->playlist()==playlist)
    {
       TaskProgress->hide();
    }

    }

}
/**清除历史记录
 * @brief Widget::ClearHistory_Slot
 */
void Widget::ClearHistory_Slot(){

    int values=QMessageBox::information(this,("清除历史记录"),("确定清除所有历史记录?                              ."),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(values==QMessageBox::Yes)
    {

     ui->listWidget_5->clear();
     playlist_4->clear();
     for(int i=0;i<list1.size();i++)
     {
         list1[i] = 0;
     }
     map.clear();
     if(music->playlist()==playlist_4)
     {
         TaskProgress->hide();
     }
    }

}

void Widget::ClearALL_2_slot()//清除我喜欢列表
{
    int values=QMessageBox::information(this,("清除我喜欢列表"),("确定清除我喜欢列表?                              ."),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(values==QMessageBox::Yes)
    {
        QSqlQuery query;
    query.exec("select * from LikeMusic");
    query.exec("delete from LikeMusic");
    query.exec("select * from LocalMusic");
    query.prepare(QString("update LocalMusic set biaoji = ? where biaoji = 1"));
    query.bindValue(0,0);
    query.exec();
    ui->listWidget_2->clear();
    playlist_2->clear();

    if(music->playlist()==playlist_2)
    {
       TaskProgress->hide();
    }
    }
}
void Widget::ClearALL_3_slot()//清除我的收藏
{
    int values=QMessageBox::information(this,("清除我的收藏"),("确定清除我的收藏?                              ."),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(values==QMessageBox::Yes)
    {
        QSqlQuery query;
    query.exec("select * from CollectMusic");
    query.exec("delete from CollectMusic");
    ui->listWidget->clear();
    playlist_3->clear();

    if(music->playlist()==playlist_3)
    {
        TaskProgress->hide();
    }

    }


}
void Widget::ClearALL_4_slot()//清除所有
{
    int values=QMessageBox::information(this,("清除所有列表"),("确定清除所有列表?                              ."),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(values==QMessageBox::Yes)
    {
    QSqlQuery query;

    query.exec("delete from LocalMusic");
    query.exec("delete from CollectMusic");
    query.exec("delete from LikeMusic");
    ui->listWidget_3->clear();
    ui->listWidget_2->clear();
    ui->listWidget->clear();
    playlist->clear();
    playlist_2->clear();
    playlist_3->clear();
    playlist_4->clear();
    list1.clear();
    map.clear();
    FilePath.clear();
    ui->listWidget_5->clear();

            
   TaskProgress->hide();
    }


}

void Widget::action1_slot()//添加菜单  添加至本地音乐
{

    ListFocus();
    ui->stackedWidget->setCurrentIndex(0);
    pushbuttonstyle();
    QSqlQuery query;
    query.exec("select * from LocalMusic");
    QStringList list=QFileDialog::getOpenFileNames(this,("文件"),currentFileName[1],("音频文件(*.mp3)"));
    if(!list.isEmpty())
   {
        //进度条对话框
    QProgressDialog *progressdialog=new QProgressDialog(this);
    progressdialog->setWindowModality(Qt::WindowModal);
    progressdialog->resize(400,120);
    progressdialog->setMinimumSize(400,120);
    progressdialog->setMaximumSize(400,120);
    progressdialog->setMinimumDuration(100);
    progressdialog->setWindowTitle(("添加歌曲"));
    progressdialog->setLabelText(("正在添加,请稍后."));
    QPushButton *button=new QPushButton(this);
    QPixmap pixmap;
    pixmap.load(":/image/image/58d4d135e7bce713bd501050.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(progressdialog->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    progressdialog->setPalette(palette);
    button->setStyleSheet("QPushButton{"
                          "width:100px;"
                          "height:32px;"
                          "text-align:center;"
                          "line-height:32px;"
                          "background-color: deepskyblue;"
                          "border-style:solid;"
                          "border-width: 1px;"
                          "border-radius: 6px;"
                          "border-color: deepskyblue;"
                          "font: bold 14px;"
                          "color :white;"
                          "}"
                          "QPushButton:hover{"



                          "background-color: aqua;"
                          "color: white;"
                          "border-color:aqua;"


                          "}"
                          "QPushButton:pressed{"


                     "background-color:  white;"
                          "border-color:white;"
    
                          "color:deepskyblue;"

                          "}");
    button->setText(("关闭"));
    progressdialog->setCancelButton(button);
    progressdialog->setRange(0,list.size()-1);
    progressdialog->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;background-color:rgba(255,255,255,150);}"
                                  "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}");

    for(int i=0;i<list.size();i++)
    {
        QListWidgetItem *item=new QListWidgetItem;
        item->setIcon(QIcon(":/image/image/Music_32px_1144946_easyicon.net.png"));
        QString path=QDir::toNativeSeparators(list.at(i));
        if(!progressdialog->wasCanceled())
        progressdialog->setValue(i);
        else
        {
            progressdialog->close();
        }
        if(i==list.size()-1)
        {
            progressdialog->close();
        }

        if(!path.isEmpty())
        {

            QString path1 = path;
          
           playlist->addMedia(QUrl::fromLocalFile(path));
           QString Name=path.split("\\").last();
           currentFileName[1] = path1.remove(Name);
           Name.remove(QString(".mp3"));
           item->setText(QString("%1").arg(Name));
           item->setToolTip(Name);
           list1.push_back(0);
           ui->listWidget_3->addItem(item);

           int x=qrand()%1000000;
           query.exec(QString("insert into LocalMusic values (%1,'%2','%3',%4)").arg(x).arg(Name).arg(path).arg(0));
           FilePath.push_back(path);
        
        
        }
    }
    delete button;

    }


}
void Widget::action2_slot()//添加菜单  添加至我喜欢
{
    ListFocus();
    ui->stackedWidget->setCurrentIndex(0);
    pushbuttonstyle();
      /*ui->stackedWidget->setCurrentIndex(1);
      pushbuttonstyle_2();
    QSqlQuery query;
    query.exec("select *from LikeMusic");
    QStringList list = QFileDialog::getOpenFileNames(this,("所有文件"),currentFileName[2],("音频文件(*.mp3)"));
    if(!list.isEmpty())
   {//进度条对话框
        QProgressDialog *progressdialog=new QProgressDialog(this);
    progressdialog->setWindowModality(Qt::WindowModal);
    progressdialog->resize(400,120);
    progressdialog->setMinimumSize(400,120);
    progressdialog->setMaximumSize(400,120);
    progressdialog->setMinimumDuration(100);
    progressdialog->setWindowTitle(("添加歌曲"));
    progressdialog->setLabelText(("正在添加,请稍后."));
    QPushButton *button=new QPushButton(this);
    QPixmap pixmap;
    pixmap.load(":/image/image/58d4d135e7bce713bd501050.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(progressdialog->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    progressdialog->setPalette(palette);
    button->setStyleSheet("QPushButton{"

                          "background-color: rgba(122, 122, 122,100);"
                          "border-style:outset;"
                          "border-width: 1px;"
                          "border-radius: 10px;"
                          "border-color: rgba(122, 122, 122,100);"
                          "font: bold 14px;"
                          "color :rgba(0,0,0,100);"
                          "padding: 6px;"

                          "}"
                          "QPushButton:hover{"



                          "background-color: rgba(176, 58, 176,200);"
                          "color: rgba(0,0,0,200);"


                          "}"
                          "QPushButton:pressed{"


                              "background-color:  rgba(255,255,255,150);"
                          "border-color:rgba(255,255,255,150);"
                          "border-style:inset;"
                          "color:rgba(0,0,0,100);"

                          "}");
    button->setText(("关闭"));
    progressdialog->setCancelButton(button);
    progressdialog->setRange(0,list.size()-1);
    progressdialog->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;background-color:rgba(255,255,255,150);}"
                                  "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}");

    for(int i=0;i<list.size();i++)
    {
        QListWidgetItem *item2=new QListWidgetItem;
        item2->setIcon(QIcon(":/image/image/like_outline_32px_1170275_easyicon.net.png"));
        QString path=QDir::toNativeSeparators(list.at(i));
        if(!progressdialog->wasCanceled())
        {
            progressdialog->setValue(i);
        }
        else
        {
            progressdialog->close();
        }
        progressdialog->setValue(i);
        if(i==list.size()-1)
        {
            progressdialog->close();
        }

        if(!path.isEmpty())
        {
            QString path1 = path;
            playlist_2->addMedia(QUrl::fromLocalFile(path));
            QString Name=path.split("\\").last();
            currentFileName[2] = path1.remove(Name);
            Name.remove(QString(".mp3"));
            item2->setText(QString("%1").arg(Name));
            item2->setToolTip(Name);


            ui->listWidget_2->addItem(item2);
            query.exec(QString("insert into LikeMusic values (%1,'%2','%3')").arg(qrand()%1000000).arg(Name).arg(path));

        }


    }

    delete button;
    }
*/
    return;

}
void Widget::action3_slot()//添加菜单  添加至我的收藏
{ListFocus();
  ui->stackedWidget->setCurrentIndex(0);
   pushbuttonstyle();
  /*ui->stackedWidget->setCurrentIndex(2);
  pushbuttonstyle_3();
    QSqlQuery query;
    query.exec("select *from  CollectMusic");
    QStringList list = QFileDialog::getOpenFileNames(this,("所有文件"),currentFileName[3],("音频文件(*.mp3)"));
   if(!list.isEmpty())
   {
       //进度条对话框
    QProgressDialog *progressdialog=new QProgressDialog(this);
    progressdialog->setWindowModality(Qt::WindowModal);
    progressdialog->resize(400,120);
    progressdialog->setMinimumSize(400,120);
    progressdialog->setMaximumSize(400,120);
    progressdialog->setMinimumDuration(100);
    progressdialog->setWindowTitle(("添加歌曲"));
    progressdialog->setLabelText(("正在添加,请稍后."));
    QPushButton *button=new QPushButton(this);
    QPixmap pixmap;
    pixmap.load(":/image/image/58d4d135e7bce713bd501050.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(progressdialog->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    progressdialog->setPalette(palette);
    button->setStyleSheet("QPushButton{"

                          "background-color: rgba(122, 122, 122,100);"
                          "border-style:outset;"
                          "border-width: 1px;"
                          "border-radius: 10px;"
                          "border-color: rgba(122, 122, 122,100);"
                          "font: bold 14px;"
                          "color :rgba(0,0,0,100);"
                          "padding: 6px;"

                          "}"
                          "QPushButton:hover{"



                          "background-color: rgba(176, 58, 176,200);"
                          "color: rgba(0,0,0,200);"


                          "}"
                          "QPushButton:pressed{"


                              "background-color:  rgba(255,255,255,150);"
                          "border-color:rgba(255,255,255,150);"
                          "border-style:inset;"
                          "color:rgba(0,0,0,100);"

                          "}");
    button->setText(("关闭"));
    progressdialog->setCancelButton(button);
    progressdialog->setRange(0,list.size()-1);
    progressdialog->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;background-color:rgba(255,255,255,150);}"
                                  "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}");

    for(int i=0;i<list.size();i++)
    {
        QListWidgetItem *item3=new QListWidgetItem;
        item3->setIcon(QIcon(":/image/image/music_not_25.570093457944px_1171234_easyicon.net.png"));
        QString path=QDir::toNativeSeparators(list.at(i));
        if(!progressdialog->wasCanceled())
        {
        progressdialog->setValue(i);
        }
        else
        {
            progressdialog->close();
        }
        if(i==list.size()-1)
        {
            progressdialog->close();
        }

        if(!path.isEmpty())
        {
            QString path1 = path;

            playlist_3->addMedia(QUrl::fromLocalFile(path));
            QString Name=path.split("\\").last();
            currentFileName[3] = path1.remove(Name);
            Name.remove(QString(".mp3"));
            item3->setText(QString("%1").arg(Name));
            item3->setToolTip(Name);

            ui->listWidget->addItem(item3);
            query.exec(QString("insert into  CollectMusic values (%1,'%2','%3')").arg(qrand()%1000000).arg(Name).arg(path));

        }


    }

delete button;
   }
*/
    return ;
}
void Widget::action4_1_slot()//设置菜单  透明度+5%
{
    QSqlQuery query;
    query.exec("select * from TRA_DATA");
    query.exec("delete from TRA_DATA");
    if(transparency<1.0)
    {
        transparency+=0.05;

        query.exec(QString("insert into TRA_DATA values (%1)").arg(transparency));

    }
    ui->frame->setWindowOpacity(transparency);
ListFocus();
}
void Widget::action4_2_slot()//设置菜单  透明度-5%
{ QSqlQuery query;
    query.exec("select * from TRA_DATA");
    query.exec("delete from TRA_DATA");
    if(transparency>0.4)
    {
        transparency-=0.05;
        query.exec(QString("insert into TRA_DATA values (%1)").arg(transparency));

    }
    ui->frame->setWindowOpacity(transparency);
ListFocus();
}
void Widget::action5_1_slot()//设置默认壁纸1
{   ListFocus();
    QString FileName=":/image/image/background/bg8.jpg";
    QSqlQuery query;
    query.exec("delete from WALLPAPER_DATA");
    query.exec(QString("insert into WALLPAPER_DATA values('%1')").arg(FileName));
    ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:5px;border-image: url(%1);}").arg(FileName));

}
void Widget::action5_2_slot()//设置默认壁纸2
{
   ListFocus();
    QString FileName=":/image/image/background/bg7.jpg";
    QSqlQuery query;
    query.exec("delete from WALLPAPER_DATA");
    query.exec(QString("insert into WALLPAPER_DATA values('%1')").arg(FileName));
        ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:5px;border-image: url(%1);}").arg(FileName));
}
void Widget::action5_4_slot()
{
  ListFocus();
      QString FileName=":/image/image/background/bg3.jpg";
      QSqlQuery query;
      query.exec("delete from WALLPAPER_DATA");
      query.exec(QString("insert into WALLPAPER_DATA values('%1')").arg(FileName));
         ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:5px;border-image: url(%1);}").arg(FileName));
}

void Widget::action5_3_slot()//设置菜单  设置自定义壁纸
{
    ListFocus();
    QString FileName=QFileDialog::getOpenFileName(this,("文件"),currentFileName[0],("图片文件(*jpg *png)"));
    if(!FileName.isEmpty())
    {
        QString file1 = FileName;
        QString file = FileName.split("//").last();
        currentFileName[0] = file1.remove(file);
        QSqlQuery query;
        query.exec("delete from WALLPAPER_DATA");
        query.exec(QString("insert into WALLPAPER_DATA values('%1')").arg(FileName));
        ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:5px;border-image: url(%1);}").arg(FileName));
    }
}
void Widget::action6_slot()//设置  关于
{ListFocus();

QMessageBox::about(this,("关于"),(
                                     "名称 : 我的音乐                         \n"
                                     "作者 : 邓鹏飞                           \n"
                                     "介绍 : 我的音乐是个界面简洁,具有添加,播放,列表搜索,\n"
                                     "删除，播放记录，多选，清空列表，该表播放模式等基础功能,用户可按喜好设置皮肤,窗体透明度,\n"
                                     "使界面更加绚丽,支持右键菜单和列表菜单和快捷键,使用户操作更便利,\n"
                                     "极简模式,可以进行基础的播放暂停等功能,缩小窗口体积,使播放器可玩性更高\n"));



}
void Widget::action7_slot()//设置菜单  使用
{QMessageBox::about(this,("使用"),("右键 : 菜单栏               Esc : 退出程序\n"
                                     "双击 : 切换至极简模式         Ctrl-- : 透明度减\n"
                                     "空格 : 播放暂停              Ctrl++ : 透明度加\n"
                                     "向右键/数字键6 : 下一首       Ctrl+Q : 退出\n"
                                     "向左键/数字键4 : 上一首       Ctrl+V : 清除所有列表\n"
                                     "A : 切换列表                Ctrl+O : 添加至所有列表\n"
                                     "D : 切换列表                Ctrl+A : 添加至我喜欢列表\n"
                                     "W : 增加音量                Ctrl+Z : 添加至我的收藏\n"
                                     "S : 减少音量                Ctrl+X : 自定义皮肤\n"
                                     "Q : 定位                   Ctrl+M : 清除所有歌曲列表\n"
                                     "E : 切换播放模式             Ctrl+N : 清除我喜欢列表\n"
                                     "R : 添加我喜欢              Ctrl+B : 清除我的收藏\n"
                                     "X : 多选/取消多选                              .\n"));

ListFocus();
}
void Widget::action8_slot()//主窗口右键菜单 关闭
{

  QCoreApplication::quit();

}
void Widget::action9_slot()//主窗口右键菜单 播放下一曲
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
    ListFocus();
    if(music->playlist()==playlist)
     {
        ui->stackedWidget->setCurrentIndex(0);
        pushbuttonstyle();
        int currentIndex;
        if(playlist->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
        currentIndex=playlist->currentIndex();
        if(++currentIndex==playlist->mediaCount())
        {
            currentIndex=0;
        }

        }

         playlist->setCurrentIndex(currentIndex);
         if(list1[currentIndex]==0){
             QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(currentIndex)->text());
             myitem->setToolTip(ui->listWidget_3->item(currentIndex)->text());
             ui->listWidget_5->addItem(myitem);
         playlist_4->addMedia(QUrl::fromLocalFile(FilePath[currentIndex]));        
         map.push_back(currentIndex);
         list1[currentIndex]++;
         }
         else
         {
             list1[currentIndex]++;
         }
    }
    else if(music->playlist()==playlist_2)
    {
        ui->stackedWidget->setCurrentIndex(1);
        pushbuttonstyle_2();
        int currentIndex;
        if(playlist_2->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist_2->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
        currentIndex=playlist_2->currentIndex();

        if(++currentIndex==playlist_2->mediaCount())
        {
            currentIndex=0;

        }

        }
        playlist_2->setCurrentIndex(currentIndex);
    }
    else if(music->playlist()==playlist_3)
    {

        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        int currentIndex;
        if(playlist_3->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist_3->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
         currentIndex=playlist_3->currentIndex();

        if(++currentIndex==playlist_3->mediaCount())
        {
            currentIndex=0;

        }

        }
        playlist_3->setCurrentIndex(currentIndex);

    }
    else
    {
        ui->stackedWidget->setCurrentIndex(4);
        pushbuttonstyle_5();
        int currentIndex;
        if(playlist_4->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist_4->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
         currentIndex=playlist_4->currentIndex();

        if(++currentIndex==playlist_4->mediaCount())
        {
            currentIndex=0;

        }

        }
        playlist_4->setCurrentIndex(currentIndex);
    }
    music->play();
}
void Widget::action10_slot()//主窗口右键菜单 播放上一曲
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
ListFocus();
    if(music->playlist()==playlist)
    {
        ui->stackedWidget->setCurrentIndex(0);
        pushbuttonstyle();
        int currentIndex;
        if(playlist->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist->mediaCount();
            currentIndex=qrand()%row;

        }
        else
        {
        currentIndex=playlist->currentIndex();

        if(--currentIndex<0)
        {

            currentIndex=0;


        }

        }
       playlist->setCurrentIndex(currentIndex);
       if(list1[currentIndex]==0){
           QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(currentIndex)->text());
           myitem->setToolTip(ui->listWidget_3->item(currentIndex)->text());

       ui->listWidget_5->addItem(myitem);
       playlist_4->addMedia(QUrl::fromLocalFile(FilePath[currentIndex]));
       map.push_back(currentIndex);
       list1[currentIndex]++;
       }
       else
       {
           list1[currentIndex]++;
       }
    }
    else if(music->playlist()==playlist_2)
    {

        ui->stackedWidget->setCurrentIndex(1);
        pushbuttonstyle_2();
         int currentIndex;

         if(playlist_2->playbackMode()==QMediaPlaylist::Random)
         {

             int row=playlist_2->mediaCount();
             currentIndex=qrand()%row;
         }
         else
         {
        currentIndex=playlist_2->currentIndex();
        if(--currentIndex<0)
        {
            currentIndex=0;
        }
         }
        playlist_2->setCurrentIndex(currentIndex);
    }
    else if(music->playlist()==playlist_3)
    {
        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
         int currentIndex;
         if(playlist_3->playbackMode()==QMediaPlaylist::Random)
         {
             int row=playlist_3->mediaCount();
             currentIndex=qrand()%row;
         }
           else
         {
        currentIndex=playlist_3->currentIndex();

        if(--currentIndex<0)
        {
            currentIndex=0;
        }
         }
        playlist_3->setCurrentIndex(currentIndex);
    }
    else
    {    ui->stackedWidget->setCurrentIndex(4);
        pushbuttonstyle_5();
         int currentIndex;
         if(playlist_4->playbackMode()==QMediaPlaylist::Random)
         {
             int row=playlist_4->mediaCount();
             currentIndex=qrand()%row;
         }
           else
         {
        currentIndex=playlist_4->currentIndex();

        if(--currentIndex<0)
        {
            currentIndex=0;
        }
         }
        playlist_4->setCurrentIndex(currentIndex);
        
    }
     music->play();
}
void Widget::action11_slot()//暂停
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
ListFocus();
       music->pause();


}
void Widget::action11_1_slot()//播放
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
ListFocus();
    music->play();
}
void Widget::action12_1_slot()//主窗口右键菜单 顺序播放
{

    ListFocus();
    ui->pushButton_9->setIcon(QIcon(":/image/image/image/loop.png"));
    ui->pushButton_9->setStyleSheet(LoopStyle());
    ui->pushButton_9->setToolTip(("顺序播放"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist_2->setPlaybackMode(QMediaPlaylist::Loop);
    playlist_3->setPlaybackMode(QMediaPlaylist::Loop);

}
void Widget::action12_2_slot()//主窗口右键菜单 随机播放
{

ListFocus();
    ui->pushButton_9->setIcon(QIcon(":/image/image/image/play-random.png"));
    ui->pushButton_9->setToolTip(("随机播放"));
    ui->pushButton_9->setStyleSheet(RandomStyle());
    playlist->setPlaybackMode(QMediaPlaylist::Random);
    playlist_2->setPlaybackMode(QMediaPlaylist::Random);
    playlist_3->setPlaybackMode(QMediaPlaylist::Random);
}
void Widget::action12_3_slot()//主窗口右键菜单 单曲循环
{

    ListFocus();
    ui->pushButton_9->setIcon(QIcon(":/image/image/image/loop-one.png"));
    ui->pushButton_9->setToolTip(("单曲循环"));
    ui->pushButton_9->setStyleSheet(LoopOneStyle());
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    playlist_2->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    playlist_3->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

}

void Widget::on_pushButton_2_clicked()//播放/暂停
{

    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
    ListFocus();
   if(music->state()==QMediaPlayer::PlayingState)
    {
       ui->pushButton_2->setIcon(QIcon(":/image/image/image/pase.png"));
       ui->pushButton_2->setStyleSheet(PaseStyle());
       ui->pushButton_2->setToolTip(("暂停"));
       pause->setToolTip(("暂停"));
       pause->setIcon(QIcon(":/image/image/bf13.png"));
       music->pause();



    }
    else
    {
       ui->pushButton_2->setIcon(QIcon(":/image/image/image/play.png"));
       ui->pushButton_2->setStyleSheet(PlayStyle());
       ui->pushButton_2->setToolTip(("播放"));
       pause->setToolTip(("播放"));
       pause->setIcon(QIcon(":/image/image/zt13.png"));
       music->play();

    }
}

void Widget::on_pushButton_3_clicked()//播放下一曲
{

    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
    ListFocus();

    if(music->playlist()==playlist)
     {
        ui->stackedWidget->setCurrentIndex(0);
        pushbuttonstyle();
        int currentIndex;
        if(playlist->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
        currentIndex=playlist->currentIndex();

        if(++currentIndex==playlist->mediaCount())
        {
            currentIndex=0;

        }

        }
         ui->listWidget_3->scrollToItem(ui->listWidget_3->item(currentIndex));
         playlist->setCurrentIndex(currentIndex);
         if(list1[currentIndex]==0){
             QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(currentIndex)->text());
             myitem->setToolTip(ui->listWidget_3->item(currentIndex)->text());

         ui->listWidget_5->addItem(myitem);
         playlist_4->addMedia(QUrl::fromLocalFile(FilePath[currentIndex]));
         map.push_back(currentIndex);
         list1[currentIndex]++;
         }
         else
         {
             list1[currentIndex]++;
         }

    }
    else if(music->playlist()==playlist_2)
    {
        ui->stackedWidget->setCurrentIndex(1);
        pushbuttonstyle_2();
        int currentIndex;
        if(playlist_2->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist_2->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
        currentIndex=playlist_2->currentIndex();

        if(++currentIndex==playlist_2->mediaCount())
        {
            currentIndex=0;

        }

        }
        ui->listWidget_2->scrollToItem(ui->listWidget_2->item(currentIndex));
        playlist_2->setCurrentIndex(currentIndex);
    }
    else if(music->playlist()==playlist_3)
    {

        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        int currentIndex;
        if(playlist_3->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist_3->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
         currentIndex=playlist_3->currentIndex();

        if(++currentIndex==playlist_3->mediaCount())
        {
            currentIndex=0;

        }

        }
        ui->listWidget->scrollToItem(ui->listWidget->item(currentIndex));
        playlist_3->setCurrentIndex(currentIndex);

    }
    else
    {    ui->stackedWidget->setCurrentIndex(4);
        pushbuttonstyle_5();
         int currentIndex;
         if(playlist_4->playbackMode()==QMediaPlaylist::Random)
         {
             int row=playlist_4->mediaCount();
             currentIndex=qrand()%row;
         }
           else
         {
        currentIndex=playlist_4->currentIndex();

        if(--currentIndex<0)
        {
            currentIndex=0;
        }
         }
         ui->listWidget_4->scrollToItem(ui->listWidget_4->item(currentIndex));
        playlist_4->setCurrentIndex(currentIndex);
        
    }
    music->play();

}

void Widget::on_pushButton_4_clicked()//播放上一曲
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
      ListFocus();

    if(music->playlist()==playlist)
    {
        ui->stackedWidget->setCurrentIndex(0);
        pushbuttonstyle();
        int currentIndex;
        if(playlist->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist->mediaCount();
            currentIndex=qrand()%row;

        }
        else
        {
        currentIndex=playlist->currentIndex();

        if(--currentIndex<0)
        {

            currentIndex=0;


        }

        }
       ui->listWidget_3->scrollToItem(ui->listWidget_3->item(currentIndex));
       playlist->setCurrentIndex(currentIndex);
       if(list1[currentIndex]==0){
           QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(currentIndex)->text());
           myitem->setToolTip(ui->listWidget_3->item(currentIndex)->text());

       ui->listWidget_5->addItem(myitem);
       playlist_4->addMedia(QUrl::fromLocalFile(FilePath[currentIndex]));
       map.push_back(currentIndex);
       list1[currentIndex]++;
       }
       else
       {
           list1[currentIndex]++;
       }
    }
    else if(music->playlist()==playlist_2)
    {

        ui->stackedWidget->setCurrentIndex(1);
        pushbuttonstyle_2();
         int currentIndex;

         if(playlist_2->playbackMode()==QMediaPlaylist::Random)
         {

             int row=playlist_2->mediaCount();
             currentIndex=qrand()%row;
         }
         else
         {
        currentIndex=playlist_2->currentIndex();
        if(--currentIndex<0)
        {
            currentIndex=0;
        }
         }
         ui->listWidget_2->scrollToItem(ui->listWidget_2->item(currentIndex));
        playlist_2->setCurrentIndex(currentIndex);
    }
    else if(music->playlist()==playlist_3)
    {
        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
         int currentIndex;
         if(playlist_3->playbackMode()==QMediaPlaylist::Random)
         {
             int row=playlist_3->mediaCount();
             currentIndex=qrand()%row;
         }
           else
         {
        currentIndex=playlist_3->currentIndex();

        if(--currentIndex<0)
        {
            currentIndex=0;
        }
         }
           ui->listWidget->scrollToItem(ui->listWidget->item(currentIndex));
        playlist_3->setCurrentIndex(currentIndex);
    }
    else
    {    ui->stackedWidget->setCurrentIndex(4);
        pushbuttonstyle_5();
         int currentIndex;
         if(playlist_4->playbackMode()==QMediaPlaylist::Random)
         {
             int row=playlist_4->mediaCount();
             currentIndex=qrand()%row;
         }
           else
         {
        currentIndex=playlist_4->currentIndex();

        if(--currentIndex<0)
        {
            currentIndex=0;
        }
         }
         ui->listWidget_4->scrollToItem(ui->listWidget_4->item(currentIndex));
        playlist_4->setCurrentIndex(currentIndex);
        
    }
     music->play();
}
void Widget::updatalistwidget_3(int value)//更新listWidget_3
{

    if(ui->listWidget_3->selectionMode()==QListWidget::SingleSelection)
    {
        ui->listWidget_3->item(value)->setSelected(true);
        int currentIndex = value;
        if(list1[currentIndex]==0){
            QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(currentIndex)->text());
            myitem->setToolTip(ui->listWidget_3->item(currentIndex)->text());

        ui->listWidget_5->addItem(myitem);
       playlist_4->addMedia(QUrl::fromLocalFile(FilePath[currentIndex]));
        map.push_back(currentIndex);
        list1[currentIndex]++;
        }
        else
        {
            list1[currentIndex]++;
        }
    }

}
void Widget::updatalistwidget_2(int value)//更新listWidget_2
{

 if(ui->listWidget_2->selectionMode()==QListWidget::SingleSelection)
   ui->listWidget_2->item(value)->setSelected(true);


}
void Widget::updatalistwidget(int value)//更新listWidget
{

 if(ui->listWidget->selectionMode()==QListWidget::SingleSelection)
    ui->listWidget->item(value)->setSelected(true);

}

void Widget::on_listWidget_3_doubleClicked(const QModelIndex &index)//双击播放playlist 本地音乐列表
{

    if(ui->listWidget_3->selectionMode()==QListWidget::SingleSelection)
    {
    music->setPlaylist(playlist);
    int currentIndex = index.row();
    playlist->setCurrentIndex(currentIndex);
    music->play();
    if(list1[currentIndex]==0){
        QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(currentIndex)->text());
        myitem->setToolTip(ui->listWidget_3->item(currentIndex)->text());

    ui->listWidget_5->addItem(myitem);
   playlist_4->addMedia(QUrl::fromLocalFile(FilePath[currentIndex]));
    map.push_back(currentIndex);
    list1[currentIndex]++;
    }
    else
    {
        list1[currentIndex]++;
    }
    }
}
void Widget::music_stateChang(QMediaPlayer::State state)//播放状态改变
{


    if(state==QMediaPlayer::PlayingState)
    {
        ui->pushButton_2->setIcon(QIcon(":/image/image/image/play.png"));
        ui->pushButton_2->setToolTip(("播放"));
        ui->pushButton_2->setStyleSheet(PlayStyle());
        pause->setToolTip(("播放"));
        pause->setIcon(QIcon(":/image/image/zt13.png"));

        TaskProgress->show();
        TaskProgress->resume();

    }
    else
    {

        ui->pushButton_2->setIcon(QIcon(":/image/image/image/pase.png"));
        ui->pushButton_2->setToolTip(("暂停"));
        ui->pushButton_2->setStyleSheet(PaseStyle());
        pause->setToolTip(("暂停"));
        pause->setIcon(QIcon(":/image/image/bf13.png"));

        TaskProgress->show();
        TaskProgress->pause();
    }
}

void Widget::on_pushButton_15_clicked()//隐藏stackedWidget
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
   QPropertyAnimation *AnimationForLabel3 = new QPropertyAnimation(ui->label_3,"geometry");
   QPropertyAnimation *AnimationForLabel4 = new QPropertyAnimation(ui->label_4,"geometry");
   QPropertyAnimation *AnimationForLabel = new QPropertyAnimation(ui->label,"geometry");
   QPropertyAnimation *AnimationForPushButton = new QPropertyAnimation(ui->pushButton_15,"geometry");


    QPropertyAnimation *AnimationForPushButton1 = new QPropertyAnimation(ui->pushButton_10,"geometry");
    QPropertyAnimation *AnimationForPushButton2 = new QPropertyAnimation(ui->pushButton_11,"geometry");
    QPropertyAnimation *AnimationForPushButton3 = new QPropertyAnimation(ui->pushButton_12,"geometry");
    QPropertyAnimation *AnimationForPushButton4 = new QPropertyAnimation(ui->pushButton_22,"geometry");

   // QPropertyAnimation *AnimationForStactWidget = new QPropertyAnimation(ui->stackedWidget,"windowOpacity");

    AnimationForLabel3->setDuration(1000);
    AnimationForLabel4->setDuration(1000);
    AnimationForLabel->setDuration(1000);
    //AnimationForStactWidget->setDuration(500);
    AnimationForPushButton->setDuration(900);
    AnimationForPushButton1->setDuration(500);
    AnimationForPushButton2->setDuration(600);
    AnimationForPushButton3->setDuration(700);
    AnimationForPushButton4->setDuration(800);
    if(ui->stackedWidget->isHidden())
    {ListFocus();
        ui->pushButton_15->setIcon(QIcon(":/image/image/image/left.png"));
        ui->pushButton_15->setStyleSheet(HideListStyle());
        ui->pushButton_15->setToolTip(("隐藏播放列表"));
        ui->stackedWidget->show();



//        ui->pushButton_10->show();
//        ui->pushButton_11->show();
//        ui->pushButton_12->show();
//        ui->pushButton_22->show();


//        AnimationForStactWidget->setKeyValueAt(0,0);
//        AnimationForStactWidget->setKeyValueAt(1,1);
//        AnimationForStactWidget->setEasingCurve(QEasingCurve::InBounce);

        AnimationForLabel->setStartValue(QRect(250,600,510,32));
        AnimationForLabel->setEndValue(QRect(370,600,510,32));
        AnimationForLabel->setEasingCurve(QEasingCurve::InBounce);

        AnimationForLabel3->setStartValue(QRect(200,390,510,32));
        AnimationForLabel3->setEndValue(QRect(400,390,510,32));
        AnimationForLabel3->setEasingCurve(QEasingCurve::InBounce);

        AnimationForLabel4->setStartValue(QRect(600,450,450,32));
        AnimationForLabel4->setEndValue(QRect(670,450,450,32));
        AnimationForLabel4->setEasingCurve(QEasingCurve::InBounce);

        AnimationForPushButton->setStartValue(QRect(10,60,32,32));
        AnimationForPushButton->setEndValue(QRect(320,60,32,32));
        AnimationForPushButton->setEasingCurve(QEasingCurve::InBounce);


        AnimationForPushButton1->setStartValue(QRect(-32,60,32,32));
        AnimationForPushButton1->setEndValue(QRect(10,60,32,32));
        AnimationForPushButton1->setEasingCurve(QEasingCurve::InBounce);



        AnimationForPushButton2->setStartValue(QRect(-32,60,32,32));
        AnimationForPushButton2->setEndValue(QRect(80,60,32,32));
        AnimationForPushButton2->setEasingCurve(QEasingCurve::InBounce);

        AnimationForPushButton3->setStartValue(QRect(-32,60,32,32));
        AnimationForPushButton3->setEndValue(QRect(160,60,32,32));
        AnimationForPushButton3->setEasingCurve(QEasingCurve::InBounce);

        AnimationForPushButton4->setStartValue(QRect(-32,60,32,32));
        AnimationForPushButton4->setEndValue(QRect(240,60,32,32));
        AnimationForPushButton4->setEasingCurve(QEasingCurve::InBounce);


        AnimationForLabel->start();
        AnimationForLabel3->start();
        AnimationForLabel4->start();
        AnimationForPushButton->start();
        AnimationForPushButton1->start();
        AnimationForPushButton2->start();
        AnimationForPushButton3->start();
        AnimationForPushButton4->start();



    }
    else
    {

        ui->pushButton_15->setIcon(QIcon(":/image/image/image/right.png"));
        ui->pushButton_15->setToolTip(("显示播放列表"));
        ui->pushButton_15->setStyleSheet(ShowListStyle());
         ui->stackedWidget->hide();
//        ui->pushButton_10->hide();
//        ui->pushButton_11->hide();
//        ui->pushButton_12->hide();
//        ui->pushButton_22->hide();

//        AnimationForStactWidget->setKeyValueAt(0,1);
//        AnimationForStactWidget->setKeyValueAt(1,0);
//        AnimationForStactWidget->setEasingCurve(QEasingCurve::InBounce);

        AnimationForLabel->setStartValue(QRect(370,600,510,32));
        AnimationForLabel->setEndValue(QRect(250,600,510,32));
        AnimationForLabel->setEasingCurve(QEasingCurve::InBounce);


        AnimationForLabel3->setStartValue(QRect(400,390,510,32));
         AnimationForLabel3->setEndValue(QRect(200,390,510,32));
        AnimationForLabel3->setEasingCurve(QEasingCurve::InBounce);


        AnimationForLabel4->setStartValue(QRect(670,450,450,32));
        AnimationForLabel4->setEndValue(QRect(600,450,450,32));
        AnimationForLabel4->setEasingCurve(QEasingCurve::InBounce);


        AnimationForPushButton->setStartValue(QRect(320,60,32,32));
        AnimationForPushButton->setEndValue(QRect(10,60,32,32));
        AnimationForPushButton->setEasingCurve(QEasingCurve::InBounce);

        AnimationForPushButton1->setStartValue(QRect(10,60,32,32));
        AnimationForPushButton1->setEndValue(QRect(-32,60,32,32));
        AnimationForPushButton1->setEasingCurve(QEasingCurve::InBounce);



        AnimationForPushButton2->setStartValue(QRect(80,60,32,32));
        AnimationForPushButton2->setEndValue(QRect(-32,60,32,32));
        AnimationForPushButton2->setEasingCurve(QEasingCurve::InBounce);

        AnimationForPushButton3->setStartValue(QRect(160,60,32,32));
        AnimationForPushButton3->setEndValue(QRect(-32,60,32,32));
        AnimationForPushButton3->setEasingCurve(QEasingCurve::InBounce);

        AnimationForPushButton4->setStartValue(QRect(240,60,32,32));
        AnimationForPushButton4->setEndValue(QRect(-32,60,32,32));
        AnimationForPushButton4->setEasingCurve(QEasingCurve::InBounce);

        AnimationForLabel->start();
        AnimationForLabel3->start();
        AnimationForLabel4->start();
        AnimationForPushButton->start();
        AnimationForPushButton1->start();
        AnimationForPushButton2->start();
        AnimationForPushButton3->start();
        AnimationForPushButton4->start();

    }
}

void Widget::on_pushButton_9_clicked()//播放模式
{

ListFocus();
    if(playlist->playbackMode()==QMediaPlaylist::Loop)
    {

        ui->pushButton_9->setIcon(QIcon(":/image/image/image/play-random.png"));
        ui->pushButton_9->setStyleSheet(RandomStyle());
        ui->pushButton_9->setToolTip(("随机播放"));
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        playlist_2->setPlaybackMode(QMediaPlaylist::Random);
        playlist_3->setPlaybackMode(QMediaPlaylist::Random);
    }
    else if(playlist->playbackMode()==QMediaPlaylist::Random)
    {
        ui->pushButton_9->setIcon(QIcon(":/image/image/image/loop-one.png"));
        ui->pushButton_9->setStyleSheet(LoopOneStyle());
        ui->pushButton_9->setToolTip(("单曲循环"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        playlist_2->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        playlist_3->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);


    }
    else if(playlist->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
    {
        ui->pushButton_9->setIcon(QIcon(":/image/image/image/loop.png"));
        ui->pushButton_9->setStyleSheet(LoopStyle());
        ui->pushButton_9->setToolTip(("顺序播放"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        playlist_2->setPlaybackMode(QMediaPlaylist::Loop);
        playlist_3->setPlaybackMode(QMediaPlaylist::Loop);

    }

}

void Widget::on_listWidget_2_doubleClicked(const QModelIndex &index)//双击播放playlist_2 我喜欢列表
{

if(ui->listWidget_2->selectionMode()==QListWidget::SingleSelection)
      {
      music->setPlaylist(playlist_2);
      int row = index.row();
      playlist_2->setCurrentIndex(row);
      music->play();
}


}


void Widget::on_listWidget_doubleClicked(const QModelIndex &index)//双击播放playlist_3 我的收藏
{

    if(ui->listWidget->selectionMode()==QListWidget::SingleSelection)
       {
       music->setPlaylist(playlist_3);
       int row = index.row();
       playlist_3->setCurrentIndex(row);

       music->play();
      }


}
void Widget::on_pushButton_7_clicked()//歌曲定位
{


    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }

    if(music->playlist()==playlist)
    {
        if(ui->listWidget_3->count()==0){
            return;
        }
        else{
        ui->stackedWidget->setCurrentIndex(0);
        ui->listWidget_3->setFocus();
        pushbuttonstyle();
        if(ui->listWidget_3->selectionMode()==QListWidget::SingleSelection)
       {
            ui->listWidget_3->item(playlist->currentIndex())->setSelected(true);
            ui->listWidget_3->scrollToItem(ui->listWidget_3->item(playlist->currentIndex()));
       }
        }
    }
    else if(music->playlist()==playlist_2)
    {
if(ui->listWidget_2->count()==0){
return ;
}
else{
        ui->stackedWidget->setCurrentIndex(1);
         ui->listWidget_2->setFocus();
        pushbuttonstyle_2();
        if(ui->listWidget_2->selectionMode()==QListWidget::SingleSelection)
       { ui->listWidget_2->item(playlist_2->currentIndex())->setSelected(true);
         ui->listWidget_2->scrollToItem(ui->listWidget_2->item(playlist_2->currentIndex()));
        }
}

    }
    else if(music->playlist()==playlist_3)
    {

if(ui->listWidget->count()==0){
return;
}
else{
        ui->stackedWidget->setCurrentIndex(2);
        ui->listWidget->setFocus();
        pushbuttonstyle_3();
        if(ui->listWidget->selectionMode()==QListWidget::SingleSelection)
        {
            ui->listWidget->item(playlist_3->currentIndex())->setSelected(true);
            ui->listWidget->scrollToItem(ui->listWidget->item(playlist_3->currentIndex()));

        }
}
    }
    else
    {
        if(ui->listWidget_5->count()==0){
        return;
        }
        else{
                ui->stackedWidget->setCurrentIndex(4);
                ui->listWidget_5->setFocus();
                pushbuttonstyle_5();
           
                    ui->listWidget_5->item(playlist_4->currentIndex())->setSelected(true);
                    ui->listWidget_5->scrollToItem(ui->listWidget_5->item(playlist_4->currentIndex()));
        
                
        }
    }
}
void Widget::mousePressEvent(QMouseEvent *event)//拖拽 移动窗口
{

ListFocus();
        offset=event->globalPos()-pos();
        event->accept();
        ui->verticalSlider->hide();
        setFocus();
        if(event->button()==Qt::LeftButton)
        setCursor(Qt::OpenHandCursor);


}
void Widget::mouseMoveEvent(QMouseEvent *event)//拖拽 移动窗口
{
ListFocus();
 move(event->globalPos()-offset);
        event->accept();
        setCursor(Qt::ClosedHandCursor);


}
void Widget::mouseReleaseEvent(QMouseEvent *event)//拖拽 移动窗口
{
ListFocus();
    offset=QPoint();
    event->accept();
    setCursor(Qt::ArrowCursor);

}
void Widget::mouseDoubleClickEvent(QMouseEvent *)//双击切换至极简模式
{
    setCursor(Qt::ArrowCursor);

    hide();
    int i;
    if(music->playlist()==playlist)
    {
        i=0;
    }
    else if(music->playlist()==playlist_2)
    {
        i=1;
    }
    else if(music->playlist()==playlist_3)
    {
        i=2;
    }
    else
      {
        i=3;
      }
    Music->setPlaylist(music->playlist(),music->playlist()->currentIndex(),music->position(),music->volume(),music->state(),playlist->playbackMode(),i);
    music->pause();
    if(Music->exec()==Dialog::Accepted)
    {
      ListFocus();
      show();
    }

}

void Widget::contextMenuEvent(QContextMenuEvent *)//主窗口右键菜单
{

ListFocus();
    menu = new QMenu(this);
    menu->setStyleSheet(
           MenuStyle()

            );
    menu->addAction(add);
    menu->addAction(action9);
    menu->addAction(action10);
    if(music->state()==QMediaPlayer::PlayingState)

    {
        menu->addAction(action11);

    }
    else
    {

        menu->addAction(action11_1);
    }
    menu->addAction(ClearALL_3);
    menu->addAction(action12);
    menu->addAction(action5);
    menu->addAction(ClearALL);
    menu->addAction(location);
    menu->addAction(detila);
    menu->addAction(action13);
    menu->exec(QCursor::pos());

}

void Widget::on_pushButton_17_clicked()//关闭
{
    QCoreApplication::quit();
}

void Widget::on_pushButton_16_clicked()//最小化
{ListFocus();
    showMinimized();

}

void Widget::on_pushButton_8_clicked()//隐藏verticalSlider
{
  ListFocus();

if(ui->verticalSlider->isHidden())
        ui->verticalSlider->show();
else
{
    ui->verticalSlider->hide();
}

}
void Widget::changeVolume(int values)//改变音量
{
    if(values==0)
    {

        ui->pushButton_8->setIcon(QIcon(":/image/image/image/none-music.png"));
        ui->pushButton_8->setStyleSheet(NoVoiceStyle());
    }
    else
    {
        ui->pushButton_8->setIcon(QIcon(":/image/image/music-voice.png"));
        ui->pushButton_8->setStyleSheet(VoiceStyle());

    }
    music->setVolume(values);

}

void Widget::on_listWidget_3_customContextMenuRequested(const QPoint &pos)//listWidget_3右键菜单 本地音乐列表
{
    if(ui->listWidget_3->itemAt(pos)==NULL)
    {
        return ;
    }
QMenu *Menu=new QMenu(this);
Menu->setStyleSheet(
       MenuStyle()

            );
QAction *Action1=new QAction(this);//播放
QAction *Action1_1=new QAction(this);//暂停
QAction *Action2=new QAction(this);//添加至我喜欢
QAction *Action4=new QAction(this);//添加至我的收藏
QAction *Action3=new QAction(this);//多选
QAction *Action5=new QAction(this);//取消多选
QAction *Action7=new QAction(this);//删除
QAction *Action8=new QAction(this);//歌曲信息
Action1->setIcon(QIcon(":/image/image/zt13.png"));
Action1->setText(("播放"));
Action1_1->setIcon(QIcon(":/image/image/bofang1.png"));
Action1_1->setText(("暂停"));
Action2->setIcon(QIcon(":/image/image/like_outline_32px_1170275_easyicon.net.png"));
Action2->setText(("添加至我喜欢"));
Action4->setIcon(QIcon(":/image/image/list_32px_1142913_easyicon.net.png"));
Action4->setText(("添加至我的收藏"));
Action7->setIcon(QIcon(":/image/image/duoxuan.png"));
Action7->setText(("多选"));
Action8->setIcon(QIcon(":/image/image/quxiao.png"));
Action8->setText(("取消多选"));
Action3->setIcon(QIcon(":/image/image/delete_32px_1168909_easyicon.net.png"));
Action3->setText(("删除"));
Action5->setIcon(QIcon(":/image/image/inf.png"));
Action5->setText(("歌曲信息"));
connect(Action1,&QAction::triggered,this,&Widget::Action1_slot);
connect(Action1_1,&QAction::triggered,this,&Widget::action11_slot);
connect(Action2,&QAction::triggered,this,&Widget::Action2_slot);
connect(Action4,&QAction::triggered,this,&Widget::Action4_slot);
connect(Action3,&QAction::triggered,this,&Widget::Action3_slot);
connect(Action5,&QAction::triggered,this,&Widget::Action5_slot);
connect(Action7,&QAction::triggered,this,&Widget::Action7_slot);
connect(Action8,&QAction::triggered,this,&Widget::Action8_slot);
    if(ui->listWidget_3->selectionMode()==QListWidget::SingleSelection)
    {
        if(music->playlist()==playlist)
        {
         if(ui->listWidget_3->currentIndex().row()==playlist->currentIndex())
         {
        if(music->state()==QMediaPlayer::PlayingState)
        {
            Menu->addAction(Action1_1);
        }
        else
        {
            Menu->addAction(Action1);

        }
          }
         else
         {

                Menu->addAction(Action1);
         }

        }
        else
        {
               Menu->addAction(Action1);
        }

    Menu->addAction(Action2);
    Menu->addAction(Action4);
    Menu->addAction(Action7);
    Menu->addAction(Action5);
    Menu->addAction(Action3);
    }
    else if(ui->listWidget_3->selectionMode()==QListWidget::MultiSelection)
    {
          Menu->addAction(Action2);
          Menu->addAction(Action4);
          Menu->addAction(Action8);
          Menu->addAction(Action3);
    }
    Menu->exec(QCursor::pos());
    delete Menu;
    delete Action1;
    delete Action2;
    delete Action3;
    delete Action4;
    delete Action5;
    delete Action7;
    delete Action8;
    delete Action1_1;

}
void Widget::Action1_slot()//listWidget_3右键菜单 播放歌曲
{

if(music->playlist()==playlist)
{

   if(ui->listWidget_3->currentIndex().row()==playlist->currentIndex())
   {

       music->play();

   }
   else
   {

        playlist->setCurrentIndex(ui->listWidget_3->currentIndex().row());
        music->play();
   }
   int currentIndex = ui->listWidget_3->currentIndex().row();
   if(list1[currentIndex]==0){
       QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(currentIndex)->text());
       myitem->setToolTip(ui->listWidget_3->item(currentIndex)->text());

   ui->listWidget_5->addItem(myitem);
   playlist_4->addMedia(QUrl::fromLocalFile(FilePath[currentIndex]));
   map.push_back(currentIndex);
   list1[currentIndex]++;
   }
   else
   {
       list1[currentIndex]++;
   }


}
    else
    {
    music->setPlaylist(playlist);
    playlist->setCurrentIndex(ui->listWidget_3->currentIndex().row());
    int currentIndex = ui->listWidget_3->currentIndex().row();
    if(list1[currentIndex]==0){
        QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(currentIndex)->text());
        myitem->setToolTip(ui->listWidget_3->item(currentIndex)->text());

    ui->listWidget_5->addItem( myitem);
    playlist_4->addMedia(QUrl::fromLocalFile(FilePath[currentIndex]));
    map.push_back(currentIndex);
    list1[currentIndex]++;
    }
    else
    {
        list1[currentIndex]++;
    }
    music->play();
    }

}
void Widget::Action2_slot()//listWidget_3右键菜单 添加至我喜欢
{
    if(ui->listWidget_3->selectionMode()==QListWidget::SingleSelection)
    {
    model->setTable("LocalMusic");
    model->select();
    int row=ui->listWidget_3->currentIndex().row();
    int flag=model->data(model->index(row,3)).toInt();
    if(flag==0)
    {
    QString Text=ui->listWidget_3->item(row)->text();
    QListWidgetItem *ITEMM=new QListWidgetItem;
    ITEMM->setIcon(QIcon(":/image/image/like_outline_32px_1101681_easyicon.net.png"));
    ITEMM->setText(QString("%1").arg(Text));
    ITEMM->setToolTip(Text);


    ui->listWidget_2->addItem(ITEMM);

    QSqlQuery query;
    playlist_2->addMedia(playlist->media(row));
    model->setTable("LocalMusic");
    model->select();
    QString MusicName=model->data(model->index(row,1)).toString();
    QString FileName=model->data(model->index(row,2)).toString();
    model->setTable("LocalMusic");
    model->select();
    model->setData(model->index(row,3),1);
    model->submitAll();
    query.exec("select * from LikeMusic");
    query.exec(QString("insert into LikeMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(MusicName).arg(FileName));
    ui->stackedWidget->setCurrentIndex(1);
    pushbuttonstyle_2();
    if(music->playlist()==playlist)
    {

    if(playlist->currentIndex()==row)
    {
    ui->pushButton_14->setIcon(QIcon(":/image/image/image/Ilike1.png"));
    ui->pushButton_14->setStyleSheet(Ilike1Style());
    ui->pushButton_14->setToolTip(("我喜欢"));
    }

    }
    }
    else
    {

     QMessageBox::information(this,("提示"),("该歌曲已添加                              ."),QMessageBox::Yes);

    }
    }
    else if(ui->listWidget_3->selectionMode()==QListWidget::MultiSelection)
    {
        ui->stackedWidget->setCurrentIndex(1);
        pushbuttonstyle_2();
        model->setTable("LocalMusic");
        model->select();
        QList<QListWidgetItem*> items;
        items=ui->listWidget_3->selectedItems();
        if(items.size()==0)
        {
            return;
        }
        QProgressDialog *progressdialog=new QProgressDialog(this);
        progressdialog->setWindowModality(Qt::WindowModal);
        progressdialog->setMinimumDuration(100);
        progressdialog->resize(400,120);
        progressdialog->setMinimumSize(400,120);
        progressdialog->setMaximumSize(400,120);
        progressdialog->setMinimumDuration(100);
        progressdialog->setWindowTitle(("添加至我喜欢"));
        progressdialog->setLabelText(("正在添加,请稍后."));
        QPushButton *button=new QPushButton(this);
        QPixmap pixmap;
        pixmap.load(":/image/image/58d4d135e7bce713bd501050.jpg");
        QPalette palette;
        palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(progressdialog->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        progressdialog->setPalette(palette);
        button->setStyleSheet("QPushButton{"

                              "background-color: rgba(122, 122, 122,100);"
                              "border-style:outset;"
                              "border-width: 1px;"
                              "border-radius: 10px;"
                              "border-color: rgba(122, 122, 122,100);"
                              "font: bold 14px;"
                              "color :rgba(0,0,0,100);"
                              "padding: 6px;"

                              "}"
                              "QPushButton:hover{"



                              "background-color: rgba(176, 58, 176,200);"
                              "color: rgba(0,0,0,200);"


                              "}"
                              "QPushButton:pressed{"


                                  "background-color:  rgba(255,255,255,150);"
                              "border-color:rgba(255,255,255,150);"
                              "border-style:inset;"
                              "color:rgba(0,0,0,100);"

                              "}");
        button->setText(("关闭"));
        progressdialog->setCancelButton(button);
        progressdialog->setRange(0,items.size()-1);
        progressdialog->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;background-color:rgba(255,255,255,150);}"
                                      "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}");

        for(int i=0;i<items.size();i++)
        {

            if(i==items.size()-1)
            {
                progressdialog->close();
            }
            if(!progressdialog->wasCanceled())
            {
                progressdialog->setValue(i);

            }
            else
            {
                progressdialog->close();
            }
            int row=ui->listWidget_3->row(items.at(i));
            int flag=model->data(model->index(row,3)).toInt();
            if(flag==0)
            {
            QString Text=ui->listWidget_3->item(row)->text();
            QListWidgetItem *ITEMM1=new QListWidgetItem;
            ITEMM1->setIcon(QIcon(":/image/image/like_outline_32px_1101681_easyicon.net.png"));
            ITEMM1->setText(QString("%1").arg(Text));
            ITEMM1->setToolTip(Text);

            ui->listWidget_2->addItem(ITEMM1);

            QSqlQuery query;
            playlist_2->addMedia(playlist->media(row));
            model->setTable("LocalMusic");
            model->select();
            QString MusicName=model->data(model->index(row,1)).toString();
            QString FileName=model->data(model->index(row,2)).toString();
            model->setTable("LocalMusic");
            model->select();
            model->setData(model->index(row,3),1);
            model->submitAll();
            query.exec("select * from LikeMusic");
            query.exec(QString("insert into LikeMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(MusicName).arg(FileName));
            if(music->playlist()==playlist)
            {

            if(playlist->currentIndex()==row)
            {
            ui->pushButton_14->setIcon(QIcon(":/image/image/image/Ilike1.png"));
            ui->pushButton_14->setStyleSheet(Ilike1Style());
            ui->pushButton_14->setToolTip(("我喜欢"));
            }

            }
            }

        }
delete button;

        ui->listWidget_3->setSelectionMode(QListWidget::SingleSelection);



    }
}
void Widget::Action4_slot()//listWidget_3右键菜单 添加至我的收藏
{


    if(ui->listWidget_3->selectionMode()==QListWidget::SingleSelection)
    {
        int row=ui->listWidget_3->currentIndex().row();
    QString Text=ui->listWidget_3->item(row)->text();
    QListWidgetItem *ITEMM1=new QListWidgetItem;
    ITEMM1->setIcon(QIcon(":/image/image/music_not_25.570093457944px_1171234_easyicon.net.png"));
    ITEMM1->setText(QString("%1").arg(Text));
    ITEMM1->setToolTip(Text);

    ui->listWidget->addItem(ITEMM1);

    model->setTable("LocalMusic");
    model->select();
    playlist_3->addMedia(playlist->media(row));
    QSqlQuery query;
    QString MusicName=model->data(model->index(row,1)).toString();
    QString FileName=model->data(model->index(row,2)).toString();

    query.exec("select * from  CollectMusic");
    query.exec(QString("insert into  CollectMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(MusicName).arg(FileName));
    ui->stackedWidget->setCurrentIndex(2);
    pushbuttonstyle_3();
    }
    else if(ui->listWidget_3->selectionMode()==QListWidget::MultiSelection)
    {
        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        QList<QListWidgetItem*> items;
        items=ui->listWidget_3->selectedItems();
        if(items.size()==0)
        {
            return ;
        }
        QProgressDialog *progressdialog=new QProgressDialog(this);
        progressdialog->setWindowModality(Qt::WindowModal);
        progressdialog->resize(400,120);
        progressdialog->setMinimumSize(400,120);
        progressdialog->setMaximumSize(400,120);
        progressdialog->setMinimumDuration(100);
        progressdialog->setWindowTitle(("添加至我的收藏"));
        progressdialog->setLabelText(("正在添加,请稍后."));
        QPushButton *button=new QPushButton(this);
        QPixmap pixmap;
        pixmap.load(":/image/image/58d4d135e7bce713bd501050.jpg");
        QPalette palette;
        palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(progressdialog->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        progressdialog->setPalette(palette);
        button->setStyleSheet("QPushButton{"

                              "background-color: rgba(122, 122, 122,100);"
                              "border-style:outset;"
                              "border-width: 1px;"
                              "border-radius: 10px;"
                              "border-color: rgba(122, 122, 122,100);"
                              "font: bold 14px;"
                              "color :rgba(0,0,0,100);"
                              "padding: 6px;"

                              "}"
                              "QPushButton:hover{"



                              "background-color: rgba(176, 58, 176,200);"
                              "color: rgba(0,0,0,200);"


                              "}"
                              "QPushButton:pressed{"


                                  "background-color:  rgba(255,255,255,150);"
                              "border-color:rgba(255,255,255,150);"
                              "border-style:inset;"
                              "color:rgba(0,0,0,100);"

                              "}");
        button->setText(("关闭"));
        progressdialog->setCancelButton(button);
        progressdialog->setRange(0,items.size()-1);
        progressdialog->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;background-color:rgba(255,255,255,150);}"
                                      "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}");

        for(int i=0;i<items.size();i++)
        {

            if(i==items.size()-1)
            {
                progressdialog->close();
            }
            if(!progressdialog->wasCanceled())
            {
                 progressdialog->setValue(i);

            }
            else
            {
                 progressdialog->close();
            }

            int row=ui->listWidget_3->row(items.at(i));
        QString Text=ui->listWidget_3->item(row)->text();
        QListWidgetItem *ITEMM2=new QListWidgetItem;
        ITEMM2->setIcon(QIcon(":/image/image/music_not_25.570093457944px_1171234_easyicon.net.png"));
        ITEMM2->setText(QString("%1").arg(Text));
        ITEMM2->setToolTip(Text);

        ui->listWidget->addItem(ITEMM2);
        model->setTable("LocalMusic");
        model->select();
        playlist_3->addMedia(playlist->media(row));
        QSqlQuery query;
        QString MusicName=model->data(model->index(row,1)).toString();
        QString FileName=model->data(model->index(row,2)).toString();

        query.exec("select * from  CollectMusic");
        query.exec(QString("insert into  CollectMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(MusicName).arg(FileName));



        }


delete button;
        ui->listWidget_3->setSelectionMode(QListWidget::SingleSelection);
    }


}
void Widget::Action7_slot()//多选模式
{
ui->listWidget_3->setSelectionMode(QListWidget::MultiSelection);
}
void Widget::Action8_slot()//单选模式
{

    if(ui->listWidget_3->selectionMode()==QListWidget::MultiSelection)
    {
    ui->listWidget_3->setSelectionMode(QListWidget::SingleSelection);
    if(music->playlist()==playlist)
    {

        ui->listWidget_3->item(playlist->currentIndex())->setSelected(true);
    }
    else
    {
        ui->listWidget_3->item(0)->setSelected(true);
    }
    }
}

void Widget::Action5_slot()//歌曲信息
{
    int row=ui->listWidget_3->currentIndex().row();
    QString temp=ui->listWidget_3->currentIndex().data().toString();
    QString MusicName=temp.split(" - ").last();
    QString Author=temp.remove(" - "+MusicName);
    model->setTable("LocalMusic");
    model->select();
    QString FileName=model->data(model->index(row,2)).toString();
    QString time;
    if(music->playlist()==playlist)
    {

        if(row==playlist->currentIndex())
        {
            time=Time(music->duration());
        }
        else
        {
            time="00:00";
        }
    }
    else
    {
        time="00:00";
    }
    QMessageBox::about(this,"歌曲信息",QString("歌曲名 : %1  \n"
                                             "作者 : %2 \n"
                                             "时长 : %3\n "
                                             "文件路径 : %4\n").arg(MusicName).arg(Author).arg(time).arg(FileName));

}

void Widget::Action3_slot()//listWidget_3右键菜单 删除
{


if(ui->listWidget_3->selectionMode()==QListWidget::SingleSelection)
{
if(music->playlist()==playlist)
{

    int Row=playlist->currentIndex();
    int row=ui->listWidget_3->currentIndex().row();
    if(row<Row)
    {
        int Position=0;
        int flag=0;
        if(music->state()==QMediaPlayer::PlayingState)
        {
            Position=music->position();
            flag=1;
        }

        playlist->setCurrentIndex(0);
        delete ui->listWidget_3->takeItem(row);
        playlist->removeMedia(row,row);
        model->setTable("LocalMusic");
        model->select();
        model->removeRow(row);
        model->submitAll();
        music->setPlaylist(playlist);
        playlist->setCurrentIndex(Row-1);
        music->setPosition(Position);
        ui->horizontalSlider->setValue(Position);
        if(flag)
        music->play();
        if(list1[row]){
            int index;
            if((index = map.indexOf(row))!=-1)
            {
                delete ui->listWidget_5->takeItem(index);
                playlist_4->removeMedia(index,index);
                map.removeAt(index);
                for(int i=0;i<map.size();i++)
                {
                    if(map[i]>row)
                    {
                        map[i]--;
                    }
                }
            }
        }

        FilePath.removeAt(row);
        list1.removeAt(row);

    }
    else
    {


        ui->listWidget_3->takeItem(row);
        playlist->removeMedia(row,row);
        model->setTable("LocalMusic");
        model->select();
        model->removeRow(row);
        model->submitAll();
        if(list1[row]){
            int index;
            if((index = map.indexOf(row))!=-1)
            {
                delete ui->listWidget_5->takeItem(index);
                 playlist_4->removeMedia(index,index);
                map.removeAt(index);
                for(int i=0;i<map.size();i++)
                {
                    if(map[i]>row)
                    {
                        map[i]--;
                    }
                }
            }
        }
        list1.removeAt(row);
        FilePath.removeAt(row);
    }


}
else
{
    int row=ui->listWidget_3->currentIndex().row();

    ui->listWidget_3->takeItem(row);
    playlist->removeMedia(row,row);
    model->setTable("LocalMusic");
    model->select();
    model->removeRow(row);
    model->submitAll();
    if(list1[row]){
        int index;
        if((index = map.indexOf(row))!=-1)
        {
            delete ui->listWidget_5->takeItem(index);
             playlist_4->removeMedia(index,index);
            map.removeAt(index);
            for(int i=0;i<map.size();i++)
            {
                if(map[i]>row)
                {
                    map[i]--;
                }
            }
        }
    }
    list1.removeAt(row);
    FilePath.removeAt(row);
}

}
else if(ui->listWidget_3->selectionMode()==QListWidget::MultiSelection)
{
    QList<QListWidgetItem*> items;
    items=ui->listWidget_3->selectedItems();
    if(items.size()==0)
    {
        return ;
    }
    QProgressDialog *progressdialog=new QProgressDialog(this);
    progressdialog->setWindowModality(Qt::WindowModal);
    progressdialog->setMinimumDuration(100);
    progressdialog->resize(400,120);
    progressdialog->setMinimumSize(400,120);
    progressdialog->setMaximumSize(400,120);
    progressdialog->setMinimumDuration(100);
    progressdialog->setWindowTitle(("删除"));
    progressdialog->setLabelText(("正在删除,请稍后."));
    QPushButton *button=new QPushButton(this);
    QPixmap pixmap;
    pixmap.load(":/image/image/58d4d135e7bce713bd501050.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(progressdialog->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    progressdialog->setPalette(palette);
    button->setStyleSheet("QPushButton{"

                          "background-color: rgba(122, 122, 122,100);"
                          "border-style:outset;"
                          "border-width: 1px;"
                          "border-radius: 10px;"
                          "border-color: rgba(122, 122, 122,100);"
                          "font: bold 14px;"
                          "color :rgba(0,0,0,100);"
                          "padding: 6px;"

                          "}"
                          "QPushButton:hover{"



                          "background-color: rgba(176, 58, 176,200);"
                          "color: rgba(0,0,0,200);"


                          "}"
                          "QPushButton:pressed{"


                              "background-color:  rgba(255,255,255,150);"
                          "border-color:rgba(255,255,255,150);"
                          "border-style:inset;"
                          "color:rgba(0,0,0,100);"

                          "}");
    button->setText(("关闭"));
    progressdialog->setCancelButton(button);
    progressdialog->setRange(0,items.size()-1);
    progressdialog->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;background-color:rgba(255,255,255,150);}"
                                  "QProgressBar::chunk{background-color: yellow;width: 10px;margin: 0.5px;}");

    int position=0;
    int current=0;
    int count=0;

    if(music->playlist()==playlist)
    {
        int flag=0;
        if(music->state()==QMediaPlayer::PlayingState)
        {
            flag=1;
            position=music->position();
            music->pause();
        }
        current=playlist->currentIndex();
        for(int i=0;i<items.count();i++)
        {
            if(current>(ui->listWidget_3->row(items.at(i))))
            {
                count++;
            }
        }
    for(int i=0;i<items.size();i++)
    {

        if(i==items.size()-1)
        {
            progressdialog->close();
        }
        if(!progressdialog->wasCanceled())
        {
            progressdialog->setValue(i);

        }
        else
        {
             progressdialog->close();
        }
            int row=ui->listWidget_3->row(items.at(i));


            delete ui->listWidget_3->takeItem(row);
            playlist->removeMedia(row,row);

            model->setTable("LocalMusic");
            model->select();
            model->removeRow(row);
            model->submitAll();
            if(list1[row]){
                int index;
                if((index = map.indexOf(row))!=-1)
                {
                    delete ui->listWidget_5->takeItem(index);
                     playlist_4->removeMedia(index,index);
                    map.removeAt(index);
                    for(int i=0;i<map.size();i++)
                    {
                        if(map[i]>row)
                        {
                            map[i]--;
                        }
                    }
                }
            }
            list1.removeAt(row);
            FilePath.removeAt(row);
    }
     music->setPlaylist(playlist);
     playlist->setCurrentIndex(current-count);
    music->setPosition(position);
    ui->horizontalSlider->setValue(position);
    if(flag)
      music->play();

    }
    else
    {
        for(int i=0;i<items.size();i++)
        {

            if(i==items.size()-1)
            {
                progressdialog->close();
            }
            if(!progressdialog->wasCanceled())
            {
                progressdialog->setValue(i);
            }
            else
            {
                 progressdialog->close();

                }
               int row=ui->listWidget_3->row(items.at(i));
                delete ui->listWidget_3->takeItem(row);

                playlist->removeMedia(row,row);

                model->setTable("LocalMusic");
                model->select();
                model->removeRow(row);
                model->submitAll();
                if(list1[row]){
                    int index;
                    if((index = map.indexOf(row))!=-1)
                    {
                        delete ui->listWidget_5->takeItem(index);
                         playlist_4->removeMedia(index,index);
                        map.removeAt(index);
                        for(int i=0;i<map.size();i++)
                        {
                            if(map[i]>row)
                            {
                                map[i]--;
                            }
                        }
                    }
                }
                   list1.removeAt(row);
                   FilePath.removeAt(row);
        }

    }
    delete button;
    ui->listWidget_3->setSelectionMode(QListWidget::SingleSelection);

}

}

void Widget::on_listWidget_2_customContextMenuRequested(const QPoint &pos)//listWidget_2右键菜单 我喜欢列表
{
    QListWidgetItem *curItem1=ui->listWidget_2->itemAt(pos);
    if(curItem1==NULL)
    {
        return ;
    }
    QMenu *Menu1=new QMenu(this);
    Menu1->setStyleSheet(
               MenuStyle()

                );
    QAction *Action1_2=new QAction(this);
    QAction *Action1_2_1=new QAction(this);
    QAction *Action2_2=new QAction(this);
    QAction *Action3_2=new QAction(this);
    QAction *Action4_2=new QAction(this);
    QAction *Action6_2=new QAction(this);
    QAction *Action7_2=new QAction(this);
    Action1_2->setIcon(QIcon(":/image/image/zt13.png"));
    Action1_2->setText(("播放"));
    Action1_2_1->setIcon(QIcon(":/image/image/bofang1.png"));
    Action1_2_1->setText(("暂停"));
    Action3_2->setIcon(QIcon(":/image/image/list_32px_1142913_easyicon.net.png"));
    Action3_2->setText(("添加至我的收藏"));

    Action2_2->setIcon(QIcon(":/image/image/delete_32px_1168909_easyicon.net.png"));
    Action2_2->setText(("移除"));
    Action4_2->setIcon(QIcon(":/image/image/inf.png"));
    Action4_2->setText(("歌曲信息"));
    Action6_2->setIcon(QIcon(":/image/image/duoxuan.png"));
    Action6_2->setText(("多选"));
    Action7_2->setIcon(QIcon(":/image/image/quxiao.png"));
    Action7_2->setText(("取消多选"));
    if(ui->listWidget_2->selectionMode()==QListWidget::SingleSelection)
    {
        if(music->playlist()==playlist_2)
        {
            if(ui->listWidget_2->currentIndex().row()==playlist_2->currentIndex())
            {

                if(music->state()==QMediaPlayer::PlayingState)
                {
                      Menu1->addAction(Action1_2_1);
                }
                else
                {
                      Menu1->addAction(Action1_2);
                }
            }
            else
            {
                  Menu1->addAction(Action1_2);
            }
        }
        else
        {
              Menu1->addAction(Action1_2);
        }

    Menu1->addAction(Action3_2);
    Menu1->addAction(Action6_2);
    Menu1->addAction(Action4_2);
    Menu1->addAction(Action2_2);

    }
    else if(ui->listWidget_2->selectionMode()==QListWidget::MultiSelection)
    {

        Menu1->addAction(Action3_2);
        Menu1->addAction(Action7_2);
        Menu1->addAction(Action2_2);
    }
    connect(Action1_2,&QAction::triggered,this,&Widget::Action1_2_slot);
    connect(Action1_2_1,&QAction::triggered,this,&Widget::action11_slot);
    connect(Action2_2,&QAction::triggered,this,&Widget::Action2_2_slot);
    connect(Action3_2,&QAction::triggered,this,&Widget::Action3_2_slot);
    connect(Action4_2,&QAction::triggered,this,&Widget::Action4_2_slot);
    connect(Action6_2,&QAction::triggered,this,&Widget::Action6_2_slot);
    connect(Action7_2,&QAction::triggered,this,&Widget::Action7_2_slot);
    Menu1->exec(QCursor::pos());
    delete Menu1;
    delete Action1_2;
    delete Action1_2_1;
    delete Action2_2;
    delete Action3_2;
    delete Action4_2;
    delete Action6_2;
    delete Action7_2;

}
void Widget::Action1_2_slot()//listWidget_2右键菜单   播放
{

    if(music->playlist()==playlist_2)
    {
    if(ui->listWidget_2->currentIndex().row()==playlist_2->currentIndex())
    {


            music->play();

    }
    else
    {
        playlist_2->setCurrentIndex(ui->listWidget_2->currentIndex().row());
        music->play();
    }
    }
    else
    {
        music->setPlaylist(playlist_2);
    playlist_2->setCurrentIndex(ui->listWidget_2->currentIndex().row());

    music->play();
    }

}

void Widget::Action3_2_slot()//添加至我的收藏
{

    if(ui->listWidget_2->selectionMode()==QListWidget::SingleSelection)
    {
        int row=ui->listWidget_2->currentIndex().row();
    QString Text=ui->listWidget_2->item(row)->text();
    QListWidgetItem *ITEMM1=new QListWidgetItem;
    ITEMM1->setIcon(QIcon(":/image/image/music_not_25.570093457944px_1171234_easyicon.net.png"));
    ITEMM1->setText(QString("%1").arg(Text));
    ITEMM1->setToolTip(Text);

    ui->listWidget->addItem(ITEMM1);
    model_2->setTable("LikeMusic");
    model_2->select();
    playlist_3->addMedia(playlist_2->media(row));
    QSqlQuery query;
    QString MusicName=model_2->data(model_2->index(row,1)).toString();
    QString FileName=model_2->data(model_2->index(row,2)).toString();

    query.exec("select * from  CollectMusic");
    query.exec(QString("insert into  CollectMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(MusicName).arg(FileName));
    ui->stackedWidget->setCurrentIndex(2);
    pushbuttonstyle_3();

    }
    else if(ui->listWidget_2->selectionMode()==QListWidget::MultiSelection)
    {

        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        QList<QListWidgetItem*> items;
        items=ui->listWidget_2->selectedItems();
        if(items.size()==0)
        {
            return ;
        }
        QProgressDialog *progressdialog=new QProgressDialog(this);
        progressdialog->setWindowModality(Qt::WindowModal);
        progressdialog->resize(400,120);
        progressdialog->setMinimumSize(400,120);
        progressdialog->setMaximumSize(400,120);
        progressdialog->setMinimumDuration(100);
        progressdialog->setWindowTitle(("添加至我的收藏"));
        progressdialog->setLabelText(("正在添加,请稍后."));
        QPushButton *button=new QPushButton(this);
        QPixmap pixmap;
        pixmap.load(":/image/image/58d4d135e7bce713bd501050.jpg");
        QPalette palette;
        palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(progressdialog->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        progressdialog->setPalette(palette);
        button->setStyleSheet("QPushButton{"

                              "background-color: rgba(122, 122, 122,100);"
                              "border-style:outset;"
                              "border-width: 1px;"
                              "border-radius: 10px;"
                              "border-color: rgba(122, 122, 122,100);"
                              "font: bold 14px;"
                              "color :rgba(0,0,0,100);"
                              "padding: 6px;"

                              "}"
                              "QPushButton:hover{"



                              "background-color: rgba(176, 58, 176,200);"
                              "color: rgba(0,0,0,200);"


                              "}"
                              "QPushButton:pressed{"


                                  "background-color:  rgba(255,255,255,150);"
                              "border-color:rgba(255,255,255,150);"
                              "border-style:inset;"
                              "color:rgba(0,0,0,100);"

                              "}");
        button->setText(("关闭"));
        progressdialog->setCancelButton(button);
        progressdialog->setRange(0,items.size()-1);
        progressdialog->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;background-color:rgba(255,255,255,150);}"
                                      "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}");

        for(int i=0;i<items.size();i++)
        {

            if(i==items.size()-1)
            {
                progressdialog->close();
            }
            if(progressdialog->wasCanceled())
            {
                progressdialog->close();
            }
            else
            {
                progressdialog->setValue(i);
            }

            int row=ui->listWidget_2->row(items.at(i));
        QString Text=ui->listWidget_2->item(row)->text();
        QListWidgetItem *ITEMM2=new QListWidgetItem;
        ITEMM2->setIcon(QIcon(":/image/image/music_not_25.570093457944px_1171234_easyicon.net.png"));
        ITEMM2->setText(QString("%1").arg(Text));
        ITEMM2->setToolTip(Text);

        ui->listWidget->addItem(ITEMM2);
        model_2->setTable("LikeMusic");
        model_2->select();
        playlist_3->addMedia(playlist_2->media(row));
        QSqlQuery query;
        QString MusicName=model_2->data(model_2->index(row,1)).toString();
        QString FileName=model_2->data(model_2->index(row,2)).toString();

        query.exec("select * from  CollectMusic");
        query.exec(QString("insert into  CollectMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(MusicName).arg(FileName));



        }


delete button;
        ui->listWidget_2->setSelectionMode(QListWidget::SingleSelection);
    }
}

void Widget::Action6_2_slot()//多选模式
{

    ui->listWidget_2->setSelectionMode(QListWidget::MultiSelection);
}
void Widget::Action7_2_slot()//单选模式
{

    if(ui->listWidget_2->selectionMode()==QListWidget::MultiSelection)
    {
    ui->listWidget_2->setSelectionMode(QListWidget::SingleSelection);
    if(music->playlist()==playlist_2)
    {

        ui->listWidget_2->item(playlist_2->currentIndex())->setSelected(true);
    }
    else
    {
        ui->listWidget_2->item(0)->setSelected(true);
    }
    }

}

void Widget::Action4_2_slot()//歌曲信息
{

    int row=ui->listWidget_2->currentIndex().row();
    QString temp=ui->listWidget_2->currentIndex().data().toString();
    QString MusicName=temp.split(" - ").last();
    QString Author=temp.remove(" - "+MusicName);
    model_2->setTable("LikeMusic");
    model_2->select();
    QString FileName=model_2->data(model_2->index(row,2)).toString();
    QString time;
    if(music->playlist()==playlist_2)
    {

        if(row==playlist_2->currentIndex())
        {
            time=Time(music->duration());
        }
        else
        {
            time="00:00";
        }
    }
    else
    {
        time="00:00";
    }
    QMessageBox::about(this,"歌曲信息",QString("歌曲名 : %1  \n"
                                             "作者 : %2 \n"
                                             "时长 : %3 \n"
                                             "文件路径 : %4\n").arg(MusicName).arg(Author).arg(time).arg(FileName));

}

void Widget::Action2_2_slot()//listWidget_2右键菜单 删除
{
    if(ui->listWidget_2->selectionMode()==QListWidget::SingleSelection)
    {
        QString MusicName=ui->listWidget_2->currentItem()->text();
    if(music->playlist()==playlist_2)
    {

        int Row=playlist_2->currentIndex();
        int row=ui->listWidget_2->currentIndex().row();

        if(row<Row)
        {
            int Position=0;
            if(music->state()==QMediaPlayer::PlayingState)
            {

                Position=music->position();
            }
            playlist_2->setCurrentIndex(0);
            ui->listWidget_2->takeItem(row);
            playlist_2->removeMedia(row,row);

            model_2->setTable("LikeMusic");
            model_2->select();
            model_2->removeRow(row);
            model_2->submitAll();

            music->setPlaylist(playlist_2);
            playlist_2->setCurrentIndex(Row-1);
            music->setPosition(Position);
            ui->horizontalSlider->setValue(Position);
            music->play();
        }
        else
        {
            ui->listWidget_2->takeItem(row);

            playlist_2->removeMedia(row,row);
            model_2->setTable("LikeMusic");
            model_2->select();
            model_2->removeRow(row);
            model_2->submitAll();

        }


    }
    else
    {
        int row=ui->listWidget_2->currentIndex().row();

        ui->listWidget_2->takeItem(row);
        playlist_2->removeMedia(row,row);
        model_2->setTable("LikeMusic");
        model_2->select();
        model_2->removeRow(row);
        model_2->submitAll();
    }
    QSqlQuery query;
    query.exec("select * from LocalMusic");
    query.prepare(QString("update LocalMusic set biaoji = ? where MusicName = '%1' ").arg(MusicName));
    query.bindValue(0,0);
    query.exec();


    }
    else if(ui->listWidget_2->selectionMode()==QListWidget::MultiSelection)
    {
        QList<QListWidgetItem*> items;
        items=ui->listWidget_2->selectedItems();
        if(items.size()==0)
        {
            return ;
        }
        QProgressDialog *progressdialog=new QProgressDialog(this);
        progressdialog->setWindowModality(Qt::WindowModal);
        progressdialog->resize(400,120);
        progressdialog->setMinimumSize(400,120);
        progressdialog->setMaximumSize(400,120);
        progressdialog->setMinimumDuration(100);
        progressdialog->setWindowTitle(("移除"));
        progressdialog->setLabelText(("正在移除,请稍后."));
        QPushButton *button=new QPushButton(this);
        QPixmap pixmap;
        pixmap.load(":/image/image/58d4d135e7bce713bd501050.jpg");
        QPalette palette;
        palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(progressdialog->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        progressdialog->setPalette(palette);
        button->setStyleSheet("QPushButton{"

                              "background-color: rgba(122, 122, 122,100);"
                              "border-style:outset;"
                              "border-width: 1px;"
                              "border-radius: 10px;"
                              "border-color: rgba(122, 122, 122,100);"
                              "font: bold 14px;"
                              "color :rgba(0,0,0,100);"
                              "padding: 6px;"

                              "}"
                              "QPushButton:hover{"



                              "background-color: rgba(176, 58, 176,200);"
                              "color: rgba(0,0,0,200);"


                              "}"
                              "QPushButton:pressed{"


                                  "background-color:  rgba(255,255,255,150);"
                              "border-color:rgba(255,255,255,150);"
                              "border-style:inset;"
                              "color:rgba(0,0,0,100);"

                              "}");
        button->setText(("关闭"));
        progressdialog->setCancelButton(button);
        progressdialog->setRange(0,items.size()-1);
        progressdialog->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;background-color:rgba(255,255,255,150);}"
                                      "QProgressBar::chunk{background-color: yellow;width: 10px;margin: 0.5px;}");

        int position=0;
        int current=0;
        int count=0;
        if(music->playlist()==playlist_2)
        {
            int flag=0;
            if(music->state()==QMediaPlayer::PlayingState)
            {
                flag=1;
                position=music->position();
                music->pause();
            }
            current=playlist_2->currentIndex();
            for(int i=0;i<items.count();i++)
            {

                if(current>(ui->listWidget_2->row(items.at(i))))
                {
                    count++;
                }
            }
        for(int i=0;i<items.size();i++)
        {

            if(i==items.size()-1)
            {
                progressdialog->close();
            }
            if(progressdialog->wasCanceled())
            {
                progressdialog->close();
            }
            else
            {
                progressdialog->setValue(i);
            }
                int row=ui->listWidget_2->row(items.at(i));
                QString MusicName=ui->listWidget_2->item(row)->text();
                delete ui->listWidget_2->takeItem(row);

                playlist_2->removeMedia(row,row);
                model_2->setTable("LikeMusic");
                model_2->select();
                model_2->removeRow(row);
                model_2->submitAll();
                QSqlQuery query;
                query.exec("select * from LocalMusic");
                query.prepare(QString("update LocalMusic set biaoji = ? where MusicName = '%1' ").arg(MusicName));
                query.bindValue(0,0);
                query.exec();

        }
         music->setPlaylist(playlist_2);
         playlist_2->setCurrentIndex(current-count);
        music->setPosition(position);
        ui->horizontalSlider->setValue(position);
        if(flag)
          music->play();

        }
        else
        {
            for(int i=0;i<items.size();i++)
            {


                if(i==items.size()-1)
                {
                    progressdialog->close();
                }
                if(progressdialog->wasCanceled())
                {
                    progressdialog->close();
                }
                else
                {
                     progressdialog->setValue(i);
                }
                   int row=ui->listWidget_2->row(items.at(i));
                   QString MusicName=ui->listWidget_2->item(row)->text();
                    delete ui->listWidget_2->takeItem(row);

                    playlist_2->removeMedia(row,row);
                    model_2->setTable("LikeMusic");
                    model_2->select();
                    model_2->removeRow(row);
                    model_2->submitAll();
                    QSqlQuery query;
                    query.exec("select * from LocalMusic");
                    query.prepare(QString("update LocalMusic set biaoji = ? where MusicName = '%1' ").arg(MusicName));
                    query.bindValue(0,0);
                    query.exec();
            }

        }
        ui->listWidget_2->setSelectionMode(QListWidget::SingleSelection);
        delete button;
    }

}

void Widget::on_listWidget_customContextMenuRequested(const QPoint &pos)//listWidget右键菜单  我的收藏
{
    QListWidgetItem *curItem2=ui->listWidget->itemAt(pos);
    if(curItem2==NULL)
    {
        return ;
    }
    QMenu *Menu2=new QMenu(this);
    Menu2->setStyleSheet(
               MenuStyle()

                );
    QAction *Action1_3=new QAction(this);//播放
    QAction *Action1_3_1=new QAction(this);//暂停
    QAction *Action3_3=new QAction(this);//歌曲信息
    QAction *Action2_3=new QAction(this);//移除
    QAction *Action5_3=new QAction(this);//多选
    QAction *Action6_3=new QAction(this);//取消多选
    Action1_3->setIcon(QIcon(":/image/image/zt13.png"));
    Action1_3->setText(("播放"));
    Action1_3_1->setIcon(QIcon(":/image/image/bofang1.png"));
    Action1_3_1->setText(("暂停"));
    Action2_3->setIcon(QIcon(":/image/image/delete_32px_1168909_easyicon.net.png"));
    Action2_3->setText(("移除"));
    Action3_3->setIcon(QIcon(":/image/image/inf.png"));
    Action3_3->setText(("歌曲信息"));
    Action5_3->setIcon(QIcon(":/image/image/duoxuan.png"));
    Action5_3->setText(("多选"));
    Action6_3->setIcon(QIcon(":/image/image/quxiao.png"));
    Action6_3->setText(("取消多选"));
    if(ui->listWidget->selectionMode()==QListWidget::SingleSelection)
    {
        if(music->playlist()==playlist_3)
        {
            if(ui->listWidget->currentIndex().row()==playlist_3->currentIndex())
            {
                if(music->state()==QMediaPlayer::PlayingState)
                {
                    Menu2->addAction(Action1_3_1);
                }
                else
                {
                    Menu2->addAction(Action1_3);
                }
            }
            else
            {
                Menu2->addAction(Action1_3);
            }
        }
        else
        {
            Menu2->addAction(Action1_3);
        }

    Menu2->addAction(Action5_3);
    Menu2->addAction(Action3_3);
    Menu2->addAction(Action2_3);

    }
    else if(ui->listWidget->selectionMode()==QListWidget::MultiSelection)
    {

        Menu2->addAction(Action6_3);
        Menu2->addAction(Action2_3);

    }
    connect(Action1_3,&QAction::triggered,this,&Widget::Action1_3_slot);
    connect(Action1_3_1,&QAction::triggered,this,&Widget::action11_slot);
    connect(Action2_3,&QAction::triggered,this,&Widget::Action2_3_slot);
    connect(Action3_3,&QAction::triggered,this,&Widget::Action3_3_slot);
    connect(Action5_3,&QAction::triggered,this,&Widget::Action5_3_slot);
    connect(Action6_3,&QAction::triggered,this,&Widget::Action6_3_slot);
    Menu2->exec(QCursor::pos());
    delete Menu2;
    delete Action1_3;
    delete Action2_3;
    delete Action3_3;
    delete Action5_3;
    delete Action6_3;
    delete Action1_3_1;

}
void Widget::Action1_3_slot()//listWidget右键菜单 播放
{

    if(music->playlist()==playlist_3)
    {

int row=ui->listWidget->currentIndex().row();
    if(row==playlist_3->currentIndex())
    {


            music->play();

    }
    else
    {

        playlist_3->setCurrentIndex(ui->listWidget->currentIndex().row());
        music->play();
    }

    }
    else
    {
        music->setPlaylist(playlist_3);
    playlist_3->setCurrentIndex(ui->listWidget->currentIndex().row());
    music->play();
    }

}
void Widget::Action5_3_slot()//多选模式
{
    ui->listWidget->setSelectionMode(QListWidget::MultiSelection);
}
void Widget::Action6_3_slot()//单选模式
{
    if(ui->listWidget->selectionMode()==QListWidget::MultiSelection)
    {
    ui->listWidget->setSelectionMode(QListWidget::SingleSelection);
    if(music->playlist()==playlist_3)
    {

        ui->listWidget->item(playlist_3->currentIndex())->setSelected(true);
    }
    else
    {
        ui->listWidget->item(0)->setSelected(true);
    }
    }

}
void Widget::Action3_3_slot()//歌曲信息
{

    int row=ui->listWidget->currentIndex().row();
    QString temp=ui->listWidget->currentIndex().data().toString();
    QString MusicName=temp.split(" - ").last();
    QString Author=temp.remove(" - "+MusicName);
    model_3->setTable("  CollectMusic");
    model_3->select();
    QString FileName=model_3->data(model_3->index(row,2)).toString();
    QString time;
    if(music->playlist()==playlist_3)
    {

        if(row==playlist_3->currentIndex())
        {
            time=Time(music->duration());
        }
        else
        {
            time="00:00";
        }
    }
    else
    {
        time="00:00";
    }
    QMessageBox::about(this,"歌曲信息",QString("歌曲名 : %1  \n"
                                             "作者 : %2 \n"
                                             "时长 : %3 \n"
                                             "文件路径 : %4\n").arg(MusicName).arg(Author).arg(time).arg(FileName));

}

void Widget::Action2_3_slot()//listWidget右键菜单  删除
{
    if(ui->listWidget->selectionMode()==QListWidget::SingleSelection)
    {
    if(music->playlist()==playlist_3)
    {

        int Row=playlist_3->currentIndex();
        int row=ui->listWidget->currentIndex().row();
        if(row<Row)
        {
            int Position=0;
            if(music->state()==QMediaPlayer::PlayingState)
            {

                Position=music->position();
            }
            playlist_3->setCurrentIndex(0);

            ui->listWidget->takeItem(row);
            playlist_3->removeMedia(row,row);
            model_3->setTable("  CollectMusic");
            model_3->select();
            model_3->removeRow(row);
            model_3->submitAll();
            music->setPlaylist(playlist_3);
            playlist_3->setCurrentIndex(Row-1);
            music->setPosition(Position);
            ui->horizontalSlider->setValue(Position);
            music->play();
        }
        else
        {
            ui->listWidget->takeItem(row);

            playlist_3->removeMedia(row,row);
            model_3->setTable("  CollectMusic");
            model_3->select();
            model_3->removeRow(row);
            model_3->submitAll();

        }


    }
    else
    {
        int row=ui->listWidget->currentIndex().row();
        ui->listWidget->takeItem(row);

        playlist_3->removeMedia(row,row);
        model_3->setTable("  CollectMusic");
        model_3->select();
        model_3->removeRow(row);
        model_3->submitAll();
    }

    }
    else if(ui->listWidget->selectionMode()==QListWidget::MultiSelection)
    {
        QList<QListWidgetItem*> items;
        items=ui->listWidget->selectedItems();
        if(items.size()==0)
        {
            return ;
        }
        QProgressDialog *progressdialog=new QProgressDialog(this);
        progressdialog->setWindowModality(Qt::WindowModal);
        progressdialog->resize(400,120);
        progressdialog->setMinimumSize(400,120);
        progressdialog->setMaximumSize(400,120);
        progressdialog->setMinimumDuration(100);
        progressdialog->setWindowTitle(("移除"));
        progressdialog->setLabelText(("正在移除,请稍后."));
        QPushButton *button=new QPushButton(this);
        QPixmap pixmap;
        pixmap.load(":/image/image/58d4d135e7bce713bd501050.jpg");
        QPalette palette;
        palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(progressdialog->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        progressdialog->setPalette(palette);
        button->setStyleSheet("QPushButton{"

                              "background-color: rgba(122, 122, 122,100);"
                              "border-style:outset;"
                              "border-width: 1px;"
                              "border-radius: 10px;"
                              "border-color: rgba(122, 122, 122,100);"
                              "font: bold 14px;"
                              "color :rgba(0,0,0,100);"
                              "padding: 6px;"

                              "}"
                              "QPushButton:hover{"



                              "background-color: rgba(176, 58, 176,200);"
                              "color: rgba(0,0,0,200);"


                              "}"
                              "QPushButton:pressed{"


                                  "background-color:  rgba(255,255,255,150);"
                              "border-color:rgba(255,255,255,150);"
                              "border-style:inset;"
                              "color:rgba(0,0,0,100);"

                              "}");
        button->setText(("关闭"));
        progressdialog->setCancelButton(button);
        progressdialog->setRange(0,items.size()-1);
        progressdialog->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;background-color:rgba(255,255,255,150);}"
                                      "QProgressBar::chunk{background-color: yellow;width: 10px;margin: 0.5px;}");

        int position=0;
        int current=0;
        int count=0;
        if(music->playlist()==playlist_3)
        {
            int flag=0;
            if(music->state()==QMediaPlayer::PlayingState)
            {
                flag=1;
                position=music->position();
            }
            current=playlist_3->currentIndex();
            for(int i=0;i<items.count();i++)
            {
                if(current>(ui->listWidget->row(items.at(i))))
                {
                    count++;

                }
            }
        for(int i=0;i<items.size();i++)
        {

            if(i==items.size()-1)
            {
                progressdialog->close();
            }
            if(progressdialog->wasCanceled())
            {
                progressdialog->close();
            }
            else
            {
                progressdialog->setValue(i);
            }
               int row=ui->listWidget->row(items.at(i));
               delete ui->listWidget->takeItem(row);

                playlist_3->removeMedia(row,row);
                model_3->setTable("  CollectMusic");
                model_3->select();
                model_3->removeRow(row);
                model_3->submitAll();

        }
         music->setPlaylist(playlist_3);
         playlist_3->setCurrentIndex(current-count);
        music->setPosition(position);
        ui->horizontalSlider->setValue(position);
        if(flag)
          music->play();

        }
        else
        {
            for(int i=0;i<items.size();i++)
            {


                if(i==items.size()-1)
                {
                    progressdialog->close();
                }
                if(progressdialog->wasCanceled())
                {
                    progressdialog->close();
                }
                else
                {
                   progressdialog->setValue(i);
                }
                   int row=ui->listWidget->row(items.at(i));
                    delete ui->listWidget->takeItem(row);

                    playlist_3->removeMedia(row,row);
                    model_3->setTable("  CollectMusic");
                    model_3->select();
                    model_3->removeRow(row);
                    model_3->submitAll();
            }

        }
        ui->listWidget->setSelectionMode(QListWidget::SingleSelection);
delete button;
    }

}
void Widget::on_pushButton_13_clicked()//极简模式
{

    hide();
    int i;
    if(music->playlist()==playlist)
    {
        i=0;
    }
    else if(music->playlist()==playlist_2)
    {
        i=1;
    }
    else
    {
        i=2;
    }
    Music->setPlaylist(music->playlist(),music->playlist()->currentIndex(),music->position(),music->volume(),music->state(),playlist->playbackMode(),i);
    music->pause();
    if(Music->exec()==Dialog::Accepted)
    {

        show();

    }


}

void Widget::Data_slot(int row,int position,QMediaPlaylist *list,QMediaPlayer::State state,QMediaPlaylist::PlaybackMode model,QList<int> Index)//接收数据
{
    playlist->setPlaybackMode(model);
    playlist_2->setPlaybackMode(model);
    playlist_3->setPlaybackMode(model);
    if(list==playlist)
    {
        playlist->setCurrentIndex(row);
        music->setPosition(position);
        if(state==QMediaPlayer::PlayingState)
        music->play();
        for(int i=0;i<Index.size();i++)
        {
            if(list1[Index[i]]==0)
            {
                list1[Index[i]]++;
                map.push_back(Index[i]);
                QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(Index[i])->text());
                myitem->setToolTip(ui->listWidget_3->item(Index[i])->text());

                ui->listWidget_5->addItem(myitem);
                playlist_4->addMedia(QUrl::fromLocalFile(FilePath[Index[i]]));
            }
        }

    }
    else  if(list==playlist_2)
    {


        playlist_2->setCurrentIndex(row);
        music->setPosition(position);
        if(state==QMediaPlayer::PlayingState)
        music->play();


    }
    else
    {
       playlist_3->setCurrentIndex(row);
       music->setPosition(position);
       if(state==QMediaPlayer::PlayingState)
       music->play();

    }

}

void Widget::on_pushButton_14_clicked()//添加至我喜欢
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
    ListFocus();
    if(music->playlist()==playlist)
    {

        int row=playlist->currentIndex();
        model->setTable("LocalMusic");
        model->select();
        int flag=model->data(model->index(row,3)).toInt();
        if(flag==0)
        {
            ui->pushButton_14->setIcon(QIcon(":/image/image/image/Ilike1.png"));
            ui->pushButton_14->setStyleSheet(Ilike1Style());
            ui->pushButton_14->setToolTip(("我喜欢"));
            int row=playlist->currentIndex();
            QString Text=ui->listWidget_3->item(row)->text();
            QListWidgetItem *ITEMM2=new QListWidgetItem;
            ITEMM2->setIcon(QIcon(":/image/image/like_outline_32px_1101681_easyicon.net.png"));
            ITEMM2->setText(QString("%1").arg(Text));
            ui->listWidget_2->addItem(ITEMM2);
            playlist_2->addMedia(playlist->media(row));
            QSqlQuery query;
            model->setTable("LocalMusic");
            model->select();
            QString MusicName=model->data(model->index(row,1)).toString();
            QString FileName=model->data(model->index(row,2)).toString();
            model->setData(model->index(row,3),1);
            model->submitAll();
            query.exec("select * from LikeMusic");
            query.exec(QString("insert into LikeMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(MusicName).arg(FileName));
        }
        else
        {


              QMessageBox::information(this,("提示"),("该歌曲已添加                              ."),QMessageBox::Yes);
        }

    }

}


void Widget::on_pushButton_18_clicked()//查找歌曲
{
    QString text=ui->lineEdit->text();
    if(!text.isEmpty())
    {
    load.clear();
    ui->listWidget_4->clear();
   std::string MusicName=ui->lineEdit->text().toStdString();
   const char* MusicName1=MusicName.c_str();
   ui->stackedWidget->setCurrentIndex(3);
   int Count=ui->listWidget_3->count();
   pushbuttonstyle_4();
   for(int i=0;i<Count;i++)
   {


       QString Text=ui->listWidget_3->item(i)->text();
       QString Name=Text.split(" - ").last();
       std::string Name1=Name.toStdString();
       const  char *Name2=Name1.c_str();
       QString Author=Text.remove(" - "+Name);
       std::string Author1=Author.toStdString();
       const char *Author2=Author1.c_str();
       if(strstr(Name2,MusicName1)||strstr(Author2,MusicName1))
       {

        QString Text=ui->listWidget_3->item(i)->text();
        QListWidgetItem *item20=new QListWidgetItem;
        item20->setIcon(QIcon(":/image/image/sss.png"));
        item20->setText(Text);
        ui->listWidget_4->addItem(item20);
        load.push_back(i);

       }
   }
   ui->lineEdit->clear();
}
}

void Widget::on_listWidget_4_doubleClicked(const QModelIndex &index)//双击播放ListWidget_4 搜索列表
{


    music->setPlaylist(playlist);
    playlist->setCurrentIndex(load[index.row()]);
    music->play();
}

void Widget::on_listWidget_4_customContextMenuRequested(const QPoint &pos)//listWidget_4 菜单 搜索列表
{
    QListWidgetItem *ITEM20=ui->listWidget_4->itemAt(pos);
    if(ITEM20==NULL)
    {

        return ;
    }
    QMenu *MENU20=new QMenu(this);
    MENU20->setStyleSheet(
              MenuStyle()
                );
    QAction *Action =new QAction(this);//播放
    QAction *Action_A=new QAction(this);//暂停
    QAction *Action1 =new QAction(this);//添加至我喜欢
    QAction *Action2 =new QAction(this);//添加至我的收藏
    QAction *Action3 =new QAction(this);//删除歌曲
    QAction *Action4 =new QAction(this);//歌曲信息
    Action->setIcon(QIcon(":/image/image/zt13.png"));
    Action->setText(("播放"));
    Action_A->setIcon(QIcon(":/image/image/bofang1.png"));
    Action_A->setText(("暂停"));
    Action1->setIcon(QIcon(":/image/image/like_outline_32px_1101681_easyicon.net.png"));
    Action1->setText(("添加至我喜欢"));
    Action2->setIcon(QIcon(":/image/image/list_32px_1074296_easyicon.net.png"));
    Action2->setText(("添加至我的收藏"));
    Action3->setIcon(QIcon(":/image/image/delete_32px_1168909_easyicon.net.png"));
    Action3->setText(("删除歌曲"));
    Action4->setIcon(QIcon(":/image/image/inf.png"));
    Action4->setText(("歌曲信息"));
    connect(Action,&QAction::triggered,this,&Widget::Action_slot);
    connect(Action_A,&QAction::triggered,this,&Widget::action11_slot);
    connect(Action1,&QAction::triggered,this,&Widget::Action_1_slot);
    connect(Action2,&QAction::triggered,this,&Widget::Action_2_slot);
    connect(Action3,&QAction::triggered,this,&Widget::Action_3_slot);
    connect(Action4,&QAction::triggered,this,&Widget::Action_4_slot);
    int row=ui->listWidget_4->currentIndex().row();
    if(music->playlist()==playlist)
    {
        if(load[row]==playlist->currentIndex())
        {

            if(music->state()==QMediaPlayer::PlayingState)
            {
                MENU20->addAction(Action_A);

            }
            else
            {
                 MENU20->addAction(Action);
            }

        }
        else
        {
             MENU20->addAction(Action);
        }

    }
    else
    {
         MENU20->addAction(Action);
    }
    MENU20->addAction(Action1);
    MENU20->addAction(Action2);
    MENU20->addAction(Action4);
    MENU20->addAction(Action3);
    MENU20->exec(QCursor::pos());
    delete Action;
    delete Action1;
    delete Action2;
    delete Action3;
    delete Action4;
    delete MENU20;
}
void Widget::Action_slot()//播放
{

    int row=ui->listWidget_4->currentIndex().row();

    if(music->playlist()==playlist)
    {

        if(load[row]==playlist->currentIndex())
        {


                music->play();

        }
        else
        {
            playlist->setCurrentIndex(load[row]);

            music->play();

            ui->listWidget_3->item(load[row])->setSelected(true);

        }
    }
        else
        {
         music->setPlaylist(playlist);
         playlist->setCurrentIndex(load[row]);
         music->play();
        }
}
void Widget::Action_1_slot()//添加至我喜欢
{
    model->setTable("LocalMusic");
    model->select();
    int row=ui->listWidget_4->currentIndex().row();
    int flag=model->data(model->index(load[row],3)).toInt();
    if(flag==0)
    {
    QString Text=ui->listWidget_3->item(load[row])->text();
    QListWidgetItem *ITEMM=new QListWidgetItem;
    ITEMM->setIcon(QIcon(":/image/image/like_outline_32px_1101681_easyicon.net.png"));
    ITEMM->setText(QString("%1").arg(Text));
    ui->listWidget_2->addItem(ITEMM);
    QSqlQuery query;
    playlist_2->addMedia(playlist->media(load[row]));
    model->setTable("LocalMusic");
    model->select();
    QString MusicName=model->data(model->index(load[row],1)).toString();
    QString FileName=model->data(model->index(load[row],2)).toString();
    model->setTable("LocalMusic");
    model->select();
    model->setData(model->index(load[row],3),1);
    model->submitAll();
    query.exec("select * from LikeMusic");
    query.exec(QString("insert into LikeMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(MusicName).arg(FileName));
    ui->stackedWidget->setCurrentIndex(1);
    pushbuttonstyle_2();
    if(music->playlist()==playlist)
    {

    if(playlist->currentIndex()==load[row])
    {
    ui->pushButton_14->setIcon(QIcon(":/image/image/image/Ilike1.png"));
    ui->pushButton_14->setToolTip(("我喜欢"));
    }

    }
    }
    else
    {

     QMessageBox::information(this,("提示"),("该歌曲已添加                              ."),QMessageBox::Yes);

    }

}
void Widget::Action_2_slot()//添加至我的收藏
{
    int row=ui->listWidget_4->currentIndex().row();
    QString Text=ui->listWidget_3->item(load[row])->text();
    QListWidgetItem *ITEMM1=new QListWidgetItem;
    ITEMM1->setIcon(QIcon(":/image/image/music_not_25.570093457944px_1171234_easyicon.net.png"));
    ITEMM1->setText(QString("%1").arg(Text));
    ui->listWidget->addItem(ITEMM1);
    model->setTable("LocalMusic");
    model->select();
    playlist_3->addMedia(playlist->media(load[row]));
    QSqlQuery query;
    QString MusicName=model->data(model->index(load[row],1)).toString();
    QString FileName=model->data(model->index(load[row],2)).toString();

    query.exec("select * from  CollectMusic");
    query.exec(QString("insert into  CollectMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(MusicName).arg(FileName));
    ui->stackedWidget->setCurrentIndex(2);
    pushbuttonstyle_3();


}
void Widget::Action_4_slot()//歌曲信息
{

    int row=ui->listWidget_4->currentIndex().row();
    QString temp=ui->listWidget_4->currentIndex().data().toString();
    QString MusicName=temp.split(" - ").last();
    QString Author=temp.remove(" - "+MusicName);
    model->setTable("LocalMusic");
    model->select();
    QString FileName=model->data(model->index(load[row],2)).toString();
    QString time;
    if(music->playlist()==playlist)
    {

        if(load[row]==playlist->currentIndex())
        {
            time=Time(music->duration());
        }
        else
        {
            time="00:00";
        }
    }
    else
    {
        time="00:00";
    }
    QMessageBox::about(this,"歌曲信息",QString("歌曲名 : %1  \n"
                                             "作者 : %2 \n"
                                             "时长 : %3 \n"
                                             "文件路径 : %4\n").arg(MusicName).arg(Author).arg(time).arg(FileName));

}

void Widget::Action_3_slot()//删除
{

    if(music->playlist()==playlist)
    {

        int Row=playlist->currentIndex();
        int row=ui->listWidget_4->currentIndex().row();
        if(load[row]<Row)
        {
            int Position=0;
            if(music->state()==QMediaPlayer::PlayingState)
            {
                Position=music->position();
            }
            playlist->setCurrentIndex(0);
            ui->listWidget_3->takeItem(load[row]);
            ui->listWidget_4->takeItem(row);
            playlist->removeMedia(load[row],load[row]);
            model->setTable("LocalMusic");
            model->select();
            model->removeRow(load[row]);
            model->submitAll();
            music->setPlaylist(playlist);
            playlist->setCurrentIndex(Row-1);
            music->setPosition(Position);
            ui->horizontalSlider->setValue(Position);
            music->play();
        }
        else
        {
            ui->listWidget_4->takeItem(row);
            ui->listWidget_3->takeItem(load[row]);
            playlist->removeMedia(load[row],load[row]);
            model->setTable("LocalMusic");
            model->select();
            model->removeRow(load[row]);
            model->submitAll();

        }


    }
    else
    {
        int row=ui->listWidget_4->currentIndex().row();
        ui->listWidget_4->takeItem(row);
        ui->listWidget_3->takeItem(load[row]);
        playlist->removeMedia(load[row],load[row]);
        model->setTable("LocalMusic");
        model->select();
        model->removeRow(load[row]);
        model->submitAll();
    }
}

void Widget::CreateSortCut()//创建快捷键
{
    QShortcut *QUIT=new QShortcut(Qt::Key_Escape,this);//退出
    connect(QUIT,&QShortcut::activated,QCoreApplication::quit);
    QShortcut *play=new QShortcut(Qt::Key_Space,this);//播放/暂停
    connect(play,&QShortcut::activated,this,&Widget::Key_Space_slot);
    QShortcut *next=new QShortcut(Qt::Key_Right,this);//下一首
    QShortcut *next1=new QShortcut(Qt::Key_6,this);//下一首
    connect(next,&QShortcut::activated,this,&Widget::Next_slot);
    connect(next1,&QShortcut::activated,this,&Widget::Next_slot);
    QShortcut *pre=new QShortcut(Qt::Key_Left,this);//上一首
    QShortcut *pre1=new QShortcut(Qt::Key_4,this);//上一首
    connect(pre,&QShortcut::activated,this,&Widget::Pre_slot);
    connect(pre1,&QShortcut::activated,this,&Widget::Pre_slot);
    QShortcut *nextlist=new QShortcut(Qt::Key_D,this);//转换列表
    connect(nextlist,&QShortcut::activated,this,&Widget::nextlist_slot);
    QShortcut *prelist=new QShortcut(Qt::Key_A,this);//转换列表
    connect(prelist,&QShortcut::activated,this,&Widget::prelist_slot);
    QShortcut *addV=new QShortcut(Qt::Key_W,this);//音量加
    connect(addV,&QShortcut::activated,this,&Widget::addV_slot);
    QShortcut *subV=new QShortcut(Qt::Key_S,this);//音量减
    connect(subV,&QShortcut::activated,this,&Widget::subV_slot);
    QShortcut *Locole=new QShortcut(Qt::Key_Q,this);//定位
    connect(Locole,&QShortcut::activated,this,&Widget::Locale_slot);
    QShortcut *change=new QShortcut(Qt::Key_E,this);//改变播放模式
    connect(change,&QShortcut::activated,this,&Widget::change_slot);
    QShortcut *love=new QShortcut(Qt::Key_R,this);//添加我喜欢
    connect(love,&QShortcut::activated,this,&Widget::love_slot);
    QShortcut *multiselect=new QShortcut(Qt::Key_X,this);//多选/取消多选
    connect(multiselect,&QShortcut::activated,this,&Widget::Multiselect_slot);



}
void Widget::Key_Space_slot()//播放/暂停
{
    ListFocus();
    if(music->state()==QMediaPlayer::PlayingState)
    {
        music->pause();
    }
    else
    {
        music->play();
    }
}
void Widget::Multiselect_slot()//多选
{

    if(ui->stackedWidget->currentIndex()==0)
    {

        if(ui->listWidget_3->selectionMode()==QListWidget::SingleSelection)
        {

            ui->listWidget_3->setSelectionMode(QListWidget::MultiSelection);

        }
        else if(ui->listWidget_3->selectionMode()==QListWidget::MultiSelection)
        {
            ui->listWidget_3->setSelectionMode(QListWidget::SingleSelection);
            if(music->playlist()==playlist)
            {

                ui->listWidget_3->item(playlist->currentIndex())->setSelected(true);
            }
            else
            {
                ui->listWidget_3->item(0)->setSelected(true);
            }

        }

    }
    else if(ui->stackedWidget->currentIndex()==1)
    {
        if(ui->listWidget_2->selectionMode()==QListWidget::SingleSelection)
        {

            ui->listWidget_2->setSelectionMode(QListWidget::MultiSelection);

        }
        else if(ui->listWidget_2->selectionMode()==QListWidget::MultiSelection)
        {
            ui->listWidget_2->setSelectionMode(QListWidget::SingleSelection);
            if(music->playlist()==playlist_2)
            {

                ui->listWidget_2->item(playlist_2->currentIndex())->setSelected(true);
            }
            else
            {
                ui->listWidget_2->item(0)->setSelected(true);
            }
        }

    }
    else if(ui->stackedWidget->currentIndex()==2)
    {

        if(ui->listWidget->selectionMode()==QListWidget::SingleSelection)
        {

            ui->listWidget->setSelectionMode(QListWidget::MultiSelection);

        }
        else if(ui->listWidget->selectionMode()==QListWidget::MultiSelection)
        {
            ui->listWidget->setSelectionMode(QListWidget::SingleSelection);
            if(music->playlist()==playlist_3)
            {

                ui->listWidget->item(playlist_3->currentIndex())->setSelected(true);
            }
            else
            {
                ui->listWidget->item(0)->setSelected(true);
            }
        }

    }
}

void Widget::Next_slot()//下一首
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
ListFocus();
    if(music->playlist()==playlist)
     {
        ui->stackedWidget->setCurrentIndex(0);
        pushbuttonstyle();
        int currentIndex;
        if(playlist->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
        currentIndex=playlist->currentIndex();

        if(++currentIndex==playlist->mediaCount())
        {
            currentIndex=0;

        }

        }
          ui->listWidget_3->scrollToItem(ui->listWidget_3->item(currentIndex));
         playlist->setCurrentIndex(currentIndex);
         if(list1[currentIndex]==0){
             QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(currentIndex)->text());
             myitem->setToolTip(ui->listWidget_3->item(currentIndex)->text());

         ui->listWidget_5->addItem(myitem);
          playlist_4->addMedia(QUrl::fromLocalFile(FilePath[currentIndex]));
         map.push_back(currentIndex);
         list1[currentIndex]++;
         }
         else
         {
             list1[currentIndex]++;
         }

    }
    else if(music->playlist()==playlist_2)
    {
        ui->stackedWidget->setCurrentIndex(1);
        pushbuttonstyle_2();
        int currentIndex;
        if(playlist_2->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist_2->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
        currentIndex=playlist_2->currentIndex();

        if(++currentIndex==playlist_2->mediaCount())
        {
            currentIndex=0;

        }

        }
          ui->listWidget_2->scrollToItem(ui->listWidget_2->item(currentIndex));
        playlist_2->setCurrentIndex(currentIndex);
    }
    else if(music->playlist()==playlist_3)
    {

        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
        int currentIndex;
        if(playlist_3->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist_3->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
         currentIndex=playlist_3->currentIndex();

        if(++currentIndex==playlist_3->mediaCount())
        {
            currentIndex=0;

        }

        }
          ui->listWidget->scrollToItem(ui->listWidget->item(currentIndex));
        playlist_3->setCurrentIndex(currentIndex);

    }
    else if(music->playlist()==playlist_4)
    {

        ui->stackedWidget->setCurrentIndex(4);
        pushbuttonstyle_5();
        int currentIndex;
        if(playlist_4->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist_4->mediaCount();
            currentIndex=qrand()%row;
        }
        else
        {
         currentIndex=playlist_4->currentIndex();

        if(++currentIndex==playlist_4->mediaCount())
        {
            currentIndex=0;

        }

        }
          ui->listWidget_5->scrollToItem(ui->listWidget_5->item(currentIndex));
        playlist_4->setCurrentIndex(currentIndex);
    }
    music->play();
}
void Widget::Pre_slot()//上一首
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
    ListFocus();
    if(music->playlist()==playlist)
    {
        ui->stackedWidget->setCurrentIndex(0);
        pushbuttonstyle();
        int currentIndex;
        if(playlist->playbackMode()==QMediaPlaylist::Random)
        {
            int row=playlist->mediaCount();
            currentIndex=qrand()%row;

        }
        else
        {
        currentIndex=playlist->currentIndex();

        if(--currentIndex<0)
        {

            currentIndex=0;


        }

        }
          ui->listWidget_3->scrollToItem(ui->listWidget_3->item(currentIndex));
       playlist->setCurrentIndex(currentIndex);
       if(list1[currentIndex]==0){
           QListWidgetItem *myitem = new QListWidgetItem(QIcon(":/image/image/nextbo.png"),ui->listWidget_3->item(currentIndex)->text());
           myitem->setToolTip(ui->listWidget_3->item(currentIndex)->text());

       ui->listWidget_5->addItem(myitem);
        playlist_4->addMedia(QUrl::fromLocalFile(FilePath[currentIndex]));
       map.push_back(currentIndex);
       list1[currentIndex]++;
       }
       else
       {
           list1[currentIndex]++;
       }

    }
    else if(music->playlist()==playlist_2)
    {

        ui->stackedWidget->setCurrentIndex(1);
        pushbuttonstyle_2();
         int currentIndex;

         if(playlist_2->playbackMode()==QMediaPlaylist::Random)
         {

             int row=playlist_2->mediaCount();
             currentIndex=qrand()%row;
         }
         else
         {
        currentIndex=playlist_2->currentIndex();
        if(--currentIndex<0)
        {
            currentIndex=0;
        }
         }
           ui->listWidget_2->scrollToItem(ui->listWidget_2->item(currentIndex));
        playlist_2->setCurrentIndex(currentIndex);
    }
    else if(music->playlist()==playlist_3)
    {
        ui->stackedWidget->setCurrentIndex(2);
        pushbuttonstyle_3();
         int currentIndex;
         if(playlist_3->playbackMode()==QMediaPlaylist::Random)
         {
             int row=playlist_3->mediaCount();
             currentIndex=qrand()%row;
         }
           else
         {
        currentIndex=playlist_3->currentIndex();

        if(--currentIndex<0)
        {
            currentIndex=0;
        }
         }
           ui->listWidget->scrollToItem(ui->listWidget->item(currentIndex));
        playlist_3->setCurrentIndex(currentIndex);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(4);
        pushbuttonstyle_5();
         int currentIndex;
         if(playlist_4->playbackMode()==QMediaPlaylist::Random)
         {
             int row=playlist_4->mediaCount();
             currentIndex=qrand()%row;
         }
           else
         {
        currentIndex=playlist_4->currentIndex();

        if(--currentIndex<0)
        {
            currentIndex=0;
        }
         }
           ui->listWidget_5->scrollToItem(ui->listWidget_5->item(currentIndex));
        playlist_4->setCurrentIndex(currentIndex);
    }
     music->play();

}
void Widget::nextlist_slot()//下一个播放列表
{

    int current=ui->stackedWidget->currentIndex();

    if(current<3)
    {
        current++;
        ui->stackedWidget->setCurrentIndex(current);
        if(current==0)
        {

            pushbuttonstyle();

        }
        else if(current==1)
        {

            pushbuttonstyle_2();

        }
        else if(current==2)
        {

            pushbuttonstyle_3();

        }
        else
        {
            pushbuttonstyle_5();
        }

    }


}
void Widget::prelist_slot()//上一个播放列表
{

    int current=ui->stackedWidget->currentIndex();
    if(current>0)
    {

        current--;
        ui->stackedWidget->setCurrentIndex(current);

        if(current==0)
        {

            pushbuttonstyle();

        }
        else if(current==1)
        {

            pushbuttonstyle_2();

        }
        else if(current==2)
        {

            pushbuttonstyle_3();

        }
        else {
            pushbuttonstyle_5();
        }


    }


}
void Widget::addV_slot()//增加音量
{

    ui->verticalSlider->show();
    int values=ui->verticalSlider->value();
    if(values<100)
    {

        values++;
        ui->verticalSlider->setValue(values);

    }
}
void Widget::subV_slot()//减少音量
{

    ui->verticalSlider->show();
    int values=ui->verticalSlider->value();
    if(values>0)
    {

        values--;
        ui->verticalSlider->setValue(values);

    }
}
void Widget::Locale_slot()//定位
{    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }

    if(music->playlist()==playlist)
    {



        if(ui->listWidget_3->count()==0){
        return;
        }
        else{
            ui->stackedWidget->setCurrentIndex(0);
          ui->listWidget_3->setFocus();
        pushbuttonstyle();
        if(ui->listWidget_3->selectionMode()==QListWidget::SingleSelection)
       {
            ui->listWidget_3->item(playlist->currentIndex())->setSelected(true);
            ui->listWidget_3->scrollToItem(ui->listWidget_3->item(playlist->currentIndex()));
    }
        }
    }
    else if(music->playlist()==playlist_2)
    {


        if(ui->listWidget_2->count()==0) return ;
        else{
              ui->stackedWidget->setCurrentIndex(1);
         ui->listWidget_2->setFocus();
        pushbuttonstyle_2();
        if(ui->listWidget_2->selectionMode()==QListWidget::SingleSelection)
       { ui->listWidget_2->item(playlist_2->currentIndex())->setSelected(true);
         ui->listWidget_2->scrollToItem(ui->listWidget_2->item(playlist_2->currentIndex()));
        }
        }

    }
    else if(music->playlist()==playlist_3)
    {



        if(ui->listWidget->count()==0){
            return ;
        }
        else
        {
         ui->stackedWidget->setCurrentIndex(2);
        ui->listWidget->setFocus();
        pushbuttonstyle_3();
        if(ui->listWidget->selectionMode()==QListWidget::SingleSelection)
        {
            ui->listWidget->item(playlist_3->currentIndex())->setSelected(true);
            ui->listWidget->scrollToItem(ui->listWidget->item(playlist_3->currentIndex()));

        }
        }
    }
    else
    {
        if(ui->listWidget->count()==0){
            return ;
        }
        else
        {
         ui->stackedWidget->setCurrentIndex(4);
        ui->listWidget->setFocus();
        pushbuttonstyle_5();

            ui->listWidget_5->item(playlist_4->currentIndex())->setSelected(true);
            ui->listWidget_5->scrollToItem(ui->listWidget_5->item(playlist_4->currentIndex()));


        }
    }
}
void Widget::change_slot()//改变播放模式
{

    if(playlist->playbackMode()==QMediaPlaylist::Loop)
    {

        ui->pushButton_9->setIcon(QIcon(":/image/image/image/play-random.png"));
        ui->pushButton_9->setToolTip(("随机播放"));
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        playlist_2->setPlaybackMode(QMediaPlaylist::Random);
        playlist_3->setPlaybackMode(QMediaPlaylist::Random);
    }
    else if(playlist->playbackMode()==QMediaPlaylist::Random)
    {
        ui->pushButton_9->setIcon(QIcon(":/image/image/image/loop-one.png"));
        ui->pushButton_9->setToolTip(("单曲循环"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        playlist_2->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        playlist_3->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);


    }
    else if(playlist->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
    {
        ui->pushButton_9->setIcon(QIcon(":/image/image/loop.png"));
        ui->pushButton_9->setToolTip(("顺序播放"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        playlist_2->setPlaybackMode(QMediaPlaylist::Loop);
        playlist_3->setPlaybackMode(QMediaPlaylist::Loop);

    }
}
void Widget::love_slot()//添加至我喜欢
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0&&ui->listWidget_5->count()==0){
        return;
    }
    if(music->playlist()==playlist)
    {

        int row=playlist->currentIndex();
        model->setTable("LocalMusic");
        model->select();
        int flag=model->data(model->index(row,3)).toInt();
        if(flag==0)
        {
            ui->pushButton_14->setIcon(QIcon(":/image/image/Ilike.png"));
            ui->pushButton_14->setStyleSheet(IlikeStyle());
            ui->pushButton_14->setToolTip(("我喜欢"));
            int row=playlist->currentIndex();
            QString Text=ui->listWidget_3->item(row)->text();
            QListWidgetItem *ITEMM2=new QListWidgetItem;
            ITEMM2->setIcon(QIcon(":/image/image/like_outline_32px_1101681_easyicon.net.png"));
            ITEMM2->setText(QString("%1").arg(Text));
            ui->listWidget_2->addItem(ITEMM2);
            playlist_2->addMedia(playlist->media(row));
            QSqlQuery query;
            model->setTable("LocalMusic");
            model->select();
            QString MusicName=model->data(model->index(row,1)).toString();
            QString FileName=model->data(model->index(row,2)).toString();
            model->setData(model->index(row,3),1);
            model->submitAll();
            query.exec("select * from LikeMusic");
            query.exec(QString("insert into LikeMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(MusicName).arg(FileName));
        }

    }

}

void Widget::on_lineEdit_returnPressed()//输入框回车查找
{
    QString text=ui->lineEdit->text();
    if(!text.isEmpty())
    {
        load.clear();
    ui->listWidget_4->clear();
   std::string MusicName=ui->lineEdit->text().toStdString();
   const char* MusicName1=MusicName.c_str();
   ui->stackedWidget->setCurrentIndex(3);
   int Count=ui->listWidget_3->count();
   pushbuttonstyle_4();
   for(int i=0;i<Count;i++)
   {

       QString Text=ui->listWidget_3->item(i)->text();
       QString Name=Text.split(" - ").last();
       std::string Name1=Name.toStdString();
       const  char *Name2=Name1.c_str();
       QString Author=Text.remove(" - "+Name);
       std::string Author1=Author.toStdString();
       const char *Author2=Author1.c_str();
       if(strstr(Name2,MusicName1)||strstr(Author2,MusicName1))
       {
        QString Text=ui->listWidget_3->item(i)->text();
        QListWidgetItem *item20=new QListWidgetItem;
        item20->setIcon(QIcon(":/image/image/sss.png"));
        item20->setText(Text);
        ui->listWidget_4->addItem(item20);
        load.push_back(i);

       }
   }
   ui->lineEdit->clear();
    }
}
void Widget::PlaylistModel_slot(QMediaPlaylist::PlaybackMode model)//播放模式改变
{

    if(model==QMediaPlaylist::Loop)//顺序播放
    {
        ui->pushButton_9->setIcon(QIcon(":/image/image/image/loop.png"));
        ui->pushButton_9->setStyleSheet(LoopStyle());
        ui->pushButton_9->setToolTip(("顺序播放"));

    }
    else if(model==QMediaPlaylist::Random)//随机播放
    {
        ui->pushButton_9->setIcon(QIcon(":/image/image/image/play-random.png"));
        ui->pushButton_9->setStyleSheet(RandomStyle());
        ui->pushButton_9->setToolTip(("随机播放"));

    }
    else if(model==QMediaPlaylist::CurrentItemInLoop)//单曲循环
    {
        ui->pushButton_9->setIcon(QIcon(":/image/image/image/loop-one.png"));
           ui->pushButton_9->setStyleSheet(LoopOneStyle());
        ui->pushButton_9->setToolTip(("单曲循环"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    }
}

void Widget::on_pushButton_19_clicked()
{
ListFocus();


//


}


void Widget::on_pushButton_20_clicked()
{
    ListFocus();
   QPropertyAnimation *a = new QPropertyAnimation(ui->pushButton_5,"geometry");
   QPropertyAnimation *a1 = new QPropertyAnimation(ui->pushButton_6,"geometry");
   QPropertyAnimation *a2 = new QPropertyAnimation(ui->pushButton,"geometry");
   QPropertyAnimation *a3 =new QPropertyAnimation(ui->pushButton_13,"geometry");
   a->setDuration(500);
   a1->setDuration(600);
   a2->setDuration(700);
   a3->setDuration(800);
    if(ui->pushButton_5->y() == -32)
    {
        a->setStartValue(QRect(1020,-32,32,32));
        a->setEndValue(QRect(1020,20,32,32));
        a->setEasingCurve(QEasingCurve::InBounce);

        a1->setStartValue(QRect(968,-32,32,32));
        a1->setEndValue(QRect(968,20,32,32));
        a1->setEasingCurve(QEasingCurve::InBounce);

        a2->setStartValue(QRect(916,-32,32,32));
        a2->setEndValue(QRect(916,20,32,32));
        a2->setEasingCurve(QEasingCurve::InBounce);


        a3->setStartValue(QRect(864,-32,32,32));
        a3->setEndValue(QRect(864,20,32,32));
        a3->setEasingCurve(QEasingCurve::InBounce);

    }
    else
    {

        a->setStartValue(QRect(1020,20,32,32));
        a->setEndValue(QRect(1020,-32,32,32));
        a->setEasingCurve(QEasingCurve::InBounce);

        a1->setStartValue(QRect(968,20,32,32));
        a1->setEndValue(QRect(968,-32,32,32));
        a1->setEasingCurve(QEasingCurve::InBounce);

        a2->setStartValue(QRect(916,20,32,32));
        a2->setEndValue(QRect(916,-32,32,32));
        a2->setEasingCurve(QEasingCurve::InBounce);


        a3->setStartValue(QRect(864,20,32,32));
        a3->setEndValue(QRect(864,-32,32,32));
        a3->setEasingCurve(QEasingCurve::InBounce);
    }
    a->start();
    a1->start();
    a2->start();
    a3->start();


}
inline void Widget::ListFocus(){

    if(music->playlist() == playlist){

        ui->listWidget_3->setFocus();

    }
    else if(music->playlist() == playlist_2){
         ui->listWidget_2->setFocus();
    }
    else if(music->playlist() == playlist_3){
         ui->listWidget->setFocus();
    }
    else
    {
        ui->listWidget_5->setFocus();
    }

}
void Widget::ListItemToolTip()
{

    for(int i=0;i<ui->listWidget_3->count();i++)
    {
        ui->listWidget_3->item(i)->setToolTip(ui->listWidget_3->item(i)->text());
    }
    for(int i=0;i<ui->listWidget_2->count();i++)
    {
        ui->listWidget_2->item(i)->setToolTip(ui->listWidget_2->item(i)->text());

                
    }
    for(int i=0;i<ui->listWidget->count();i++){

        ui->listWidget->item(i)->setToolTip(ui->listWidget->item(i)->text());

    }
    for(int i=0;i<ui->listWidget_4->count();i++)
    {
        ui->listWidget_4->item(i)->setToolTip(ui->listWidget_4->item(i)->text());

    }
    for(int i=0;i<ui->listWidget_5->count();i++)
    {
        ui->listWidget_5->item(i)->setToolTip(ui->listWidget_5->item(i)->text());
    }

}


void Widget::on_listWidget_5_doubleClicked(const QModelIndex &index)
{
    music->setPlaylist(playlist_4);
    int currentIndex = index.row();
    playlist_4->setCurrentIndex(currentIndex);
    music->play();
}

void Widget::on_listWidget_5_customContextMenuRequested(const QPoint &pos)//播放历史
{
  QListWidgetItem *curItem=ui->listWidget_5->itemAt(pos);
  if(curItem==NULL)
  {
      return ;
  }
  QMenu *Menu=new QMenu(this);
  Menu->setStyleSheet(
             MenuStyle()

              );
  QAction *play=new QAction(this);//播放
  QAction *puase=new QAction(this);//暂停
  QAction *information=new QAction(this);//歌曲信息
  QAction *Clear = new QAction(this);
  play->setIcon(QIcon(":/image/image/zt13.png"));
  play->setText(("播放"));
  puase->setIcon(QIcon(":/image/image/bofang1.png"));
  puase->setText(("暂停"));
  information->setIcon(QIcon(":/image/image/inf.png"));
  information->setText(("歌曲信息"));

  Clear->setText(("清除播放记录"));
  Clear->setIcon(QIcon(":/image/image/quxiao.png"));

      if(music->playlist()==playlist_4)
      {
          if(ui->listWidget_5->currentIndex().row()==playlist_4->currentIndex())
          {
              if(music->state()==QMediaPlayer::PlayingState)
              {
                  Menu->addAction(puase);
              }
              else
              {
                  Menu->addAction(play);
              }
          }
          else
          {
              Menu->addAction(play);
          }
      }
      else
      {
          Menu->addAction(play);
      }

  Menu->addAction(information);

  Menu->addAction(Clear);

  connect(play,&QAction::triggered,this,&Widget::playMusic_slot);
  connect(puase,&QAction::triggered,this,&Widget::action11_slot);
  connect(information,&QAction::triggered,this,&Widget::listWidget_5_info);
  connect(Clear,&QAction::triggered,this,&Widget::clearListWidget_slot);
  Menu->exec(QCursor::pos());
  delete Menu;
  delete  play;
  delete  puase;
  delete  information;

  delete  Clear;
}
void Widget::playMusic_slot()
{
  if(music->playlist()==playlist_4)
  {
  if(ui->listWidget_5->currentIndex().row()==playlist_4->currentIndex())
  {


          music->play();

  }
  else
  {
      playlist_4->setCurrentIndex(ui->listWidget_5->currentIndex().row());
      music->play();
  }
  }
  else
  {
      music->setPlaylist(playlist_4);
  playlist_4->setCurrentIndex(ui->listWidget_5->currentIndex().row());

  music->play();
  }

}

void Widget::listWidget_5_info()
{
  {
      int row=ui->listWidget_5->currentIndex().row();
      QString temp=ui->listWidget_5->currentIndex().data().toString();
      QString MusicName=temp.split(" - ").last();
      QString Author=temp.remove(" - "+MusicName);

      QString FileName=FilePath[row];
      QString time;
      if(music->playlist()==playlist_4)
      {

          if(row==playlist_4->currentIndex())
          {
              time=Time(music->duration());
          }
          else
          {
              time="00:00";
          }
      }
      else
      {
          time="00:00";



      }
      QMessageBox::about(this,"歌曲信息",QString("歌曲名 : %1  \n"
                                               "作者 : %2 \n"
                                               "时长 : %3\n "
                                               "文件路径 : %4\n").arg(MusicName).arg(Author).arg(time).arg(FileName));

  }
}
void Widget::clearListWidget_slot()
{
  ClearHistory_Slot();
}
