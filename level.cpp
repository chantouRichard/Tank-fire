#include "level.h"
#include <QPushButton>
#include <QPainter>
#include <QBrush>
#include <QPixmap>
#include<QPaintEvent>
#include<QRandomGenerator>


Level::Level(QWidget *parent)
    : QWidget(parent) ,score(0){
    statusBar = new QLabel(this);
    statusText = new QLabel(statusBar);
    //通关界面
    setFixedSize(1800, 1500);
    setWindowTitle("tankfire");
    initColumn(statusBar,statusText);
    setupUI();
    show_failpage_show=false;
    passwindowshown=0;
    setedwater=0;
}

void Level::initchangeTimer(){
    qDebug()<<"1  init";
    changeTimer=new QTimer(this);
    changeTimer->disconnect();
    changeTimer->stop();
    changeTimer->start(QRandomGenerator::global()->bounded(5000, 5500));
    connect(changeTimer, &QTimer::timeout, this, &Level::onTimeout);
}

void Level::DeletechangeTimer() {

         qDebug()<<" 1 remove";
            changeTimer->stop();
        changeTimer->disconnect();
        delete changeTimer;
        changeTimer = nullptr; // 将指针设为 nullptr，以防后续访问无效指针

}

// 在其他地方调用 DeletechangTimer 之前，进行检查
Level::~Level() {
    // 清理工作
}

void Level::keyReleaseEvent(QKeyEvent *event){
    my_tank->keyReleaseEvent(event);
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

void Level::initColumn(QLabel* statusBar, QLabel* statusText) {
    // 初始化状态栏
    statusBar->setGeometry(1500, 0, 300, 1500);
    statusBar->setStyleSheet(
        "background-color: black;"
        "border: 10px solid #888888;"
        "border-radius: 20px;"
        "padding: 20px;"
        "box-shadow: 5px 5px 15px rgba(0, 0, 0, 0.5);"
    );

    statusText->setGeometry(0, 0, 300, 800);
    statusText->setStyleSheet(
        "color: white;"
        "font-size: 40px;"
        "font-family: Comic Sans MS, sans-serif;"
        "padding: 10px;"
        "text-align: center;"
    );
    statusText->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    // 初始化计时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        updateTime(statusText);
    });
    startTime = QDateTime::currentDateTime();
    timer->start(1000); // 每秒触发一次 timeout 信号

    // 创建并初始化按钮
    next = new QPushButton("Next", statusBar);
    next->setStyleSheet(
                "color:white;"
                "font-size: 40px;"
                "padding: 10px;"
                "font-family:Comic Sans MS;"
                );
    next->resize(150, 70);
    next->move(75, 1800);

    backbutton = new QPushButton("back", statusBar);
    backbutton->setStyleSheet(
                "color:white;"
                "font-size: 40px;"
                "padding: 10px;"
                "font-family:Comic Sans MS;"
                );
    backbutton->resize(150, 70);
    backbutton->move(75, 1300);

    passButton = new QPushButton("Pass", statusBar);
    passButton->setStyleSheet(
                "color:white;"
                "font-size: 40px;"
                "padding: 10px;"
                "font-family:Comic Sans MS;"
                );
    passButton->resize(150, 70);
    passButton->move(75, 1800);

    failButton=new QPushButton("Fail",statusBar);
    failButton->setStyleSheet(
                "color:white;"
                "font-size: 40px;"
                "padding: 10px;"
                "font-family:Comic Sans MS;"
                );
    failButton->resize(150, 70);
    failButton->move(75, 1800);

    backButWinbutton=new QPushButton("Back",statusBar);
    backButWinbutton->setStyleSheet(
                "color:white;"
                "font-size: 40px;"
                "padding: 10px;"
                "font-family:Comic Sans MS;"
                );
    backButWinbutton->resize(150, 70);
    backButWinbutton->move(75, 1800);

    replay=new QPushButton("Replay",this);
    replay->setStyleSheet(
                "color:white;"
                "font-size: 40px;"
                "padding: 10px;"
                "font-family:Comic Sans MS;"
                );
    replay->resize(150,70);
    replay->move(75,1800);
    //连接部分
    connect(backbutton, &QPushButton::clicked, [=]() {
        emit this->back();
    });

    connect(next, &QPushButton::clicked, [=]() {
        emit this->Win();
    });

    connect(passButton, &QPushButton::clicked, this, &Level::passPageShow);

    connect(failButton,&QPushButton::clicked,this,&Level::failPageShow);

    connect(backButWinbutton,&QPushButton::clicked,[=](){
        emit this->backButWin();
    });
}

