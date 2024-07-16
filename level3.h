#ifndef LEVEL3_H
#define LEVEL3_H

#include "level.h"

class level3 : public Level
{
    Q_OBJECT
public:
    // 改变地图的计时器
    QTimer *changeTimer;
    // 构造函数
    explicit level3(QWidget *parent = nullptr);
    // 绘制事件
    void paintEvent(QPaintEvent *event) override;
    // 处理按键按下事件
    void keyPressEvent(QKeyEvent* event);
    // 删除坦克
    void Deletetank() override;
    // 隐藏所有坦克
    void hide_all_tank() override;
    // 初始化我的坦克和我的子弹
    void initTank(int enemy_num, int *enemysx, int *enemysy, int *styles, int my_tankx, int my_tanky) override;
    // 初始化敌人和敌人子弹
    void initEnemyTank(int enemy_num) override;
    // 更新敌人位置
    void updateenemysit() override;
    // 初始化地图
    void Initmap();
    // 清除敌人坦克
    void clear_enemytank(int id) override;

    // 显示时间的标签
    QLabel *timeLabel;
    // 显示分数的标签
    QLabel *scoreLabel;
    // 计时器
    QTimer *timer;
    // 游戏时间
    int gameTime;
    // 游戏分数
    int gameScore;

    // 冰冻敌人坦克
    frostenemy1 *frosttank;

private:

};

#endif // LEVEL3_H
