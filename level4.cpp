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

int level4map[14][20]=
{
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};
level4::level4(QWidget *parent)
    : mainlevel(parent), ui(new Ui::level4) {

    ui->setupUi(this);
    loadMap(level4map);
}

level4::~level4() {
    delete ui;
}
void level4::paintEvent(QPaintEvent *event) {
    mainlevel::paintEvent(event);
}

void level4::initTank() {
    mainlevel::initTank();
}

void level4::initEnemyTank() {
    mainlevel::initEnemyTank();
}

void level4::dead() {
    mainlevel::dead();
}
