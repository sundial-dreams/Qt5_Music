#include "dialog.h"
#include "ui_dialog.h"
#include<QPixmap>
#include<QPalette>
#include<QIcon>
#include<QMenu>
#include<QAction>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QShortcut>
#include<QGraphicsDropShadowEffect>
#include<QFileDialog>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
    {
    ui->setupUi(this);
    ui->frame->setAutoFillBackground(true);
    setAutoFillBackground(true);
    setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(5,5);
    effect->setColor(QColor(0,0,0,60));
    effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(effect);

    QSqlQuery query;
    query.exec("select * from Bizi_DATA");//壁纸数据
    query.next();
    QString FileName=query.value(0).toString();
    QString FileName1;
    if(FileName.isEmpty())
    {
    FileName1 = ":/image/image/background/bg4.jpg";
    }
    else
    {

        FileName1 = FileName;
    }
    ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:3px;border-image: url(%1);}").arg(FileName1));
    query.exec("select * from Toumin_DATA");//透明度数据
    query.next();
    QString Temp=query.value(0).toString();
    if(Temp=="")
    {
        TouMin=1.0;
    }
    else
    {
        TouMin=Temp.toDouble();
    }
    ui->frame->setWindowOpacity(TouMin);//设置透明度
    ui->pushButton_2->setIconSize(QSize(24,24));
    ui->pushButton_2->setIcon(QIcon(":/image/image/image/pase.png"));
    ui->pushButton->setToolTip(("上一首"));
    ui->pushButton_2->setToolTip(("暂停"));
    ui->pushButton_3->setToolTip(("下一首"));
    ui->pushButton_4->setToolTip(("关闭"));
    ui->pushButton_5->setToolTip(("最小化"));
    ui->horizontalSlider->setToolTip(("播放进度"));
    music=new QMediaPlayer(this);
    playlist=new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    play=new QAction(this);//播放
    pause=new QAction(this);//暂停
    next=new QAction(this);//下一首
    pre =new QAction(this);//上一首
    back=new QAction(this);//返回
    play->setIcon(QIcon(":/image/image/zt13.png"));
    play->setText(("播放"));
    pause->setIcon(QIcon(":/image/image/bofang1.png"));
    pause->setText(("暂停"));
    next->setIcon(QIcon(":/image/image/next1.png"));
    next->setText(("下一首"));
    pre->setIcon(QIcon(":/image/image/pre1.png"));
    pre->setText(("上一首"));
    back->setIcon(QIcon(":/image/image/退出 (3).png"));
    back->setText(("返回主窗口"));


    action=new QAction(this);//设置皮肤
    action1=new QAction(this);//默认皮肤1
    action2=new QAction(this);//默认皮肤2
    action3=new QAction(this);//默认皮肤3
    action4=new QAction(this);//自定义皮肤
    action->setIcon(QIcon(":/image/image/pf.png"));
    action->setText(("设置皮肤"));

    action1->setIcon(QIcon(":/image/image/pf2.png"));
    action1->setText(("棕色"));
    action2->setIcon(QIcon(":/image/image/pf5.png"));
    action2->setText(("晨曦"));
    action3->setIcon(QIcon(":/image/image/pf3.png"));
    action3->setText(("天空"));
    action4->setIcon(QIcon(":/image/image/pf4.png"));
    action4->setText(("自定义"));

    QMenu *Menu=new QMenu(this);//皮肤菜单
    Menu->addAction(action1);
    Menu->addAction(action2);
    Menu->addAction(action3);
    Menu->addAction(action4);
    Menu->setStyleSheet(
                " QMenu {\
                background-color: white; /* sets background of the menu 设置整个菜单区域的背景色，我用的是白色：white*/\
                border: 3px solid white;/*整个菜单区域的边框粗细、样式、颜色*/\
            }\
            QMenu::item {\
                /* sets background of menu item. set this to something non-transparent\
                    if you want menu color and menu item color to be different */\
                background-color: transparent;\
                padding:5px 30px;/*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/\
                margin:0px 0px;/*设置菜单项的外边距*/\
                border-bottom:0px solid #DBDBDB;/*为菜单项之间添加横线间隔*/\
            }\
            QMenu::item:selected { /* when user selects item using mouse or keyboard */\
                background-color: rgba(122,122,122,100);/*这一句是设置菜单项鼠标经过选中的样式*/\
            }"

                );
    action->setMenu(Menu);
    Action=new QAction(this);//设置透明度
    Action1=new QAction(this);//透明度加
    Action2=new QAction(this);//透明度减
    Action->setIcon(QIcon(":/image/image/ooopic_1500874104.png"));
    Action->setText(("设置透明度"));
    Action1->setIcon(QIcon(":/image/image/add.png"));
    Action1->setText(("+5%"));

    Action2->setIcon(QIcon(":/image/image/sub.png"));

    Action2->setText(("-5%"));


    QMenu *Menu1=new QMenu(this);//透明度菜单
    Menu1->addAction(Action1);
    Menu1->addAction(Action2);
    Menu1->setStyleSheet(
            " QMenu {\
            background-color: white; /* sets background of the menu 设置整个菜单区域的背景色，我用的是白色：white*/\
            border: 3px solid white;/*整个菜单区域的边框粗细、样式、颜色*/\
        }\
        QMenu::item {\
            /* sets background of menu item. set this to something non-transparent\
                if you want menu color and menu item color to be different */\
            background-color: transparent;\
            padding:5px 30px;/*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/\
            margin:0px 0px;/*设置菜单项的外边距*/\
            border-bottom:0px solid #DBDBDB;/*为菜单项之间添加横线间隔*/\
        }\
        QMenu::item:selected { /* when user selects item using mouse or keyboard */\
            background-color: rgba(122,122,122,100);/*这一句是设置菜单项鼠标经过选中的样式*/\
        }"

            );
    Action->setMenu(Menu1);
    quit=new QAction(this);
    quit->setIcon(QIcon(":/image/image/tc.png"));
    quit->setText(("退出"));
    connect(music,&QMediaPlayer::metaDataAvailableChanged,this,&Dialog::updateText);
    connect(music,&QMediaPlayer::positionChanged,this,&Dialog::updatePosition);
    connect(music,&QMediaPlayer::durationChanged,this,&Dialog::updateDuration);
    connect(music,&QMediaPlayer::stateChanged,this,&Dialog::stateChange);
    connect(ui->horizontalSlider,&QSlider::sliderMoved,music,&QMediaPlayer::setPosition);
    connect(play,&QAction::triggered,this,&Dialog::play_slot);
    connect(pause,&QAction::triggered,this,&Dialog::pause_slot);
    connect(next,&QAction::triggered,this,&Dialog::next_slot);
    connect(pre,&QAction::triggered,this,&Dialog::pre_slot);
    connect(action1,&QAction::triggered,this,&Dialog::action1_slot);
    connect(action2,&QAction::triggered,this,&Dialog::action2_slot);
    connect(action3,&QAction::triggered,this,&Dialog::action3_slot);
    connect(action4,&QAction::triggered,this,&Dialog::action4_slot);
    connect(Action1,&QAction::triggered,this,&Dialog::Action1_slot);
    connect(Action2,&QAction::triggered,this,&Dialog::Action2_slot);
    connect(quit,&QAction::triggered,this,&Dialog::quit_slot);
    connect(playlist,&QMediaPlaylist::playbackModeChanged,this,&Dialog::PlaybackModel_slot);
    connect(back,&QAction::triggered,this,&Dialog::back_slot);
    ui->pushButton_7->setIconSize(QSize(20,20));
    ui->pushButton_7->setIcon(QIcon(":/image/image/image/loop.png"));
    ui->pushButton_7->setToolTip(("顺序播放"));

    ui->pushButton_8->setIconSize(QSize(20,20));
    ui->pushButton_8->setIcon(QIcon(":/image/image/Music_32px_1144946_easyicon.net.png"));
    ui->pushButton_8->setToolTip(("本地音乐列表"));

