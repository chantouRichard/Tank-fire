#include "pass.h"
#include "ui_pass.h"
#include"level1.h"
#include<QPushButton>
#include<QTimer>
#include<QVBoxLayout>
#include<QIcon>
#include<QLabel>


pass::pass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pass)
{
    ui->setupUi(this);
    setFixedSize(1200,800);
    setWindowTitle("tankfire");
//    this->setStyleSheet("background-color: blue;");
    QLabel *backgroundLabel = new QLabel(this);

    backgroundLabel->setScaledContents(true); // 这将使图片缩放以填充QLabel的整个区域
    backgroundLabel->resize(this->size()); // 确保QLabel的大小与父窗口或控件相同
    backgroundLabel->setPixmap(QPixmap(":/1/Res/res/gameover.jpg"));

    level1* Level1=new level1;

    //设置按钮
//    QIcon icon("C:/Users/qq864/Downloads/backbtn.png");
    backbtn=new QPushButton("Back");
    backbtn->setParent(this);
    backbtn->move(10,10);
    backbtn->resize(100,50);
    //level1
    QPushButton * l1btn=new QPushButton("level1",this);
    l1btn->resize(160,80);
    l1btn->move(this->width()/5-l1btn->width()/2,this->height()/2-l1btn->height()/2);
    l1btn->setStyleSheet(
        "QPushButton {"
        "   background-color: red;"
        "   color: white;"
        "   border: none;"
        "   padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: pink;"
        "}"
        "QPushButton:pressed {"
        "   background-color: red;"
        "}"
    );
    //level2
    QPushButton * l2btn=new QPushButton("level2",this);
    l2btn->resize(160,80);
    l2btn->move(this->width()*2/5-l2btn->width()/2,this->height()/2-l2btn->height()/2);
    if(pass_judge[0]==true)
    {
        l2btn->setStyleSheet(
            "QPushButton {"
            "   background-color: red;"
            "   color: white;"
            "   border: none;"
            "   padding: 10px 20px;"
            "}"
            "QPushButton:hover {"
            "   background-color: pink;"
            "}"
            "QPushButton:pressed {"
            "   background-color: red;"
            "}"
        );
    }
    else
    {
        l2btn->setStyleSheet(
            "QPushButton {"
            "   background-color: lightgrey;"
            "   color: white;"
            "   border: none;"
            "   padding: 10px 20px;"
            "}"
            "QPushButton:hover {"
            "   background-color: grey;"
            "}"
            "QPushButton:pressed {"
            "   background-color: lightgrey;"
            "}"
        );
    }
    //level3
    QPushButton * l3btn=new QPushButton("level2",this);
    l3btn->resize(160,80);
    l3btn->move(this->width()*3/5-l3btn->width()/2,this->height()/2-l3btn->height()/2);
    if(pass_judge[1]==true)
    {
        l3btn->setStyleSheet(
            "QPushButton {"
            "   background-color: red;"
            "   color: white;"
            "   border: none;"
            "   padding: 10px 20px;"
            "}"
            "QPushButton:hover {"
            "   background-color: pink;"
            "}"
            "QPushButton:pressed {"
            "   background-color: red;"
            "}"
        );
    }
    else
    {
        l3btn->setStyleSheet(
            "QPushButton {"
            "   background-color: lightgrey;"
            "   color: white;"
            "   border: none;"
            "   padding: 10px 20px;"
            "}"
            "QPushButton:hover {"
            "   background-color: grey;"
            "}"
            "QPushButton:pressed {"
            "   background-color: lightgrey;"
            "}"
        );
    }
    //level4
    QPushButton * l4btn=new QPushButton("level2",this);
    l4btn->resize(160,80);
    l4btn->move(this->width()*4/5-l4btn->width()/2,this->height()/2-l4btn->height()/2);
    if(pass_judge[0]==true)
    {
        l4btn->setStyleSheet(
            "QPushButton {"
            "   background-color: red;"
            "   color: white;"
            "   border: none;"
            "   padding: 10px 20px;"
            "}"
            "QPushButton:hover {"
            "   background-color: pink;"
            "}"
            "QPushButton:pressed {"
            "   background-color: red;"
            "}"
        );
    }
    else
    {
        l4btn->setStyleSheet(
            "QPushButton {"
            "   background-color: lightgrey;"
            "   color: white;"
            "   border: none;"
            "   padding: 10px 20px;"
            "}"
            "QPushButton:hover {"
            "   background-color: grey;"
            "}"
            "QPushButton:pressed {"
            "   background-color: lightgrey;"
            "}"
        );
    }
    //test
    //未解锁显示


    //test
    QFont font = backbtn->font();
    QFont font1 = l1btn->font();
    QFont font2 = l2btn->font();
    QFont font3 = l3btn->font();
    QFont font4 = l4btn->font();
    font.setPointSize(20);
    font1.setPointSize(20);
    font2.setPointSize(20);
    font3.setPointSize(20);
    font4.setPointSize(20);

    connect(l1btn,&QPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            this->hide();
            Level1->show();
            connect(Level1,&level1::back,this,[=](){
                this->show();
                Level1->hide();
            });
        });

    });

    connect(backbtn,&QPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            emit this->back();
        });
    });
}
pass::~pass()
{
    delete ui;
}
