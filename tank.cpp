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
    my_tank_speed=30;
    control_mode=1;
    move_direction=2;
    moveforward=moveforward=0;
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

void Tank::showtank(QWidget *pa)
{
    srand(static_cast<unsigned>(time(0)));
    tank_img->setParent(pa);
    TANK.load(TankUp);
    tank_img->setPixmap(TANK);
    tank_img->move(tankx,tanky);
    tank_img->show();
    //设置坦克图片始终在顶部
    tank_img->setWindowFlags(tank_img->windowFlags() | Qt::WindowStaysOnTopHint);
    updatemapsit();
    emit my_tank_move(tankx,tanky);
}
//检查坦克是否可以移动,可以移动返回false
bool Tank::irremovable()
{
    check_get_prop();
    tankx=tank_img->pos().x();
    tanky=tank_img->pos().y();
    updatemapsit();
    bool check1=1;bool check2=1;bool check3=1;bool check4=1;bool check5=1,check6=1,check7=1,check8=1,check9=1,check10=1,check11=1,check12=1;
    if(MAP_Global[maptanky1-1][maptankx1]==0||MAP_Global[maptanky1-1][maptankx1]>10){
        check1=0;
    }
    if(MAP_Global[maptanky2-1][maptankx2]==0||MAP_Global[maptanky2-1][maptankx2]>10){
        check2=0;
    }
    if(MAP_Global[maptanky1+1][maptankx1]==0||MAP_Global[maptanky1+1][maptankx1]>10){
        check3=0;
    }
    if(MAP_Global[maptanky2+1][maptankx2]==0||MAP_Global[maptanky2+1][maptankx2]>10){
        check4=0;
    }
    if(MAP_Global[maptanky1][maptankx1-1]==0||MAP_Global[maptanky1][maptankx1-1]>10){
        check5=0;
    }
    if(MAP_Global[maptanky4][maptankx4-1]==0||MAP_Global[maptanky4][maptankx4-1]>10){
        check6=0;
    }
    if(MAP_Global[maptanky1][maptankx1+1]==0||MAP_Global[maptanky1][maptankx1+1]>10){
        check7=0;
    }
    if(MAP_Global[maptanky4][maptankx4+1]==0||MAP_Global[maptanky4][maptankx4+1]>10){
        check8=0;
    }
    if(MAP_Global[maptanky1][maptankx1]==0||MAP_Global[maptanky1][maptankx1]>10){
        check9=0;
    }
    if(MAP_Global[maptanky2][maptankx2]==0||MAP_Global[maptanky2][maptankx2]>10){
        check10=0;
    }
    if(MAP_Global[maptanky3][maptankx3]==0||MAP_Global[maptanky3][maptankx3]>10){
        check11=0;
    }
    if(MAP_Global[maptanky4][maptankx4]==0||MAP_Global[maptanky4][maptankx4]>10){
        check12=0;
    }
    if(control_mode==1||control_mode==3){
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
    else if(control_mode==2){

        if(tankx%60==0||tanky%60==0)
        {
            if(move_direction==1)
            {
                if(tankx%60==0)
                {
                    return check1&&(tanky%60==0);
                }
                else
                    return (check1||check2);
            }
            if(move_direction==2){
                if(tankx%60==0)
                {
                    return check3&&(tanky%60==0);
                }
                else
                    return check3||check4;
            }
            if(move_direction==3)
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
            if(move_direction==4)
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
    if(event->key()==KeyProp1)
    {
        emit this->use_prop(0);
    }
    if(event->key()==KeyProp2)
    {
        emit this->use_prop(1);
    }
    if(event->key()==KeyProp3)
    {
        emit this->use_prop(2);
    }
    if(event->key()==KeyProp4)
    {
        emit this->use_prop(3);
    }
}

void Tank::shoot_control2(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;
    if(event->key()==KeyShoot&&my_tank_live){
        int pretype=type;
        type=rand()%4+1;
        if(moveforward){
            if(pretype==1){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_up);
                startedmup=0;
                if(type==1){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmup=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_up);

                }
                if(type==2){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmdo=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_down);

                }
                if(type==3){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmle=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_left);

                }
                if(type==4){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmri=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                }
            }
            if(pretype==2){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_down);
                startedmdo=0;
                if(type==1){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmup=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_up);

                }
                if(type==2){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmdo=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_down);

                }
                if(type==3){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmle=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_left);

                }
                if(type==4){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmri=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                }
            }
            if(pretype==3){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_left);
                startedmle=0;
                if(type==1){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmup=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_up);

                }
                if(type==2){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmdo=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_down);

                }
                if(type==3){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmle=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_left);

                }
                if(type==4){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmri=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                }
            }
            if(pretype==4){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                startedmri=0;
                if(type==1){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmup=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_up);

                }
                if(type==2){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmdo=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_down);

                }
                if(type==3){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmle=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_left);

                }
                if(type==4){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmri=1;
                    moveforward=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                }
            }
        }
        if(moveback){

            if(pretype==2){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_up);
                startedmdo=0;
                if(type==2){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmup=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_up);

                }
                if(type==1){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmdo=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_down);

                }
                if(type==4){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmle=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_left);

                }
                if(type==3){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmri=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                }
            }
            if(pretype==1){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_down);
                startedmup=0;
                if(type==2){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmup=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_up);

                }
                if(type==1){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmdo=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_down);

                }
                if(type==4){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmle=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_left);

                }
                if(type==3){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmri=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                }
            }
            if(pretype==4){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_left);
                startedmri=0;
                if(type==2){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmup=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_up);

                }
                if(type==1){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmdo=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_down);

                }
                if(type==4){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmle=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_left);

                }
                if(type==3){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmri=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                }
            }
            if(pretype==3){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                startedmle=0;
                if(type==2){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmup=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_up);

                }
                if(type==1){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmdo=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_down);

                }
                if(type==4){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmle=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_left);

                }
                if(type==3){
                    updatestarted();
                    movetimer->disconnect();

                    movetimer->start(my_tank_speed);
                    startedmri=1;
                    moveback=1;
                    connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                }
            }
        }
        if(type==1){
            TANK.load(TankUp);
            tank_img->setPixmap(TANK);
        }
        if(type==2){
            TANK.load(TankDown);
            tank_img->setPixmap(TANK);
        }
        if(type==3){
            TANK.load(TankLeft);
            tank_img->setPixmap(TANK);
        }
        if(type==4){
            TANK.load(TankRight);
            tank_img->setPixmap(TANK);
        }
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
    if(event->key()==KeyProp1)
    {
        emit this->use_prop(0);
    }
    if(event->key()==KeyProp2)
    {
        emit this->use_prop(1);
    }
    if(event->key()==KeyProp3)
    {
        emit this->use_prop(2);
    }
    if(event->key()==KeyProp4)
    {
        emit this->use_prop(3);
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
            TANK.load(TankUp);
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
        TANK.load(TankDown);
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
        TANK.load(TankLeft);
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
        TANK.load(TankRight);
        tank_img->setPixmap(TANK);
        if(type==4)
        {
            startedmri=1;
            movetimer->start(my_tank_speed);
            connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
        }
    }

}

