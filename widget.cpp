#include "widget.h"
#include "ui_widget.h"
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QTransform>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    tankx=50;tanky=50;
    bul->setParent(this);
    this->resize(1500,1500);
    BUL.load("D:/PICC/Res/res/p2tankD.gif");
    bul->setPixmap(BUL);
    bul->move(tankx,tanky);



    idx=-1;
}

Widget::~Widget()
{

}
bool Widget::checkmovement(QKeyEvent *event){

}   //检查坦克是否可以移动
void Widget::shoot(QKeyEvent *event){
    if(event->key()==Qt::Key_Space){
        idx++;
    if(idx<=4)
          bugdet[idx].movebullet(this,this->type,tankx,tanky);
    else{
    if(idx==5){
        bugdet[idx-5].Disconnected();
        bugdet[idx-5].movebullet(this,this->type,tankx,tanky);
    }
    if(idx==6){
        bugdet[idx-5].Disconnected();
        bugdet[idx-5].movebullet(this,this->type,tankx,tanky);
    }
    if(idx==7){
        bugdet[idx-5].Disconnected();
        bugdet[idx-5].movebullet(this,this->type,tankx,tanky);
    }
    if(idx==8){
        bugdet[idx-5].Disconnected();
        bugdet[idx-5].movebullet(this,this->type,tankx,tanky);
    }
    if(idx==9){
        bugdet[idx-5].Disconnected();
        bugdet[idx-5].movebullet(this,this->type,tankx,tanky);
    }
    if(idx==10){
        idx=5;
        bugdet[idx-5].Disconnected();
        bugdet[idx-5].movebullet(this,this->type,tankx,tanky);

    }
    }
        }}//坦克的射击
void Widget::MOVE(QKeyEvent *event,int x,int y){
    if(event->key()==Qt::Key_W){
        if(type==1){
        bul->move(x,y-10);
        }
        else{
        type=1;
       BUL.load("D:/PICC/Res/res/p2tankU.gif");
       bul->setPixmap(BUL);
        }
    }
    if(event->key()==Qt::Key_S){
        if(type==2){
        bul->move(x,y+10);
        }
        else{
        type=2;
      BUL.load("D:/PICC/Res/res/p2tankD.gif");
       bul->setPixmap(BUL);
        }
    }if(event->key()==Qt::Key_A){
        if(type==3){
        bul->move(x-10,y);
        }
        else{
        type=3;
       BUL.load("D:/PICC/Res/res/p2tankL.gif");
       bul->setPixmap(BUL);
        }

    }if(event->key()==Qt::Key_D){
        if(type==4){
        bul->move(x+10,y);
        }
        else{
        type=4;
        BUL.load("D:/PICC/Res/res/p2tankR.gif");
        bul->setPixmap(BUL);
        }
    }
}
void Widget::keyPressEvent(QKeyEvent *event) {
    tankx=bul->pos().x();
    tanky=bul->pos().y();
    MOVE(event,tankx,tanky);
    //以上是坦克的移动
    //以下是子弹的移动
    shoot(event);
}

