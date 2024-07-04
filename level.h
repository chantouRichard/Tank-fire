#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>

class Level : public QWidget
{
    Q_OBJECT
public:
    explicit Level(QWidget *parent = nullptr);
    virtual ~Level();

    virtual void paintEvent(QPaintEvent *event) override;
    virtual void setupUI(); // 初始化UI组件

signals:
    void Win();
    void back();

protected:
    int map[14][20]; // 存储地图
    void loadMap(int newMap[14][20]); // 加载地图

    virtual void initTank();
    virtual void initEnemyTank();
    virtual void dead();
};

#endif // LEVEL_H
