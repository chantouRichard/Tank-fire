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

    explicit enemybullet(QWidget *parent = nullptr);
    void bulletboom(int boomsitx, int boomsity);
//    void set_parent(EnemyTank* parent);
signals:

};

#endif // ENEMYBULLET_H