void Tank::updatestarted(){
    startedmdo=startedmle=startedmri=startedmup=0;
    moveforward=moveback=0;
}

void Tank::keyPressEvent(QKeyEvent *event) {
    if(control_mode==1){
        MOVE(event);
        //以上是坦克的移动
        //以下是子弹的移动
        shoot(event);
    }
    else if(control_mode==2){   //移动方向玩法
        MOVE_control2(event);
        shoot_control2(event);
    }
}

void Tank::keyReleaseEvent(QKeyEvent *event){
    if(event->isAutoRepeat())
        return;
    if(control_mode==1||control_mode==3){
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
    else if(control_mode==2){
        if(event->key()==KeyUp){
            if(type==1){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_up);
                startedmup=0;
                moveforward=0;
            }
            if(type==2){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_down);
                startedmdo=0;
                moveforward=0;
            }
            if(type==3){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_left);
                startedmle=0;
                moveforward=0;
            }
            if(type==4){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                startedmri=0;
                moveforward=0;
            }
        }
        if(event->key()==KeyDown){
            if(type==2){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_up);
                startedmup=0;
                moveback=0;
            }
            if(type==1){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_down);
                startedmdo=0;
                moveback=0;
            }
            if(type==4){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_left);
                startedmle=0;
                moveback=0;
            }
            if(type==3){
                disconnect(movetimer,&QTimer::timeout,this,&Tank::move_right);
                startedmri=0;
                moveback=0;
            }

        }
    }
}

