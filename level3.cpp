#include "level3.h"
#include "ui_level3.h"
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

int level3map[14][20]=
{
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};
level3::level3(QWidget *parent)
    : mainlevel(parent), ui(new Ui::level3) {

    ui->setupUi(this);
    loadMap(level3map);
}

level3::~level3() {
    delete ui;
}

void level3::paintEvent(QPaintEvent *event) {
    mainlevel::paintEvent(event);
}

void level3::initTank() {
    mainlevel::initTank();
}

void level3::initEnemyTank() {
    mainlevel::initEnemyTank();
}

void level3::dead() {
    mainlevel::dead();
}
