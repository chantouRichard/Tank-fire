#include "passWindow.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include <QPushButton>
#include<QApplication>
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
#include<QMovie>
#include<QFontDatabase>

PassWindow::PassWindow(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(2000, 1200);
    setWindowTitle("TankFire");
    // 设置背景图片
    QLabel *backgroundLabel = new QLabel(this);
    QPixmap pixmap(pass_page_pic);
    backgroundLabel->setPixmap(pixmap);
    backgroundLabel->setScaledContents(true);  // 使图片适应标签大小
    backgroundLabel->resize(this->size());    // 使标签大小适应窗口大小
    //Test
    movie1=new QMovie(":/6/Res/res6/test1.gif");
    movie2=new QMovie(":/6/Res/res6/gif2.gif");
    movie3=new QMovie(":/6/Res/res6/gif3.gif");
    movie4=new QMovie(":/6/Res/res6/gif4.gif");
    QSize gifSize(900,600);
    movie1->setScaledSize(gifSize);
    movie2->setScaledSize(gifSize);
    movie3->setScaledSize(gifSize);
    movie4->setScaledSize(gifSize);
    // 创建按钮

    // 创建 QLabel 用于显示 GIF 动画
    gifLabel1 = new QLabel(this);
    gifLabel2 = new QLabel(this);
    gifLabel3 = new QLabel(this);
    gifLabel4 = new QLabel(this);
    gifLabel1->setMovie(movie1);
    gifLabel2->setMovie(movie2);
    gifLabel3->setMovie(movie3);
    gifLabel4->setMovie(movie4);
    gifLabel1->setGeometry(1100, 100, 1200, 1000); // 设置GIF标签的位置和大小
    gifLabel2->setGeometry(1100, 100, 1200, 1000);
    gifLabel3->setGeometry(1100, 100, 1200, 1000);
    gifLabel4->setGeometry(1100, 100, 1200, 1000);
    gifLabel1->hide(); // 初始隐藏标签
    gifLabel2->hide();
    gifLabel3->hide();
    gifLabel4->hide();


    //Test

    level1* Level1 = new level1;
    level2* Level2 = new level2;
    level3* Level3 = new level3;
    level4* Level4 = new level4;

    // 设置返回按钮
    backbtn = new transimplebutton("返回主界面");
    backbtn->setParent(this);
    backbtn->move(60, 850);
    backbtn->resize(400, 60);
    setButtonStyle(backbtn);
    //选择关卡按钮（新的）
    l1New=new transimplebutton("关卡一",this);
    l2New=new transimplebutton("关卡二",this);
    l3New=new transimplebutton("关卡三",this);
    l4New=new transimplebutton("关卡四",this);
    l1New->resize(400,80);
    l2New->resize(400,80);
    l3New->resize(400,80);
    l4New->resize(400,80);
    l1New->move(60,200);
    l2New->move(60,360);
    l3New->move(60,520);
    l4New->move(60,680);
    setButtonStyle(l1New);
    setButtonStyle(l2New);
    setButtonStyle(l3New);
    setButtonStyle(l4New);

    // 设置关卡按钮
    l1btn = new HoverFillButton("开始第一关", this);
    l1btn->resize(300, 70);
    StartButtonStyle(l1btn);

    l2btn = new HoverFillButton("开始第二关", this);
    l2btn->resize(300, 70);
    StartButtonStyle(l2btn);

    l3btn = new HoverFillButton("开始第三关", this);
    l3btn->resize(300, 70);
    StartButtonStyle(l3btn);

    l4btn = new HoverFillButton("开始第四关", this);
    l4btn->resize(300, 70);
    StartButtonStyle(l4btn);

    // 设置按钮为未解锁状态
    l2btn->setEnabled(false);
    l3btn->setEnabled(false);
    l4btn->setEnabled(false);
    l2New->setEnabled(false);
    l3New->setEnabled(false);
    l4New->setEnabled(false);

    // 初始化connect
    setupLevel0Button(l1btn, Level1, l2btn,l2New);
    setupLevel1Button(l2btn, Level2, l3btn,l3New);
    setupLevel2Button(l3btn, Level3, l4btn,l4New);
    setupLevel3Button(l4btn, Level4);

//    setColor(l2New);
//    setColor(l3New);
//    setColor(l4New);

    // 按钮状态设置
//    if (pass_judge[0]) {
//        l2btn->setEnabled(true);
//        colorChange(l2btn);
//    }
//    if (pass_judge[1]) {
//        l3btn->setEnabled(true);
//        colorChange(l3btn);
//    }
//    if (pass_judge[2]) {
//        l4btn->setEnabled(true);
//        colorChange(l4btn);
//    }
    //先隐藏所有下一关按钮
    HideAllButton();

    connect(backbtn, &QPushButton::clicked, [=]() {
        QTimer::singleShot(500, this, [=]() {
            emit this->back();
        });
    });
    connect(l1New,&QPushButton::clicked,[=]{
        HideAllGif();
        HideAllButton();
        playGif(movie1,gifLabel1);
        l1btn->move(1600,1000);
    });
    connect(l2New,&QPushButton::clicked,[=]{
        HideAllGif();
        HideAllButton();
        playGif(movie2,gifLabel2);
        l2btn->move(1600,1000);
        qDebug()<<"movie2";
    });
    connect(l3New,&QPushButton::clicked,[=]{
        HideAllGif();
        HideAllButton();
        playGif(movie3,gifLabel3);
        l3btn->move(1600,1000);
        qDebug()<<"movie3";
    });
    connect(l4New,&QPushButton::clicked,[=]{
        HideAllGif();
        HideAllButton();
        playGif(movie4,gifLabel4);
        l4btn->move(1600,1000);
    });
}