void Tank::MOVE_control2(QKeyEvent *event){
    if(my_tank_live==0) return;
    if(event->key()==KeyUp){
        if(type==1&&!startedmup){
            updatestarted();
            movetimer->disconnect();

            movetimer->start(my_tank_speed);
            startedmup=1;
            moveforward=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_up);

        }
        if(type==2&&!startedmdo){
            updatestarted();
            movetimer->disconnect();

            movetimer->start(my_tank_speed);
            startedmdo=1;
            moveforward=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_down);

        }
        if(type==3&&!startedmle){
            updatestarted();
            movetimer->disconnect();

            movetimer->start(my_tank_speed);
            startedmle=1;
            moveforward=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_left);

        }
        if(type==4&&!startedmri){
            updatestarted();
            movetimer->disconnect();

            movetimer->start(my_tank_speed);
            startedmri=1;
            moveforward=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
        }

    }
    if(event->key()==KeyDown){
        if(type==2&&!startedmup){
            updatestarted();
            movetimer->disconnect();

            movetimer->start(my_tank_speed);
            startedmup=1;
            moveback=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_up);

        }
        if(type==1&&!startedmdo){
            updatestarted();
            movetimer->disconnect();

            movetimer->start(my_tank_speed);
            startedmdo=1;
            moveback=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_down);

        }
        if(type==4&&!startedmle){
            updatestarted();
            movetimer->disconnect();

            movetimer->start(my_tank_speed);
            startedmle=1;
            moveback=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_left);

        }
        if(type==3&&!startedmri){
            updatestarted();
            movetimer->disconnect();

            movetimer->start(my_tank_speed);
            startedmri=1;
            moveback=1;
            connect(movetimer,&QTimer::timeout,this,&Tank::move_right);
        }

    }

}

void Tank::Deletebullets(){
    for(int i=0;i<bulletsnumber;i++){
        bugdet[i].BULA->hide();
        bugdet[i].BOOM->hide();
    }
}

void Tank::move_up(){
    move_direction=1;
    if(irremovable()) return;
    check_get_prop();
    if(control_mode==1||control_mode==3) type=1;
    tank_img->move(tankx,tanky-10);
    emit my_tank_move(tankx,tanky);
}

void Tank::move_down(){
    move_direction=2;
    if(irremovable()) return;
    check_get_prop();
    if(control_mode==1||control_mode==3) type=2;
    tank_img->move(tankx,tanky+10);
    emit my_tank_move(tankx,tanky);
}

void Tank::move_left(){
    move_direction=3;
    if(irremovable()) return;
    check_get_prop();
    if(control_mode==1||control_mode==3) type=3;
    tank_img->move(tankx-10,tanky);
    emit my_tank_move(tankx,tanky);
}

void Tank::move_right(){
    move_direction=4;
    if(irremovable()) return;
    check_get_prop();
    if(control_mode==1||control_mode==3) type=4;
    tank_img->move(tankx+10,tanky);
    emit my_tank_move(tankx,tanky);
}

void Tank::addLife(int lifenumber)
{
    my_tank_live+=lifenumber;
}

void Tank::shield()
{
    int tempLife=my_tank_live;
    my_tank_live=100;
    QTimer * tempTimer=new QTimer;
    tempTimer->start(10000);
    connect(tempTimer,&QTimer::timeout,[=]{
        delete tempTimer;
        my_tank_live=tempLife;
    });
}

void Tank::attack()
{
//    int tempattack=my_tank->attack;
//    my_tank_live=100;
//    QTimer * tempTimer=new QTimer;
//    tempTimer->start(10000);
//    connect(tempTimer,&QTimer::timeout,[=]{
//        delete tempTimer;
//        my_tank_live=tempLife;
//    });
}

void Tank::speedUp()
{
    int tempSpeed=my_tank_speed;
    my_tank_speed=20;
    QTimer * tempTimer2=new QTimer;
    tempTimer2->start(10000);
    connect(tempTimer2,&QTimer::timeout,[=]{
        tempTimer2->stop();
        if(tempSpeed==my_tank_speed)
            my_tank_speed=50;
        else
            my_tank_speed=tempSpeed;
    });
}

