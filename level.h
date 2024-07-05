#ifndef LEVEL_H
#define LEVEL_H
#include"tank.h"
#include"enemytank.h"
#include"enemybullet.h"
#include"bullet.h"
#include"global.h"
#include <QWidget>
#include<QPaintEvent>

class Level : public QWidget
{
    Q_OBJECT
public:
    int enemy_num;
    int* enemy_x_site;
    int* enemy_y_site;
    Tank* my_tank;
    EnemyTank** enemys;
    void loadMap(int newMap[Mapx_size][Mapy_size]); // 加载地图
    virtual void initTank();
    virtual void initEnemyTank();
    virtual void dead();
    explicit Level(QWidget *parent = nullptr);
    virtual void updatemapforboom(int mapx,int mapy);
    virtual ~Level();
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void setupUI(); // 初始化UI组件

signals:
    void Win();
    void back();

protected:

};

#endif // LEVEL_H
