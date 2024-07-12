#ifndef LEVEL1_H
#define LEVEL1_H
#include"global.h"
#include "level.h"
#include<QKeyEvent>
class level1 : public Level {
    Q_OBJECT

public:
    explicit level1(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent* event)override;
    void paintEvent(QPaintEvent *event) override;
    void Initmap();

    //
    QLabel *timeLabel;
    QLabel *Label1;
    QLabel *Label2;
    QLabel *Label3;
    QLabel *Label4;
    QLabel *Label5;

    QPixmap pixWall0;
    QPixmap pixWall1;
    QPixmap pixWall2;
    QPixmap p1;
    QPixmap p2;

    QLabel *scoreLabel;
    QTimer *timer;
    int gameTime;
    int gameScore;
private:
    void dead() override;
};

#endif // LEVEL1_H
