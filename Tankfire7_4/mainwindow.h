#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"passWindow.h"
#include"global.h"
#include <QMainWindow>
#include<QPushButton>
#include<QLabel>
#include"SettingWindow.h"
#include"loginwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPushButton* startGameButton,* setGameButton,*loginButton;
    QLabel* gameTitleLabel;
    SettingWindow* setting_window;
    LoginWindow* login_window;
    pass* pass_window;
    bool is_login;
    void setButtonStyle(QPushButton* button,bool enabled);
    void updateButton(bool enabled);
private slots:
//    void on_startGameButton_clicked();
    void login_success();

};
#endif // MAINWINDOW_H
