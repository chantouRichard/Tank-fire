#include "tankwindow.h"
#include "ui_tankwindow.h"
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QString>
#include <QDebug>

TankWindow::TankWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TankWindow)
{
    ui->setupUi(this);
    connect(ui->level1btn, &QPushButton::clicked, this, &TankWindow::on_level1Button_clicked);
    connect(ui->endbtn, &QPushButton::clicked, this, &TankWindow::on_endButton_clicked);

    ST1=new QLabel(this);
    ST2=new QLabel(this);
    ST3=new QLabel(this);

    QPixmap star(":/1/tank/star1.png");
    QPixmap restar(":/1/tank/star2.png");
    star1= star.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    star2= restar.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ST1->move(150,150);
    ST1->setFixedSize(100,100);
    ST2->move(175,125);
    ST2->setFixedSize(100,100);
    ST3->move(200,150);
    ST3->setFixedSize(100,100);

    ST1->setPixmap(star1);
    ST2->setPixmap(star1);
    ST3->setPixmap(star1);

    timer = new QTimer(this);
    TimeLabel = new QLabel(this);
    ui->Layout1->addWidget(TimeLabel);
    TimeLabel->show();
    startTime = QTime::currentTime();
    time=0;
}

TankWindow::~TankWindow(){
    delete ui;
}

void TankWindow::on_level1Button_clicked()
{
    startTime = QTime::currentTime();
    timer->start(1000);
}

void TankWindow::on_endButton_clicked()
{
    timer->stop();
    QTime endTime = QTime::currentTime();
    time=startTime.secsTo(endTime);
    updateTimeDisplay();

    if(time<=30)
    {   QTimer *Timer1=new QTimer(this);
        Timer1->start(800);
        int num=1;
        connect(Timer1, &QTimer::timeout, [=]() mutable{
            if(num==4)
                Timer1->stop();
            else
            {
                if(num==1)
                     ST1->setPixmap(star2);
                else if(num==2)
                     ST2->setPixmap(star2);
                else if(num==3)
                     ST3->setPixmap(star2);
                num++;
            }
        });

    }
    else if(time<=60)
    {
        QTimer *Timer1=new QTimer(this);
        Timer1->start(800);
        int n=1;
        connect(Timer1, &QTimer::timeout, [=]() mutable{
            if(n==3)
                Timer1->stop();
            else
            {
                if(n==1)
                    ST1->setPixmap(star2);
                else if(n==2)
                    ST2->setPixmap(star2);
                n++;
            }
        });
    }
    else
    {
        QTimer *Timer1=new QTimer(this);
        Timer1->start(800);
        connect(Timer1, &QTimer::timeout, [=]() mutable{
             ST1->setPixmap(star2);
             Timer1->stop();
        });
    }

}

void TankWindow::updateTimeDisplay()
{
    QTime endTime = QTime::currentTime();
    time=startTime.secsTo(endTime);
    TimeLabel->setText(QString("通关用时: %1 s").arg(time));
}
