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
    type=1;
    startedmup=startedmdo=startedmle=startedmri=0;
    my_tank_live=true;
    movetimer=new QTimer(this);
    movetimer->setParent(this);
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
    tankx=tank_img->pos().x();
    tanky=tank_img->pos().y();
    updatemapsit();
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
    if(event->key()==KeyShoot&&my_tank_live){
        emit my_tank_shoot();
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

void Tank::MOVE(QKeyEvent *event){
    if(!my_tank_live) return;
    if(event->key()==KeyUp)
    {
        qDebug()<<"up";
        if(!startedmup)
        {
        updatestarted();
        movetimer->disconnect();
        type=1;
        TANK.load(":/1/Res/res/p2tankU.gif");
        tank_img->setPixmap(TANK);
        if(type==1)
        {
            movetimer->start(50);
            startedmup=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_up);
        }
    }
    }
    if(event->key()==KeyDown&&!startedmdo)
    {
        updatestarted();
        movetimer->disconnect();
        type=2;
        TANK.load(":/1/Res/res/p2tankD.gif");
        tank_img->setPixmap(TANK);
        if(type==2)
        {
            movetimer->start(50);
            startedmdo=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_down);
        }
    }
    if(event->key()==KeyLeft&&!startedmle)
    {
        updatestarted();
        movetimer->disconnect();
        type=3;
        TANK.load(":/1/Res/res/p2tankL.gif");
        tank_img->setPixmap(TANK);
        if(type==3)
        {
            movetimer->start(50);
            startedmle=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_left);
        }
    }
    if(event->key()==KeyRight&&!startedmri)
    {
        updatestarted();
        movetimer->disconnect();
        type=4;
        TANK.load(":/1/Res/res/p2tankR.gif");
        tank_img->setPixmap(TANK);
        if(type==4)
        {
            startedmri=1;
            movetimer->start(50);
            connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
        }
    }
}
void Tank::updatestarted(){
    startedmdo=startedmle=startedmri=startedmup=0;
}
void Tank::keyPressEvent(QKeyEvent *event) {
    MOVE(event);
    //以上是坦克的移动
    //以下是子弹的移动
    shoot(event);
}
void Tank::keyReleaseEvent(QKeyEvent *event){
if(event->isAutoRepeat())
    return;
    if(event->key()==KeyUp){
        disconnect(movetimer,&QTimer::timeout,this,&Tank::move_up);
        startedmup=0;
    }
    if(event->key()==KeyDown){
        disconnect(movetimer,&QTimer::timeout,this,&Tank::move_down);
        startedmdo=0;
    }
    if(event->key()==KeyLeft){
        disconnect(movetimer,&QTimer::timeout,this,&Tank::move_left);
        startedmle=0;
    }
    if(event->key()==KeyRight){
        qDebug()<<"stop";
        disconnect(movetimer,&QTimer::timeout,this,&Tank::move_right);
        startedmri=0;
    }
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

void Tank::Deletebullets(){
    for(int i=0;i<bulletsnumber;i++){
        bugdet[i].hide();
        bugdet[i].BOOM->hide();
        bugdet[i].bigBOOM->hide();
    }
}
void Tank::move_up(){
    if(irremovable()) return;
    type=1;
    tank_img->move(tankx,tanky-10);
    emit my_tank_move(tankx,tanky);
}
void Tank::move_down(){
    if(irremovable()) return;
    type=2;
    tank_img->move(tankx,tanky+10);
    emit my_tank_move(tankx,tanky);
}
void Tank::move_left(){
    if(irremovable()) return;
    type=3;
    tank_img->move(tankx-10,tanky);
    emit my_tank_move(tankx,tanky);
}
void Tank::move_right(){
    if(irremovable()) return;
    type=4;
    tank_img->move(tankx+10,tanky);
    emit my_tank_move(tankx,tanky);
}
