#include "enemybullet.h"

enemybullet::enemybullet(QWidget *parent) : Bullet(parent)
{
    BULA=new QLabel;
    BOOM=new QLabel;
    bigBOOM=new QLabel;

    BULL.load(bullet1_pic);
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
bool enemybullet::checkshootenemy(){
    if(bux>=enemyx&&bux<=(enemyx+60)&&buy>=enemyy&&buy<=(enemyy+60))
        return true;
    return false;
}

void enemybullet::getenemysit(int x,int y){
    enemyx=x;
    enemyy=y;
}

bool enemybullet::checkmovebullet(){
    if(checkshootenemy()){
        boommapsitx=mapbux;
        boommapsity=mapbuy;
        bulletboom(bux-50,buy-50);
        emit boom(mapbux,mapbuy);
        emit kill_my_tank();
        return true;
    }
    if(type==1){
        if(MAP_Global[mapbuy][mapbux]!=0&&MAP_Global[mapbuy][mapbux]!=3&&MAP_Global[mapbuy][mapbux]!=4&&MAP_Global[mapbuy][mapbux]<=10)
        {
            boommapsitx=mapbuy;
            boommapsity=mapbux;
            bulletboom(bux-50,buy-50);
            emit boom(mapbuy,mapbux);
            return true;
        }
        if(MAP_Global[mapbuy][mapbux-1]==0||MAP_Global[mapbuy][mapbux-1]==3||MAP_Global[mapbuy][mapbux-1]==4||MAP_Global[mapbuy][mapbux-1]>10){
            return false;
        }
        else{
            if(buy>60*mapbux)
                return false;
            else{
                boommapsitx=mapbuy;
                boommapsity=mapbux-1;
                bulletboom(bux-50,buy-50);
                emit boom(mapbuy,mapbux-1);
                return true;
            }
        }
    }
    if(type==2){
        if(MAP_Global[mapbuy][mapbux+1]==0||MAP_Global[mapbuy][mapbux+1]==3||MAP_Global[mapbuy][mapbux+1]==4||MAP_Global[mapbuy][mapbux+1]>10){
            return false;
        }
        else{
            if(buy+5<60*(mapbux+1)){
                return false;
            }
            else{
                boommapsitx=mapbuy;
                boommapsity=mapbux+1;
                bulletboom(bux-50,buy-50);
                emit boom(mapbuy,mapbux+1);
                return true;
            }}
    }
    if(type==3){
        if(MAP_Global[mapbuy][mapbux]!=0&&MAP_Global[mapbuy][mapbux]!=3&&MAP_Global[mapbuy][mapbux]!=4&&MAP_Global[mapbuy][mapbux]<=10){
            boommapsitx=mapbuy;
            boommapsity=mapbux;
            bulletboom(bux-50,buy-50);
            emit boom(mapbuy,mapbux);
            return true;
        }
        if( MAP_Global[mapbuy-1][mapbux]==0||MAP_Global[mapbuy-1][mapbux]==3||MAP_Global[mapbuy-1][mapbux]==4||MAP_Global[mapbuy-1][mapbux]>10)
            return false;
        else{
            if(bux>60*mapbuy)
                return false;
            else{
                boommapsitx=mapbuy-1;
                boommapsity=mapbux;
                bulletboom(bux-50,buy-50);
                emit boom(mapbuy-1,mapbux);
                return true;
            }
        }
    }
    if(type==4){
        if(MAP_Global[mapbuy+1][mapbux]==0||MAP_Global[mapbuy+1][mapbux]==3||MAP_Global[mapbuy+1][mapbux]==4||MAP_Global[mapbuy+1][mapbux]>10)
            return false;
        else{
            if(bux+5<60*(mapbuy+1)){
                return false;
            }
            else{
                boommapsitx=mapbuy+1;
                boommapsity=mapbux;
                bulletboom(bux-50,buy-50);
                emit boom(mapbuy+1,mapbux);
                return true;
            }
        }
    }

}
