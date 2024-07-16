#include "level3.h"
#include<QKeyEvent>
#include<QPainter>
#include<QRandomGenerator>

const int level3map[Mapy_size][Mapx_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,1,0,0,0,1,0,0,0,2,0,0,0,4,4,0,0,0,1,0,0,1,0,0,0,2},
    {2,0,0,1,0,0,0,1,0,0,0,1,0,0,0,4,4,0,0,0,1,0,0,1,0,0,0,2},
    {2,0,0,1,1,6,6,2,0,0,0,1,0,0,1,0,0,1,0,0,1,1,6,6,0,2,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,2,0,0,1,0,0,1,2,2,1,0,0,6,0,2,0,2},
    {2,0,0,0,0,0,0,0,1,1,2,2,0,0,1,0,0,1,0,0,1,0,0,6,0,2,0,2},
    {2,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,2},
    {2,2,0,1,0,6,6,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,0,0,0,0,0,0,5,5,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,2},
    {2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,6,0,1,0,0,0,0,0,5,5,0,2},
    {2,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,6,0,2,0,0,0,0,0,5,5,0,2},
    {2,0,0,0,0,2,0,0,0,2,0,0,0,0,6,6,6,0,2,0,0,2,2,0,0,0,0,2},
    {2,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2},
    {2,0,2,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2},
    {2,0,2,0,0,0,0,0,2,1,1,1,1,1,0,0,0,0,1,1,0,4,4,1,1,0,0,2},
    {2,0,0,6,6,6,6,0,2,0,0,0,0,1,2,2,1,0,0,2,0,4,4,0,1,0,0,2},
    {2,0,0,1,0,2,2,0,1,0,4,4,0,1,2,2,1,0,0,2,0,0,0,0,1,0,0,2},
    {2,0,0,1,0,0,0,0,1,0,4,4,0,0,0,0,1,0,0,1,0,0,6,6,2,0,0,2},
    {2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,2,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

int initenemyx3[3]={120,240,360};
int initenemyy3[3]={120,120,120};
int my_tankx3=1560;
int my_tanky3=1080;
int frosttankx=60;
int frosttanky=60;

level3::level3(QWidget *parent) : Level(parent)
{

    Initmap();
    show_failpage_show=false;
}

void level3::Initmap(){
    resetTime();
    loadMap(level3map);
    initTank(3,initenemyx3,initenemyy3,my_tankx3,my_tanky3);
    initEnemyTank(3);
//    my_tank->control_mode=2;
}

void level3::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush(Qt::black);
    for (int i = 0; i < Mapy_size; ++i) {
        for (int j = 0; j < Mapx_size; ++j)
        {
            switch(MAP_Global[i][j])
            {
            case 0:
                pixWall=QPixmap(level3_0);
                break;
            case 1:
                pixWall=QPixmap(level3_1);
                break;
            case 2:
                pixWall=QPixmap(level3_2);
                break;
            case 6:
                pixWall=QPixmap(level3_6);
                break;
            case 20:
                pixWall=pixtool1;
                break;
            case 30:
                pixWall=pixtool2;
                break;
            case 40:
                pixWall=pixtool3;
                break;
            case 50:
                pixWall=pixtool4;
                break;
            case 70:
                pixWall=QPixmap(frosted_ground);
                break;
            }
            painter.drawPixmap(j * 60, i * 60, 60, 60,pixWall);
        }
    }
    pixWall=QPixmap(level3_4);
    painter.drawPixmap(900, 60, 120, 120,pixWall);
    painter.drawPixmap(600, 960, 120, 120,pixWall);
    painter.drawPixmap(1260, 840, 120, 120,pixWall);
    pixWall=QPixmap(level3_5);
    painter.drawPixmap(600, 420, 120, 120,pixWall);
    painter.drawPixmap(140, 540, 120, 120,pixWall);
    painter.drawPixmap(24*60,9*60,120,120,pixWall);
}

void level3::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}

void level3::initTank(int enemy_num,int *enemysx,int *enemysy,int my_tankx,int my_tanky) {
    // 通用的初始化主坦克的逻辑

    this->enemy_num=enemy_num;
    enemy_x_site=new int[enemy_num+1];
    enemy_y_site=new int[enemy_num+1];
    for(int i=0;i<enemy_num;i++){
        enemy_x_site[i]=enemysx[i];
        enemy_y_site[i]=enemysy[i];
    }
    enemy_x_site[enemy_num]=frosttankx;
    enemy_x_site[enemy_num]=frosttanky;
    //初始化敌人位置
    my_tank=new Tank(my_tankx,my_tanky,this);
    my_tank->showtank(this);
    connect(my_tank,&Tank::get_prop,this,&Level::HandleGetProp);
    connect(my_tank,&Tank::use_prop,this,&Level::HandleKey);
    connect(my_tank,&Tank::get_prop,[=](){update();});
    connect(my_tank,&Tank::hurt,[=](){
        my_tank->my_tank_live--;
        if(my_tank->my_tank_live<=0)
        {
            my_tank->tank_img->move(-60,-60);
            show_failpage_show=true;
        }
        if(show_failpage_show)
        {
            failPageShow();
            emit pass_fail();
        }
    });
    for(int i=0;i<bulletsnumber;i++)
    {
        Bullet* it=&my_tank->bugdet[i];
        connect(it,&Bullet::boom,this,&Level::updatemapforboom);
        my_tank->bugdet[i].enemy_num=enemy_num+1;
        my_tank->bugdet[i].getenemysit(enemy_x_site,enemy_y_site);
        connect(it,&Bullet::kill_enemy,this,&Level::clear_enemytank);
    }
}

