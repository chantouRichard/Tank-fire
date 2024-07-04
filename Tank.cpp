#include "Tank.h"
#include "ui_widget.h"
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QTransform>
Tank::Tank(QWidget *parent)
    : QWidget(parent)
{
    tankx=60;tanky=60;
    idx=-1;
}
void Tank::showtank(QWidget *pa){
    bul->setParent(pa);
    BUL.load("D:/PICC/Res/res/p2tankD.gif");
    bul->setPixmap(BUL);
    bul->move(tankx,tanky);
    bul->setWindowFlags(bul->windowFlags() | Qt::WindowStaysOnTopHint);
}
Tank::~Tank()
{

}
bool Tank::checkmovement(){
   int  maptankx1=tankx/60;
    int maptanky1=tanky/60;
    int maptankx2=(tankx+60)/60;
    int maptanky2=maptanky1;
    int maptankx3=maptankx2;
    int maptanky3=(tanky+60)/60;
    int maptankx4=maptankx1;
    int maptanky4=maptanky3;
    if(type==1){
     maptanky1=(tanky-10)/60;
     maptanky2=maptanky1;
     maptanky3=(tanky+60-10)/60;
     maptanky4=maptanky3;
        }
        if(type==2){
            maptanky1=(tanky+10)/60;
            maptanky2=maptanky1;
            maptanky3=(tanky+60+10)/60;
            maptanky4=maptanky3;
        }
        if(type==3){
            maptankx1=(tankx-10)/60;
            maptankx2=maptankx1;
            maptankx3=(tankx+60-10)/60;
            maptankx4=maptankx3;

        }
        if(type==4){
            maptankx1=(tankx+10)/60;
            maptankx2=maptankx1;
            maptankx3=(tankx+60+10)/60;
            maptankx4=maptankx3;

        }
        return !((!MAP[maptankx1][maptanky1])&&(!MAP[maptankx2][maptanky2])&&(!MAP[maptankx3][maptanky3])&&(!MAP[maptankx4][maptanky4]));
 }  //检查坦克是否可以移动
void Tank::shoot(QKeyEvent *event){
    if(event->key()==KeyShoot){
        idx++;
    if(idx<=bulletsnumber-1)
          bugdet[idx].movebullet(parentWidget(),this->type,tankx,tanky);
    else{
    if(idx>=bulletsnumber&&idx<2*bulletsnumber){
        bugdet[idx-bulletsnumber].Disconnected();
        bugdet[idx-bulletsnumber].movebullet(parentWidget(),this->type,tankx,tanky);
    }
    else{
        idx=bulletsnumber;
        bugdet[idx-bulletsnumber].Disconnected();
        bugdet[idx-bulletsnumber].movebullet(parentWidget(),this->type,tankx,tanky);
    }

    }
        }}//坦克的射击
void Tank::MOVE(QKeyEvent *event,int x,int y){
    if(event->key()==KeyUp){
        if(type==1&&!checkmovement()){
        bul->move(x,y-10);
        }
        else{

        type=1;
        BUL.load("D:/PICC/Res/res/p2tankU.gif");
        bul->setPixmap(BUL);
        }
    }
    if(event->key()==KeyDown){
        if(type==2&&!checkmovement()){
        bul->move(x,y+10);
        }
        else{
        type=2;
        BUL.load("D:/PICC/Res/res/p2tankD.gif");
        bul->setPixmap(BUL);
        }
    }if(event->key()==KeyLeft){
        if(type==3&&!checkmovement()){
        bul->move(x-10,y);
        }
        else{
        type=3;
        BUL.load("D:/PICC/Res/res/p2tankL.gif");
        bul->setPixmap(BUL);
        }

    }if(event->key()==KeyRight){
        if(type==4&&!checkmovement()){
        bul->move(x+10,y);
        }
        else{
        type=4;
        BUL.load("D:/PICC/Res/res/p2tankR.gif");
        bul->setPixmap(BUL);
        }
    }
}
void Tank::keyPressEvent(QKeyEvent *event) {
    tankx=bul->pos().x();
    tanky=bul->pos().y();

    MOVE(event,tankx,tanky);
    //以上是坦克的移动
    //以下是子弹的移动
    shoot(event);
}
void Tank::Loadmap(int map[25][25]){
for(int i=0;i<25;i++){
    for(int j=0;j<25;j++){
    MAP[i][j]=map[i][j];
}
}
}
void Tank::addbudget(){
    for(int i=0;i<bulletsnumber;i++){
        bugdet[i].Loadmap(MAP);
    }
}
