#include "mypushbutton.h"
#include<qwidget.h>
#include<QDebug>
#include<QPropertyAnimation>

myPushButton::myPushButton(QWidget *parent) : QPushButton(parent)
{

}

void myPushButton::zoom1()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //动画开始
    animation->start();
}

void myPushButton::zoom2()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //动画开始
    animation->start();
}
myPushButton::myPushButton(QString normalImg, QString pressImg )
{
        //成员变量normalImgPath保存正常显示图片路径
        normalImgPath = normalImg;
        //成员变量pressedImgPath保存按下后显示的图片
        pressedImgPath = pressImg;
        //创建QPixmap对象
        QPixmap pixmap;

        bool ret=pixmap.load(normalImgPath);

        if(!ret)
        {
            qDebug()<< normalImg << "图片加载失败";
        }

        //设置图片的固定尺寸
        this->setFixedSize(pixmap.width(),pixmap.height());

         //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border:0px}");

         //设置图标
        this->setIcon(pixmap);

        //设置图标大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));


}
void myPushButton:: mousePressEvent(QMouseEvent * e)
{
    if(this->pressedImgPath!="")
    {
        QPixmap pixmap;

        bool ret=pixmap.load(this->pressedImgPath);

        if(!ret)
        {
            qDebug()<< this->pressedImgPath << "图片加载失败";
        }

            //设置图片的固定尺寸
            this->setFixedSize(pixmap.width(),pixmap.height());

             //设置不规则图片的样式表
            this->setStyleSheet("QPushButton{border:0px}");

             //设置图标
            this->setIcon(pixmap);

            //设置图标大小
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }

    //让父类执行其他操作
    return QPushButton::mousePressEvent(e);
}
void myPushButton:: mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressedImgPath!="")
    {
        QPixmap pixmap;

        bool ret=pixmap.load(this->normalImgPath);

        if(!ret)
        {
            qDebug()<< this->normalImgPath << "图片加载失败";
        }

        //设置图片的固定尺寸
        this->setFixedSize(pixmap.width(),pixmap.height());

         //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border:0px}");

         //设置图标
        this->setIcon(pixmap);

        //设置图标大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }

    //让父类执行其他操作
    return QPushButton::mouseReleaseEvent(e);
}
