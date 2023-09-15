#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:

    //参数代表传入 金币的路径还是 银币的路径
    MyCoin(QString btnImg);

    //金币属性
    int posX;//x坐标
    int posY;//y坐标
    bool flag;// 正反标志

    //改变标志的方法
    void changeFlag();

    QTimer *timer1; //正面翻反面
    QTimer *timer2; //反面翻正面

    int min = 1;
    int max = 8;

    //执行动画的标志
    bool isAnimation = false;

    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

    //胜利标志
    bool isWin = false;

signals:

};

#endif // MYCOIN_H
