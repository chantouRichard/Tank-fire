#include "frostenemy.h"

FrostEnemy::FrostEnemy(int startX, int startY, Tank*& playerTank):EnemyTank(startX,startY,playerTank)
{

}


void FrostEnemy::showTank(QWidget*pa)
{

    //    QPixmap scaledPixmap = Enemy_Tank.scaled(60,60, Qt::KeepAspectRatio, Qt::FastTransformation);
    enemy_HP=3;
    enemy_tank_img->setParent(pa);
    Enemy_Tank.load(FrostEnemyUp);
    enemy_tank_img->setPixmap(Enemy_Tank);
    enemy_tank_img->move(currentX,currentY);
    //设置坦克图片始终在顶部
    enemy_tank_img->show();
    enemy_tank_img->setWindowFlags(enemy_tank_img->windowFlags() | Qt::WindowStaysOnTopHint);

    moveTimer = new QTimer(this);
    moveTimer->start(10);
    connect(moveTimer, &QTimer::timeout, this, &FrostEnemy::updatePosition);

    pauseTimer = new QTimer(this);
    connect(pauseTimer, &QTimer::timeout, this, &FrostEnemy::resumeMovement);
    srand(static_cast<unsigned>(time(0)));
}


void FrostEnemy::updatePosition()
{
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
        if (!irremovable())
            currentY -= stepSize;
        Enemy_Tank.load(FrostEnemyUp);
        enemy_tank_img->setPixmap(Enemy_Tank);
        enemy_tank_img->move(currentX,currentY);
        break;
    case 90: // Right
        if (!irremovable()) currentX += stepSize;
        Enemy_Tank.load(FrostEnemyRight);
        enemy_tank_img->setPixmap(Enemy_Tank);
        enemy_tank_img->move(currentX,currentY);
        break;
    case 180: // Down
        if (!irremovable()) currentY += stepSize;
        Enemy_Tank.load(FrostEnemyDown);
        enemy_tank_img->setPixmap(Enemy_Tank);
        enemy_tank_img->move(currentX,currentY);
        break;
    case 270: // Left
        if (!irremovable()) currentX -= stepSize;
        Enemy_Tank.load(FrostEnemyLeft);
        enemy_tank_img->setPixmap(Enemy_Tank);
        enemy_tank_img->move(currentX,currentY);
        break;
    }
    if (rand() % 100 == 0) { // 5%的概率暂停
        isPaused = true;
        pauseTimer->start(500); // 暂停1秒
    }
    emit enemy_move();
}

void FrostEnemy::resumeMovement()
{
    isPaused = false;
    pauseTimer->stop();
}
