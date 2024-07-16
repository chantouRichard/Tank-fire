#include "enemybullet.h"

enemybullet::enemybullet(QWidget *parent) : Bullet(parent)
{
    BULA=new QLabel;
    BOOM=new QLabel;
    boomvideo=new QMovie(BulletBoom_gif);
//    qDebug()<<"this parent down";
    BULL.load(bullet1_pic);

    BULL = BULL.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    BULA->setPixmap(BULL);
    BULA->setParent(parent);

    boomvideo->setScaledSize(QSize(60,60));
    BOOM->setMovie(boomvideo);
    bullettimer=new QTimer(this);
    boomtimer=new QTimer(this);
    bullettimer->start(5);
    started=false;
}
void enemybullet::bulletboom(int boomsitx, int boomsity) {
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

bool enemybullet::checkshootenemy(){
    if((bux+15)>=enemyx&&(bux+15)<=(enemyx+60)&&(buy+15)>=enemyy&&(buy+15)<=(enemyy+60)){
        bulletboom(enemyx,enemyy);
        return true;
    }
    return false;
}

void enemybullet::getenemysit(int x,int y){
    enemyx=x;
    enemyy=y;
}

bool enemybullet::checkmovebullet(){
    updatemapsit();
    if(checkshootenemy()){
        boommapsitx=mapbux;
        boommapsity=mapbuy;
        emit kill_my_tank();
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
