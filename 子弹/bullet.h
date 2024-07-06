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
    int enemyx; //记录对面阵营的x坐标
    int enemyy; //记录对面阵营的y坐标
    bool started;    //记录是否开始计时
    QTimer *bullettimer;
    QTimer *boomtimer;
    QTimer *bigboomtimer;
    int MAP[25][25];
    QPixmap BULL;
    QPixmap Boom;
    QPixmap Bigboom;
    QLabel *BULA;
    QLabel *BOOM;
    QLabel *bigBOOM;

    virtual void Loadmap(int map[25][25]);
    void movebullet(QWidget* parent,int style,int x,int y);//发射子弹的移动
    virtual bool checkmovebullet();//检查子弹是否可以继续移动
    virtual void updatemapsit();
    virtual void Disconnected();
    virtual void moveup();
    virtual void movedown();
    virtual void moveleft();
    virtual void moveright();
    virtual void bulletboom(int boomsitx,int boomsity);
    void updateenemy(int x,int y);
    bool checkshootenemy();

signals:
    virtual void boom(int x,int y);
};

#endif // BULLET_H
