#include "enemytank.h"
#include <QDebug>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <QPixmap>
#include <QPainter>
#include <QBrush>
#include <QWidget>
#include<QTimer>
#include<QLabel>
#include<QDebug>

Box::Box(int x,int y,Box* pre)
{
    this->x=x;
    this->y=y;
    this->pre=pre;
}

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

EnemyTank::EnemyTank(int startX, int startY, Tank*& my_tank,QWidget* parent)
    : QWidget(parent), currentX(startX), currentY(startY), angle(90), isPaused(false), moveCounter(0) ,playerTank(my_tank) {
    idx=-1;
    enemy_tank_img=new QLabel();
    enemy_tank_img->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    live=1;
    enemytank_style=1;
    enemy_HP=1;
}

void EnemyTank::showTank(QWidget*pa)
{
    if(enemytank_style==1){
        enemy_HP=1;
    }
    else if(enemytank_style==2){
        enemy_HP=5;
    }
    enemy_tank_img->setParent(pa);
    if(enemytank_style==1)
    {
    Enemy_Tank.load(":/2/Res/res2/up.jpg");
    enemy_tank_img->setPixmap(Enemy_Tank);
    enemy_tank_img->move(currentX,currentY);
    //设置坦克图片始终在顶部
    enemy_tank_img->show();
    enemy_tank_img->setWindowFlags(enemy_tank_img->windowFlags() | Qt::WindowStaysOnTopHint);
    }
    else if(enemytank_style==2){
        Enemy_Tank.load(":/1/Res/res/tank_up.jpg");
        QPixmap scaledPixmap = Enemy_Tank.scaled(60,60, Qt::KeepAspectRatio, Qt::FastTransformation);
        enemy_tank_img->setPixmap(scaledPixmap);
        enemy_tank_img->move(currentX,currentY);
        //设置坦克图片始终在顶部
        enemy_tank_img->show();
        enemy_tank_img->setWindowFlags(enemy_tank_img->windowFlags() | Qt::WindowStaysOnTopHint);
    }
    moveTimer = new QTimer(this);
    moveTimer->start(50); // 每50毫秒更新一次位置
    connect(moveTimer, &QTimer::timeout, this, &EnemyTank::updatePosition);

    pauseTimer = new QTimer(this);
    connect(pauseTimer, &QTimer::timeout, this, &EnemyTank::resumeMovement);
    srand(static_cast<unsigned>(time(0)));
}

void EnemyTank::updatePosition() {
    if(!live) return;
    if (isPaused) return;

    if (moveCounter >= maxMoveSteps) {
        chooseNewDirection_smarter();
        moveCounter = 0;
        return;
    } else {
        moveCounter++;
    }
    updatemapsit();
    int stepSize = 5; // 设置步长
    switch (angle) {
    case 0: // Up
        if (!irremovable()) currentY -= stepSize;
        if(enemytank_style==1)
        {
            Enemy_Tank.load(":/2/Res/res2/up.jpg");
            enemy_tank_img->setPixmap(Enemy_Tank);
        }
        else if(enemytank_style==2)
        {
            Enemy_Tank.load(":/1/Res/res/tank_up.jpg");
            QPixmap scaledPixmap = Enemy_Tank.scaled(60,60, Qt::KeepAspectRatio, Qt::FastTransformation);
            enemy_tank_img->setPixmap(scaledPixmap);
        }
        enemy_tank_img->move(currentX,currentY);
        break;
    case 90: // Right
        if (!irremovable()) currentX += stepSize;
        if(enemytank_style==1){
            Enemy_Tank.load(":/2/Res/res2/right.jpg");
            enemy_tank_img->setPixmap(Enemy_Tank);
        }
        else if(enemytank_style==2){
            Enemy_Tank.load(":/1/Res/res/tank_right.jpg");
            QPixmap scaledPixmap = Enemy_Tank.scaled(60,60, Qt::KeepAspectRatio, Qt::FastTransformation);
            enemy_tank_img->setPixmap(scaledPixmap);
        }
        enemy_tank_img->move(currentX,currentY);
        break;
    case 180: // Down
        if (!irremovable()) currentY += stepSize;
        if(enemytank_style==1){
            Enemy_Tank.load(":/2/Res/res2/down.jpg");
            enemy_tank_img->setPixmap(Enemy_Tank);
        }
        else if(enemytank_style==2){
            Enemy_Tank.load(":/1/Res/res/tank_down.jpg");
            QPixmap scaledPixmap = Enemy_Tank.scaled(60,60, Qt::KeepAspectRatio, Qt::FastTransformation);
            enemy_tank_img->setPixmap(scaledPixmap);
        }
        enemy_tank_img->move(currentX,currentY);
        break;
    case 270: // Left
        if (!irremovable()) currentX -= stepSize;
        if(enemytank_style==1){
            Enemy_Tank.load(":/2/Res/res2/left.jpg");
            enemy_tank_img->setPixmap(Enemy_Tank);
        }
        else if(enemytank_style==2){
            Enemy_Tank.load(":/1/Res/res/tank_left.jpg");
            QPixmap scaledPixmap = Enemy_Tank.scaled(60,60, Qt::KeepAspectRatio, Qt::FastTransformation);
            enemy_tank_img->setPixmap(scaledPixmap);
        }
        enemy_tank_img->move(currentX,currentY);
        break;
    }
    if (rand() % 100 == 0) { // 5%的概率暂停
        isPaused = true;
        pauseTimer->start(500); // 暂停1秒
    }
    emit enemy_move();
}

