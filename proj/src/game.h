#ifndef _SNAKE_H
#define _SNAKE_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "devices/keyboard.h"
#include "devices/mouse.h"
#include "snake.h"
#include "menu.h"
#include "pause.h"
#include "kbcKeys.h"
#include "devices/graphics.h"
#include "leaderboard.h"


enum DEVICE{
  KBC,
  TIMER,
  MOUSE,
  RTC,
  SERIAL_PORT
};



void gameLoop();
void InterruptRouter(enum DEVICE device);
void MenuIH(enum DEVICE device);
void PauseIH(enum DEVICE device);
void PlaySoloIH(enum DEVICE device);
void PlayMultiplayerIH(enum DEVICE device);
void DeadIH(enum DEVICE device);
void changePosition();
void updateKBC();
void loadAll();

#endif
