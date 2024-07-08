#ifndef SETWINDOW_H
#define SETWINDOW_H
#include"global.h"
#include<QWidget>
#include<QSlider>
#include<QPushButton>
#include<QKeyEvent>
#include<QLabel>

class SettingWindow : public QWidget
{
    Q_OBJECT
public:

    explicit SettingWindow(QWidget *parent = nullptr);

private slots:
    void handleVolumeChange(int value);
    void handleKeyChange();
    bool key_check(int key);
private:
    QSlider* volumeSlider;
    QPushButton* returnButton;
    QPushButton* KeyUpButton;
    QPushButton* keyDownButton;
    QPushButton* KeyLeftButton;
    QPushButton* KeyRightButton;
    QPushButton* KeyShootButton;
    QLabel* volumeLabel;
    QLabel* gameTitleLabel;

    void keyPressEvent(QKeyEvent *event) override;
    QPushButton* currentKeyButton;

signals:
    void ret_sign();
};

#endif // SETWINDOW_H
