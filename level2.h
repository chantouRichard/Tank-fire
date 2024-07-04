#ifndef LEVEL2_H
#define LEVEL2_H

#include <QWidget>

namespace Ui {
class level2;
}

class level2 : public QWidget
{
    Q_OBJECT

public:
    explicit level2(QWidget *parent = nullptr);
    ~level2();
    void paintEvent(QPaintEvent *event) override;
signals:
    void Win();
    void back();
private:
    Ui::level2 *ui;

    bool Pass=false;//判断是否通过该关卡
    bool mainTankIsDead=false;
    void initTank();
    void initEnemyTank();
    void dead();


};

#endif // LEVEL1_H
