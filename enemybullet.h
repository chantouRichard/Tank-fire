
#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include "bullet.h"
#include <QObject>
#include <QWidget>

class enemybullet : public Bullet
{
    Q_OBJECT
public:
//    EnemyTank* parent;
    int enemyx; //记录对面阵营的x坐标
    int enemyy; //记录对面阵营的y坐标
    explicit enemybullet(QWidget *parent = nullptr);
    void bulletboom(int boomsitx, int boomsity);
    bool checkshootenemy() override;
    void getenemysit(int x, int y);
    bool checkmovebullet() override;
//    void set_parent(EnemyTank* parent);
signals:
    void kill_my_tank();
};

#endif // ENEMYBULLET_H
