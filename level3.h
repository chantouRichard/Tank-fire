#ifndef LEVEL3_H
#define LEVEL3_H

#include <QWidget>

namespace Ui {
class level3;
}

class level3 : public QWidget
{
    Q_OBJECT

public:
    explicit level3(QWidget *parent = nullptr);
    ~level3();
    void paintEvent(QPaintEvent *event) override;
signals:
    void Win();
    void back();
private:
    Ui::level3 *ui;

    bool Pass=false;//判断是否通过该关卡
    bool mainTankIsDead=false;
    void initTank();
    void initEnemyTank();
    void dead();


};

#endif // LEVEL3_H
