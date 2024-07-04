#ifndef LEVEL2_H
#define LEVEL2_H

#include "mainlevel.h"
#include <QWidget>

namespace Ui {
class level2;
}

class level2 : public mainlevel {
    Q_OBJECT

public:
    explicit level2(QWidget *parent = nullptr);
    ~level2();
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::level2 *ui;

    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};

#endif // LEVEL2_H
