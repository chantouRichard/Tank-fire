#include "frostbullet1.h"

// 构造函数
frostbullet::frostbullet(QWidget *parent) : Bullet(parent)
{
    BULA = new QLabel; // 子弹标签
    BOOM = new QLabel; // 爆炸标签
    boomvideo = new QMovie(BulletBoom_gif); // 爆炸动画

    BULL.load(frost_bullet_pic); // 加载冰冻子弹图片
    BULL = BULL.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 缩放子弹图片
    BULA->setPixmap(BULL);
    BULA->setParent(parent);

    boomvideo->setScaledSize(QSize(60, 60)); // 缩放爆炸动画
    BOOM->setMovie(boomvideo);

    bullettimer = new QTimer(this); // 子弹移动计时器
    boomtimer = new QTimer(this); // 爆炸计时器
    bullettimer->start(5);
    started = false;
}

// 检查子弹是否可以继续移动
bool frostbullet::checkmovebullet()
{
    updatemapsit();
    emit frosted(this->mapbuy, this->mapbux);

    if (checkshootenemy()) {
        boommapsitx = mapbux;
        boommapsity = mapbuy;
        emit kill_my_tank();
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

// 子弹爆炸处理
void frostbullet::bulletboom(int boomsitx, int boomsity)
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

// 检查子弹是否击中敌人
bool frostbullet::checkshootenemy()
{
    if ((bux + 15) >= enemyx && (bux + 15) <= (enemyx + 60) && (buy + 15) >= enemyy && (buy + 15) <= (enemyy + 60)) {
        bulletboom(enemyx, enemyy);
        return true;
    }
    return false;
}

// 获取敌人位置
void frostbullet::getenemysit(int x, int y)
{
    enemyx = x;
    enemyy = y;
}
