#include "level3.h"
#include <QPainter>

int level3map[Mapx_size][Mapy_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,2,0,0,5,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,1,0,0,0,5,0,2,2,2,0,0,0,0,2},
    {2,1,1,1,0,0,1,1,1,2,2,0,0,0,0,0,1,1,1,2},
    {2,0,0,1,0,0,0,0,0,0,0,0,0,1,5,5,0,0,0,2},
    {2,0,0,1,0,0,0,0,0,0,2,2,2,1,0,0,2,0,0,2},
    {2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2},
    {2,1,1,2,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,1,0,0,4,4,0,0,0,0,5,5,1,1,2,2},
    {2,0,0,0,0,1,0,0,0,0,0,2,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,2,1,1,5,5,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,3,3,0,0,0,0,1,0,0,0,0,2},
    {2,0,0,5,5,0,0,0,3,3,0,0,0,0,1,1,1,0,0,2},
    {2,0,0,1,1,1,1,0,0,0,0,0,0,0,0,2,2,0,0,2},
    {2,4,4,0,0,0,1,0,0,0,5,5,0,0,0,2,2,0,0,2},
    {2,4,4,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,2},
    {2,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,2,0,0,0,1,1,5,5,1,1,1,0,0,0,0,2},
    {2,0,0,0,2,0,0,0,1,0,0,0,0,0,1,2,2,1,1,2},
    {2,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,0,0,0,0,1,0,0,2,0,0,4,4,0,0,0,2},
    {2,0,0,1,0,0,0,0,1,0,0,2,0,0,4,4,0,0,0,2},
    {2,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,5,5,2},
    {2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}

};

int initenemyx3[3]={120,240,360};
int initenemyy3[3]={120,120,120};
int my_tankx3=60;
int my_tanky3=60;

level3::level3(QWidget *parent) : Level(parent)
{
    statusBar = new QLabel(this);
    statusText = new QLabel(statusBar);
    Initmap();
    show_failpage_show=false;
    p0=QPixmap(":/8/Res/res8/dizhuan.jpg");
    p1=QPixmap(":/8/Res/res8/jiqi1.jpg");
    p2=QPixmap(":/8/Res/res8/jiqi2.jpg");
    p3=QPixmap(":/8/Res/res8/jiqi3.jpg");
    QPixmap m1=QPixmap(":/8/Res/res8/jiqi4.1.jpg");
    p4=m1.scaled(120,120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap m2=QPixmap(":/8/Res/res8/jiqi5.jpg");
    p5=m2.scaled(120,120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap m3=QPixmap(":/8/Res/res8/jiqi6.jpg");
    p6=m3.scaled(120,120, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    b1=new QLabel(this);
    b2=new QLabel(this);
    b3=new QLabel(this);
    b4=new QLabel(this);
    b5=new QLabel(this);

}
void level3::Initmap(){
    resetTime();
    loadMap(level3map);
    initTank(3,initenemyx3,initenemyy3,my_tankx3,my_tanky3);
    initEnemyTank(3);
}

void level3::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    for (int i = 0; i < Mapx_size; ++i) {
        for (int j = 0; j < Mapy_size; ++j) {
            if (MAP_Global[i][j] == 0) {
                painter.drawPixmap(i* 60, j * 60, 60, 60, p0);
            }
            else  if (MAP_Global[i][j] == 1) {
                painter.drawPixmap(i * 60, j * 60, 60, 60, p1);
            } else if (MAP_Global[i][j] == 2) {
                painter.drawPixmap(i * 60, j * 60, 60, 60, p2);
            }
            else if (MAP_Global[i][j] == 5) {
                            painter.drawPixmap(i * 60, j * 60, 60, 60, p3);
                        }

        }
    }
    b1->move(900,60);
    b2->move(420,480);
    b3->move(720,480);
    b4->move(1440,540);
    b5->move(1260,840);

    b1->setFixedSize(120,120);
    b2->setFixedSize(120,120);
    b3->setFixedSize(120,120);
    b4->setFixedSize(120,120);
    b5->setFixedSize(120,120);

    b1->setPixmap(p6);
    b2->setPixmap(p5);
    b3->setPixmap(p6);
    b5->setPixmap(p5);

}

void level3::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}

void level3::dead() {
    Level::dead();
}
