#ifndef MAINLEVEL_H
#define MAINLEVEL_H

#include <QWidget>

class mainlevel : public QWidget {
    Q_OBJECT

public:
    explicit mainlevel(QWidget *parent = nullptr);
    virtual ~mainlevel();

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

#endif // MAINLEVEL_H
