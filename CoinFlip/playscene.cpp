#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSoundEffect>

PlayScene::PlayScene(int level)
{
    QString str = QString("进入了第%1关").arg(level);
    qDebug()<<str;
    this->level =level;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(350, 588);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("翻金币场景");

    //设置菜单栏
    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);

    //设置开始菜单
    QMenu *startMenu = bar->addMenu("开始");

    //创建退出菜单项
    QAction *quitAction = startMenu->addAction("退出");

    //实现点击退出 关闭游戏
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
        qDebug()<<"翻金币场景中点击返回按钮";

        backSound->play();
        //告诉主场景，我返回了，主场景监听ChooseLevelScene的返回按钮
        //延时返回
        QTimer::singleShot(300,this,[=](){
            emit this->chooseSceneBack();
        });

    });

    //显示当前关卡
    QLabel *label = new QLabel();
    label->setParent(this);

    //设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);

    //将字体设置放入label中
    label->setFont(font);

    QString str1 = QString("Level: %1").arg(this->level);
    label->setText(str1);
    label->setGeometry(30, this->height()-50, 120, 50);

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j< 4 ;j++)
        {
            this->gameArray[i][j] = config.mData[this->level][i][j];
        }
    }

    //胜利图片显示 默认在背景外
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width())*0.5, -tmpPix.height());

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            //绘制背景图片
            QLabel *label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(77+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1)
            {
                //显示金币
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }

            MyCoin *coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(77+i*50,200+j*50);

            //给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j]; //1正面 0反面

            //将金币放入 金币的二维数组 方便后续维护
            coinBtn[i][j] = coin;

            //点击金币，进行翻转
            connect(coin,&MyCoin::clicked,this,[=](){

                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1:0;

                //翻转周围的金币
                //右侧硬币翻转条件 延时翻转
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX +1 < 4)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1:0;
                    }

                    //左侧硬币翻转条件
                    if(coin->posX-1 >= 0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1:0;
                    }

                    //上侧硬币翻转条件
                    if(coin->posY-1 >= 0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1:0;

                    }

                    //下侧硬币翻转条件
                    if(coin->posY+1 <4)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1:0;
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++){
                            if(coinBtn[i][j]->flag == false){
                                this->isWin = false;
                                break;
                            }
                        }
                    }

                    if(this->isWin == true)
                    {
                        //达到胜利条件
                        qDebug()<<"游戏胜利";
                        for(int i = 0; i < 4; i++)
                        {
                            for(int j = 0; j < 4; j++)
                            {
                                this->coinBtn[i][j]->isWin = true;
                            }
                        }

                        //将胜利的图片移动下来
                        QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+180,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                });

            });
        }
    }

}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    //加载背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);

    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
