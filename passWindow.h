#ifndef PASS_H
#define PASS_H

#include <QPushButton>
#include <QWidget>
#include <QMovie>
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "transimplebutton.h"
#include "simplebutton.h"

namespace Ui {
class PassWindow;
}

class PassWindow : public QWidget
{
    Q_OBJECT

public:
    // 构造函数
    explicit PassWindow(QWidget *parent = nullptr);
    // 析构函数
    ~PassWindow();

    // 返回按钮
    transimplebutton *backbtn;

    // 布尔数组，表示关卡通过状态
    bool pass_judge[4] = {false, false, false, false};

    // 改变 pass_judge 的函数
    void level1Win();
    void show_level();

    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *event);

    // 设置关卡按钮
    void setupLevel0Button(QPushButton *button, level1 *level, QPushButton *nextButton, QPushButton *nextNew);
    void setupLevel1Button(QPushButton *button, level2 *level, QPushButton *nextButton, QPushButton *nextNew);
    void setupLevel2Button(QPushButton *button, level3 *level, QPushButton *nextButton, QPushButton *nextNew);
    void setupLevel3Button(QPushButton *button, level4 *level);

    // 设置按钮样式
    void setButtonStyle(transimplebutton*& btn);
    void StartButtonStyle(HoverFillButton *button);

    // 隐藏所有 GIF
    void HideAllGif();
    // 隐藏所有按钮
    void HideAllButton();

    // 修改分数
    void modifyScore(QString file_name);

    // GIF 标签
    QLabel *gifLabel1;
    QLabel *gifLabel2;
    QLabel *gifLabel3;
    QLabel *gifLabel4;

    // 关卡说明
    QLabel *GameLine;
    QLabel *BackGround;

    // GIF 动画
    QMovie *movie1;
    QMovie *movie2;
    QMovie *movie3;
    QMovie *movie4;

    // 新关卡按钮
    transimplebutton *l1New;
    transimplebutton *l2New;
    transimplebutton *l3New;
    transimplebutton *l4New;

    // 关卡按钮
    HoverFillButton *l1btn;
    HoverFillButton *l2btn;
    HoverFillButton *l3btn;
    HoverFillButton *l4btn;

signals:
    void back();
    void play_music();

private:
    // 是否已连接
    bool isConnected1;
    bool isConnected2;
    bool isConnected3;
    bool isConnected4;

private slots:
    // 播放 GIF
    void playGif(QMovie *movie, QLabel *gifLabel);
    // 检查帧
    void checkFrame(QMovie *movie);
};

void paintEvent(QPaintEvent *);

#endif // PASS_H
