#include "level4.h"
#include<QKeyEvent>
#include<QPainter>
#include<QRandomGenerator>

const int level4map[Mapy_size][Mapx_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2},
    {2,0,0,0,1,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2},
    {2,0,0,0,1,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2},
    {2,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,2,2,0,0,1,1,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,1,3,3,1,0,0,0,0,2,2,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,1,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,2},
    {3,2,0,0,0,0,0,0,0,0,1,3,3,0,0,3,3,1,0,0,0,0,0,0,0,0,2,3},
    {3,3,2,0,0,0,0,0,0,1,3,3,2,2,2,2,3,3,1,0,0,0,0,0,0,2,3,3},
    {3,3,3,2,0,0,0,0,1,3,3,0,2,2,2,2,0,3,3,1,0,0,0,0,2,3,3,3},
    {3,3,3,2,0,0,0,0,1,3,3,0,2,2,2,2,0,3,3,1,0,0,0,0,2,3,3,3},
    {3,3,2,0,0,0,0,0,0,1,3,3,2,2,2,2,3,3,1,0,0,0,0,0,0,2,3,3},
    {3,2,0,0,0,0,0,0,0,0,1,3,3,0,0,3,3,1,0,0,0,0,0,0,0,0,2,3},
    {2,0,0,0,0,0,0,0,0,0,0,1,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,1,3,3,1,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,2},
    {2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2},
    {2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2},
    {2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};
int initenemyx4[3]={120,240,360};
int initenemyy4[3]={120,120,120};
int my_tankx4=60;
int my_tanky4=60;

level4::level4(QWidget *parent) : Level(parent)
{
    Wave=0;
    ShowNextButton=false;
    loadMap(level4map);
    initTank(3,initenemyx4,initenemyy4,my_tankx4,my_tanky4);
    initEnemyTank(3);
    show_failpage_show=false;
    timer=new QTimer(this);
    show_failpage_show=false;
}

void level4::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush(Qt::black);
    for (int i = 0; i < Mapy_size; ++i) {
        for (int j = 0; j < Mapx_size; ++j)
        {
            switch(MAP_Global[i][j])
            {
            case 0:
                pixWall=QPixmap(level4_0);
                break;
            case 1:
                pixWall=QPixmap(level4_1);
                break;
            case 2:
                pixWall=QPixmap(level4_2);
                break;
            case 3:
                pixWall=QPixmap(level4_3);
                break;
            case 4:
                pixWall=QPixmap(level4_4);
                break;
            case 20:
                pixWall=pixtool1;
                break;
            case 30:
                pixWall=pixtool2;
                break;
            case 40:
                pixWall=pixtool3;
                break;
            case 50:
                pixWall=pixtool4;
                break;
            case 60:
                pixWall=QPixmap(fired_ground);
                break;
            case 70:
                pixWall=QPixmap(frosted_ground);
                break;
            }
            painter.drawPixmap(j * 60, i * 60, 60, 60,pixWall);
        }
    }
    pixWall=QPixmap(level4_5);
    painter.drawPixmap(24*60,1*60,180,180,pixWall);
    painter.drawPixmap(24*60,16*60,180,180,pixWall);
    painter.drawPixmap(1*60,16*60,180,180,pixWall);
    painter.drawPixmap(12*60,8*60,240,240,pixWall);
}


void level4::Initmap(){
    Wave=0;
    resetTime();
    loadMap(level4map);
    score=0;
    initTank(3,initenemyx4,initenemyy4,my_tankx4,my_tanky4);
    initEnemyTank(3);
}

void level4::keyPressEvent(QKeyEvent* event)
{
    my_tank->keyPressEvent(event);
}

void level4::ChangeMapWall()
{
    QVector<QPoint> zeroPositions;
    for (int i = 0; i < Mapy_size; i++)
    {
        for (int j = 0; j < Mapx_size; j++) {
            if (MAP_Global[i][j] == 0) {
                zeroPositions.append(QPoint(i, j));
            }
        }
    }
    if (!zeroPositions.isEmpty())
    {
        int randomIndex = QRandomGenerator::global()->bounded(zeroPositions.size());
        QPoint randomPoint = zeroPositions[randomIndex];
        MAP_Global[randomPoint.x()][randomPoint.y()] = rand()%2+1;
        update();
    }
}

