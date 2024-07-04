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
    Tank(QWidget *parent = nullptr);
    ~Tank();
    Bullet bugdet[18];
    int MAP[25][25];//导入所在的地图
    void Loadmap(int map[25][25]);
    void showtank(QWidget *pa);//生成坦克
    void keyPressEvent(QKeyEvent *event) override;
    QLabel *bul=new QLabel();
    void MOVE(QKeyEvent *event,int x,int y);//坦克的移动
    bool checkmovement();   //检查坦克是否可以移动
    void shoot(QKeyEvent *event);       //坦克的射击
    int tankx;int tanky; //标记坦克的像素位置
    int maptankx1;int maptanky1; //标记坦克的地图位置
    int maptankx2;int maptanky2; //标记坦克的地图位置
    int maptankx3;int maptanky3; //标记坦克的地图位置
    int maptankx4;int maptanky4; //标记坦克的地图位置
    QPixmap BUL;
    int idx;
    int type;//记录坦克方向
    int bulletnum;//记录子弹的数量
    void addbudget();//填充子弹（将子弹设为当前地图）
    void updatemapsit();
private:

};
#endif // WIDGET_H
