#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int level);

    int level =0;//记录所选的关卡


    //重写绘图事件
    void paintEvent(QPaintEvent *);

    int gameArray[4][4]; //二维数组 维护关卡的具体数据

    MyCoin *coinBtn[4][4]; //二维数组指针 维护金币按钮

    //是否胜利的标志
    bool isWin = false;

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
