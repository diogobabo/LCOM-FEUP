#ifndef _MENU_H
#define _MENU_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include <xpms/playPart.xpm>
#include <xpms/exitPart.xpm>
#include <xpms/brick.xpm>
#include "kbcKeys.h"
#include <xpms/menu.xpm>
#include <xpms/mouseCursor.xpm>
#include "devices/graphics.h"

void MenuMouseHandler();
void MenuTimerHandler();
void drawMenu();
void drawCursor();
void drawDefMenu();
void cleanMenuBG();
void changeState();
#endif
