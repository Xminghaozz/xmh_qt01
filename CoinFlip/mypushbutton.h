#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数，参数1： 正常显示的图片路径 参数2： 按下后显示的图片路径
    MyPushButton(QString nomalImg, QString pressImg = "");

    //成员变量，保存用户传入的默认显示路径以及按下后的图片路径
    QString nomalImgPath;
    QString pressImgPath;

    //弹跳特效
    void zoom1();
    void zoom2();

    //重写按钮 按下和释放事件
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
