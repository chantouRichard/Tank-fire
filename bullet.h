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
class Bullet : public QWidget
{
    Q_OBJECT
public:
    explicit Bullet(QWidget *parent = nullptr);

    int type;       //子弹移动方向
    int bux;
    int buy;        //记录子弹的像素位置
    int mapbux;
    int mapbuy;     //子弹的格子位置
    int boommapsitx;
    int boommapsity;
    int *enemyx; //记录对面阵营的x坐标
    int *enemyy; //记录对面阵营的y坐标
    int enemy_num;
    bool started;    //记录是否开始计时

    QTimer *bullettimer;
    QPixmap BULL;
    QLabel *BULA;
    QPixmap Boom;
    QPixmap Bigboom;
    QLabel *BOOM;
    QLabel *bigBOOM;
    QTimer *boomtimer;
    QTimer *bigboomtimer;
    void getenemysit(int*& x,int*& y);
    void stoptimer();
    void movebullet(QWidget* parent,int style,int x,int y);//发射子弹的移动
    virtual bool checkmovebullet();//检查子弹是否可以继续移动
    void updatemapsit();
    void Disconnected();
    void moveup();
    void movedown();
    void moveleft();
    void moveright();
    void bulletboom(int boomsitx,int boomsity);
    virtual bool checkshootenemy();
signals:
    void boom(int x,int y);
    void kill_enemy(int i);
};

#endif // BULLET_H
