#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "mygraphicspicitem.h"
#include <QSlider>
#include <QLabel>
#include <QKeyEvent>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include "qtmaterialtabs.h"
#include "qtmaterialraisedbutton.h"
#include"qtmaterialslider.h"
#include"simplebutton.h"
#include "qtmaterialsnackbar.h" // include snackbar header
class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);

    void setupButton(QtMaterialRaisedButton*& button);
    void setPositionAndsize(QtMaterialRaisedButton*& button,int x,int y,int width,int height);
    void setupVolumeLabel(QLabel *&label, const QString &text);
    void setupSlider(QtMaterialSlider *&slider, int volume);
    void setSlide(QtMaterialSlider *&slider, int x, int y, int width, int height);
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void handleMainVolumeChange(int value);
    void handleButtonVolumeChange(int value);
    void handleBoomVolumeChange(int value);
    void handleVictoryVolumeChange(int value);
    void handleFailVolumeChange(int value);
    void handlePropVolumeChange(int value);
    void handleStartVolumeChange(int value);
    void handleKeyChange();
    void handleReturn();
    void chooseTank1();
    void chooseTank2();
    void chooseTank3();
    void chooseTank4();
    void chooseTank5();
    void chooseTank6();

signals:
    void ret_sign();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool key_check(int key);

    int gameVolume;
    int KeyUp, KeyDown, KeyLeft, KeyRight, KeyShoot;

    QLabel *main_volumeLabel;   //游戏中的循环音乐
    QLabel *button_volumeLabel; //进入按钮的音乐
    QLabel *boom_volumeLabel;   //敌人爆炸的音乐
    QLabel *victory_volumeLabel;//胜利
    QLabel *fail_volumeLabel;   //失败
    QLabel *prop_volumeLabel;   //捡到道具
    QLabel* start_volumeLabel;  //主界面音乐
    QtMaterialSlider *main_volumeSlider;
    QtMaterialSlider *button_volumeSlider;
    QtMaterialSlider *boom_volumeSlider;
    QtMaterialSlider *victory_volumeSlider;
    QtMaterialSlider *fail_volumeSlider;
    QtMaterialSlider *prop_volumeSlider;
    QtMaterialSlider *start_volumeSlider;
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
    QtMaterialSnackbar* messageSnackbar;

    GraphicsPicItem *item1;
    GraphicsPicItem *item2;
    GraphicsPicItem *item3;
    GraphicsPicItem *item4;
    GraphicsPicItem *item5;
    GraphicsPicItem *item6;

    QWidget *createKeySettingsPage();
    QWidget *createVolumeSettingsPage();
    QWidget *createSkinSettingsPage();

    QtMaterialTabs *tabs;
    QWidget *keySettingsPage;
    QWidget *volumeSettingsPage;
    QWidget *skinSettingsPage;

    bool m_useThemeColors;
    bool m_showHalo;
    Material::RippleStyle m_rippleStyle;
    QColor m_inkColor;
    QColor m_backgroundColor;
    QColor m_textColor;

    QWidget *mainCanvas;
};

#endif // SETTINGWINDOW_H
