#ifndef LEVEL_H
#define LEVEL_H
#include"tank.h"
#include"global.h"
#include"enemytank.h"
#include <QWidget>
#include<QPaintEvent>
class Level : public QWidget
{
    Q_OBJECT
public:
    Tank* my_tank;

    int map[Mapx_size][Mapy_size]; // 存储地图
    void loadMap(int newMap[Mapx_size][Mapy_size]); // 加载地图
    virtual void updatemapforboom(int mapx,int mapy);
    virtual void initTank();
    virtual void initEnemyTank();
    virtual void dead();
    explicit Level(QWidget *parent = nullptr);
    virtual ~Level();
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void setupUI(); // 初始化UI组件

signals:
    void Win();
    void back();

protected:

};

#endif // LEVEL_H
