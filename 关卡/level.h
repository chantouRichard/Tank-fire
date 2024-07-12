#ifndef LEVEL_H
#define LEVEL_H
#include"tank.h"
#include"enemytank.h"
#include"enemybullet.h"
#include"bullet.h"
#include"global.h"
#include <QWidget>
#include<QPaintEvent>
#include<QDateTime>
#include<QPushButton>
#include<QLabel>
#include <QVector>
#include<QHBoxLayout>
class Level : public QWidget
{
    Q_OBJECT
public:
    bool show_failpage_show;
    int enemy_num;
    int* enemy_x_site;
    int* enemy_y_site;
    Tank* my_tank;

    EnemyTank** enemys;
    void loadMap(int newMap[Mapx_size][Mapy_size]); // 加载地图
    virtual void initTank(int enemy_num,int *enemysx,int *enemysy,int my_tankx,int my_tanky);
    virtual void initEnemyTank(int enemy_num);
    virtual void dead();
    explicit Level(QWidget *parent = nullptr);
    virtual void updatemapforboom(int mapx,int mapy);
    virtual ~Level();
    void keyReleaseEvent(QKeyEvent *event) override;
    virtual void setupUI(); // 初始化UI组件
    void Deletetank();
    void updateenemysit();
    void clear_enemytank(int id);
    //
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
    //
    void resetTime();
    void initColumn(QLabel* statusBar,QLabel* statusText);
    void grade();
signals:
    void Win();
    void back();
    void backButWin();
public slots:
    void updateTime(QLabel* statusText);
    void passPageShow();
    void failPageShow();
    void deletePassPage();
    void deleteFailPage();
    //实现暂停和继续游戏的函数

};

#endif // LEVEL_H
