#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <vector>
#include <QPaintEvent>
#include <QWidget>
#include "global.h"
#include "tank.h"
#include <QLabel>
#include <QVector>
#include <QQueue>
#include "enemybullet.h"

struct Box
{
    int x; // x 坐标
    int y; // y 坐标
    Box* pre; // 指向前一个 Box 的指针
    Box(int x, int y, Box* pre = nullptr); // 盒子的构造函数
};

class EnemyTank : public QWidget {
    Q_OBJECT

public:
    QTimer* moveTimer; // 移动方向判断间隔
    QTimer* pauseTimer; // 敌人坦克暂停时间
    QTimer* shootTimer; // 发射子弹间隔
    int idx; // 子弹序号
    int type; // 和angle都标志方向
    int currentX, currentY; // 当前x和y坐标
    int map_enemy_tankx1; // 标记坦克的地图位置
    int map_enemy_tanky1; // 标记坦克的地图位置
    int map_enemy_tankx2; // 标记坦克的地图位置
    int map_enemy_tanky2; // 标记坦克的地图位置
    int map_enemy_tankx3; // 标记坦克的地图位置
    int map_enemy_tanky3; // 标记坦克的地图位置
    int map_enemy_tankx4; // 标记坦克的地图位置
    int map_enemy_tanky4; // 标记坦克的地图位置
    int angle; // 坦克的角度
    bool isPaused; // 坦克是否暂停
    bool live; // 坦克是否存活
    enemybullet bullets[5]; // 记录敌方子弹夹
    QLabel *enemy_tank_img = NULL; // 敌人坦克图片标签
    QPixmap Enemy_Tank; // 敌人坦克图片
    int moveCounter; // 移动计数器
    int enemytank_style; // 敌人坦克样式
    int enemy_HP; // 敌人坦克生命值
    const int maxMoveSteps = 12; // 坦克在同一方向上移动的最大步数
    Tank* playerTank; // 玩家坦克指针

    // 构造函数
    EnemyTank(int startX, int startY, Tank*& playerTank, QWidget* parent = nullptr);
    // 改变方向函数
    void changeDirection(int angle);
    // 设置敌人地图
    void setEnemyMap(int map[25][25]);
    // 检查坦克是否可以移动
    bool irremovable();
    // 选择新方向
    void chooseNewDirection();
    // 更新地图位置
    void updatemapsit();
    // 更智能地选择新方向
    void chooseNewDirection_smarter();
    // 显示坦克
    void showTank(QWidget* pa);
    // 获取方向的广度优先搜索
    void getDire_BFS(int sx, int sy, int ex, int ey, QVector<QVector<bool>>& visited);
    // 射击
    void shoot();
    // 开始射击计时
    void startshoottime(int w);
    // 删除子弹
    void Deletebullets();

private slots:
    // 更新位置
    void updatePosition();
    // 随机移动
    void resumeMovement();

signals:
    // 敌人移动信号
    void enemy_move();
};

#endif // ENEMYTANK_H
