#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
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
private slots:
    void handleMainVolumeChange(int value);
    void handleButtonVolumeChange(int value);
    void handleBoomVolumeChange(int value);
    void handleVictoryVolumeChange(int value);
    void handleFailVolumeChange(int value);
    void handlePropVolumeChange(int value);
    void handleKeyChange();
    void handleReturn();

signals:
    void ret_sign();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool key_check(int key);

    int gameVolume;
    int KeyUp, KeyDown, KeyLeft, KeyRight, KeyShoot;

    QLabel *main_volumeLabel;
    QLabel *button_volumeLabel;
    QLabel *boom_volumeLabel;
    QLabel *victory_volumeLabel;
    QLabel *fail_volumeLabel;
    QLabel *prop_volumeLabel;
    QtMaterialSlider *main_volumeSlider;
    QtMaterialSlider *button_volumeSlider;
    QtMaterialSlider *boom_volumeSlider;
    QtMaterialSlider *victory_volumeSlider;
    QtMaterialSlider *fail_volumeSlider;
    QtMaterialSlider *prop_volumeSlider;
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
