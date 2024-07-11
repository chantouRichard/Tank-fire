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
int buttonVolume=50;
int propVolume=50;
int boomVolume=50;
int victoryVolume=50;
int failVolume=50;
int startVolume=50;
QMediaPlayer* player_background=new QMediaPlayer(nullptr);
QMediaPlayer* player_boom=new QMediaPlayer(nullptr);
QMediaPlayer* player_enterButton=new QMediaPlayer(nullptr);
QMediaPlayer* player_victory=new QMediaPlayer(nullptr);
QMediaPlayer* player_fail=new QMediaPlayer(nullptr);
QMediaPlayer* player_prop=new QMediaPlayer(nullptr);
QMediaPlayer* player_start=new QMediaPlayer(nullptr);
QString start_wav="qrc:/resource/music/start_window.wav";
QString button_wav="qrc:/resource/music/buttonEnter.wav";
QString boom_wav="qrc:/resource/music/enemy_boom.mp3";
QString prop_wav="qrc:/resource/music/Prop.mp4";
QString main_wav="qrc:/resource/music/main_melody.m4a";

//素材路径
QString main_back_pic=":/resource/background/main_page.jpg";
QString login_back_pic=":/resource/background/login_back.jpg";
QString setting_back_pic=":/resource/background/setting_page.jpg";
QString score_back_pic=":/resource/background/score_page.jpg";
QString pass_page_pic=":/resource/background/pass_page.jpg";
QString main_music=":/resource/music/background.wav";
QString button_enter=":/resource/music/buttonEnter.wav";
QString setting_tank=":/resource/other/tank.png";
QString setting_bullet=":/resource/other/bullet.png";
QString setting_prop=":/resource/other/prop.png";
QString level1_0=":/resource/map/level1_0.jpg";
QString level1_1=":/resource/map/level1_1.jpg";
QString level1_2=":/resource/map/level1_2.png";
QString level1_3=":/resource/map/level1_3.jpg";
QString level1_4=":/resource/map/level1_4.jpg";
QString prop1_pic=":/resource/other/Prop1_pic.png";
QString prop2_pic=":/resource/other/Prop2_pic.png";
QString prop3_pic=":/resource/other/Prop3_pic.png";
QString prop4_pic=":/resource/other/Prop4_pic.png";

//坦克子弹模块
int bulletsnumber=5;
QString bullet1_pic=":/resource/bullet/bullet1.png";
QString bullet2_pic=":/resource/bullet/bullet2.png";
QString bullet3_pic=":/resource/bullet/bullet3.png";
QString bullet4_pic=":/resource/bullet/bullet4.png";
QString bullet5_pic=":/resource/bullet/bullet5.png";

QString TankUp=":/resource/tank/3.png";
QString TankRight=":/resource/tank/4.png";
QString TankDown=":/resource/tank/1.png";
QString TankLeft=":/resource/tank/2.png";
QString EnemyTankUp=":/resource/tank/enemy3.jpg";
QString EnemyTankRight=":/resource/tank/enemy4.jpg";
QString EnemyTankDown=":/resource/tank/enemy1.jpg";
QString EnemyTankLeft=":/resource/tank/enemy2.jpg";
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


