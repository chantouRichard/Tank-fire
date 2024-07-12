#include "level2.h"
#include <QPainter>
int level2map[Mapx_size][Mapy_size] = {
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
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,2},
    {2,0,0,1,1,1,1,0,0,0,0,0,0,0,0,2,2,0,0,2},
    {2,4,4,0,0,0,1,0,0,0,0,0,0,0,0,2,2,0,0,2},
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
}    ;

int initenemyx2[3]={120,240,360};
int initenemyy2[3]={120,120,120};
int my_tankx2=60;
int my_tanky2=60;

level2::level2(QWidget *parent) : Level(parent)
{
    statusBar = new QLabel(this);
    statusText = new QLabel(statusBar);

    Initmap();
    show_failpage_show=false;

    p0=QPixmap(":/7/Res/res7/shazi.jpg");
    p1=QPixmap(":/7/Res/res7/xianrenzhang.jpg");
    p2=QPixmap(":/7/Res/res7/shashi1.jpg");
    QPixmap power=QPixmap(":/7/Res/res7/jinzita2.jpg");
    p3=power.scaled(120,120, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    b1=new QLabel(this);
    b2=new QLabel(this);
    b3=new QLabel(this);
    b4=new QLabel(this);
}

void level2::paintEvent(QPaintEvent *event) {
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

        }
    }

    b1->move(900,60);
    b2->move(420,480);
    b3->move(1440,540);
    b4->move(1260,840);

    b1->setFixedSize(120,120);
    b2->setFixedSize(120,120);
    b3->setFixedSize(120,120);
    b4->setFixedSize(120,120);

    b1->setPixmap(p3);
    b2->setPixmap(p3);
    b3->setPixmap(p3);
    b4->setPixmap(p3);

}


void level2::dead() {
    Level::dead();
}

void level2::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}

void level2::Initmap(){
    resetTime();
    loadMap(level2map);

    initTank(3,initenemyx2,initenemyy2,my_tankx2,my_tanky2);
    initEnemyTank(3);
}
