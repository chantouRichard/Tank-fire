#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "mygraphicspicitem.h"
#include <QSlider>
#include <QLabel>
#include <QKeyEvent>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "qtmaterialtabs.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialslider.h"
#include "simplebutton.h"
#include "qtmaterialsnackbar.h" // 包含 snackbar 头文件

class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    // 构造函数
    explicit SettingWindow(QWidget *parent = nullptr);

    // 设置按钮
    void setupButton(QtMaterialRaisedButton*& button);
    // 设置按钮位置和大小
    void setPositionAndsize(QtMaterialRaisedButton*& button, int x, int y, int width, int height);
    // 设置音量标签
    void setupVolumeLabel(QLabel *&label, const QString &text);
    // 设置滑块
    void setupSlider(QtMaterialSlider *&slider, int volume);
    // 设置滑块位置和大小
    void setSlide(QtMaterialSlider *&slider, int x, int y, int width, int height);
    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    // 音量变化处理函数
    void handleMainVolumeChange(int value);
    void handleButtonVolumeChange(int value);
    void handleBoomVolumeChange(int value);
    void handleVictoryVolumeChange(int value);
    void handleFailVolumeChange(int value);
    void handlePropVolumeChange(int value);
    void handleStartVolumeChange(int value);
    // 按键处理函数
    void handleKeyChange();
    void handleReturn();
    // 选择坦克
    void chooseTank1();
    void chooseTank2();
    void chooseTank3();
    void chooseTank4();
    void chooseTank5();
    void chooseTank6();

signals:
    // 返回信号
    void ret_sign();

protected:
    // 按键事件处理函数
    void keyPressEvent(QKeyEvent *event) override;

private:
    // 检查按键
    bool key_check(int key);

    // 标签
    QLabel *main_volumeLabel;   // 游戏中的循环音乐
    QLabel *button_volumeLabel; // 进入按钮的音乐
    QLabel *boom_volumeLabel;   // 敌人爆炸的音乐
    QLabel *victory_volumeLabel;// 胜利
    QLabel *fail_volumeLabel;   // 失败
    QLabel *prop_volumeLabel;   // 捡到道具
    QLabel *start_volumeLabel;  // 主界面音乐

    // 滑块
    QtMaterialSlider *main_volumeSlider;
    QtMaterialSlider *button_volumeSlider;
    QtMaterialSlider *boom_volumeSlider;
    QtMaterialSlider *victory_volumeSlider;
    QtMaterialSlider *fail_volumeSlider;
    QtMaterialSlider *prop_volumeSlider;
    QtMaterialSlider *start_volumeSlider;

    // 按钮
    QtMaterialRaisedButton *KeyUpButton;
    QtMaterialRaisedButton *keyDownButton;
    QtMaterialRaisedButton *KeyLeftButton;
    QtMaterialRaisedButton *KeyRightButton;
    QtMaterialRaisedButton *KeyShootButton;
    QtMaterialRaisedButton *KeyProp1Button;
    QtMaterialRaisedButton *KeyProp2Button;
    QtMaterialRaisedButton *KeyProp3Button;
    QtMaterialRaisedButton *KeyProp4Button;
    QtMaterialRaisedButton *currentKeyButton;
    HoverFillButton *returnButton;

    // Snackbar 消息
    QtMaterialSnackbar* messageSnackbar;

    // 图片项
    GraphicsPicItem *item1;
    GraphicsPicItem *item2;
    GraphicsPicItem *item3;
    GraphicsPicItem *item4;
    GraphicsPicItem *item5;
    GraphicsPicItem *item6;

    // 创建设置页面
    QWidget *createKeySettingsPage();
    QWidget *createVolumeSettingsPage();
    QWidget *createSkinSettingsPage();

    // 标签页
    QtMaterialTabs *tabs;
    QWidget *keySettingsPage;
    QWidget *volumeSettingsPage;
    QWidget *skinSettingsPage;

    // 主题颜色设置
    bool m_useThemeColors;
    bool m_showHalo;
    Material::RippleStyle m_rippleStyle;
    QColor m_inkColor;
    QColor m_backgroundColor;
    QColor m_textColor;

    // 主画布
    QWidget *mainCanvas;
};

#endif // SETTINGWINDOW_H
