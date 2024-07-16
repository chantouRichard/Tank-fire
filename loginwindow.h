#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include "global.h"
#include "simplebutton.h"
#include "qtmaterialautocomplete.h"
#include "qtmaterialsnackbar.h" // 包含 snackbar 头文件

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    // 构造函数
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    // 登录按钮点击事件处理函数
    void on_loginButton_clicked();
    // 注册按钮点击事件处理函数
    void on_reginButton_clicked();

signals:
    // 登录成功信号
    void success_to_enter();
    // 隐藏主窗口信号
    void HideMainWindow();

private:
    // 显示消息的 Snackbar
    QtMaterialSnackbar *messageSnackbar;
    // 主布局
    QVBoxLayout *mainLayout;
    // 用户名输入框
    QtMaterialAutoComplete* usernameEdit;
    // 密码输入框
    QtMaterialAutoComplete* passwordEdit;
    // 登录按钮
    HoverFillButton* loginButton;
    // 注册按钮
    HoverFillButton* registerButton;
    // 标题标签
    QLabel* titleLabel;
    // 背景标签
    QLabel* backgroundLabel;
    // 画布
    QWidget* canvas;
    // 计时器
    QTimer* timer;

    // 显示 Snackbar 消息
    void showMessageSnackbar(const QString &message);
    // 检查登录信息
    bool checkLogin(const QString& username, const QString& password);
    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *event);
    // 居中画布
    void centerCanvas();
};

#endif // LOGINWINDOW_H
