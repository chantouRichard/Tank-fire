#include "bullet.h"
#include "global.h"

// 构造函数
Bullet::Bullet(QWidget *parent) : QWidget(parent)
{
    BULA = new QLabel; // 子弹标签
    BOOM = new QLabel; // 爆炸标签
    boomvideo = new QMovie(BulletBoom_gif); // 爆炸动画

    BULL.load(bullet5_pic); // 加载子弹图片
    BULL = BULL.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 缩放子弹图片
    BULA->setPixmap(BULL);
    BULA->setParent(parent);

    boomvideo->setScaledSize(QSize(60, 60)); // 缩放爆炸动画
    BOOM->setMovie(boomvideo);

    bullettimer = new QTimer(this); // 子弹移动计时器
    boomtimer = new QTimer(this); // 爆炸计时器
    bullettimer->start(12);
    started = false;
}

// 断开子弹移动信号
void Bullet::Disconnected()
{
    if (type == 1) {
        disconnect(bullettimer, &QTimer::timeout, this, &Bullet::moveup);
        started = false;
    }
    if (type == 2) {
        disconnect(bullettimer, &QTimer::timeout, this, &Bullet::movedown);
        started = false;
    }
    if (type == 3) {
        disconnect(bullettimer, &QTimer::timeout, this, &Bullet::moveleft);
        started = false;
    }
    if (type == 4) {
        disconnect(bullettimer, &QTimer::timeout, this, &Bullet::moveright);
        started = false;
    }
}

// 向上移动
void Bullet::moveup()
{
    if (!checkmovebullet()) {
        buy = buy - 5;
        BULA->move(bux, buy);
    }
}

// 向下移动
void Bullet::movedown()
{
    if (!checkmovebullet()) {
        buy = buy + 5;
        BULA->move(bux, buy);
    }
}

// 向左移动
void Bullet::moveleft()
{
    if (!checkmovebullet()) {
        bux = bux - 5;
        BULA->move(bux, buy);
    }
}

// 向右移动
void Bullet::moveright()
{
    if (!checkmovebullet()) {
        bux = bux + 5;
        BULA->move(bux, buy);
    }
}

// 发射子弹
void Bullet::movebullet(QWidget* parent, int style, int x, int y)
{
    type = style;
    bux = x;
    buy = y;

    if (type == 1 && !started) {
        started = true;
        bux += 16;
        buy = buy - 15;
        BULA->setParent(parent);
        BULA->move(bux, buy);
        BULA->show();
        connect(bullettimer, &QTimer::timeout, this, &Bullet::moveup);
    }
    if (type == 2 && !started) {
        started = true;
        bux += 15;
        buy += 55;
        BULA->move(bux, buy);
        BULA->setParent(parent);
        BULA->show();
        connect(bullettimer, &QTimer::timeout, this, &Bullet::movedown);
    }
    if (type == 3 && !started) {
        started = true;
        bux = bux - 15;
        buy += 17;
        BULA->move(bux, buy);
        BULA->setParent(parent);
        BULA->show();
        connect(bullettimer, &QTimer::timeout, this, &Bullet::moveleft);
    }
    if (type == 4 && !started) {
        started = true;
        bux += 55;
        buy += 15;
        BULA->move(bux, buy);
        BULA->setParent(parent);
        BULA->show();
        connect(bullettimer, &QTimer::timeout, this, &Bullet::moveright);
    }
}