//任务栏菜单
    QMenu *ToolMenu=new QMenu(this);

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
    next1=new QWinThumbnailToolButton(this);
    pre1=new QWinThumbnailToolButton(this);
    pause1=new QWinThumbnailToolButton(this);
    next1->setToolTip(("下一首"));
    next1->setIcon(QIcon(":/image/image/next1.png"));
    connect(next1,&QWinThumbnailToolButton::clicked,this,&Dialog::on_pushButton_3_clicked);
    pre1->setToolTip(("上一首"));
    pre1->setIcon(QIcon(":/image/image/pre1.png"));
    connect(pre1,&QWinThumbnailToolButton::clicked,this,&Dialog::on_pushButton_clicked);
    pause1->setToolTip(("暂停"));
    pause1->setIcon(QIcon(":/image/image/bf13.png"));
    connect(pause1,&QWinThumbnailToolButton::clicked,this,&Dialog::on_pushButton_2_clicked);
    toolbar->addButton(pre1);
    toolbar->addButton(pause1);
    toolbar->addButton(next1);
    Taskbotton=new QWinTaskbarButton(this);
    TaskProgress=new QWinTaskbarProgress(this);

    Taskbotton->setWindow(windowHandle());
    TaskProgress=Taskbotton->progress();
    connect(ui->horizontalSlider,&QSlider::valueChanged,TaskProgress,&QWinTaskbarProgress::setValue);
    connect(ui->horizontalSlider,&QSlider::rangeChanged,TaskProgress,&QWinTaskbarProgress::setRange);

    currentFile = "D:/";
}
void Dialog::UpdateIndex(int value)
{
    
    if(Index.indexOf(value)==-1)
    {
        Index.push_back(value);
    }
    
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_4_clicked()//退出
{
    QCoreApplication::quit();
}
/*
void Dialog::on_pushButton_6_clicked()//返回主窗口
{

    emit Data(playlist->currentIndex(),music->position(),playlist,music->state(),playlist->playbackMode());
    music->pause();
    accept();

}
*/
void Dialog::on_pushButton_5_clicked()//最小化
{
    showMinimized();
}
void Dialog::mousePressEvent(QMouseEvent *event)//拖动窗体
{

    offset=event->globalPos()-pos();
    event->accept();
    if(event->button()==Qt::LeftButton)
    {
        setCursor(Qt::OpenHandCursor);
    }

}
void Dialog::mouseMoveEvent(QMouseEvent *event)//拖动窗体
{

    move(event->globalPos()-offset);
    event->accept();
    setCursor(Qt::ClosedHandCursor);
}
void Dialog::mouseReleaseEvent(QMouseEvent *event)//拖动窗体
{

    offset=QPoint();
    event->accept();
    setCursor(Qt::ArrowCursor);
}
void Dialog::mouseDoubleClickEvent(QMouseEvent *)//双击返回主窗口
{

     setCursor(Qt::ArrowCursor);
     emit Data(playlist->currentIndex(),music->position(),playlist,music->state(),playlist->playbackMode(),Index);
     music->pause();
     accept();

}
void Dialog::setPlaylist(QMediaPlaylist *list,int row,int position,int volume,QMediaPlayer::State state,QMediaPlaylist::PlaybackMode playmodel,int i)//设置数据
{
    playlist=list;
    music->setPlaylist(playlist);
    playlist->setCurrentIndex(row);
    music->setPosition(position);
    music->setVolume(volume);

    if(state==QMediaPlayer::PlayingState)
        music->play();
    playlist->setPlaybackMode(playmodel);
    PlaybackModel_slot(playmodel);
    if(i==0)
    {

        ui->pushButton_8->setIcon(QIcon(":/image/image/Music_32px_1144946_easyicon.net.png"));
        ui->pushButton_8->setToolTip(("本地歌曲列表"));
        flag = true;
    }
    else if(i==1)
    {


        ui->pushButton_8->setIcon(QIcon(":/image/image/like_32px_1101682_easyicon.net.png"));
        ui->pushButton_8->setToolTip(("我喜欢列表"));
    }
    else if(i==2)
    {
        ui->pushButton_8->setIcon(QIcon(":/image/image/list_32px_1074296_easyicon.net.png"));
        ui->pushButton_8->setToolTip(("我的收藏列表"));
    }
    else if(i==3)
      {
        ui->pushButton_8->setIcon(QIcon(":/image/image/list_32px_1074296_easyicon.net.png"));
        ui->pushButton_8->setToolTip(("播放记录列表"));
      }

}
void Dialog::updateText()//更新文本
{

    QString Text;
    if(music->isMetaDataAvailable())
    {


        QString Title=music->metaData(QStringLiteral("Title")).toString();
        if(!Title.isEmpty())
        {

            Text=Title;
        }
        else
        {

            Text+=("未知歌曲");
        }
        Text+="-";
        QString Author=music->metaData(QStringLiteral("Author")).toString();
        if(!Author.isEmpty())
        {
            Text+=Author;

        }
        else
        {

            Text+=("未知作者");

        }

    }
    ui->label->setText(Text);

}
static QString Time(qint64 time)//转换时间
{

    int sec=time/1000;
    int min=sec/60;
    sec-=min*60;
    return QStringLiteral("%1:%2")
            .arg(min, 2, 10, QLatin1Char('0'))
            .arg(sec, 2, 10, QLatin1Char('0'));
}
void Dialog::updatePosition(qint64 position)//更新位置
{
    ui->horizontalSlider->setValue(position);
    ui->label_2->setText(Time(position)+"/"+Time(music->duration()));

}
void Dialog::updateDuration(qint64 duration)//更新状态
{

    ui->horizontalSlider->setRange(0,duration);
    ui->horizontalSlider->setEnabled(duration>0);
    ui->horizontalSlider->setPageStep(duration/10);

}

void Dialog::on_pushButton_2_clicked()//播放/暂停
{
    if(playlist->isEmpty())return;
    if(music->state()==QMediaPlayer::PlayingState)
    {

        music->pause();
        ui->pushButton_2->setIcon(QIcon(":/image/image/image/pase.png"));
        ui->pushButton_2->setToolTip(("暂停"));
        pause1->setToolTip(("暂停"));
        pause1->setIcon(QIcon(":/image/image/bf13.png"));
    }
    else
    {
        music->play();
        ui->pushButton_2->setIcon(QIcon(":/image/image/image/play.png"));
        ui->pushButton_2->setToolTip(("播放"));
        pause1->setToolTip(("播放"));
        pause1->setIcon(QIcon(":/image/image/zt13.png"));
    }
}
void Dialog::stateChange(QMediaPlayer::State state)//状态改变
{

    if(state==QMediaPlayer::PlayingState)
    {
        ui->pushButton_2->setIcon(QIcon(":/image/image/image/play.png"));
        ui->pushButton_2->setToolTip(("播放"));
        pause1->setToolTip(("播放"));
        pause1->setIcon(QIcon(":/image/image/zt13.png"));
        TaskProgress->show();
        TaskProgress->resume();

    }
    else
    {

        ui->pushButton_2->setIcon(QIcon(":/image/image/image/pase.png"));
        ui->pushButton_2->setToolTip(("暂停"));
        pause1->setToolTip(("暂停"));
        pause1->setIcon(QIcon(":/image/image/bf13.png"));
        TaskProgress->show();
        TaskProgress->pause();

    }
}

void Dialog::on_pushButton_3_clicked()//下一曲
{
    if(playlist->isEmpty())return;
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
    if(flag&&Index.indexOf(currentIndex)==-1)
    {
        Index.push_back(currentIndex);
    }
    playlist->setCurrentIndex(currentIndex);
}

void Dialog::on_pushButton_clicked()//上一曲
{
    if(playlist->isEmpty())return;
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
    if(flag&&Index.indexOf(currentIndex)==-1)
    {
        Index.push_back(currentIndex);
    }
   playlist->setCurrentIndex(currentIndex);
}

void Dialog::contextMenuEvent(QContextMenuEvent *)//右键菜单栏
{


 menu=new QMenu(this);
 menu->setStyleSheet(
             " QMenu {\
             background-color: white; /* sets background of the menu 设置整个菜单区域的背景色，我用的是白色：white*/\
             border: 3px solid white;/*整个菜单区域的边框粗细、样式、颜色*/\
         }\
         QMenu::item {\
             /* sets background of menu item. set this to something non-transparent\
                 if you want menu color and menu item color to be different */\
             background-color: transparent;\
             padding:5px 30px;/*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/\
             margin:0px 0px;/*设置菜单项的外边距*/\
             border-bottom:0px solid #DBDBDB;/*为菜单项之间添加横线间隔*/\
         }\
         QMenu::item:selected { /* when user selects item using mouse or keyboard */\
             background-color: rgba(122,122,122,100);/*这一句是设置菜单项鼠标经过选中的样式*/\
         }"

             );
 if(music->state()==QMediaPlayer::PlayingState)
 {
      menu->addAction(pause);
 }
 else
 {
     menu->addAction(play);
 }

 menu->addAction(next);
 menu->addAction(pre);
 menu->addAction(back);
 menu->addAction(action);
 menu->addAction(Action);
 menu->addAction(quit);
 menu->exec(QCursor::pos());



}
void Dialog::play_slot()//播放
{

music->play();

}
void Dialog::pause_slot()//暂停
{

    music->pause();
}

void Dialog::next_slot()//下一首
{
    if(playlist->isEmpty())return;
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
    if(flag&&Index.indexOf(currentIndex)==-1)
    {
        Index.push_back(currentIndex);
    }
    playlist->setCurrentIndex(currentIndex);

}
void Dialog::pre_slot()//上一首

{   if(playlist->isEmpty())return;
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
   if(flag&&Index.indexOf(currentIndex)==-1)
   {
       Index.push_back(currentIndex);
   }

}
void Dialog::action1_slot()//默认皮肤1
{

    QString FileName=":/image/image/background/bg4.jpg";
    QSqlQuery query;
    query.exec("select * from Bizi_DATA");
    query.exec("delete from Bizi_DATA");
    query.exec(QString("insert into Bizi_DATA values ('%1')").arg(FileName));
    ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:3px;border-image: url(%1);}").arg(FileName));


}
void Dialog::action2_slot()//默认皮肤2
{

    QString FileName=":/image/image/background/bg5.jpg";
    QSqlQuery query;
    query.exec("select * from Bizi_DATA");
    query.exec("delete from Bizi_DATA");
    query.exec(QString("insert into Bizi_DATA values ('%1')").arg(FileName));

     ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:3px;border-image: url(%1);}").arg(FileName));

}
void Dialog::action3_slot()//默认皮肤3
{

    QString FileName=":/image/image/background/bg6.jpg";
    QSqlQuery query;
    query.exec("select * from Bizi_DATA");
    query.exec("delete from Bizi_DATA");
    query.exec(QString("insert into Bizi_DATA values ('%1')").arg(FileName));
      ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:3px;border-image: url(%1);}").arg(FileName));
}
void Dialog::action4_slot()//自定义皮肤
{

QString FileName=QFileDialog::getOpenFileName(this,("文件"),currentFile,("图片文件(*jpg *png)"));
if(!FileName.isEmpty())
{
    QString file = FileName;
    QString file1 = FileName.split("//").last();
    currentFile = file.remove(file1);
    QSqlQuery query;
    query.exec("select * from Bizi_DATA");
    query.exec("delete from Bizi_DATA");
    query.exec(QString("insert into Bizi_DATA values ('%1')").arg(FileName));
      ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:3px;border-image: url(%1);}").arg(FileName));
}
}
void Dialog::Action1_slot()//透明度加
{

    QSqlQuery query;
    query.exec("select * from Toumin_DATA");
    query.exec("delete from Toumin_DATA");
    if(TouMin<1.0)
    {
        TouMin+=0.05;

        query.exec(QString("insert into Toumin_DATA values (%1)").arg(TouMin));

    }
    ui->frame->setWindowOpacity(TouMin);

}
void Dialog::Action2_slot()//透明度减
{
    QSqlQuery query;
    query.exec("select * from Toumin_DATA");
    query.exec("delete from Toumin_DATA");
    if(TouMin>0.4)
    {
        TouMin-=0.05;

        query.exec(QString("insert into Toumin_DATA values (%1)").arg(TouMin));

    }
   ui->frame->setWindowOpacity(TouMin);

}
void Dialog::quit_slot()//退出
{
    QCoreApplication::quit();
}

