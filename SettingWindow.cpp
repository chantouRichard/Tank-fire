#include "SettingWindow.h"
#include "global.h"
#include <QMessageBox>
#include <QDebug>
#include <QStyleFactory>
#include <QPixmap>
#include <QPalette>
#include <QLabel>
#include<QFontDatabase>

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

    int fontId = QFontDatabase::addApplicationFont(Iron);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 14);

    returnButton = new HoverFillButton("返回", this);
    returnButton->setGeometry(1800, 1100, 150, 50); // Position returnButton in bottom-right corner
    returnButton->setFillBrush(QBrush(QColor("#00AA73")));
    returnButton->setTextColor(QColor("#87CEEB"), QColor("#FFFFFF"));
    returnButton->setRadius(30);
    returnButton->setFont(customFont);
    connect(returnButton, &QPushButton::clicked, this, &SettingWindow::handleReturn);

    returnButton->installEventFilter(this);
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


    KeyUpButton = new QtMaterialRaisedButton("上: W", page);
    keyDownButton = new QtMaterialRaisedButton("下: S", page);
    KeyLeftButton = new QtMaterialRaisedButton("左: A", page);
    KeyRightButton = new QtMaterialRaisedButton("右: D", page);
    KeyShootButton = new QtMaterialRaisedButton("射击: J", page);
    KeyProp1Button = new QtMaterialRaisedButton("道具一: " + QKeySequence(KeyProp1).toString(), page);
    KeyProp2Button = new QtMaterialRaisedButton("道具二: " + QKeySequence(KeyProp2).toString(), page);
    KeyProp3Button = new QtMaterialRaisedButton("道具三: " + QKeySequence(KeyProp3).toString(), page);
    KeyProp4Button = new QtMaterialRaisedButton("道具四: " + QKeySequence(KeyProp4).toString(), page);

//    KeyUp=Qt::Key_W;
//    KeyDown=Qt::Key_S;
//    KeyLeft=Qt::Key_A;
//    KeyRight=Qt::Key_D;
//    KeyShoot=Qt::Key_J;

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
    KeyProp1Button->raise();
    KeyProp2Button->raise();
    KeyProp3Button->raise();
    KeyProp4Button->raise();

    connect(KeyUpButton, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(keyDownButton, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyLeftButton, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyRightButton, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyShootButton, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyProp1Button, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyProp2Button, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyProp3Button, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);
    connect(KeyProp4Button, &QtMaterialFlatButton::clicked, this, &SettingWindow::handleKeyChange);

    KeyUpButton->installEventFilter(this);
    keyDownButton->installEventFilter(this);
    KeyLeftButton->installEventFilter(this);
    KeyRightButton->installEventFilter(this);
    KeyShootButton->installEventFilter(this);
    KeyProp1Button->installEventFilter(this);
    KeyProp2Button->installEventFilter(this);
    KeyProp3Button->installEventFilter(this);
    KeyProp4Button->installEventFilter(this);

    // 初始化消息对话框
    int fontId1 = QFontDatabase::addApplicationFont(Iron);
    QString fontFamily1 = QFontDatabase::applicationFontFamilies(fontId1).at(0);
    QFont customFont1(fontFamily1, 12);

    messageSnackbar = new QtMaterialSnackbar(page);
    messageSnackbar->setBackgroundColor(QColor(232,230,240)); // 设置背景颜色
    messageSnackbar->setTextColor(QColor(58,46,121)); // 设置文字颜色
    messageSnackbar->setBackgroundOpacity(0.8); // 设置背景透明度
    messageSnackbar->setFont(customFont1); // 设置字体大小
    messageSnackbar->setBoxWidth(1000); // 设置Snackbar的宽度
    messageSnackbar->setAutoHideDuration(3000); // 自动隐藏持续时间
    messageSnackbar->setClickToDismissMode(true); // 点击外部隐藏

    page->show();
    return page;
}

