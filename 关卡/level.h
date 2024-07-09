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
    void loadMap(int newMap[Mapx_size][Mapy_size]); // 加载地图
    virtual void initTank(int enemy_num,int *enemysx,int *enemysy,int my_tankx,int my_tanky);
    virtual void initEnemyTank(int enemy_num);
    virtual void dead();
    explicit Level(QWidget *parent = nullptr);
    virtual void updatemapforboom(int mapx,int mapy);
    virtual ~Level();
    virtual void paintEvent(QPaintEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    virtual void setupUI(); // 初始化UI组件
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

    QLabel *passPage=new QLabel(this);
    QLabel *failPage=new QLabel(this);
    QLabel *ST1=new QLabel(passPage);
    QLabel *ST2=new QLabel(passPage);
    QLabel *ST3=new QLabel(passPage);
    QPixmap star1;
    QPixmap star2;
    QPixmap pixWall1;
    QPixmap pixWall2;
    QPixmap pixtool1;QPixmap pixColumnTool1;
    QPixmap pixtool2;QPixmap pixColumnTool2;
    QPixmap pixtool3;QPixmap pixColumnTool3;
    QPixmap pixtool4;QPixmap pixColumnTool4;
    int PropType[3];
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
    //
    void resetTime();
    void initColumn(QLabel* statusBar,QLabel* statusText);
    void grade();
    //add
    void changeRandomZeroToOne();
    QTimer *changeTimer;
    void initchangeTimer();
    void DeletechangTimer();
private slots:
    void onTimeout();
signals:
    void Win();
    void back();
    void backButWin();
    void Replay();
public slots:
    void updateTime(QLabel* statusText);
    void passPageShow();
    void failPageShow();
    void deletePassPage();
    void deleteFailPage();
    //获取道具信息
    void HandleGetProp(int id);
    void HandleKey(int id);

};

#endif // LEVEL_H
