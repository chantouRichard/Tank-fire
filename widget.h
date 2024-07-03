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

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    ~Widget();
    Bullet bugdet[ 5];
    void keyPressEvent(QKeyEvent *event) override;
    QLabel *bul=new QLabel();
    void MOVE(QKeyEvent *event,int x,int y);//坦克的移动
    bool checkmovement(QKeyEvent *event);   //检查坦克是否可以移动
    void shoot(QKeyEvent *event);       //坦克的射击
    int tankx;int tanky; //标记坦克的位置
    QPixmap BUL;
    int idx;
    int type;//记录坦克方向
    int bulletnum;//记录子弹的数量

private:

};
#endif // WIDGET_H
