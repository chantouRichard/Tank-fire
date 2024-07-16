#ifndef LEVEL3_H
#define LEVEL3_H

#include"level.h"

class level3 : public Level
{
    Q_OBJECT
public:
    QTimer *changeTimer;
    explicit level3(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent* event);
    void Deletetank() override;
    void hide_all_tank() override;
    void initTank(int enemy_num,int *enemysx,int *enemysy,int my_tankx,int my_tanky) override;//初始化我的坦克和我的子弹
    void initEnemyTank(int enemy_num) override;          //初始化敌人和敌人子弹
    void updateenemysit() override;
    void Initmap();
    void clear_enemytank(int id) override;
    QLabel *timeLabel;
    QLabel *scoreLabel;
    QTimer *timer;
    int gameTime;
    int gameScore;

    frostenemy1 *frosttank;
private:

};

#endif // LEVEL3_H
