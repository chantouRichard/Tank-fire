#include "SettingWindow.h"
#include "global.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QStyleFactory>

SettingWindow::SettingWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1200, 800);
    setWindowTitle("设置");
    //禁用右上角的关闭
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

    // 使用样式表美化界面
    setStyleSheet(
           "QWidget { background-color: #2E2E2E; }"
           "QPushButton { font-size: 24px; padding: 15px; background-color: rgba(76, 175, 80, 0.8); color: white; border: none; border-radius: 5px; }"
           "QPushButton:pressed { background-color: rgba(69, 160, 73, 0.8); }"
           "QSlider::groove:horizontal { height: 15px; background: #ddd; border-radius: 7px; }"
           "QSlider::handle:horizontal { background: #4CAF50; border: none; width: 25px; height: 25px; margin: -5px 0; border-radius: 12px; }"
           "QLabel { font-size: 28px; color: white; }"
       );

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 添加设置标题
    gameTitleLabel = new QLabel("设置", this);
    QString titleStyle =
        "QLabel {"
        "   font-size: 120px;"                 // 字体大小调整为原来的两倍
        "   font-weight: bold;"               // 字体粗体
        "   color: #FFFFFF;"                  // 字体填充为白色
        "   background-color: transparent;"   // 背景透明
        "   border-radius: 20px;"             // 边框圆角调整为原来的两倍
        "   padding: 12px;"                   // 内边距调整为原来的两倍
        "   text-shadow: 2px 2px 0px #0000FF, -2px -2px 0px #0000FF, -2px 2px 0px #0000FF, 2px -2px 0px #0000FF;" // 蓝色边框效果
        "}";
    gameTitleLabel->setStyleSheet(titleStyle);

    QHBoxLayout* volumeLayout = new QHBoxLayout();
    volumeLabel = new QLabel("音量", this);
    volumeLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 28px;"                 // 字体大小调整
        "   font-weight: bold;"               // 字体粗体
        "   color: #FFFFFF;"                  // 字体填充为白色
        "}"
    );
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(gameVolume);

    connect(volumeSlider, &QSlider::valueChanged, this, &SettingWindow::handleVolumeChange);

    volumeLayout->addWidget(volumeLabel);
    volumeLayout->addWidget(volumeSlider);

    KeyUpButton = new QPushButton("上: W", this);
    keyDownButton = new QPushButton("下: S", this);
    KeyLeftButton = new QPushButton("左: A", this);
    KeyRightButton = new QPushButton("右: D", this);
    KeyShootButton = new QPushButton("射击: J", this);
    returnButton = new QPushButton("返回", this);

    connect(KeyUpButton, &QPushButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(keyDownButton, &QPushButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyLeftButton, &QPushButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyRightButton, &QPushButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyShootButton, &QPushButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(returnButton,&QPushButton::clicked,this,&SettingWindow::ret_sign);

    mainLayout->addWidget(gameTitleLabel, 0, Qt::AlignCenter); // 将标题放在顶部居中
    mainLayout->addLayout(volumeLayout);
    mainLayout->addWidget(KeyUpButton);
    mainLayout->addWidget(keyDownButton);
    mainLayout->addWidget(KeyLeftButton);
    mainLayout->addWidget(KeyRightButton);
    mainLayout->addWidget(KeyShootButton);
    mainLayout->addWidget(returnButton);
}

void SettingWindow::handleVolumeChange(int value)
{
    gameVolume = value;
    player_background->setVolume(gameVolume);
    volumeLabel->setText(QString("音量: %1").arg(value));
    qDebug() << "value:" << value;
}

void SettingWindow::handleKeyChange()
{
    currentKeyButton = qobject_cast<QPushButton*>(sender());
    if (currentKeyButton)
    {
        currentKeyButton->setText("按下新键位...");
        qDebug() << "设置新按钮……";
    }
}

void SettingWindow::keyPressEvent(QKeyEvent *event)
{
    if (currentKeyButton)
    {
        int key = event->key();
        if (currentKeyButton == KeyUpButton && key_check(key))
        {
            KeyUp = key;
            KeyUpButton->setText(QString("上: %1").arg(QKeySequence(key).toString()));
        }
        else if (currentKeyButton == keyDownButton && key_check(key))
        {
            KeyDown = key;
            keyDownButton->setText(QString("下: %1").arg(QKeySequence(key).toString()));
        }
        else if (currentKeyButton == KeyLeftButton && key_check(key))
        {
            KeyLeft = key;
            KeyLeftButton->setText(QString("左: %1").arg(QKeySequence(key).toString()));
        }
        else if (currentKeyButton == KeyRightButton && key_check(key))
        {
            KeyRight = key;
            KeyRightButton->setText(QString("右: %1").arg(QKeySequence(key).toString()));
        }
        else if (currentKeyButton == KeyShootButton && key_check(key))
        {
            KeyShoot = key;
            KeyShootButton->setText(QString("射击: %1").arg(QKeySequence(key).toString()));
        }
        currentKeyButton = nullptr;
    }
}

bool SettingWindow::key_check(int key)
{
    return  (key!=KeyDown && key!= KeyLeft && key!= KeyRight && key!=KeyUp && key!= KeyShoot);
}
