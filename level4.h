#ifndef LEVEL4_H
#define LEVEL4_H

#include"level.h"
#include "firetank1.h"
class level4 : public Level
{
    Q_OBJECT
public:
    QTimer * ChangeMapTimer;
    QTimer *changeTimer;
    QLabel *timeLabel;
    QLabel *scoreLabel;
    QTimer *timer;
    int gameTime;
    int gameScore;
    int Wave;
    frostenemy1 *frosttank;
    firetank *fire_tank;
    void Deletetank() override;
    void clear_enemytank(int id) override;
    void ChangeMapWall();
    void InitChangeMapTimer();
    void DeleteChangeMapTimer();
    explicit level4(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void Initmap();
    void initTank(int enemy_num, int *enemysx, int *enemysy, int my_tankx, int my_tanky) override;
    void initEnemyTank(int enemy_num) override;
    void hide_all_tank() override;
    void updateenemysit() override;

private:
};
#endif // LEVEL4_H
