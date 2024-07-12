#include "level1.h"
#include <QLabel>
#include<QPixmap>
#include<QPainter>

#include<QKeyEvent>

int level1map[Mapx_size][Mapy_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,1,0,0,0,0,0,2,2,2,0,0,0,0,2},
    {2,1,1,1,0,0,1,1,1,2,2,0,0,0,0,0,1,1,1,2},
    {2,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2},
    {2,0,0,1,0,0,0,0,0,0,2,2,2,1,0,0,2,0,0,2},
    {2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2},
    {2,1,1,2,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,1,0,0,4,4,0,0,0,0,2,2,1,1,2,2},
    {2,0,0,0,0,1,0,0,0,0,0,2,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,2,1,1,2,2,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,3,3,3,3,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,3,3,3,3,0,0,1,1,1,0,0,2},
    {2,0,0,1,1,1,1,0,3,3,3,3,0,0,0,2,2,0,0,2},
    {2,4,4,0,0,0,1,0,3,3,3,3,0,0,0,2,2,0,0,2},
    {2,4,4,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,2},
    {2,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,2,0,0,0,1,1,2,2,1,1,1,0,0,0,0,2},
    {2,0,0,0,2,0,0,0,1,0,0,0,0,0,1,2,2,1,1,2},
    {2,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,0,0,0,0,1,0,0,2,0,0,4,4,0,0,0,2},
    {2,0,0,1,0,0,0,0,1,0,0,2,0,0,4,4,0,0,0,2},
    {2,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,3,3,0,0,0,1,1,1,2,2,2},
    {2,0,0,2,2,2,0,0,0,3,3,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};



int initenemyx1[3]={120,240,360};
int initenemyy1[3]={120,120,120};
int my_tankx1=60;
int my_tanky1=60;

level1::level1(QWidget *parent) : Level(parent)
{
    statusBar = new QLabel(this);
    statusText = new QLabel(statusBar);
    Initmap();
    Label1=new QLabel(this);
    Label2=new QLabel(this);
    Label3=new QLabel(this);
    Label4=new QLabel(this);
    Label5=new QLabel(this);

    pixWall0=QPixmap(":/6/Res/res6/grass.jpg");
    pixWall1=QPixmap(":/6/Res/res6/penzai1.jpg");
    pixWall2=QPixmap(":/6/Res/res6/shitou1.png");
    QPixmap pixWall3(":/6/Res/res6/bigzaocong.jpg");
    QPixmap pixWall4(":/6/Res/res6/shuichi2.jpg");
    p1=pixWall3.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2=pixWall4.scaled(240, 240, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void level1::Initmap(){
    loadMap(level1map);
    resetTime();
    score=0;
    initTank(3,initenemyx1,initenemyy1,my_tankx1,my_tanky1);
    initEnemyTank(3);
    show_failpage_show=false;
}

void level1::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}

void level1::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    for (int i = 0; i < Mapx_size; ++i) {
        for (int j = 0; j < Mapy_size; ++j) {
            if (MAP_Global[i][j] == 0) {
                painter.drawPixmap(i* 60, j * 60, 60, 60, pixWall0);
            }
            else  if (MAP_Global[i][j] == 1) {
                painter.drawPixmap(i * 60, j * 60, 60, 60, pixWall1);
            } else if (MAP_Global[i][j] == 2) {
                painter.drawPixmap(i * 60, j * 60, 60, 60, pixWall2);
            }

        }
    }
    Label1->move(900,60);
    Label2->move(420,480);
    Label3->move(720,480);
    Label4->move(1440,540);
    Label5->move(1260,840);
    Label1->setFixedSize(120,120);
    Label2->setFixedSize(120,120);
    Label3->setFixedSize(240,240);
    Label4->setFixedSize(120,120);
    Label5->setFixedSize(120,120);



    Label1->setPixmap(p1);
    Label2->setPixmap(p1);
    Label3->setPixmap(p2);
    Label4->setPixmap(p1);
    Label5->setPixmap(p1);
}

void level1::dead() {
    Level::dead();
}



