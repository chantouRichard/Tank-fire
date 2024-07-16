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
#include <QFile>
#include <QTextStream>

PassWindow::PassWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(2000, 1200);
    setWindowTitle("TankFire");

    is_main_music_play=false;
    player_background->setMedia(QUrl(main_wav));
    player_background->setVolume(gameVolume);

    // 设置背景图片
    QLabel *backgroundLabel = new QLabel(this);
    QPixmap pixmap(pass_page_pic);
    backgroundLabel->setPixmap(pixmap);
    backgroundLabel->setScaledContents(true);  // 使图片适应标签大小
    backgroundLabel->resize(this->size());    // 使标签大小适应窗口大小
    //Test
    movie1=new QMovie(pass_ground1_gif);
    movie2=new QMovie(pass_ground2_gif);
    movie3=new QMovie(pass_ground3_gif);
    movie4=new QMovie(pass_ground4_gif);
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
    gifLabel1->setGeometry(800, 50, 1300, 800); // 设置GIF标签的位置和大小
    gifLabel2->setGeometry(800, 50, 1300, 800);
    gifLabel3->setGeometry(800, 50, 1300, 800);
    gifLabel4->setGeometry(800, 50, 1300, 800);
    gifLabel1->hide(); // 初始隐藏标签
    gifLabel2->hide();
    gifLabel3->hide();
    gifLabel4->hide();

    GameLine=new QLabel(this);
    GameLine->resize(400,600);
    GameLine->move(640,50);
    GameLine->setText("");
    GameLine->setAlignment(Qt::AlignCenter|Qt::AlignTop);
    GameLine->setStyleSheet("background: transparent; color: white; font-size: 36px;");
    GameLine->setWordWrap(true);

    BackGround=new QLabel(this);
    BackGround->resize(800,400);
    BackGround->move(700,850);
    BackGround->setText("");
    BackGround->setStyleSheet("background: transparent; color: white; font-size: 40px;");
    BackGround->setWordWrap(true);
    int fontId1 = QFontDatabase::addApplicationFont(Free);
    QString fontFamily1 = QFontDatabase::applicationFontFamilies(fontId1).at(0);
    QFont customFont1(fontFamily1,30);
    customFont1.setBold(true);
    BackGround->setFont(customFont1);
    //Test

    level2* Level2 = new level2;
    level3* Level3 = new level3;
    level4* Level4 = new level4;
    level1* Level1 = new level1;

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
    l1btn->resize(300, 80);
    StartButtonStyle(l1btn);

    l2btn = new HoverFillButton("开始第二关", this);
    l2btn->resize(300, 80);
    StartButtonStyle(l2btn);

    l3btn = new HoverFillButton("开始第三关", this);
    l3btn->resize(300, 80);
    StartButtonStyle(l3btn);

    l4btn = new HoverFillButton("开始第四关", this);
    l4btn->resize(300, 80);
    StartButtonStyle(l4btn);

    // 设置按钮为未解锁状态
    l2btn->setEnabled(true);
    l3btn->setEnabled(true);
    l4btn->setEnabled(true);
    l2New->setEnabled(true);
    l3New->setEnabled(true);
    l4New->setEnabled(true);

    l1New->installEventFilter(this);
    l2New->installEventFilter(this);
    l3New->installEventFilter(this);
    l4New->installEventFilter(this);
    backbtn->installEventFilter(this);
    l1btn->installEventFilter(this);
    l2btn->installEventFilter(this);
    l3btn->installEventFilter(this);
    l4btn->installEventFilter(this);

    // 初始化connect
    setupLevel0Button(l1btn, Level1, l2btn,l2New);
    setupLevel1Button(l2btn, Level2, l3btn,l3New);
    setupLevel2Button(l3btn, Level3, l4btn,l4New);
    setupLevel3Button(l4btn, Level4);

    HideAllButton();

    //分数处理
    QString runPath = QCoreApplication::applicationDirPath() + score_filename;
    runPath.replace(QString("/"), QString("\\"));


    connect(player_background,&QMediaPlayer::stateChanged,[=](){
        if(is_main_music_play)
            player_background->play();
        else
        {
            player_background->setPosition(0);
            player_background->pause();
        }
    });

    connect(backbtn, &QPushButton::clicked, [=]() {
        modifyScore(runPath);
        QTimer::singleShot(500, this, [=]() {
            emit this->back();
        });
    });
    connect(l1New,&QPushButton::clicked,[=]{
        HideAllGif();
        HideAllButton();
        BackGround->setText("你进入了茂密的草原地带，这里是敌军的前哨基地。敌人依靠草原的开阔地形进行快速的移动和攻击。你必须击败的敌军，逐步推进到敌人的指挥中心");
        playGif(movie1,gifLabel1);
        l1btn->move(1600,1000);
    });
    connect(l2New,&QPushButton::clicked,[=]{
        HideAllGif();
        HideAllButton();
        BackGround->setText("在击败了草原上的敌人后，你来到了炙热的沙漠。这片沙漠被另一股敌军势力所占据，他们利用沙漠的恶劣环境对抗入侵者。你需要面对强大的敌军和隐藏在沙漠之中的隐形坦克，同时小心随机出现的障碍物");
        playGif(movie2,gifLabel2);
        l2btn->move(1600,1000);

    });
    connect(l3New,&QPushButton::clicked,[=]{
        HideAllGif();
        HideAllButton();
        BackGround->setText("突破沙漠后，你进入了一个由钢铁和混凝土构成的工业区。这里是敌人的兵工厂，他们在此生产强大的寒冰坦克。寒冰坦克可以减速任何接近的目标，同时，混乱的磁场使你的左右操作键失效，而攻击键会随机改变方向，你必须小心应对，同时适应新的操控方式");
        playGif(movie3,gifLabel3);
        l3btn->move(1600,1000);
    });
    connect(l4New,&QPushButton::clicked,[=]{
        HideAllGif();
        HideAllButton();
        BackGround->setText("最终，你到达了敌人最坚固的堡垒——位于火山腹地。这里的敌军拥有最致命的武器：火焰坦克。这些坦克能喷射炙热的火焰，焚毁一切障碍。你需要充分利用地形和战术，面对一波又一波的敌人，最终击败火焰坦克的首领，解放整个星球");
        playGif(movie4,gifLabel4);
        l4btn->move(1600,1000);
    });

    QLabel *TextBackGround=new QLabel(this);
    TextBackGround->resize(2000,1200);
    TextBackGround->move(0,0);
    TextBackGround->setStyleSheet("background-color: rgba(0, 0, 0, 128); color: white; font-size: 50px;");
    TextBackGround->setText(
            "<br>"
            "<br>"
            "<div style='text-align: center; font-size: 70px;'>"
            "故事背景<br>"
            "</div>"
            "<div style='text-align: center; font-size: 50px;'>"
            "在一个遥远的星球上<br>"
            "四个截然不同的地区长期被四个强大的势力所控制<br>"
            "这些势力不仅威胁着当地的和平<br>"
            "也不断扩张势力<br>"
            "妄图统治整个星球<br>"
            "你作为一个勇敢的练习时长两年半的 坦克指挥官<br>"
            "肩负起了打击这些邪恶势力的重任<br>"
            "你必须穿越草原、沙漠、工业区和火山，消灭各个地区的敌军<br>"
            "解放这片被压迫的土地！！!"
            "</div>"
        );
    int fontId = QFontDatabase::addApplicationFont(Titleround);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily);
    customFont.setBold(true);
    TextBackGround->setFont(customFont);
    TextBackGround->setWordWrap(true);
    TextBackGround->setAlignment(Qt::AlignHCenter);

    HoverFillButton* HideStoryButton = new HoverFillButton("继续",TextBackGround);
    HideStoryButton->resize(300, 70);
    HideStoryButton->move(1600,1000);
    StartButtonStyle(HideStoryButton);

    connect(HideStoryButton,&HoverFillButton::clicked,[=]{
        TextBackGround->hide();
        HideStoryButton->move(0,1500);
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
        level->HideProp();
        level->Initmap();

        level->initchangeTimer();
        level->show();
        level->my_tank->startshoottime();
        for(int i=0; i<level->enemy_num; i++) {
            level->enemys[i]->startshoottime(2000);
        }

        if(!isConnected1)
        {
            connect(level, &level1::Win, [=]() {
                if(level->score>highest_level1_score)
                    highest_level1_score=level->score;
                pass_judge[0] = true;
                level->DeletechangTimer();
                nextButton->setEnabled(true);
                nextNew->setEnabled(true);
                this->show();
                level->close();
                nextButton->click();
                this->hide();
            });
            connect(level, &level1::back, this, [=]() {
                level->hide_all_tank();
                level->Deletetank();
                level->DeletechangTimer();
                level->Initmap();
                this->show();
                level->close();
            });
            connect(level, &level1::backButWin, [=]() {
                if(level->score>highest_level1_score)
                    highest_level1_score=level->score;
                level->DeletechangTimer();
                pass_judge[0] = true;
                nextButton->setEnabled(true);
                nextNew->setEnabled(true);
                this->show();
                level->close();
            });

            connect(level, &level1::Replay, [=]() {
                level->hide_all_tank();
                level->DeletechangTimer();
                level->deleteFailPage();
                level->close();
                button->clicked();

            });

            isConnected1 = true;
        }
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
        level->my_tank->startshoottime();
        for(int i=0; i<3; i++) {
            level->enemys[i]->startshoottime(2000);
        }
        level->enemys[3]->startshoottime(4000);
        level->enemys[4]->startshoottime(2000);
        if (!isConnected2) {
            connect(level, &level2::Win, [=]() {
                if(level->score>highest_level2_score)
                    highest_level2_score=level->score;
                pass_judge[1] = true;
                level->DeletechangTimer();
                nextButton->setEnabled(true);
                nextNew->setEnabled(true);
                this->show();
                level->close();
                nextButton->click();
                this->hide();
            });

            connect(level, &level2::back, this, [=]() {

                level->Deletetank();

                level->DeletechangTimer();

                level->Initmap();
                this->show();
                level->close();
            });

            connect(level, &level2::backButWin, [=]() {
                if(level->score>highest_level2_score)
                    highest_level2_score=level->score;
                level->DeletechangTimer();
                pass_judge[1] = true;
                nextButton->setEnabled(true);
                nextNew->setEnabled(true);
                this->show();
                level->close();
            });

            connect(level, &level2::Replay, [=]() {
                this->show();
                level->DeletechangTimer();
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
        level->my_tank->startshoottime();
        for(int i=0; i<level->enemy_num; i++) {
            level->enemys[i]->startshoottime(2000);
        }
        level->frosttank->startshoottime();
        if (!isConnected3)
        {
            connect(level, &level3::Win, [=]() {
                if(level->score>highest_level3_score)
                    highest_level3_score=level->score;

                pass_judge[2] = true;
                level->DeletechangTimer();
                nextButton->setEnabled(true);
                nextNew->setEnabled(true);
                this->show();
                level->close();
                nextButton->click();
                this->hide();
            });

            connect(level, &level3::back, this, [=]() {
                level->Deletetank();
                level->DeletechangTimer();
                level->Initmap();
                this->show();
                level->close();
            });

            connect(level, &level3::backButWin, [=]() {
                if(level->score>highest_level3_score)
                    highest_level3_score=level->score;
                level->DeletechangTimer();

                pass_judge[2] = true;
                nextButton->setEnabled(true);
                nextNew->setEnabled(true);
                this->show();
                level->close();
            });

            connect(level, &level3::Replay, [=]() {
                this->show();

                level->DeletechangTimer();

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
        level->timer->stop();
        level->timer->disconnect();
        level->deletePassPage();
        level->deleteFailPage();
        level->Deletetank();
        level->Initmap();
        level->InitChangeMapTimer();
        level->initchangeTimer();
        level->HideProp();
        level->show();
        level->my_tank->startshoottime();
        for(int i=0; i<level->enemy_num; i++) {
            level->enemys[i]->startshoottime(2000);
        }

        if(!isConnected4)
        {
            connect(level, &level4::Win, [=]() {

                if(level->score>highest_level4_score)
                    highest_level4_score=level->score;
                pass_judge[3] = true;
                level->DeletechangTimer();
                level->DeleteChangeMapTimer();
                this->show();
                level->close();
            });
            connect(level, &level4::back, this, [=]() {
                level->timer->stop();
                level->timer->disconnect();
                level->Deletetank();
                level->DeletechangTimer();
                level->DeleteChangeMapTimer();
                level->Initmap();
                this->show();
                level->close();
            });
            connect(level,&level4::backButWin,[=](){

                if(level->score>highest_level4_score)
                    highest_level4_score=level->score;
                pass_judge[0] = true;
                this->show();
                level->DeletechangTimer();
                level->DeleteChangeMapTimer();
                level->close();
            });
            connect(level,&level4::Replay,[=]{
                level->timer->stop();
                level->timer->disconnect();
                this->show();
                level->DeletechangTimer();
                level->DeleteChangeMapTimer();
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
    int fontId = QFontDatabase::addApplicationFont(AI);
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
    int fontId = QFontDatabase::addApplicationFont(Titleround);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily,20);

    button->setFillTime(300);
    button->setFillBrush(QBrush(QColor("#A39A7C")));
    button->setTextColor(QColor("#141822"), QColor("#312F3B"));
    button->setRadius(30);
    button->setFont(customFont);
}

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

bool PassWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Enter)
    {
        // 如果事件是进入事件，检查是哪个按钮并播放音效
        QPushButton *button = qobject_cast<QPushButton*>(obj);
        if (button)
        {
            if (button->isEnabled())
            {
                player_enterButton->setPosition(0); // 将音效位置设置为开头，以便从头播放
                player_enterButton->play();
            }
        }
    }
    // 继续传递事件
    return QObject::eventFilter(obj, event);
}

void PassWindow::modifyScore(QString filePath)
{
    QFile file(filePath);
    sumScore=highest_level1_score+highest_level2_score+highest_level3_score+highest_level4_score;
    // 读取文件内容
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for reading:" << file.errorString();
        return;
    }
    QStringList fileLines;
    QTextStream in(&file);
    while (!in.atEnd()) {
        fileLines.append(in.readLine());
    }

    file.close();

    // 修改指定账号的分数
    bool accountFound = false;
    for (int i = 0; i < fileLines.size(); ++i)
    {
        QStringList parts = fileLines[i].split(":");
        if (parts.size() == 2 && parts[0] == User_name && sumScore>= parts[1].toInt())
        {
            fileLines[i] = User_name + ":" + QString::number(sumScore);
            accountFound = true;
            break; // 如果只修改第一个匹配项，找到后跳出循环
        }
    }
    if (!accountFound) {
        file.close();
        QFile file1(filePath);
        if (!file1.open(QIODevice::Append | QIODevice::Text)) {
            qDebug() << "Unable to open file for writing:" << file1.errorString();
            return;
        }
        QTextStream out(&file1);
        out << User_name << ":" << QString::number(sumScore) << "\n"; // 使用 QTextStream 写入
        file1.close();
        return;
    }
    else
    {
        // 将修改后的内容写回文件
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Cannot open file for writing:" << file.errorString();
            return;
        }
        QTextStream out(&file);
        for (const QString &line : fileLines) {
            out << line << "\n";
        }

        file.close();
    }
}

PassWindow::~PassWindow()
{

}
