#include "global.h"
#include<Qt>

//键位模块
int KeyUp=Qt::Key_W;
int KeyLeft=Qt::Key_A;
int KeyRight=Qt::Key_D;
int KeyDown=Qt::Key_S;
int KeyShoot=Qt::Key_J;
int KeyProp1=Qt::Key_1;
int KeyProp2=Qt::Key_2;
int KeyProp3=Qt::Key_3;
int KeyProp4=Qt::Key_4;

//文件模块
QString filename="/User.txt";
QString score_filename="/Score.txt";
QString User_name="";
//音乐模块
int gameVolume=50;
int buttonVolumn=50;
int propVolume=50;
int boomVolumn=50;
int victoryVolume=50;
int failVolume=50;
QMediaPlayer* player_background=new QMediaPlayer(nullptr);
QMediaPlayer* player_boom=new QMediaPlayer(nullptr);
QMediaPlayer* player_enterButton=new QMediaPlayer(nullptr);
QMediaPlayer* player_victory=new QMediaPlayer(nullptr);
QMediaPlayer* player_fail=new QMediaPlayer(nullptr);
QMediaPlayer* player_prop=new QMediaPlayer(nullptr);

//素材路径
QString main_back_pic=":/resource/background/main_page.jpg";
QString login_back_pic=":/resource/background/login_back.jpg";
QString setting_back_pic=":/resource/background/setting_page.jpg";
QString score_back_pic=":/resource/background/score_page.jpg";
QString main_music=":/resource/music/background.wav";
QString button_enter=":/resource/music/buttonEnter.wav";
QString setting_tank=":/resource/other/tank.png";
QString setting_bullet=":/resource/other/bullet.png";
QString setting_prop=":/resource/other/prop.png";
//坦克子弹模块
int bulletsnumber=5;
QString TankUp=":/resource/tank/3.png";
QString TankRight=":/resource/tank/4.png";
QString TankDown=":/resource/tank/1.png";
QString TankLeft=":/resource/tank/2.png";
//字体模块
QString DottedFont=":/resource/my_font/DottedSongtiSquareRegular.otf";
QString AI=":/resource/my_font/AI.ttf";
QString Titleround=":/resource/my_font/titleround.otf";
QString WinteCicada=":/resource/my_font/winter_cicada.ttf";
QString Iron=":/resource/my_font/iron.ttf";
QString Ink=":/resource/my_font/ink.ttf";
//地图模块
int MAP_Global[Mapy_size][Mapx_size] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};


