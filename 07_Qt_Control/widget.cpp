#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置单选按钮 默认选中男
    ui->rdtnMan->setChecked(true);

    //单选按钮选中 女 打印信息
    connect(ui->rbtnWoman,&QRadioButton::clicked,[=](){
        qDebug()<<"选中女";
    });

    //多选按钮 2是选中 0是未选中
    connect(ui->cBox3,&QCheckBox::stateChanged,[=](int state){
        qDebug()<<state;
    });

//    //利用listWidget写文本
//    QListWidgetItem *item = new QListWidgetItem("床前明月光");
//    //将这行文本添加到listWidget控件中
//    ui->listWidget->addItem(item);
//    //设置文本对齐格式
//    item->setTextAlignment(Qt::AlignHCenter);

    //QStringList List(String) 这种方式不能设置水平居中
    QStringList list;
    list<<"床前明月光"<<"疑是地上霜"<<"举头望明月"<<"低头思故乡";
    ui->listWidget->addItems(list);//一次性添加整个内容

    //利用循环可以实现水平居中
//    for (int i = 0;  i< list.size(); i++) {
//        QListWidgetItem *item = new QListWidgetItem(list[i]);
//        ui->listWidget->addItem(item);
//        item->setTextAlignment(Qt::AlignHCenter);
//    }
}

Widget::~Widget()
{
    delete ui;
}

