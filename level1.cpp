#include "level1.h"
#include<QKeyEvent>

int level1map[Mapx_size][Mapy_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
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
    my_tank=new Tank(60,60,this);
    enemy_num=3;
    enemy_x_site=new int[enemy_num];
    enemy_y_site=new int[enemy_num];
    enemy_x_site[0]=120;enemy_x_site[1]=240;enemy_x_site[2]=360;
    enemy_y_site[0]=enemy_y_site[1]=enemy_y_site[2]=120;
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
    for(int i=0;i<enemy_num;i++)
    {
        enemys[i]->enemy_tank_img->hide();
        delete enemys[i];
    }

    delete my_tank;
    delete[] enemys;
}

void level1::initEnemyTank() {

    enemys=new EnemyTank*[enemy_num];
    enemybullet* bul;
    for(int i=0;i<enemy_num;i++)
    {
        enemys[i]=new EnemyTank(enemy_x_site[i],enemy_y_site[i],my_tank,this);
        enemys[i]->Loadmap(map);
        enemys[i]->showTank(this);
        for(int j=0;j<bulletsnumber;j++)
        {
            bul=&enemys[i]->bullets[j];
            connect(bul,&Bullet::boom,this,&level1::updatemapforboom);
        }
    }
}

void level1::dead() {
    Level::dead();
}


