#include "enemytank.h"
#include <QDebug>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <QPixmap>
#include <QPainter>
#include <QBrush>
#include <QWidget>
#include <QTimer>
#include <QLabel>

// Box 构造函数
Box::Box(int x, int y, Box* pre)
{
    this->x = x;
    this->y = y;
    this->pre = pre;
}

// 定义方向数组
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

// EnemyTank 构造函数
EnemyTank::EnemyTank(int startX, int startY, Tank*& my_tank, QWidget* parent)
    : QWidget(parent), currentX(startX), currentY(startY), angle(90), isPaused(false), moveCounter(0), playerTank(my_tank)
{
    idx = -1;
    enemy_tank_img = new QLabel();
    enemy_tank_img->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    live = 1;
    enemytank_style = 1;
    enemy_HP = 2;
    shootTimer = new QTimer(this);
}

// 显示坦克
void EnemyTank::showTank(QWidget* pa)
{
    if (enemytank_style == 1) {
        enemy_HP = 2;
    }
    else if (enemytank_style == 2) {
        enemy_HP = 3;
    }
    else if (enemytank_style == 3) {
        enemy_HP = 5;
    }

    enemy_tank_img->setParent(pa);

    if (enemytank_style == 1) {
        Enemy_Tank.load(Enemy1TankUp);
    }
    else if (enemytank_style == 2) {
        Enemy_Tank.load(Enemy2TankUp);
        Enemy_Tank = Enemy_Tank.scaled(60, 60, Qt::KeepAspectRatio, Qt::FastTransformation);
    }
    else if (enemytank_style == 3) {
        Enemy_Tank.load(Enemy3TankUp);
        Enemy_Tank = Enemy_Tank.scaled(60, 60, Qt::KeepAspectRatio, Qt::FastTransformation);
    }

    enemy_tank_img->setPixmap(Enemy_Tank);
    enemy_tank_img->move(currentX, currentY);
    enemy_tank_img->show();
    enemy_tank_img->setWindowFlags(enemy_tank_img->windowFlags() | Qt::WindowStaysOnTopHint);

    moveTimer = new QTimer(this);
    moveTimer->start(50);
    connect(moveTimer, &QTimer::timeout, this, &EnemyTank::updatePosition);

    pauseTimer = new QTimer(this);
    connect(pauseTimer, &QTimer::timeout, this, &EnemyTank::resumeMovement);

    srand(static_cast<unsigned>(time(0)));
}

// 更新位置
void EnemyTank::updatePosition()
{
    if (!live) return;
    if (isPaused) return;

    if (moveCounter >= maxMoveSteps) {
        chooseNewDirection_smarter();
        moveCounter = 0;
        return;
    }
    else {
        moveCounter++;
    }

    updatemapsit();
    int stepSize = 5; // 设置步长

    switch (angle) {
    case 0: // 向上
        if (!irremovable()) currentY -= stepSize;
        break;
    case 90: // 向右
        if (!irremovable()) currentX += stepSize;
        break;
    case 180: // 向下
        if (!irremovable()) currentY += stepSize;
        break;
    case 270: // 向左
        if (!irremovable()) currentX -= stepSize;
        break;
    }

    if (enemytank_style == 1) {
        if (angle == 0) Enemy_Tank.load(Enemy1TankUp);
        else if (angle == 90) Enemy_Tank.load(Enemy1TankRight);
        else if (angle == 180) Enemy_Tank.load(Enemy1TankDown);
        else if (angle == 270) Enemy_Tank.load(Enemy1TankLeft);
    }
    else if (enemytank_style == 2) {
        if (angle == 0) Enemy_Tank.load(Enemy2TankUp);
        else if (angle == 90) Enemy_Tank.load(Enemy2TankRight);
        else if (angle == 180) Enemy_Tank.load(Enemy2TankDown);
        else if (angle == 270) Enemy_Tank.load(Enemy2TankLeft);
        Enemy_Tank = Enemy_Tank.scaled(60, 60, Qt::KeepAspectRatio, Qt::FastTransformation);
    }
    else if (enemytank_style == 3) {
        if (angle == 0) Enemy_Tank.load(Enemy3TankUp);
        else if (angle == 90) Enemy_Tank.load(Enemy3TankRight);
        else if (angle == 180) Enemy_Tank.load(Enemy3TankDown);
        else if (angle == 270) Enemy_Tank.load(Enemy3TankLeft);
        Enemy_Tank = Enemy_Tank.scaled(60, 60, Qt::KeepAspectRatio, Qt::FastTransformation);
    }

    enemy_tank_img->setPixmap(Enemy_Tank);
    enemy_tank_img->move(currentX, currentY);

    if (rand() % 100 == 0) { // 5%的概率暂停
        isPaused = true;
        pauseTimer->start(500); // 暂停1秒
    }

    emit enemy_move();
}

