#ifndef PASS_H
#define PASS_H
#include<QPushButton>
#include <QWidget>
#include"level1.h"
#include"level2.h"
#include"level3.h"
#include"level4.h"
#include<QMovie>

namespace Ui {
class pass;
}

class pass : public QWidget
{
    Q_OBJECT

public:
    QPushButton * backbtn;

    explicit pass(QWidget *parent = nullptr);
    ~pass();

    //布尔数组
    bool pass_judge[4]={false,false,false,false};

    //改变pass_judge的函数
    void level1Win();
    void show_level();
    void setColor(QPushButton * btn);
    void colorChange(QPushButton * btn);
    int num=0;
    void setupLevel0Button(QPushButton *button, level1 *level, QPushButton *nextButton,QPushButton *nextNew);
    void setupLevel1Button(QPushButton *button, level2 *level, QPushButton *nextButton,QPushButton *nextNew);
    void setupLevel2Button(QPushButton *button, level3 *level, QPushButton *nextButton,QPushButton *nextNew);
    void setupLevel3Button(QPushButton *button, level4 *level);
    void setButtonStyle(QPushButton *btn);
    void HideAllGif();
    void HideAllButton();
    void StartButtonStyle(QPushButton *button);
    QLabel *gifLabel1;
    QLabel *gifLabel2;
    QLabel *gifLabel3;
    QLabel *gifLabel4;
    QMovie *movie1;
    QMovie *movie2;
    QMovie *movie3;
    QMovie *movie4;
    QPushButton *l1New;
    QPushButton *l2New;
    QPushButton *l3New;
    QPushButton *l4New;
    QPushButton *l1btn;
    QPushButton *l2btn;
    QPushButton *l3btn;
    QPushButton *l4btn;
signals:
    void back();



private:
    bool isConnected1;
    bool isConnected2;
    bool isConnected3;
    bool isConnected4;
private slots:
    void playGif(QMovie *movie,QLabel *gifLabel);
    void checkFrame(QMovie *movie);

};

#endif // PASS_H