void PassWindow::setupLevel0Button(QPushButton *button, level1 *level, QPushButton *nextButton,QPushButton *nextNew)
{
    static bool isConnected1 = false;

    connect(button, &QPushButton::clicked, [=]() {
            this->hide();
            level->deletePassPage();
            level->deleteFailPage();
            level->Deletetank();
            level->Initmap();
            level->initchangeTimer();
            level->show();
//            for(int i=0; i<level->enemy_num; i++) {
//                level->enemys[i]->startshoottime();
//            }

            if(!isConnected1)
                connect(level, &level1::Win, [=]() {
                    pass_judge[0] = true;
                    qDebug() << "level1 Timer:" << level->changeTimer << "???";
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                        qDebug() << "level1 Timer:" << level->changeTimer;
                    }



//                    colorChange(nextNew);
                    nextButton->setEnabled(true);
                    nextNew->setEnabled(true);
                    this->show();
                    level->close();
                    nextButton->click();
                    this->hide();
                });
                connect(level, &level1::back, this, [=]() {


                    level->Deletetank();
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }
                    level->Initmap();
                    this->show();
                    level->close();
                });

                connect(level, &level1::backButWin, [=]() {
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }
                    pass_judge[0] = true;

//                    colorChange(nextNew);
                    nextButton->setEnabled(true);
                    nextNew->setEnabled(true);
                    this->show();
                    level->close();
                });

                connect(level, &level1::Replay, [=]() {
                    this->show();
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }
                    level->deleteFailPage();
                    level->close();
                    button->clicked();
                    this->hide();
                });

                isConnected1 = true;

        });
}

