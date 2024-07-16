#ifndef FROSTBULLET1_H
#define FROSTBULLET1_H

#include "enemybullet.h"
#include "global.h"
#include <QWidget>
#include <QMovie>
#include <QTimer>

class frostBullet1 : public enemybullet
{
    Q_OBJECT
public:
    explicit frostBullet1(QWidget *parent = nullptr);
    bool checkmovebullet() override;
signals:
    void refrosted(int mapsitx,int mapxity);
};

#endif // FROSTBULLET1_H
