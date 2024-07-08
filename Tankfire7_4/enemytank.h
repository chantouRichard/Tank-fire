#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <vector>
#include<QPaintEvent>
#include<QWidget>
#include"global.h"
#include"tank.h"
#include<QLabel>
#include<QVector>
#include<QQueue>
#include "enemybullet.h"

struct Box
{
    int x;int y;
    Box* pre;
    Box(int x,int y,Box* pre=nullptr);
};

class EnemyTank : public QWidget{
    Q_OBJECT

public:
    QTimer* moveTimer;  //移动方向判断间隔
    QTimer* pauseTimer; //敌人坦克暂停时间
    QTimer* shootTimer; //发射子弹间隔
    int idx;            //子弹序号
    int type;           //和angle都标志方向
    int currentX, currentY;
    int map_enemy_tankx1;int map_enemy_tanky1; //标记坦克的地图位置
    int map_enemy_tankx2;int map_enemy_tanky2; //标记坦克的地图位置
    int map_enemy_tankx3;int map_enemy_tanky3; //标记坦克的地图位置
    int map_enemy_tankx4;int map_enemy_tanky4; //标记坦克的地图位置
    int angle;
    bool isPaused;
    bool live;
    enemybullet bullets[5];//记录敌方子弹夹
    QLabel *enemy_tank_img=NULL;
    QPixmap Enemy_Tank;
    int moveCounter;
    const int maxMoveSteps = 24; // 坦克在同一方向上移动的最大步数
    Tank* playerTank;

    EnemyTank(int startX, int startY, Tank*& playerTank,QWidget* parent = nullptr);
    //改变方向函数
    void changeDirection(int angle);
    void setEnemyMap(int map[25][25]);
    //检查坦克是否可以移动
    bool irremovable();
    void chooseNewDirection();
    void updatemapsit();
    void chooseNewDirection_smarter();
    void showTank(QWidget*pa);
    void getDire_BFS(int sx,int sy,int ex,int ey,QVector<QVector<bool>>& visited);
    void shoot();
    void startshoottime();
    void Deletebullets();
private slots:
    void updatePosition();
    void resumeMovement();
signals:
    void enemy_move();
private:



};

#endif // ENEMYTANK_H
