#ifndef LEVEL4_H
#define LEVEL4_H

#include"level.h"

class level4 : public Level
{
    Q_OBJECT
public:
    explicit level4(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent* event);
    void Initmap();
    QLabel *timeLabel;
    QLabel *scoreLabel;
    QTimer *timer;
    int gameTime;
    int gameScore;
    QPixmap p0;
    QPixmap p1;
    QPixmap p2;
    QPixmap p3;
    QPixmap p4;
    QPixmap p5;

    QLabel * b1;
    QLabel * b2;
    QLabel * b3;
    QLabel * b4;
    QLabel * b5;
private:
    void dead() override;
};
#endif // LEVEL4_H