bool Tank::check_get_prop(){
    bool flag=false;
    if(control_mode==1||control_mode==2)
    {
        if(MAP_Global[maptanky1][maptankx1]==20||MAP_Global[maptanky1][maptankx1]==30||MAP_Global[maptanky1][maptankx1]==40||MAP_Global[maptanky1][maptankx1]==50){
            emit get_prop(MAP_Global[maptanky1][maptankx1]);
            MAP_Global[maptanky1][maptankx1]=0;
            flag=true;
            update();
        }
        if((MAP_Global[maptanky2][maptankx2]==20||MAP_Global[maptanky2][maptankx2]==30||MAP_Global[maptanky2][maptankx2]==40||MAP_Global[maptanky2][maptankx2]==50)&&(tankx%60!=0)){
            emit get_prop(MAP_Global[maptanky2][maptankx2]);
            MAP_Global[maptanky2][maptankx2]=0;
            flag=true;
            update();
        }
        if((MAP_Global[maptanky3][maptankx3]==20||MAP_Global[maptanky3][maptankx3]==30||MAP_Global[maptanky3][maptankx3]==40||MAP_Global[maptanky3][maptankx3]==50)&&(tankx%60!=0)&&(tanky%60!=0)){
            emit get_prop(MAP_Global[maptanky3][maptankx3]);
            MAP_Global[maptanky3][maptankx3]=0;
            flag=true;
            update();
        }
        if((MAP_Global[maptanky4][maptankx4]==20||MAP_Global[maptanky4][maptankx4]==30||MAP_Global[maptanky4][maptankx4]==40||MAP_Global[maptanky4][maptankx4]==50)&&(tanky%60!=0)){
            emit get_prop(MAP_Global[maptanky4][maptankx4]);
            MAP_Global[maptanky4][maptankx4]=0;
            flag=true;
            update();
        }
    }
    else if(control_mode==3)
    {
        if(tankx%60!=0||tanky%60!=0)
        {
            switch(MAP_Global[maptanky1][maptankx1])
            {
            case 20:
                addLife(1);
                MAP_Global[maptanky1][maptankx1]=0;
                flag=true;
                break;
            case 30:
                shield();
                MAP_Global[maptanky1][maptankx1]=0;
                flag=true;
                break;
            case 40:
                attack();
                MAP_Global[maptanky1][maptankx1]=0;
                flag=true;
                break;
            case 50:
                speedUp();
                MAP_Global[maptanky1][maptankx1]=0;
                flag=true;
                break;
            }
            switch(MAP_Global[maptanky2][maptankx2])
            {
            case 20:
                addLife(1);
                MAP_Global[maptanky2][maptankx2]=0;
                flag=true;
                break;
            case 30:
                shield();
                MAP_Global[maptanky2][maptankx2]=0;
                flag=true;
                break;
            case 40:
                attack();
                MAP_Global[maptanky2][maptankx2]=0;
                flag=true;
                break;
            case 50:
                speedUp();
                MAP_Global[maptanky2][maptankx2]=0;
                flag=true;
                break;
            }
            switch(MAP_Global[maptanky3][maptankx3])
            {
            case 20:
                MAP_Global[maptanky3][maptankx3]=0;
                addLife(1);
                flag=true;
                break;
            case 30:
                MAP_Global[maptanky3][maptankx3]=0;
                shield();
                flag=true;
                break;
            case 40:
                MAP_Global[maptanky3][maptankx3]=0;
                attack();
                flag=true;
                break;
            case 50:
                MAP_Global[maptanky3][maptankx3]=0;
                speedUp();
                flag=true;
                break;
            }
            switch(MAP_Global[maptanky4][maptankx4])
            {
            case 20:
                MAP_Global[maptanky4][maptankx4]=0;
                addLife(1);
                flag=true;
                break;
            case 30:
                MAP_Global[maptanky4][maptankx4]=0;
                shield();
                flag=true;
                break;
            case 40:
                MAP_Global[maptanky4][maptankx4]=0;
                attack();
                flag=true;
                break;
            case 50:
                MAP_Global[maptanky4][maptankx4]=0;
                speedUp();
                flag=true;
                break;
            }
        }
    }
    if(flag)
    {
            qDebug()<<"getProp";
            player_prop->setMedia(QUrl(prop_wav));
            player_prop->setVolume(propVolume);
            player_prop->setPosition(0);
            player_prop->play();
    }
    return flag;
}

