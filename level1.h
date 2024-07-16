#ifndef LEVEL1_H
#define LEVEL1_H

#include "global.h"
#include "level.h"
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>

class level1 : public Level {
    Q_OBJECT

public:
    // 构造函数
    explicit level1(QWidget *parent = nullptr);
    // 处理按键按下事件
    void keyPressEvent(QKeyEvent* event) override;
    // 绘制事件
    void paintEvent(QPaintEvent *event) override;
    // 初始化地图
    void Initmap();

    // 显示时间的标签
    QLabel *timeLabel;
    // 显示分数的标签
    QLabel *scoreLabel;
    // 计时器
    QTimer *timer;
    // 改变计时器
    QTimer *changeTimer1;
    // 游戏时间
    int gameTime;
    // 游戏分数
    int gameScore;

};

#endif // LEVEL1_H
