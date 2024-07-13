#include "level4.h"
#include<QKeyEvent>
#include<QPainter>
#include<QRandomGenerator>

const int level4map[Mapy_size][Mapx_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2},
    {2,0,0,0,1,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2},
    {2,0,0,0,1,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2},
    {2,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,2,2,0,0,1,1,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,1,3,3,1,0,0,0,0,2,2,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,1,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,2},
    {3,2,0,0,0,0,0,0,0,0,1,3,3,0,0,3,3,1,0,0,0,0,0,0,0,0,2,3},
    {3,3,2,0,0,0,0,0,0,1,3,3,2,2,2,2,3,3,1,0,0,0,0,0,0,2,3,3},
    {3,3,3,2,0,0,0,0,1,3,3,0,2,2,2,2,0,3,3,1,0,0,0,0,2,3,3,3},
    {3,3,3,2,0,0,0,0,1,3,3,0,2,2,2,2,0,3,3,1,0,0,0,0,2,3,3,3},
    {3,3,2,0,0,0,0,0,0,1,3,3,2,2,2,2,3,3,1,0,0,0,0,0,0,2,3,3},
    {3,2,0,0,0,0,0,0,0,0,1,3,3,0,0,3,3,1,0,0,0,0,0,0,0,0,2,3},
    {2,0,0,0,0,0,0,0,0,0,0,1,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,1,3,3,1,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,2},
    {2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2},
    {2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2},
    {2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};
int initenemyx4[3]={120,240,360};
int initenemyy4[3]={120,120,120};
int my_tankx4=60;
int my_tanky4=60;

level4::level4(QWidget *parent) : Level(parent)
{

    loadMap(level4map);
    initTank(3,initenemyx4,initenemyy4,my_tankx4,my_tanky4);
    initEnemyTank(3);
    show_failpage_show=false;
}

void level4::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush(Qt::black);
    for (int i = 0; i < Mapy_size; ++i) {
        for (int j = 0; j < Mapx_size; ++j)
        {
            switch(MAP_Global[i][j])
            {
            case 0:
                pixWall=QPixmap(level4_0);
                break;
            case 1:
                pixWall=QPixmap(level4_1);
                break;
            case 2:
                pixWall=QPixmap(level4_2);
                break;
            case 3:
                pixWall=QPixmap(level4_3);
                break;
            case 4:
                pixWall=QPixmap(level4_4);
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
    pixWall=QPixmap(level4_5);
    painter.drawPixmap(24*60,1*60,180,180,pixWall);
    painter.drawPixmap(24*60,16*60,180,180,pixWall);
    painter.drawPixmap(1*60,16*60,180,180,pixWall);
    painter.drawPixmap(12*60,8*60,240,240,pixWall);
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

void level4::ChangeMapWall()
{
    QVector<QPoint> zeroPositions;
    for (int i = 0; i < Mapy_size; i++)
    {
        for (int j = 0; j < Mapx_size; j++) {
            if (MAP_Global[i][j] == 0) {
                zeroPositions.append(QPoint(i, j));
            }
        }
    }
    if (!zeroPositions.isEmpty())
    {
        int randomIndex = QRandomGenerator::global()->bounded(zeroPositions.size());
        QPoint randomPoint = zeroPositions[randomIndex];
        MAP_Global[randomPoint.x()][randomPoint.y()] = rand()%2+1;
        update();
    }
}

void level4::InitChangeMapTimer()
{
    ChangeMapTimer=new QTimer(this);
    ChangeMapTimer->disconnect();
    ChangeMapTimer->stop();
    ChangeMapTimer->start(QRandomGenerator::global()->bounded(2000, 2500));
    qDebug()<<"TestTest";
    static bool judgeConnect=false;
    qDebug()<<"ChangeMapTimer";
    connect(ChangeMapTimer, &QTimer::timeout, this, &level4::ChangeMapWall);
    judgeConnect=true;
}

void level4::DeleteChangeMapTimer()
{
    ChangeMapTimer->stop();
    ChangeMapTimer->disconnect();
    delete ChangeMapTimer;
    ChangeMapTimer = nullptr;
}
