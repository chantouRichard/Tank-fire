#ifndef GLOBAL_H
#define GLOBAL_H
#include<QString>
#include<QMediaPlayer>
#include<QMediaPlaylist>

//音效模块
extern int gameVolume;
extern int buttonVolumn;
extern int propVolume;
extern int boomVolumn;
extern int victoryVolume;
extern int failVolume;
extern QMediaPlayer* player_background;
extern QMediaPlayer* player_enterButton;
extern QMediaPlayer* player_boom;
extern QMediaPlayer* player_prop;
extern QMediaPlayer* player_victory;
extern QMediaPlayer* player_fail;
//键位模块
extern int KeyUp;
extern int KeyLeft;
extern int KeyRight;
extern int KeyDown;
extern int KeyShoot;
extern int KeyProp1;
extern int KeyProp2;
extern int KeyProp3;
extern int KeyProp4;
//坦克子弹模块
extern int My_speed;
extern int enemy_speed;
extern int bulletsnumber;
extern QString TankUp;
extern QString TankDown;
extern QString TankLeft;
extern QString TankRight;
//文件模块
extern QString filename;
extern QString score_filename;
extern QString User_name;
//素材路径
extern QString main_back_pic;
extern QString login_back_pic;
extern QString setting_back_pic;
extern QString score_back_pic;
extern QString score_back_pic;
extern QString main_music;
extern QString button_enter_music;
extern QString setting_tank;
extern QString setting_bullet;
extern QString setting_prop;
//地图模块
const int Mapx_size=28;
const int Mapy_size=20;
extern int MAP_Global[Mapy_size][Mapx_size];
//字体模块
extern QString DottedFont;
extern QString WinterCicada;
extern QString AI;
extern QString Titleround;
extern QString Iron;
extern QString Ink;

#endif // GLOBAL_H
