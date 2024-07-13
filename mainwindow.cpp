#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtmaterialflatbutton.h"
#include <QDebug>
#include <QPalette>
#include <QPixmap>
#include<QFontDatabase>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口标题和大小
    this->setWindowTitle("坦克大战");
    this->setFixedSize(2000, 1200); // 窗口大小调整为2000x1200

    // 设置背景图片
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(main_back_pic).scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    // 初始状态未登录
    is_login = false;

    // 创建开始游戏按钮
    startGameButton = new QtMaterialFlatButton("开始游戏", this);
    startGameButton->setGeometry(250, 400, 350, 75); // 设置按钮位置和大小
    setButtonStyle(startGameButton, is_login);

    // 创建设置按钮
    setGameButton = new QtMaterialFlatButton("设置", this);
    setGameButton->setGeometry(250, 520, 350, 75); // 设置按钮位置和大小
    setButtonStyle(setGameButton, is_login);

    // 创建登录按钮
    loginButton = new QtMaterialFlatButton("登录", this);
    loginButton->setGeometry(250, 640, 350, 75); // 设置按钮位置和大小
    setButtonStyle(loginButton, !is_login);

    // 创建历史分数按钮
    historyScoresButton = new QtMaterialFlatButton("历史分数", this);
    historyScoresButton->setGeometry(250, 760, 350, 75); // 设置按钮位置和大小
    setButtonStyle(historyScoresButton, is_login);

    // 设置背景音乐
    player_start->setMedia(QUrl(start_wav));
    player_start->setVolume(gameVolume);
    player_start->play();
    is_play=true;
    connect(player_start, &QMediaPlayer::stateChanged, player_start, [=](){
        if(/*player_start->mediaStatus()==QMediaPlayer::EndOfMedia&&*/is_play)
            player_start->play();
        else
        {
            is_main_music_play=true;
            player_background->play();
            player_start->setPosition(0);
            player_start->pause();
        }
    });

    //设置进入按钮的音乐
    player_enterButton->setMedia(QUrl(button_wav));
    player_enterButton->setVolume(buttonVolume);

    // 设置按钮事件过滤器
    startGameButton->installEventFilter(this);
    setGameButton->installEventFilter(this);
    loginButton->installEventFilter(this);
    historyScoresButton->installEventFilter(this);

    // 创建和连接窗口实例及按钮点击事件
    pass_window = new PassWindow();
    setting_window = new SettingWindow();
    login_window = new LoginWindow();
    His_scory_window = new HistoryscoreWindow();

    //连接信号和槽
    do_connect();

    // 更新按钮状态和样式
    updateButton(is_login);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonStyle(QtMaterialFlatButton* button, bool enabled)
{
    int fontId = QFontDatabase::addApplicationFont(Titleround);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 26);
    customFont.setBold(true);
    button->setFont(customFont);
    button->setRippleStyle(Material::CenteredRipple);
    button->setForegroundColor(QColor("#FFFFFF")); // 设置字体颜色为白色
    button->setCornerRadius(12); // 设置圆角
    button->setHaloVisible(true);
    button->setHasFixedRippleRadius(false);

    if (enabled)
    {
        button->setEnabled(true);
        button->setBackgroundColor(QColor("#0000FF")); // 设置背景颜色
        button->setOverlayColor(QColor("#1E90FF")); // 悬停时背景颜色
    }
    else
    {
        button->setEnabled(false);
        button->setBackgroundColor(QColor("#CCCCCC")); // 禁用状态下的背景颜色
    }
}

void MainWindow::updateButton(bool enabled)
{
    setButtonStyle(startGameButton, enabled);
    setButtonStyle(setGameButton, enabled);
    setButtonStyle(loginButton, !enabled);
    setButtonStyle(historyScoresButton, enabled);
}

void MainWindow::login_success()
{
    // 更新登录状态
    is_login = true;
    // 更新按钮样式
    updateButton(is_login);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Enter)
    {
        // 如果事件是进入事件，检查是哪个按钮并播放音效
        QtMaterialFlatButton *button = qobject_cast<QtMaterialFlatButton*>(obj);
        if (button)
        {
            if (button == startGameButton || button == setGameButton || button == loginButton || button == historyScoresButton)
            {
                if (button->isEnabled())
                {
                    player_enterButton->setPosition(0); // 将音效位置设置为开头，以便从头播放
                    player_enterButton->play();
                }
            }
        }
    }
    // 继续传递事件
    return QObject::eventFilter(obj, event);
}

void MainWindow::do_connect()
{
    connect(startGameButton, &QtMaterialFlatButton::clicked, this, [=]() {
        this->hide();
        pass_window->show();
    });

    connect(setGameButton, &QtMaterialFlatButton::clicked, this, [=]() {
        this->hide();
        setting_window->show();
    });

    connect(pass_window->backbtn, &QPushButton::clicked, this, [=]() {
        pass_window->hide();
        this->show();
    });

    connect(setting_window, &SettingWindow::ret_sign, this, [=]() {
        setting_window->hide();
        show();
    });

    connect(loginButton, &QtMaterialFlatButton::clicked, this, [=]() {
        this->hide();
        login_window->show();
    });

    connect(login_window, &LoginWindow::success_to_enter, this, [=]() {
        show();
    });

    connect(login_window, &LoginWindow::success_to_enter, this, &MainWindow::login_success);

    connect(historyScoresButton, &QtMaterialFlatButton::clicked, this, [=]() {
        this->hide();
        His_scory_window->show();
    });

    connect(His_scory_window->returnButton, &QPushButton::clicked, this, [=]() {
        this->show();
        His_scory_window->hide();
    });

    connect(startGameButton,&QPushButton::clicked,player_start,[=](){
        is_play=false;
        player_start->setPosition(0);
        player_start->pause();
    });

    connect(pass_window->backbtn,&transimplebutton::clicked,player_start,[=](){
        is_play=true;
        is_main_music_play=false;
        player_background->pause();
        player_start->play();
    });
}
