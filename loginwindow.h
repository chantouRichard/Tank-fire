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
#include"global.h"
#include "simplebutton.h"
#include "qtmaterialautocomplete.h"
#include "qtmaterialsnackbar.h" // include snackbar header

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
    QtMaterialSnackbar *messageSnackbar;
    QVBoxLayout *mainLayout;
    QtMaterialAutoComplete* usernameEdit;
    QtMaterialAutoComplete* passwordEdit;
    HoverFillButton* loginButton;
    HoverFillButton* registerButton;
    QLabel* titleLabel;
    QLabel* backgroundLabel;
    QWidget* canvas;
    QTimer* timer;
    void showMessageSnackbar(const QString &message);
    bool checkLogin(const QString& username, const QString& password);
    bool eventFilter(QObject *obj, QEvent *event);
    void centerCanvas();
};

#endif // LOGINWINDOW_H
