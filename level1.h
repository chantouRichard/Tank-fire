#ifndef LEVEL1_H
#define LEVEL1_H

#include "level.h"
#include<QKeyEvent>
class level1 : public Level {
    Q_OBJECT

public:
    explicit level1(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent *event) override;
private:
    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};

#endif // LEVEL1_H
