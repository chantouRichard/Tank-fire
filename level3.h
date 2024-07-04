#ifndef LEVEL3_H
#define LEVEL3_H

#include "mainlevel.h"
#include <QWidget>

namespace Ui {
class level3;
}

class level3 : public mainlevel {
    Q_OBJECT

public:
    explicit level3(QWidget *parent = nullptr);
    ~level3();
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::level3 *ui;

    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};

#endif // LEVEL3_H
