#include "bullet.h"

Bullet::Bullet(QWidget *parent) : QWidget(parent)
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

void Bullet::Loadmap(int map[25][25]){
    for(int i=0;i<25;i++){
        for(int j=0;j<25;j++){
            MAP[i][j]=map[i][j];
        }
    }
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
    if(!checkmovebullet())
    {
        buy=buy-5;
        updatemapsit();
        BULA->move(bux,buy);
    }
}

void Bullet::movedown(){
    if(!checkmovebullet()){
        buy=buy+5;
        updatemapsit();
        BULA->move(bux,buy);
    }
}

void Bullet::moveleft(){
    if(!checkmovebullet()){
        bux=bux-5;
        updatemapsit();
        BULA->move(bux,buy);
    }
}

void Bullet::moveright(){
    if(!checkmovebullet()){
        bux=bux+5;
        updatemapsit();
        BULA->move(bux,buy);
    }
}

void Bullet::movebullet(QWidget* parent,int style,int x,int y){
    //发射子弹的移动
    type=style;
    bux=x;buy=y;
    updatemapsit();

    if(type==1&&started==0){
        started=1;
        bux+=25;buy=buy-10;
        updatemapsit();
        BULA->setParent(parent);
        BULA->move(bux,buy);
        BULA->show();
        connect(bullettimer,&QTimer::timeout,this,&Bullet::moveup);
    }
    if(type==2&&started==0){
        started=1;
        bux+=25;buy+=55;
        updatemapsit();
        BULA->move(bux,buy);
        BULA->setParent(parent);
        BULA->show();
        connect(bullettimer,&QTimer::timeout,this,&Bullet::movedown);
    }
    if(type==3&&started==0){
        started=1;
        bux=bux-5;buy+=22;
        updatemapsit();
        BULA->move(bux,buy);
        BULA->setParent(parent);
        BULA->show();

        connect(bullettimer,&QTimer::timeout,this,&Bullet::moveleft);
    }
    if(type==4&&started==0){
        started=1;
        bux+=55;buy+=25;
        updatemapsit();
        BULA->move(bux,buy);
        BULA->setParent(parent);
        BULA->show();

        connect(bullettimer,&QTimer::timeout,this,&Bullet::moveright);
    }
}

bool Bullet::checkmovebullet(){

    if(type==1){
        if(MAP[mapbux][mapbuy]!=0)
        {
            boommapsitx=mapbux;
            boommapsity=mapbuy;
            bulletboom(bux-50,buy-50);
            emit boom(mapbux,mapbuy);
            return true;
        }
        if(!MAP[mapbux][mapbuy-1]){
            return false;
        }
        else{
            if(buy>60*mapbuy)
                return false;
            else{
                boommapsitx=mapbux;
                boommapsity=mapbuy-1;
                bulletboom(bux-50,buy-50);
                emit boom(mapbux,mapbuy-1);
                return true;
            }
        }
    }
    if(type==2){
        if(!MAP[mapbux][mapbuy+1]){
            return false;
        }
        else{
            if(buy+5<60*(mapbuy+1)){
                return false;
            }
            else{
                boommapsitx=mapbux;
                boommapsity=mapbuy+1;
                bulletboom(bux-50,buy-50);
                emit boom(mapbux,mapbuy+1);
                return true;
            }}
    }
    if(type==3){
        if(MAP[mapbux][mapbuy]!=0){
            boommapsitx=mapbux;
            boommapsity=mapbuy;
            bulletboom(bux-50,buy-50);
            emit boom(mapbux,mapbuy);
            return true;
        }
        if( !MAP[mapbux-1][mapbuy])
            return false;
        else{
            if(bux>60*mapbux)
                return false;
            else{
                boommapsitx=mapbux-1;
                boommapsity=mapbuy;
                bulletboom(bux-50,buy-50);
                emit boom(mapbux-1,mapbuy);
                return true;
            }
        }
    }
    if(type==4){
        if(! MAP[mapbux+1][mapbuy])
            return false;
        else{
            if(bux+5<60*(mapbux+1)){
                return false;
            }
            else{
                boommapsitx=mapbux+1;
                boommapsity=mapbuy;
                bulletboom(bux-50,buy-50);
                emit boom(mapbux+1,mapbuy);
                return true;
            }
        }
    }
}
//检查子弹是否可以继续移动
void Bullet::updatemapsit(){
    mapbux=bux/60;
    mapbuy=buy/60;
}
bool Bullet::checkshootenemy(){
    if(bux>=enemyx&&bux<=(enemyx+60)&&buy>=enemyy&&bux<=(enemyx+60))
        return true;
    else
        return false;
}

void Bullet::bulletboom(int boomsitx,int boomsity){
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
