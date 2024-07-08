#ifndef PASS_H
#define PASS_H
#include<QPushButton>
#include <QWidget>
#include"level1.h"
#include"level2.h"
#include"level3.h"
#include"level4.h"

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

    void setupLevel0Button(QPushButton *button, level1 *level, QPushButton *nextButton);
    void setupLevel1Button(QPushButton *button, level2 *level, QPushButton *nextButton);
    void setupLevel2Button(QPushButton *button, level3 *level, QPushButton *nextButton);
    void setupLevel3Button(QPushButton *button, level4 *level);
    void setButtonStyle(QPushButton *btn);
signals:
    void back();

private:
    Ui::pass *ui;
};

#endif // PASS_H
