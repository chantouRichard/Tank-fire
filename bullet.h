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
    bool started;    //记录是否开始计时
    QTimer *bullettimer;
    void stoptimer();

    int MAP[25][25];
    QPixmap BULL;
    QLabel *BULA;;

    void Loadmap(int map[25][25]);
    void movebullet(QWidget* parent,int style,int x,int y);//发射子弹的移动
    bool checkmovebullet();//检查子弹是否可以继续移动
    void updatemapsit();
    void Disconnected();
    void moveup();
    void movedown();
    void moveleft();
    void moveright();
};

#endif // BULLET_H
