#ifndef LEVEL_H
#define LEVEL_H

#include"tank.h"
#include"enemytank.h"
#include"global.h"
#include <QWidget>
#include<QPaintEvent>
#include<QDateTime>
#include<QPushButton>
#include<QHBoxLayout>

class Level : public QWidget
{
    Q_OBJECT
public:
    Tank* my_tank;

    int map[Mapx_size][Mapy_size]; // 存储地图
    void loadMap(int newMap[Mapx_size][Mapy_size]); // 加载地图
    void resetTime();
    virtual void initTank();
    virtual void initEnemyTank();
    virtual void dead();
    explicit Level(QWidget *parent = nullptr);
    virtual ~Level();
    virtual void updatemapforboom(int mapx,int mapy);
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void setupUI(); // 初始化UI组件
    void initColumn(QLabel* statusBar,QLabel* statusText);
    void grade();

    QDateTime startTime;
    QTimer* timer;
    QHBoxLayout *layout;// 创建布局
    QLabel *statusBar;
    QLabel *statusText;
    QLabel *passPage=new QLabel(this);
    QLabel *failPage=new QLabel(this);
    QLabel *ST1=new QLabel(passPage);
    QLabel *ST2=new QLabel(passPage);
    QLabel *ST3=new QLabel(passPage);
    QPixmap star1;
    QPixmap star2;
    //任务栏信息
    int score;
    int passTime=0;
    QPushButton *next;
    QPushButton *backbutton;
    QPushButton *passButton;
    QPushButton *failButton;
    QPushButton *backButWinbutton;
    QPushButton *replay;


public slots:
    void updateTime(QLabel* statusText);
    void passPageShow();
    void failPageShow();
    void deletePassPage();
    void deleteFailPage();
    //实现暂停和继续游戏的函数

signals:
    void Win();
    void back();
    void backButWin();

protected:


};

#endif // LEVEL_H
