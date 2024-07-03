#include "bullet.h"

Bullet::Bullet(QWidget *parent) : QWidget(parent)
{
    BULL.load("D:/PICC/Res/res2/tree.png");
    BULA->setPixmap(BULL);
    BULA->setParent(parent);
    bullettimer=new QTimer(this);
    bullettimer->start(100);
    bux=100;buy=100;
    type=1;started=0;
}

void Bullet::Disconnected(){
if(type==1){
    disconnect(bullettimer,&QTimer::timeout,this,&Bullet::moveup);
    started=0;
}
if(type==2){
    disconnect(bullettimer,&QTimer::timeout,this,&Bullet::movedown);
    started=0;
}
if(type==3){
    disconnect(bullettimer,&QTimer::timeout,this,&Bullet::moveleft);
    started=0;
}
if(type==4){
    disconnect(bullettimer,&QTimer::timeout,this,&Bullet::moveright);
    started=0;
}
}
void Bullet::moveup(){
    buy=buy-5;
    BULA->move(bux,buy);
}
void Bullet::movedown(){
    buy=buy+5;
    BULA->move(bux,buy);
}
void Bullet::moveleft(){
    bux=bux-5;
    BULA->move(bux,buy);
}
void Bullet::moveright(){
    bux=bux+5;
    BULA->move(bux,buy);
}
void Bullet::movebullet(QWidget *parent,int style,int x,int y){
    //发射子弹的移动
    type=style;
  bux=x;buy=y;
if(type==1&&started==0){
    started=1;
bux+=50;buy+=50;
BULA->setParent(parent);
BULA->move(bux,buy);
BULA->show();
connect(bullettimer,&QTimer::timeout,this,&Bullet::moveup);
}
if(type==2&&started==0){
      started=1;
    bux+=50;buy+=50;
BULA->move(bux,buy);
BULA->setParent(parent);
BULA->show();
connect(bullettimer,&QTimer::timeout,this,&Bullet::movedown);
}
if(type==3&&started==0){
      started=1;
    bux+=50;buy+=50;
BULA->move(bux,buy);
BULA->setParent(parent);
BULA->show();

connect(bullettimer,&QTimer::timeout,this,&Bullet::moveleft);
}
if(type==4&&started==0){
      started=1;
    bux+=50;buy+=50;
BULA->move(bux,buy);
BULA->setParent(parent);
BULA->show();

connect(bullettimer,&QTimer::timeout,this,&Bullet::moveright);
}
}
void Bullet::checkmovebullet(int type){



}//检查子弹是否可以继续移动