// 检查子弹是否可以继续移动
bool Bullet::checkmovebullet()
{
    updatemapsit();
    if (checkshootenemy()) {
        boommapsitx = mapbux;
        boommapsity = mapbuy;
        return true;
    }
    if (type == 1) {
        if (MAP_Global[mapbuy][mapbux] != 0 && MAP_Global[mapbuy][mapbux] != 3 && MAP_Global[mapbuy][mapbux] <= 10) {
            boommapsitx = mapbux;
            boommapsity = mapbuy;
            bulletboom(60 * boommapsitx, 60 * boommapsity);
            emit boom(mapbuy, mapbux);
            return true;
        }
        if (MAP_Global[mapbuy - 1][mapbux] == 0 || MAP_Global[mapbuy - 1][mapbux] == 3 || MAP_Global[mapbuy - 1][mapbux] > 10) {
            return false;
        } else {
            if ((buy + 15) > 60 * mapbuy)
                return false;
            else {
                boommapsitx = mapbux;
                boommapsity = mapbuy - 1;
                bulletboom(60 * boommapsitx, 60 * boommapsity);
                emit boom(mapbuy - 1, mapbux);
                return true;
            }
        }
    }
    if (type == 2) {
        if (MAP_Global[mapbuy][mapbux] != 0 && MAP_Global[mapbuy][mapbux] != 3 && MAP_Global[mapbuy][mapbux] <= 10) {
            boommapsitx = mapbux;
            boommapsity = mapbuy;
            bulletboom(60 * boommapsitx, 60 * boommapsity);
            emit boom(mapbuy, mapbux);
            return true;
        }
        if (MAP_Global[mapbuy + 1][mapbux] == 0 || MAP_Global[mapbuy + 1][mapbux] == 3 || MAP_Global[mapbuy + 1][mapbux] > 10) {
            return false;
        } else {
            if ((buy + 15 + 5) < 60 * (mapbuy + 1)) {
                return false;
            } else {
                boommapsitx = mapbux;
                boommapsity = mapbuy + 1;
                bulletboom(60 * boommapsitx, 60 * boommapsity);
                emit boom(mapbuy + 1, mapbux);
                return true;
            }
        }
    }
    if (type == 3) {
        if (MAP_Global[mapbuy][mapbux] != 0 && MAP_Global[mapbuy][mapbux] != 3 && MAP_Global[mapbuy][mapbux] <= 10) {
            boommapsitx = mapbux;
            boommapsity = mapbuy;
            bulletboom(60 * boommapsitx, 60 * boommapsity);
            emit boom(mapbuy, mapbux);
            return true;
        }
        if (MAP_Global[mapbuy][mapbux - 1] == 0 || MAP_Global[mapbuy][mapbux - 1] == 3 || MAP_Global[mapbuy][mapbux - 1] > 10) {
            return false;
        } else {
            if ((bux + 15) > 60 * mapbux)
                return false;
            else {
                boommapsitx = mapbux - 1;
                boommapsity = mapbuy;
                bulletboom(60 * boommapsitx, 60 * boommapsity);
                emit boom(mapbuy, mapbux - 1);
                return true;
            }
        }
    }
    if (type == 4) {
        if (MAP_Global[mapbuy][mapbux] != 0 && MAP_Global[mapbuy][mapbux] != 3 && MAP_Global[mapbuy][mapbux] <= 10) {
            boommapsitx = mapbux;
            boommapsity = mapbuy;
            bulletboom(60 * boommapsitx, 60 * boommapsity);
            emit boom(mapbuy, mapbux);
            return true;
        }
        if (MAP_Global[mapbuy][mapbux + 1] == 0 || MAP_Global[mapbuy][mapbux + 1] == 3 || MAP_Global[mapbuy][mapbux + 1] > 10) {
            return false;
        } else {
            if ((bux + 15 + 5) < 60 * (mapbux + 1)) {
                return false;
            } else {
                boommapsitx = mapbux + 1;
                boommapsity = mapbuy;
                bulletboom(60 * boommapsitx, 60 * boommapsity);
                emit boom(mapbuy, mapbux + 1);
                return true;
            }
        }
    }
    return false;
}

// 检查子弹是否击中敌人
bool Bullet::checkshootenemy()
{
    for (int i = 0; i < enemy_num; i++) {
        if ((bux + 15) >= enemyx[i] && (bux + 15) <= (enemyx[i] + 60) && (buy + 15) >= enemyy[i] && (buy + 15) <= (enemyy[i] + 60)) {
            bulletboom(enemyx[i], enemyy[i]);
            emit kill_enemy(i);
            return true;
        }
    }
    return false;
}

// 子弹爆炸处理
void Bullet::bulletboom(int boomsitx, int boomsity)
{
    BULA->hide();
    Disconnected();
    boomtimer->start(400);
    BOOM->setParent(BULA->parentWidget());
    BOOM->move(boomsitx, boomsity);
    boomvideo->start();
    boomvideo->setSpeed(400);
    BOOM->show();
    connect(boomtimer, &QTimer::timeout, [=]() {
        boomvideo->stop();
        BOOM->hide();
        boomtimer->stop();
        boomtimer->disconnect();
    });
}

// 获取敌人位置
void Bullet::getenemysit(int*& x, int*& y)
{
    enemyx = x;
    enemyy = y;
}

// 更新子弹的地图位置
void Bullet::updatemapsit()
{
    mapbux = (bux + 15) / 60;
    mapbuy = (buy + 15) / 60;
}
