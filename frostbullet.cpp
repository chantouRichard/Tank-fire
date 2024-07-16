#include "frostbullet1.h"

frostBullet1::frostBullet1(QWidget *parent):enemybullet(parent)
{
    boomvideo=new QMovie(BulletBoom_gif);

    BULL.load(frost_bullet_pic);

    BULL = BULL.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    BULA->setPixmap(BULL);
    BULA->setParent(parent);

    boomvideo->setScaledSize(QSize(60,60));
    BOOM->setMovie(boomvideo);
    bullettimer=new QTimer(this);
    boomtimer=new QTimer(this);

}
bool frostBullet1::checkmovebullet()
{
    updatemapsit();
    if(checkshootenemy())
    {
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
