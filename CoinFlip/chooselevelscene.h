#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include<playscene.h>

class chooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseLevelScene(QWidget *parent = nullptr);


    void paintEvent(QPaintEvent *);

    //游戏场景的指针
    playScene * play = NULL;

signals:

    //自定义信号，告诉主场景返回
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
