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
    void Initmap();
    QLabel *timeLabel;
    QLabel *scoreLabel;
    QTimer *timer;
    int gameTime;
    int gameScore;
private:
    void dead() override;

};

#endif // LEVEL3_H
