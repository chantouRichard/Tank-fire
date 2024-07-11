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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QtMaterialFlatButton* startGameButton;
    QtMaterialFlatButton* setGameButton;
    QtMaterialFlatButton* loginButton;
    QtMaterialFlatButton* historyScoresButton;
    QLabel* gameTitleLabel;
    SettingWindow* setting_window;
    LoginWindow* login_window;
    PassWindow* pass_window;
    HistoryscoreWindow* His_scory_window;
    bool is_login;

    void do_connect();
    void setButtonStyle(QtMaterialFlatButton* button, bool enabled);
    void updateButton(bool enabled);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void login_success();
};

#endif // MAINWINDOW_H
