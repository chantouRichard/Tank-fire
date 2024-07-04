#include "passWindow.h"
#include<QPushButton>
#include<QTimer>
#include<QVBoxLayout>
#include<QIcon>
#include<QLabel>
#include<QDebug>

PassWindow::PassWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1200,800);
    setWindowTitle("tankfire");

    QLabel *backgroundLabel = new QLabel(this);

    backgroundLabel->setScaledContents(true); // 这将使图片缩放以填充QLabel的整个区域
    backgroundLabel->resize(this->size()); // 确保QLabel的大小与父窗口或控件相同
    backgroundLabel->setPixmap(QPixmap(":/1/Res/res/gameover.jpg"));

    level1* Level1=new level1;
    level2* Level2=new level2;
    level3* Level3=new level3;
    level4* Level4=new level4;

    //设置按钮
    backbtn=new QPushButton("Back");
    backbtn->setParent(this);
    backbtn->move(10,10);
    backbtn->resize(100,50);

    //


    //level1
    QPushButton * l1btn=new QPushButton("level1",this);
    l1btn->resize(160,80);
    l1btn->move(this->width()/5-l1btn->width()/2,this->height()/2-l1btn->height()/2);
    l1btn->setStyleSheet(
                "QPushButton {"
                "   background-color: red;"
                "   color: white;"
                "   border: none;"
                "   padding: 10px 20px;"
                "}"
                "QPushButton:hover {"
                "   background-color: pink;"
                "}"
                "QPushButton:pressed {"
                "   background-color: red;"
                "}"
                );
    //level2
    QPushButton * l2btn=new QPushButton("level2",this);
    l2btn->resize(160,80);
    l2btn->move(this->width()*2/5-l2btn->width()/2,this->height()/2-l2btn->height()/2);
    setColor(l2btn);
    //level3
    QPushButton * l3btn=new QPushButton("level3",this);
    l3btn->resize(160,80);
    l3btn->move(this->width()*3/5-l3btn->width()/2,this->height()/2-l3btn->height()/2);
    setColor(l3btn);
    //level4
    QPushButton * l4btn=new QPushButton("level4",this);
    l4btn->resize(160,80);
    l4btn->move(this->width()*4/5-l4btn->width()/2,this->height()/2-l4btn->height()/2);
    setColor(l4btn);
    //未解锁显示

    QFont font = backbtn->font();
    QFont font1 = l1btn->font();
    QFont font2 = l2btn->font();
    QFont font3 = l3btn->font();
    QFont font4 = l4btn->font();
    //字体设置
    font.setPointSize(20);
    font1.setPointSize(20);
    font2.setPointSize(20);
    font3.setPointSize(20);
    font4.setPointSize(20);

    //设置成未解锁状态
    l2btn->setEnabled(false);
    l3btn->setEnabled(false);
    l4btn->setEnabled(false);

    //初始化connect
//    setupLevel0Button(l1btn,Level1,l2btn);
//    setupLevel1Button(l2btn,Level2,l3btn);
//    setupLevel2Button(l3btn,Level3,l4btn);
//    setupLevel3Button(l4btn,Level4);
//    //第二关按钮触发
//    if(pass_judge[0])
//    {
//        l2btn->setEnabled(true);
//        colorChange(l2btn);
//    }
//    //第三关按钮触发
//    if(pass_judge[1])
//    {
//        l3btn->setEnabled(true);
//        colorChange(l3btn);
//    }
//    //第四关按钮触发
//    if(pass_judge[2])
//    {
//        l4btn->setEnabled(true);
//        colorChange(l4btn);
//    }

    //按钮的重新配色

}

//void PassWindow::setupLevel0Button(QPushButton *button, level1 *level, QPushButton *nextButton)
//{
//    connect(button,&QPushButton::clicked,[=](){
//        QTimer::singleShot(500,this,[=](){
//            this->hide();
//            level->show();

//            connect(level,&level1::Win,[=](){
//                pass_judge[0]=true;
//                colorChange(nextButton);
//                nextButton->setEnabled(true);
//                this->show();
//                level->close();
//                nextButton->clicked();
//                this->hide();
//            });

//            connect(level,&level1::back,this,[=](){
//                this->show();
//                level->close();
//            });
//        });

//    });
//}

//void PassWindow::setupLevel1Button(QPushButton *button, level2 *level, QPushButton *nextButton)
//{
//    connect(button, &QPushButton::clicked, [=]() {
//        QTimer::singleShot(500, this, [=]() {
//            this->hide();
//            level->show();

//            connect(level, &level2::Win, [=]() {
//                pass_judge[1] = true;
//                colorChange(nextButton);
//                nextButton->setEnabled(true);
//                this->show();
//                level->close();
//                nextButton->click();
//                this->hide();
//            });

//            connect(level, &level2::back, this, [=]() {
//                this->show();
//                level->hide();
//            });
//        });
//    });
//}

//void PassWindow::setupLevel2Button(QPushButton *button, level3 *level, QPushButton *nextButton)
//{
//    connect(button, &QPushButton::clicked, [=]() {
//        QTimer::singleShot(500, this, [=]() {
//            this->hide();
//            level->show();

//            connect(level, &level3::Win, [=]() {
//                pass_judge[2] = true;
//                colorChange(nextButton);
//                nextButton->setEnabled(true);
//                this->show();
//                level->close();
//                nextButton->click();
//                this->hide();
//            });

//            connect(level, &level3::back, this, [=]() {
//                this->show();
//                level->hide();
//            });
//        });
//    });
//}

//void PassWindow::setupLevel3Button(QPushButton *button, level4 *level)
//{
//    connect(button,&QPushButton::clicked,[=](){
//        QTimer::singleShot(500,this,[=](){
//            this->hide();
//            level->show();

//            connect(level,&level4::Win,[=](){
//                pass_judge[3]=true;
//                colorChange(button);
//                this->show();
//                level->close();

//            });

//            connect(level,&level4::back,this,[=](){
//                this->show();
//                level->close();
//            });
//        });

//    });
//}

void PassWindow::setColor(QPushButton * btn)
{
    btn->setStyleSheet(
                "QPushButton {"
                "   background-color: lightgrey;"
                "   color: white;"
                "   border: none;"
                "   padding: 10px 20px;"
                "}"
                "QPushButton:hover {"
                "   background-color: grey;"
                "}"
                "QPushButton:pressed {"
                "   background-color: lightgrey;"
                "}"
                );
}

void PassWindow::colorChange(QPushButton * btn)
{

    btn->setStyleSheet(
                "QPushButton {"
                "   background-color: red;"
                "   color: white;"
                "   border: none;"
                "   padding: 10px 20px;"
                "}"
                "QPushButton:hover {"
                "   background-color: pink;"
                "}"
                "QPushButton:pressed {"
                "   background-color: red;"
                "}"
                );
}

