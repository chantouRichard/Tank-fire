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
    QLabel *scoreLabel;
    QTimer *timer;
    QTimer *changeTimer1;
    int gameTime;
    int gameScore;
private:
    void dead() override;
};

#endif // LEVEL1_H