void PassWindow::setupLevel1Button(QPushButton *button, level2 *level, QPushButton *nextButton,QPushButton *nextNew)
{
    static bool isConnected2 = false;

    connect(button, &QPushButton::clicked, [=]() {
            this->hide();
            level->deletePassPage();
            level->deleteFailPage();
            level->Deletetank();
            level->Initmap();
            level->initchangeTimer();
            level->show();
//            for(int i=0; i<level->enemy_num; i++) {
//                level->enemys[i]->startshoottime();
//            }

            if (!isConnected2) {
                connect(level, &level2::Win, [=]() {
                    pass_judge[1] = true;
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }

//                    colorChange(nextNew);
                    nextButton->setEnabled(true);
                    nextNew->setEnabled(true);
                    this->show();
                    level->close();
                    nextButton->click();
                    this->hide();
                });

                connect(level, &level2::back, this, [=]() {

                    level->Deletetank();
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }
                    level->Initmap();
                    this->show();
                    level->close();
                });

                connect(level, &level2::backButWin, [=]() {
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }
                    pass_judge[1] = true;
//                    colorChange(nextNew);
                    nextButton->setEnabled(true);
                    nextNew->setEnabled(true);
                    this->show();
                    level->close();
                });

                connect(level, &level2::Replay, [=]() {
                    this->show();
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }
                    level->deleteFailPage();
                    level->close();
                    button->clicked();
                    this->hide();
                });

                isConnected2 = true;
            }
        });
}

void PassWindow::setupLevel2Button(QPushButton *button, level3 *level, QPushButton *nextButton,QPushButton *nextNew)
{
    static bool isConnected3 = false;

    connect(button, &QPushButton::clicked, [=]() {
            this->hide();
            level->deletePassPage();
            level->deleteFailPage();
            level->Deletetank();
            level->Initmap();
            level->initchangeTimer();
            level->show();
//            for(int i=0; i<level->enemy_num; i++) {
//                level->enemys[i]->startshoottime();
//            }

            if (!isConnected3) {
                connect(level, &level3::Win, [=]() {
                    pass_judge[2] = true;
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }

//                    colorChange(nextNew);
                    nextButton->setEnabled(true);
                    nextNew->setEnabled(true);
                    this->show();
                    level->close();
                    nextButton->click();
                    this->hide();
                });

                connect(level, &level3::back, this, [=]() {

                    level->Deletetank();
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }
                    level->Initmap();
                    this->show();
                    level->close();
                });

                connect(level, &level3::backButWin, [=]() {
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }
                    pass_judge[2] = true;

//                    colorChange(nextNew);
                    nextButton->setEnabled(true);
                    nextNew->setEnabled(true);
                    this->show();
                    level->close();
                });

                connect(level, &level3::Replay, [=]() {
                    this->show();
                    if (level->changeTimer) {
                        level->DeletechangTimer();
                    }
                    level->deleteFailPage();
                    level->close();
                    button->clicked();
                    this->hide();
                });

                isConnected3 = true;
            }
        });
}

void PassWindow::setupLevel3Button(QPushButton *button, level4 *level)
{
    static bool isConnected4=false;
    connect(button, &QPushButton::clicked, [=]() {
            this->hide();
            level->deletePassPage();
            level->deleteFailPage();
            level->Deletetank();
            level->Initmap();
            level->initchangeTimer();
            level->show();
//            for(int i=0;i<level->enemy_num;i++){
//                level->enemys[i]->startshoottime();
//            }
            if(!isConnected4)
            {
                connect(level, &level4::Win, [=]() {
                    pass_judge[3] = true;
                    qDebug()<<"level4 Timer:"<<level->changeTimer;
                    if (level->changeTimer)
                    {
                        level->DeletechangTimer();
                        qDebug()<<"level4 Timer:"<<level->changeTimer;
                    }
                    this->show();
                    level->close();
                });

                connect(level, &level4::back, this, [=]() {
                    level->Deletetank();
                    if (level->changeTimer)
                    {
                        level->DeletechangTimer();
                    }
                    level->Initmap();
                    this->show();
                    level->close();
                });
                connect(level,&level4::backButWin,[=](){
                    pass_judge[0] = true;
                    this->show();
                    if (level->changeTimer)
                    {
                        level->DeletechangTimer();
                    }
                    level->close();
                });
                connect(level,&level4::Replay,[=]{
                    this->show();
                    if (level->changeTimer)
                    {
                        level->DeletechangTimer();
                    }
                    level->deleteFailPage();
                    level->close();
                    button->clicked();
                    this->hide();
                });
                isConnected4=true;
            }
        });
}

