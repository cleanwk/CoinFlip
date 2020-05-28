#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<mycoin.h>

class playScene : public QMainWindow
{
    Q_OBJECT
public:
   //explicit playScene(QWidget *parent = nullptr);

    playScene(int levelNum);

    void paintEvent(QPaintEvent *);

     int levelIndex;

     int gameArray[4][4];
         bool isWin= false;

     myCoin *coinBtn[4][4];
signals:

     //自定义信号，返回
     void chooseSceneBack();
};

#endif // PLAYSCENE_H
