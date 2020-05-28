#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myPushButton(QWidget *parent = nullptr);

    //normalImg 代表正常显示的图片
        //pressImg  代表按下后显示的图片，默认为空
    myPushButton(QString normalImg, QString pressImg = "");   // 重载版本的构造函数

            void zoom1();
            void zoom2();  //弹跳特效

            QString normalImgPath;  //默认显示图片路径
            QString pressedImgPath; //按下后显示图片路径

            //重写按钮按下和释放鼠标事件
            void mousePressEvent(QMouseEvent * e);

            void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBUTTON_H
