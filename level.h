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
    int passwindowshown;
    void loadMap(const int newMap[Mapy_size][Mapx_size]); // 加载地图
    void initTank(int enemy_num,int *enemysx,int *enemysy,int my_tankx,int my_tanky);//初始化我的坦克和我的子弹
    void initEnemyTank(int enemy_num);          //初始化敌人和敌人子弹
    explicit Level(QWidget *parent = nullptr);
    virtual void updatemapforboom(int mapx,int mapy);//子弹爆炸后更新地图
    virtual ~Level();
    virtual void paintEvent(QPaintEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;//让我的子弹获取按键信息
    void Deletetank();
    void updateenemysit();
    void clear_enemytank(int id);
    void hide_all_tank();
    //
    QDateTime startTime;
    QTimer* timer;
    QHBoxLayout *layout;// 创建布局
    QLabel *statusBar;
    QLabel *statusText;
    //道具栏
    QLabel *statusProp;
    QLabel *Prop1;
    QLabel *Prop2;
    QLabel *Prop3;
    QLabel *Prop4;

    QLabel *PageText;
    QLabel *PageText2;

    QLabel *passPage=new QLabel(this);
    QLabel *failPage=new QLabel(this);
    QLabel *ST1=new QLabel(passPage);
    QLabel *ST2=new QLabel(passPage);
    QLabel *ST3=new QLabel(passPage);
    QPixmap star1;
    QPixmap star2;
    QPixmap pixWall;
    QPixmap pixtool1;QPixmap pixColumnTool1;
    QPixmap pixtool2;QPixmap pixColumnTool2;
    QPixmap pixtool3;QPixmap pixColumnTool3;
    QPixmap pixtool4;QPixmap pixColumnTool4;
    int PropType[4];
    int GetColumnIndex();
    //任务栏信息
    int score;
    int passTime=0;
    QPushButton *next;
    QPushButton *backbutton;
    QPushButton *passButton;
    QPushButton *failButton;
    QPushButton *backButWinbutton;
    QPushButton *replay;
    void resetTime();
    void initColumn(QLabel* statusBar,QLabel* statusText);
    void grade();
    void changeRandomZeroToOne();
    QTimer *changeTimer;
    void initchangeTimer();
    void DeletechangTimer();
    void onTimeout();
signals:
    void Win();
    void back();
    void backButWin();
    void Replay();
    void pass_fail();
    void pass_victory();
public slots:
    void updateTime();
    void passPageShow();
    void failPageShow();
    void deletePassPage();
    void deleteFailPage();
    //获取道具信息
    void HandleGetProp(int id);
    void HandleKey(int id);
    void HideProp();
};

#endif // LEVEL_H
