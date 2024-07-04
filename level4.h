#ifndef LEVEL4_H
#define LEVEL4_H

#include <QWidget>

namespace Ui {
class level4;
}

class level4 : public QWidget
{
    Q_OBJECT

public:
    explicit level4(QWidget *parent = nullptr);
    ~level4();
    void paintEvent(QPaintEvent *event) override;
signals:
    void Win();
    void back();
private:
    Ui::level4 *ui;

    bool Pass=false;//判断是否通过该关卡
    bool mainTankIsDead=false;
    void initTank();
    void initEnemyTank();
    void dead();


};

#endif // LEVEL4_H
