#ifndef _SNAKE_H
#define _SNAKE_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "keyboard.h"
#include "mouse.h"
#include "graphics.h"
#include "play.h"

enum DEVICE{
  KBC,
  TIMER,
  MOUSE,
  RTC,
  SERIAL_PORT,
};
enum STATE{
  PAUSE,
  MENU,
  PLAY_SOLO,
  PLAY_MULTIPLAYER,
  DEAD,
  EXIT,
};

void playSnakeLoop();
void InterruptRouter(enum DEVICE device);
void MenuIH(enum DEVICE device);
void PauseIH(enum DEVICE device);
void PlaySoloIH(enum DEVICE device);
void PlayMultiplayerIH(enum DEVICE device);
void DeadIH(enum DEVICE device);

#endif
