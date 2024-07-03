#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"pass.h"
#include<QPushButton>
#include<QTimer>
#include"pass.h"
#include<QDebug>
#include<QLabel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    ui->setupUi(this);
    setFixedSize(1200,800);
    setWindowTitle("tankfire");

    QLabel *backgroundLabel = new QLabel(this);

    backgroundLabel->setScaledContents(true); // 这将使图片缩放以填充QLabel的整个区域
    backgroundLabel->resize(this->size()); // 确保QLabel的大小与父窗口或控件相同
    backgroundLabel->setPixmap(QPixmap(":/1/Res/res/gameover.jpg"));
//    this->setStyleSheet("background-image:url(C:/Users/qq864/Documents/tank_fire/Res/res/gameover.jpg);");

//    ui->actionNew->setIcon(QIcon("C:/Users/qq864/Desktop/Res/res/home.jpg"));
//    ui->actionNew->setIcon(QIcon(":/1/Res/res/enemy_tank_right.jpg"));
    QPushButton *button = new QPushButton("开始游戏", this);
    button->resize(200, 100);
    button->move(this->width() / 2 - button->width() / 2, this->height() / 2 - button->height() / 2);

    // 创建一个QFont对象，并设置其大小
    QFont font = button->font(); // 首先获取当前字体（可选，如果你不想改变其他字体属性的话）
    font.setPointSize(24); // 设置字体大小为24点（你可以根据需要调整这个值）

    // 将修改后的字体应用到按钮上
    button->setFont(font);
//    button->setIcon(QIcon(":/1/Res/res/backbtn.png")); // 设置图标
//    button->setIconSize(QSize(50, 50)); // 设置图标大小（可选）
//    // 如果不希望显示文本，可以将文本设置为空字符串
//    button->setText("");


    pass * level=new pass;

    connect(button,&QPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            this->hide();
            level->show();
            connect(level->backbtn,&QPushButton::clicked,[=](){
                this->show();
                level->hide();
            });
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