void EnemyTank::resumeMovement() {
    isPaused = false;
    pauseTimer->stop();
}

void EnemyTank::chooseNewDirection() {
    if(!live) return;
    int direction = rand() % 4;
    switch (direction) {
    case 0:
        angle = 0; // Up
        break;
    case 1:
        angle = 90; // Right
        break;
    case 2:
        angle = 180; // Down
        break;
    case 3:
        angle = 270; // Left
        break;
    }
}

void EnemyTank::chooseNewDirection_smarter(){
    if(!live) return;
    int end_x=(playerTank->tankx+30)/60;
    int end_y=(playerTank->tanky+30)/60;
    int start_x=(currentX+30)/60;
    int start_y=(currentY+30)/60;

    QVector<QVector<bool>> visited(Mapy_size,QVector<bool>(Mapx_size,false));
    getDire_BFS(start_x,start_y,end_x,end_y,visited);
}

void EnemyTank::getDire_BFS(int sx, int sy, int ex, int ey, QVector<QVector<bool>>& visited)
{
    if(!live) return;
    QQueue<Box*> record;
    QQueue<Box*> qu;
    Box* box = new Box(sx, sy, nullptr);
    qu.push_back(box);
    record.push_back(box);
    visited[sx][sy] = true;
    int curx, cury, tempx, tempy;

    while (!qu.empty()) {
        box = qu.front();
        qu.pop_front();
        curx = box->x;
        cury = box->y;

        if (curx == ex && cury == ey) {
            break;
        }

        for (int i = 0; i < 4; ++i) {
            tempx = curx + dx[i];
            tempy = cury + dy[i];

            if (tempx >= 0 && tempx < Mapx_size && tempy >= 0 && tempy < Mapy_size && (MAP_Global[tempx][tempy]%10) == 0 && !(visited[tempx][tempy]%10)) {
                Box* addbox = new Box(tempx, tempy, box);
                qu.push_back(addbox);
                record.push_back(addbox);
                visited[tempx][tempy] = true;
            }
        }
    }

    // 处理找到路径或未找到路径的情况
    if (!qu.empty() && box->x == ex && box->y == ey)
    {
        while (box->pre != nullptr && (box->pre->x != sx || box->pre->y != sy))
        {
            box = box->pre;
        }
        if (box->pre == nullptr)
        {
            int direction = rand() % 4;
            switch (direction) {
            case 0:
                angle = 0; // Up
                break;
            case 1:
                angle = 90; // Right
                break;
            case 2:
                angle = 180; // Down
                break;
            case 3:
                angle = 270; // Left
                break;
            }
        }
        else
        {
            if (box->x == sx + 1)   //right
                angle = 90;
            else if (box->x == sx - 1)  //left
                angle = 270;
            else if (box->y == sy - 1)  //up
                angle = 0;
            else    //down
                angle = 180;
        }
    }
    else
    {
        int direction = rand() % 4;
        switch (direction)
        {
        case 0:
            angle = 0; // Up
            break;
        case 1:
            angle = 90; // Right
            break;
        case 2:
            angle = 180; // Down
            break;
        case 3:
            angle = 270; // Left
            break;
        }
    }

    // 释放动态分配的内存
    while (!record.isEmpty())
    {
        Box* temp = record.front();
        record.pop_front();
        delete temp;
    }

}