void Level::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush(Qt::black);

    QPixmap pixWall1(":/1/Res/res/wall1.jpg");
    QPixmap pixWall2(":/1/Res/res/block.png");
    QPixmap pixtool1(":/1/Res/res/heart.png");
        QPixmap pixtool2(":/1/Res/res/defend.png");
        QPixmap pixtool3(":/1/Res/res/attack.png");
        QPixmap pixtool4(":/1/Res/res/speed.png");

    QPixmap pixmap_block(":/1/Res/res/slots.png");
    QPixmap scaledPixmap = pixmap_block.scaled(60,60, Qt::KeepAspectRatio, Qt::FastTransformation);
    QPixmap Babypig(":/1/Res/res/Baby_pig.png");
    QPixmap scaledPixmappig = Babypig.scaled(60,60, Qt::KeepAspectRatio, Qt::FastTransformation);
    for (int i = 0; i < Mapx_size; ++i) {
        for (int j = 0; j < Mapy_size; ++j) {
            if (MAP_Global[j][i] == 1) {
                painter.drawPixmap(j * 60, i * 60, 60, 60, pixWall1);
            } else if (MAP_Global[j][i] == 2) {
                painter.drawPixmap(j * 60, i * 60, 60, 60, pixWall2);
            }
            else if(MAP_Global[j][i]==0){
                painter.drawPixmap(j * 60, i * 60, 60, 60, scaledPixmap);
            }
            else if(MAP_Global[j][i]==5){
                painter.drawPixmap(j * 60, i * 60, 60, 60, scaledPixmap);
                painter.drawPixmap(j*60,i*60,60,60,scaledPixmappig);
            }
            else if(MAP_Global[j][i]==20){painter.drawPixmap(j*60,i*60,60,60,pixtool1);}
                       else if(MAP_Global[j][i]==30){painter.drawPixmap(j*60,i*60,60,60,pixtool2);}
                       else if(MAP_Global[j][i]==40){painter.drawPixmap(j*60,i*60,60,60,pixtool3);}
                       else if(MAP_Global[j][i]==50){painter.drawPixmap(j*60,i*60,60,60,pixtool4);}
        }
    }
    if(!setedwater){
        watermove->setScaledSize(QSize(60,60));
        watermove->start();
        int k=0;
        for (int i = 0; i < Mapx_size; ++i) {
            for (int j = 0; j < Mapy_size; ++j) {
                if (MAP_Global[j][i] == 3) {
                    k++;
                }
                }
        }
        water=new QLabel*[k];
        for(int i=0;i<k;i++){
            water[i]=new QLabel(this);
            water[i]->setMovie(watermove);
            water[i]->setFixedSize(60,60);
        }
        setedwater=1;
        k=0;
        for (int i = 0; i < Mapx_size; ++i) {
            for (int j = 0; j < Mapy_size; ++j) {
                if (MAP_Global[j][i] == 3) {
                    water[k]->move(j*60,i*60);
                    water[k]->show();
                    k++;
                }
                }
        }
    }
}

void Level::updateTime(QLabel* statusText) {
    QDateTime currentTime = QDateTime::currentDateTime();
    qint64 secondsPassed = startTime.secsTo(currentTime);

    // 更新状态栏文本，显示游戏时间和分数
    int hours = secondsPassed / 3600;
    int minutes = (secondsPassed % 3600) / 60;
    int seconds = secondsPassed % 60;

    QString timeString = QString("%1:%2:%3")
        .arg(hours, 2, 10, QChar('0'))
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'));

    QString text = QString("\n\nTime:\n %1\n\nScore: %2").arg(timeString).arg(score);
    passTime = secondsPassed;

    statusText->setText(text);
}

