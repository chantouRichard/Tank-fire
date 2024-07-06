#include "level4.h"
#include "ui_level4.h"
#include<QPushButton>
#include<QTimer>
#include<QPainter>
#include<QBrush>
#include<QString>
#include<QKeyEvent>
#include<QTimer>
#include<QDebug>
#include<queue>
#include<QSound>
#include<vector>
#include"pass.h"

int level4map[25][25]={
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

level4::level4(QWidget *parent):Level(parent){
    // 初始化状态栏
    QLabel* statusBar = new QLabel(this);
    QLabel* statusText = new QLabel(statusBar);

    loadMap(level4map);
    initTank();
    initEnemyTank();
}

level4::~level4() {
    delete ui;
}

void level4::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}

void level4::paintEvent(QPaintEvent *event) {
    Level::paintEvent(event);
}

void level4::initTank() {
    my_tank=new Tank(60,60,this);
    my_tank->showtank(this);
    my_tank->Loadmap(map);
    my_tank->addbudget();
}

void level4::initEnemyTank() {
    enemy1=new EnemyTank(1300,1340,this);
    enemy2=new EnemyTank(1300,1280,this);
    enemy3=new EnemyTank(1300,1160,this);

    enemy1->Loadmap(map);
    enemy1->showTank(this);

    enemy2->Loadmap(map);
    enemy2->showTank(this);

    enemy3->Loadmap(map);
    enemy3->showTank(this);
}

void level4::dead() {
    Level::dead();
}

void level4::Initmap(){
    resetTime();
    loadMap(level4map);

    initTank();
    initEnemyTank();
}

void level4::Deletetank(){
    my_tank->tank_img->hide();
    enemy1->tank_img->hide();
    enemy2->tank_img->hide();
    enemy3->tank_img->hide();
    delete my_tank;
    delete enemy1;
    delete enemy2;
    delete enemy3;
}
void level4::updatemapforboom(int mapx,int mapy)
{
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
