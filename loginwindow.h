#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include"global.h"
#include <QMainWindow>
#include <QWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QMessageBox>
#include<QString>
#include<QLabel>
#include<QVBoxLayout>
class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void on_loginButton_clicked();
    void on_reginButton_clicked();

signals:
    void success_to_enter();
    void HideMainWindow();
private:
    QVBoxLayout *mainLayout;
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QPushButton* loginButton;
    QPushButton* registerButton;
    QLabel* usernameLabel;
    QLabel* passwordLabel;
    QLabel *hintLabel;
    bool checkLogin(const QString& username,const QString& password);

};

#endif // LOGINWINDOW_H
