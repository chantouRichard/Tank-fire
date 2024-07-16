#ifndef FROSTENEMY1_H
#define FROSTENEMY1_H

#include <QObject>
#include "enemytank.h"
#include "frostbullet1.h"

class frostenemy1 : public EnemyTank
{
    Q_OBJECT
public:
    // 构造函数
    explicit frostenemy1(int startX, int startY, Tank*& playerTank, QWidget* parent = nullptr);
    // 显示坦克
    void showTank(QWidget* pa);
    // 冰冻子弹数组
    frostbullet fbullets[5];
    // 射击函数
    void shoot();
    // 开始射击计时
    void startshoottime();

private slots:
    // 更新位置
    void updatePosition();
    // 随机移动
    void resumeMovement();

signals:

};

#endif // FROSTENEMY1_H
