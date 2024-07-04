#ifndef LEVEL1_H
#define LEVEL1_H

#include <QWidget>

namespace Ui {
class level1;
}

class level1 : public QWidget
{
    Q_OBJECT

public:
    explicit level1(QWidget *parent = nullptr);
    ~level1();
    void paintEvent(QPaintEvent *event) override;
signals:
    void Win();
    void back();
private:
    Ui::level1 *ui;

    bool Pass=false;//判断是否通过该关卡
    bool mainTankIsDead=false;
    void initTank();
    void initEnemyTank();
    void dead();


};

#endif // LEVEL1_H
