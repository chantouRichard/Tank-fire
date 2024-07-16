#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "bullet.h"
#include <QObject>
#include <QWidget>

class enemybullet : public Bullet
{
    Q_OBJECT
public:
    int enemyx;
    // 记录对面阵营的x坐标

    int enemyy;
    // 记录对面阵营的y坐标

    explicit enemybullet(QWidget *parent = nullptr);
    // 构造函数

    void bulletboom(int boomsitx, int boomsity);
    // 处理子弹爆炸

    bool checkshootenemy() override;
    // 检查子弹是否击中敌人

    void getenemysit(int x, int y);
    // 获取敌人位置

    bool checkmovebullet() override;
    // 检查子弹是否可以继续移动

signals:
    void kill_my_tank();
    // 击中我方坦克的信号
};

#endif // ENEMYBULLET_H
