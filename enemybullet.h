#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include "bullet.h"
#include <QObject>
#include <QWidget>

class enemybullet : public Bullet
{
    Q_OBJECT
public:
    explicit enemybullet(QWidget *parent = nullptr);
    void bulletboom(int boomsitx, int boomsity) override;
signals:

};

#endif // ENEMYBULLET_H
