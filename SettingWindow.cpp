#include "SettingWindow.h"
#include "global.h"
#include <QMessageBox>
#include <QDebug>
#include <QStyleFactory>
#include <QPixmap>
#include <QPalette>
#include <QLabel>

SettingWindow::SettingWindow(QWidget *parent)
    : QWidget(parent),
      keySettingsPage(nullptr),
      volumeSettingsPage(nullptr),
      skinSettingsPage(nullptr),
      m_useThemeColors(true),
      m_showHalo(true),
      m_rippleStyle(Material::CenteredRipple)
{
    setFixedSize(2000, 1200);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);

    // Set background image
    QPixmap backgroundImage(setting_back_pic);
    QPalette palette;
    palette.setBrush(QPalette::Window, backgroundImage.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setPalette(palette);
    setAutoFillBackground(true);

    mainCanvas = new QWidget(this);
    mainCanvas->setGeometry(400, 50, 1200, 1100); // Adjusted size and position
    mainCanvas->setStyleSheet(
                "background-color: rgba(173, 216, 230, 0.7);"
                "border-radius: 20px;"
                );

    tabs = new QtMaterialTabs(this);
    tabs->setUseThemeColors(true);
    tabs->setHaloVisible(true);
    tabs->setRippleStyle(static_cast<Material::RippleStyle>(m_rippleStyle));
    tabs->setInkColor(Qt::gray);
    tabs->setBackgroundColor(QColor(0, 0, 0, 0)); // Transparent background
    tabs->setTextColor(Qt::white);
    tabs->setStyleSheet(
                "QtMaterialTab {"
                "   background-color: none;"          // 标签背景颜色
                "   color: gold;"                     // 标签文本颜色
                "   font-weight: bold;"               // 标签文本加粗
                "   font-size: 28px;"                 // 标签文本字体大小
                "   border-radius: 15px;"             // 标签圆角
                "   border: 2px solid white;"         // 标签边框样式
                "   margin: 5px;"                     // 标签外边距
                "   text-align: center;"              // 标签文本对齐方式
                "   min-width: 400px;"                // 标签最小宽度
                "   min-height: 60px;"                // 标签最小高度
                "   max-width: 400px;"                // 标签最大宽度
                "   max-height: 60px;"                // 标签最大高度
                "   opacity: 0.1;"                    // 标签透明度
                "}"
                "QtMaterialTab:hover {"
                "   background-color: rgba(255, 255, 255, 0.2);" // 标签悬停背景颜色
                "}"
                "QtMaterialTab:checked {"
                "   background-color: #3f51b5;"       // 选中标签背景颜色
                "   color: white;"                    // 选中标签文本颜色
                "}"
                "QtMaterialTabsInkBar {"
                "   background-color: #ffffff;"       // 墨水条颜色
                "}"
                );

    tabs->addTab("键位设置");
    tabs->addTab("音量调节");
    tabs->addTab("皮肤选择");

    connect(tabs, &QtMaterialTabs::currentChanged, this, [=](int index) {
        keySettingsPage->setVisible(index == 0);
        volumeSettingsPage->setVisible(index == 1);
        skinSettingsPage->setVisible(index == 2);
    });

    tabs->setGeometry(400, 50, 1200, 150); // Increased y-width

    keySettingsPage = createKeySettingsPage();
    volumeSettingsPage = createVolumeSettingsPage();
    skinSettingsPage = createSkinSettingsPage();

    keySettingsPage->setGeometry(400, 200, 1200, 950); // Adjusted y position
    volumeSettingsPage->setGeometry(400, 200, 1200, 950);
    skinSettingsPage->setGeometry(400, 200, 1200, 950);

    keySettingsPage->setVisible(true);
    volumeSettingsPage->setVisible(false);
    skinSettingsPage->setVisible(false);

    returnButton = new HoverFillButton("返回", this);
    returnButton->setGeometry(1800, 1100, 150, 50); // Position returnButton in bottom-right corner
    returnButton->setFillBrush(QBrush(QColor("#00AA73")));
    returnButton->setTextColor(QColor("#87CEEB"), QColor("#FFFFFF"));
    returnButton->setRadius(30);
    connect(returnButton, &QPushButton::clicked, this, &SettingWindow::handleReturn);
}

