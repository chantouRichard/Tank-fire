#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"

class level2 : public Level
{
    Q_OBJECT
public:
    // 构造函数
    explicit level2(QWidget *parent = nullptr);
    // 绘制事件
    void paintEvent(QPaintEvent *event) override;
    // 初始化地图
    void Initmap();
    // 处理按键按下事件
    void keyPressEvent(QKeyEvent* event);
    // 改变地图墙壁
    void ChangeMapWall();
    // 初始化改变地图计时器
    void InitChangeMapTimer();
    // 删除改变地图计时器
    void DeleteChangeMapTimer();

    // 改变地图的计时器
    QTimer *changeTimer;
    QTimer *ChangeMapTimer;

};

#endif // LEVEL2_H
