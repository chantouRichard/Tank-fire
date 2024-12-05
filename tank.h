#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QTransform>
#include <QWidget>
#include <QLabel>
#include <QVector>
#include "bullet.h"
QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class Tank : public QWidget
{
    Q_OBJECT

public:

    int idx;
    int type;//记录坦克方向
    int bulletnum;//记录子弹的数量
    int tankx;int tanky; //标记坦克的像素位置
    int enemy_tank_x;int enemy_tank_y;
    int maptankx1;int maptanky1; //标记坦克的地图位置
    int maptankx2;int maptanky2; //标记坦克的地图位置
    int maptankx3;int maptanky3; //标记坦克的地图位置
    int maptankx4;int maptanky4; //标记坦克的地图位置
    QLabel *tank_img;
    Bullet bugdet[5];
    QPixmap TANK;
    Tank(int init_tank_x,int init_tank_y,QWidget *parent = nullptr);
    void showtank(QWidget *pa);//生成坦克
    void keyPressEvent(QKeyEvent *event) override;
    void MOVE(QKeyEvent *event,int x,int y);//坦克的移动
    bool irremovable();   //检查坦克是否可以移动
    void shoot(QKeyEvent *event);       //坦克的射击
    void updatemapsit();
signals:

};
#endif // WIDGET_H
