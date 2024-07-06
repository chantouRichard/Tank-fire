#include "loginwindow.h"
#include <QFile>
#include <QTextStream>
#include <QRegExpValidator>
#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include<QStringList>
#include<QResource>
#include<QTextStream>
#include<QLayout>
#include<QCoreApplication>
LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent)
{
    // 登录界面的大小
    this->setFixedSize(1000, 800); // 增大窗口大小

    // 设置布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter); // 居中对齐布局

    // 创建标签和输入框
    usernameLabel = new QLabel("账号", this);
    passwordLabel = new QLabel("密码", this);
    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password); // 输入加密
    hintLabel = nullptr; // 初始化 hintLabel 为 nullptr

    // 创建按钮
    loginButton = new QPushButton("登录", this);
    registerButton = new QPushButton("注册", this);

    // 设置按钮和输入框的更大大小
    loginButton->setMinimumSize(200, 60);
    registerButton->setMinimumSize(200, 60);
    usernameEdit->setMinimumSize(400, 50);
    passwordEdit->setMinimumSize(400, 50);

    // 将标签和输入框加入布局
    mainLayout->addWidget(usernameLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(usernameEdit, 0, Qt::AlignHCenter);
    mainLayout->addWidget(passwordLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(passwordEdit, 0, Qt::AlignHCenter);

    // 将按钮加入布局，并设置布局属性
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1); // 上方留白
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(registerButton);
    buttonLayout->addStretch(1); // 下方留白
    mainLayout->addLayout(buttonLayout);

    // 设置布局的外边距和间距
    mainLayout->setMargin(150); // 增大外边距
    mainLayout->setSpacing(30); // 增大控件之间的间距

    // 应用 CSS 样式
    setStyleSheet("QWidget { background-color: #f9f9f9; }"
                  "QLabel { font-size: 24px; color: #333; }"
                  "QLineEdit { border: 1px solid #ddd; border-radius: 8px; padding: 15px; font-size: 18px; }"
                  "QPushButton { font-size: 20px; border-radius: 8px; background-color: #5cb85c; color: white; border: none; padding: 15px; }"
                  "QPushButton:hover { background-color: #4cae4c; }"
                  "QPushButton:pressed { background-color: #449d44; }"
                  "QLineEdit:focus { border: 2px solid #5cb85c; }"
                  "QLabel { margin-bottom: 20px; }");

    // 连接信号和槽

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::on_loginButton_clicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::on_reginButton_clicked);
    connect(this, &LoginWindow::success_to_enter, this, [=]() {
        this->hide();
    });
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
    runPath.replace(QString("/"),QString("\\"));qDebug()<<runPath;

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
    runPath.replace(QString("/"),QString("\\"));qDebug()<<runPath;

    QFile file1(runPath);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file:" << file1.errorString();
        return ;
    }

    QTextStream in(&file1);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList data = line.split(":"); // 假设账号和密码以":"分隔
        if (username == data[0])
        {
            QMessageBox::information(this,"提醒","该账号已存在");
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

