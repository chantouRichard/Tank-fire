#include "loginwindow.h"
#include <QFile>
#include <QTextStream>
#include <QRegExpValidator>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>
#include <QResource>
#include <QTextStream>
#include <QLayout>
#include <QCoreApplication>
#include <QFontDatabase>
#include <QTimer>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent)
{
    // 设置无边框和窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(2000, 1200); // 增大窗口大小

    // 设置背景图片
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(login_back_pic).scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    backgroundLabel->setGeometry(0, 0, 2000, 1200);
    backgroundLabel->lower(); // 确保背景图片在最底层

    // 创建无边框的半透明白色画布
    canvas = new QWidget(this);
    canvas->setStyleSheet("background-color: rgba(255, 255, 255, 200); border-radius: 15px;");
    canvas->setGeometry((this->width() - 800) / 2, (this->height() - 600) / 2, 800, 600); // 调整画布位置和大小

    // 添加阴影效果
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 160));
    shadowEffect->setOffset(0, 0);
    canvas->setGraphicsEffect(shadowEffect);

    // 设置布局
    mainLayout = new QVBoxLayout(canvas);
    mainLayout->setAlignment(Qt::AlignCenter); // 居中对齐布局

    titleLabel = new QLabel("Login", this);
    titleLabel->setStyleSheet("color: rgba(0, 0, 0, 150); font-size: 68px; font-weight: bold; background-color: transparent;"); // 设置半透明字体颜色和透明背景
    titleLabel->setAlignment(Qt::AlignCenter);
    int fontId = QFontDatabase::addApplicationFont(DottedFont);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 20);
    titleLabel->setFont(customFont);

    // 创建标签和输入框
    usernameEdit = new QtMaterialAutoComplete(this);
    usernameEdit->setPlaceholderText(" Username");
    usernameEdit->setStyleSheet("color: black; font-size: 24px;"); // 设置字体颜色为黑色，并调整字体大小

    passwordEdit = new QtMaterialAutoComplete(this);
    passwordEdit->setPlaceholderText(" Password");
    passwordEdit->setEchoMode(QLineEdit::Password); // 输入加密
    passwordEdit->setStyleSheet("color: black; font-size: 24px;"); // 设置字体颜色为黑色

    usernameEdit->setAccessibleName("账户");
    usernameEdit->setAccessibleDescription("input username");

    passwordEdit->setAccessibleName("密码");
    passwordEdit->setAccessibleDescription("input password");

    int fontId1 = QFontDatabase::addApplicationFont(Iron);
    QString fontFamily1 = QFontDatabase::applicationFontFamilies(fontId1).at(0);
    QFont customFont1(fontFamily1, 12);

    loginButton = new HoverFillButton(this, HoverFillButton::AnimationType::CrossFill);
    loginButton->setText("登录");
    loginButton->setFillBrush(QBrush(QColor("#00AA73")));
    loginButton->setTextColor(QColor("#87CEEB"), QColor("#FFFFFF"));
    loginButton->setRadius(30);
    loginButton->setFont(customFont1);

    registerButton = new HoverFillButton(this, HoverFillButton::AnimationType::CrossFill);
    registerButton->setText("注册");
    registerButton->setFillBrush(QBrush(QColor("#00AA73")));
    registerButton->setTextColor(QColor("#87CEEB"), QColor("#FFFFFF"));
    registerButton->setRadius(30);
    registerButton->setFont(customFont1);

    // 设置按钮和输入框的更大大小
    loginButton->setMinimumSize(250, 80);
    registerButton->setMinimumSize(250, 80);
    usernameEdit->setMinimumSize(500, 70);
    passwordEdit->setMinimumSize(500, 70);

    //设置按钮音效
    loginButton->installEventFilter(this);
    registerButton->installEventFilter(this);

    // 将标题加入布局
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);

    // 将标签和输入框加入布局
    QHBoxLayout* userLayout = new QHBoxLayout;
    userLayout->addSpacing(30); // 调整图像和输入行之间的间隔
    QLabel* userIcon = new QLabel(this);
    userIcon->setPixmap(QPixmap(":/login/Res/res6/pic/user_name.png").scaled(58, 58, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    userIcon->setStyleSheet("background-color: transparent;"); // 背景设置为完全透明
    userLayout->addWidget(userIcon);
    userLayout->addWidget(usernameEdit);
    mainLayout->addLayout(userLayout);

    QHBoxLayout* pwdLayout = new QHBoxLayout;
    pwdLayout->addSpacing(30); // 调整图像和输入行之间的间隔
    QLabel* pwdIcon = new QLabel(this);
    pwdIcon->setPixmap(QPixmap(":/login/Res/res6/pic/pwd.png").scaled(58, 58, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    pwdIcon->setStyleSheet("background-color: transparent;"); // 背景设置为完全透明
    pwdLayout->addWidget(pwdIcon);
    pwdLayout->addWidget(passwordEdit);
    mainLayout->addLayout(pwdLayout);

    // 将按钮加入布局，并设置布局属性
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1); // 上方留白
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(registerButton);
    buttonLayout->addStretch(1); // 下方留白
    mainLayout->addLayout(buttonLayout);

    // 设置布局的外边距和间距
    mainLayout->setMargin(50); // 增大外边距
    mainLayout->setSpacing(40); // 增大控件之间的间距

    // 初始化消息对话框
    messageSnackbar = new QtMaterialSnackbar(this);
    messageSnackbar->setBackgroundColor(QColor(232,230,240)); // 设置背景颜色
    messageSnackbar->setTextColor(QColor(58,46,121)); // 设置文字颜色
    messageSnackbar->setBackgroundOpacity(0.8); // 设置背景透明度
    messageSnackbar->setFont(customFont1); // 设置字体大小
    messageSnackbar->setBoxWidth(1000); // 设置Snackbar的宽度
    messageSnackbar->setAutoHideDuration(3000); // 自动隐藏持续时间
    messageSnackbar->setClickToDismissMode(true); // 点击外部隐藏


    // 连接信号和槽
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::on_loginButton_clicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::on_reginButton_clicked);
    connect(this, &LoginWindow::success_to_enter, this, [=]() {
        this->hide();
    });

    // 画布始终位于窗口中心
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LoginWindow::centerCanvas);
    timer->start(100);
}

