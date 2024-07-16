#ifndef GLOBAL_H
#define GLOBAL_H
#include<QString>
#include<QMediaPlayer>
#include<QMediaPlaylist>

//本局分数
extern int sumScore;
extern int highest_level1_score;
extern int highest_level2_score;
extern int highest_level3_score;
extern int highest_level4_score;
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
extern bool is_play;   //主音乐是否播放
extern bool is_main_music_play; //主音乐是否播放
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
extern QString Enemy1TankUp;
extern QString Enemy1TankDown;
extern QString Enemy1TankLeft;
extern QString Enemy1TankRight;
extern QString Enemy2TankUp;
extern QString Enemy2TankDown;
extern QString Enemy2TankLeft;
extern QString Enemy2TankRight;
extern QString Enemy3TankUp;
extern QString Enemy3TankDown;
extern QString Enemy3TankLeft;
extern QString Enemy3TankRight;
extern QString FrostEnemyUp;
extern QString FrostEnemyDown;
extern QString FrostEnemyLeft;
extern QString FrostEnemyRight;
extern QString FireEnemyUp;
extern QString FireEnemyDown;
extern QString FireEnemyLeft;
extern QString FireEnemyRight;
extern QString BulletBoom_gif;
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
extern QString fail_page_pic;
extern QString victory_page_pic;
extern QString column_pic;
extern QString setting_tank;
extern QString setting_bullet;
extern QString setting_prop;

extern QString pass_ground1_gif;
extern QString pass_ground2_gif;
extern QString pass_ground3_gif;
extern QString pass_ground4_gif;
extern QString level1_0;
extern QString level1_1;
extern QString level1_2;
extern QString level1_3;
extern QString level1_4;
extern QString level2_0;
extern QString level2_1;
extern QString level2_2;
extern QString level2_5;
extern QString level3_0;
extern QString level3_1;
extern QString level3_2;
extern QString level3_4;
extern QString level3_5;
extern QString level3_6;
extern QString level4_0;
extern QString level4_1;
extern QString level4_2;
extern QString level4_3;
extern QString level4_4;
extern QString level4_5;
extern QString frosted_ground;
extern QString fired_ground;

extern QString prop1_pic;
extern QString prop2_pic;
extern QString prop3_pic;
extern QString prop4_pic;

extern QString bullet1_pic;
extern QString bullet2_pic;
extern QString bullet3_pic;
extern QString bullet4_pic;
extern QString bullet5_pic;
extern QString frost_bullet_pic;
extern QString fire_bullet_pic;

extern QString star1_pic;
extern QString star2_pic;
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
extern QString Write;
extern QString Spring;
extern QString Cloud;
extern QString Free;
#endif // GLOBAL_H