void level4::InitChangeMapTimer()
{
    ChangeMapTimer=new QTimer(this);
    ChangeMapTimer->disconnect();
    ChangeMapTimer->stop();
    ChangeMapTimer->start(QRandomGenerator::global()->bounded(2000, 2500));
    qDebug()<<"TestTest";
    static bool judgeConnect=false;
    qDebug()<<"ChangeMapTimer";
    connect(ChangeMapTimer, &QTimer::timeout, this, &level4::ChangeMapWall);
    judgeConnect=true;
}

void level4::DeleteChangeMapTimer()
{
    ChangeMapTimer->stop();
    ChangeMapTimer->disconnect();
    delete ChangeMapTimer;
    ChangeMapTimer = nullptr;
}

void level4::initTank(int enemy_num, int *enemysx, int *enemysy, int my_tankx, int my_tanky)
{

    this->enemy_num=enemy_num;
    enemy_x_site=new int[enemy_num+1];
    enemy_y_site=new int[enemy_num+1];
    for(int i=0;i<enemy_num;i++){
        enemy_x_site[i]=enemysx[i];
        enemy_y_site[i]=enemysy[i];
    }
    //初始化敌人位置
    enemy_x_site[enemy_num]=0;
    enemy_y_site[enemy_num]=0;
    my_tank=new Tank(my_tankx,my_tanky,this);
    my_tank->showtank(this);
    connect(my_tank,&Tank::get_prop,this,&level4::HandleGetProp);
    connect(my_tank,&Tank::use_prop,this,&level4::HandleKey);
    connect(my_tank,&Tank::get_prop,[=](){update();});
    connect(my_tank,&Tank::hurt,[=](){
        my_tank->my_tank_live--;
        if(my_tank->my_tank_live<=0)
        {
            my_tank->tank_img->move(-60,-60);
            show_failpage_show=true;
        }
        if(show_failpage_show)
        {
            failPageShow();
            emit pass_fail();
        }
    });
    for(int i=0;i<bulletsnumber;i++)
    {
        Bullet* it=&my_tank->bugdet[i];
        connect(it,&Bullet::boom,this,&level4::updatemapforboom);
        my_tank->bugdet[i].enemy_num=enemy_num+1;
        my_tank->bugdet[i].getenemysit(enemy_x_site,enemy_y_site);
        connect(it,&Bullet::kill_enemy,this,&level4::clear_enemytank);
    }



}

