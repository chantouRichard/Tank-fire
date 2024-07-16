#ifndef FROSTENEMY_H
#define FROSTENEMY_H
#include"enemytank.h"
#include"frostbullet1.h"
class FrostEnemy:public EnemyTank
{
public:
    FrostEnemy(int startX, int startY, Tank*& playerTank,QWidget);
    void showTank(QWidget*pa);

    frostbullet bullets[5];

private slots:
    void updatePosition();
    void resumeMovement();
};

#endif // FROSTENEMY_H
