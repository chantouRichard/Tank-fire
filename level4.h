#ifndef LEVEL4_H
#define LEVEL4_H

#include"level.h"

class level4 : public Level
{
    Q_OBJECT
public:
    QTimer *changeTimer;
    explicit level4(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent* event);
    void Initmap();
    QLabel *timeLabel;
    QLabel *scoreLabel;
    QTimer *timer;
    int gameTime;
    int gameScore;
private:
    void dead() override;
};
#endif // LEVEL4_H
