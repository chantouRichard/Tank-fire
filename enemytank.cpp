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


EnemyTank::EnemyTank(int startX, int startY, QWidget* parent)
    : QWidget(parent), currentX(startX), currentY(startY), angle(90), isPaused(false), moveCounter(0) {

    tank_img=new QLabel();
}

void EnemyTank::showTank(QWidget*pa)
{
    tank_img->setParent(pa);
    TANK.load(":/2/Res/res2/up.jpg");
    tank_img->setPixmap(TANK);
    tank_img->move(currentX,currentY);
    //设置坦克图片始终在顶部
    tank_img->setWindowFlags(tank_img->windowFlags() | Qt::WindowStaysOnTopHint);
    moveTimer = new QTimer(this);
    moveTimer->start(20); // 每20毫秒更新一次位置
    connect(moveTimer, &QTimer::timeout, this, &EnemyTank::updatePosition);
    
    pauseTimer = new QTimer(this);
    connect(pauseTimer, &QTimer::timeout, this, &EnemyTank::resumeMovement);
    srand(static_cast<unsigned>(time(0)));
}

void EnemyTank::updatePosition() {
    if (isPaused) return;

    if (moveCounter >= maxMoveSteps) {
        chooseNewDirection();
        moveCounter = 0;
    } else {
        moveCounter++;

    }
    updatemapsit();
    int stepSize = 5; // 设置步长
    switch (angle) {
        case 0: // Up
            if (!irremovable()) currentY -= stepSize;
            TANK.load(":/2/Res/res2/up.jpg");
            tank_img->setPixmap(TANK);
            tank_img->move(currentX,currentY);
            break;
        case 90: // Right
            if (!irremovable()) currentX += stepSize;
            TANK.load(":/2/Res/res2/right.jpg");
            tank_img->setPixmap(TANK);
            tank_img->move(currentX,currentY);
            break;
        case 180: // Down
            if (!irremovable()) currentY += stepSize;
            TANK.load(":/2/Res/res2/down.jpg");
            tank_img->setPixmap(TANK);
            tank_img->move(currentX,currentY);
            break;
        case 270: // Left
            if (!irremovable()) currentX -= stepSize;
            TANK.load(":/2/Res/res2/left.jpg");
            tank_img->setPixmap(TANK);
            tank_img->move(currentX,currentY);
            break;
    }
    if (rand() % 100 == 0) { // 5%的概率暂停
        isPaused = true;
        pauseTimer->start(500); // 暂停1秒
    }
}

void EnemyTank::resumeMovement() {
    isPaused = false;
    pauseTimer->stop();
}

void EnemyTank::chooseNewDirection() {
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
bool EnemyTank::irremovable() {

    if (currentX % 60 == 0 || currentY % 60 == 0) {
        if (angle == 0) {
            if (currentX % 60 == 0) {
                return MAP[maptankx1][maptanky1 - 1] && (currentY % 60 == 0);
            } else {
                return MAP[maptankx1][maptanky1 - 1] || MAP[maptankx2][maptanky2 - 1];
            }
        }
        if (angle == 180) {
            if (currentX % 60 == 0) {
                return MAP[maptankx1][maptanky1 + 1] && (currentY % 60 == 0);
            } else {
                return MAP[maptankx1][maptanky1 + 1] || MAP[maptankx2][maptanky2 + 1];
            }
        }
        if (angle == 270) {
            if (currentY % 60 == 0) {
                return MAP[maptankx1 - 1][maptanky1] && (currentX % 60 == 0);
            } else {
                return MAP[maptankx1 - 1][maptanky1] || MAP[maptankx4 - 1][maptanky4];
            }
        }
        if (angle == 90) {
            if (currentY % 60 == 0) {
                return MAP[maptankx1 + 1][maptanky1] && (currentX % 60 == 0);
            } else {
                return MAP[maptankx1 + 1][maptanky1] || MAP[maptankx4 + 1][maptanky4];
            }
        }
    }
    return !((!MAP[maptankx1][maptanky1]) && (!MAP[maptankx2][maptanky2]) && (!MAP[maptankx3][maptanky3]) && (!MAP[maptankx4][maptanky4]));
}

void EnemyTank::Loadmap(int map[Mapx_size][Mapy_size]) {
    for (int i = 0; i < Mapx_size; i++) {
        for (int j = 0; j < Mapy_size; j++) {
            MAP[i][j] = map[i][j];
        }
    }
}

void EnemyTank::updatemapsit(){
    maptankx1=currentX/60;
    maptanky1=currentY/60;
    maptankx2=(currentX+60)/60;
    maptanky2=maptanky1;
    maptankx3=maptankx2;
    maptanky3=(currentY+60)/60;
    maptankx4=maptankx1;
    maptanky4=maptanky3;
}
