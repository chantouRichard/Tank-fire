#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "global.h"
#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include "simplebutton.h"
#include "qtmaterialautocomplete.h"

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
    QtMaterialAutoComplete* usernameEdit;
    QtMaterialAutoComplete* passwordEdit;
    HoverFillButton* loginButton;
    HoverFillButton* registerButton;
    QLabel* titleLabel;
    QLabel* backgroundLabel;
    QWidget* canvas;
    QTimer* timer;

    bool checkLogin(const QString& username, const QString& password);
    void centerCanvas();
};

#endif // LOGINWINDOW_H
