#ifndef LEVEL1_H
#define LEVEL1_H

#include "level.h"

class level1 : public Level {
    Q_OBJECT

public:
    explicit level1(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
private:
    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};

#endif // LEVEL1_H