QWidget* SettingWindow::createVolumeSettingsPage()
{
    QWidget *page = new QWidget(this);

//    gameVolume=50;
//    buttonVolume=50;
//    propVolume=50;
//    boomVolume=50;
//    victoryVolume=50;
//    failVolume=50;
//    startVolume=50;

    start_volumeLabel = new QLabel(page);
    setupVolumeLabel(start_volumeLabel, QString("主音量: %2").arg(startVolume));
    start_volumeLabel->setGeometry(40, 60, 250, 75);

    button_volumeLabel = new QLabel(page);
    setupVolumeLabel(button_volumeLabel, QString("按钮音量: %2").arg(buttonVolume));
    button_volumeLabel->setGeometry(40, 310, 250, 75);

    boom_volumeLabel = new QLabel(page);
    setupVolumeLabel(boom_volumeLabel, QString("爆炸音量: %2").arg(boomVolume));
    boom_volumeLabel->setGeometry(40, 560, 250, 75);

    victory_volumeLabel = new QLabel(page);
    setupVolumeLabel(victory_volumeLabel, QString("胜利音量: %2").arg(victoryVolume));
    victory_volumeLabel->setGeometry(640, 30, 250, 75);

    fail_volumeLabel = new QLabel(page);
    setupVolumeLabel(fail_volumeLabel, QString("失败音量: %2").arg(failVolume));
    fail_volumeLabel->setGeometry(640, 230, 250, 75);

    prop_volumeLabel = new QLabel(page);
    setupVolumeLabel(prop_volumeLabel, QString("道具音量: %2").arg(propVolume));
    prop_volumeLabel->setGeometry(640, 430, 250, 75);

    main_volumeLabel = new QLabel(page);
    setupVolumeLabel(main_volumeLabel, QString("游戏音量: %2").arg(gameVolume));
    main_volumeLabel->setGeometry(640, 630, 250, 75);

    QtMaterialSlider *start_volumeSlider = new QtMaterialSlider(page);
    setupSlider(start_volumeSlider, startVolume);
    setSlide(start_volumeSlider, 40, 150, 400, 40);

    QtMaterialSlider *button_volumeSlider = new QtMaterialSlider(page);
    setupSlider(button_volumeSlider, buttonVolume);
    setSlide(button_volumeSlider, 40, 400, 400, 50);

    QtMaterialSlider *boom_volumeSlider = new QtMaterialSlider(page);
    setupSlider(boom_volumeSlider, boomVolume);
    setSlide(boom_volumeSlider, 40, 640, 400, 50);

    QtMaterialSlider *victory_volumeSlider = new QtMaterialSlider(page);
    setupSlider(victory_volumeSlider, victoryVolume);
    setSlide(victory_volumeSlider, 640, 120, 400, 50);

    QtMaterialSlider *fail_volumeSlider = new QtMaterialSlider(page);
    setupSlider(fail_volumeSlider, failVolume);
    setSlide(fail_volumeSlider, 640, 320, 400, 50);

    QtMaterialSlider *prop_volumeSlider = new QtMaterialSlider(page);
    setupSlider(prop_volumeSlider, propVolume);
    setSlide(prop_volumeSlider, 640, 520, 400, 50);

    QtMaterialSlider *main_volumeSlider = new QtMaterialSlider(page);
    setupSlider(main_volumeSlider, gameVolume);
    setSlide(main_volumeSlider, 640, 720, 400, 50);

    connect(main_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleMainVolumeChange);
    connect(button_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleButtonVolumeChange);
    connect(boom_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleBoomVolumeChange);
    connect(victory_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleVictoryVolumeChange);
    connect(fail_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleFailVolumeChange);
    connect(prop_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handlePropVolumeChange);
    connect(start_volumeSlider, &QtMaterialSlider::valueChanged, this, &SettingWindow::handleStartVolumeChange);

    page->show();
    return page;
}

