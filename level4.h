#ifndef LEVEL4_H
#define LEVEL4_H

#include "level.h"
#include <QWidget>

namespace Ui {
class level4;
}

class level4 : public Level {
    Q_OBJECT

public:
    EnemyTank* enemy1=NULL;
    EnemyTank* enemy2=NULL;
    EnemyTank* enemy3=NULL;
    explicit level4(QWidget *parent = nullptr);
    ~level4();
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
    Ui::level4 *ui;

    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};

#endif // LEVEL4_H
