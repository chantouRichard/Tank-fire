#ifndef FROSTENEMY1_H
#define FROSTENEMY1_H

#include <QObject>
#include"enemytank.h"
#include"frostbullet1.h"
class frostenemy1 : public EnemyTank
{
    Q_OBJECT
public:
    explicit  frostenemy1(int startX, int startY, Tank*& playerTank,QWidget* parent=NULL);
    void showTank(QWidget*pa);

    frostbullet fbullets[5];
    void shoot();
    void startshoottime();

private slots:
    void updatePosition();
    void resumeMovement();
signals:

};

#endif // FROSTENEMY1_H
