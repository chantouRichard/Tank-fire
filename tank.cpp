#include "tank.h"
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QTransform>

Tank::Tank(int init_tank_x,int init_tank_y,QWidget *parent): QWidget(parent)
{
    tankx=init_tank_x;tanky=init_tank_y;
    idx=-1;
    tank_img=new QLabel();
}

void Tank::showtank(QWidget *pa)
{
    tank_img->setParent(pa);
    TANK.load(":/1/Res/res/p2tankD.gif");
    tank_img->setPixmap(TANK);
    tank_img->move(tankx,tanky);
    tank_img->show();
    //设置坦克图片始终在顶部
    tank_img->setWindowFlags(tank_img->windowFlags() | Qt::WindowStaysOnTopHint);
}

//检查坦克是否可以移动,可以移动返回false
bool Tank::irremovable()
{
    if(tankx%60==0||tanky%60==0)
    {
        if(type==1)
        {
            if(tankx%60==0)
            {
                return MAP_Global[maptankx1][maptanky1-1]&&(tanky%60==0);
            }
            else
                return MAP_Global[maptankx1][maptanky1-1]||MAP_Global[maptankx2][maptanky2-1];
        }
        if(type==2){
            if(tankx%60==0)
            {
                return MAP_Global[maptankx1][maptanky1+1]&&(tanky%60==0);
            }
            else
                return MAP_Global[maptankx1][maptanky1+1]||MAP_Global[maptankx2][maptanky2+1];
        }
        if(type==3)
        {
            if(tanky%60==0)
            {
                return MAP_Global[maptankx1-1][maptanky1]&&(tankx%60==0);
            }
            else
            {
                return MAP_Global[maptankx1-1][maptanky1]||MAP_Global[maptankx4-1][maptanky4];
            }

        }
        if(type==4)
        {
            if(tanky%60==0)
                return MAP_Global[maptankx1+1][maptanky1]&&(tankx%60==0);
            else
                return MAP_Global[maptankx1+1][maptanky1]||MAP_Global[maptankx4+1][maptanky4];
        }
    }
    else
    {
        return !((!MAP_Global[maptankx1][maptanky1])&&(!MAP_Global[maptankx2][maptanky2])&&(!MAP_Global[maptankx3][maptanky3])&&(!MAP_Global[maptankx4][maptanky4]));
    }
}
//坦克的射击
void Tank::shoot(QKeyEvent *event)
{
    if(event->key()==KeyShoot){
        idx++;
        if(idx<=bulletsnumber-1)
            bugdet[idx].movebullet(this->parentWidget(),this->type,tankx,tanky);
        else
        {
            if(idx<2*bulletsnumber){
                bugdet[idx-bulletsnumber].Disconnected();
                bugdet[idx-bulletsnumber].movebullet(this->parentWidget(),this->type,tankx,tanky);
            }
            else
            {
                idx=bulletsnumber;
                bugdet[idx-bulletsnumber].Disconnected();
                bugdet[idx-bulletsnumber].movebullet(this->parentWidget(),this->type,tankx,tanky);
            }

        }
    }
}

void Tank::MOVE(QKeyEvent *event,int x,int y){
    if(event->key()==KeyUp)
    {
        type=1;
        TANK.load(":/1/Res/res/p2tankU.gif");
        tank_img->setPixmap(TANK);
        if(!irremovable())
        {
            tank_img->move(x,y-10);
        }
    }
    if(event->key()==KeyDown)
    {
        type=2;
        TANK.load(":/1/Res/res/p2tankD.gif");
        tank_img->setPixmap(TANK);
        if(type==2&&!irremovable())
        {
            tank_img->move(x,y+10);
        }
    }
    if(event->key()==KeyLeft)
    {
        type=3;
        TANK.load(":/1/Res/res/p2tankL.gif");
        tank_img->setPixmap(TANK);
        if(type==3&&!irremovable())
        {
            tank_img->move(x-10,y);
        }
    }
    if(event->key()==KeyRight)
    {
        type=4;
        TANK.load(":/1/Res/res/p2tankR.gif");
        tank_img->setPixmap(TANK);
        if(type==4&&!irremovable())
        {
            tank_img->move(x+10,y);
        }
    }
}

void Tank::keyPressEvent(QKeyEvent *event) {
    tankx=tank_img->pos().x();
    tanky=tank_img->pos().y();

    updatemapsit();
    MOVE(event,tankx,tanky);
    //以上是坦克的移动
    //以下是子弹的移动
    shoot(event);
}

void Tank::updatemapsit(){
    maptankx1=tankx/60;
    maptanky1=tanky/60;
    maptankx2=(tankx+60)/60;
    maptanky2=maptanky1;
    maptankx3=maptankx2;
    maptanky3=(tanky+60)/60;
    maptankx4=maptankx1;
    maptanky4=maptanky3;
}
