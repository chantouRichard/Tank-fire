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
    {
        ST1->setPixmap(star2);
        ST2->setPixmap(star2);
        ST3->setPixmap(star2);
    }
    else if(time<=60)
    {
        ST1->setPixmap(star2);
        ST2->setPixmap(star2);
    }
    else
    {
        ST1->setPixmap(star2);
    }

}

void TankWindow::updateTimeDisplay()
{
    QTime endTime = QTime::currentTime();
    time=startTime.secsTo(endTime);
    TimeLabel->setText(QString("通关用时: %1 s").arg(time));
}
