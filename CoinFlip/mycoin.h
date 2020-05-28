#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>

class myCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit myCoin(QWidget *parent = nullptr);

    myCoin(QString btnImg);

    //改变标志的方法
    void changerFlag();
    QTimer * timer1;
    QTimer * timer2;
    int min = 1;
    int max = 8;

    //执行动画  标志位
    bool isAnimation = false;

//    //重写鼠标按下事件
 void mousePressEvent(QMouseEvent * e);


    //金币的属性
    int posX;
    int posY;
    bool  flag;

    bool isWin = false;
signals:

};

#endif // MYCOIN_H