QWidget* SettingWindow::createSkinSettingsPage()
{
    QWidget *page = new QWidget(this);

    QGraphicsView *view = new QGraphicsView(page);
    QGraphicsScene *scene = new QGraphicsScene(view);

    scene->setBackgroundBrush(QColor(186,203,214,100));
    view->setStyleSheet("background: transparent; border: none;"); // 设置背景透明和无边框
    view->setScene(scene);
    view->setGeometry(0, 0, 1200, 950);

    QPixmap tank1(":/resource/tank/3.png");
    QPixmap tank2(":/resource/tank/33.png");
    QPixmap tank3(":/resource/tank/333.png");
    QPixmap tank4(":/resource/tank/3333.png");
    QPixmap tank5(":/resource/tank/33333.png");
    QPixmap tank6(":/resource/tank/333333.png");

    item1 =  new GraphicsPicItem(tank1.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    item2 =  new GraphicsPicItem(tank2.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    item3 =  new GraphicsPicItem(tank3.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    item4 =  new GraphicsPicItem(tank4.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    item5 =  new GraphicsPicItem(tank5.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    item6 =  new GraphicsPicItem(tank6.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    item1->setPos(-20, 40);
    item2->setPos(550, 40);
    item3->setPos(-20, 340);
    item4->setPos(550, 340);
    item5->setPos(-20, 640);
    item6->setPos(550, 640);


    scene->addItem(item1);
    scene->addItem(item2);
    scene->addItem(item3);
    scene->addItem(item4);
    scene->addItem(item5);
    scene->addItem(item6);

    item1->m_selected=true;

    connect(item1, &GraphicsPicItem::clicked, this, &SettingWindow::chooseTank1);
    connect(item2, &GraphicsPicItem::clicked, this, &SettingWindow::chooseTank2);
    connect(item3, &GraphicsPicItem::clicked, this, &SettingWindow::chooseTank3);
    connect(item4, &GraphicsPicItem::clicked, this, &SettingWindow::chooseTank4);
    connect(item5, &GraphicsPicItem::clicked, this, &SettingWindow::chooseTank5);
    connect(item6, &GraphicsPicItem::clicked, this, &SettingWindow::chooseTank6);

    page->show();
    return page;
}

void SettingWindow::handleMainVolumeChange(int value)
{
    gameVolume = value;
    player_background->setVolume(gameVolume);
    main_volumeLabel->setText(QString("主音乐音量: %2").arg(value));
}

void SettingWindow::handleButtonVolumeChange(int value)
{
    buttonVolume = value;
    player_enterButton->setVolume(buttonVolume);
    button_volumeLabel->setText(QString("按钮音量: %2").arg(value));
}

void SettingWindow::handleBoomVolumeChange(int value)
{
    boomVolume = value;
    player_boom->setVolume(boomVolume);
    boom_volumeLabel->setText(QString("爆炸音量: %2").arg(value));
}

void SettingWindow::handleVictoryVolumeChange(int value)
{
    victoryVolume = value;
    player_victory->setVolume(victoryVolume);
    victory_volumeLabel->setText(QString("胜利音量: %2").arg(value));
}

void SettingWindow::handleFailVolumeChange(int value)
{
    failVolume = value;
    player_fail->setVolume(failVolume);
    fail_volumeLabel->setText(QString("失败音量: %2").arg(value));
}

void SettingWindow::handlePropVolumeChange(int value)
{
    propVolume = value;
    player_prop->setVolume(propVolume);
    prop_volumeLabel->setText(QString("道具音量: %2").arg(value));
}

void SettingWindow::handleStartVolumeChange(int value)
{
    startVolume = value;
    player_start->setVolume(startVolume);
    start_volumeLabel->setText(QString("主音量: %2").arg(value));
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
        if (currentKeyButton == KeyUpButton && (key==KeyUp || key_check(key)))
        {
            KeyUp = key;
            KeyUpButton->setText("上: " + keyText);
        }
        else if (currentKeyButton == keyDownButton && (key==KeyDown || key_check(key)))
        {
            KeyDown = key;
            keyDownButton->setText("下: " + keyText);
        }
        else if (currentKeyButton == KeyLeftButton && (key==KeyLeft || key_check(key)))
        {
            KeyLeft = key;
            KeyLeftButton->setText("左: " + keyText);
        }
        else if (currentKeyButton == KeyRightButton && (key==KeyRight || key_check(key)))
        {
            KeyRight = key;
            KeyRightButton->setText("右: " + keyText);
        }
        else if (currentKeyButton == KeyShootButton && (key==KeyShoot || key_check(key)))
        {
            KeyShoot = key;
            KeyShootButton->setText("射击: " + keyText);
        }
        else if (currentKeyButton == KeyProp1Button && (key==KeyProp1 || key_check(key)))
        {
            KeyProp1 =key;
            qDebug()<<"KeyProp1 setting:" << KeyProp1;
            KeyProp1Button->setText("道具一: " + keyText);
        }
        else if (currentKeyButton == KeyProp2Button && (key==KeyProp2 || key_check(key)))
        {
            KeyProp2 =key;
            KeyProp2Button->setText("道具二: " + keyText);
        }
        else if (currentKeyButton == KeyProp3Button && (key==KeyProp3 || key_check(key)))
        {
            KeyProp3 =key;
            KeyProp3Button->setText("道具三: " + keyText);
        }
        else if (currentKeyButton == KeyProp4Button && (key==KeyProp4 || key_check(key)))
        {
            KeyProp4 =key;
            KeyProp4Button->setText("道具四: " + keyText);
        }
        currentKeyButton = nullptr;
    }
}

bool SettingWindow::key_check(int key)
{
    if((key != KeyDown && key != KeyLeft && key != KeyRight && key != KeyUp && key != KeyShoot && key != KeyProp1 && key!= KeyProp2 && key!= KeyProp3 && key != KeyProp4))
    {
        return true;
    }
    else
    {
        qDebug()<<"1";
        messageSnackbar->addMessage("键位不能重复");
        return false;
    }
}

void SettingWindow::handleReturn()
{
    emit ret_sign();
}

void SettingWindow::setupButton(QtMaterialRaisedButton*& button)
{
    int fontId = QFontDatabase::addApplicationFont(Iron);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 28);

    button->setFont(customFont);
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
    int fontId = QFontDatabase::addApplicationFont(Iron);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 25);

    label->setFont(customFont);

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

void SettingWindow::chooseTank1()
{
    TankUp=":/resource/tank/3.png";
    TankRight=":/resource/tank/4.png";
    TankDown=":/resource/tank/1.png";
    TankLeft=":/resource/tank/2.png";
    item2->m_selected=false;item2->update();
    item3->m_selected=false;item3->update();
    item4->m_selected=false;item4->update();
    item5->m_selected=false;item5->update();
    item6->m_selected=false;item6->update();
}

void SettingWindow::chooseTank2()
{
    TankUp=":/resource/tank/33.png";
    TankRight=":/resource/tank/44.png";
    TankDown=":/resource/tank/11.png";
    TankLeft=":/resource/tank/22.png";
    item1->m_selected=false;item1->update();
    item3->m_selected=false;item3->update();
    item4->m_selected=false;item4->update();
    item5->m_selected=false;item5->update();
    item6->m_selected=false;item6->update();
}

void SettingWindow::chooseTank3()
{
    TankUp=":/resource/tank/333.png";
    TankRight=":/resource/tank/444.png";
    TankDown=":/resource/tank/111.png";
    TankLeft=":/resource/tank/222.png";
    item2->m_selected=false;item1->update();
    item1->m_selected=false;item2->update();
    item4->m_selected=false;item4->update();
    item5->m_selected=false;item5->update();
    item6->m_selected=false;item6->update();
}

void SettingWindow::chooseTank4()
{
    TankUp=":/resource/tank/3333.png";
    TankRight=":/resource/tank/4444.png";
    TankDown=":/resource/tank/1111.png";
    TankLeft=":/resource/tank/2222.png";
    item2->m_selected=false;item1->update();
    item3->m_selected=false;item2->update();
    item1->m_selected=false;item3->update();
    item5->m_selected=false;item5->update();
    item6->m_selected=false;item6->update();
}

void SettingWindow::chooseTank5()
{
    TankUp=":/resource/tank/33333.png";
    TankRight=":/resource/tank/44444.png";
    TankDown=":/resource/tank/11111.png";
    TankLeft=":/resource/tank/22222.png";
    item2->m_selected=false;item1->update();
    item3->m_selected=false;item2->update();
    item4->m_selected=false;item3->update();
    item1->m_selected=false;item4->update();
    item6->m_selected=false;item6->update();
}

void SettingWindow::chooseTank6()
{
    TankUp=":/resource/tank/333333.png";
    TankRight=":/resource/tank/444444.png";
    TankDown=":/resource/tank/111111.png";
    TankLeft=":/resource/tank/222222.png";
    item2->m_selected=false;item1->update();
    item3->m_selected=false;item2->update();
    item4->m_selected=false;item3->update();
    item5->m_selected=false;item4->update();
    item1->m_selected=false;item5->update();
}

bool SettingWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Enter)
    {
        player_enterButton->setPosition(0); // 将音效位置设置为开头，以便从头播放
        player_enterButton->play();
    }
    return QObject::eventFilter(obj, event);
}