void Dialog::on_pushButton_7_clicked()//播放模式
{


    if(playlist->playbackMode()==QMediaPlaylist::Loop)
    {

        ui->pushButton_7->setIcon(QIcon(":/image/image/image/play-random.png"));
        ui->pushButton_7->setToolTip(("随机播放"));
        playlist->setPlaybackMode(QMediaPlaylist::Random);

    }
    else if(playlist->playbackMode()==QMediaPlaylist::Random)
    {
        ui->pushButton_7->setIcon(QIcon(":/image/image/image/loop-one.png"));
        ui->pushButton_7->setToolTip(("单曲循环"));
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);


    }
    else if(playlist->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
    {
        ui->pushButton_7->setIcon(QIcon(":/image/image/image/loop.png"));
        ui->pushButton_7->setToolTip(("顺序播放"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

    }
}
void Dialog::PlaybackModel_slot(QMediaPlaylist::PlaybackMode model)//播放模式改变
{

    if(model==QMediaPlaylist::Loop)
    {
        ui->pushButton_7->setIcon(QIcon(":/image/image/image/loop.png"));
        ui->pushButton_7->setToolTip(("顺序播放"));

    }
    else if(model==QMediaPlaylist::Random)
    {
        ui->pushButton_7->setIcon(QIcon(":/image/image/image/play-random.png"));
        ui->pushButton_7->setToolTip(("随机播放"));

    }
    else if(model==QMediaPlaylist::CurrentItemInLoop)
    {
        ui->pushButton_7->setIcon(QIcon(":/image/image/image/loop-one.png"));
        ui->pushButton_7->setToolTip(("单曲循环"));


    }
}
void Dialog::back_slot(){

    setCursor(Qt::ArrowCursor);
    emit Data(playlist->currentIndex(),music->position(),playlist,music->state(),playlist->playbackMode(),Index);
    music->pause();
    accept();

}
