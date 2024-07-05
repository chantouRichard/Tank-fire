#include "global.h"
#include<Qt>

int gameVolume=50;
int KeyUp=Qt::Key_W;
int KeyLeft=Qt::Key_A;
int KeyRight=Qt::Key_D;
int KeyDown=Qt::Key_S;
int KeyShoot=Qt::Key_J;
int map_Lattice_count=25;
int bulletsnumber=5;
QString filename="/User.txt";
QMediaPlayer* player_background=new QMediaPlayer(nullptr);
QMediaPlayer* player_boom=new QMediaPlayer(nullptr);
//QMediaPlaylist* playlist = new QMediaPlaylist(player_background);


