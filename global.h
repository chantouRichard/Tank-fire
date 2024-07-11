#ifndef GLOBAL_H
#define GLOBAL_H
#include<QString>
#include<QMediaPlayer>
#include<QMediaPlaylist>

//音效模块
extern int gameVolume;
extern int buttonVolume;
extern int propVolume;
extern int boomVolume;
extern int victoryVolume;
extern int failVolume;
extern int startVolume;
extern QMediaPlayer* player_background;
extern QMediaPlayer* player_enterButton;
extern QMediaPlayer* player_boom;
extern QMediaPlayer* player_prop;
extern QMediaPlayer* player_victory;
extern QMediaPlayer* player_fail;
extern QMediaPlayer* player_start;
extern QString start_wav;
extern QString button_wav;
extern QString boom_wav;
extern QString main_wav;
extern QString fail_wav;
extern QString victory_wav;
extern QString prop_wav;
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
extern QString EnemyTankUp;
extern QString EnemyTankDown;
extern QString EnemyTankLeft;
extern QString EnemyTankRight;
//文件模块
extern QString filename;
extern QString score_filename;
extern QString User_name;
//素材路径
extern QString main_back_pic;
extern QString login_back_pic;
extern QString setting_back_pic;
extern QString score_back_pic;
extern QString pass_page_pic;
extern QString main_music;
extern QString button_enter_music;
extern QString setting_tank;
extern QString setting_bullet;
extern QString setting_prop;
extern QString level1_0;
extern QString level1_1;
extern QString level1_2;
extern QString level1_3;
extern QString level1_4;
extern QString prop1_pic;
extern QString prop2_pic;
extern QString prop3_pic;
extern QString prop4_pic;
extern QString bullet1_pic;
extern QString bullet2_pic;
extern QString bullet3_pic;
extern QString bullet4_pic;
extern QString bullet5_pic;

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
