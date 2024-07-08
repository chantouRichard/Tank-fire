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
    bool check1=1;bool check2=1;bool check3=1;bool check4=1;bool check5=1,check6=1,check7=1,check8=1,check9=1,check10=1,check11=1,check12=1;
    if(MAP_Global[maptankx1][maptanky1-1]==4||MAP_Global[maptankx1][maptanky1-1]==0){
        check1=0;
    }
    if(MAP_Global[maptankx2][maptanky2-1]==4||MAP_Global[maptankx2][maptanky2-1]==0){
        check2=0;
    }
    if(MAP_Global[maptankx1][maptanky1+1]==4||MAP_Global[maptankx1][maptanky1+1]==0){
        check3=0;
    }
    if(MAP_Global[maptankx2][maptanky2+1]==4||MAP_Global[maptankx2][maptanky2+1]==0){
        check4=0;
    }
    if(MAP_Global[maptankx1-1][maptanky1]==4||MAP_Global[maptankx1-1][maptanky1]==0){
        check5=0;
    }
    if(MAP_Global[maptankx4-1][maptanky4]==4||MAP_Global[maptankx4-1][maptanky4]==0){
        check6=0;
    }
    if(MAP_Global[maptankx1+1][maptanky1]==4||MAP_Global[maptankx1+1][maptanky1]==0){
        check7=0;
    }
    if(MAP_Global[maptankx4+1][maptanky4]==4||MAP_Global[maptankx4+1][maptanky4]==0){
        check8=0;
    }
    if(MAP_Global[maptankx1][maptanky1]==4||MAP_Global[maptankx1][maptanky1]==0){
        check9=0;
    }
    if(MAP_Global[maptankx2][maptanky2]==4||MAP_Global[maptankx2][maptanky2]==0){
        check10=0;
    }
    if(MAP_Global[maptankx3][maptanky3]==4||MAP_Global[maptankx3][maptanky3]==0){
        check11=0;
    }
    if(MAP_Global[maptankx4][maptanky4]==4||MAP_Global[maptankx4][maptanky4]==0){
        check12=0;
    }
    if(tankx%60==0||tanky%60==0)
    {
        if(type==1)
        {
            if(tankx%60==0)
            {
                return check1&&(tanky%60==0);
            }
            else
                return (check1||check2);
        }
        if(type==2){
            if(tankx%60==0)
            {
                return check3&&(tanky%60==0);
            }
            else
                return check3||check4;
        }
        if(type==3)
        {
            if(tanky%60==0)
            {
                return check5&&(tankx%60==0);
            }
            else
            {
                return check5||check6;
            }

        }
        if(type==4)
        {
            if(tanky%60==0)
                return check7&&(tankx%60==0);
            else
                return check7||check8;
        }
    }
    else
    {
        return !((!check9)&&(!check10)&&(!check11)&&(!check12));
    }
}
//坦克的射击
void Tank::shoot(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;
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
        bugdet[i].BULA->hide();
        bugdet[i].BOOM->hide();
        bugdet[i].bigBOOM->hide();
    }
}
void Tank::move_up(){
    if(irremovable()) return;
    check_get_prop();
    type=1;
    tank_img->move(tankx,tanky-10);
    emit my_tank_move(tankx,tanky);
}
void Tank::move_down(){
    if(irremovable()) return;
    check_get_prop();
    type=2;
    tank_img->move(tankx,tanky+10);
    emit my_tank_move(tankx,tanky);
}
void Tank::move_left(){
    if(irremovable()) return;
    check_get_prop();
    type=3;
    tank_img->move(tankx-10,tanky);
    emit my_tank_move(tankx,tanky);
}
void Tank::move_right(){
    if(irremovable()) return;
    check_get_prop();
    type=4;
    tank_img->move(tankx+10,tanky);
    emit my_tank_move(tankx,tanky);
}

void Tank::check_get_prop(){
    if(MAP_Global[maptankx1][maptanky1]==20||MAP_Global[maptankx1][maptanky1]==30||MAP_Global[maptankx1][maptanky1]==40||MAP_Global[maptankx1][maptanky1]==50){
        emit get_prop(MAP_Global[maptankx1][maptanky1]);
        MAP_Global[maptankx1][maptanky1]=0;
    }
    if((MAP_Global[maptankx2][maptanky2]==20||MAP_Global[maptankx2][maptanky2]==30||MAP_Global[maptankx2][maptanky2]==40||MAP_Global[maptankx2][maptanky2]==50)&&(tankx%60!=0)){
        emit get_prop(MAP_Global[maptankx2][maptanky2]);
        MAP_Global[maptankx2][maptanky2]=0;
    }
    if((MAP_Global[maptankx3][maptanky3]==20||MAP_Global[maptankx3][maptanky3]==30||MAP_Global[maptankx3][maptanky3]==40||MAP_Global[maptankx3][maptanky3]==50)&&(tankx%60!=0)&&(tanky%60!=0)){
        emit get_prop(MAP_Global[maptankx3][maptanky3]);
        MAP_Global[maptankx3][maptanky3]=0;
    }
    if((MAP_Global[maptankx4][maptanky4]==20||MAP_Global[maptankx4][maptanky4]==30||MAP_Global[maptankx4][maptanky4]==40||MAP_Global[maptankx4][maptanky4]==50)&&(tanky%60!=0)){
        emit get_prop(MAP_Global[maptankx4][maptanky4]);
        MAP_Global[maptankx4][maptanky4]=0;
    }
}
