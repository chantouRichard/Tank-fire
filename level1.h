#ifndef LEVEL1_H
#define LEVEL1_H

#include "mainlevel.h"
#include <QWidget>

namespace Ui {
class level1;
}

class level1 : public mainlevel {
    Q_OBJECT

public:
    explicit level1(QWidget *parent = nullptr);
    ~level1();
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::level1 *ui;

    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};

#endif // LEVEL1_H
