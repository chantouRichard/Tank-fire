#include "level.h"
#include <QPushButton>
#include <QPainter>
#include <QBrush>
#include <QPixmap>
#include<QPaintEvent>

Level::Level(QWidget *parent)
    : QWidget(parent) {
    setFixedSize(1500, 1500);
    setWindowTitle("tankfire");
    setupUI();
}

Level::~Level() {
    // 清理工作
}

void Level::setupUI() {
    QPushButton *next = new QPushButton("Next level", this);
    next->resize(150, 50);
    next->move(675, 200);

    QPushButton *backbutton = new QPushButton("Back", this);
    backbutton->resize(100, 50);
    backbutton->move(10, 10);

    connect(backbutton, &QPushButton::clicked, [=]() {
        emit this->back();
    });

    connect(next, &QPushButton::clicked, [=]() {
        emit this->Win();
    });
}

void Level::loadMap(int newMap[Mapx_size][Mapy_size]) {
    for (int i = 0; i < Mapx_size; ++i) {
        for (int j = 0; j < Mapy_size; ++j) {
            MAP_Global[i][j] = newMap[i][j];
        }
    }
}

void Level::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush(Qt::black);

    QPixmap pixWall1(":/1/Res/res/wall1.jpg");
    QPixmap pixWall2(":/1/Res/res/wall2.jpg");

    for (int i = 0; i < Mapx_size; ++i) {
        for (int j = 0; j < Mapy_size; ++j) {
            if (MAP_Global[j][i] == 1) {
                painter.drawPixmap(j * 60, i * 60, 60, 60, pixWall1);
            } else if (MAP_Global[j][i] == 2) {
                painter.drawPixmap(j * 60, i * 60, 60, 60, pixWall2);
            }
        }
    }
}

void Level::initTank() {
    // 通用的初始化主坦克的逻辑
}

void Level::initEnemyTank() {
    // 通用的初始化敌人坦克的逻辑
}

void Level::dead() {
    // 通用的判断主坦克死亡的逻辑
}

void Level::updatemapforboom(int mapx,int mapy){
    if(MAP_Global[mapx][mapy]==1)
    {
        MAP_Global[mapx][mapy]=0;
    }

    this->update();
}
