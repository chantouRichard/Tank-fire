#include "level2.h"
#include<QKeyEvent>
#include<QPainter>
#include<QRandomGenerator>

const int level2map[Mapy_size][Mapx_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,1,0,0,0,1,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,2},
    {2,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,2},
    {2,0,0,1,1,1,1,2,0,0,0,1,0,0,1,0,0,1,0,0,1,5,5,1,0,2,0,2},
    {2,0,0,0,0,0,1,0,0,0,0,2,0,0,1,0,0,1,2,2,1,5,5,1,0,2,0,2},
    {2,0,0,0,0,0,1,0,1,1,2,2,0,0,1,0,0,1,0,0,1,0,0,1,0,2,0,2},
    {2,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,2},
    {2,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,0,0,0,5,5,0,0,0,0,2,2,0,0,0,1,1,1,1,1,0,0,0,0,2},
    {2,0,0,2,0,0,0,5,5,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,2},
    {2,0,0,2,0,2,0,0,0,0,0,0,5,5,0,1,1,1,2,0,0,0,0,0,1,1,0,2},
    {2,0,0,0,0,2,0,0,0,2,0,0,5,5,0,0,0,0,2,0,0,2,2,0,0,1,0,2},
    {2,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,2},
    {2,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,2,1,1,1,1,1,0,0,0,0,1,1,0,5,5,1,1,0,0,2},
    {2,0,5,5,0,0,0,0,2,0,0,0,0,1,2,2,1,0,0,2,0,5,5,0,1,0,0,2},
    {2,0,5,5,0,2,2,0,1,0,0,0,0,1,2,2,1,0,0,2,0,0,0,0,1,0,0,2},
    {2,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,2,0,0,2},
    {2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,2,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

int initenemyx2[4]={120,240,360,60};
int initenemyy2[4]={120,120,120,1080};
int my_tankx2=1560;
int my_tanky2=1080;

level2::level2(QWidget *parent) : Level(parent)
{

    Initmap();
    show_failpage_show=false;

}

void level2::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush(Qt::black);
    for (int i = 0; i < Mapy_size; ++i) {
        for (int j = 0; j < Mapx_size; ++j)
        {
            switch(MAP_Global[i][j])
            {
            case 0:
                pixWall=QPixmap(level2_0);
                break;
            case 1:
                pixWall=QPixmap(level2_1);
                break;
            case 2:
                pixWall=QPixmap(level2_2);
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
    pixWall=QPixmap(level2_5);
    painter.drawPixmap(1260,180, 120, 120,pixWall);
    painter.drawPixmap(420,480, 120, 120,pixWall);
    painter.drawPixmap(720,600, 120, 120,pixWall);
    painter.drawPixmap(1260,840, 120, 120,pixWall);
    painter.drawPixmap(120,900, 120, 120,pixWall);
}

void level2::ChangeMapWall()
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

void level2::InitChangeMapTimer()
{
    ChangeMapTimer=new QTimer(this);
    ChangeMapTimer->disconnect();
    ChangeMapTimer->stop();
    ChangeMapTimer->start(QRandomGenerator::global()->bounded(2000, 2500));
    qDebug()<<"TestTest";
    static bool judgeConnect=false;
    qDebug()<<"ChangeMapTimer";
    connect(ChangeMapTimer, &QTimer::timeout, this, &level2::ChangeMapWall);
    judgeConnect=true;
}

void level2::DeleteChangeMapTimer()
{
    ChangeMapTimer->stop();
    ChangeMapTimer->disconnect();
    delete ChangeMapTimer;
    ChangeMapTimer = nullptr;
}
void level2::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}

void level2::Initmap(){
    resetTime();
    loadMap(level2map);

    initTank(4,initenemyx2,initenemyy2,my_tankx2,my_tanky2);
    initEnemyTank(4);
    this->enemys[3]->enemy_tank_img->hide();
    my_tank->control_mode=1;
    show_failpage_show=false;
}
