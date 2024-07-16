#ifndef BULLET_H
#define BULLET_H

#include "global.h"
#include <QObject>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QTransform>
#include <QTimer>
#include <QtDebug>
#include <QMovie>

class Bullet : public QWidget
{
    Q_OBJECT
public:
    explicit Bullet(QWidget *parent = nullptr);
    // 构造函数

    int type;
    // 子弹移动方向

    int bux;
    // 子弹的像素x坐标

    int buy;
    // 子弹的像素y坐标

    int mapbux;
    // 子弹的格子x坐标

    int mapbuy;
    // 子弹的格子y坐标

    int boommapsitx;
    // 爆炸格子x坐标

    int boommapsity;
    // 爆炸格子y坐标

    int *enemyx;
    // 存储敌人x坐标的数组

    int *enemyy;
    // 存储敌人y坐标的数组

    int enemy_num;
    // 敌人的数量

    bool started;
    // 计时器是否已启动的标志

    QTimer *bullettimer;
    // 子弹移动的计时器

    QPixmap BULL;
    // 子弹的图片

    QLabel *BULA;
    // 显示子弹的标签

    QMovie *boomvideo;
    // 爆炸动画

    QLabel *BOOM;
    // 显示爆炸的标签

    QTimer *boomtimer;
    // 爆炸动画的计时器

    void getenemysit(int*& x, int*& y);
    // 获取敌人位置的函数

    void stoptimer();
    // 停止子弹计时器的函数

    void movebullet(QWidget* parent, int style, int x, int y);
    // 子弹移动的函数

    virtual bool checkmovebullet();
    // 检查子弹是否可以继续移动的虚函数

    void updatemapsit();
    // 更新子弹的格子位置

    void Disconnected();
    // 断开信号和槽的连接

    void moveup();
    // 向上移动子弹

    void movedown();
    // 向下移动子弹

    void moveleft();
    // 向左移动子弹

    void moveright();
    // 向右移动子弹

    void bulletboom(int boomsitx, int boomsity);
    // 处理子弹爆炸

    virtual bool checkshootenemy();
    // 检查子弹是否击中敌人的虚函数

signals:
    void boom(int x, int y);
    // 爆炸信号，带有x和y坐标

    void kill_enemy(int i);
    // 击杀敌人的信号，带有敌人的索引
};

#endif // BULLET_H
