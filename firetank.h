#ifndef FROSTENEMY1_H
#define FROSTENEMY1_H

#include <QObject>
#include"enemytank.h"
#include"firebullet.h"
class firetank : public EnemyTank
{
    Q_OBJECT
public:
    explicit firetank(int startX, int startY, Tank*& playerTank,QWidget* parent=NULL);
    void showTank(QWidget*pa);

    firebullet fbullets[5];
    void shoot();
    void startshoottime();

private slots:
    void updatePosition();
    void resumeMovement();
signals:

};

#endif // FROSTENEMY1_H
