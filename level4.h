#ifndef level4_H
#define level4_H

#include "mainlevel.h"
#include <QWidget>

namespace Ui {
class level4;
}

class level4 : public mainlevel {
    Q_OBJECT

public:
    explicit level4(QWidget *parent = nullptr);
    ~level4();
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::level4 *ui;

    void initTank() override;
    void initEnemyTank() override;
    void dead() override;
};

#endif // level4_H
