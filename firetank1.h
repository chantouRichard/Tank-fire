#ifndef FIRETANK1_H
#define FIRETANK1_H

#include <QObject>
#include "enemytank.h"
#include "firebullet.h"

class firetank : public EnemyTank
{
    Q_OBJECT
public:
    // 构造函数
    explicit firetank(int startX, int startY, Tank*& playerTank, QWidget* parent = nullptr);
    // 显示坦克
    void showTank(QWidget* pa);

    // 火焰子弹数组
    firebullet fbullets[5];
    // 射击函数
    void shoot();
    // 开始射击计时
    void startshoottime();

private slots:
    // 更新位置
    void updatePosition();
    // 恢复移动
    void resumeMovement();

signals:

};

#endif // FROSTENEMY1_H
