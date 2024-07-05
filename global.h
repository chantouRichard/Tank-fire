#ifndef GLOBAL_H
#define GLOBAL_H
#include<QString>
#include<QMediaPlayer>
#include<QMediaPlaylist>
extern int gameVolume;
extern int KeyUp;
extern int KeyLeft;
extern int KeyRight;
extern int KeyDown;
extern int KeyShoot;
extern int map_Lattice_count;
extern int My_speed;
extern int enemy_speed;
extern int bulletsnumber;
const int Mapx_size=25;
const int Mapy_size=25;
extern QString filename;
extern QMediaPlayer* player_background;
extern QMediaPlayer* player_boom;
extern QMediaPlaylist *playlist;

#endif // GLOBAL_H