void level4::initEnemyTank(int enemy_num) {
    // 通用的初始化敌人坦克的逻辑
    if( Wave==0||Wave==1){
        enemys=new EnemyTank*[enemy_num];
        enemybullet* bul;

        for(int i=0;i<enemy_num;i++)
        {
            enemys[i]=new EnemyTank(enemy_x_site[i],enemy_y_site[i],my_tank,this);
            if(i==1){
                enemys[1]->enemytank_style=2;
            }
            enemys[i]->showTank(this);
            for(int j=0;j<bulletsnumber;j++)
            {
                bul=&enemys[i]->bullets[j];
                connect(bul,&enemybullet::boom,this,&Level::updatemapforboom);
                connect(my_tank,&Tank::my_tank_move,bul,&enemybullet::getenemysit);
                connect(bul,&enemybullet::kill_my_tank,[=](){
                    my_tank->my_tank_live--;
                    show_failpage_show=false;
                    qDebug()<<"FailPageSHow:"<<show_failpage_show;
                    qDebug()<<"Kill:"<<my_tank->my_tank_live;
                    if(my_tank->my_tank_live<=0)
                    {
                        my_tank->tank_img->move(-60,-60);
                        show_failpage_show=true;
                    }
                    if(show_failpage_show)
                    {
                        failPageShow();
                        emit pass_fail();
                    }
                });
            }
            connect(enemys[i],&EnemyTank::enemy_move,this,&Level::updateenemysit);
        }
        emit my_tank->my_tank_move(my_tank->tankx,my_tank->tanky);
        if(Wave==1) enemys[2]->enemy_tank_img->hide();
    }



    else if(Wave==2){
        enemys=new EnemyTank*[enemy_num];
        enemybullet* bul;
        enemy_num=4;
        for(int i=0;i<enemy_num;i++)
        {
            enemy_x_site[i]=240+120*i;
            enemy_y_site[i]=60;
            enemys[i]=new EnemyTank(enemy_x_site[i],enemy_y_site[i],my_tank,this);
            if(i==1){
                enemys[1]->enemytank_style=2;
            }
            enemys[i]->showTank(this);
            for(int j=0;j<bulletsnumber;j++)
            {
                bul=&enemys[i]->bullets[j];
                connect(bul,&enemybullet::boom,this,&Level::updatemapforboom);
                connect(my_tank,&Tank::my_tank_move,bul,&enemybullet::getenemysit);
                connect(bul,&enemybullet::kill_my_tank,[=](){
                    my_tank->my_tank_live--;
                    if(my_tank->my_tank_live<=0)
                    {
                        my_tank->tank_img->move(-60,-60);
                        show_failpage_show=true;
                    }
                    if(show_failpage_show)
                    {
                        failPageShow();
                        emit pass_fail();
                    }
                });
            }
            connect(enemys[i],&EnemyTank::enemy_move,this,&level4::updateenemysit);
        }
        emit my_tank->my_tank_move(my_tank->tankx,my_tank->tanky);


        frosttank=new frostenemy1(120,60,my_tank,this);
        frostbullet* buf;
        frosttank->showTank(this);
        updateenemysit();
        for(int j=0;j<bulletsnumber;j++)
        {
            buf=&frosttank->fbullets[j];
            connect(buf,&frostbullet::boom,this,&Level::updatemapforboom);
            connect(my_tank,&Tank::my_tank_move,buf,&frostbullet::getenemysit);
            connect(buf,&frostbullet::refrosted,this,&Level::updatemapforfrosted);
            connect(buf,&frostbullet::kill_my_tank,[=](){
                my_tank->my_tank_live--;
                if(my_tank->my_tank_live<=0)
                {
                    my_tank->tank_img->move(-60,-60);
                    show_failpage_show=true;
                }
                if(show_failpage_show)
                {
                    failPageShow();
                    emit pass_fail();
                }
            });
            connect(buf,&frostbullet::frosted,this,&Level::updatemapforfrosted);
        }
        connect(frosttank,&frostenemy1::enemy_move,this,&level4::updateenemysit);


    }

    else if(Wave==3){
        enemys=new EnemyTank*[enemy_num];
        enemybullet* bul;
        enemy_num=5;
        for(int i=0;i<enemy_num;i++)
        {
            enemy_x_site[i]=240+120*i;
            enemy_y_site[i]=60;
            enemys[i]=new EnemyTank(enemy_x_site[i],enemy_y_site[i],my_tank,this);
            if(i==1){
                enemys[1]->enemytank_style=2;
            }
            enemys[i]->showTank(this);
            for(int j=0;j<bulletsnumber;j++)
            {
                bul=&enemys[i]->bullets[j];
                connect(bul,&enemybullet::boom,this,&Level::updatemapforboom);
                connect(my_tank,&Tank::my_tank_move,bul,&enemybullet::getenemysit);
                connect(bul,&enemybullet::kill_my_tank,[=](){
                    my_tank->my_tank_live--;
                    if(my_tank->my_tank_live<=0)
                    {
                        my_tank->tank_img->move(-60,-60);
                        show_failpage_show=true;
                    }
                    if(show_failpage_show)
                    {
                        failPageShow();
                        emit pass_fail();
                    }
                });
            }
            connect(enemys[i],&EnemyTank::enemy_move,this,&level4::updateenemysit);
        }
        emit my_tank->my_tank_move(my_tank->tankx,my_tank->tanky);


        fire_tank=new firetank(120,60,my_tank,this);
        firebullet* buf;
        fire_tank->showTank(this);
        for(int j=0;j<bulletsnumber;j++)
        {
            buf=&fire_tank->fbullets[j];
            connect(buf,&firebullet::boom,this,&Level::updatemapforboom);
            connect(my_tank,&Tank::my_tank_move,buf,&firebullet::getenemysit);
            connect(buf,&firebullet::fired,this,&Level::updatemapforfired);
            connect(buf,&firebullet::kill_my_tank,[=](){
                my_tank->my_tank_live--;
                show_failpage_show=false;
                if(my_tank->my_tank_live<=0)
                {
                    my_tank->tank_img->move(-60,-60);
                    show_failpage_show=true;
                }
                if(show_failpage_show)
                {
                    failPageShow();
                    emit pass_fail();
                }
            });

        }
        connect(fire_tank,&firetank::enemy_move,this,&level4::updateenemysit);


    }
}

