#ifndef LEVEL3_H
#define LEVEL3_H

#include "level.h"
#include <QWidget>

namespace Ui {
class level3;
}

class level3 : public Level {
    Q_OBJECT

public:
    EnemyTank* enemy1=NULL;
    EnemyTank* enemy2=NULL;
    EnemyTank* enemy3=NULL;
    explicit level3(QWidget *parent = nullptr);
    ~level3();
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
    Ui::level3 *ui;

    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};

#endif // LEVEL3_H