QWidget* SettingWindow::createKeySettingsPage()
{
    QWidget *page = new QWidget(this);

    QLabel *imageLabel_tank = new QLabel(page);
    QPixmap image(setting_tank);
    imageLabel_tank->setPixmap(image);
    imageLabel_tank->setGeometry(-130, -80, 320, 240); // Adjusted size and position
    imageLabel_tank->setScaledContents(true);

    QLabel *imageLabel_bullet = new QLabel(page);
    QPixmap image_bullet(setting_bullet);
    imageLabel_bullet->setPixmap(image_bullet);
    imageLabel_bullet->setGeometry(70, 550, 100, 100); // Adjusted size and position
    imageLabel_bullet->setScaledContents(true);

    QLabel *imageLabel_prop = new QLabel(page);
    QPixmap image_prop(setting_prop);
    imageLabel_prop->setPixmap(image_prop);
    imageLabel_prop->setGeometry(650, 60, 100, 100); // Adjusted size and position
    imageLabel_prop->setScaledContents(true);

    KeyUpButton = new QtMaterialRaisedButton("上: " + QKeySequence(KeyUp).toString(), page);
    keyDownButton = new QtMaterialRaisedButton("下: " + QKeySequence(KeyDown).toString(), page);
    KeyLeftButton = new QtMaterialRaisedButton("左: " + QKeySequence(KeyLeft).toString(), page);
    KeyRightButton = new QtMaterialRaisedButton("右: " + QKeySequence(KeyRight).toString(), page);
    KeyShootButton = new QtMaterialRaisedButton("射击: " + QKeySequence(KeyShoot).toString(), page);
    KeyProp1Button = new QtMaterialRaisedButton("第一个道具: " + QKeySequence(KeyProp1).toString(), page);
    KeyProp2Button = new QtMaterialRaisedButton("第二个道具: " + QKeySequence(KeyProp2).toString(), page);
    KeyProp3Button = new QtMaterialRaisedButton("第三个道具: " + QKeySequence(KeyProp3).toString(), page);
    KeyProp4Button = new QtMaterialRaisedButton("第四个道具: " + QKeySequence(KeyProp4).toString(), page);

    setupButton(KeyUpButton);
    setupButton(keyDownButton);
    setupButton(KeyLeftButton);
    setupButton(KeyRightButton);
    setupButton(KeyShootButton);
    setupButton(KeyProp1Button);
    setupButton(KeyProp2Button);
    setupButton(KeyProp3Button);
    setupButton(KeyProp4Button);

    setPositionAndsize(KeyUpButton, 150, 130, 300, 70);
    setPositionAndsize(keyDownButton, 150, 210, 300, 70);
    setPositionAndsize(KeyLeftButton, 150, 290, 300, 70);
    setPositionAndsize(KeyRightButton, 150, 370, 300, 70);
    setPositionAndsize(KeyShootButton, 150, 650, 300, 100);
    setPositionAndsize(KeyProp1Button, 750, 150, 300, 80);
    setPositionAndsize(KeyProp2Button, 750, 250, 300, 80);
    setPositionAndsize(KeyProp3Button, 750, 350, 300, 80);
    setPositionAndsize(KeyProp4Button, 750, 450, 300, 80);

    // Ensure buttons are clickable
    KeyUpButton->raise();
    keyDownButton->raise();
    KeyLeftButton->raise();
    KeyRightButton->raise();
    KeyShootButton->raise();

    connect(KeyUpButton, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(keyDownButton, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyLeftButton, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyRightButton, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyShootButton, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);

    page->show();
    return page;
}

QWidget* SettingWindow::createVolumeSettingsPage()
{
    QWidget *page = new QWidget(this);

        main_volumeLabel = new QLabel(page);
        setupVolumeLabel(main_volumeLabel, "主音量");
        main_volumeLabel->setGeometry(40, 30, 250, 75);

        button_volumeLabel = new QLabel(page);
        setupVolumeLabel(button_volumeLabel, "按钮音量");
        button_volumeLabel->setGeometry(40, 230, 250, 75);

        boom_volumeLabel = new QLabel(page);
        setupVolumeLabel(boom_volumeLabel, "爆炸音量");
        boom_volumeLabel->setGeometry(40, 430, 250, 75);

        victory_volumeLabel = new QLabel(page);
        setupVolumeLabel(victory_volumeLabel, "胜利音量");
        victory_volumeLabel->setGeometry(640, 30, 250, 75);

        fail_volumeLabel = new QLabel(page);
        setupVolumeLabel(fail_volumeLabel, "失败音量");
        fail_volumeLabel->setGeometry(640, 230, 250, 75);

        prop_volumeLabel = new QLabel(page);
        setupVolumeLabel(prop_volumeLabel, "道具音量");
        prop_volumeLabel->setGeometry(640, 430, 250, 75);

        QtMaterialSlider *main_volumeSlider = new QtMaterialSlider(page);
        setupSlider(main_volumeSlider, gameVolume);
        setSlide(main_volumeSlider, 40, 120, 400, 40);

        QtMaterialSlider *button_volumeSlider = new QtMaterialSlider(page);
        setupSlider(button_volumeSlider, buttonVolumn);
        setSlide(button_volumeSlider, 40, 320, 400, 50);

        QtMaterialSlider *boom_volumeSlider = new QtMaterialSlider(page);
        setupSlider(boom_volumeSlider, boomVolumn);
        setSlide(boom_volumeSlider, 40, 520, 400, 50);

        QtMaterialSlider *victory_volumeSlider = new QtMaterialSlider(page);
        setupSlider(victory_volumeSlider, victoryVolume);
        setSlide(victory_volumeSlider, 640, 120, 400, 50);

        QtMaterialSlider *fail_volumeSlider = new QtMaterialSlider(page);
        setupSlider(fail_volumeSlider, failVolume);
        setSlide(fail_volumeSlider, 640, 320, 400, 50);

        QtMaterialSlider *prop_volumeSlider = new QtMaterialSlider(page);
        setupSlider(prop_volumeSlider, propVolume);
        setSlide(prop_volumeSlider, 640, 520, 400, 50);

        connect(main_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleMainVolumeChange);
        connect(button_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleButtonVolumeChange);
        connect(boom_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleBoomVolumeChange);
        connect(victory_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleVictoryVolumeChange);
        connect(fail_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleFailVolumeChange);
        connect(prop_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handlePropVolumeChange);

        page->show();
        return page;
}


QWidget* SettingWindow::createSkinSettingsPage()
{
    QWidget *page = new QWidget(this);

    // Add your skin setting widgets here

    page->show();
    return page;
}

void SettingWindow::handleMainVolumeChange(int value)
{
    gameVolume = value;
    player_background->setVolume(gameVolume);
    main_volumeLabel->setText(QString("主音乐音量: %1").arg(value));
}

void SettingWindow::handleButtonVolumeChange(int value)
{
    buttonVolumn = value;
    player_enterButton->setVolume(buttonVolumn);
    button_volumeLabel->setText(QString("按钮音量: %1").arg(value));
}

void SettingWindow::handleBoomVolumeChange(int value)
{
    boomVolumn = value;
    player_boom->setVolume(boomVolumn);
    boom_volumeLabel->setText(QString("爆炸音量: %1").arg(value));
}

void SettingWindow::handleVictoryVolumeChange(int value)
{
    victoryVolume = value;
    player_victory->setVolume(victoryVolume);
    victory_volumeLabel->setText(QString("胜利音量: %1").arg(value));
}

void SettingWindow::handleFailVolumeChange(int value)
{
    failVolume = value;
    player_fail->setVolume(failVolume);
    fail_volumeLabel->setText(QString("失败音量: %1").arg(value));
}

void SettingWindow::handlePropVolumeChange(int value)
{
    propVolume = value;
    player_prop->setVolume(propVolume);
    prop_volumeLabel->setText(QString("道具音量: %1").arg(value));
}

void SettingWindow::handleKeyChange()
{
    currentKeyButton = qobject_cast<QtMaterialRaisedButton*>(sender());
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
        QString keyText = QKeySequence(key).toString();
        if (currentKeyButton == KeyUpButton && key_check(key))
        {
            KeyUp = key;
            KeyUpButton->setText("上: " + keyText);
        }
        else if (currentKeyButton == keyDownButton && key_check(key))
        {
            KeyDown = key;
            keyDownButton->setText("下: " + keyText);
        }
        else if (currentKeyButton == KeyLeftButton && key_check(key))
        {
            KeyLeft = key;
            KeyLeftButton->setText("左: " + keyText);
        }
        else if (currentKeyButton == KeyRightButton && key_check(key))
        {
            KeyRight = key;
            KeyRightButton->setText("右: " + keyText);
        }
        else if (currentKeyButton == KeyShootButton && key_check(key))
        {
            KeyShoot = key;
            KeyShootButton->setText("射击: " + keyText);
        }
        currentKeyButton = nullptr;
    }
}

