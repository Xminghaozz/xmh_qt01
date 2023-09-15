#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QTimer>
#include <QLabel>
#include <QSoundEffect>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置选择关卡的场景
    this->setFixedSize(350,588);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);

    //创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");

    //创建退出 菜单项
    QAction *quitAction = startMenu->addAction("退出");

    //点击退出，实现退出游戏
    connect(quitAction,&QAction::triggered,this,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());

    //创建返回按钮音效
    QSoundEffect *backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    //点击返回
    connect(backBtn,&MyPushButton::clicked,this,[=](){
        qDebug()<<"点击返回按钮";
        //告诉主场景，我返回了，主场景监听ChooseLevelScene的返回按钮
        //延时返回

        backSound->play();

        QTimer::singleShot(300,this,[=](){
            emit this->chooseSceneBack();
        });

    });

    //创建选择关卡的按钮
    for(int i = 0; i < 20; i++)
    {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(30 + i%4 * 80, 145+i/4 *80);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,this,[=](){
            qDebug()<<"选择了第"<<i<<"关";
            //进入到游戏场景
            this->hide();
            playScene = new PlayScene(i+1);//创建游戏场景
            playScene->show();

            //设置游戏场景位置
            playScene->setGeometry(this->geometry());

            //点击游戏场景中的返回按钮，返回到选择游戏关卡界面
            connect(playScene,&PlayScene::chooseSceneBack,this,[=](){
                this->setGeometry(playScene->geometry());

                this->show();
                delete playScene;
                playScene = nullptr;
            });
        });

        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(28 + i%4 * 80, 143+i/4 *80);

        //设置label上文字对齐的方式 水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //设置鼠标穿透事件 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
