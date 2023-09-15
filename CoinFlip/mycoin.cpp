#include "mycoin.h"

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);

    if(ret != true)
    {
        QString str = QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号
    connect(timer1,&QTimer::timeout,this,[=](){

        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断，如果翻完了，将min重置为1
        if(this->min > this->max)
        {
            this->min = 1;
            this->isAnimation = false;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号
    connect(timer2,&QTimer::timeout,this,[=](){

        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断，如果翻完了，将max重置为8
        if(this->min > this->max)
        {
            this->max = 8;
            this->isAnimation = false;
            timer2->stop();
        }
    });
}

//改变正反面标志的方法
void MyCoin::changeFlag()
{
    if(this->flag == true)
    {
        timer1->start(30);
        this->isAnimation = true; //开始动画
        this->flag = false;
    }
    else
    {
        timer2->start(30);
        this->isAnimation = true; //开始动画
        this->flag = true;
    }
}

//重写鼠标按下事件
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation == true || this->isWin == true)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
