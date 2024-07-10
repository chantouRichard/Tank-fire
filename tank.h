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
#include <QTimer>
QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class Tank : public QWidget
{
    Q_OBJECT

public:
    int control_mode;
    int idx;
    int type;//
    int move_direction;
    int bulletnum;//记录子弹的数量
    int tankx;int tanky; //标记坦克的像素位置
    int maptankx1;int maptanky1; //标记坦克的地图位置
    int maptankx2;int maptanky2; //标记坦克的地图位置
    int maptankx3;int maptanky3; //标记坦克的地图位置
    int maptankx4;int maptanky4; //标记坦克的地图位置
    int startedmup;int startedmdo;
    int startedmle;int startedmri;
    int moveforward;int moveback;
    void updatestarted();
    QTimer *movetimer;
    QLabel *tank_img;
    Bullet bugdet[5];
    QPixmap TANK;
    Tank(int init_tank_x,int init_tank_y,QWidget *parent = nullptr);
    void showtank(QWidget *pa);//生成坦克
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void MOVE(QKeyEvent *event);//坦克的移动
    void MOVE_control2(QKeyEvent *event);
    void shoot_control2(QKeyEvent *event);
    bool irremovable();   //检查坦克是否可以移动
    void shoot(QKeyEvent *event);       //坦克的射击
    void updatemapsit();
    void Deletebullets();
    int my_tank_live;
    int my_tank_speed;//坦克速度，越小越快

    //
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void check_get_prop();
    //道具属性
    void addLife(int lifenumber);
    void shield();
    void attack();
    void speedUp();
signals:
    void my_tank_shoot();
    void my_tank_move(int x,int y);
    void get_prop(int id);
};
#endif // WIDGET_H