void PassWindow::setButtonStyle(transimplebutton*& btn)
{
    int fontId = QFontDatabase::addApplicationFont(Ink);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 28);
    customFont.setBold(true);
    btn->setAnimationType(transimplebutton::AnimationType::DiagonalRectangle);
    btn->setFillTime(500);
    btn->setFillBrush(QBrush(QColor("#141822")));
    btn->setTextColor(QColor("#312F3B"), QColor("#FFFBF1"));
    btn->setRadius(0);
    btn->setFont(customFont);
}

void PassWindow::StartButtonStyle(HoverFillButton *button)
{
    int fontId = QFontDatabase::addApplicationFont(Ink);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily,20);

    button->setFillTime(300);
    button->setFillBrush(QBrush(QColor("#A39A7C")));
    button->setTextColor(QColor("#141822"), QColor("#312F3B"));
    button->setRadius(30);
    button->setFont(customFont);
}

//void PassWindow::colorChange(QPushButton *btn)
//{
////    btn->setStyleSheet(
////        "QPushButton {"
////        "   background-color: #f44336;"
////        "   color: white;"
////        "   border-radius: 15px;"
////        "   padding: 10px 20px;"
////        "   font-size: 20px;"
////        "   transition: all 0.3s ease;"
////        "}"
////        "QPushButton:hover {"
////        "   background-color: #e57373;"
////        "}"
////        "QPushButton:pressed {"
////        "   background-color: #d32f2f;"
////        "   transform: scale(0.95);"
////        "}"
////    );
//    btn->setStyleSheet(
//        "QPushButton {"
//        "   background-color: transparent;"
//        "   color: black;"
//        "   border: none;"
//        "   padding: 10px 20px;"
//        "}"
//        "QPushButton:hover {"
//        "   border-top: 4px solid white;"    // 上侧描边变粗为4像素
//        "   border-bottom: 4px solid white;" // 下侧描边变粗为4像素
//        "}"
//        "QPushButton:pressed {"
//        "   background-color: black;"
//        "   color: white;"
//        "}"
//    );
//}

//void PassWindow::setColor(QPushButton *btn)
//{
////    btn->setStyleSheet(
////        "QPushButton {"
////        "   background-color: lightgrey;"
////        "   color: white;"
////        "   border-radius: 15px;"
////        "   padding: 10px 20px;"
////        "   font-size: 20px;"
////        "   transition: all 0.3s ease;"
////        "}"
////        "QPushButton:hover {"
////        "   background-color: grey;"
////        "}"
////        "QPushButton:pressed {"
////        "   background-color: lightgrey;"
////        "   transform: scale(0.95);"
////        "}"
////    );
//    btn->setStyleSheet(
//        "QPushButton {"
//        "   background-color: transparent;"
//        "   color: black;"
//        "   border: none;"
//        "   padding: 10px 20px;"
//        "}"
//        "QPushButton:hover {"
//        "   border-top: 4px solid white;"    // 上侧描边变粗为4像素
//        "   border-bottom: 4px solid white;" // 下侧描边变粗为4像素
//        "}"
//        "QPushButton:pressed {"
//        "   background-color: black;"
//        "   color: white;"
//        "}"
//    );
//}

void PassWindow::playGif(QMovie *movie,QLabel *gifLabel)
{
    gifLabel->show(); // 显示标签
    movie->start();
//     连接 movie 的 finished() 信号到 stopGif() 槽函数
    connect(movie, &QMovie::frameChanged,[=]{
        checkFrame(movie);
    });
}

void PassWindow::checkFrame(QMovie *movie)
{
    int frameNumber=movie->currentFrameNumber();
    if (frameNumber == movie->frameCount() - 1) {
        movie->stop();
    }
}

void PassWindow::HideAllGif()
{
    gifLabel1->hide();
    gifLabel2->hide();
    gifLabel3->hide();
    gifLabel4->hide();
}

void PassWindow::HideAllButton()
{
    l1btn->move(0,-300);
    l2btn->move(0,-300);
    l3btn->move(0,-300);
    l4btn->move(0,-300);
}



PassWindow::~PassWindow()
{

}
