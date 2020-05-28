#include "playscene.h"
#include<QDebug>
#include<qmenubar.h>
#include<QPainter>
#include<mypushbutton.h>
#include<qdebug.h>
#include<QTimer>
#include<qlabel.h>
#include<qfont.h>
#include<mycoin.h>
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//playScene::playScene(QWidget *parent) : QMainWindow(parent)
//{

//}

playScene:: playScene(int levelNum)
{
    QString str = QString("进入了第%1关").arg(levelNum);
    qDebug() << str;

    this->levelIndex = levelNum;

    this->setFixedSize(450,800);  //设置固定大小

    this->setWindowIcon(QPixmap(":/res/Coin0001")); //设置应用图片

    this->setWindowTitle("翻金币场景");  //设置窗口标题


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


    //返回按钮音效
        QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //翻金币音效
        QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
        //胜利按钮音效
        QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);



    //返回按钮

    myPushButton * backBtn = new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    backBtn->setParent(this);

    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&myPushButton::clicked,[=](){
 //  主场景监听chooselevelscene的信号

        qDebug()<<"翻金币场景中点击了，返回按钮";
//播放声音
        backSound->play();
        QTimer::singleShot(300,this,[=](){

            emit this->chooseSceneBack();
        });
    });


    //当前关卡选择
    QLabel * label = new QLabel;
    label->setParent(this);
    //设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);

    label->setText(QString("当前LEVEL: %1").arg(this->levelIndex));
    label->setGeometry(30,this->height()-70,270,50);

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i =0;i<4;i++)
    {
        for(int j =0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }
//显示胜利背景图片
    QLabel* winLabel = new QLabel;
        QPixmap tmpPix;
        tmpPix.load(":/res/LevelCompletedDialogBg.png");
        winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
        winLabel->setPixmap(tmpPix);
        winLabel->setParent(this);
        winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());

    //显示金币背景图片

    for(int i = 0;i<4;i++)
    {
        for(int j =0;j<4;j++)
        {
            //绘制背景图片
                       QLabel* label = new QLabel;
                       label->setGeometry(0,0,100,100);
                       label->setPixmap(QPixmap(":/res/BoardNode.png"));
                       label->setParent(this);
                       label->move(130 + i*50,300+j*50);

                       QString str;
                         if(this->gameArray[i][j]==1)
                         {
                             //金币的 dir
                             str = ":/res/Coin0001.png";
                         }
                         else
                         {
                             //银币的 dir
                               str = ":/res/Coin0008.png";
                         }

                         myCoin *coin = new myCoin(str);
                         coin->setParent(this);
                         coin->move(132 + i*50,330+j*50);

                         //给金币属性赋值、
                         coin->posX = i;
                         coin->posY = j;
                         coin->flag = this->gameArray[i][j];

                         //将金币放在金币的二维数组中，以便维护
                         coinBtn[i][j] = coin;
                         connect(coin,&myCoin::clicked,[=](){

                             //翻金币特效
                             flipSound->play();
                           coin->changerFlag();
                           this->gameArray[i][j] = this->gameArray[i][j] == 0 ?1:0;

                           //翻转周围硬币
                           QTimer::singleShot(300,this,[=](){
                               //右侧翻转
                               if(coin->posX+1<=3)
                               {
                                   coinBtn[coin->posX+1][coin->posY]->changerFlag();
                                   this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY]==0 ?1:0;
                               }

                               //左侧翻转
                               if(coin->posX-1>=0)
                               {
                                   coinBtn[coin->posX-1][coin->posY]->changerFlag();
                                   this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY]==0 ?1:0;
                               }


                               //上侧翻转
                               if(coin->posY+1<=3)
                               {
                                   coinBtn[coin->posX][coin->posY+1]->changerFlag();
                                   this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1]==0 ?1:0;
                               }
                               //下侧翻转
                               if(coin->posY-1>=0)
                               {
                                   coinBtn[coin->posX][coin->posY-1]->changerFlag();
                                   this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1]==0 ?1:0;
                               }


                               //判断是否胜利
                               this->isWin = true;
                               for(int i = 0;i<4 ;i++)
                               {
                                   for(int j= 0;j<4;j++)
                                   {
                                       if(coinBtn[i][j]->flag==false)
                                       {
                                           this->isWin= false;
                                           break;
                                       }
                                   }
                               }


                               if(this->isWin==true)
                               {
                                   //胜利了
                                   qDebug()<<"胜利了！";
                                   for(int i = 0;i<4 ;i++)
                                   {
                                       for(int j= 0;j<4;j++)
                                       {
                                           coinBtn[i][j]->isWin=true;
                                       }
                                   }

                                   //胜利音效
                                   winSound->play();

                                   QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                                   //设置时间间隔
                                   animation->setDuration(1000);
                                   //设置开始位置
                                   animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                                   //设置结束位置
                                   animation->setEndValue(QRect(winLabel->x(),winLabel->y()+200,winLabel->width(),winLabel->height()));
                                   //设置缓和曲线
                                   animation->setEasingCurve(QEasingCurve::OutBounce);
                                   //执行动画
                                   animation->start();



                               }

                           });

                         });
        }
    }

}


void playScene:: paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap(0,0,pix.width()*0.7,pix.height()*0.7,pix);

}
