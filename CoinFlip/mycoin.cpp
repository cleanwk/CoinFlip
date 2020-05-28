#include "mycoin.h"
#include<QDebug>

//myCoin::myCoin(QWidget *parent) : QWidget(parent)
//{

//}
myCoin::myCoin(QString btnImg)
{
    QPixmap pixmap;
    bool ret = pixmap.load(btnImg);

    if(!ret)
    {
        QString str = QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
    }
    this->setFixedSize( pixmap.width(), pixmap.height() );
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pixmap);
       this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号，并反转金币
            connect(timer1,&QTimer::timeout,[=](){
                QPixmap pixmap;
                QString str = QString(":/res/Coin000%1").arg(this->min++);
                pixmap.load(str);
                this->setFixedSize( pixmap.width(), pixmap.height() );
                   this->setStyleSheet("QPushButton{border:0px;}");
                   this->setIcon(pixmap);
                   this->setIconSize(QSize(pixmap.width(),pixmap.height()));

                if(this->min >this->max)
                {
                    this->min = 1;
                      isAnimation = false;
                    timer1->stop();
                }

            });

            //监听反面翻正面的信号，并反转银币
                    connect(timer2,&QTimer::timeout,[=](){
                        QPixmap pixmap;
                        QString str = QString(":/res/Coin000%1").arg(this->max--);
                        pixmap.load(str);
                        this->setFixedSize( pixmap.width(), pixmap.height() );
                           this->setStyleSheet("QPushButton{border:0px;}");
                           this->setIcon(pixmap);
                           this->setIconSize(QSize(pixmap.width(),pixmap.height()));

                        if(this->max <this->min)
                        {
                            this->max = 8;
                                isAnimation = false;
                            timer2->stop();
                        }

                    });
}
void myCoin:: changerFlag()
{
    //若正面则 反过来；
    if(this->flag)
    {
        //开启正翻反面的定时器
        timer1->start(30);
        isAnimation = true;
        this->flag = false;
    }
    else
    {
        timer2->start(30);
         isAnimation = true;
        this->flag = true;
    }
}



void myCoin:: mousePressEvent(QMouseEvent * e)
{
    if(this->isAnimation || this->isWin)
    {
        return;

    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}















