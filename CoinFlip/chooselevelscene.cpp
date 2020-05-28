#include "chooselevelscene.h"
#include<qmenubar.h>
#include<mypushbutton.h>
#include<playscene.h>
#include<QPainter>
#include<QLabel>
#include<QDebug>
#include<QSound>

chooseLevelScene::chooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(450,800);  //设置固定大小

    this->setWindowIcon(QPixmap(":/res/Coin0001")); //设置应用图片

    this->setWindowTitle("选择关卡场景");  //设置窗口标题

    //创建菜单栏
    QMenuBar * bar= menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startBar= bar->addMenu("开始");

   //创建退出菜单
    QAction * quitAction =  startBar->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡按钮音效
        QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
        //返回按钮音效
            QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);


    myPushButton * backBtn = new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    backBtn->setParent(this);

    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&myPushButton::clicked,[=](){
        backSound->play();
   //主场景监听chooselevelscene的信号
        QTimer::singleShot(500,this,[=](){
              emit this->chooseSceneBack();
        });

    });

    //选择关卡的按钮
    for(int i=0;i <20;i++)
    {
        myPushButton * menuBtn = new myPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);

        menuBtn->move(i % 4 * 90 +60 , i / 4 * 90+200);

        //监听每个按钮的点击事件
        connect(menuBtn,&myPushButton::clicked,[=](){

            chooseSound->play();
           QString str = QString("选择的是第%1关").arg(i+1);
            qDebug()<<str;

            //进入游戏场景
            this->hide();
            play = new playScene(i+1);
            play->show();

            connect(play,&playScene::chooseSceneBack,[=](){
                this->show();
                delete play;
                play = NULL;
            });
        });


        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(i % 4 * 90 +60 , i / 4 * 90+200);

        //设置label中的文字对齐方式
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //设置鼠标穿透  51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);





    }
}

 void chooseLevelScene:: paintEvent(QPaintEvent *)
 {
     //加载背景
     QPainter painter(this);
     QPixmap pix;
     pix.load(":/res/OtherSceneBg.png");
     painter.drawPixmap(0,0,this->width(),this->height(),pix);

     //加载标题
     pix.load(":/res/Title.png");
     painter.drawPixmap((this->width()-pix.width())*0.6,30,pix.width(),pix.height(),pix);

 }