bool SettingWindow::key_check(int key)
{
    return  (key != KeyDown && key != KeyLeft && key != KeyRight && key != KeyUp && key != KeyShoot);
}

void SettingWindow::handleReturn()
{
    emit ret_sign();
}

void SettingWindow::setupButton(QtMaterialRaisedButton*& button)
{
    //    button->setStyleSheet(
    //                "QtMaterialRaisedButton {"
    //                "   font-size: 40px;"             // 字体大小
    //                "   font-weight: bold;"           // 字体粗体
    //                "   color: white;"                // 文字颜色
    //                "   background-color: #5CACEE;"   // 按钮背景颜色
    //                "   border-radius: 20px;"         // 边框圆角
    //                "   padding: 12px;"               // 内边距
    //                "}"
    //                "QtMaterialRaisedButton:hover {"
    //                "   background-color: #1E90FF;"   // 悬停时背景颜色
    //                "}"
    //                "QtMaterialRaisedButton:pressed {"
    //                "   background-color: #0B60AD;"   // 按下时背景颜色
    //                "}"
    //                );
    button->setForegroundColor(Qt::white);
    button->setBackgroundColor(QColor(84,115,125,30));

    button->setFontSize(12);
    button->setHaloVisible(true);
    button->setRippleStyle(Material::CenteredRipple);
    button->setCornerRadius(15);  // 圆角设置
}

void SettingWindow::setPositionAndsize(QtMaterialRaisedButton *&button, int x, int y, int width, int height)
{
    button->setGeometry(x, y, width, height);
    button->raise(); // Ensure the button is on top
}

void SettingWindow::setupVolumeLabel(QLabel *&label, const QString &text)
{
    label->setText(text);
    label->setStyleSheet(
        "QLabel {"
        "   font-size: 28px;"
        "   font-weight: bold;"
        "   color: #FFFFFF;"
        "}"
    );

    QFont font("Helvetica", 25, QFont::Bold);
    label->setFont(font);

}

void SettingWindow::setupSlider(QtMaterialSlider *&slider, int volume)
{
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(volume);

    slider->setThumbColor(QColor("#003150"));
    slider->setTrackColor(QColor("#407433"));
    slider->setDisabledColor(QColor("#999999"));
}

void SettingWindow::setSlide(QtMaterialSlider *&slider, int x, int y, int width, int height)
{
    slider->setGeometry(x, y, width, height);
}
