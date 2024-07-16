#include "global.h"
#include<Qt>

//本局分数
int sumScore=0;
int highest_level1_score=0;
int highest_level2_score=0;
int highest_level3_score=0;
int highest_level4_score=0;

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
int buttonVolume=20;
int propVolume=50;
int boomVolume=50;
int victoryVolume=20;
int failVolume=20;
int startVolume=30;

QMediaPlayer* player_background=new QMediaPlayer(nullptr);
QMediaPlayer* player_boom=new QMediaPlayer(nullptr);
QMediaPlayer* player_enterButton=new QMediaPlayer(nullptr);
QMediaPlayer* player_victory=new QMediaPlayer(nullptr);
QMediaPlayer* player_fail=new QMediaPlayer(nullptr);
QMediaPlayer* player_prop=new QMediaPlayer(nullptr);
QMediaPlayer* player_start=new QMediaPlayer(nullptr);
QString start_wav="qrc:/resource/music/start_window.wav";
QString button_wav="qrc:/resource/music/buttonEnter.wav";
QString boom_wav="qrc:/resource/music/enemy_boom.wav";
QString prop_wav="qrc:/resource/music/Prop.wav";
QString main_wav="qrc:/resource/music/main_melody.wav";
QString fail_wav="qrc:resource/music/fail.wav";
QString victory_wav="qrc:/resource/music/victory.wav";
bool is_play=false;
bool is_main_music_play=false;

//素材路径
QString main_back_pic=":/resource/background/main_page.jpg";
QString login_back_pic=":/resource/background/login_back.jpg";
QString setting_back_pic=":/resource/background/setting_page.jpg";
QString score_back_pic=":/resource/background/score_page.jpg";
QString pass_page_pic=":/resource/background/pass_page.jpg";
QString fail_page_pic=":/resource/background/fail_page.jpg";
QString victory_page_pic=":/resource/background/victory_page.jpg";
QString column_pic=":/resource/background/column.jpg";
QString star1_pic=":/resource/other/star1.png";
QString star2_pic=":/resource/other/star2.png";

QString pass_ground1_gif=":/resource/background/gif1.gif";
QString pass_ground2_gif=":/resource/background/gif2.gif";
QString pass_ground3_gif=":/resource/background/gif3.gif";
QString pass_ground4_gif=":/resource/background/gif4.gif";

QString setting_tank=":/resource/other/tank.png";
QString setting_bullet=":/resource/other/bullet.png";
QString setting_prop=":/resource/other/prop.png";

QString level1_0=":/resource/map/level1_0.jpg";
QString level1_1=":/resource/map/level1_1.jpg";
QString level1_2=":/resource/map/level1_2.png";
QString level1_3=":/resource/map/level1_3.jpg";
QString level1_4=":/resource/map/level1_4.jpg";


QString level2_0=":/resource/map/level2_0.jpg";
QString level2_1=":/resource/map/level2_1.jpg";
QString level2_2=":/resource/map/level2_2.jpg";
QString level2_5=":/resource/map/level2_5.jpg";

QString level3_0=":/resource/map/level3_0.jpg";
QString level3_1=":/resource/map/level3_1.jpg";
QString level3_2=":/resource/map/level3_2.jpg";
QString level3_4=":/resource/map/level3_4.jpg";
QString level3_5=":/resource/map/level3_5.jpg";
QString level3_6=":/resource/map/level3_6.jpg";

QString level4_0=":/resource/map/level4_0.jpg";
QString level4_1=":/resource/map/level4_1.jpg";
QString level4_2=":/resource/map/level4_2.jpg";
QString level4_3=":/resource/map/level4_3.jpg";
QString level4_4=":/resource/map/level4_4.jpg";
QString level4_5=":/resource/map/level4_5.jpg";

QString prop1_pic=":/resource/other/Prop1_pic.png";
QString prop2_pic=":/resource/other/Prop2_pic.png";
QString prop3_pic=":/resource/other/Prop3_pic.png";
QString prop4_pic=":/resource/other/Prop4_pic.png";
QString frosted_ground=":/resource/map/frosted_ground.jpg";
QString fired_ground=":/resource/map/fire_ground.jpg";

//坦克子弹模块
int bulletsnumber=5;
QString bullet1_pic=":/resource/bullet/bullet1.png";
QString bullet2_pic=":/resource/bullet/bullet2.png";
QString bullet3_pic=":/resource/bullet/bullet3.png";
QString bullet4_pic=":/resource/bullet/bullet4.png";
QString bullet5_pic=":/resource/bullet/bullet5.png";
QString frost_bullet_pic=":/resource/bullet/frost_bullet.png";
QString fire_bullet_pic=":/resource/bullet/fire_bullet.png";

QString BulletBoom_gif=":/resource/bullet/Boom.gif";

QString TankUp=":/resource/tank/3.png";
QString TankRight=":/resource/tank/4.png";
QString TankDown=":/resource/tank/1.png";
QString TankLeft=":/resource/tank/2.png";
QString Enemy1TankUp=":/resource/tank/enemy3.png";
QString Enemy1TankRight=":/resource/tank/enemy4.png";
QString Enemy1TankDown=":/resource/tank/enemy1.png";
QString Enemy1TankLeft=":/resource/tank/enemy2.png";
QString Enemy2TankUp=":/resource/tank/enemy33.png";
QString Enemy2TankRight=":/resource/tank/enemy44.png";
QString Enemy2TankDown=":/resource/tank/enemy11.png";
QString Enemy2TankLeft=":/resource/tank/enemy22.png";
QString Enemy3TankUp=":/resource/tank/enemy333.png";
QString Enemy3TankRight=":/resource/tank/enemy444.png";
QString Enemy3TankDown=":/resource/tank/enemy111.png";
QString Enemy3TankLeft=":/resource/tank/enemy222.png";

QString FrostEnemyDown=":/resource/tank/FrostEnemy1.png";
QString FrostEnemyLeft=":/resource/tank/FrostEnemy2.png";
QString FrostEnemyUp=":/resource/tank/FrostEnemy3.png";
QString FrostEnemyRight=":/resource/tank/FrostEnemy4.png";
QString FireEnemyUp=":/resource/tank/firetank_Up.png";
QString FireEnemyDown=":/resource/tank/firetank_Down.png";
QString FireEnemyLeft=":/resource/tank/firetank_Left.png";
QString FireEnemyRight=":/resource/tank/firetank_Right.png";

//字体模块

QString DottedFont=":/resource/my_font/DottedSongtiSquareRegular.otf";
QString AI=":/resource/my_font/AI.ttf";
QString Titleround=":/resource/my_font/titleround.otf";
QString WinterCicada=":/resource/my_font/winter_cicada.ttf";
QString Iron=":/resource/my_font/iron.ttf";
QString Ink=":/resource/my_font/ink.ttf";
QString Cloud=":/resource/my_font/cloud.ttf";
QString Free=":/resource/my_font/free.ttf";
QString Write=":/resource/my_font/Write.ttf";
QString Spring=":/resource/my_font/Spring.ttf";
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


