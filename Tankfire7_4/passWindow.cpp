#include "passWindow.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QFontDatabase>
#include <QDebug>
#include<QPushButton>
#include <QWidget>
#include <QPalette>
#include <QBrush>
#include <QPixmap>

pass::pass(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(1600, 1200);
    setWindowTitle("TankFire");

    // 设置背景图片
//    QPalette palette;
//    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/1/Res/res/gameover.jpg").scaled(this->size())));
//    this->setPalette(palette);

    level1* Level1 = new level1;
    level2* Level2 = new level2;
    level3* Level3 = new level3;
    level4* Level4 = new level4;

    // 设置返回按钮
    backbtn = new QPushButton("Back");
    backbtn->setParent(this);
    backbtn->move(10, 10);
    backbtn->resize(100, 50);
    setButtonStyle(backbtn);

    // 设置关卡按钮
    QPushButton *l1btn = new QPushButton("Level 1", this);
    l1btn->resize(160, 80);
    l1btn->move(this->width() / 5 - l1btn->width() / 2, this->height() / 2 - l1btn->height() / 2);
    setButtonStyle(l1btn);

    QPushButton *l2btn = new QPushButton("Level 2", this);
    l2btn->resize(160, 80);
    l2btn->move(this->width() * 2 / 5 - l2btn->width() / 2, this->height() / 2 - l2btn->height() / 2);
    setButtonStyle(l2btn);

    QPushButton *l3btn = new QPushButton("Level 3", this);
    l3btn->resize(160, 80);
    l3btn->move(this->width() * 3 / 5 - l3btn->width() / 2, this->height() / 2 - l3btn->height() / 2);
    setButtonStyle(l3btn);

    QPushButton *l4btn = new QPushButton("Level 4", this);
    l4btn->resize(160, 80);
    l4btn->move(this->width() * 4 / 5 - l4btn->width() / 2, this->height() / 2 - l4btn->height() / 2);
    setButtonStyle(l4btn);

    // 设置字体大小
    QFont font = QFont("Arial", 20);
    backbtn->setFont(font);
    l1btn->setFont(font);
    l2btn->setFont(font);
    l3btn->setFont(font);
    l4btn->setFont(font);

    // 设置按钮为未解锁状态
    l2btn->setEnabled(false);
    l3btn->setEnabled(false);
    l4btn->setEnabled(false);

    // 初始化connect
    setupLevel0Button(l1btn, Level1, l2btn);
    setupLevel1Button(l2btn, Level2, l3btn);
    setupLevel2Button(l3btn, Level3, l4btn);
    setupLevel3Button(l4btn, Level4);

    setColor(l2btn);
    setColor(l3btn);
    setColor(l4btn);

    // 按钮状态设置
    if (pass_judge[0]) {
        l2btn->setEnabled(true);
        colorChange(l2btn);
    }
    if (pass_judge[1]) {
        l3btn->setEnabled(true);
        colorChange(l3btn);
    }
    if (pass_judge[2]) {
        l4btn->setEnabled(true);
        colorChange(l4btn);
    }

    connect(backbtn, &QPushButton::clicked, [=]() {
        QTimer::singleShot(500, this, [=]() {
            emit this->back();
        });
    });
}

void pass::setupLevel0Button(QPushButton *button, level1 *level, QPushButton *nextButton)
{
    connect(button, &QPushButton::clicked, [=]() {
        QTimer::singleShot(500, this, [=]() {
            this->hide();
            level->deletePassPage();
            level->deleteFailPage();
            level->Deletetank();
            level->Initmap();
            level->show();
            for(int i=0;i<level->enemy_num;i++){
                level->enemys[i]->startshoottime();
            }
            connect(level, &level1::Win, [=]() {
                pass_judge[0] = true;
                colorChange(nextButton);
                nextButton->setEnabled(true);
                this->show();
                level->close();
                nextButton->click();
                this->hide();
            });

            connect(level, &level1::back, this, [=]() {
                level->Deletetank();
                level->Initmap();
                this->show();
                level->close();
            });

            connect(level,&level1::backButWin,[=](){
                pass_judge[0] = true;
                colorChange(nextButton);
                nextButton->setEnabled(true);
                this->show();
                level->close();
            });
        });
    });
}

