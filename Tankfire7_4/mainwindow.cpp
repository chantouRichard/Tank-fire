#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置窗口标题和大小
    this->setWindowTitle("坦克大战");
    this->setFixedSize(1600, 1200); // 窗口大小调整为1600x1200

    // 创建并设置游戏标题标签
    gameTitleLabel = new QLabel(this);
    gameTitleLabel->setText("坦克大战");
    gameTitleLabel->setGeometry(500, 100, 650, 200); // 调整位置和大小以确保标题完整显示
    gameTitleLabel->setAlignment(Qt::AlignCenter); // 文本居中对齐

    //初始状态未登录
    is_login=false;

    // 设置标题的样式
    QString titleStyle =
        "QLabel {"
        "   font-size: 150px;"                 // 字体大小调整为原来的两倍
        "   font-weight: bold;"               // 字体粗体
        "   font-style: italic;"              // 字体倾斜
        "   color: #FFFFFF;"                  // 字体填充为白色
        "   background-color: transparent;"   // 背景透明
        "   border-radius: 20px;"             // 边框圆角调整为原来的两倍
        "   padding: 12px;"                   // 内边距调整为原来的两倍
        "}";
    gameTitleLabel->setStyleSheet(titleStyle);

    // 创建并设置开始游戏按钮
    startGameButton = new QPushButton("开始游戏", this);
    startGameButton->setGeometry(630, 600, 350, 75); // 按钮位置和大小调整为原来的两倍
    // 设置开始游戏按钮的样式
    setButtonStyle(startGameButton, is_login);


    // 创建并设置“设置”游戏按钮
    setGameButton = new QPushButton("设置", this);
    setGameButton->setGeometry(630, 800, 350, 75); // 按钮位置和大小调整为原来的两倍
    // 设置“设置”按钮的样式
   setButtonStyle(setGameButton, is_login);

    loginButton =new QPushButton("登录",this);
    loginButton->setGeometry(630, 1000, 350, 75);
    loginButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 40px;"           // 字体大小调整为原来的两倍
        "   font-weight: bold;"         // 字体粗细
        "   color: white;"              // 文本颜色
        "   background-color: #5CACEE;" // 背景颜色
        "   border-radius: 20px;"       // 边框圆角调整为原来的两倍
        "   padding: 12px;"             // 内边距调整为原来的两倍
        "}"
        "QPushButton:hover {"
        "   background-color: #1E90FF;" // 鼠标悬停时的背景颜色
        "}"
        "QPushButton:pressed {"
        "   background-color: #0B60AD;" // 鼠标按下时的背景颜色
        "}"
    );

    //背景音乐
    player_background->setMedia(QUrl("qrc:/5/Res/music/background.wav"));
    //    playlist->addMedia(QUrl("qrc:/5/Res/music/background.wav"));
    //    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player_background->setVolume(gameVolume);
    player_background->play();

    connect(player_background,&QMediaPlayer::stateChanged,player_background,&QMediaPlayer::play);

    pass_window=new pass();
    setting_window=new SettingWindow();
    login_window=new LoginWindow();
    connect(startGameButton, &QPushButton::clicked, this, [=](){
        this->hide();
        pass_window->show();
    });
    connect(setGameButton,&QPushButton::clicked,this,[=](){
        this->hide();
        setting_window->show();
    });
    connect(pass_window->backbtn,&QPushButton::clicked,this,[=](){
        pass_window->hide();
        this->show();
    });
    connect(setting_window,&SettingWindow::ret_sign,this,[=](){
        setting_window->hide();
        show();
    });
    connect(loginButton,&QPushButton::clicked,this,[=](){
        this->hide();
        login_window->show();
    });
    connect(login_window,&LoginWindow::success_to_enter,this,[=](){
        show();
    });
    connect(login_window,&LoginWindow::success_to_enter,this,&MainWindow::login_success);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonStyle(QPushButton* button,bool enabled)
{
    if(enabled)
    {
        button->setEnabled(true);
        button->setStyleSheet(
                "QPushButton {"
                "   font-size: 40px;"           // 字体大小调整为原来的两倍
                "   font-weight: bold;"         // 字体粗细
                "   color: white;"              // 文本颜色
                "   background-color: #5CACEE;" // 背景颜色
                "   border-radius: 20px;"       // 边框圆角调整为原来的两倍
                "   padding: 12px;"             // 内边距调整为原来的两倍
                "}"
                "QPushButton:hover {"
                "   background-color: #1E90FF;" // 鼠标悬停时的背景颜色
                "}"
                "QPushButton:pressed {"
                "   background-color: #0B60AD;" // 鼠标按下时的背景颜色
                "}"
            );
    }
    else
    {
        button->setEnabled(false);
        button->setStyleSheet(
                "QPushButton {"
                "   font-size: 40px;"           // 字体大小调整为原来的两倍
                "   font-weight: bold;"         // 字体粗细
                "   color: white;"              // 文本颜色
                "   background-color: #CCCCCC;" // 背景颜色
                "   border-radius: 20px;"       // 边框圆角调整为原来的两倍
                "   padding: 12px;"             // 内边距调整为原来的两倍
                "}"
                "QPushButton:hover {"
                "   background-color: #1E90FF;" // 鼠标悬停时的背景颜色
                "}"
                "QPushButton:pressed {"
                "   background-color: #0B60AD;" // 鼠标按下时的背景颜色
                "}"
            );
    }
}

void MainWindow::updateButton(bool enabled)
{
    setButtonStyle(startGameButton, enabled);
    setButtonStyle(setGameButton, enabled);
    setButtonStyle(loginButton,!enabled);
}

void MainWindow::login_success()
{
    // 更新登录状态
       is_login = true;
       // 更新按钮样式
       updateButton(is_login);
}