void level3::initEnemyTank(int enemy_num) {
    // 通用的初始化敌人坦克的逻辑
    enemys=new EnemyTank*[enemy_num];
    enemybullet* bul;

    for(int i=0;i<enemy_num;i++)
    {
        enemys[i]=new EnemyTank(enemy_x_site[i],enemy_y_site[i],my_tank,this);
        if(i==1){
            enemys[1]->enemytank_style=2;
        }
        enemys[i]->showTank(this);
        for(int j=0;j<bulletsnumber;j++)
        {
            bul=&enemys[i]->bullets[j];
            connect(bul,&enemybullet::boom,this,&Level::updatemapforboom);
            connect(my_tank,&Tank::my_tank_move,bul,&enemybullet::getenemysit);
            connect(bul,&enemybullet::kill_my_tank,[=](){
                my_tank->my_tank_live--;
                if(my_tank->my_tank_live<=0)
                {
                    my_tank->tank_img->move(-60,-60);
                    show_failpage_show=true;
                }
                if(show_failpage_show)
                {
                    failPageShow();
                    emit pass_fail();
                }
            });
        }
        connect(enemys[i],&EnemyTank::enemy_move,this,&Level::updateenemysit);
    }
    emit my_tank->my_tank_move(my_tank->tankx,my_tank->tanky);


    frosttank=new frostenemy1(120,120,my_tank,this);
    frostbullet* buf;
    frosttank->showTank(this);
    for(int j=0;j<bulletsnumber;j++)
    {
        buf=&frosttank->fbullets[j];
        connect(buf,&frostbullet::boom,this,&Level::updatemapforboom);
        connect(my_tank,&Tank::my_tank_move,buf,&frostbullet::getenemysit);
        connect(buf,&frostbullet::refrosted,this,&Level::updatemapforfrosted);
        connect(buf,&frostbullet::kill_my_tank,[=](){
            my_tank->my_tank_live--;
            if(my_tank->my_tank_live<=0)
            {
                my_tank->tank_img->move(-60,-60);
                show_failpage_show=true;
            }
            if(show_failpage_show)
            {
                failPageShow();
                emit pass_fail();
            }
        });
        connect(buf,&frostbullet::frosted,this,&Level::updatemapforfrosted);
    }
    connect(frosttank,&frostenemy1::enemy_move,this,&level3::updateenemysit);

}

void level3::updateenemysit(){
    for(int i=0;i<enemy_num;i++){
        enemy_x_site[i]=enemys[i]->currentX;
        enemy_y_site[i]=enemys[i]->currentY;
    }
    enemy_x_site[enemy_num]=frosttank->currentX;
    enemy_y_site[enemy_num]=frosttank->currentY;
}

void level3::clear_enemytank(int id){
    if(id<enemy_num){
    if(enemys[id]->enemy_HP==1)
    {
        score+=10;
        enemys[id]->live=0;
        enemys[id]->enemy_tank_img->hide();
        enemys[id]->enemy_tank_img->move(-10,-10);
        enemys[id]->currentX=-10;
        enemys[id]->currentY=-10;
        updateenemysit();
    }
    else
        enemys[id]->enemy_HP--;
    }
    if(id==enemy_num){
    if(frosttank->enemy_HP==1)
    {
        score+=10;
        frosttank->live=0;
        frosttank->enemy_tank_img->hide();
        frosttank->enemy_tank_img->move(-10,-10);
        frosttank->currentX=-10;
        frosttank->currentY=-10;
        updateenemysit();
    }
    else{
        frosttank->enemy_HP--;
    }
    }
    bool check=1;
    for(int i=0;i<enemy_num;i++){
        if(enemys[i]->live){
            check=0;
            break;
        }
    }
    if(frosttank->live){
        check=0;
    }
    if(check)
    {
        emit pass_victory();
        updateTime();
        passPageShow();
    }
}

void level3::Deletetank(){
    my_tank->my_tank_live=0;
    my_tank->tank_img->hide();
    frosttank->enemy_HP=0;
    frosttank->enemy_tank_img->hide();
    frosttank->Deletebullets();
    delete frosttank;
    for(int i=0;i<enemy_num;i++)
    {
        enemys[i]->enemy_tank_img->hide();
        enemys[i]->enemy_HP=0;
        enemys[i]->Deletebullets();
        delete enemys[i];
    }
    delete my_tank;
    delete[] enemys;


}

void level3::hide_all_tank(){
    my_tank->tank_img->move(-100,-100);
    my_tank->tankx=my_tank->tanky=-100;
    for(int i=0;i<bulletsnumber;i++){
        my_tank->bugdet[i].BULA->hide();
        my_tank->bugdet[i].BOOM->hide();
        my_tank->bugdet[i].BULA->move(-10,-10);
    }
    for(int i=0;i<enemy_num;i++)
    {
        enemys[i]->enemy_tank_img->hide();
        enemys[i]->shootTimer->stop();
        for(int j=0;j<bulletsnumber;j++){
            enemys[i]->bullets[j].BULA->hide();
            enemys[i]->bullets[j].BOOM->hide();
            enemys[i]->bullets[j].BULA->move(-100,-100);
            enemys[i]->bullets[j].enemyx=-200;
            enemys[i]->bullets[j].enemyy=-200;
        }

    }
    frosttank->enemy_tank_img->hide();
    frosttank->shootTimer->stop();
    for(int j=0;j<bulletsnumber;j++){
        frosttank->bullets[j].BULA->hide();
        frosttank->bullets[j].BOOM->hide();
        frosttank->bullets[j].BULA->move(-100,-100);
        frosttank->bullets[j].enemyx=-200;
        frosttank->bullets[j].enemyy=-200;
    }

}
