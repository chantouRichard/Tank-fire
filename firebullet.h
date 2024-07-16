#ifndef FIREBULLET_H
#define FIREBULLE1_H

#include "enemybullet.h"
#include "global.h"
#include <QWidget>
#include <QMovie>
#include <QTimer>

class firebullet : public Bullet
{
    Q_OBJECT
public:
    explicit firebullet(QWidget *parent = nullptr);
    bool checkmovebullet() override;
    QLabel *BULA1;
    QPixmap BULL;
signals:
    void refrosted(int mapsitx,int mapxity);
public:
//    EnemyTank* parent;
    int enemyx; //记录对面阵营的x坐标
    int enemyy; //记录对面阵营的y坐标

    void bulletboom(int boomsitx, int boomsity);
    bool checkshootenemy() override;
    void getenemysit(int x, int y);

//    void set_parent(EnemyTank* parent);
signals:
    void kill_my_tank();
    void fired(int mapx,int mapy);
};

#endif // FROSTBULLET1_H
