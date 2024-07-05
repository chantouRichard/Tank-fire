#include "enemybullet.h"

enemybullet::enemybullet(QWidget *parent) : Bullet(parent)
{
    BULA=new QLabel;
    BOOM=new QLabel;
    bigBOOM=new QLabel;

    BULL.load(":/2/Res/res2/tree.png");
    Boom.load(":/1/Res/res/blast2.gif");
    Bigboom.load(":/1/Res/res/blast4.gif");

    BULA->setPixmap(BULL);
    BULA->setParent(parent);
    BOOM->setPixmap(Boom);
    bigBOOM->setPixmap(Bigboom);

    bullettimer=new QTimer(this);
    boomtimer=new QTimer(this);
    bigboomtimer=new QTimer(this);
    bullettimer->start(10);
    started=false;
}

void enemybullet::bulletboom(int boomsitx, int boomsity) {
    BULA->hide();
    Disconnected();
    boomtimer->start(150);
    BOOM->setParent(BULA->parentWidget());
    bigBOOM->setParent(BULA->parentWidget());
    BOOM->move(boomsitx,boomsity);
    BOOM->show();
    connect(boomtimer,&QTimer::timeout,[&](){
        BOOM->hide();
        bigboomtimer->start(350);
        bigBOOM->setParent(BULA->parentWidget());
        bigBOOM->move(60*boommapsitx-30,60*boommapsity-20);
        bigBOOM->show();
        connect(bigboomtimer,&QTimer::timeout,[&](){
            bigBOOM->hide();
            bigboomtimer->stop();
            bigboomtimer->disconnect();
        });
        boomtimer->stop();
        boomtimer->disconnect();
    });

}

//void enemybullet::set_parent(EnemyTank *parent)
//{
//    this->parent=parent;
//}