// 恢复移动
void EnemyTank::resumeMovement()
{
    isPaused = false;
    pauseTimer->stop();
}

// 选择新方向
void EnemyTank::chooseNewDirection()
{
    if (!live) return;

    int direction = rand() % 4;
    switch (direction) {
    case 0:
        angle = 0; // 向上
        break;
    case 1:
        angle = 90; // 向右
        break;
    case 2:
        angle = 180; // 向下
        break;
    case 3:
        angle = 270; // 向左
        break;
    }
}

// 更智能地选择新方向
void EnemyTank::chooseNewDirection_smarter()
{
    if (!live) return;

    int end_x = (playerTank->tankx + 30) / 60;
    int end_y = (playerTank->tanky + 30) / 60;
    int start_x = (currentX + 30) / 60;
    int start_y = (currentY + 30) / 60;

    QVector<QVector<bool>> visited(Mapy_size, QVector<bool>(Mapx_size, false));
    getDire_BFS(start_x, start_y, end_x, end_y, visited);
}

// 广度优先搜索获取方向
void EnemyTank::getDire_BFS(int sx, int sy, int ex, int ey, QVector<QVector<bool>>& visited)
{
    if (!live) return;

    QQueue<Box*> record;
    QQueue<Box*> qu;
    Box* box = new Box(sx, sy, nullptr);
    qu.push_back(box);
    record.push_back(box);
    visited[sy][sx] = true;

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

            if (tempx >= 0 && tempx < Mapx_size && tempy >= 0 && tempy < Mapy_size && MAP_Global[tempy][tempx] % 10 == 0 && !visited[tempy][tempx]) {
                Box* addbox = new Box(tempx, tempy, box);
                qu.push_back(addbox);
                record.push_back(addbox);
                visited[tempy][tempx] = true;
            }
        }
    }

    // 处理找到路径或未找到路径的情况
    if (!qu.empty() && box->x == ex && box->y == ey) {
        while (box->pre != nullptr && (box->pre->x != sx || box->pre->y != sy)) {
            box = box->pre;
        }
        if (box->pre == nullptr) {
            chooseNewDirection();
        }
        else {
            if (box->x == sx + 1) angle = 90; // 向右
            else if (box->x == sx - 1) angle = 270; // 向左
            else if (box->y == sy - 1) angle = 0; // 向上
            else angle = 180; // 向下
        }
    }
    else {
        chooseNewDirection();
    }

    // 释放动态分配的内存
    while (!record.isEmpty()) {
        Box* temp = record.front();
        record.pop_front();
        delete temp;
    }
}

