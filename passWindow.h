#ifndef PASS_H
#define PASS_H
#include<QPushButton>
#include <QWidget>
#include"level1.h"
#include"level2.h"
#include"level3.h"
#include"level4.h"
#include<QMovie>
#include"transimplebutton.h"
#include"simplebutton.h"
namespace Ui {
class PassWindow;
}

class PassWindow : public QWidget
{
    Q_OBJECT

public:
    transimplebutton * backbtn;

    explicit PassWindow(QWidget *parent = nullptr);
    ~PassWindow();

    //布尔数组

    bool pass_judge[4]={false,false,false,false};

    //改变pass_judge的函数
    void level1Win();
    void show_level();
//    void setColor(QPushButton * btn);
//    void colorChange(QPushButton * btn);
    int num=0;
    bool eventFilter(QObject *obj, QEvent *event);
    void setupLevel0Button(QPushButton *button, level1 *level, QPushButton *nextButton,QPushButton *nextNew);
    void setupLevel1Button(QPushButton *button, level2 *level, QPushButton *nextButton,QPushButton *nextNew);
    void setupLevel2Button(QPushButton *button, level3 *level, QPushButton *nextButton,QPushButton *nextNew);
    void setupLevel3Button(QPushButton *button, level4 *level);
    void setButtonStyle(transimplebutton*& btn);
    void HideAllGif();
    void HideAllButton();
    void StartButtonStyle(HoverFillButton *button);
    QLabel *gifLabel1;
    QLabel *gifLabel2;
    QLabel *gifLabel3;
    QLabel *gifLabel4;
    QMovie *movie1;
    QMovie *movie2;
    QMovie *movie3;
    QMovie *movie4;
    transimplebutton *l1New;
    transimplebutton *l2New;
    transimplebutton *l3New;
    transimplebutton *l4New;
    HoverFillButton *l1btn;
    HoverFillButton *l2btn;
    HoverFillButton *l3btn;
    HoverFillButton *l4btn;
signals:
    void back();
    void play_music();
private:
    bool isConnected1;
    bool isConnected2;
    bool isConnected3;
    bool isConnected4;
private slots:
    void playGif(QMovie *movie,QLabel *gifLabel);
    void checkFrame(QMovie *movie);

};

void paintEvent(QPaintEvent *);

#endif // PASS_H
