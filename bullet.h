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
    QTimer *bullettimer;
    void stoptimer();
    int type;    //标志子弹方向，1：上，2：下，3：左，4：右
    QPixmap BULL;
    QLabel *BULA=new QLabel;
    void movebullet(QWidget*parent,int style,int x,int y);//发射子弹的移动
    void checkmovebullet(int type);//检查子弹是否可以继续移动
    int bux;int buy;//记录子弹的位置
    int started; //记录是否开始计时
    void Disconnected();
    void moveup();
    void movedown();
    void moveleft();
    void moveright();
signals:

};

#endif // BULLET_H
