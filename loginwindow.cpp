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

    // 设置布局
    mainLayout = new QVBoxLayout(canvas);
    mainLayout->setAlignment(Qt::AlignCenter); // 居中对齐布局

    titleLabel = new QLabel("Login", this);
    titleLabel->setStyleSheet("color: rgba(0, 0, 0, 150); font-size: 58px; font-weight: bold; background-color: transparent;"); // 设置半透明字体颜色和透明背景
    titleLabel->setAlignment(Qt::AlignCenter);
    int fontId = QFontDatabase::addApplicationFont(DottedFont);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 16);
    titleLabel->setFont(customFont);

    // 创建标签和输入框
    usernameEdit = new QtMaterialAutoComplete(this);
    usernameEdit->setPlaceholderText(" Username");
    usernameEdit->setStyleSheet("color: black; font-size: 24px;"); // 设置字体颜色为黑色，并调整字体大小

    passwordEdit = new QtMaterialAutoComplete(this);
    passwordEdit->setPlaceholderText(" Password");
    passwordEdit->setEchoMode(QLineEdit::Password); // 输入加密
    passwordEdit->setStyleSheet("color: black; font-size: 24px;"); // 设置字体颜色为黑色

    loginButton = new HoverFillButton(this, HoverFillButton::AnimationType::CrossFill);
    loginButton->setText("登录");
    loginButton->setFillBrush(QBrush(QColor("#00AA73")));
    loginButton->setTextColor(QColor("#87CEEB"), QColor("#FFFFFF"));
    loginButton->setRadius(30);

    registerButton = new HoverFillButton(this, HoverFillButton::AnimationType::CrossFill);
    registerButton->setText("注册");
    registerButton->setFillBrush(QBrush(QColor("#00AA73")));
    registerButton->setTextColor(QColor("#87CEEB"), QColor("#FFFFFF"));
    registerButton->setRadius(30);

    // 设置按钮和输入框的更大大小
    loginButton->setMinimumSize(250, 80);
    registerButton->setMinimumSize(250, 80);
    usernameEdit->setMinimumSize(500, 70);
    passwordEdit->setMinimumSize(500, 70);

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
        QMessageBox::critical(this, "登录失败", "账号或密码有误");
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
        QMessageBox::warning(this, "注册失败", "账号和密码不能为空");
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
            QMessageBox::information(this, "提醒", "该账号已存在");
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
    QMessageBox::information(this, "注册成功", "账号注册成功，请重新运行，并使用注册的账号登录。");
}
