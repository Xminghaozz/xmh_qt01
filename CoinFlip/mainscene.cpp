#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QTimer>
#include <QSoundEffect>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景

    //设置固定大小
    this->setFixedSize(350,588);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("翻金币主场景");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,this,[=](){
        this->close();
    });

    //设置开始按钮音效
    QSoundEffect *startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));

    //开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooseLevelScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮信号
    connect(chooseLevelScene,&ChooseLevelScene::chooseSceneBack,this,[=](){

        this->setGeometry(chooseLevelScene->geometry());
        chooseLevelScene->hide();//隐藏选择关卡场景

        this->show();//重新显示主场景
    });

    connect(startBtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"点击了开始";

        startSound->play();

        //做弹跳特效
        startBtn->zoom1();

        //延时进入到选择关卡场景
        QTimer::singleShot(300,this,[=](){

            //设置chooseScene场景位置
            chooseLevelScene->setGeometry(this->geometry());
            //将自身隐藏，
            this->hide();

            chooseLevelScene->show();

        });

    });

}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制背景上图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);


}
MainScene::~MainScene()
{
    delete ui;
}



