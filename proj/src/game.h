#ifndef _SNAKE_H
#define _SNAKE_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "devices/keyboard.h"
#include "devices/mouse.h"
#include "snake.h"
#include "devices/graphics.h"

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

void gameLoop();
void InterruptRouter(enum DEVICE device);
void MenuIH(enum DEVICE device);
void PauseIH(enum DEVICE device);
void PlaySoloIH(enum DEVICE device);
void PlayMultiplayerIH(enum DEVICE device);
void DeadIH(enum DEVICE device);
void changePosition();

#endif
