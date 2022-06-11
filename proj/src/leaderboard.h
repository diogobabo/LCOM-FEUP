#ifndef _LEADER_H
#define _LEADER_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "kbcKeys.h"
#include <xpms/leaderMenu.xpm>
#include "devices/graphics.h"
#include <stdio.h>
#include <string.h>
#include "snake.h"



int leaderboard();
void BoardTimerHandler();
void BoardHandlerKBC(enum KEY k);
void drawBoard(int opt);
void drawDefBoard();

#endif