void pass::setupLevel1Button(QPushButton *button, level2 *level, QPushButton *nextButton)
{
    connect(button, &QPushButton::clicked, [=]() {
        QTimer::singleShot(500, this, [=]() {
            this->hide();
            level->deletePassPage();
            level->deleteFailPage();
            level->Deletetank();
            level->Initmap();
            level->show();
            for(int i=0;i<level->enemy_num;i++){
                level->enemys[i]->startshoottime();
            }
            connect(level, &level2::Win, [=]() {
                pass_judge[1] = true;
                colorChange(nextButton);
                nextButton->setEnabled(true);
                this->show();
                level->close();
                nextButton->click();
                this->hide();
            });

            connect(level, &level2::back, this, [=]() {
                level->Deletetank();
                level->Initmap();
                this->show();
                level->hide();
            });
            connect(level,&level2::backButWin,[=](){
                pass_judge[0] = true;
                colorChange(nextButton);
                nextButton->setEnabled(true);
                this->show();
                level->close();
            });
        });
    });
}

void pass::setupLevel2Button(QPushButton *button, level3 *level, QPushButton *nextButton)
{
    connect(button, &QPushButton::clicked, [=]() {
        QTimer::singleShot(500, this, [=]() {
            this->hide();
            level->deletePassPage();
            level->deleteFailPage();
            level->Deletetank();
            level->Initmap();
            level->show();
            for(int i=0;i<level->enemy_num;i++){
                level->enemys[i]->startshoottime();
            }
            connect(level, &level3::Win, [=]() {
                pass_judge[2] = true;
                colorChange(nextButton);
                nextButton->setEnabled(true);
                this->show();
                level->close();
                nextButton->click();
                this->hide();
            });

            connect(level, &level3::back, this, [=]() {
                level->Deletetank();
                level->Initmap();
                this->show();
                level->hide();
            });
            connect(level,&level3::backButWin,[=](){
                pass_judge[0] = true;
                colorChange(nextButton);
                nextButton->setEnabled(true);
                this->show();
                level->close();
            });
        });
    });
}

void pass::setupLevel3Button(QPushButton *button, level4 *level)
{
    connect(button, &QPushButton::clicked, [=]() {
        QTimer::singleShot(500, this, [=]() {
            this->hide();
            level->deletePassPage();
            level->deleteFailPage();
            level->Deletetank();
            level->Initmap();
            level->show();
            for(int i=0;i<level->enemy_num;i++){
                level->enemys[i]->startshoottime();
            }
            connect(level, &level4::Win, [=]() {
                pass_judge[3] = true;
                colorChange(button);
                this->show();
                level->close();
            });

            connect(level, &level4::back, this, [=]() {
                level->Deletetank();
                level->Initmap();
                this->show();
                level->close();
            });
            connect(level,&level4::backButWin,[=](){
                pass_judge[0] = true;
                this->show();
                level->close();
            });
        });
    });
}

void pass::setButtonStyle(QPushButton *btn)
{
    btn->setStyleSheet(
        "QPushButton {"
        "   background-color: #f44336;"
        "   color: white;"
        "   border-radius: 15px;"
        "   padding: 10px 20px;"
        "   font-size: 20px;"
        "   transition: all 0.3s ease;"
        "}"
        "QPushButton:hover {"
        "   background-color: #e57373;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #d32f2f;"
        "   transform: scale(0.95);"
        "}"
    );
}

void pass::colorChange(QPushButton *btn)
{
    btn->setStyleSheet(
        "QPushButton {"
        "   background-color: #f44336;"
        "   color: white;"
        "   border-radius: 15px;"
        "   padding: 10px 20px;"
        "   font-size: 20px;"
        "   transition: all 0.3s ease;"
        "}"
        "QPushButton:hover {"
        "   background-color: #e57373;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #d32f2f;"
        "   transform: scale(0.95);"
        "}"
    );
}

void pass::setColor(QPushButton *btn)
{
    btn->setStyleSheet(
        "QPushButton {"
        "   background-color: lightgrey;"
        "   color: white;"
        "   border-radius: 15px;"
        "   padding: 10px 20px;"
        "   font-size: 20px;"
        "   transition: all 0.3s ease;"
        "}"
        "QPushButton:hover {"
        "   background-color: grey;"
        "}"
        "QPushButton:pressed {"
        "   background-color: lightgrey;"
        "   transform: scale(0.95);"
        "}"
    );
}

pass::~pass()
{
    delete ui;
}