void LoginWindow::centerCanvas()
{
    canvas->move((this->width() - canvas->width()) / 2, (this->height() - canvas->height()) / 2);
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    if (checkLogin(username, password))
        emit success_to_enter();
    else
        showMessageSnackbar("账号或密码错误"); // 显示登录失败
}

bool LoginWindow::checkLogin(const QString &username, const QString &password)
{
    QString runPath = QCoreApplication::applicationDirPath() + filename;
    runPath.replace(QString("/"), QString("\\"));
    qDebug() << runPath;

    QFile file(runPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file:" << file.errorString();
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList data = line.split(":"); // 假设账号和密码以":"分隔
        if (data.size() == 2 && username == data[0] && password == data[1]) {
            User_name = username;
            file.close();
            return true; // 登录成功
        }
    }
    file.close();
    return false; // 登录失败
}

void LoginWindow::on_reginButton_clicked()
{
    // 处理注册信息
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    // 确保用户名和密码不为空
    if (username.isEmpty() || password.isEmpty()) {
        showMessageSnackbar("账号和密码不能为空"); // 显示注册失败消息
        return;
    }

    QString runPath = QCoreApplication::applicationDirPath() + filename;
    runPath.replace(QString("/"), QString("\\"));
    qDebug() << runPath;

    QFile file1(runPath);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file:" << file1.errorString();
        return;
    }

    QTextStream in(&file1);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList data = line.split(":"); // 假设账号和密码以":"分隔
        if (username == data[0])
        {
            showMessageSnackbar("该账号已存在"); // 显示账号已存在消息
            file1.close();
            return;
        }
    }

    QFile file(runPath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Unable to open file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << username << ":" << password << "\n"; // 使用 QTextStream 写入
    file.close();

    // 显示注册成功的消息
    showMessageSnackbar("账号注册成功"); // 显示注册成功消息
}

void LoginWindow::showMessageSnackbar(const QString &message)
{
    messageSnackbar->addMessage(message);
}

bool LoginWindow::eventFilter(QObject *obj, QEvent *event)
{
     if (event->type() == QEvent::Enter)
     {
         player_enterButton->setPosition(0); // 将音效位置设置为开头，以便从头播放
         player_enterButton->play();
     }
     return QObject::eventFilter(obj, event);
}