// 检查坦克是否可以移动
bool EnemyTank::irremovable()
{
    currentX = enemy_tank_img->pos().x();
    currentY = enemy_tank_img->pos().y();
    updatemapsit();

    bool check1 = MAP_Global[map_enemy_tanky1 - 1][map_enemy_tankx1] != 0 && MAP_Global[map_enemy_tanky1 - 1][map_enemy_tankx1] <= 10;
    bool check2 = MAP_Global[map_enemy_tanky2 - 1][map_enemy_tankx2] != 0 && MAP_Global[map_enemy_tanky2 - 1][map_enemy_tankx2] <= 10;
    bool check3 = MAP_Global[map_enemy_tanky1 + 1][map_enemy_tankx1] != 0 && MAP_Global[map_enemy_tanky1 + 1][map_enemy_tankx1] <= 10;
    bool check4 = MAP_Global[map_enemy_tanky2 + 1][map_enemy_tankx2] != 0 && MAP_Global[map_enemy_tanky2 + 1][map_enemy_tankx2] <= 10;
    bool check5 = MAP_Global[map_enemy_tanky1][map_enemy_tankx1 - 1] != 0 && MAP_Global[map_enemy_tanky1][map_enemy_tankx1 - 1] <= 10;
    bool check6 = MAP_Global[map_enemy_tanky4][map_enemy_tankx4 - 1] != 0 && MAP_Global[map_enemy_tanky4][map_enemy_tankx4 - 1] <= 10;
    bool check7 = MAP_Global[map_enemy_tanky1][map_enemy_tankx1 + 1] != 0 && MAP_Global[map_enemy_tanky1][map_enemy_tankx1 + 1] <= 10;
    bool check8 = MAP_Global[map_enemy_tanky4][map_enemy_tankx4 + 1] != 0 && MAP_Global[map_enemy_tanky4][map_enemy_tankx4 + 1] <= 10;
    bool check9 = MAP_Global[map_enemy_tanky1][map_enemy_tankx1] != 0 && MAP_Global[map_enemy_tanky1][map_enemy_tankx1] <= 10;
    bool check10 = MAP_Global[map_enemy_tanky2][map_enemy_tankx2] != 0 && MAP_Global[map_enemy_tanky2][map_enemy_tankx2] <= 10;
    bool check11 = MAP_Global[map_enemy_tanky3][map_enemy_tankx3] != 0 && MAP_Global[map_enemy_tanky3][map_enemy_tankx3] <= 10;
    bool check12 = MAP_Global[map_enemy_tanky4][map_enemy_tankx4] != 0 && MAP_Global[map_enemy_tanky4][map_enemy_tankx4] <= 10;

    if (currentX % 60 == 0 || currentY % 60 == 0) {
        if (angle == 0) return check1 && (currentY % 60 == 0);
        if (angle == 180) return check3 && (currentY % 60 == 0);
        if (angle == 270) return check5 && (currentX % 60 == 0);
        if (angle == 90) return check7 && (currentX % 60 == 0);
    }

    return !(check9 || check10 || check11 || check12);
}

// 更新坦克的地图位置
void EnemyTank::updatemapsit()
{
    map_enemy_tankx1 = currentX / 60;
    map_enemy_tanky1 = currentY / 60;
    map_enemy_tankx2 = (currentX + 60) / 60;
    map_enemy_tanky2 = map_enemy_tanky1;
    map_enemy_tankx3 = map_enemy_tankx2;
    map_enemy_tanky3 = (currentY + 60) / 60;
    map_enemy_tankx4 = map_enemy_tankx1;
    map_enemy_tanky4 = map_enemy_tanky3;
}

// 射击函数
void EnemyTank::shoot()
{
    if (!live) return;

    if (angle == 0) type = 1;
    else if (angle == 90) type = 4;
    else if (angle == 180) type = 2;
    else if (angle == 270) type = 3;

    idx++;
    if (idx <= bulletsnumber - 1)
        bullets[idx].movebullet(this->parentWidget(), this->type, currentX, currentY);
    else {
        if (idx < 2 * bulletsnumber) {
            bullets[idx - bulletsnumber].Disconnected();
            bullets[idx - bulletsnumber].movebullet(this->parentWidget(), this->type, currentX, currentY);
        }
        else {
            idx = bulletsnumber;
            bullets[idx - bulletsnumber].Disconnected();
            bullets[idx - bulletsnumber].movebullet(this->parentWidget(), this->type, currentX, currentY);
        }
    }
}

// 启动射击计时器
void EnemyTank::startshoottime(int inter)
{
    shootTimer->start(inter);
    connect(shootTimer, &QTimer::timeout, this, &EnemyTank::shoot);
}

// 删除子弹
void EnemyTank::Deletebullets()
{
    for (int i = 0; i < bulletsnumber; i++) {
        bullets[i].BULA->hide();
        bullets[i].BOOM->hide();
    }
}
