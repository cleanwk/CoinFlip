#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPaintEvent>
#include<QPainter>
#include<qlabel.h>
#include "mypushbutton.h"
#include<QDebug>
#include<qtimer.h>
#include<QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    this->setFixedSize(450,800);  //设置固定大小

    this->setWindowIcon(QPixmap(":/res/Coin0001")); //设置应用图片

    this->setWindowTitle("老吴带你翻金币");  //设置窗口标题

    connect(ui->actionQuit,&QAction::triggered,[=](){this->close();});

    //音效按钮实现
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);




    myPushButton * startBtn = new myPushButton(":/res/MenuSceneStartButton.png");

    startBtn->setParent(this);

    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    qDebug()<<"点击了开始";

    chooseScene = new chooseLevelScene;

    //监听选择关卡的返回信号的按钮
    connect(chooseScene,&chooseLevelScene::chooseSceneBack,[=](){
        //重新显示主场景
        QTimer::singleShot(300,this,[=](){
            chooseScene->hide();
            this->show();
        });

    });
    connect(startBtn,&myPushButton::clicked,[=](){

        //启动开始音效
        startSound->play();
        startBtn->zoom1();
        startBtn->zoom2();

        //演示进入场景中，为了看动画
        QTimer::singleShot(500,this,[=]{
            //自身隐藏
            this->hide();
            //选择关卡
            chooseScene->show();

        });

    });

}
void MainScene::paintEvent(QPaintEvent *event)
{
    //创建画家，指定绘画设备
    QPainter painter(this);

    //创建qpixmap对象
    QPixmap pix;

    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");

    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");

   //缩放图片
  pix = pix.scaled(pix.width()*0.9,pix.height()*0.9);

    painter.drawPixmap(20,30,pix);

}
MainScene::~MainScene()
{
    delete ui;
}

