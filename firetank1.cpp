#include "firetank.h"

// 构造函数
firetank::firetank(int startX, int startY, Tank*& playerTank, QWidget* parent)
    : EnemyTank(startX, startY, playerTank, parent)
{
}

// 显示火焰坦克
void firetank::showTank(QWidget* pa)
{
    enemy_HP = 3;
    enemy_tank_img->setParent(pa);
    Enemy_Tank.load(FireEnemyUp);
    Enemy_Tank = Enemy_Tank.scaled(60, 60);
    enemy_tank_img->setPixmap(Enemy_Tank);
    enemy_tank_img->move(currentX, currentY);
    // 设置坦克图片始终在顶部
    enemy_tank_img->show();
    enemy_tank_img->setWindowFlags(enemy_tank_img->windowFlags() | Qt::WindowStaysOnTopHint);

    moveTimer = new QTimer(this);
    moveTimer->start(50);
    connect(moveTimer, &QTimer::timeout, this, &firetank::updatePosition);

    pauseTimer = new QTimer(this);
    connect(pauseTimer, &QTimer::timeout, this, &firetank::resumeMovement);
    srand(static_cast<unsigned>(time(0)));
}

// 更新火焰坦克位置
void firetank::updatePosition()
{
    if (!live) return;
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
    case 0: // 向上
        if (!irremovable()) currentY -= stepSize;
        Enemy_Tank.load(FireEnemyUp);
        break;
    case 90: // 向右
        if (!irremovable()) currentX += stepSize;
        Enemy_Tank.load(FireEnemyRight);
        break;
    case 180: // 向下
        if (!irremovable()) currentY += stepSize;
        Enemy_Tank.load(FireEnemyDown);
        break;
    case 270: // 向左
        if (!irremovable()) currentX -= stepSize;
        Enemy_Tank.load(FireEnemyLeft);
        break;
    }
    Enemy_Tank = Enemy_Tank.scaled(60, 60);
    enemy_tank_img->setPixmap(Enemy_Tank);
    enemy_tank_img->move(currentX, currentY);

    if (rand() % 100 == 0) { // 5%的概率暂停
        isPaused = true;
        pauseTimer->start(500); // 暂停1秒
    }
    emit enemy_move();
}

// 恢复移动
void firetank::resumeMovement()
{
    isPaused = false;
    pauseTimer->stop();
}

// 火焰坦克射击
void firetank::shoot()
{
    if (!live) return;

    if (angle == 0) type = 1;
    else if (angle == 90) type = 4;
    else if (angle == 180) type = 2;
    else if (angle == 270) type = 3;

    idx++;
    if (idx <= bulletsnumber - 1)
        fbullets[idx].movebullet(this->parentWidget(), this->type, currentX, currentY);
    else {
        if (idx < 2 * bulletsnumber) {
            fbullets[idx - bulletsnumber].Disconnected();
            fbullets[idx - bulletsnumber].movebullet(this->parentWidget(), this->type, currentX, currentY);
        } else {
            idx = bulletsnumber;
            fbullets[idx - bulletsnumber].Disconnected();
            fbullets[idx - bulletsnumber].movebullet(this->parentWidget(), this->type, currentX, currentY);
        }
    }
}

// 启动射击计时器
void firetank::startshoottime()
{
    shootTimer->start(5000);
    connect(shootTimer, &QTimer::timeout, this, &firetank::shoot);
}
