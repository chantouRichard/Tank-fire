#ifndef LEVEL_H
#define LEVEL_H

#include "tank.h"
#include "enemytank.h"
#include "enemybullet.h"
#include "frostenemy1.h"
#include "firetank1.h"
#include "bullet.h"
#include "global.h"
#include <QWidget>
#include <QPaintEvent>
#include <QDateTime>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

class Level : public QWidget
{
    Q_OBJECT
public:
    // 显示下一个按钮
    bool ShowNextButton = true;
    // 显示失败页面标志
    bool show_failpage_show;
    // 敌人数量
    int enemy_num;
    // 敌人x坐标
    int* enemy_x_site;
    // 敌人y坐标
    int* enemy_y_site;
    // 敌人样式
    int* enemy_styles;
    // 我的坦克
    Tank* my_tank;
    // 敌人坦克数组
    EnemyTank** enemys;
    // 冰冻敌人坦克
    frostenemy1 *frosttank;
    // 通过窗口显示标志
    int passwindowshown;

    // 构造函数
    explicit Level(QWidget *parent = nullptr);
    // 析构函数
    ~Level();

    // 加载地图
    void loadMap(const int newMap[Mapy_size][Mapx_size]);
    // 初始化坦克和子弹
    virtual void initTank(int enemy_num, int *enemysx, int *enemysy, int *styles, int my_tankx, int my_tanky);
    // 初始化敌人和敌人子弹
    virtual void initEnemyTank(int enemy_num);
    // 子弹爆炸后更新地图
    virtual void updatemapforboom(int mapx, int mapy);
    // 子弹冻结后更新地图
    virtual void updatemapforfrosted(int mapx, int mapy);
    // 子弹燃烧后更新地图
    virtual void updatemapforfired(int mapx, int mapy);
    // 绘制事件
    virtual void paintEvent(QPaintEvent *event) override;
    // 处理按键释放事件
    void keyReleaseEvent(QKeyEvent *event) override;
    // 删除坦克
    virtual void Deletetank();
    // 更新敌人位置
    virtual void updateenemysit();
    // 清除敌人坦克
    virtual void clear_enemytank(int id);
    // 隐藏所有坦克
    virtual void hide_all_tank();

    // 计时器处理
    void resetTime();
    void initchangeTimer();
    void DeletechangTimer();
    void onTimeout();

    // 设置UI
    void setupUI();
    // 初始化列
    void initColumn(QLabel* statusBar, QLabel* statusText);
    // 评分
    void grade();
    // 将随机数0变为1
    void changeRandomZeroToOne();

    // 分数
    int score;
    // 游戏时间
    int passTime = 0;

    // 布局
    QHBoxLayout *layout;
    // 状态栏
    QLabel *statusBar;
    // 状态文本
    QLabel *statusText;
    // 道具栏
    QLabel *statusProp;
    QLabel *Prop1;
    QLabel *Prop2;
    QLabel *Prop3;
    QLabel *Prop4;
    // 页面文本
    QLabel *PageText;
    QLabel *PageText2;

    // 通过和失败页面
    QLabel *passPage = new QLabel(this);
    QLabel *failPage = new QLabel(this);
    QLabel *ST1 = new QLabel(passPage);
    QLabel *ST2 = new QLabel(passPage);
    QLabel *ST3 = new QLabel(passPage);
    // 星级图片
    QPixmap star1;
    QPixmap star2;
    // 墙壁图片
    QPixmap pixWall;
    // 工具图片
    QPixmap pixtool1;
    QPixmap pixColumnTool1;
    QPixmap pixtool2;
    QPixmap pixColumnTool2;
    QPixmap pixtool3;
    QPixmap pixColumnTool3;
    QPixmap pixtool4;
    QPixmap pixColumnTool4;
    QPixmap pixtool_frost;
    // 道具类型
    int PropType[4];
    // 获取列索引
    int GetColumnIndex();

    // 计时器
    QTimer* timer;
    QTimer* changeTimer;

    // 按钮
    QPushButton *next;
    QPushButton *backbutton;
    QPushButton *passButton;
    QPushButton *failButton;
    QPushButton *backButWinbutton;
    QPushButton *replay;

    // 开始时间
    QDateTime startTime;

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
    void HandleGetProp(int id);
    void HandleKey(int id);
    void HideProp();
};

#endif // LEVEL_H
