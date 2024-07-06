#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"
#include <QWidget>

namespace Ui {
class level2;
}

class level2 : public Level {
    Q_OBJECT

public:
    EnemyTank* enemy1=NULL;
    EnemyTank* enemy2=NULL;
    EnemyTank* enemy3=NULL;
    explicit level2(QWidget *parent = nullptr);
    ~level2();
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
    Ui::level2 *ui;

    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};

#endif // LEVEL2_H
