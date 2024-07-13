#include "level3.h"
#include<QKeyEvent>
#include<QPainter>
#include<QRandomGenerator>

const int level3map[Mapy_size][Mapx_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,1,0,0,0,1,0,0,0,2,0,0,0,4,4,0,0,0,1,0,0,1,0,0,0,2},
    {2,0,0,1,0,0,0,1,0,0,0,1,0,0,0,4,4,0,0,0,1,0,0,1,0,0,0,2},
    {2,0,0,1,1,6,6,2,0,0,0,1,0,0,1,0,0,1,0,0,1,1,6,6,0,2,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,2,0,0,1,0,0,1,2,2,1,0,0,6,0,2,0,2},
    {2,0,0,0,0,0,0,0,1,1,2,2,0,0,1,0,0,1,0,0,1,0,0,6,0,2,0,2},
    {2,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,2},
    {2,2,0,1,0,6,6,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,0,0,0,0,0,0,5,5,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,2},
    {2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,0,1,0,0,0,0,0,5,5,0,2},
    {2,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,6,0,2,0,0,0,0,0,5,5,0,2},
    {2,0,0,0,0,2,0,0,0,2,0,0,0,0,6,6,6,0,2,0,0,2,2,0,0,0,0,2},
    {2,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2},
    {2,0,2,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2},
    {2,0,2,0,0,0,0,0,2,1,1,1,1,1,0,0,0,0,1,1,0,4,4,1,1,0,0,2},
    {2,0,0,6,6,6,6,0,2,0,0,0,0,1,2,2,1,0,0,2,0,4,4,0,1,0,0,2},
    {2,0,0,1,0,2,2,0,1,0,4,4,0,1,2,2,1,0,0,2,0,0,0,0,1,0,0,2},
    {2,0,0,1,0,0,0,0,1,0,4,4,0,0,0,0,1,0,0,1,0,0,6,6,2,0,0,2},
    {2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,2,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

int initenemyx3[3]={120,240,360};
int initenemyy3[3]={120,120,120};
int my_tankx3=60;
int my_tanky3=60;

level3::level3(QWidget *parent) : Level(parent)
{

    Initmap();
    show_failpage_show=false;
}
void level3::Initmap(){
    resetTime();
    loadMap(level3map);
    initTank(3,initenemyx3,initenemyy3,my_tankx3,my_tanky3);
    initEnemyTank(3);
     my_tank->control_mode=2;
}
void level3::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush(Qt::black);
    for (int i = 0; i < Mapy_size; ++i) {
        for (int j = 0; j < Mapx_size; ++j)
        {
            switch(MAP_Global[i][j])
            {
            case 0:
                pixWall=QPixmap(level3_0);
                break;
            case 1:
                pixWall=QPixmap(level3_1);
                break;
            case 2:
                pixWall=QPixmap(level3_2);
                break;
            case 6:
                pixWall=QPixmap(level3_6);
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
    pixWall=QPixmap(level3_4);
    painter.drawPixmap(900, 60, 120, 120,pixWall);
    painter.drawPixmap(600, 960, 120, 120,pixWall);
    painter.drawPixmap(1260, 840, 120, 120,pixWall);
    pixWall=QPixmap(level3_5);
    painter.drawPixmap(600, 420, 120, 120,pixWall);
    painter.drawPixmap(140, 540, 120, 120,pixWall);
}

void level3::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}

