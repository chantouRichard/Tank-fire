#include "level1.h"
#include<QKeyEvent>

int level1map[Mapx_size][Mapy_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,1,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,1,1,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,1,2,2,2,2},
    {2,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,1,2,2,2,2,2},
    {2,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,1,2,2,2},
    {2,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,2,2,1,2,2,2},
    {2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,2,2,1,2,2,2},
    {2,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,2,2,2},
    {2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2},
    {2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

level1::level1(QWidget *parent) : Level(parent)
{
    Initmap();
}

void level1::Initmap(){
    loadMap(level1map);
    initTank();
    initEnemyTank();
}

void level1::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}

void level1::paintEvent(QPaintEvent *event) {
    Level::paintEvent(event);
}

void level1::initTank() {
    my_tank=new Tank(60,60,this);
    my_tank->showtank(this);
    my_tank->Loadmap(map);
    my_tank->addbudget();
    for(int i=0;i<bulletsnumber;i++)
    {
    Bullet* it=&my_tank->bugdet[i];
    connect(it,&Bullet::boom,this,&level1::updatemapforboom);
}
}
void level1::Deletetank(){
    my_tank->tank_img->hide();
    enemy1->tank_img->hide();
    enemy2->tank_img->hide();
    enemy3->tank_img->hide();
    delete my_tank;
    delete enemy1;
    delete enemy2;
    delete enemy3;
}
void level1::initEnemyTank() {
    enemy1=new EnemyTank(120,120,this);
    enemy2=new EnemyTank(240,120,this);
    enemy3=new EnemyTank(360,120,this);
    enemy1->Loadmap(map);
    enemy1->showTank(this);

    enemy2->Loadmap(map);
    enemy2->showTank(this);

    enemy3->Loadmap(map);
    enemy3->showTank(this);
    for(int i=0;i<bulletsnumber;i++)
    {
    Bullet* it1=&enemy1->budget[i];
    Bullet* it2=&enemy2->budget[i];
    Bullet* it3=&enemy3->budget[i];
    connect(it1,&Bullet::boom,this,&level1::updatemapforboom);
    connect(it2,&Bullet::boom,this,&level1::updatemapforboom);
    connect(it3,&Bullet::boom,this,&level1::updatemapforboom);
    connect(my_tank,&Tank::move,it1,&enemybullet::updateenemy);
    connect(my_tank,&Tank::move,it2,&enemybullet::updateenemy);
    connect(my_tank,&Tank::move,it3,&enemybullet::updateenemy);
    }
}

void level1::dead() {
    Level::dead();
}
void level1::updatemapforboom(int mapx,int mapy){
    if(map[mapx][mapy]==1)
    {
        map[mapx][mapy]=0;
    }

    this->update();
    my_tank->Loadmap(map);
    enemy1->Loadmap(map);
    enemy2->Loadmap(map);
    enemy3->Loadmap(map);
    for(int i=0;i<bulletsnumber;i++){
        my_tank->bugdet[i].Loadmap(map);
    }
    for(int i=0;i<bulletsnumber;i++){
        enemy1->budget[i].Loadmap(map);
    }
    for(int i=0;i<bulletsnumber;i++){
        enemy2->budget[i].Loadmap(map);
    }
    for(int i=0;i<bulletsnumber;i++){
        enemy3->budget[i].Loadmap(map);
    }
}
