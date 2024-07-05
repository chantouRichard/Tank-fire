#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <vector>
#include<QPaintEvent>
#include<QWidget>
#include"global.h"
#include<QLabel>
#include"tank.h"

class EnemyTank : public QWidget, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    EnemyTank(int startX, int startY, QWidget* parent = nullptr);
    QTimer* moveTimer;
    QTimer* pauseTimer;
    int initEnemyMap[25][25];//定义敌方坦克的地图
    int currentX, currentY;


    int maptankx1;int maptanky1; //标记坦克的地图位置
    int maptankx2;int maptanky2; //标记坦克的地图位置
    int maptankx3;int maptanky3; //标记坦克的地图位置
    int maptankx4;int maptanky4; //标记坦克的地图位置

    QLabel *tank_img=NULL;
    QPixmap TANK;
    //改变方向函数
    void changeDirection(int angle);
    int angle;
    bool isPaused;
    std::vector<std::vector<int>> grid;
    void setEnemyMap(int map[25][25]);
    void Loadmap(int map[25][25]);
    int MAP[Mapx_size][Mapy_size];

    int moveCounter=0;
    const int maxMoveSteps = 80; // 坦克在同一方向上移动的最大步数

    bool irremovable();   //检查坦克是否可以移动

    void chooseNewDirection();
    void updatemapsit();
    void showTank(QWidget*pa);
private slots:
    void updatePosition();
    void resumeMovement();

private:



};

#endif // ENEMYTANK_H
