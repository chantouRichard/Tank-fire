#ifndef TANKWINDOW_H
#define TANKWINDOW_H

#include<QMainWindow>
#include<QTimer>
#include<QTime>
#include<QLabel>
#include<QPaintEvent>
#include<QDebug>
#include<QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class TankWindow; }
QT_END_NAMESPACE

class TankWindow : public QMainWindow
{
    Q_OBJECT

public:
    TankWindow(QWidget *parent = nullptr);
    ~TankWindow();

private slots:
    void on_level1Button_clicked();
    void on_endButton_clicked();
    void updateTimeDisplay();

private:
    Ui::TankWindow *ui;
    QTimer *timer;
    QTime startTime;
    QLabel *TimeLabel;
    QLabel *ST1;
    QLabel *ST2;
    QLabel *ST3;
    QPixmap star1;
    QPixmap star2;
    int time;
};
#endif
