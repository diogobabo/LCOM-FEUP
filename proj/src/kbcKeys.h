#ifndef _KBC_KEYS_H
#define _KBC_KEYS_H

enum KEY{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  ENTER,
  ESC,
};

enum STATE{
  PAUSE,
  MENU,
  PLAY_SOLO,
  PLAY_MULTIPLAYER,
  DEAD,
  EXIT,
  LEADERBOARD,
};

typedef struct mouseInfo_t
{
  bool rb, mb, lb; 
  int16_t delta_x;  
  int16_t delta_y;
} mouseInfo;

typedef struct character_t {
  int x;
  int y;
  int letter;
}Character;

#endif