void level4::Deletetank(){
    if(Wave==0){
        my_tank->my_tank_live=0;
        my_tank->tank_img->hide();
        my_tank->Deletebullets();
        for(int i=0;i<enemy_num;i++)
        {
            if(enemys[i]!=nullptr){
            enemys[i]->enemy_tank_img->hide();
            enemys[i]->enemy_HP=0;
            enemys[i]->Deletebullets();
            delete enemys[i];
            enemys[i]=nullptr;
            }
        }
        delete my_tank;
        delete[] enemys;
    }
    else if(Wave==1){
        my_tank->my_tank_live=0;
        my_tank->tank_img->hide();
        my_tank->Deletebullets();
        for(int i=0;i<enemy_num;i++)
        {
            if(enemys[i]!=nullptr){
                enemys[i]->enemy_tank_img->hide();
                enemys[i]->enemy_HP=0;
                enemys[i]->Deletebullets();
                delete enemys[i];
                enemys[i]=nullptr;
            }
        }
        delete my_tank;
        delete[] enemys;
    }
    else if(Wave==2){
        my_tank->my_tank_live=0;
        my_tank->tank_img->hide();
        my_tank->Deletebullets();
        for(int i=0;i<enemy_num;i++)
        {
            if(enemys[i]!=nullptr){
                enemys[i]->enemy_tank_img->hide();
                enemys[i]->enemy_HP=0;
                enemys[i]->Deletebullets();
                delete enemys[i];
                enemys[i]=nullptr;
            }
        }
        delete my_tank;
        delete[] enemys;
        if(frosttank!=nullptr){
            frosttank->enemy_HP=0;
            frosttank->enemy_tank_img->hide();
            frosttank->Deletebullets();
            delete frosttank;
            frosttank=nullptr;
        }
    }
    else if(Wave==3){
        my_tank->my_tank_live=0;
        my_tank->tank_img->hide();
        my_tank->Deletebullets();
        fire_tank->enemy_HP=0;
        fire_tank->enemy_tank_img->hide();
        fire_tank->Deletebullets();
        delete fire_tank;
        fire_tank=nullptr;
        for(int i=0;i<enemy_num;i++)
        {
            if(enemys[i]!=nullptr){
            enemys[i]->enemy_tank_img->hide();
            enemys[i]->enemy_HP=0;
            enemys[i]->Deletebullets();
            delete enemys[i];
            enemys[i]=nullptr;
            }
        }
        delete my_tank;
        delete[] enemys;
    }
    delete []enemy_x_site;
    delete []enemy_y_site;
    Wave=0;
}
void level4::updateenemysit(){
    if(Wave==1||Wave==0){
        for(int i=0;i<enemy_num;i++){
            enemy_x_site[i]=enemys[i]->currentX;
            enemy_y_site[i]=enemys[i]->currentY;
        }
    }
    else if(Wave==2){
        for(int i=0;i<enemy_num;i++){
            enemy_x_site[i]=enemys[i]->currentX;
            enemy_y_site[i]=enemys[i]->currentY;
        }
        enemy_x_site[enemy_num]=frosttank->currentX;
        enemy_y_site[enemy_num]=frosttank->currentY;

    }
    else if(Wave==3){
        for(int i=0;i<enemy_num;i++){
            enemy_x_site[i]=enemys[i]->currentX;
            enemy_y_site[i]=enemys[i]->currentY;
        }
        enemy_x_site[enemy_num]=fire_tank->currentX;
        enemy_y_site[enemy_num]=fire_tank->currentY;

    }
}
void level4::clear_enemytank(int id)
{
    bool check=1;
    qDebug()<<"Begin!";
    if(Wave==0||Wave==1){
        if(enemys[id]->enemy_HP==1)
        {
            player_boom->setMedia(QUrl(boom_wav));
            player_boom->setVolume(boomVolume);
            player_boom->play();
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
        for(int i=0;i<enemy_num;i++){
            if(enemys[i]->live){
                check=0;
                break;
            }
        }
    }
    else if(Wave==2){
        if(id!=enemy_num){
            if(enemys[id]->enemy_HP==1)
            {
                player_boom->setMedia(QUrl(boom_wav));
                player_boom->setVolume(boomVolume);
                player_boom->play();
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
        }


        else if(id==enemy_num){
            if(frosttank->enemy_HP==1)
            {
                player_boom->setMedia(QUrl(boom_wav));
                player_boom->setVolume(boomVolume);
                player_boom->play();
                score+=10;
                frosttank->live=0;
                frosttank->enemy_tank_img->hide();
                frosttank->enemy_tank_img->move(-10,-10);
                frosttank->currentX=-10;
                frosttank->currentY=-10;
                updateenemysit();
            }
            else
                frosttank->enemy_HP--;
        }

        for(int i=0;i<enemy_num;i++){
            if(enemys[i]->live){
                check=0;
                break;
            }
        }
        if(frosttank->live){
            check=0;
        }
    }

    else if(Wave==3){
        if(id!=enemy_num){
            if(enemys[id]->enemy_HP==1)
            {
                player_boom->setMedia(QUrl(boom_wav));
                player_boom->setVolume(boomVolume);
                player_boom->play();
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
        }


        else if(id==enemy_num){
            if(fire_tank->enemy_HP==1)
            {
                player_boom->setMedia(QUrl(boom_wav));
                player_boom->setVolume(boomVolume);
                player_boom->play();
                score+=10;
                fire_tank->live=0;
                fire_tank->enemy_tank_img->hide();
                fire_tank->enemy_tank_img->move(-10,-10);
                fire_tank->currentX=-10;
                fire_tank->currentY=-10;
                updateenemysit();
            }
            else
                fire_tank->enemy_HP--;
        }

        for(int i=0;i<enemy_num;i++){
            if(enemys[i]->live){
                check=0;
                break;
            }
        }
        if(fire_tank->live){
            check=0;
        }
    }

    if(Wave==3&&check)
    {
        updateTime();
        ShowNextButton=false;
        passPageShow();
    }
    else if(Wave==0&&check)
    {
        for (int i=0;i<3;i++)
        {
            if(enemys[i]!=nullptr){
                enemys[i]->enemy_tank_img->hide();
                enemys[i]->enemy_HP=0;
                enemys[i]->Deletebullets();
                delete enemys[i];
                enemys[i]=nullptr;
            }
        }

//        if(enemys!=nullptr)delete enemys;

        timer->setSingleShot(true); // 设置为单次触发

        connect(timer, &QTimer::timeout, this, [this]() {
            Wave++;
            qDebug() << "Delayed function call after 5 seconds.";
            enemy_x_site[0]=480;enemy_x_site[1]=480;enemy_x_site[2]=480;
            enemy_y_site[0]=120;enemy_y_site[1]=180;enemy_y_site[2]=240;
            initEnemyTank(3);
            for(int i=0;i<enemy_num;i++){
                enemys[i]->startshoottime(5000);
            }
            timer->stop() ;// 定时器触发后删除它自己
            timer->disconnect();
        });

        timer->start(5000); // 5秒后触发
        //        initEnemyTank(3);

        qDebug()<<"Wave:"<<Wave;
    }
    else if(Wave==1&&check)
    {
        for (int i=0;i<3;i++)
        {
            if(enemys[i]!=nullptr){
                enemys[i]->enemy_tank_img->hide();
                enemys[i]->enemy_HP=0;
                enemys[i]->Deletebullets();
                delete enemys[i];
                enemys[i]=nullptr;
            }
        }

//        if(enemys!=nullptr)delete enemys;

        timer->setSingleShot(true); // 设置为单次触发

        connect(timer, &QTimer::timeout, this, [this]() {
            Wave++;
            qDebug() << "Delayed function call after 5 seconds.";
            enemy_x_site[0]=480;enemy_x_site[1]=480;enemy_x_site[2]=480;
            enemy_y_site[0]=120;enemy_y_site[1]=180;enemy_y_site[2]=240;
            initEnemyTank(3);
            for(int i=0;i<enemy_num;i++){
                enemys[i]->startshoottime(5000);
            }
            frosttank->startshoottime();
            timer->stop() ;// 定时器触发后删除它自己
            timer->disconnect();

        });

        timer->start(5000); // 5秒后触发
        //        initEnemyTank(3);

        qDebug()<<"Wave:"<<Wave;
    }
    else if(Wave==2&&check){
        for (int i=0;i<3;i++)
        {
            if(enemys[i]!=nullptr){
                enemys[i]->enemy_tank_img->hide();
                enemys[i]->enemy_HP=0;
                enemys[i]->Deletebullets();
                delete enemys[i];
                enemys[i]=nullptr;
            }
        }

//        if(enemys!=nullptr)delete enemys;
        frosttank->enemy_HP=0;
        frosttank->enemy_tank_img->hide();
        frosttank->Deletebullets();
        delete frosttank;
        frosttank=nullptr;

        timer->setSingleShot(true); // 设置为单次触发

        connect(timer, &QTimer::timeout, this, [this]() {
            Wave++;
            qDebug() << "Delayed function call after 5 seconds.";
            enemy_x_site[0]=480;enemy_x_site[1]=480;enemy_x_site[2]=480;
            enemy_y_site[0]=120;enemy_y_site[1]=180;enemy_y_site[2]=240;
            initEnemyTank(3);
            for(int i=0;i<enemy_num;i++){
                enemys[i]->startshoottime(5000);
            }
            fire_tank->startshoottime();
            timer->stop() ;// 定时器触发后删除它自己
            timer->disconnect();

        });

        timer->start(5000); // 5秒后触发
        //        initEnemyTank(3);

        qDebug()<<"Wave:"<<Wave;
    }
}

void level4::hide_all_tank(){
    my_tank->tank_img->move(-100,-100);
    my_tank->tankx=my_tank->tanky=-100;
    for(int i=0;i<bulletsnumber;i++){
        my_tank->bugdet[i].BULA->hide();
        my_tank->bugdet[i].BOOM->hide();
        my_tank->bugdet[i].BULA->move(-10,-10);
    }
    for(int i=0;i<enemy_num;i++)
    {
        enemys[i]->enemy_tank_img->hide();
        enemys[i]->shootTimer->stop();
        for(int j=0;j<bulletsnumber;j++){
            enemys[i]->bullets[j].BULA->hide();
            enemys[i]->bullets[j].BOOM->hide();
            enemys[i]->bullets[j].BULA->move(-100,-100);
            enemys[i]->bullets[j].enemyx=-200;
            enemys[i]->bullets[j].enemyy=-200;
        }

    }
    if(Wave==2){
    if(frosttank!=nullptr){
        frosttank->enemy_tank_img->hide();
        frosttank->shootTimer->stop();
        for(int j=0;j<bulletsnumber;j++){
            frosttank->fbullets[j].BULA->hide();
            frosttank->fbullets[j].BOOM->hide();
            frosttank->fbullets[j].BULA->move(-100,-100);
            frosttank->fbullets[j].enemyx=-200;
            frosttank->fbullets[j].enemyy=-200;
        }
    }
    }
    else if(Wave==3){
    if(fire_tank!=nullptr){
        fire_tank->enemy_tank_img->hide();
        fire_tank->shootTimer->stop();
        for(int j=0;j<bulletsnumber;j++){
            fire_tank->fbullets[j].BULA->hide();
            fire_tank->fbullets[j].BOOM->hide();
           fire_tank->fbullets[j].BULA->move(-100,-100);
            fire_tank->fbullets[j].enemyx=-200;
            fire_tank->fbullets[j].enemyy=-200;
        }
    }
    }
}
