#include "level1.h"
#include<QKeyEvent>
#include<QPainter>
#include<QRandomGenerator>

const int level1map[Mapy_size][Mapx_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,1,0,0,0,1,0,0,0,2,0,0,0,4,4,0,0,0,1,0,0,1,0,0,0,2},
    {2,0,0,1,0,0,0,1,0,0,0,1,0,0,0,4,4,0,0,0,1,0,0,1,0,0,0,2},
    {2,0,0,1,1,1,1,2,0,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,0,2,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,2,0,0,1,0,0,1,2,2,1,0,0,1,0,2,0,2},
    {2,0,0,0,0,0,0,0,1,1,2,2,0,0,1,0,0,1,0,0,1,0,0,1,0,2,0,2},
    {2,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,2},
    {2,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,0,0,0,4,4,0,0,0,3,3,3,3,0,0,1,1,1,1,1,0,0,0,0,2},
    {2,0,0,2,0,0,0,4,4,0,0,0,3,3,3,3,0,0,1,0,0,0,0,0,3,3,0,2},
    {2,0,0,2,0,2,0,0,0,0,0,0,3,3,3,3,0,0,2,0,0,0,0,0,3,3,0,2},
    {2,0,0,0,0,2,0,0,0,2,0,0,3,3,3,3,0,0,2,0,0,2,2,0,0,0,0,2},
    {2,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2},
    {2,0,2,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2},
    {2,0,2,0,0,0,0,0,2,1,1,1,1,1,0,0,0,0,1,1,0,4,4,1,1,0,0,2},
    {2,0,0,0,0,0,0,0,2,0,0,0,0,1,2,2,1,0,0,2,0,4,4,0,1,0,0,2},
    {2,0,0,1,0,2,2,0,1,0,0,0,0,1,2,2,1,0,0,2,0,0,0,0,1,0,0,2},
    {2,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,2,0,0,2},
    {2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,2,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

int initenemyx1[3]={300,240,360};
int initenemyy1[3]={240,120,120};
int my_tankx1=660;
int my_tanky1=660;

level1::level1(QWidget *parent) : Level(parent)
{
    Initmap();
}

void level1::Initmap(){
    loadMap(level1map);
    resetTime();
    score=0;
    initTank(3,initenemyx1,initenemyy1,my_tankx1,my_tanky1);
    initEnemyTank(3);
    my_tank->control_mode=1;
    show_failpage_show=false;
}

void level1::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}

void level1::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush(Qt::black);
    for (int i = 0; i < Mapy_size; ++i)
    {
        for (int j = 0; j < Mapx_size; ++j)
        {
            switch(MAP_Global[i][j])
            {
            case 0:
                pixWall=QPixmap(level1_0);
                break;
            case 1:
                pixWall=QPixmap(level1_1);
                break;
            case 2:
                pixWall=QPixmap(level1_2);
                break;
            case 20:
                pixWall=pixtool1;
                break;
            case 30:
                pixWall=pixtool2;
                break;
            case 40:
                pixWall=pixtool3;
                break;
            case 50:
                pixWall=pixtool4;
                break;
            }
            painter.drawPixmap(j * 60, i * 60, 60, 60,pixWall);
        }
    }
    pixWall=QPixmap(level1_3);
    painter.drawPixmap(720,480,240,240,pixWall);
    for(int i=0;i<4;i++)
    pixWall=QPixmap(level1_4);
    painter.drawPixmap(900,60,120,120,pixWall);
    painter.drawPixmap(420,480,120,120,pixWall);
    painter.drawPixmap(1260,840,120,120,pixWall);
    painter.drawPixmap(1440,540,120,120,pixWall);
}
