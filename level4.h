#ifndef LEVEL4_H
#define LEVEL4_H

#include"level.h"

class level4 : public Level
{
    Q_OBJECT
public:
    explicit level4(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

private:

    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};
#endif // LEVEL4_H
