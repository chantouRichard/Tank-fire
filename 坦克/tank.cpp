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
    my_tank_live=1;
    movetimer=new QTimer(this);
    movetimer->setParent(this);
    //坦克速度
    my_tank_speed=50;
}

void Tank::showtank(QWidget *pa)
{
    tank_img->setParent(pa);
    TANK.load(":/1/Res/res/p2tankD.gif");
    tank_img->setPixmap(TANK);
    tank_img->move(tankx,tanky);
    updatemapsit();
    tank_img->show();
    //设置坦克图片始终在顶部
    tank_img->setWindowFlags(tank_img->windowFlags() | Qt::WindowStaysOnTopHint);
}

//检查坦克是否可以移动,可以移动返回false
bool Tank::irremovable()
{
    check_get_prop();
    tankx=tank_img->pos().x();
    tanky=tank_img->pos().y();
    updatemapsit();
    if(tankx%60==0||tanky%60==0)
    {
        if(type==1)
        {
            if(tankx%60==0)
            {
                return (MAP_Global[maptankx1][maptanky1-1]%10)&&(tanky%60==0);
            }
            else
                return (MAP_Global[maptankx1][maptanky1-1]%10)||(MAP_Global[maptankx2][maptanky2-1]%10);
        }
        if(type==2){
            if(tankx%60==0)
            {
                return (MAP_Global[maptankx1][maptanky1+1]%10)&&(tanky%60==0);
            }
            else
                return (MAP_Global[maptankx1][maptanky1+1]%10)||(MAP_Global[maptankx2][maptanky2+1]%10);
        }
        if(type==3)
        {
            if(tanky%60==0)
            {
                return (MAP_Global[maptankx1-1][maptanky1]%10)&&(tankx%60==0);
            }
            else
            {
                return (MAP_Global[maptankx1-1][maptanky1]%10)||(MAP_Global[maptankx4-1][maptanky4]%10);
            }

        }
        if(type==4)
        {
            if(tanky%60==0)
                return (MAP_Global[maptankx1+1][maptanky1]%10)&&(tankx%60==0);
            else
                return (MAP_Global[maptankx1+1][maptanky1]%10)||(MAP_Global[maptankx4+1][maptanky4]%10);
        }
    }
    else
    {
        return !((!(MAP_Global[maptankx1][maptanky1]%10))&&(!(MAP_Global[maptankx2][maptanky2]%10))&&(!(MAP_Global[maptankx3][maptanky3]%10))&&(!(MAP_Global[maptankx4][maptanky4]%10)));
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
    if(event->key()==Qt::Key_U)
    {
        emit this->use_prop(0);
    }
    if(event->key()==Qt::Key_I)
    {
        emit this->use_prop(1);
    }
    if(event->key()==Qt::Key_O)
    {
        emit this->use_prop(2);
    }
}

void Tank::MOVE(QKeyEvent *event){
    if(!my_tank_live) return;
    if(event->key()==KeyUp)
    {
        if(!startedmup)
        {
        updatestarted();
        movetimer->disconnect();
        type=1;
        TANK.load(":/1/Res/res/p2tankU.gif");
        tank_img->setPixmap(TANK);
        if(type==1)
        {
            movetimer->start(my_tank_speed);
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
//        TANK.load(":/6/Res/res6/Tank2.png");
        TANK.load(":/1/Res/res/p2tankD.gif");
        tank_img->setPixmap(TANK);
        if(type==2)
        {
            movetimer->start(my_tank_speed);
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
            movetimer->start(my_tank_speed);
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
            movetimer->start(my_tank_speed);
            connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
        }
    }

//    check_get_prop();
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

void Tank::addLife(int lifenumber)
{
    my_tank_live+=lifenumber;
    qDebug()<<"Life+1:"<<my_tank_live;
}

void Tank::shield()
{
    int tempLife=my_tank_live;
    my_tank_live=100;
    qDebug()<<"shield:"<<my_tank_live;
    QTimer * tempTimer=new QTimer;
    tempTimer->start(10000);
    connect(tempTimer,&QTimer::timeout,[=]{
        delete tempTimer;
        my_tank_live=tempLife;
    });


    qDebug()<<"shield:"<<my_tank_live;
}

void Tank::attack()
{
    qDebug()<<"attack";
}

void Tank::speedUp()
{
    int tempSpeed=my_tank_speed;
    my_tank_speed=20;
    QTimer * tempTimer2=new QTimer;
    tempTimer2->start(10000);
    connect(tempTimer2,&QTimer::timeout,[=]{
        tempTimer2->stop();
        my_tank_speed=tempSpeed;
    });

    qDebug()<<"Speed";
}

void Tank::check_get_prop(){
    if(MAP_Global[maptankx1][maptanky1]==20||MAP_Global[maptankx1][maptanky1]==30||MAP_Global[maptankx1][maptanky1]==40||MAP_Global[maptankx1][maptanky1]==50){
        emit get_prop(MAP_Global[maptankx1][maptanky1]);
//        if(MAP_Global[maptankx1][maptanky1]==20)addLife(1);
//        else if(MAP_Global[maptankx1][maptanky1]==30)shield();
//        else if(MAP_Global[maptankx1][maptanky1]==40)attack();
//        else if(MAP_Global[maptankx1][maptanky1]==50)speedUp();
        MAP_Global[maptankx1][maptanky1]=0;
        update();
    }
    if((MAP_Global[maptankx2][maptanky2]==20||MAP_Global[maptankx2][maptanky2]==30||MAP_Global[maptankx2][maptanky2]==40||MAP_Global[maptankx2][maptanky2]==50)&&(tankx%60!=0)){
        emit get_prop(MAP_Global[maptankx2][maptanky2]);
//        if(MAP_Global[maptankx2][maptanky2]==20)addLife(1);
//        else if(MAP_Global[maptankx2][maptanky2]==30)shield();
//        else if(MAP_Global[maptankx2][maptanky2]==40)attack();
//        else if(MAP_Global[maptankx2][maptanky2]==50)speedUp();
        MAP_Global[maptankx2][maptanky2]=0;
        update();
    }
    if((MAP_Global[maptankx3][maptanky3]==20||MAP_Global[maptankx3][maptanky3]==30||MAP_Global[maptankx3][maptanky3]==40||MAP_Global[maptankx3][maptanky3]==50)&&(tankx%60!=0)&&(tanky%60!=0)){
        emit get_prop(MAP_Global[maptankx3][maptanky3]);
//        if(MAP_Global[maptankx3][maptanky3]==20)addLife(1);
//        else if(MAP_Global[maptankx3][maptanky3]==30)shield();
//        else if(MAP_Global[maptankx3][maptanky3]==40)attack();
//        else if(MAP_Global[maptankx3][maptanky3]==50)speedUp();
        MAP_Global[maptankx3][maptanky3]=0;
        update();
    }
    if((MAP_Global[maptankx4][maptanky4]==20||MAP_Global[maptankx4][maptanky4]==30||MAP_Global[maptankx4][maptanky4]==40||MAP_Global[maptankx4][maptanky4]==50)&&(tanky%60!=0)){
        emit get_prop(MAP_Global[maptankx4][maptanky4]);
//        if(MAP_Global[maptankx4][maptanky4]==20)addLife(1);
//        else if(MAP_Global[maptankx4][maptanky4]==30)shield();
//        else if(MAP_Global[maptankx4][maptanky4]==40)attack();
//        else if(MAP_Global[maptankx4][maptanky4]==50)speedUp();
        MAP_Global[maptankx4][maptanky4]=0;
        update();
    }
//    update();
}

