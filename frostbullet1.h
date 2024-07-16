#ifndef FROSTBULLET1_H
#define FROSTBULLET1_H

#include "enemybullet.h"
#include "global.h"
#include <QWidget>
#include <QMovie>
#include <QTimer>

class frostbullet : public Bullet
{
    Q_OBJECT
public:
    // 构造函数
    explicit frostbullet(QWidget *parent = nullptr);
    // 检查子弹是否可以继续移动
    bool checkmovebullet() override;
    // 子弹的标签
    QLabel *BULA1;
    // 子弹的图片
    QPixmap BULL;

signals:
    // 再次冻结信号
    void refrosted(int mapsitx, int mapxity);

public:
    // 记录对面阵营的x坐标
    int enemyx;
    // 记录对面阵营的y坐标
    int enemyy;

    // 子弹爆炸
    void bulletboom(int boomsitx, int boomsity);
    // 检查子弹是否击中敌人
    bool checkshootenemy() override;
    // 获取敌人位置
    void getenemysit(int x, int y);

signals:
    // 击中我方坦克信号
    void kill_my_tank();
    // 冻结信号
    void frosted(int mapx, int mapy);
};

#endif // FROSTBULLET1_H