bool EnemyTank::irremovable() {
    if (currentX % 60 == 0 || currentY % 60 == 0) {
        if (angle == 0) {
            if (currentX % 60 == 0) {
                return (MAP_Global[map_enemy_tankx1][map_enemy_tanky1 - 1]%10) && (currentY % 60 == 0);
            } else {
                return (MAP_Global[map_enemy_tankx1][map_enemy_tanky1 - 1]%10) || (MAP_Global[map_enemy_tankx2][map_enemy_tanky2 - 1]%10);
            }
        }
        if (angle == 180) {
            if (currentX % 60 == 0) {
                return (MAP_Global[map_enemy_tankx1][map_enemy_tanky1 + 1]%10) && (currentY % 60 == 0);
            } else {
                return (MAP_Global[map_enemy_tankx1][map_enemy_tanky1 + 1]%10) || (MAP_Global[map_enemy_tankx2][map_enemy_tanky2 + 1]%10);
            }
        }
        if (angle == 270) {
            if (currentY % 60 == 0) {
                return MAP_Global[map_enemy_tankx1 - 1][map_enemy_tanky1]%10 && (currentX % 60 == 0);
            } else {
                return (MAP_Global[map_enemy_tankx1 - 1][map_enemy_tanky1]%10) || (MAP_Global[map_enemy_tankx4 - 1][map_enemy_tanky4]%10);
            }
        }
        if (angle == 90) {
            if (currentY % 60 == 0) {
                return (MAP_Global[map_enemy_tankx1 + 1][map_enemy_tanky1]%10) && (currentX % 60 == 0);
            } else {
                return (MAP_Global[map_enemy_tankx1 + 1][map_enemy_tanky1]%10) || (MAP_Global[map_enemy_tankx4 + 1][map_enemy_tanky4]%10);
            }
        }
    }
    return !((!MAP_Global[map_enemy_tankx1][map_enemy_tanky1]) && (!MAP_Global[map_enemy_tankx2][map_enemy_tanky2]) && (!MAP_Global[map_enemy_tankx3][map_enemy_tanky3]) && (!MAP_Global[map_enemy_tankx4][map_enemy_tanky4]));
}

void EnemyTank::updatemapsit(){
    map_enemy_tankx1=currentX/60;
    map_enemy_tanky1=currentY/60;
    map_enemy_tankx2=(currentX+60)/60;
    map_enemy_tanky2=map_enemy_tanky1;
    map_enemy_tankx3=map_enemy_tankx2;
    map_enemy_tanky3=(currentY+60)/60;
    map_enemy_tankx4=map_enemy_tankx1;
    map_enemy_tanky4=map_enemy_tanky3;
}

void EnemyTank::shoot(){
    if(!live) return;
    if(angle==0)
        type=1;
    else if(angle==90)
        type=4;
    else if(angle==180)
        type=2;
    else if(angle==270)
        type=3;

    idx++;
    if(idx<=bulletsnumber-1)
        bullets[idx].movebullet(this->parentWidget(),this->type,currentX,currentY);
    else
    {
        if(idx<2*bulletsnumber){
            bullets[idx-bulletsnumber].Disconnected();
            bullets[idx-bulletsnumber].movebullet(this->parentWidget(),this->type,currentX,currentY);
        }
        else
        {
            idx=bulletsnumber;
            bullets[idx-bulletsnumber].Disconnected();
            bullets[idx-bulletsnumber].movebullet(this->parentWidget(),this->type,currentX,currentY);
        }

    }
}

void  EnemyTank::startshoottime(){
    shootTimer = new QTimer(this);
    shootTimer->start(5000);
    connect(shootTimer,&QTimer::timeout,this,&EnemyTank::shoot);
}


void EnemyTank::Deletebullets(){
    for(int i=0;i<bulletsnumber;i++){
        bullets[i].hide();
        bullets[i].BOOM->hide();
        bullets[i].bigBOOM->hide();
    }
}

