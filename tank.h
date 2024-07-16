#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QTransform>
#include <QVector>
#include "bullet.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class Tank : public QWidget
{
    Q_OBJECT

public:
    // 构造函数
    Tank(int init_tank_x, int init_tank_y, QWidget *parent = nullptr);

    // 锁定标志
    bool locked = false;
    // 子弹索引
    int idx;
    // 坦克方向
    int type;
    // 子弹数量
    int bulletnum;
    // 控制模式
    int control_mode;
    // 移动方向
    int move_direction;
    // 前进和后退标志
    int moveforward;
    int moveback;

    // 坦克像素位置
    int tankx;
    int tanky;
    // 坦克地图位置
    int maptankx1;
    int maptanky1;
    int maptankx2;
    int maptanky2;
    int maptankx3;
    int maptanky3;
    int maptankx4;
    int maptanky4;
    // 移动状态标志
    int startedmup;
    int startedmdo;
    int startedmle;
    int startedmri;

    // 坦克图像标签
    QLabel *tank_img;
    // 子弹数组
    Bullet bugdet[5];
    // 坦克图像
    QPixmap TANK;

    // 显示坦克
    void showtank(QWidget *pa);
    // 按键按下事件
    void keyPressEvent(QKeyEvent *event) override;
    // 按键释放事件
    void keyReleaseEvent(QKeyEvent *event) override;
    // 坦克移动
    void MOVE(QKeyEvent *event);
    // 检查坦克是否可以移动
    bool irremovable();
    // 坦克射击
    void shoot(QKeyEvent *event);
    // 更新地图位置
    void updatemapsit();
    // 删除子弹
    void Deletebullets();
    // 控制模式2的移动
    void MOVE_control2(QKeyEvent *event);
    // 控制模式2的射击
    void shoot_control2(QKeyEvent *event);

    // 坦克生命值
    int my_tank_live;
    // 坦克速度（值越小越快）
    int my_tank_speed;
    // 启动射击计时器
    void startshoottime();
    // 射击计时器
    QTimer* shoottimer;
    // 攻击力
    int attackforce;

    // 状态标志
    bool isSpeedingUp = false;
    bool isAttackUp = false;
    bool isShieldUp = false;
    bool isSpeedingDown = false;

    // 临时计时器
    QTimer *tempTimer1 = nullptr;
    QTimer *tempTimer2 = nullptr;
    QTimer *tempAttack = nullptr;
    QTimer *tempShield = nullptr;

    // 更新移动状态
    void updatestarted();

    // 移动定时器
    QTimer *movetimer;

    // 坦克移动函数
    void move_up();
    void move_down();
    void move_left();
    void move_right();

    // 检查是否获得道具
    bool check_get_prop();

    // 道具属性函数
    void addLife(int lifenumber);
    void shield();
    void attack();
    void speedUp();
    void speedDown();

signals:
    void my_tank_shoot();
    void my_tank_move(int x, int y);
    void get_prop(int id);
    void use_prop(int index);
    void hurt();

public slots:
};

#endif // WIDGET_H
