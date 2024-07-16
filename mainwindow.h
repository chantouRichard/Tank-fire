#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "SettingWindow.h"
#include "loginwindow.h"
#include "passWindow.h"
#include "historyscorewindow.h"
#include "global.h"
#include "qtmaterialflatbutton.h"
#include "qtmaterialautocomplete.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 构造函数
    MainWindow(QWidget *parent = nullptr);
    // 析构函数
    ~MainWindow();

private:
    // UI 对象指针
    Ui::MainWindow *ui;

    // 启动游戏按钮
    QtMaterialFlatButton* startGameButton;
    // 设置游戏按钮
    QtMaterialFlatButton* setGameButton;
    // 登录按钮
    QtMaterialFlatButton* loginButton;
    // 历史成绩按钮
    QtMaterialFlatButton* historyScoresButton;
    // 游戏标题标签
    QLabel* gameTitleLabel;
    // 设置窗口
    SettingWindow* setting_window;
    // 登录窗口
    LoginWindow* login_window;
    // 通过窗口
    PassWindow* pass_window;
    // 历史成绩窗口
    HistoryscoreWindow* His_scory_window;
    // 登录状态
    bool is_login;

    // 连接信号和槽
    void do_connect();
    // 设置按钮样式
    void setButtonStyle(QtMaterialFlatButton* button, bool enabled);
    // 更新按钮状态
    void updateButton(bool enabled);
    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    // 登录成功槽函数
    void login_success();
};

#endif // MAINWINDOW_H
