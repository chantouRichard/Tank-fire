#ifndef LEVEL1_H
#define LEVEL1_H

#include "level.h"
#include<QKeyEvent>
#include<QTimer>
#include<QDateTime>

class level1 : public Level {
    Q_OBJECT

public:
    EnemyTank* enemy1=NULL;
    EnemyTank* enemy2=NULL;
    EnemyTank* enemy3=NULL;
    explicit level1(QWidget *parent = nullptr);
    void updatemapforboom(int mapx, int mapy) override;
    void Initmap();
    void Deletetank();
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent *event) override;
    QLabel *timeLabel;
    QLabel *scoreLabel;
    QTimer *timer;
    int gameTime;
    int gameScore;

private:
    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};

#endif // LEVEL1_H
