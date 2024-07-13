#include "bullet.h"
#include"global.h"

Bullet::Bullet(QWidget *parent) : QWidget(parent)
{
    BULA=new QLabel;
    BOOM=new QLabel;
    boomvideo=new QMovie(BulletBoom_gif);

    BULL.load(bullet5_pic);

    BULL = BULL.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    BULA->setPixmap(BULL);
    BULA->setParent(parent);
    boomvideo->setScaledSize(QSize(60,60));
    BOOM->setMovie(boomvideo);
    bullettimer=new QTimer(this);
    boomtimer=new QTimer(this);
    bullettimer->start(12);
    started=false;
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
        BULA->move(bux,buy);
    }
}

void Bullet::movedown(){
    if(!checkmovebullet()){
        buy=buy+5;
        BULA->move(bux,buy);
    }
}

void Bullet::moveleft(){
    if(!checkmovebullet()){
        bux=bux-5;
        BULA->move(bux,buy);
    }
}

void Bullet::moveright(){
    if(!checkmovebullet()){
        bux=bux+5;
        BULA->move(bux,buy);
    }
}

void Bullet::movebullet(QWidget* parent,int style,int x,int y){
    //发射子弹的移动
    type=style;
    bux=x;buy=y;


    if(type==1&&started==0){
        started=1;
        bux+=16;buy=buy-15;////

        BULA->setParent(parent);
        BULA->move(bux,buy);
        BULA->show();
        connect(bullettimer,&QTimer::timeout,this,&Bullet::moveup);
    }
    if(type==2&&started==0){
        started=1;
        bux+=15;buy+=55;////

        BULA->move(bux,buy);
        BULA->setParent(parent);
        BULA->show();
        connect(bullettimer,&QTimer::timeout,this,&Bullet::movedown);
    }
    if(type==3&&started==0){
        started=1;
        bux=bux-15;buy+=17;////

        BULA->move(bux,buy);
        BULA->setParent(parent);
        BULA->show();

        connect(bullettimer,&QTimer::timeout,this,&Bullet::moveleft);
    }
    if(type==4&&started==0){
        started=1;
        bux+=55;buy+=15;////

        BULA->move(bux,buy);
        BULA->setParent(parent);
        BULA->show();

        connect(bullettimer,&QTimer::timeout,this,&Bullet::moveright);
    }
}

bool Bullet::checkmovebullet(){
    updatemapsit();
    if(checkshootenemy()){
        boommapsitx=mapbux;
        boommapsity=mapbuy;
        return true;
    }
    if(type==1){
        if(MAP_Global[mapbuy][mapbux]!=0&&MAP_Global[mapbuy][mapbux]!=3&&MAP_Global[mapbuy][mapbux]<=10)
        {
            boommapsitx=mapbux;
            boommapsity=mapbuy;
            bulletboom(60*boommapsitx,60*boommapsity);
            emit boom(mapbuy,mapbux);
            return true;
        }
        if(MAP_Global[mapbuy-1][mapbux]==0||MAP_Global[mapbuy-1][mapbux]==3||MAP_Global[mapbuy-1][mapbux]>10){
            return false;
        }
        else{
            if((buy+15)>60*mapbuy)
                return false;
            else{
                boommapsitx=mapbux;
                boommapsity=mapbuy-1;
                bulletboom(60*boommapsitx,60*boommapsity);
                emit boom(mapbuy-1,mapbux);
                return true;
            }
        }
    }
    if(type==2){
        if(MAP_Global[mapbuy][mapbux]!=0&&MAP_Global[mapbuy][mapbux]!=3&&MAP_Global[mapbuy][mapbux]<=10)
        {
            boommapsitx=mapbux;
            boommapsity=mapbuy;
            bulletboom(60*boommapsitx,60*boommapsity);
            emit boom(mapbuy,mapbux);
            return true;
        }
        if(MAP_Global[mapbuy+1][mapbux]==0||MAP_Global[mapbuy+1][mapbux]==3||MAP_Global[mapbuy+1][mapbux]>10){
            return false;
        }
        else{
            if((buy+15+5)<60*(mapbuy+1)){
                return false;
            }
            else{
                boommapsitx=mapbux;
                boommapsity=mapbuy+1;
                bulletboom(60*boommapsitx,60*boommapsity);
                emit boom(mapbuy+1,mapbux);
                return true;
            }}
    }
    if(type==3){
        if(MAP_Global[mapbuy][mapbux]!=0&&MAP_Global[mapbuy][mapbux]!=3&&MAP_Global[mapbuy][mapbux]<=10){
            boommapsitx=mapbux;
            boommapsity=mapbuy;
            bulletboom(60*boommapsitx,60*boommapsity);
            emit boom(mapbuy,mapbux);
            return true;
        }
        if( MAP_Global[mapbuy][mapbux-1]==0||MAP_Global[mapbuy][mapbux-1]==3||MAP_Global[mapbuy][mapbux-1]>10)
            return false;
        else{
            if((bux+15)>60*mapbux)
                return false;
            else{
                boommapsitx=mapbux-1;
                boommapsity=mapbuy;
                bulletboom(60*boommapsitx,60*boommapsity);
                emit boom(mapbuy,mapbux-1);
                return true;
            }
        }
    }
    if(type==4){
        if(MAP_Global[mapbuy][mapbux]!=0&&MAP_Global[mapbuy][mapbux]!=3&&MAP_Global[mapbuy][mapbux]<=10)
        {
            boommapsitx=mapbux;
            boommapsity=mapbuy;
            bulletboom(60*boommapsitx,60*boommapsity);
            emit boom(mapbuy,mapbux);
            return true;
        }
        if(MAP_Global[mapbuy][mapbux+1]==0||MAP_Global[mapbuy][mapbux+1]==3||MAP_Global[mapbuy][mapbux+1]>10)
            return false;
        else{
            if((bux+15+5)<60*(mapbux+1)){
                return false;
            }
            else{
                boommapsitx=mapbux+1;
                boommapsity=mapbuy;
                bulletboom(60*boommapsitx,60*boommapsity);
                emit boom(mapbuy,mapbux+1);
                return true;
            }
        }
    }
}

//检查子弹是否可以继续移动
bool Bullet::checkshootenemy(){
    for(int i=0;i<enemy_num;i++){
        if((bux+15)>=enemyx[i]&&(bux+15)<=(enemyx[i]+60)&&(buy+15)>=enemyy[i]&&(buy+15)<=(enemyy[i]+60)){
            bulletboom(enemyx[i],enemyy[i]);
            emit kill_enemy(i);
            return true;
        }
    }
    return false;
}

void Bullet::bulletboom(int boomsitx,int boomsity){
    BULA->hide();
    Disconnected();
    boomtimer->start(400);
    BOOM->setParent(BULA->parentWidget());

    BOOM->move(boomsitx,boomsity);
    boomvideo->start();
    boomvideo->setSpeed(400);
    BOOM->show();
    connect(boomtimer,&QTimer::timeout,[&](){
        boomvideo->stop();
        BOOM->hide();
        boomtimer->stop();
        boomtimer->disconnect();
    });
}
void Bullet::getenemysit(int*& x, int*& y){
    enemyx=x;
    enemyy=y;
}

void Bullet::updatemapsit(){
    mapbux=(bux+15)/60;
    mapbuy=(buy+15)/60;
}
