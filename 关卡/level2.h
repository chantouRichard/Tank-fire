#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"

class level2 : public Level
{
    Q_OBJECT
public:
    explicit level2(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void Initmap();
    void keyPressEvent(QKeyEvent* event);
    QPixmap p0;
    QPixmap p1;
    QPixmap p2;
    QPixmap p3;

    QLabel * b1;
    QLabel * b2;
    QLabel * b3;
    QLabel * b4;


private:

    void dead() override;

};

#endif // LEVEL2_H
