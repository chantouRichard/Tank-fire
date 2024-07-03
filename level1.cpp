#include "level1.h"
#include "ui_level1.h"
#include<QPushButton>
#include<QTimer>
#include "level1.h"
#include<QPainter>
#include<QBrush>
#include<QString>
#include<QKeyEvent>
#include<QTimer>
#include<QDebug>
#include<queue>
#include<QSound>
#include<vector>
#include"pass.h"

int level1map[14][20]=
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0}
};

level1::level1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::level1)
{

    ui->setupUi(this);
    setFixedSize(1200,800);
    setWindowTitle("tankfire");
    //下一关按钮设置
//    this->setStyleSheet("background-color: black;");
    QPushButton * next=new QPushButton("Next level",this);
    next->resize(150,50);
    next->move(675,200);
    //返回按钮
    QPushButton * backbutton=new QPushButton("Back",this);
    backbutton->resize(200,100);
    backbutton->move(1200,900);
    backbutton->move(this->width()/3-backbutton->width()/2,this->height()/2-backbutton->height()/2);
    QPushButton * nextlevel=new QPushButton("Next",this);
    nextlevel->resize(200,100);
    nextlevel->move(1200,1000);
//    nextlevel->move(this->width()*2/3-backbutton->width()/2,this->height()/2-backbutton->height()/2);


    connect(backbutton,&QPushButton::clicked,[=](){
        emit this->back();
    });
    connect(next,&QPushButton::clicked,[=](){
        emit this->Win();
    });
}

void level1::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush(Qt::black);

    QPixmap pixWall1(":/1/Res/res/wall1.jpg");
    QPixmap pixWall2(":/1/Res/res/wall2.jpg");
    QPixmap water("");


    for(int i=0;i<14;i++)
    {
        for(int j=0;j<20;j++)
        {
            if(level1map[i][j]==1)painter.drawPixmap(j*60,i*60,60,60,pixWall1);
            else if(level1map[i][j]==2)painter.drawPixmap(j*60,i*60,60,60,pixWall2);
            //其他ip

        }
    }

    QPixmap mainup(":/1/Res/res/tank_up.jpg");
    QPixmap maindown(":/1/Res/res/tank_down.jpg");
    QPixmap mainleft(":/1/Res/res/tank_left.jpg");
    QPixmap mainright(":/1/Res/res/tank_right.jpg");

}
//初始化玩家坦克
void level1::initTank()
{
    int tankx=400;
    int tanky=400;
}
//初始化敌军坦克
void level1::initEnemyTank()
{}

//死亡效果
void dead()
{}

level1::~level1()
{
    delete ui;
}
