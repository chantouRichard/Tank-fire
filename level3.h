#ifndef LEVEL3_H
#define LEVEL3_H

#include"level.h"

class level3 : public Level
{
    Q_OBJECT
public:
    explicit level3(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

private:

    void initTank() override;
    void initEnemyTank() override;
    void dead() override;

};

#endif // LEVEL3_H
