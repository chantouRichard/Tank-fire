#include "level4.h"
#include <QPainter>

int level4map[Mapx_size][Mapy_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,1,0,0,0,0,0,2,2,2,0,0,0,0,2},
    {2,1,1,1,0,0,1,1,1,2,2,0,0,0,0,0,1,1,1,2},
    {2,0,0,6,0,0,0,0,0,0,0,0,0,1,0,0,0,6,0,2},
    {2,0,0,6,0,0,0,0,0,0,6,2,2,1,0,0,2,6,0,2},
    {2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2},
    {2,1,1,2,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,1,0,0,4,4,0,0,0,0,6,6,1,1,2,2},
    {2,0,0,0,0,1,0,0,0,0,0,2,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,2,6,6,2,2,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,0,6,0,0,0,0,0,3,3,0,0,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,3,3,0,0,0,0,1,1,1,0,0,2},
    {2,0,0,1,1,1,1,0,0,0,0,0,0,0,0,2,2,0,0,2},
    {2,4,4,0,0,0,1,0,0,0,2,2,0,0,0,2,2,0,0,2},
    {2,4,4,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,2},
    {2,0,0,1,1,1,1,0,0,0,6,6,0,0,0,0,0,0,0,2},
    {2,0,0,0,2,0,0,0,1,1,2,2,1,1,1,0,0,0,0,2},
    {2,0,0,0,2,0,0,0,1,0,0,0,0,0,1,2,2,1,1,2},
    {2,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,0,0,0,0,1,0,0,2,0,0,4,4,0,0,0,2},
    {2,0,0,1,0,0,0,0,1,0,0,2,0,0,4,4,0,0,0,2},
    {2,1,1,1,6,6,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2},
    {2,0,0,2,2,2,0,0,0,1,1,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}

};

int initenemyx4[3]={120,240,360};
int initenemyy4[3]={120,120,120};
int my_tankx4=60;
int my_tanky4=60;

level4::level4(QWidget *parent) : Level(parent)
{
    statusBar = new QLabel(this);
    statusText = new QLabel(statusBar);

    loadMap(level4map);
    initTank(3,initenemyx4,initenemyy4,my_tankx4,my_tanky4);
    initEnemyTank(3);
    show_failpage_show=false;

    p0=QPixmap(":/8/Res/res8/beijing6.jpg");
    p1=QPixmap(":/8/Res/res8/dong.jpg");
    p2=QPixmap(":/8/Res/res8/dong1.2.png");
    p3=QPixmap(":/8/Res/res8/dong4.jpg");
    QPixmap m1=QPixmap(":/8/Res/res8/dong5.png");
    p4=m1.scaled(120,120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap m2=QPixmap(":/8/Res/res8/dong6.jpg");
    p5=m2.scaled(120,120, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    b1=new QLabel(this);
    b2=new QLabel(this);
    b3=new QLabel(this);
    b4=new QLabel(this);
    b5=new QLabel(this);
}

void level4::paintEvent(QPaintEvent *event) {
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
            else if (MAP_Global[i][j] == 6) {
                            painter.drawPixmap(i * 60, j * 60, 60, 60, p3);
                        }

        }
    }
    b1->move(900,60);
    b2->move(420,480);
    b3->move(720,480);

    b5->move(1260,840);

    b1->setFixedSize(120,120);
    b2->setFixedSize(120,120);
    b3->setFixedSize(120,120);

    b5->setFixedSize(120,120);

    b1->setPixmap(p4);
    b2->setPixmap(p5);
    b3->setPixmap(p4);
    b5->setPixmap(p5);

}

void level4::dead() {
    Level::dead();
}

void level4::Initmap(){
    resetTime();
    loadMap(level4map);

    initTank(3,initenemyx4,initenemyy4,my_tankx4,my_tanky4);
    initEnemyTank(3);
}

void level4::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}
