#include "level2.h"
#include "ui_level2.h"
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

int level2map[14][20]=
{
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};
level2::level2(QWidget *parent)
    : mainlevel(parent), ui(new Ui::level2) {

    ui->setupUi(this);
    loadMap(level2map);
}

level2::~level2() {
    delete ui;
}

void level2::paintEvent(QPaintEvent *event) {
    mainlevel::paintEvent(event);
}

void level2::initTank() {
    mainlevel::initTank();
}

void level2::initEnemyTank() {
    mainlevel::initEnemyTank();
}

void level2::dead() {
    mainlevel::dead();
}