void Level::initTank(int enemy_num,int *enemysx,int *enemysy,int my_tankx,int my_tanky) {
    // 通用的初始化主坦克的逻辑
    this->enemy_num=enemy_num;
    enemy_x_site=new int[enemy_num];
    enemy_y_site=new int[enemy_num];
    for(int i=0;i<enemy_num;i++){
        enemy_x_site[i]=enemysx[i];
        enemy_y_site[i]=enemysy[i];
    }
    //初始化敌人位置
    my_tank=new Tank(my_tankx,my_tanky,this);
    my_tank->showtank(this);
    my_tank->control_mode=2;
    connect(my_tank,&Tank::get_prop,[=](){
        update();
    });
    for(int i=0;i<bulletsnumber;i++)
    {
        Bullet* it=&my_tank->bugdet[i];
        connect(it,&Bullet::boom,this,&Level::updatemapforboom);
        my_tank->bugdet[i].enemy_num=enemy_num;
        my_tank->bugdet[i].getenemysit(enemy_x_site,enemy_y_site);
        connect(it,&Bullet::kill_enemy,this,&Level::clear_enemytank);
    }
}

void Level::initEnemyTank(int enemy_num) {
    // 通用的初始化敌人坦克的逻辑
    enemys=new EnemyTank*[enemy_num];
    enemybullet* bul;
    for(int i=0;i<enemy_num;i++)
    {
        enemys[i]=new EnemyTank(enemy_x_site[i],enemy_y_site[i],my_tank,this);
        //
        if(i==1){
        enemys[1]->enemytank_style=2;
             }
        //
        enemys[i]->showTank(this);
        for(int j=0;j<bulletsnumber;j++)
        {
            bul=&enemys[i]->bullets[j];
            connect(bul,&enemybullet::boom,this,&Level::updatemapforboom);
            connect(my_tank,&Tank::my_tank_move,bul,&enemybullet::getenemysit);
            connect(bul,&enemybullet::kill_my_tank,[=](){

                my_tank->my_tank_live--;
                if(my_tank->my_tank_live<=0)show_failpage_show=true;
                if(show_failpage_show)
                    failPageShow();
                show_failpage_show=true;
            });
        }
        connect(enemys[i],&EnemyTank::enemy_move,this,&Level::updateenemysit);
    }
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

void Level::Deletetank(){
    my_tank->my_tank_live=0;
    my_tank->tank_img->hide();
    my_tank->Deletebullets();
    my_tank->disconnect();
    for(int i=0;i<enemy_num;i++)
    {
        enemys[i]->enemy_tank_img->hide();
        enemys[i]->enemy_HP=0;
        enemys[i]->Deletebullets();
        delete enemys[i];
    }
    delete my_tank;
    delete[] enemys;
}

void Level::updateenemysit(){
    for(int i=0;i<enemy_num;i++){
        enemy_x_site[i]=enemys[i]->currentX;
        enemy_y_site[i]=enemys[i]->currentY;
    }
}

void Level::clear_enemytank(int id){
    if(enemys[id]->enemy_HP==1){
    score+=10;
    enemys[id]->live=0;
    enemys[id]->enemy_tank_img->hide();
    enemys[id]->enemy_tank_img->move(-10,-10);
    enemys[id]->currentX=-10;
    enemys[id]->currentY=-10;
    updateenemysit();
    }
    else
       enemys[id]->enemy_HP--;
    bool check=1;
    for(int i=0;i<enemy_num;i++){
        if(enemys[i]->live){
            check=0;
        }
    }
    if(check) {
        passPageShow();
        hide_all_tank();
        qDebug()<<"you Win";
}
}

void Level::resetTime() {
    // 重置时间计数为0
    startTime = QDateTime::currentDateTime();
    timer->start();
}

void Level::passPageShow() {
    passwindowshown=1;
    timer->stop();
    //移动按钮
    failButton->move(75,1800);
    next->move(75, 1400);
    backbutton->move(75,1800);
    backButWinbutton->move(75,1300);
    //
    passPage = new QLabel(this); // 确保 passPage 是 QWidget 的实例
    passPage->setGeometry(0, 0, 1500, 1500);
    passPage->setStyleSheet("background-color: white;");
    passPage->setVisible(true);

    QHBoxLayout *layout = new QHBoxLayout(passPage); // 创建布局

    ST1 = new QLabel(passPage);
    ST2 = new QLabel(passPage);
    ST3 = new QLabel(passPage);

    QPixmap star(":/6/Res/res6/star1.png");
    QPixmap restar(":/6/Res/res6/star2.png");
    star1 = star.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    star2 = restar.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ST1->setPixmap(star1);
    ST2->setPixmap(star1);
    ST3->setPixmap(star1);

    layout->addWidget(ST1);
    layout->addWidget(ST2);
    layout->addWidget(ST3);

    passPage->setLayout(layout); // 设置布局

    grade(); // 调用 grade 函数
}

void Level::hide_all_tank(){
    my_tank->tank_img->hide();
    for(int i=0;i<bulletsnumber;i++){
        my_tank->bugdet[i].BULA->hide();
        my_tank->bugdet[i].BOOM->hide();
        my_tank->bugdet[i].bigBOOM->hide();
        my_tank->bugdet[i].BULA->move(-10,-10);
    }
    for(int i=0;i<enemy_num;i++)
    {
        enemys[i]->enemy_tank_img->hide();
        enemys[i]->shootTimer->stop();
        for(int j=0;j<bulletsnumber;j++){
            enemys[i]->bullets[j].BULA->hide();
            enemys[i]->bullets[j].BOOM->hide();
            enemys[i]->bullets[j].bigBOOM->hide();
            enemys[i]->bullets[j].BULA->move(-100,-100);
            enemys[i]->bullets[j].enemyx=-200;
            enemys[i]->bullets[j].enemyy=-200;
        }

    }
}

void Level::failPageShow()
{
    if(passwindowshown) return;
    timer->stop();
    //移动按钮
    passButton->move(75,1800);
    replay->move(75,1400);
    backbutton->move(75,1300);
    //
    failPage = new QLabel(this);
    failPage->setGeometry(0, 0, 1500, 1500);
    failPage->setStyleSheet("background-color: white;");
    failPage->setVisible(true);
    failPage->setStyleSheet("background-color: white; color: red; font-size: 100px; font-family: Comic Sans MS;");
    failPage->setText("你输了，你是傻逼");
    failPage->setAlignment(Qt::AlignCenter);
}

void Level::grade() {
    if(passTime <= 10) {
        QTimer *timer = new QTimer(this);
        int num = 1;
        connect(timer, &QTimer::timeout, [=]() mutable {
            if(num == 4) {
                timer->stop();
            } else {
                if(num == 1) {
                    ST1->setPixmap(star2);
                } else if(num == 2) {
                    ST2->setPixmap(star2);
                } else if(num == 3) {
                    ST3->setPixmap(star2);
                }
                num++;
            }
        });
        timer->start(800);
    } else if(passTime <= 15) {
        QTimer *timer = new QTimer(this);
        int n = 1;
        connect(timer, &QTimer::timeout, [=]() mutable {
            if(n == 3) {
                timer->stop();
            } else {
                if(n == 1) {
                    ST1->setPixmap(star2);
                } else if(n == 2) {
                    ST2->setPixmap(star2);
                }
                n++;
            }
        });
        timer->start(800);
    } else {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [=]() mutable {
            ST1->setPixmap(star2);
            timer->stop();
        });
        timer->start(800);
    }
}

void Level::deletePassPage()
{
    failButton->move(75,1100);
    next->move(75,1800);
    passPage->hide();
    ST1->hide();
    ST2->hide();
    ST3->hide();
    failPage->hide();
}

void Level::deleteFailPage()
{
    next->move(75,1800);
    passButton->move(75,1200);
    replay->move(75,1800);
    failPage->hide();
}

void Level::changeRandomZeroToOne() {
    QVector<QPoint> zeroPositions;
    for (int x = 0; x < Mapx_size; ++x) {
        for (int y = 0; y < Mapy_size; ++y) {
            if (MAP_Global[x][y] == 0) {
                zeroPositions.append(QPoint(x, y));
            }
        }
    }

    if (!zeroPositions.isEmpty()) {
        qDebug()<<"1";
        int randomIndex = QRandomGenerator::global()->bounded(zeroPositions.size());
        QPoint randomPoint = zeroPositions[randomIndex];
        MAP_Global[randomPoint.x()][randomPoint.y()] = (rand()%4+2)*10;
        update();
    }
}

void Level::onTimeout() {
    changeRandomZeroToOne();
//    changeTimer->start(QRandomGenerator::global()->bounded(25000, 25001)); // 重新设置定时器
}
