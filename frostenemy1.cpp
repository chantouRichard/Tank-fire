#include "frostenemy1.h"

frostenemy1::frostenemy1(int startX, int startY, Tank*& playerTank,QWidget* parent):EnemyTank(startX,startY,playerTank,parent)
{

}


void frostenemy1::showTank(QWidget*pa)
{

    //    QPixmap scaledPixmap = Enemy_Tank.scaled(60,60, Qt::KeepAspectRatio, Qt::FastTransformation);
    enemy_HP=3;
    enemy_tank_img->setParent(pa);
    Enemy_Tank.load(FrostEnemyUp);
    Enemy_Tank=Enemy_Tank.scaled(60,60);
    enemy_tank_img->setPixmap(Enemy_Tank);
    enemy_tank_img->move(currentX,currentY);
    //设置坦克图片始终在顶部
    enemy_tank_img->show();
    enemy_tank_img->setWindowFlags(enemy_tank_img->windowFlags() | Qt::WindowStaysOnTopHint);

    moveTimer = new QTimer(this);
    moveTimer->start(50);
    connect(moveTimer, &QTimer::timeout, this, &frostenemy1::updatePosition);

    pauseTimer = new QTimer(this);
    connect(pauseTimer, &QTimer::timeout, this, &frostenemy1::resumeMovement);
    srand(static_cast<unsigned>(time(0)));
}


void frostenemy1::updatePosition()
{
    if(!live) return;
    if (isPaused) return;
    if (moveCounter >= maxMoveSteps) {
        chooseNewDirection_smarter();
        moveCounter = 0;
        return;
    } else {
        moveCounter++;
    }
    updatemapsit();
    int stepSize = 5; // 设置步长
    switch (angle) {
    case 0: // Up
        if (!irremovable())
            currentY -= stepSize;
        Enemy_Tank.load(FrostEnemyUp);
        Enemy_Tank=Enemy_Tank.scaled(60,60);
        enemy_tank_img->setPixmap(Enemy_Tank);
        enemy_tank_img->move(currentX,currentY);
        break;
    case 90: // Right
        if (!irremovable()) currentX += stepSize;
        Enemy_Tank.load(FrostEnemyRight);
        Enemy_Tank=Enemy_Tank.scaled(60,60);
        enemy_tank_img->setPixmap(Enemy_Tank);
        enemy_tank_img->move(currentX,currentY);
        break;
    case 180: // Down
        if (!irremovable()) currentY += stepSize;
        Enemy_Tank.load(FrostEnemyDown);
        Enemy_Tank=Enemy_Tank.scaled(60,60);
        enemy_tank_img->setPixmap(Enemy_Tank);
        enemy_tank_img->move(currentX,currentY);
        break;
    case 270: // Left
        if (!irremovable()) currentX -= stepSize;
        Enemy_Tank.load(FrostEnemyLeft);
        Enemy_Tank=Enemy_Tank.scaled(60,60);
        enemy_tank_img->setPixmap(Enemy_Tank);
        enemy_tank_img->move(currentX,currentY);
        break;
    }
    if (rand() % 100 == 0) { // 5%的概率暂停
        isPaused = true;
        pauseTimer->start(500); // 暂停1秒
    }
    emit enemy_move();
}

void frostenemy1::resumeMovement()
{
    isPaused = false;
    pauseTimer->stop();
}

void frostenemy1::shoot(){
    if(!live) return;
    if(angle==0)
        type=1;
    else if(angle==90)
        type=4;
    else if(angle==180)
        type=2;
    else if(angle==270)
        type=3;

    idx++;
    if(idx<=bulletsnumber-1)
        fbullets[idx].movebullet(this->parentWidget(),this->type,currentX,currentY);
    else
    {
        if(idx<2*bulletsnumber){
            fbullets[idx-bulletsnumber].Disconnected();
            fbullets[idx-bulletsnumber].movebullet(this->parentWidget(),this->type,currentX,currentY);
        }
        else
        {
            idx=bulletsnumber;
            fbullets[idx-bulletsnumber].Disconnected();
            fbullets[idx-bulletsnumber].movebullet(this->parentWidget(),this->type,currentX,currentY);
        }

    }
}
void  frostenemy1::startshoottime(){
    shootTimer->start(5000);
    connect(shootTimer,&QTimer::timeout,this,&frostenemy1::shoot);
}
